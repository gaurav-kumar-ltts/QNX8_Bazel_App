#ifndef _PCI_ERROR_H_
#define _PCI_ERROR_H_
/*
 * $QNXLicenseC:
 * Copyright (c) 2019 QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#include <time.h>

#include <pci/pci.h>
#include <pci/cap_pcie.h>
#include <pci/capx_aer.h>


/*
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 PCI/PCIe Error Events and error handling APIs

 In addition to the event handling APIs which allow for notification of error
 events, the error handling APIs allow users to retrieve and process the error
 records associated with a specific device.

 This file should be read in conjunction with pci/pci_event.h

 By default, when an error event is successfully created and registered, the
 client will receive an event notification indicating that the error event of
 interest occurred. Depending on the error handling policy of the system, for
 some clients this may be all that is required.

 For other clients, details regarding register values and the state of affected
 device(s) may be required in order to take corrective action, again based on
 the error handling policy of the system. This additional information is
 contained within a separate error record ('pci_err_record_t') which will be
 automatically retrieved for the client and provided to the registered handler
 function if the error event ('pci_event_t') is created with the appropriate
 attributes. See 'pci_event_type_e' error events in pci/pci_event.h for details
 on how to indicate interest in error record retrieval

 In addition, and because response to error events may be considered critical
 in a given system, the event handling infrastructure described in
 pci/pci_event.h will allow individual threads to be created for specific error
 events or groups of events for specific devices or groups of devices. Thread
 priority and scheduling can all be similarly controlled

 For PCIe devices which support the Advanced Error Handling (AER) capability,
 the PCIe specification allows for the individual masking of specific
 correctable and uncorrectable errors as well as for specifying the severity of
 uncorrectable errors

 Advanced Error Reporting (AER) capability registers
 ---------------------------------------------------

 It is the responsibility of the user/system designer as part of the overall
 definition of the system error handling policy, to make any modifications of
 the AER mask and severity registers from their default values. This can be
 accomplished using the APIs defined in pci/capx_aer.h

 Post reset of any device configured for error event reporting, the current
 setting of the mask and severity registers will be automatically restored so
 these registered need only be configured once

 ECRC generation and checking will be always be enabled in all devices which
 support it unless explicitly excluded from uncorrectable error reporting by
 the error event handling module.
 See the 'use' information in pci_server-error_event_handler.so for more details
 Users can modify the severity of ECRC errors as well as mask them altogether
 as defined below

 Multi-header recording will be always be enabled in all devices which support
 it unless the device has been explicitly excluded from all error reporting by
 the error event handling module.
 See the 'use' information in pci_server-error_event_handler.so for more details
 The validity of the header and TLP prefix logs are marked in the error record
 as defined below

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

/*
 ===============================================================================
 pci_err_record_id_t

 Partition wide unique identifier associated with a 'pci_err_record_t'. In the
 case of receiving multiple error event notifications (from either the same or
 a different device) for which a 'pci_err_record_t' is generated, this value
 uniquely associates the event occurrence with the generated error record

 Valid values are from 1 to the maximum value represented by the type, currently
 65535 after which the values will be reused

 Although ID values will generally increase linearly (modulo 65536) they will
 not necessarily increase sequentially for a given event for a given device
 because the ID is unique system wide. Clients should not assume the relative
 occurrence of events based on the ID alone. For that, the 'pci_err_record_t'
 contains a 'timestamp' which will indicate this information

*/
typedef uint16_t	pci_err_record_id_t;

/*
 ===============================================================================
 pci_error_regs_t

 This structure holds the relevant device and error reporting agent registers
 of the error record

 The 'valid' sub-fields will only be set true if all of the registers to which
 the 'valid' field applies were retrieved successfully and contain valid values
 If the 'valid' field is false, one or more of the register sub-fields may or
 may not contain valid values (in the case there is more than one associated
 register)

*/
typedef struct
{
	struct device_regs_s
	{
		pci_stat_t stat_reg;
		struct
		{
			/* 'valid' is true if
			 *     - PCIe is supported and 'dev_stat_reg' contains a valid value
			 */
			bool_t valid;
			cap_pcie_stat_reg_t dev_stat_reg;
			struct
			{
				/*
				 * 'valid' is true if
				 *    - AER is supported
				 *    AND depending on whether CERR or UCERR
				 *    - correctable.status and correctable.mask registers
				 *      both contain valid values
				 *    - uncorrectable.status, uncorrectable.mask and
				 *      uncorrectable.severity registers all contain valid
				 *      values
				 */
				bool_t valid;
				union
				{
					struct
					{
						capx_aer_status_t status;
						capx_aer_mask_t mask;
					} correctable;
					struct
					{
						capx_aer_status_t status;
						capx_aer_mask_t mask;
						capx_aer_sev_t severity;
						uint_t first_uc_error_bit;
						struct
						{
							/*
							 * 'valid' is true if header logging is supported
							 * and the 'hdr' log is valid
							 */
							bool_t hdr_valid;
							capx_aer_log_t hdr;
							/*
							 * 'valid' is true if a TLP Prefix log recording is
							 * supported and the 'tlp' log is valid
							 */
							bool_t tlp_valid;
							capx_aer_log_t tlp;
						} logs;
					} uncorrectable;
				} u;
			} aer;
		} pcie;
	} device;
	struct reporting_agent_regs_s
	{
		pci_stat_t sstat_reg;	/* bridge secondary status for bridge RA */
		struct
		{
			bool_t valid;	/* PCIe might not be supported */
			struct
			{
				/*
				 * 'valid' is true if
				 *    - AER is supported and root_status, first_correctable and
				 *     first_uncorrectable all contain valid values
				 */
				bool_t valid;
				capx_aer_status_t root_status;
				struct
				{
					capx_aer_requester_id_t first_correctable;
					capx_aer_requester_id_t first_uncorrectable;
				} rid;
			} aer;
		} pcie;
	} reporting_agent;
} pci_error_regs_t;

/*
 ===============================================================================
 pci_err_record_t

 This structure contains all of the information gathered from the respective
 device(s) at the time of occurrence of the registered error event.
 This information is optional and clients interested in this information must
 indicate this preference in the 'pci_event_attr_t' when the event is created.
 See the description of 'pci_event_type_e' for error events in pci/pci_event.h

 IMPORTANT:
 When the registered handler is done with the 'pci_err_record_t', it must free
 it

*/
typedef struct pci_err_record_s
{
	struct
	{
		uint_t size;	/* total size of the 'pci_err_record_t' structure */
		pci_version_t version;	/* 'pci_err_record_t' version */
	} hdr;

	pci_err_record_id_t id;
	struct timespec timestamp;

	struct device_info_s
	{
		pci_bdf_t bdf;
		pci_device_type_e type;
		/* valid only if device_type is pci_device_type_e_PCIe, otherwise -1 */
		cap_pcie_portType_e pcie_type;
	} device;

	struct device_info_s agent;

	pci_error_regs_t regs;

} pci_err_record_t;



#endif	/* _PCI_ERROR_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/pci/mainline/lib/public/pci/pci_error.h $ $Rev: 973254 $")
#endif
