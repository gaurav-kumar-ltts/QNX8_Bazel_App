/*
 * $QNXLicenseC:
 * Copyright 2017, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef _SYS_CNDFS_H_INCLUDED
#define _SYS_CNDFS_H_INCLUDED

#include <inttypes.h>
#include <string.h>
#if defined(__QNXNTO__) || defined(__LINUX__) || defined(__APPLE__)
# include <pthread.h>
#elif defined(__MINGW32__) || defined(__MINGW64__)
# include <windows.h>
#endif
#if defined(__QNXNTO__)
# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
#endif


/* Make sure we have EOK, and it's 0 */
#if !defined(EOK)
# define EOK    0
#elif EOK != 0
# error Panic! EOK != 0!
#endif


#if defined (__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif /* __cplusplus */


/****************************************************************************
	SHARED-MEMORY SYNCHRONIZATION OBJECTS
 ****************************************************************************/

/*
	Inter-process synchronization is actively used only under QNX right now.

	Under Linux, shared memory is still missing. For Windows, both shared
	memory and thread synchronization across process boundaries need to be
	explored.

	The non-QNX versions of sync objects and related functions below are
	currently only used inside cndfs itself. This may change as soon as
	the questions/limitations mentioned above are resolved.
*/

/* Use a mutex for locking and a condvar for signaling */
typedef struct {
#if defined(__QNXNTO__) || defined(__LINUX__) || defined(__APPLE__)
	pthread_mutex_t     mtx;
	pthread_cond_t      cond;
#elif defined(__MINGW32__) || defined(__MINGW64__)
	/* Newer versions of Windows seem to know condvars, and newer */
	/* versions of minGW seem to even support them. As long as we */
	/* need to support older versions, stick to semaphores.       */
	CRITICAL_SECTION    cs;      /* Mimic a mutex              */
	HANDLE              sema;    /* Mimic a condition variable */
#endif
} cndfs_sync_t;


/****************************************************************************
	Lock the given sync object. The sync object must have been initialized
	by cndfs.

	Arguments:
		sync    The object to lock.

	Returns:
		EOK          Success.
		EAGAIN       Insufficient system resources available.
		EDEADLK      The calling thread already owns the sync object.
		EFAULT       A fault occurred when the kernel tried to access the
		             sync object.
		EINTR        (QNX Neutrino extension) The thread was unblocked by
		             a call to pthread_mutex_wakeup_np().
		EINVAL       Invalid sync object.
		ETIMEDOUT    A kernel timeout unblocked the call.
*/
static inline int cndfs_sync_lock(cndfs_sync_t *sync_arg) {
#if defined(__QNXNTO__) || defined(__LINUX__) || defined(__APPLE__)
	int  e;
	e = pthread_mutex_lock(&sync_arg->mtx);
	return e;
#elif defined(__MINGW32__) || defined(__MINGW64__)
	EnterCriticalSection(&sync_arg->cs);
	return EOK;
#endif
}

/****************************************************************************
	Unlock the given sync object. The sync object must have been initialized
	by cndfs and previously locked by the calling thread.

	Arguments:
		sync    The object to unlock.

	Returns:
		EOK       Success.
		EINVAL    Invalid sync object.
		EPERM     The current thread doesn't own <sync>.
*/
static inline int cndfs_sync_unlock(cndfs_sync_t *sync_arg) {
#if defined(__QNXNTO__) || defined(__LINUX__) || defined(__APPLE__)
	int  e;
	e = pthread_mutex_unlock(&sync_arg->mtx);
	return e;
#elif defined(__MINGW32__) || defined(__MINGW64__)
	LeaveCriticalSection(&sync_arg->cs);
	return EOK;
#endif
}

