#ifndef MEMCHUNK_H
#define MEMCHUNK_H

#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/rsrcdbmgr.h>
#include <sys/syspage.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>

/* see memchunk_global_usr_init() */
#define MEMCHUNK_PRE_ALLOC   ( 1 << 0 )
#define MEMCHUNK_FIXED       ( 1 << 1 )
#define MEMCHUNK_FIXED_WEAK  ( 1 << 2 )

typedef union MemchunkEntry {
    union MemchunkEntry        *link;
    struct MemchunkHdr         *owner;
} MemchunkEntry;

typedef struct {
    size_t            nbytes;
    MemchunkEntry     filler;
} MemchunkExternal;

typedef struct MemchunkHdr {
    struct MemchunkHdr    *link;
    MemchunkEntry         *unused;
    paddr_t                paddr;
    unsigned short         used;
    unsigned short         ctrl;
} MemchunkHdr;

typedef struct {
    unsigned short     capacity;        // Size of each chunk
    unsigned short     count;          // Number of chunks to allocate at a time
    int                available;
    MemchunkHdr        *header;
} MemchunkBucket;

typedef struct memchunk_ctrl {
    pthread_mutex_t    mutex;
    int                pagesize;
    unsigned           pflags;
    size_t            *cfg;

#ifndef ALLOC_0_NULL
    int                zero;
#endif
    int                nbytes;
    int                slogcode;

    MemchunkBucket     buckets[1];
} memchunk_ctrl;

extern struct memchunk_ctrl *mctrl_global;

/* Variants */
void pci_memchunk_global_init_once (void);

/* Public */

/*
 *  Initialise memchunk using user configured defaults.  This mechanism will
 *  allow clients to define their own memory pools sized to each use case.
 *  Control will be stored in internal global variable.
 *
 *      cfg    Array of size_t elements representing bucket size.  That is,
 *             the size of elements to be allocated from that bucket.
 *      cfg_n  Number of elements in each bucket.
 *      n      Number of buckets
 *      flags
 *          MEMCHUNK_PRE_ALLOC  - Requested buckets all fully allocated at startup.
 *                                Else they are allocated as needed.
 *          MEMCHUNK_FIXED      - Do not allow any additional allocations after initialization.
 *          MEMCHUNK_FIXED_WEAK - Warn if bucket capacities are exceeded but do best effort
 *                                to get more memory from the system
 *
 *     Returns
 *         EALREADY Global memchunk_ctrl already allocated.
 *         EOK      success
 *         ENOMEN   Failed to initialize buckets
 *
 */
int memchunk_global_usr_init( const size_t cfg[], const size_t cfg_n[], int n, unsigned flags );

/*
 *  Initialise memchunk. Contol data structure to be explicitly managed by caller.
 *  Allows different subsystems to specify own pools.
 *
 *      Other args same as memchunk_global_usr_init()
 *      memchunk_ctrl - double pointer which will point to newly allocated and initialized memchunk_ctrl structure
 *
 *     Returns
 *         EALREADY Global memchunk_ctrl already allocated.
 *         EOK      success
 *         ENOMEN   Failed to initialize buckets
 *
 */
extern int memchunk_init( const size_t cfg[], const size_t cfg_n[], int n, unsigned flags, memchunk_ctrl **init_ctrl );


/*
 *  Destroy memchunk_ctrl structure
 *
 *      memchunk_ctrl - double pointer to structure for destruction and free
 */
extern int memchunk_destroy(struct memchunk_ctrl **mctrl);

/*
 *  Alloc
 *
 *      mctrl    Which memchunk pools to allocate from.  If NULL, a default pool will be selected from.
 *
 */
extern void* memchunk_malloc(struct memchunk_ctrl *mctrl, size_t nbytes);
extern void* memchunk_calloc(struct memchunk_ctrl *mctrl, int n, size_t nbytes);
extern void memchunk_free( struct memchunk_ctrl *mctrl, const void *ptr);


/*
 *  Test if memchunk is initialized.
 *
 */
extern int memchunk_use( void );




#endif
