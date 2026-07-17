/*
 * This file is @generated automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   ../qnx/ptp/ptp_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _ptp_if_h_
#define _ptp_if_h_

/** @brief Unique descriptor for the PTP_READ_TIME() method */
extern struct kobjop_desc ptp_read_time_desc;
/** @brief A function implementing the PTP_READ_TIME() method */
typedef int ptp_read_time_t(device_t dev, struct ptp_time *ptp_time);
/**
 * @brief Read the current ptp clock time
 *
 * @details Called with @c ptp_mtx locked. @c ptp_time must be within the bounds:
 * - @c ptp_time.sec <= @c MAX_SECONDS (provided in @e ptp_attach() )
 * - @c ptp_time.sec > @c 0
 * - @c ptp_time.nsec < @c 1000000000 (equivalent to 1s)
 * - @c ptp_time.nsec > @c 0
 * This function is required.
 *
 * @param[in]  dev      A driver's @c device_t struct given on @e ptp_attach().
 * @param[out] ptp_time Current ptp clock time.
 *
 * @retval EOK  @c ptp_time set to current PTP clock time
 * @retval !EOK Failure
 */

static __inline int PTP_READ_TIME(device_t dev, struct ptp_time *ptp_time)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,ptp_read_time);
	rc = ((ptp_read_time_t *) _m)(dev, ptp_time);
	return (rc);
}

/** @brief Unique descriptor for the PTP_WRITE_TIME() method */
extern struct kobjop_desc ptp_write_time_desc;
/** @brief A function implementing the PTP_WRITE_TIME() method */
typedef int ptp_write_time_t(device_t dev, struct ptp_time *ptp_time);
/**
 * @brief Set the ptp clock to the provided time
 *
 * @details Called with @c ptp_mtx locked. You may assume @c ptp_time follows
 * the same bounds as required in @e ptp_read_time(). This function is required.
 *
 * @param[in] dev      A driver's @c device_t struct given on @e ptp_attach().
 * @param[in] ptp_time Provided time to write to the ptp clock.
 *
 * @retval EOK  @c ptp_time written to PTP clock
 * @retval !EOK Failure
 */

static __inline int PTP_WRITE_TIME(device_t dev, struct ptp_time *ptp_time)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,ptp_write_time);
	rc = ((ptp_write_time_t *) _m)(dev, ptp_time);
	return (rc);
}

/** @brief Unique descriptor for the PTP_WRITE_COMP() method */
extern struct kobjop_desc ptp_write_comp_desc;
/** @brief A function implementing the PTP_WRITE_COMP() method */
typedef int ptp_write_comp_t(device_t dev, struct ptp_comp *comp);
/**
 * @brief Write the ptp clock's clock adjustments
 *
 * @details This function is required. Updates the logical clock addend hardware.
 * Syntonization in PTP is optional, but mandatory in gPTP.
 *
 * @param[in] dev  A driver's @c device_t struct given on @e ptp_attach().
 * @param[in] comp Requested addend adjustment value and sign.
 *
 * @retval EOK  PTP clock adjusted by @c comp
 * @retval !EOK Failure
 */

static __inline int PTP_WRITE_COMP(device_t dev, struct ptp_comp *comp)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,ptp_write_comp);
	rc = ((ptp_write_comp_t *) _m)(dev, comp);
	return (rc);
}

/** @brief Unique descriptor for the PTP_READ_COMP() method */
extern struct kobjop_desc ptp_read_comp_desc;
/** @brief A function implementing the PTP_READ_COMP() method */
typedef int ptp_read_comp_t(device_t dev, struct ptp_comp *comp);
/**
 * @brief Read the ptp clock's clock adjustments
 *
 * @details This function is not required.
 *
 * @param[in]  dev  A driver's @c device_t struct given on @e ptp_attach().
 * @param[out] comp PTP clock's current addend adjustment value and sign.
 *
 * @retval EOK  @c comp set to current PTP clock adjustment value
 * @retval !EOK Failure
 */

static __inline int PTP_READ_COMP(device_t dev, struct ptp_comp *comp)
{
	kobjop_t _m;
	int rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,ptp_read_comp);
	rc = ((ptp_read_comp_t *) _m)(dev, comp);
	return (rc);
}

/** @brief Unique descriptor for the PTP_COMPARE_HDR() method */
extern struct kobjop_desc ptp_compare_hdr_desc;
/** @brief A function implementing the PTP_COMPARE_HDR() method */
typedef bool ptp_compare_hdr_t(device_t dev, struct ptp_uhdr *mod,
                               struct ptp_uhdr *drv);
/**
 * @brief Compare two @c ptp_uhdr structures.
 *
 * @details This function is required @b iff the TX timestamp is returned via
 * an interrupt, @b AND @e ptp_txintr_finish() is called. It should be
 * constructed with the @c PTP_UHDR_* macros, and must return @c true at the end
 * of the function. @c mod will have its values in host byte order.
 *
 * @param[in] dev A driver's @c device_t struct given on @c ptp_attach().
 * @param[in] mod @c ptp_uhdr copied from @c ptp_txintr()
 * @param[in] drv @c ptp_uhdr provided as an argument to @c ptp_txintr_finish()
 *
 * @retval true  @c mod and @c drv are equivalent
 * @retval false @c mod and @c drv are not equivalent
 */

static __inline bool PTP_COMPARE_HDR(device_t dev, struct ptp_uhdr *mod,
                                     struct ptp_uhdr *drv)
{
	kobjop_t _m;
	bool rc;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,ptp_compare_hdr);
	rc = ((ptp_compare_hdr_t *) _m)(dev, mod, drv);
	return (rc);
}

#endif /* _ptp_if_h_ */