/****************************************************************************
	Wait for the given sync object to be signalled. The sync object must
	have been initialized by cndfs, and previously locked by a call to
	cndfs_sync_lock().

	Arguments:
		sync    The sync object to wait on.

	Returns:
		EOK       Success.
		EAGAIN    Insufficient system resources are available
		          to wait on the condition.
		EFAULT    A fault occurred trying to access <sync>.
		EINVAL    Invalid sync object.
		EPERM     The current thread doesn't own <sync>.
*/
static inline int cndfs_sync_wait(cndfs_sync_t *sync_arg) {
#if defined(__QNXNTO__) || defined(__LINUX__) || defined(__APPLE__)
	int  e;
	e = pthread_cond_wait(&sync_arg->cond, &sync_arg->mtx);
	return e;
#elif defined(__MINGW32__) || defined(__MINGW64__)
	DWORD  e;

	LeaveCriticalSection(&sync_arg->cs);
	/* There appears to be a window for race conditions here, */
	/* but since semaphores will, other than condvars, retain */
	/* the "signaled" state, there is no risk of accidentally */
	/* running into an infinite wait due to a missed "signal" */
	e = WaitForSingleObject(sync_arg->sema, INFINITE);
	switch(e) {
	case WAIT_OBJECT_0:  e = EOK;    break;
	case WAIT_ABANDONED: e = EFAULT; break;
	case WAIT_TIMEOUT:   e = EAGAIN; break;
	case WAIT_FAILED:    e = EINVAL; break;
	default:             e = EPERM;  break;
	}

	EnterCriticalSection(&sync_arg->cs);
	return e;
#endif
}

/****************************************************************************
	Signal the given sync object, to wake up threads waiting on it.
	The sync object must have been initialized by cndfs.

	Arguments:
		sync    The sync object to signal.

	Returns:
		EOK       Success.
		EFAULT    A fault occurred trying to access <sync>.
		EINVAL    Invalid sync object.
*/
static inline int cndfs_sync_signal(cndfs_sync_t *sync_arg) {
#if defined(__QNXNTO__) || defined(__LINUX__) || defined(__APPLE__)
	int  e;
	e = pthread_cond_broadcast(&sync_arg->cond);
	return e;
#elif defined(__MINGW32__) || defined(__MINGW64__)
	BOOL  e;
	int  rc = EOK;

	e = ReleaseSemaphore(sync_arg->sema, 1, NULL);
	if(!e) {
		rc = EFAULT;
	}

	return rc;
#endif
}


/****************************************************************************
	SHARED-MEMORY PROGRESS INFORMATION
 ****************************************************************************/

/* Progress information. This is mostly dynamic, i.e., it will change while  */
/* cndfs is operating. One exception is <total_bytes>, which should remain   */
/* the same all the time. It's been put in here so it can quickly be grabbed */
/* together with the number of bytes processed (<done_bytes>) in order to    */
/* calculate a percentage without reading the large cndfs_info_t structure.  */
typedef struct {
	uint64_t volatile    total_bytes;   /* Total number of bytes to process         */
	uint64_t volatile    done_bytes;    /* Number of bytes processed                */
	uint32_t volatile    seqno;         /* Increasing sequence number               */
	uint32_t volatile    status;        /* Program status, see below                */
#define CNDFS_STATUS_INITIAL    0U      /* - Program is initializing                */
#define CNDFS_STATUS_RUNNING    1U      /* - Program is running                     */
#define CNDFS_STATUS_SUCCESS    2U      /* - Program terminated successfully        */
#define CNDFS_STATUS_FAILURE    3U      /* - Program terminated with an error       */
	int32_t volatile     err_no;        /* Error code if status==CNDFS_EXIT_FAILURE */
	uint32_t volatile    zero;          /* Unused                                   */
} cndfs_progress_t;

/* Full information, including progress and file names for in- and output. */
typedef struct {
	cndfs_progress_t     progress;                    /* Progress information                  */
	uint32_t volatile    src_name_len;                /* Length of source path (w/o NUL)       */
	uint32_t volatile    dst_name_len;                /* Length of destination path (w/o NUL)  */
#define CNDFS_PATH_MAX    1024
	char                 src_name[CNDFS_PATH_MAX];    /* Source pathname (NUL-terminated)      */
	char                 dst_name[CNDFS_PATH_MAX];    /* Destination pathname (NUL-terminated) */
} cndfs_info_t;

