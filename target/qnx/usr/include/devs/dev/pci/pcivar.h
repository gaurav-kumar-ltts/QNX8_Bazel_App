/*
 * $QNXLicenseC:
 * Copyright 2018, QNX Software Systems. All Rights Reserved.
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

#ifndef _PCIVAR_H__
#define _PCIVAR_H__
struct pci_device_table {
#if BYTE_ORDER == LITTLE_ENDIAN
	uint16_t
		match_flag_vendor:1,
		match_flag_device:1,
		match_flag_subvendor:1,
		match_flag_subdevice:1,
		match_flag_class:1,
		match_flag_subclass:1,
		match_flag_revid:1,
		match_flag_unused:9;
#else
	uint16_t
		match_flag_unused:9,
		match_flag_revid:1,
		match_flag_subclass:1,
		match_flag_class:1,
		match_flag_subdevice:1,
		match_flag_subvendor:1,
		match_flag_device:1,
		match_flag_vendor:1;
#endif
	uint16_t	vendor;
	uint16_t	device;
	uint16_t	subvendor;
	uint16_t	subdevice;
	uint16_t	class_id;
	uint16_t	subclass;
	uint16_t	revid;
	uint16_t	unused;
	uintptr_t	driver_data;
	char		*descr;
};

typedef uint64_t pci_addr_t;

struct pci_map {
    pci_addr_t	pm_value;	/* Raw BAR value */
    pci_addr_t	pm_size;
    uint16_t	pm_reg;
    STAILQ_ENTRY(pci_map) pm_link;
};

#define	PCI_DEV_FBSD(v, d)						\
	.match_flag_vendor = 1, .vendor = (v),				\
	.match_flag_device = 1, .device = (d)
#define	PCI_SUBDEV(sv, sd)						\
	.match_flag_subvendor = 1, .subvendor = (sv),			\
	.match_flag_subdevice = 1, .subdevice = (sd)
#define	PCI_CLASS(x)							\
	.match_flag_class = 1, .class_id = (x)
#define	PCI_SUBCLASS(x)							\
	.match_flag_subclass = 1, .subclass = (x)
#define	PCI_REVID(x)							\
	.match_flag_revid = 1, .revid = (x)
#define	PCI_DESCR(x)							\
	.descr = (x)
#define PCI_PNP_STR							\
	"M16:mask;U16:vendor;U16:device;U16:subvendor;U16:subdevice;"	\
	"U16:class;U16:subclass;U16:revid;"
#define PCI_PNP_INFO(table)						\
	MODULE_PNP_INFO(PCI_PNP_STR, pci, table, table,			\
	    sizeof(table) / sizeof(table[0]))

/* From pci_if.m/pci_if.h */
enum pci_id_type {
    PCI_ID_RID,
    PCI_ID_MSI,
};
int PCI_GET_ID(device_t dev, device_t child, enum pci_id_type type, uintptr_t *id);

const struct pci_device_table *pci_match_device(device_t child,
    const struct pci_device_table *id, size_t nelt);
#define PCI_MATCH(child, table) \
	pci_match_device(child, (table), nitems(table));

int pci_get_as_type(device_t, int bar);
int pci_get_domain(device_t);
int pci_get_bus(device_t);
int pci_get_slot(device_t);
int pci_get_function(device_t);
uint16_t pci_get_vendor(device_t);
uint16_t pci_get_device(device_t);
uint8_t pci_get_revid(device_t);
uint8_t pci_get_cachelnsz(device_t dev);
uint16_t pci_get_subvendor(device_t);
uint16_t pci_get_subdevice(device_t);
uint32_t pci_get_class(device_t);
device_t pci_find_dbsf(uint32_t domain, uint8_t bus, uint8_t slot, uint8_t func);
struct resource_list * pci_get_resource_list(device_t dev);

bool pci_has_pm(device_t dev);
uint32_t pci_read_config(device_t dev, int reg, int width);
void pci_write_config(device_t dev, int reg, uint32_t val, int width);

int pci_get_max_read_req(device_t dev);
int pci_set_max_read_req(device_t dev, int size);

int pci_enable_busmaster(device_t dev);
int pci_disable_busmaster(device_t dev);

int pci_find_cap(device_t dev, int capability, int *capreg);
int pci_find_next_cap(device_t dev, int capability, int start, int *capreg);
int pci_msi_count(device_t dev);
int pci_msix_count(device_t dev);
int pci_msix_table_bar(device_t dev);
int pci_msix_pba_bar(device_t dev);
int pci_alloc_msi(device_t dev, int *count);
int pci_alloc_msix(device_t dev, int *count);
int pci_release_msi(device_t dev);
int pci_translate_dma(device_t dev, bus_addr_t start, bus_size_t len, bus_addr_t *newstart);

static __inline int
pci_get_id(device_t dev, enum pci_id_type type, uintptr_t *id)
{
    return (PCI_GET_ID(device_get_parent(dev), dev, type, id));
}


#endif
