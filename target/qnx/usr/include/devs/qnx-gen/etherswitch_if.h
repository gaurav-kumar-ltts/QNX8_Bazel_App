/*
 * This file is @generated automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   ../dev/etherswitch/etherswitch_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _etherswitch_if_h_
#define _etherswitch_if_h_

/** @brief Unique descriptor for the ETHERSWITCH_GETINFO() method */
extern struct kobjop_desc etherswitch_getinfo_desc;
/** @brief A function implementing the ETHERSWITCH_GETINFO() method */
typedef etherswitch_info_t* etherswitch_getinfo_t(device_t dev);

static __inline etherswitch_info_t* ETHERSWITCH_GETINFO(device_t dev)
{
	kobjop_t _m;
	etherswitch_info_t* rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_getinfo);
	rc = ((etherswitch_getinfo_t *) _m)(dev);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_LOCK() method */
extern struct kobjop_desc etherswitch_lock_desc;
/** @brief A function implementing the ETHERSWITCH_LOCK() method */
typedef void etherswitch_lock_t(device_t dev);

static __inline void ETHERSWITCH_LOCK(device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_lock);
	((etherswitch_lock_t *) _m)(dev);
}

/** @brief Unique descriptor for the ETHERSWITCH_UNLOCK() method */
extern struct kobjop_desc etherswitch_unlock_desc;
/** @brief A function implementing the ETHERSWITCH_UNLOCK() method */
typedef void etherswitch_unlock_t(device_t dev);

static __inline void ETHERSWITCH_UNLOCK(device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_unlock);
	((etherswitch_unlock_t *) _m)(dev);
}

/** @brief Unique descriptor for the ETHERSWITCH_READREG() method */
extern struct kobjop_desc etherswitch_readreg_desc;
/** @brief A function implementing the ETHERSWITCH_READREG() method */
typedef int etherswitch_readreg_t(device_t dev, int reg);

static __inline int ETHERSWITCH_READREG(device_t dev, int reg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_readreg);
	rc = ((etherswitch_readreg_t *) _m)(dev, reg);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_WRITEREG() method */
extern struct kobjop_desc etherswitch_writereg_desc;
/** @brief A function implementing the ETHERSWITCH_WRITEREG() method */
typedef int etherswitch_writereg_t(device_t dev, int reg, int value);

static __inline int ETHERSWITCH_WRITEREG(device_t dev, int reg, int value)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_writereg);
	rc = ((etherswitch_writereg_t *) _m)(dev, reg, value);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_READPHYREG() method */
extern struct kobjop_desc etherswitch_readphyreg_desc;
/** @brief A function implementing the ETHERSWITCH_READPHYREG() method */
typedef int etherswitch_readphyreg_t(device_t dev, int phy, int reg);

static __inline int ETHERSWITCH_READPHYREG(device_t dev, int phy, int reg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_readphyreg);
	rc = ((etherswitch_readphyreg_t *) _m)(dev, phy, reg);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_WRITEPHYREG() method */
extern struct kobjop_desc etherswitch_writephyreg_desc;
/** @brief A function implementing the ETHERSWITCH_WRITEPHYREG() method */
typedef int etherswitch_writephyreg_t(device_t dev, int phy, int reg,
                                      int value);

static __inline int ETHERSWITCH_WRITEPHYREG(device_t dev, int phy, int reg,
                                            int value)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_writephyreg);
	rc = ((etherswitch_writephyreg_t *) _m)(dev, phy, reg, value);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_GETPORT() method */
extern struct kobjop_desc etherswitch_getport_desc;
/** @brief A function implementing the ETHERSWITCH_GETPORT() method */
typedef int etherswitch_getport_t(device_t dev, etherswitch_port_t *vg);

static __inline int ETHERSWITCH_GETPORT(device_t dev, etherswitch_port_t *vg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_getport);
	rc = ((etherswitch_getport_t *) _m)(dev, vg);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_SETPORT() method */
extern struct kobjop_desc etherswitch_setport_desc;
/** @brief A function implementing the ETHERSWITCH_SETPORT() method */
typedef int etherswitch_setport_t(device_t dev, etherswitch_port_t *vg);

static __inline int ETHERSWITCH_SETPORT(device_t dev, etherswitch_port_t *vg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_setport);
	rc = ((etherswitch_setport_t *) _m)(dev, vg);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_GETVGROUP() method */
