/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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

#ifndef _NW_DATASTRUCT_H_INCLUDED
#define _NW_DATASTRUCT_H_INCLUDED

#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <sys/types.h>

#define NW_PRIORITY 21

#define NW_NAME_MAX 64

enum modload_obj_type {
	MODLOAD_CLOSED,
	MODLOAD_TOP,
	MODLOAD_DRV,
	MODLOAD_DEV,
};

/* Note the following will index the qnx_bus_devices[] array */
enum modload_pnp_device {
	MODLOAD_PNP_PCI,
	MODLOAD_PNP_OFW,
	MODLOAD_PNP_USB,

	MODLOAD_PNP_NUM
};


typedef struct modload_ocb {
	iofunc_ocb_t io_ocb;
	void *obj;                          /* object that open was on */
	enum modload_obj_type obj_type;     /* object type for obj */
} modload_ocb_t;

struct modload_dev_entry {
	iofunc_attr_t attr;                 /* first member! */
	LIST_ENTRY(modload_dev_entry) list; /* list entry */
	struct modload_mod_entry *mod_entry;/* pointer to parent */
	struct _device *bus_child;          /* device on the bus (for NPNP) */
	struct _device *dev;                /* device */
	char devname[NW_NAME_MAX];          /* device name */

	/* including struct ifnet definition causes many conflicts in
	 * qnx_options.c. instead use dev_entry_get_ifp()
	 */
	void *ifp;                          /* interface */
	char opts[PATH_MAX];                /* interface opts */
	unsigned int refs;                  /* module entry reference count */
	int removed;                        /* marked for destruction */
};
LIST_HEAD(dev_list, modload_dev_entry);
#define dev_entry_get_ifp(dev) ((struct ifnet *)dev->ifp)

struct modload_mod_opts {
	char opts[PATH_MAX];                /* next loaded opts */
	char qnxdev[NW_NAME_MAX];           /* next loaded qnxdev name */
};

struct mod_cls_entry {
	LIST_ENTRY(mod_cls_entry) list;
	char name[NW_NAME_MAX];
};
LIST_HEAD(cls_list, mod_cls_entry);

typedef enum {
	MODLOAD_MOD_TYPE_UNKNOWN,
	MODLOAD_MOD_TYPE_MODULE,
	MODLOAD_MOD_TYPE_DRIVER,
	MODLOAD_MOD_TYPE_MAX
} modload_mod_type_t;

struct modload_mod_entry {
	iofunc_attr_t attr;                 /* first member! */
	LIST_ENTRY(modload_mod_entry) list; /* list entry */
	char path[PATH_MAX];                /* full path name */
	char name[NW_NAME_MAX];             /* module name */
	struct modload_mod_opts next_opts;  /* next loaded opts */
	struct dev_list loaded_devs;        /* loaded devices */
	pthread_mutex_t loaded_devs_lock;   /* loaded devices list lock */
	unsigned int refs;                  /* module entry reference count */
	int unloaded;                       /* marked for destruction */
	struct cls_list classes;            /* module object class names */
	modload_mod_type_t type;            /* module type (for path autocomplete) */
};
LIST_HEAD(mod_list, modload_mod_entry);

struct nw_stk_ctl {
	/* mount stuff */
	iofunc_attr_t       attr; /* first member! */
	int                 mount_handler_id;
	int                 mount_path_id;
	char                mount_name[PATH_MAX];

	/* resmgr stuff */
	int                 chid;
	int                 chan_width;
	dispatch_t          *dpp;

	/* startup stuff */
	const char          *prefix;
	const char          *config;
	bool                run_foreground;
	unsigned long       max_stack_size;
	int                 priority;
};

struct iosock_ctp {
	struct thread *td;
};

#define CTP2SCTP(ctp) ((ctp)->resmgr_context.extra->data)
#define RCTX2SCTP(ctp) ((ctp)->extra->data)

extern struct nw_stk_ctl stk_ctl;

static __inline struct nw_stk_ctl *sctlp(void);

static __inline struct nw_stk_ctl *

sctlp(void)
{
	return (&stk_ctl);
}

void qnx_kthread_context_free(struct thread *td);
int qnx_kthread_context_alloc(struct thread **newtdp);

#endif /* !_NW_DATASTRUCT_H_INCLUDED */