/* The info structure defined above, combined with a sync     */
/* object, is what will be exposed via shared memory.         */
/* The 'initialized' member is polled by the client and will  */
/* be set by cndfs, hence it's volatile so the compiler knows */
/* it could potentially 'just' change in the client.          */
typedef struct {
	cndfs_info_t    info;           /* cndfs information                          */
	cndfs_sync_t    sync;           /* Synchronization between cndfs and user app */
	int volatile    initialized;    /* !0 when the shinfo is fully initialized    */
} cndfs_shinfo_t;


/****************************************************************************
	Open and map the shared-memory object containing cndfs progress
	information, then wait <retries> iterations for the <initialized>
	member of the shinfo to become true. Wait <delay_ms> milliseconds
	between retries. The function will not return success unless the
	shared-memory object has been fully initialized.

	Arguments:
		pshinfo     The address of a pointer to a shared-info structure.
		            Upon successful return, this pointer will be set
		            to point to the mapped shared-memory object.
		name        The name of the shared-memory object.
		delay_ms    Number of milliseconds to sleep between retries.
		retries     Number of times to wait for <delay_ms> milliseconds
		            and re-inspect the <initialized> member.

	Returns:
		EOK             Success.
		EACCES          Access to the shared memory object is denied.
		EAGAIN          The mapping couldn't be locked in memory (if
		                required by mlockall()), or the shared-memory
		                object isn't yet fully initialized.
		EBUSY           The shared-memory object is busy.
		EINTR           The call was interrupted by a signal.
		EINVAL          An underlying call to resmgr_open_bind() failed.
		ELOOP           Too many levels of symbolic links or prefixes.
		EMFILE          Too many file descriptors in use by this process, or
		                the number of mapped regions has reached the maximum
		                limit (see the RLIMIT_AS and RLIMIT_DATA resources
		                for setrlimit()).
		ENAMETOOLONG    The length of the name argument exceeds NAME_MAX.
		ENFILE          Too many shared memory objects are currently open
		                in the system.
		ENOENT          The named shared memory object doesn't exist.
		ENOMEM          There wasn't enough memory to satisfy the request.
		ENOSYS          The shm_open() function isn't supported by this
		                implementation.
*/
static inline int cndfs_shinfo_open_ex(cndfs_shinfo_t **pshinfo, char const *const name,
                                       int const delay_ms, unsigned retries) {
#if defined(__QNXNTO__)
	cndfs_shinfo_t  *shinfo;
	int  ecode, fd;

	fd = shm_open(name, O_RDWR, 0);
	if(-1 == fd) {
		ecode = errno;
	} else {
#if _LARGEFILE64_SOURCE - 0 > 0 && _FILE_OFFSET_BITS - 0 < 64
		shinfo = mmap64(NULL, sizeof(cndfs_shinfo_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#else
		shinfo = mmap(NULL, sizeof(cndfs_shinfo_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#endif
		close(fd);
		if(MAP_FAILED == shinfo) {
			ecode = errno;
		} else {
			struct timespec  ts;
			ts.tv_nsec = (delay_ms % 1000) * 1000000;
			ts.tv_sec  = delay_ms / 1000;
			while(!shinfo->initialized && (retries > 0)) {
				nanosleep(&ts, NULL);
				retries--;
			}

			if(!shinfo->initialized) {
				munmap(shinfo, sizeof(cndfs_shinfo_t));
				ecode = EAGAIN;
			} else {
				*pshinfo = shinfo;
				ecode = EOK;
			}
		}
	}

	return ecode;
#else
	return ENOSYS;
#endif /* __QNXNTO__ */
}

/****************************************************************************
	Open and map the shared-memory object containing cndfs progress
	information. This function will not return success unless the shared-
	memory object has been fully initialized; it will wait for up to one
	second for the object to become initialized once mapping was successful.
	To fine-tune the waiting behavior, use cndfs_shinfo_open_ex().

	Arguments:
		pshinfo    The address of a pointer to a shared-info structure.
		           Upon successful return, this pointer will be set
		           to point to the mapped shared-memory object.
		name       The name of the shared-memory object.

	Returns:
		EOK             Success.
		EACCES          Access to the shared memory object is denied.
		EAGAIN          The mapping couldn't be locked in memory (if
		                required by mlockall()), or the shared-memory
		                object isn't yet fully initialized.
		EBUSY           The shared-memory object is busy.
		EINTR           The call was interrupted by a signal.
		EINVAL          An underlying call to resmgr_open_bind() failed.
		ELOOP           Too many levels of symbolic links or prefixes.
		EMFILE          Too many file descriptors in use by this process, or
		                the number of mapped regions has reached the maximum
		                limit (see the RLIMIT_AS and RLIMIT_DATA resources
		                for setrlimit()).
		ENAMETOOLONG    The length of the name argument exceeds NAME_MAX.
		ENFILE          Too many shared memory objects are currently open
		                in the system.
		ENOENT          The named shared memory object doesn't exist.
		ENOMEM          There wasn't enough memory to satisfy the request.
		ENOSYS          The shm_open() function isn't supported by this
		                implementation.
*/
static inline int cndfs_shinfo_open(cndfs_shinfo_t **const pshinfo, char const *const name) {
#define CNDFS_SHINFO_OPEN_DFLT_DELAY_MS  10
#define CNDFS_SHINFO_OPEN_DFLT_RETRIES   100U
	return cndfs_shinfo_open_ex(pshinfo, name, CNDFS_SHINFO_OPEN_DFLT_DELAY_MS, CNDFS_SHINFO_OPEN_DFLT_RETRIES);
}

/****************************************************************************
	Unmap the shared-memory object containing cndfs progress information.

	Arguments:
		pshinfo    The address of a pointer to the shared-info structure.
		           Upon successful return, this pointer will be set
		           to NULL.

	Returns:
		EOK       Success.
		EINVAL    The address in *<pshinfo> is invalid.
		ENOMEM    The memory manager failed to allocate memory to handle the
		          munmap() request. This allocation of memory is necessary
		          for internal structures to represent the new state of
		          mapped memory.
*/
static inline int cndfs_shinfo_close(cndfs_shinfo_t **pshinfo) {
#if defined(__QNXNTO__)
	int  e;

	e = munmap(*pshinfo, sizeof(cndfs_shinfo_t));
	if(0 != e) {
		e = errno;
	} else {
		*pshinfo = NULL;
	}

	return e;
#else
	return ENOSYS;
#endif /* __QNXNTO__ */
}

/****************************************************************************
	Retrieve the current cndfs progress information.

	Arguments:
		shinfo    Pointer to the shared memory containing the progress info.
		          Can be acquired by a call to cndfs_shinfo_open().
		prg       Address of a progress structure that will be filled with
		          the current progress information upon return.

	Returns:
		EOK          Success.
		EAGAIN       Insufficient system resources available.
		EDEADLK      The calling thread already owns the sync object.
		EFAULT       A fault occurred when the kernel tried to access the
		             sync object.
		EINTR        (QNX Neutrino extension) The thread was unblocked by
		             a call to pthread_mutex_wakeup_np().
		EINVAL       Invalid sync object.
		ETIMEDOUT    A kernel timeout unblocked the call.
*/
static inline int cndfs_shinfo_get_progress(cndfs_shinfo_t *shinfo, cndfs_progress_t *const prg) {
#if defined(__QNXNTO__)
	int  e;

	e = cndfs_sync_lock(&shinfo->sync);
	if(EOK == e) {
		memcpy(prg, &shinfo->info.progress, sizeof(cndfs_progress_t));
		cndfs_sync_unlock(&shinfo->sync);
	}

	return e;
#else
	return ENOSYS;
#endif /* __QNXNTO__ */
}

/****************************************************************************
	Wait until the cndfs progress information changes, then read it.

	Arguments:
		shinfo    Pointer to the shared memory containing the progress info.
		          Can be acquired by a call to cndfs_shinfo_open().
		prg       Address of a progress structure that will be filled with
		          the current progress information upon return.

	Returns:
		EOK          Success.
		EAGAIN       Insufficient system resources available.
		EFAULT       A fault occurred when trying to access <sync>.
		EINTR        (QNX Neutrino extension) The thread was unblocked by
		             a call to pthread_mutex_wakeup_np().
		EINVAL       Invalid sync object.
		ETIMEDOUT    A kernel timeout unblocked the call.
*/
static inline int cndfs_shinfo_wait_progress(cndfs_shinfo_t *shinfo, cndfs_progress_t *const prg) {
#if defined(__QNXNTO__)
	int  e0 = cndfs_sync_lock(&shinfo->sync);

	/* Consider it ok if we already own the mutex */
	if((EOK == e0) || (EDEADLK == e0)) {
		int  e1 = EOK;

		while(shinfo->info.progress.seqno == prg->seqno) {
			e1 = cndfs_sync_wait(&shinfo->sync);
			if(EOK != e1) {
				break;
			}
		}

		if(EOK == e1) {
			memcpy(prg, &shinfo->info.progress, sizeof(cndfs_progress_t));
		}

		if(EOK == e0) {
			cndfs_sync_unlock(&shinfo->sync);
		}

		/* Locking was 'successful' if we got here. In that */
		/* case, report whatever status the wait returned.  */
		e0 = e1;
	}

	return e0;
#else
	return ENOSYS;
#endif /* __QNXNTO__ */
}

/****************************************************************************
	Retrieve cndfs progress- and file information.

	Arguments:
		shinfo    Pointer to the shared memory containing the progress info.
		          Can be acquired by a call to cndfs_shinfo_open().
		info      Address of an info structure that will be filled with the
		          progress- / file information upon return.

	Returns:
		EOK          Success.
		EAGAIN       Insufficient system resources available.
		EDEADLK      The calling thread already owns the sync object.
		EFAULT       A fault occurred when the kernel tried to access the
		             sync object.
		EINTR        (QNX Neutrino extension) The thread was unblocked by
		             a call to pthread_mutex_wakeup_np().
		EINVAL       Invalid sync object.
		ETIMEDOUT    A kernel timeout unblocked the call.
*/
static inline int cndfs_shinfo_get_info(cndfs_shinfo_t *shinfo, cndfs_info_t *const info) {
#if defined(__QNXNTO__)
	int  e;

	e = cndfs_sync_lock(&shinfo->sync);
	if(EOK == e) {
		memcpy(info, &shinfo->info, sizeof(cndfs_info_t));
		cndfs_sync_unlock(&shinfo->sync);
	}

	return e;
#else
	return ENOSYS;
#endif /* __QNXNTO__ */
}


/****************************************************************************
	KEY PROVIDER DLLs
 ****************************************************************************/

/* Key provider DLLs only supported under QNX */
#if defined(__QNXNTO__)

/* This function must be exported by a user-DLL for dynamic crypto key    */
/* provision. <filename> will be the full pathname of the condensed file; */
/* <args> will be NULL or the optional argument string given after the    */
/* DLL name on the command line (-K <dll>,<args>). The function must      */
/* provide <keylen> bytes of key data in the buffer <keybuf>. The buffer  */
/* will be 0-filled before the function is called.                        */
/* The function must return the number of key bytes generated;            */
/* any value < 0 will be treated as an error.                             */
extern int cndfs_key_provider(const char *filename, const char *args,
                              unsigned keylen, uint8_t *keybuf);

#endif /* __QNXNTO__ */


/****************************************************************************
	EXTERNAL INPUT PROVIDERS
 ****************************************************************************/

/* EIPs are only available under QNX */
#if defined(__QNXNTO__)

/****************************************************************************
	External Input Providers (EIPs) can be used to provide condensed input
	to the uncondenser from other sources than regular files. The '-x'
	option instructs cndfs to use a given EIP.

	In order to allow data to be produced by other processes, cndfs can
	expose its internal I/O buffers in a shared-memory object. This object
	will have a header containing information about the ongoing request,
	and a cndfs_sync_t synchronization object to serialize access and signal
	changes.

	If the external process is happy with using a mutex and a condvar over
	shared memory to interact with cndfs, specify the EIP on the command
	line as '-x-' and provide the shared-memory object name to use in place
	of the input file name.

	If the external process requires some other kind of interaction/protocol,
	or if the input provider doesn't need to run as a separate process, the
	EIP can be implemented as a DLL that will be loaded by cndfs. In this
	case, specify '-x <dll-name>[,<dll-arg>[,<dll-arg>...]]' on the command
	line.
*/

/****************************************************************************
	External Input Provider Memory Interface
 ****************************************************************************/

/*
	No matter whether the EIP is implemented as a DLL or as a separate
	process, the request/response interaction will always happen across
	the same data structures.
*/

/* Define a request type, describing how much data to read from which */
/* input position and where to store it in the memory buffer.         */
/* Note that the destination pointer <vaddr> will NOT be valid        */
/* when the EIP is a separate process!                                */
typedef struct {
	uint64_t     file_pos;    /* Source starting position in input [file]   */
	uint64_t     mem_off;     /* Destination offset in shared-memory object */
	paddr64_t    paddr;       /* Physical address of destination buffer     */
	void         *vaddr;      /* Destination address (only valid in DLL!)   */
	size_t       nreq;        /* Number of bytes requested by cndfs         */
} cndfs_eip_req_t;

/* Further, there is a response type. In this structure, the EIP MUST... */
/* ...tell how many bytes it successfully provided, and                  */
/* ...what the resulting error code was. This must be set to EOK on      */
/*    successful read of at least one byte!                              */
typedef struct {
	size_t    nprv;      /* Number of bytes provided by the EIP */
	int       err_no;    /* EIP error status                    */
} cndfs_eip_rsp_t;

/* Combine request and response into an I/O descriptor */
/* type for communication between cndfs and EIP.       */
typedef struct {
	cndfs_eip_req_t    req;     /* EIP request descriptor */
	cndfs_eip_rsp_t    rsp;     /* EIP response           */
} cndfs_eip_io_t;

/* Finally add a sync object to the I/O descriptor, to define a complete */
/* shared-memory object header for communication between cndfs and EIP.  */
typedef struct {
	cndfs_eip_io_t    io;      /* EIP I/O descriptor     */
	cndfs_sync_t      sync;    /* Synchronization object */
} cndfs_eip_shm_t;


/****************************************************************************
	External Input Provider DLL Interface
 ****************************************************************************/

/*
	A cndfs EIP DLL must contain one variable named 'cndfs_eip', of data type
	cndfs_eip_t. This data structure contains at least the following members:

	name
		A descriptive name of the EIP.
	init()
		An initialization function that will be called to set up the EIP.
		It has these parameters:
			path -- The command-line argument given in place of the "input
			        file". The EIP is free to use this in any way it wants.
			args -- NULL if the DLL was specified in the form "-x <dll>",
			        or a pointer to <args> if the "-x <dll>,<args>" form
			        was used.
			pshmem -- The address of a variable that the function must set
			          to the name to be used for the sahred-memory object
			          in which cndfs should expose its I/O buffers. If the
			          EIP doesn't require shared memory, set this to NULL.
			phandle -- Address of a variable that the function can set to
			           an arbitrary instance handle; this will not be used
			           by cndfs, but passed to the subsequent EIP function
			           calls.
	read()
		A function that will be called whenever cndfs requests a block of
		data to be provided. It has two parameters:
			handle -- The handle returned by init().
			shm -- A pointer to an I/O descriptor and synchronization object.
			       This is used to pass request/response information. Note
			       that this structure will not actually reside in shared
			       memory if init() set *<pshmem> to NULL.
	shutdown()
		A function that will be called when cndfs requires no more input.
		It only takes one parameter:
			handle -- The instance handle returned by init().
		Note that this function may be called before cndfs has actually
		finished uncondensing its input.
*/

/* Registration structure for an EIP DLL */
typedef struct {
	const char    *name;
	int           (*init)(const char *path, char *args,
	                      char **pshmem, void **phandle);
	int           (*read)(void *handle, cndfs_eip_io_t *io);
	int           (*shutdown)(void *handle);
} cndfs_eip_t;

/* EIP DLL registration variable */
extern cndfs_eip_t    cndfs_eip;

#endif /* __QNXNTO__ */

#if defined (__cplusplus) || defined(__CPLUSPLUS__)
}
#endif /* __cplusplus */

#endif /* _SYS_CNDFS_H_INCLUDED */
