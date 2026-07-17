/*
 * This file is @generated automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   ../dev/mdio/mdio_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _mdio_if_h_
#define _mdio_if_h_

/** @brief Unique descriptor for the MDIO_READREG() method */
extern struct kobjop_desc mdio_readreg_desc;
/** @brief A function implementing the MDIO_READREG() method */
typedef int mdio_readreg_t(device_t dev, int phy, int reg);
/**
 * @brief Read register from device on MDIO bus.
 *
 * @param dev	MDIO bus device.
 * @param phy	PHY address.
 * @param reg	The PHY register offset.
 */

static __inline int MDIO_READREG(device_t dev, int phy, int reg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mdio_readreg);
	rc = ((mdio_readreg_t *) _m)(dev, phy, reg);
	return (rc);
}

/** @brief Unique descriptor for the MDIO_READREG_MUX() method */
extern struct kobjop_desc mdio_readreg_mux_desc;
/** @brief A function implementing the MDIO_READREG_MUX() method */
typedef int mdio_readreg_mux_t(device_t dev, int bus, int phy, int reg);
/**
 * @brief Read register from device on MDIO muxed bus.
 *
 * @param dev	MDIO bus device.
 * @param bus	MDIO bus mux position
 * @param phy	PHY address.
 * @param reg	The PHY register offset.
 */

static __inline int MDIO_READREG_MUX(device_t dev, int bus, int phy, int reg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mdio_readreg_mux);
	rc = ((mdio_readreg_mux_t *) _m)(dev, bus, phy, reg);
	return (rc);
}

/** @brief Unique descriptor for the MDIO_WRITEREG() method */
extern struct kobjop_desc mdio_writereg_desc;
/** @brief A function implementing the MDIO_WRITEREG() method */
typedef int mdio_writereg_t(device_t dev, int phy, int reg, int val);
/**
 * @brief Write register to device on MDIO bus.
 *
 * @param dev	MDIO bus device.
 * @param phy	PHY address.
 * @param reg	The PHY register offset.
 * @param val	The value to write at offset @p reg.
 */

static __inline int MDIO_WRITEREG(device_t dev, int phy, int reg, int val)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mdio_writereg);
	rc = ((mdio_writereg_t *) _m)(dev, phy, reg, val);
	return (rc);
}

/** @brief Unique descriptor for the MDIO_WRITEREG_MUX() method */
extern struct kobjop_desc mdio_writereg_mux_desc;
/** @brief A function implementing the MDIO_WRITEREG_MUX() method */
typedef int mdio_writereg_mux_t(device_t dev, int bus, int phy, int reg,
                                int val);
/**
 * @brief Write register to device on MDIO muxed bus.
 *
 * @param dev	MDIO bus device.
 * @param bus	MDIO bus mux position
 * @param phy	PHY address.
 * @param reg	The PHY register offset.
 * @param val	The value to write at offset @p reg.
 */

static __inline int MDIO_WRITEREG_MUX(device_t dev, int bus, int phy, int reg,
                                      int val)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mdio_writereg_mux);
	rc = ((mdio_writereg_mux_t *) _m)(dev, bus, phy, reg, val);
	return (rc);
}

/** @brief Unique descriptor for the MDIO_READEXTREG() method */
extern struct kobjop_desc mdio_readextreg_desc;
/** @brief A function implementing the MDIO_READEXTREG() method */
typedef int mdio_readextreg_t(device_t dev, int phy, int devad, int reg);
/**
 * @brief Read extended register from device on MDIO bus.
 *
 * @param dev	MDIO bus device.
 * @param phy	PHY address.
 * @param devad The MDIO IEEE 802.3 Clause 45 device address, or
 *		MDIO_DEVADDR_NONE to request Clause 22 register addressing.
 * @param reg	The PHY register offset.
 */

static __inline int MDIO_READEXTREG(device_t dev, int phy, int devad, int reg)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mdio_readextreg);
	rc = ((mdio_readextreg_t *) _m)(dev, phy, devad, reg);
	return (rc);
}

/** @brief Unique descriptor for the MDIO_WRITEEXTREG() method */
extern struct kobjop_desc mdio_writeextreg_desc;
/** @brief A function implementing the MDIO_WRITEEXTREG() method */
typedef int mdio_writeextreg_t(device_t dev, int phy, int devad, int reg,
                               int val);
/**
 * @brief Write extended register to device on MDIO bus.
 *
 * @param dev	MDIO bus device.
 * @param phy	PHY address.
 * @param devad The MDIO IEEE 802.3 Clause 45 device address, or
 *		MDIO_DEVADDR_NONE to request Clause 22 register addressing.
 * @param reg	The PHY register offset.
 * @param val	The value to write at offset @p reg.
 */

static __inline int MDIO_WRITEEXTREG(device_t dev, int phy, int devad, int reg,
                                     int val)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mdio_writeextreg);
	rc = ((mdio_writeextreg_t *) _m)(dev, phy, devad, reg, val);
	return (rc);
}

#endif /* _mdio_if_h_ */