extern struct kobjop_desc etherswitch_getvgroup_desc;
/** @brief A function implementing the ETHERSWITCH_GETVGROUP() method */
typedef int etherswitch_getvgroup_t(device_t dev, etherswitch_vlangroup_t *vg);

static __inline int ETHERSWITCH_GETVGROUP(device_t dev,
                                          etherswitch_vlangroup_t *vg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_getvgroup);
	rc = ((etherswitch_getvgroup_t *) _m)(dev, vg);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_SETVGROUP() method */
extern struct kobjop_desc etherswitch_setvgroup_desc;
/** @brief A function implementing the ETHERSWITCH_SETVGROUP() method */
typedef int etherswitch_setvgroup_t(device_t dev, etherswitch_vlangroup_t *vg);

static __inline int ETHERSWITCH_SETVGROUP(device_t dev,
                                          etherswitch_vlangroup_t *vg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_setvgroup);
	rc = ((etherswitch_setvgroup_t *) _m)(dev, vg);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_GETCONF() method */
extern struct kobjop_desc etherswitch_getconf_desc;
/** @brief A function implementing the ETHERSWITCH_GETCONF() method */
typedef int etherswitch_getconf_t(device_t dev, etherswitch_conf_t *conf);

static __inline int ETHERSWITCH_GETCONF(device_t dev, etherswitch_conf_t *conf)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_getconf);
	rc = ((etherswitch_getconf_t *) _m)(dev, conf);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_SETCONF() method */
extern struct kobjop_desc etherswitch_setconf_desc;
/** @brief A function implementing the ETHERSWITCH_SETCONF() method */
typedef int etherswitch_setconf_t(device_t dev, etherswitch_conf_t *conf);

static __inline int ETHERSWITCH_SETCONF(device_t dev, etherswitch_conf_t *conf)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_setconf);
	rc = ((etherswitch_setconf_t *) _m)(dev, conf);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_FLUSH_ALL() method */
extern struct kobjop_desc etherswitch_flush_all_desc;
/** @brief A function implementing the ETHERSWITCH_FLUSH_ALL() method */
typedef int etherswitch_flush_all_t(device_t dev);

static __inline int ETHERSWITCH_FLUSH_ALL(device_t dev)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_flush_all);
	rc = ((etherswitch_flush_all_t *) _m)(dev);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_FLUSH_MAC() method */
extern struct kobjop_desc etherswitch_flush_mac_desc;
/** @brief A function implementing the ETHERSWITCH_FLUSH_MAC() method */
typedef int etherswitch_flush_mac_t(device_t dev,
                                    etherswitch_atu_flush_macentry_t *entry);

static __inline int ETHERSWITCH_FLUSH_MAC(device_t dev,
                                          etherswitch_atu_flush_macentry_t *entry)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_flush_mac);
	rc = ((etherswitch_flush_mac_t *) _m)(dev, entry);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_FLUSH_PORT() method */
extern struct kobjop_desc etherswitch_flush_port_desc;
/** @brief A function implementing the ETHERSWITCH_FLUSH_PORT() method */
typedef int etherswitch_flush_port_t(device_t dev, int port);

static __inline int ETHERSWITCH_FLUSH_PORT(device_t dev, int port)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_flush_port);
	rc = ((etherswitch_flush_port_t *) _m)(dev, port);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_FETCH_TABLE() method */
extern struct kobjop_desc etherswitch_fetch_table_desc;
/** @brief A function implementing the ETHERSWITCH_FETCH_TABLE() method */
typedef int etherswitch_fetch_table_t(device_t dev,
                                      etherswitch_atu_table_t *table);

static __inline int ETHERSWITCH_FETCH_TABLE(device_t dev,
                                            etherswitch_atu_table_t *table)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_fetch_table);
	rc = ((etherswitch_fetch_table_t *) _m)(dev, table);
	return (rc);
}

/** @brief Unique descriptor for the ETHERSWITCH_FETCH_TABLE_ENTRY() method */
extern struct kobjop_desc etherswitch_fetch_table_entry_desc;
/** @brief A function implementing the ETHERSWITCH_FETCH_TABLE_ENTRY() method */
typedef int etherswitch_fetch_table_entry_t(device_t dev,
                                            etherswitch_atu_entry_t *entry);

static __inline int ETHERSWITCH_FETCH_TABLE_ENTRY(device_t dev,
                                                  etherswitch_atu_entry_t *entry)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,etherswitch_fetch_table_entry);
	rc = ((etherswitch_fetch_table_entry_t *) _m)(dev, entry);
	return (rc);
}

#endif /* _etherswitch_if_h_ */
