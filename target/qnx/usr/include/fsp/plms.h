/*
 * Copyright (c) 2023-2025, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef PLMS_EXTERNAL_H
#define PLMS_EXTERNAL_H

#include <fsp/fsp_types.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <sys/iomsg.h>
#include <sys/mman.h>
#include <sys/siginfo.h>
#include <unistd.h>

__BEGIN_DECLS
#define FSP_PLMS_RMGR_ID ((uint32_t)_IOMGR_PRIVATE_BASE + 23U)

#define FSP_PLMS_STATUS_FAIL -1
#define FSP_PLMS_STATUS_EOK 0

typedef enum {
  FSP_PLMS_COMPONENT_IDLE,
  FSP_PLMS_COMPONENT_STOPPING,
  FSP_PLMS_COMPONENT_STARTING,
  FSP_PLMS_COMPONENT_STARTED,
  FSP_PLMS_COMPONENT_SESSION_STOPPED,
  FSP_PLMS_COMPONENT_FAULT,
} fsp_plms_ComponentStateType;

typedef enum {
  FSP_PLMS_CTRL_ACTION_NONE,
  FSP_PLMS_CTRL_ACTION_START,
  FSP_PLMS_CTRL_ACTION_STOP,
  FSP_PLMS_CTRL_ACTION_RESTART,
  FSP_PLMS_CTRL_ACTION_SHUTDOWN,
  FSP_PLMS_CTRL_ACTION_SHUTDOWN_FAST,
} fsp_plms_ActionType;

typedef struct plms_handle_s fsp_plms_HandleType;

fsp_plms_HandleType *fsp_plms_Connect(const char *plms_name, uint64_t flags);
fsp_ResultType fsp_plms_Disconnect(fsp_plms_HandleType *plms_hdl, uint64_t flags);

#define FSP_PLMS_NOTIFY_STARTED 0x00000001U
#define FSP_PLMS_NOTIFY_STOPPED 0x00000002U
#define FSP_PLMS_NOTIFY_FAULT 0x00000004U
#define FSP_PLMS_NOTIFY_FAIL_HB 0x00000008U
#define FSP_PLMS_NOTIFY_FAIL 0x00000010U
#define FSP_PLMS_NOTIFY_ALL                                                                              \
  (FSP_PLMS_NOTIFY_STARTED | FSP_PLMS_NOTIFY_STOPPED | FSP_PLMS_NOTIFY_FAULT | FSP_PLMS_NOTIFY_FAIL_HB | \
   FSP_PLMS_NOTIFY_FAIL)
#define FSP_PLMS_UNREGISTER_ALL (FSP_PLMS_NOTIFY_ALL + 1U)

#define FSP_PLMS_NOTIF_SHIFT (8 * 4)
#define FSP_PLMS_GET_COMPONENT_HASH(x) ((uint32_t)(0xFFFFFFFFU & (uint64_t)(x).value.sival_ptr))
#define FSP_PLMS_GET_COMPONENT_NOTIFICATION(x) ((uint32_t)((uint64_t)(x).value.sival_ptr >> FSP_PLMS_NOTIF_SHIFT))

#define FSP_PLMS_HB_NONE 0x000000000U
#define FSP_PLMS_SETUP_PROCESS_HB 0x000000001U /*setup watchdog heartbeat from process to PLMS*/
#define FSP_PLMS_SETUP_PLMS_HB 0x000000002U    /*setup watchdog heartbeat from PLMS to process*/

fsp_ResultType fsp_plms_Action(const fsp_plms_HandleType *const plms_hdl, fsp_plms_ActionType action_type,
                               const char *node_name);
fsp_ResultType fsp_plms_GetComponentStatus(const fsp_plms_HandleType *const plms_hdl, const char *component_name,
                                           fsp_plms_ComponentStateType *status);
fsp_ResultType fsp_plms_IsComponentDegraded(const fsp_plms_HandleType *const plms_hdl, const char *component_name,
                                            bool *degraded);

fsp_ResultType fsp_plms_WatchdogHeartbeat(const fsp_plms_HandleType *const plms_hdl);
fsp_ResultType fsp_plms_WatchdogControl(const fsp_plms_HandleType *const plms_hdl, bool enable);
fsp_ResultType fsp_plms_GetLauncherHeartbeat(const fsp_plms_HandleType *const plms_hdl, uint64_t *heartbeat_value);

fsp_ResultType fsp_plms_GetDependencyTree(const fsp_plms_HandleType *const plms_hdl, const char *file_name);
fsp_ResultType fsp_plms_MsgRegisterEvent(const fsp_plms_HandleType *const plms_hdl, struct sigevent *se);
fsp_ResultType fsp_plms_RegisterNotificationEvent(const fsp_plms_HandleType *const plms_hdl, const struct sigevent *se,
                                                  uint64_t flags);
fsp_ResultType fsp_plms_UnregisterNotificationEvent(const fsp_plms_HandleType *const plms_hdl, uint64_t flags);
fsp_ResultType fsp_plms_SetVerbosity(const fsp_plms_HandleType *const plms_hdl, uint8_t verbosity);

fsp_ResultType fsp_plms_LoadConfig(const fsp_plms_HandleType *const plms_hdl, char *file_name);

__END_DECLS

#endif /* PLMS_EXTERNAL_H */
