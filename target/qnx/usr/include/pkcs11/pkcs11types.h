/*
 * Copyright (c) 2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/**
 * @file pkcs11types.h
 *
 * @brief PKCS#11 API Types
 *
 * These types were derived from the spec: https://docs.oasis-open.org/pkcs11/pkcs11-base/v3.0/csprd01/pkcs11-base-v3.0-csprd01.html
 * Algorithms (Mechanisms) are defined in https://docs.oasis-open.org/pkcs11/pkcs11-curr/v3.0/pkcs11-curr-v3.0.html
 */

#ifndef QNX_PKCS11_PKCS11TYPES_H_INCLUDED
#define QNX_PKCS11_PKCS11TYPES_H_INCLUDED

#ifndef QNX_PKCS11_PKCS11_H_INCLUDED
#error "This header can only be loaded from pkcs11.h"
#endif

#include <stdbool.h>

typedef unsigned char CK_BYTE; /*!< unsigned 8-bit value */
typedef CK_BYTE CK_CHAR; /*!< unsigned 8-bit char */
typedef CK_BYTE CK_UTF8CHAR; /*!< 8-bit UTF-8 char */
typedef unsigned long int CK_ULONG; /*!< 32+ bit unsigned integer */
typedef long int CK_LONG; /*!< 32+ bit signed integer */
typedef CK_ULONG CK_FLAGS; /*!< 32 bit flags type, each bit is a bool flag */
typedef CK_BYTE CK_BBOOL; /*!< boolean */

#define CK_TRUE  true /*!< Boolean true */
#define CK_FALSE false /*!< Boolean false */

#ifndef CK_DISABLE_TRUE_FALSE
#ifndef TRUE
#define TRUE  CK_TRUE /*!< Backwards compatible true */
#endif /* TRUE */
#ifndef FALSE
#define FALSE CK_FALSE /*!< Backwards compatible false */
#endif /* FALSE */
#endif /* CK_DISABLE_TRUE_FALSE */

#ifndef NULL_PTR
#define NULL_PTR NULL /*!< NULL pointer constant */
#endif /* NULL_PTR */

typedef CK_BYTE* CK_BYTE_PTR; /*!< pointer to CK_BYTE */
typedef CK_CHAR* CK_CHAR_PTR; /*!< pointer to CK_CHAR */
typedef CK_UTF8CHAR* CK_UTF8CHAR_PTR; /*!< pointer to CK_UTF8CHAR */
typedef CK_ULONG* CK_ULONG_PTR; /*!< pointer to CK_ULONG */
typedef void* CK_VOID_PTR; /*!< pointer to void */
typedef CK_VOID_PTR* CK_VOID_PTR_PTR; /*!< CK_VOID_PTR pointer */

typedef CK_ULONG CK_RV; /*!< function return value */

/**
 * @defgroup PKCS11_API_Return_Codes PKCS#11 function return codes
 * @{
 */
#define CKR_OK                                0x00000000UL /*!< Everything ok */

#define CKR_GENERAL_ERROR                     0x00000001UL /*!< General error, usually fatal */
#define CKR_HOST_MEMORY                       0x00000002UL /*!< Library is out of memory to perform operation */
#define CKR_FUNCTION_FAILED                   0x00000003UL /*!< Non fatal error, check CK_SESSION_INFO ulDeviceError field if failure is associated with a session */

#define CKR_SESSION_HANDLE_INVALID            0x00000021UL /*!< Invalid session handle */
#define CKR_SESSION_CLOSED                    0x00000022UL /*!< Session was closed during execution of functions on the session */
#define CKR_SESSION_COUNT                     0x00000023UL /*!< Token can't open session. See C_OpenSession */
#define CKR_SESSION_EXISTS                    0x00000024UL /*!< Session is currently opened with token. See C_InitToken */
#define CKR_SESSION_PARALLEL_NOT_SUPPORTED    0x00000025UL /*!< Legacy error code - unused */
#define CKR_SESSION_READ_ONLY                 0x00000026UL /*!< Session is read-only so operation can't be performed */
#define CKR_SESSION_READ_ONLY_EXISTS          0x00000027UL /*!< Read-only session exists, SO can't login */
#define CKR_SESSION_READ_WRITE_SO_EXISTS      0x00000028UL /*!< Read-write SO session is opened, read-only session can't be opened */

#define CKR_STATE_UNSAVEABLE                  0x00000040UL /*!< Session state can't be saved */
#define CKR_SAVED_STATE_INVALID               0x00000041UL /*!< Stae given in restoration is invalid. See C_SetOperationState */

#define CKR_OBJECT_HANDLE_INVALID             0x00000060UL /*!< Invalid object handle */
#define CKR_TEMPLATE_INCOMPLETE               0x00000061UL /*!< Incomplete object template */
#define CKR_TEMPLATE_INCONSISTENT             0x00000062UL /*!< Inconsistent object template */

#define CKR_DEVICE_MEMORY                     0x00000080UL /*!< Token is out of memory to perform operation */
#define CKR_DEVICE_ERROR                      0x00000081UL /*!< Token/slot general error */
#define CKR_TOKEN_NOT_PRESENT                 0x00000082UL /*!< Token not in slot when function called */
#define CKR_DEVICE_REMOVED                    0x00000083UL /*!< Token was removed from slot during operation */
#define CKR_TOKEN_NOT_RECOGNIZED              0x00000084UL /*!< Unrecognized token in slot */
#define CKR_TOKEN_WRITE_PROTECTED             0x00000085UL /*!< Token is write-protected */

#define CKR_SLOT_ID_INVALID                   0x00000100UL /*!< Invalid slot ID */

#define CKR_CANCEL                            0x00000120UL /*!< Used to signify to library to cancel operation, see CKN_SURRENDER */

#define CKR_MUTEX_BAD                         0x00000140UL /*!< Bad mutex object was given in a mutex call */
#define CKR_MUTEX_NOT_LOCKED                  0x00000141UL /*!< Mutex was not locked when passed to a mutex locking function */

#define CKR_CANT_LOCK                         0x00000160UL /*!< Library can't support requested locking mode. See C_Initialize */
#define CKR_NEED_TO_CREATE_THREADS            0x00000161UL /*!< Library is told that it can't create threads but it needs to be able to work. See C_Initialize */
#define CKR_FIPS_SELF_TEST_FAILED             0x00000162UL /*!< FIPS 140-2 self test failed, token entered an error state */

#define CKR_ACTION_PROHIBITED                 0x00000180UL /*!< Object action is forbidden see C_CopyObject, C_SetAttributeValue and C_DestroyObject */
#define CKR_ARGUMENTS_BAD                     0x00000181UL /*!< Bad arguments to API functions */

#define CKR_ATTRIBUTE_READ_ONLY               0x00000200UL /*!< Read-only attribute */
#define CKR_ATTRIBUTE_SENSITIVE               0x00000201UL /*!< Sensitive / un-extractable attribute */
#define CKR_ATTRIBUTE_TYPE_INVALID            0x00000202UL /*!< Invalid attribute type */
#define CKR_ATTRIBUTE_VALUE_INVALID           0x00000203UL /*!< Invalid attribute value */

#define CKR_BUFFER_TOO_SMALL                  0x00000220UL /*!< Buffer too small */

#define CKR_CRYPTOKI_ALREADY_INITIALIZED      0x00000240UL /*!< Library already initialized. See C_Initialize */
#define CKR_CRYPTOKI_NOT_INITIALIZED          0x00000241UL /*!< Library is not initialized */
#define CKR_LIBRARY_LOAD_FAILED               0x00000242UL /*!< Library can't load dependent library (dlopen) */

#define CKR_CURVE_NOT_SUPPORTED               0x00000260UL /*!< EC Curve not supported by token */

#define CKR_DATA_INVALID                      0x00000280UL /*!< Plaintext to crypto operation is invalid */
#define CKR_DATA_LEN_RANGE                    0x00000281UL /*!< Plaintext length to crypto operation is invalid */

#define CKR_DOMAIN_PARAMS_INVALID             0x00000300UL /*!< Invalid or unsupported algorithm domain parameters by token */

#define CKR_ENCRYPTED_DATA_INVALID            0x00000320UL /*!< Ciphertext to crypto operation is invalid */
#define CKR_ENCRYPTED_DATA_LEN_RANGE          0x00000321UL /*!< Ciphertext length to crypto operation is invalid */

#define CKR_EXCEEDED_MAX_ITERATIONS           0x00000340UL /*!< Crypto algorithm looping exceeded maximum iterations (key generation, etc.) */

#define CKR_FUNCTION_CANCELED                 0x00000360UL /*!< Function was canceled in mid-execution */
#define CKR_FUNCTION_NOT_PARALLEL             0x00000361UL /*!< Legacy only. See C_GetFunctionStatus and C_CancelFunction */
#define CKR_FUNCTION_NOT_SUPPORTED            0x00000362UL /*!< Function not supported by this library */
#define CKR_FUNCTION_REJECTED                 0x00000364UL /*!< Function request was rejected by the user */

#define CKR_INFORMATION_SENSITIVE             0x00000380UL /*!< Token will not reveal sensitive information */

#define CKR_KEY_CHANGED                       0x00000400UL /*!< Key was changed from original saved session. See C_SetOperationState */
#define CKR_KEY_FUNCTION_NOT_PERMITTED        0x00000401UL /*!< Key attributes do not permit requested operation */
#define CKR_KEY_HANDLE_INVALID                0x00000402UL /*!< Invalid key handle */
#define CKR_KEY_INDIGESTIBLE                  0x00000403UL /*!< Invalid or unsupported key type for token. See C_DigestKey */
#define CKR_KEY_NEEDED                        0x00000404UL /*!< Restored session is missing keys associated previously. See C_SetOperationState */
#define CKR_KEY_NOT_NEEDED                    0x00000405UL /*!< An extraneous key was supplied in session restoration. See C_SetOperationState */
#define CKR_KEY_NOT_WRAPPABLE                 0x00000406UL /*!< Extractable key can't be provided in the requested format */
#define CKR_KEY_SIZE_RANGE                    0x00000407UL /*!< Supported key type size is outside the range handled by token */
#define CKR_KEY_TYPE_INCONSISTENT             0x00000408UL /*!< Key type is invalid with algorithm */
#define CKR_KEY_UNEXTRACTABLE                 0x00000409UL /*!< Key is not extractable (secret key) */
#define CKR_PUBLIC_KEY_INVALID                0x00000410UL /*!< Invalid public key */

#define CKR_MECHANISM_INVALID                 0x00000420UL /*!< Invalid mechanism specified to crypto operation or token doesn't support it */
#define CKR_MECHANISM_PARAM_INVALID           0x00000421UL /*!< Invalid mechanism parameters */

#define CKR_NO_EVENT                          0x00000440UL /*!< Returned from C_GetSlotEvent in non blocking mode and no events are pending */

#define CKR_OPERATION_ACTIVE                  0x00000460UL /*!< An operation is in progress preventing the requested operation to proceed */
#define CKR_OPERATION_NOT_INITIALIZED         0x00000461UL /*!< No active operation of the proper type in the specified session */
#define CKR_OPERATION_CANCEL_FAILED           0x00000462UL /*!< A request to caqncel an operation could not be performed. See C_SessionCancel */

#define CKR_PIN_EXPIRED                       0x00000480UL /*!< Specified PIN has expired. PIN expiry varies by token */
#define CKR_PIN_INCORRECT                     0x00000481UL /*!< Incorrect login attempt */
#define CKR_PIN_INVALID                       0x00000482UL /*!< Invalid PIN (trying to set it) */
#define CKR_PIN_LEN_RANGE                     0x00000483UL /*!< Invalid PIN size (short or long) */
#define CKR_PIN_LOCKED                        0x00000484UL /*!< PIN is locked */
#define CKR_PIN_TOO_WEAK                      0x00000485UL /*!< PIN is too weak and easy to guess */

#define CKR_USER_ALREADY_LOGGED_IN            0x00000500UL /*!< User is already logged in. See C_Login */
#define CKR_USER_ANOTHER_ALREADY_LOGGED_IN    0x00000501UL /*!< Another user is already logged in. See C_Login */
#define CKR_USER_NOT_LOGGED_IN                0x00000502UL /*!< User is not logged in */
#define CKR_USER_PIN_NOT_INITIALIZED          0x00000503UL /*!< User PIN has not been initialized. See C_InitPIN */
#define CKR_USER_TOO_MANY_TYPES               0x00000504UL /*!< Exceeded token/library maximum logged in user count */
#define CKR_USER_TYPE_INVALID                 0x00000505UL /*!< Invalid user type was specified. See CK_USER_TYPE */

#define CKR_RANDOM_NO_RNG                     0x00000520UL /*!< Token doesn't support RNG. See C_SeedRandom and C_GenerateRandom */
#define CKR_RANDOM_SEED_NOT_SUPPORTED         0x00000521UL /*!< Token doesn't support RNG seeding. See C_SeedRandom */

#define CKR_SIGNATURE_LEN_RANGE               0x00000540UL /*!< Signature length is invalid */
#define CKR_SIGNATURE_INVALID                 0x00000541UL /*!< Signature is invalid */

#define CKR_UNWRAPPING_KEY_HANDLE_INVALID     0x00000560UL /*!< Unwrap key handle is invalid. See C_UnwrapKey */
#define CKR_UNWRAPPING_KEY_SIZE_RANGE         0x00000561UL /*!< Unwrapped key size is outside range of supported key sizes by token/library. See C_UnwrapKey */
#define CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT  0x00000562UL /*!< Unwrap mechanism type used with unwrap key is inconsistent. See C_UnwrapKey */

#define CKR_WRAPPED_KEY_INVALID               0x00000580UL /*!< Wrapped key is invalid. See C_UnwrapKey */
#define CKR_WRAPPED_KEY_LEN_RANGE             0x00000581UL /*!< Wrapped key is length is invalid. See C_UnwrapKey */

#define CKR_WRAPPING_KEY_HANDLE_INVALID       0x00000600UL /*!< Wrapped key handle  is invalid. See C_WrapKey */
#define CKR_WRAPPING_KEY_SIZE_RANGE           0x00000601UL /*!< Wrapped key size is outside range of supported key sizes by token/library. See C_WrapKey */
#define CKR_WRAPPING_KEY_TYPE_INCONSISTENT    0x00000602UL /*!< Wrap mechanism type used with wrap key is inconsistent. See C_WrapKey */

#define CKR_VENDOR_DEFINED                    0x80000000UL /*!< Anything >= to this is for vendor specific error codes */
/** @} */

/**
 * @brief API Version Object
 */
typedef struct CK_VERSION_ {
	CK_BYTE major; /*!< Major API version */
	CK_BYTE minor; /*!< Minor API version */
} CK_VERSION;

typedef CK_VERSION* CK_VERSION_PTR; /*!< pointer to CK_VERSION */


/**
 * @brief General library/module and version information
 */
typedef struct CK_INFO_ {
	CK_VERSION cryptokiVersion; /*!< Supported API version */
	CK_UTF8CHAR manufacturerID[32]; /*!< Non-NUL terminated, space filled manufacturer ID */
	CK_FLAGS flags; /*!< unused */
	CK_UTF8CHAR libraryDescription[32]; /*!< Non-NUL terminated, space filled library description */
	CK_VERSION libraryVersion; /*!< Library version */
} CK_INFO;

typedef CK_INFO* CK_INFO_PTR; /*!< pointer to CK_INFO */


/**
 * @defgroup PKCS11_Notification PKCS#11 Notification type values
 * @{
 */
#define CKN_SURRENDER 0x00000000UL /*!< Client signaling to pause operation, later signaling whether to resume or cancel */
/** @} */


typedef CK_ULONG CK_SLOT_ID; /*!< Slot ID */
typedef CK_SLOT_ID* CK_SLOT_ID_PTR; /*!< pointer to CK_SLOT_ID */


/**
 * @defgroup PKCS11_Slot_Flags PKCS#11 Slot capability flags
 * @{
 */
#define CKF_TOKEN_PRESENT    0x00000001UL /*!< Token is present in slot */
#define CKF_REMOVABLE_DEVICE 0x00000002UL /*!< Slot supports removable tokens */
#define CKF_HW_SLOT          0x00000004UL /*!< Slot is a hardware slot opposed to a software slot for a software based token */
/** @} */

/**
 * @brief Slot information
 *
 * Slots represent physical cards slots in hardware which can hold a token or be empty.
 *
 * @note The value of the CKF_REMOVABLE_DEVICE flag never changes for any slot.
 * If this flag is not set for a given slot, then the CKF_TOKEN_PRESENT
 * flag for that slot is always set.
 */
typedef struct CK_SLOT_INFO_ {
	CK_UTF8CHAR slotDescription[64]; /*!< Non-NUL terminated, space filled slot description */
	CK_UTF8CHAR manufacturerID[32]; /*!< Non-NUL terminated, space filled manufacturer ID */
	CK_FLAGS flags; /*!< slot capability flags */
	CK_VERSION hardwareVersion; /*!< slot hardware version */
	CK_VERSION firmwareVersion; /*!< slot firmware version */
} CK_SLOT_INFO;

typedef CK_SLOT_INFO* CK_SLOT_INFO_PTR; /*!< pointer to CK_SLOT_INFO */


/**
 * @defgroup PKCS11_Token_Special PKCS#11 token field special values (counts)
 * @{
 */
#define CK_UNAVAILABLE_INFORMATION  (~0UL) /*!< Information is unavailable from slot */
#define CK_EFFECTIVELY_INFINITE     ((~0UL)-1UL) /*!< Infinite supported values within physical limits */
/** @} */

/**
 * @defgroup PKCS11_Token_Flags PKCS#11 Token capability flags
 * @{
 */
#define CKF_RNG                            0x00000001UL /*!< Token supports an RNG */
#define CKF_WRITE_PROTECTED                0x00000002UL /*!< Set if token is write-protected */
#define CKF_LOGIN_REQUIRED                 0x00000004UL /*!< Set if some crypto operations require a logged in user */
#define CKF_USER_PIN_INITIALIZED           0x00000008UL /*!< Set if the user's PIN has been initialized */
#define CKF_RESTORE_KEY_NOT_NEEDED         0x00000020UL /*!< Set if a saved session's crypto operations state already contains the keys for restoring the session state */
#define CKF_CLOCK_ON_TOKEN                 0x00000040UL /*!< Set if token has a hadware clock @see utcTime */
#define CKF_PROTECTED_AUTHENTICATION_PATH  0x00000100UL /*!< Set if token supports alternate login path outside of PIN mechanism */
#define CKF_DUAL_CRYPTO_OPERATIONS         0x00000200UL /*!< If token supports dual crypto operations @see C_DigestEncryptUpdate, C_DecryptDigestUpdate, C_SignEncryptUpdate and C_DecryptVerifyUpdate */
#define CKF_TOKEN_INITIALIZED              0x00000400UL /*!< Set if token was properly initialized with C_InitToken or external mechanism. If already set, token will re-initialize */
#define CKF_SECONDARY_AUTHENTICATION       0x00000800UL /*!< @c Deprecated */
#define CKF_USER_PIN_COUNT_LOW             0x00010000UL /*!< Set if user failed to enter valid PIN at least once since last successful login */
#define CKF_USER_PIN_FINAL_TRY             0x00020000UL /*!< Set if a further incorrect login will cause user to be locked out */
#define CKF_USER_PIN_LOCKED                0x00040000UL /*!< Set if current user PIN is locked out */
#define CKF_USER_PIN_TO_BE_CHANGED         0x00080000UL /*!< Set if default manufacturing PIN still set for use or PIN has expired */
#define CKF_SO_PIN_COUNT_LOW               0x00100000UL /*!< Set if SO failed to enter valid PIN at least once since last successful login */
#define CKF_SO_PIN_FINAL_TRY               0x00200000UL /*!< Set if a further incorrect login will cause SO to be locked out */
#define CKF_SO_PIN_LOCKED                  0x00400000UL /*!< Set if SO PIN is locked out */
#define CKF_SO_PIN_TO_BE_CHANGED           0x00800000UL /*!< Set if default manufacturing PIN still set for SO or PIN has expired */
#define CKF_ERROR_STATE                    0x01000000UL /*!< Set if token failed a FIPS 140-2 self-test and is in an error state */
/** @} */

/**
 * @brief Token information
 */
typedef struct CK_TOKEN_INFO_ {
	CK_UTF8CHAR label[32]; /*!< Non-NUL terminated, space filled label identifying the token */
	CK_UTF8CHAR manufacturerID[32]; /*!< Non-NUL terminated, space filled manufacturer ID */
	CK_UTF8CHAR model[16]; /*!< Non-NUL terminated, space filled model name */
	CK_CHAR serialNumber[16]; /*!< Non-NUL terminated, space filled serial number */
	CK_FLAGS flags; /*!< Token capability flags */
	CK_ULONG ulMaxSessionCount; /*!< Maximum number of sessions an application can have open with the token, @see PKCS11_Token_Special */
	CK_ULONG ulSessionCount; /*!< Current number of sessions an application has open with the token, @see PKCS11_Token_Special */
	CK_ULONG ulMaxRwSessionCount; /*!< Maximum number of R/W sessions an application can have open with the token, @see PKCS11_Token_Special */
	CK_ULONG ulRwSessionCount; /*!< Current number of R/W sessions an application has open with the token, @see PKCS11_Token_Special */
	CK_ULONG ulMaxPinLen; /*!< Maximum PIN length (bytes) */
	CK_ULONG ulMinPinLen; /*!< Minimum PIN length (bytes) */
	CK_ULONG ulTotalPublicMemory; /*!< Total token internal memory to store public objects */
	CK_ULONG ulFreePublicMemory; /*!< Total token internal free memory to store public objects */
	CK_ULONG ulTotalPrivateMemory; /*!< Total token internal memory to store private objects */
	CK_ULONG ulFreePrivateMemory; /*!< Total token internal free memory to store private objects */
	CK_VERSION hardwareVersion; /*!< Hardware version */
	CK_VERSION firmwareVersion; /*!< Firmware version */
	CK_CHAR utcTime[16]; /*!< Token internal time in YYYYMMDDhhmmss00 format if it supports a clock */
} CK_TOKEN_INFO;

typedef CK_TOKEN_INFO* CK_TOKEN_INFO_PTR; /*!< pointer to CK_TOKEN_INFO */


typedef CK_ULONG CK_SESSION_HANDLE; /*!< Session handle */
typedef CK_SESSION_HANDLE* CK_SESSION_HANDLE_PTR; /*!< pointer to CK_SESSION_HANDLE */

#define CK_INVALID_HANDLE (0UL) /*!< Invalid handle (mandated by spec that 0 is always invalid) */


typedef CK_ULONG CK_NOTIFICATION; /*!< Notification types */

/** Notify callback function */
typedef CK_RV (*CK_NOTIFY)(CK_SESSION_HANDLE hSession, CK_NOTIFICATION event, CK_VOID_PTR pApplication);


typedef CK_ULONG CK_USER_TYPE; /*!< User identification types */

/**
 * @defgroup PKCS11_User_Types PKCS#11 User types
 * @{
 */
#define CKU_SO                 0UL /*!< Security Officer */
#define CKU_USER               1UL /*!< Normal user */
#define CKU_CONTEXT_SPECIFIC   2UL /*!< Context specific user */
/** @} */

/**
 * @defgroup PKCS11_Session_States PKCS#11 Session state
 * @{
 */
#define CKS_RO_PUBLIC_SESSION  0UL /*!< Anonymous read-only access */
#define CKS_RO_USER_FUNCTIONS  1UL /*!< Logged user read-only access */
#define CKS_RW_PUBLIC_SESSION  2UL /*!< Anonymous read-write access */
#define CKS_RW_USER_FUNCTIONS  3UL /*!< Logged user read-write access */
#define CKS_RW_SO_FUNCTIONS    4UL /*!< Security officer full access */
/** @} */

typedef CK_ULONG CK_STATE; /*!< Session state */

/**
 * @defgroup PKCS11_Session_Flags PKCS#11 Session flags
 * @{
 */
#define CKF_RW_SESSION      0x00000002UL /*!< Session is read-write if set, read-only otherwise */
#define CKF_SERIAL_SESSION  0x00000004UL /*!< This flag is for backwards compat and should always be set */
/** @} */

/**
 * @brief Session information
 */
typedef struct CK_SESSION_INFO_ {
	CK_SLOT_ID slotID; /*!< Slot unique identifier which is linked to the token */
	CK_STATE state; /*!< Session state */
	CK_FLAGS flags; /*!< Session flags CKF_* */
	CK_ULONG ulDeviceError; /*!< Device specific error code which is not covered by this API */
} CK_SESSION_INFO;

typedef CK_SESSION_INFO* CK_SESSION_INFO_PTR; /*!< pointer to CK_SESSION_INFO */


typedef CK_RV (*CK_CREATEMUTEX)(CK_VOID_PTR_PTR ppMutex); /*!< Create mutex functon pointer */
typedef CK_RV (*CK_DESTROYMUTEX)(CK_VOID_PTR pMutex); /*!< Destroy mutex functon pointer */
typedef CK_RV (*CK_LOCKMUTEX)(CK_VOID_PTR pMutex); /*!< Lock mutex functon pointer */
typedef CK_RV (*CK_UNLOCKMUTEX)(CK_VOID_PTR pMutex); /*!< Unlock mutex functon pointer */


/**
 * @defgroup PKCS11_Init_Flags PKCS#11 Library initialization flags
 * @{
 */
#define CKF_LIBRARY_CANT_CREATE_OS_THREADS  0x00000001UL /*!< Set to tell library it can't create threads */
#define CKF_OS_LOCKING_OK                   0x00000002UL /*!< Set if library can use native OS calls for locking */
/** @} */

/**
 * @brief C_Initialize function parameters
 */
typedef struct CK_C_INITIALIZE_ARGS_ {
	CK_CREATEMUTEX CreateMutex; /*!< create mutex callback */
	CK_DESTROYMUTEX DestroyMutex; /*!< destroy mutex callback */
	CK_LOCKMUTEX LockMutex; /*!< lock mutex callback */
	CK_UNLOCKMUTEX UnlockMutex; /*!< unlock mutex callback */
	CK_FLAGS flags; /*!< Initialization flags */
	CK_VOID_PTR pReserved; /*!< unused */
} CK_C_INITIALIZE_ARGS;
typedef CK_C_INITIALIZE_ARGS* CK_C_INITIALIZE_ARGS_PTR; /*!< pointer to CK_C_INITIALIZE_ARGS */


/**
 * @defgroup PKCS11_Wait_Flags PKCS#11 C_WaitForSlotEvent Flags
 * @{
 */
#define CKF_DONT_BLOCK  0x00000001UL
/** @} */

/**
 * @defgroup PKCS11_Message_Crypto_Flags PKCS#11 Message-based Crypto API Flags
 * @{
 */
#define CKF_END_OF_MESSAGE  0x00000001UL
/** @} */


typedef CK_ULONG CK_OBJECT_HANDLE; /*!< Object handle */
typedef CK_OBJECT_HANDLE* CK_OBJECT_HANDLE_PTR; /*!< pointer to CK_OBJECT_HANDLE */


typedef CK_ULONG CK_OBJECT_CLASS; /*!< Object class (types). See CKA_CLASS attribute */
typedef CK_OBJECT_CLASS* CK_OBJECT_CLASS_PTR; /*!< pointer to CK_OBJECT_CLASS */

/**
 * @defgroup PKCS11_Object_Classes PKCS#11 object classes
 * @{
 */
#define CKO_DATA              0x00000000UL /*!< Private data object */
#define CKO_CERTIFICATE       0x00000001UL /*!< Certificate object */
#define CKO_PUBLIC_KEY        0x00000002UL /*!< Public key object */
#define CKO_PRIVATE_KEY       0x00000003UL /*!< Private key object */
#define CKO_SECRET_KEY        0x00000004UL /*!< Secret key object */
#define CKO_HW_FEATURE        0x00000005UL /*!< Hardware feature object */
#define CKO_DOMAIN_PARAMETERS 0x00000006UL /*!< Domain parameter object (EC) */
#define CKO_PROFILE           0x00000009UL /*!< Profile object */
#define CKO_VENDOR_DEFINED    0x80000000UL /*!< Anything >= to this is for vendor specific objects */
/** @} */


typedef CK_ULONG CK_HW_FEATURE_TYPE; /*!< Hardware features */

/**
 * @defgroup PKCS11_Hardware_Types PKCS#11 hardware types
 * @{
 */
#define CKH_MONOTONIC_COUNTER 0x00000001UL /*!< Monotonic counter - see CKA_HW_FEATURE_TYPE */
#define CKH_CLOCK             0x00000002UL /*!< Clock - see CKA_HW_FEATURE_TYPE */
#define CKH_VENDOR_DEFINED    0x80000000UL /*!< Anything >= to this is for vendor specific classes */
/** @} */


typedef CK_ULONG CK_KEY_TYPE; /*!< Key types */

/**
 * @defgroup PKCS11_Key_Type PKCS#11 object classes
 * @{
 */
#define CKK_RSA                 0x00000000UL
#define CKK_DSA                 0x00000001UL
#define CKK_DH                  0x00000002UL
#define CKK_ECDSA               0x00000003UL /* Deprecated */
#define CKK_EC                  0x00000003UL
#define CKK_X9_42_DH            0x00000004UL
#define CKK_KEA                 0x00000005UL
#define CKK_GENERIC_SECRET      0x00000010UL
#define CKK_RC2                 0x00000011UL
#define CKK_RC4                 0x00000012UL
#define CKK_DES                 0x00000013UL
#define CKK_DES2                0x00000014UL
#define CKK_DES3                0x00000015UL
#define CKK_CAST                0x00000016UL
#define CKK_CAST3               0x00000017UL
#define CKK_CAST5               0x00000018UL /* Deprecated */
#define CKK_CAST128             0x00000018UL
#define CKK_RC5                 0x00000019UL
#define CKK_IDEA                0x0000001AUL
#define CKK_SKIPJACK            0x0000001BUL
#define CKK_BATON               0x0000001CUL
#define CKK_JUNIPER             0x0000001DUL
#define CKK_CDMF                0x0000001EUL
#define CKK_AES                 0x0000001FUL
#define CKK_BLOWFISH            0x00000020UL
#define CKK_TWOFISH             0x00000021UL
#define CKK_SECURID             0x00000022UL
#define CKK_HOTP                0x00000023UL
#define CKK_ACTI                0x00000024UL
#define CKK_CAMELLIA            0x00000025UL
#define CKK_ARIA                0x00000026UL
#define CKK_MD5_HMAC            0x00000027UL
#define CKK_SHA_1_HMAC          0x00000028UL
#define CKK_RIPEMD128_HMAC      0x00000029UL
#define CKK_RIPEMD160_HMAC      0x0000002AUL
#define CKK_SHA256_HMAC         0x0000002BUL
#define CKK_SHA384_HMAC         0x0000002CUL
#define CKK_SHA512_HMAC         0x0000002DUL
#define CKK_SHA224_HMAC         0x0000002EUL
#define CKK_SEED                0x0000002FUL
#define CKK_GOSTR3410           0x00000030UL
#define CKK_GOSTR3411           0x00000031UL
#define CKK_GOST28147           0x00000032UL
#define CKK_CHACHA20            0x00000033UL
#define CKK_POLY1305            0x00000034UL
#define CKK_AES_XTS             0x00000035UL
#define CKK_SHA3_224_HMAC       0x00000036UL
#define CKK_SHA3_256_HMAC       0x00000037UL
#define CKK_SHA3_384_HMAC       0x00000038UL
#define CKK_SHA3_512_HMAC       0x00000039UL
#define CKK_BLAKE2B_160_HMAC    0x0000003aUL
#define CKK_BLAKE2B_256_HMAC    0x0000003bUL
#define CKK_BLAKE2B_384_HMAC    0x0000003cUL
#define CKK_BLAKE2B_512_HMAC    0x0000003dUL
#define CKK_SALSA20             0x0000003eUL
#define CKK_X2RATCHET           0x0000003fUL
#define CKK_EC_EDWARDS          0x00000040UL
#define CKK_EC_MONTGOMERY       0x00000041UL
#define CKK_HKDF                0x00000042UL

#define CKK_VENDOR_DEFINED      0x80000000UL /*!< Anything >= to this is for vendor specific classes */
/** @} */

/*
 * A mask for new GOST algorithms.
 * For details visit https://tc26.ru/standarts/perevody/guidelines-the-pkcs-11-extensions-for-implementing-the-gost-r-34-10-2012-and-gost-r-34-11-2012-russian-standards-.html
 */
#define NSSCK_VENDOR_PKCS11_RU_TEAM    (CKK_VENDOR_DEFINED | 0x54321000UL)
#define CK_VENDOR_PKCS11_RU_TEAM_TK26  NSSCK_VENDOR_PKCS11_RU_TEAM

#define CKK_GOSTR3410_512  (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x003UL)


typedef CK_ULONG CK_CERTIFICATE_TYPE; /*!< X.509 certificat types */

/**
 * @defgroup PKCS11_Certificate_Types PKCS#11 certificate types
 * @{
 */
#define CKC_X_509           0x00000000UL /*!< X.509 Public Key Certificate */
#define CKC_WTLS            0x00000001UL /*!< WTLS Public Key Certificate */
#define CKC_X_509_ATTR_CERT 0x00000002UL /*!< X.509 Attribute Certificate */
#define CKC_VENDOR_DEFINED  0x80000000UL /*!< Anything >= to this is for vendor specific classes */
/** @} */


typedef CK_ULONG CK_CERTIFICATE_CATEGORY; /*!< Certificat category */

/**
 * @defgroup PKCS11_Certificate_Category PKCS#11 certificate categories
 * @{
 */
#define CK_CERTIFICATE_CATEGORY_UNSPECIFIED   0x00000000UL /*!< No category specified */
#define CK_CERTIFICATE_CATEGORY_TOKEN_USER    0x00000001UL /*!< Token origin certificate */
#define CK_CERTIFICATE_CATEGORY_AUTHORITY     0x00000002UL /*!< Certificate Authority (CA) certificate */
#define CK_CERTIFICATE_CATEGORY_OTHER_ENTITY  0x00000003UL /*!< Non-CA endpoint certificate */
/** @} */


typedef CK_ULONG CK_ATTRIBUTE_TYPE; /*!< Attribute types */

#define CKF_ARRAY_ATTRIBUTE  0x40000000UL /*!< Attribute is an array */

/**
 * @defgroup PKCS11_Attribute_Types PKCS#11 attribute types
 * @{
 */
#define CKA_CLASS                       0x00000000UL /*!< Object class - type: CK_OBJECT_CLASS */
#define CKA_TOKEN                       0x00000001UL /*!< True if token object, false otherwise - type: CK_BBOOL */
#define CKA_PRIVATE                     0x00000002UL /*!< True if private object, false otherwise - type: CK_BBOOL */
#define CKA_LABEL                       0x00000003UL /*!< Object description (default empty) - type: CK_UTF8CHAR array */
#define CKA_UNIQUE_ID                   0x00000004UL /*!< Object unique identfier - type: CK_UTF8CHAR array */
#define CKA_APPLICATION                 0x00000010UL /*!< Application description which manages object - type: CK_UTF8CHAR array */
#define CKA_VALUE                       0x00000011UL /*!< Value which depends on the object type - type: varies */
#define CKA_OBJECT_ID                   0x00000012UL /*!< DER-encoding of the object identifier indicating the data object type - type: CK_BYTE array */

#define CKA_CERTIFICATE_TYPE            0x00000080UL /*!< Certificate type - type: CK_CERTIFICATE_TYPE */
#define CKA_ISSUER                      0x00000081UL /*!< DER-encoding of the certificate issuer name (default empty)  - type: CK_BYTE array */
#define CKA_SERIAL_NUMBER               0x00000082UL /*!< DER-encoding of the certificate serial number (default empty) - type: CK_BYTE array */
#define CKA_AC_ISSUER                   0x00000083UL /*!< DER-encoding of the attribute certificate's issuer field. (default empty) - type: CK_BYTE array */
#define CKA_OWNER                       0x00000084UL /*!< DER-encoding of the attribute certificate's subject field. - type: CK_BYTE array */
#define CKA_ATTR_TYPES                  0x00000085UL /*!< BER-encoding of a sequence of object identifier values corresponding to the attribute types contained in the certificate. (default empty) - type: CK_BYTE array */
#define CKA_TRUSTED                     0x00000086UL /*!< Certificate can be trusted by application - type: CK_BBOOL */
#define CKA_CERTIFICATE_CATEGORY        0x00000087UL /*!< Certificate category - type: CK_CERTIFICATE_CATEGORY */
#define CKA_JAVA_MIDP_SECURITY_DOMAIN   0x00000088UL /*!< Java MIDP security domain.  (default CK_SECURITY_DOMAIN_UNSPECIFIED) - type: CK_JAVA_MIDP_SECURITY_DOMAIN */
#define CKA_URL                         0x00000089UL /*!< Certificate download URL if not empty - type: CK_UTF8CHAR array */
#define CKA_HASH_OF_SUBJECT_PUBLIC_KEY  0x0000008AUL /*!< Hash of the subject public key (default empty) - type: CK_BYTE array */
#define CKA_HASH_OF_ISSUER_PUBLIC_KEY   0x0000008BUL /*!< Hash of the issuer public key (default empty) - type: CK_BYTE array */
#define CKA_NAME_HASH_ALGORITHM         0x0000008CUL /*!< Hash algorithm used in certificate (default SHA1 if absent) - type: CK_MECHANISM_TYPE */
#define CKA_CHECK_VALUE                 0x00000090UL /*!< Checksum - type: CK_BYTE array */

#define CKA_KEY_TYPE                    0x00000100UL /*!< Key type - type: CK_KEY_TYPE */
#define CKA_SUBJECT                     0x00000101UL /*!< DER-encoding of the certificate subject name - type: CK_BYTE array */
#define CKA_ID                          0x00000102UL /*!<Key identifier of keypair (default empty) - type: CK_BYTE array */
#define CKA_SENSITIVE                   0x00000103UL /*!< True if key is sensitive (tied to user login) - type: CK_BBOOL */
#define CKA_ENCRYPT                     0x00000104UL /*!< True if key supports encryption - type: CK_BBOOL */
#define CKA_DECRYPT                     0x00000105UL /*!< True if key supports decryption - type: CK_BBOOL */
#define CKA_WRAP                        0x00000106UL /*!< True if key supports key wrapping - type: CK_BBOOL */
#define CKA_UNWRAP                      0x00000107UL /*!< True if key supports key unwrapping - type: CK_BBOOL */
#define CKA_SIGN                        0x00000108UL /*!< True if key supports appendix signature generation - type: CK_BBOOL */
#define CKA_SIGN_RECOVER                0x00000109UL /*!< True if key supports recovery signature generation - type: CK_BBOOL */
#define CKA_VERIFY                      0x0000010AUL /*!< True if key supports appendix signature verification - type: CK_BBOOL */
#define CKA_VERIFY_RECOVER              0x0000010BUL /*!< True if key supports recovery signature verification - type: CK_BBOOL */
#define CKA_DERIVE                      0x0000010CUL /*!< True if key supports key derivation - type: CK_BBOOL */
#define CKA_START_DATE                  0x00000110UL /*!< Certificate start date - type: CK_DATE */
#define CKA_END_DATE                    0x00000111UL /*!< Certificate end date - type: CK_DATE */

#define CKA_MODULUS                     0x00000120UL /*!< RSA modulus - type: CK_BYTE string (big integer) */
#define CKA_MODULUS_BITS                0x00000121UL /*!< RSA modulus size in bits - type: CK_ULONG */
#define CKA_PUBLIC_EXPONENT             0x00000122UL /*!< RSA public exponent e - type: CK_BYTE string (big integer) */
#define CKA_PRIVATE_EXPONENT            0x00000123UL /*!< RSA private exponent d - type: CK_BYTE string (big integer) */
#define CKA_PRIME_1                     0x00000124UL /*!< RSA prime p - type: CK_BYTE string (big integer) */
#define CKA_PRIME_2                     0x00000125UL /*!< RSA prime q - type: CK_BYTE string (big integer) */
#define CKA_EXPONENT_1                  0x00000126UL /*!< RSA private exponent d modulo p-1  - type: CK_BYTE string (big integer) */
#define CKA_EXPONENT_2                  0x00000127UL /*!< RSA private exponent d modulo q-1  - type: CK_BYTE string (big integer) */
#define CKA_COEFFICIENT                 0x00000128UL /*!< RSA CRT coefficient q-1 mod p - type: CK_BYTE string (big integer) */
#define CKA_PUBLIC_KEY_INFO             0x00000129UL /*!< DER-encoding of the SubjectPublicKeyInfo for this public key - type: CK_BYTE array */
#define CKA_PRIME                       0x00000130UL /*!< DSA prime p - type: CK_BYTE string (big integer) */
#define CKA_SUBPRIME                    0x00000131UL /*!< DSA subprime q - type: CK_BYTE string (big integer) */
#define CKA_BASE                        0x00000132UL /*!< DSA base g - type: CK_BYTE string (big integer) */
#define CKA_PRIME_BITS                  0x00000133UL /*!< DSA prime size in bits - type: CK_ULONG */
#define CKA_SUBPRIME_BITS               0x00000134UL /*!< DSA subprime size in bits (optional) - type: CK_ULONG */
#define CKA_SUB_PRIME_BITS              CKA_SUBPRIME_BITS /*!< compat */

#define CKA_VALUE_BITS                  0x00000160UL /*!< DH length in bits of private value x - type: CK_ULONG */
#define CKA_VALUE_LEN                   0x00000161UL /*!< Secret key length in bytes - type: CK_ULONG */

#define CKA_EXTRACTABLE                 0x00000162UL /*!< True if key can be extracted and wrapped - type: CK_BBOOL */
#define CKA_LOCAL                       0x00000163UL /*!< True if key originates from token (includes copies) - type: CK_BBOOL */
#define CKA_NEVER_EXTRACTABLE           0x00000164UL /*!< True if CKA_EXTRACTABLE was never True - type: CK_BBOOL */
#define CKA_ALWAYS_SENSITIVE            0x00000165UL /*!< True if CKA_SENSITIVE was always True - type: CK_BBOOL */
#define CKA_KEY_GEN_MECHANISM           0x00000166UL /*!< Mechanism used to generate the key - type: CK_MECHANISM_TYPE */

#define CKA_MODIFIABLE                  0x00000170UL /*!< True if object is modifiable, false otherwise - type: CK_BBOOL */
#define CKA_COPYABLE                    0x00000171UL /*!< True if object can be copied with C_CopyObject, false otherwise - type: CK_BBOOL */
#define CKA_DESTROYABLE                 0x00000172UL /*!< True if object can be destroyed with C_DestroyObject, false otherwise - type: CK_BBOOL */

#define CKA_EC_PARAMS                   0x00000180UL /*!< EC DER-encoding of an ANSI X9.62 Parameters value - type: CK_BYTE array */
#define CKA_ECDSA_PARAMS                CKA_EC_PARAMS /*!< compat */
#define CKA_EC_POINT                    0x00000181UL /*!< EC DER-encoding of ANSI X9.62 ECPoint value Q - type: CK_BYTE array */

#define CKA_ALWAYS_AUTHENTICATE         0x00000200UL /*!< True if key can only be used with a logged in user - type: CK_BBOOL */
#define CKA_SECONDARY_AUTH              0x00000201UL /*!< compat */
#define CKA_AUTH_PIN_FLAGS              0x00000202UL /*!< compat */

#define CKA_WRAP_WITH_TRUSTED           0x00000210UL /*!< True if key can only be wrapped with a CKA_TRUSTED key - type: CK_BBOOL */
#define CKA_WRAP_TEMPLATE               (CKF_ARRAY_ATTRIBUTE|0x00000211UL) /*!< Attributes that must possess the wrapped target key - type: CK_ATTRIBUTE array */
#define CKA_UNWRAP_TEMPLATE             (CKF_ARRAY_ATTRIBUTE|0x00000212UL) /*!< Attributes that must possess the unwrapped target key - type: CK_ATTRIBUTE array */
#define CKA_DERIVE_TEMPLATE             (CKF_ARRAY_ATTRIBUTE|0x00000213UL) /*!< Attributes that must possess the application derive template to allow key derivation to be successful - type: CK_ATTRIBUTE array (this is an extension) */

#define CKA_HW_FEATURE_TYPE             0x00000300UL /*!< Hardware feature type - type: CK_HW_FEATURE_TYPE */
#define CKA_RESET_ON_INIT               0x00000301UL /*!< Monotonic counter reset on C_InitToken - type: CK_BBOOL */
#define CKA_HAS_RESET                   0x00000302UL /*!< Monotonic counter was reset at least once - type: CK_BBOOL */

#define CKA_GOSTR3410_PARAMS            0x00000310UL
#define CKA_GOSTR3411_PARAMS            0x00000311UL
#define CKA_GOST28147_PARAMS            0x00000312UL

#define CKA_OTP_FORMAT                  0x00000320UL
#define CKA_OTP_LENGTH                  0x00000321UL
#define CKA_OTP_TIME_INTERVAL           0x00000322UL
#define CKA_OTP_USER_FRIENDLY_MODE      0x00000323UL
#define CKA_OTP_CHALLENGE_REQUIREMENT   0x00000324UL
#define CKA_OTP_TIME_REQUIREMENT        0x00000325UL
#define CKA_OTP_COUNTER_REQUIREMENT     0x00000326UL
#define CKA_OTP_PIN_REQUIREMENT         0x00000327UL
#define CKA_OTP_USER_IDENTIFIER         0x00000328UL
#define CKA_OTP_SERVICE_IDENTIFIER      0x00000329UL
#define CKA_OTP_SERVICE_LOGO            0x0000032AUL
#define CKA_OTP_SERVICE_LOGO_TYPE       0x0000032BUL
#define CKA_OTP_COUNTER                 0x0000032CUL
#define CKA_OTP_TIME                    0x0000032DUL

#define CKA_REQUIRED_CMS_ATTRIBUTES     0x00000340UL
#define CKA_DEFAULT_CMS_ATTRIBUTES      0x00000341UL
#define CKA_SUPPORTED_CMS_ATTRIBUTES    0x00000342UL

#define CKA_PIXEL_X                     0x00000350UL
#define CKA_PIXEL_Y                     0x00000351UL
#define CKA_RESOLUTION                  0x00000352UL
#define CKA_CHAR_ROWS                   0x00000353UL
#define CKA_CHAR_COLUMNS                0x00000354UL
#define CKA_COLOR                       0x00000355UL
#define CKA_BITS_PER_PIXEL              0x00000356UL
#define CKA_CHAR_SETS                   0x00000357UL
#define CKA_ENCODING_METHODS            0x00000358UL
#define CKA_MIME_TYPES                  0x00000359UL

#define CKA_MECHANISM_TYPE              0x00000500UL

#define CKA_ALLOWED_MECHANISMS          (CKF_ARRAY_ATTRIBUTE|0x00000600UL) /*!< List of allowed mechanisms to be used with a key - type: CK_MECHANISM_TYPE array */
#define CKA_PROFILE_ID                  0x00000601UL /*!< Supported profile identifier - type: CK_PROFILE_ID */

#define CKA_VENDOR_DEFINED              0x80000000UL /*!< Anything >= to this is for vendor specific classes */
/** @} */

/**
 * @brief Attribute object
 */
typedef struct CK_ATTRIBUTE_ {
	CK_ATTRIBUTE_TYPE type; /*!< Attribute type */
	CK_VOID_PTR pValue; /*!< Pointer to some value (NULL for no value) */
	CK_ULONG ulValueLen; /*!< value length in bytes (0 for no value) */
} CK_ATTRIBUTE;

typedef CK_ATTRIBUTE* CK_ATTRIBUTE_PTR; /*!< pointer to CK_ATTRIBUTE */

/**
 * @brief Date object
 */
typedef struct CK_DATE_ {
	CK_CHAR year[4]; /*!< 1900 - 9999 */
	CK_CHAR month[2]; /*!< month 01 - 12 */
	CK_CHAR day[2]; /*!< day 01 - 31 */
} CK_DATE;


typedef CK_ULONG CK_PROFILE_ID; /*!< Token profile identification number - See PKCS#11 Profile spec */
typedef CK_PROFILE_ID* CK_PROFILE_ID_PTR; /*!< pointer to CK_PROFILE_ID */


/**
 * @defgroup PKCS11_Profile_IDs PKCS#11 profile identification numbers
 * @{
 */
#define CKP_INVALID_ID                 0x00000000UL
#define CKP_BASELINE_PROVIDER          0x00000001UL
#define CKP_EXTENDED_PROVIDER          0x00000002UL
#define CKP_AUTHENTICATION_TOKEN       0x00000003UL
#define CKP_PUBLIC_CERTIFICATES_TOKEN  0x00000004UL
#define CKP_VENDOR_DEFINED             0x80000000UL /*!< Anything >= to this is for vendor specific profiles */
/** @} */


typedef CK_ULONG CK_JAVA_MIDP_SECURITY_DOMAIN; /*!< Certificate Java MIDP security domain */

/**
 * @defgroup PKCS11_Security_Domain PKCS#11 Java MIDP security domain
 * @{
 */
#define CK_SECURITY_DOMAIN_UNSPECIFIED   0x00000000UL /*!< No domain specified */
#define CK_SECURITY_DOMAIN_MANUFACTURER  0x00000001UL /*!< Manufacturer protection domain */
#define CK_SECURITY_DOMAIN_OPERATOR      0x00000002UL /*!< Operator protection domain */
#define CK_SECURITY_DOMAIN_THIRD_PARTY   0x00000003UL /*!< Third party protection domain */
/** @} */


typedef CK_ULONG CK_MECHANISM_TYPE; /*!< Mechanism types */
typedef CK_MECHANISM_TYPE* CK_MECHANISM_TYPE_PTR; /*!< pointer to CK_MECHANISM_TYPE */

/**
 * @defgroup PKCS11_Mechanism_Types PKCS#11 mechanism types
 * @{
 */
/* RSA */
#define CKM_RSA_PKCS_KEY_PAIR_GEN             0x00000000UL
#define CKM_RSA_PKCS                          0x00000001UL
#define CKM_RSA_9796                          0x00000002UL
#define CKM_RSA_X_509                         0x00000003UL
#define CKM_MD2_RSA_PKCS                      0x00000004UL
#define CKM_MD5_RSA_PKCS                      0x00000005UL
#define CKM_SHA1_RSA_PKCS                     0x00000006UL
#define CKM_SHA224_RSA_PKCS                   0x00000007UL
#define CKM_SHA256_RSA_PKCS                   0x00000008UL
#define CKM_SHA384_RSA_PKCS                   0x00000009UL
#define CKM_SHA512_RSA_PKCS                   0x0000000AUL
#define CKM_RIPEMD128_RSA_PKCS                0x0000000BUL
#define CKM_RIPEMD160_RSA_PKCS                0x0000000CUL
#define CKM_RSA_PKCS_OAEP                     0x0000000DUL
#define CKM_RSA_X9_31_KEY_PAIR_GEN            0x0000000EUL
#define CKM_RSA_X9_31                         0x0000000FUL
#define CKM_SHA1_RSA_X9_31                    0x00000010UL
#define CKM_RSA_PKCS_PSS                      0x00000011UL
#define CKM_SHA1_RSA_PKCS_PSS                 0x00000012UL
#define CKM_SHA224_RSA_PKCS_PSS               0x00000013UL
#define CKM_SHA256_RSA_PKCS_PSS               0x00000014UL
#define CKM_SHA512_RSA_PKCS_PSS               0x00000015UL
#define CKM_SHA384_RSA_PKCS_PSS               0x00000016UL
#define CKM_RSA_PKCS_TPM_1_1                  0x00000017UL
#define CKM_RSA_PKCS_OAEP_TPM_1_1             0x00000018UL
#define CKM_RSA_AES_KEY_WRAP                  0x00000019UL
#define CKM_SHA3_224_RSA_PKCS                 0x0000001AUL
#define CKM_SHA3_256_RSA_PKCS                 0x0000001BUL
#define CKM_SHA3_384_RSA_PKCS                 0x0000001CUL
#define CKM_SHA3_512_RSA_PKCS                 0x0000001DUL
#define CKM_SHA3_224_RSA_PKCS_PSS             0x0000001EUL
#define CKM_SHA3_256_RSA_PKCS_PSS             0x0000001FUL
#define CKM_SHA3_384_RSA_PKCS_PSS             0x00000020UL
#define CKM_SHA3_512_RSA_PKCS_PSS             0x00000021UL

/* DSA */
#define CKM_DSA_KEY_PAIR_GEN                  0x00000030UL
#define CKM_DSA                               0x00000031UL
#define CKM_DSA_SHA1                          0x00000032UL
#define CKM_DSA_SHA224                        0x00000033UL
#define CKM_DSA_SHA256                        0x00000034UL
#define CKM_DSA_SHA384                        0x00000035UL
#define CKM_DSA_SHA512                        0x00000036UL
#define CKM_DSA_SHA3_224                      0x00000037UL
#define CKM_DSA_SHA3_256                      0x00000038UL
#define CKM_DSA_SHA3_384                      0x00000039UL
#define CKM_DSA_SHA3_512                      0x0000003AUL
#define CKM_DSA_PARAMETER_GEN                 0x0000003BUL
#define CKM_DSA_PROBABILISTIC_PARAMETER_GEN   0x0000003CUL
#define CKM_DSA_SHAWE_TAYLOR_PARAMETER_GEN    0x0000003DUL
#define CKM_DSA_FIPS_G_GEN                    0x0000003EUL

/* EC / Edwards */
#define CKM_EC_KEY_PAIR_GEN                   0x00000040UL
#define CKM_ECDSA_KEY_PAIR_GEN                CKM_EC_KEY_PAIR_GEN /*!< compat */
#define CKM_EC_EDWARDS_KEY_PAIR_GEN           0x00000041UL
#define CKM_EC_MONTGOMERY_KEY_PAIR_GEN        0x00000042UL
#define CKM_ECDSA                             0x00000043UL
#define CKM_ECDSA_SHA1                        0x00000044UL
#define CKM_ECDSA_SHA224                      0x00000045UL
#define CKM_ECDSA_SHA256                      0x00000046UL
#define CKM_ECDSA_SHA384                      0x00000047UL
#define CKM_ECDSA_SHA512                      0x00000048UL
#define CKM_ECDSA_SHA3_224                    0x00000049UL
#define CKM_ECDSA_SHA3_256                    0x0000004AUL
#define CKM_ECDSA_SHA3_384                    0x0000004BUL
#define CKM_ECDSA_SHA3_512                    0x0000004CUL
#define CKM_EDDSA                             0x0000004DUL
#define CKM_XEDDSA                            0x0000004EUL
#define CKM_ECDH1_DERIVE                      0x0000004FUL
#define CKM_ECDH1_COFACTOR_DERIVE             0x00000050UL
#define CKM_ECMQV_DERIVE                      0x00000051UL
#define CKM_ECDH_AES_KEY_WRAP                 0x00000052UL

/* Diffie-Hellman */
#define CKM_DH_PKCS_KEY_PAIR_GEN              0x00000060UL
#define CKM_DH_PKCS_PARAMETER_GEN             0x00000061UL
#define CKM_DH_PKCS_DERIVE                    0x00000062UL
#define CKM_X9_42_DH_KEY_PAIR_GEN             0x00000063UL
#define CKM_X9_42_DH_PARAMETER_GEN            0x00000064UL
#define CKM_X9_42_DH_DERIVE                   0x00000065UL
#define CKM_X9_42_DH_HYBRID_DERIVE            0x00000066UL
#define CKM_X9_42_MQV_DERIVE                  0x00000067UL

/* Extended Triple Diffie-Hellman */
#define CKM_X3DH_INITIALIZE                   0x00000070UL
#define CKM_X3DH_RESPOND                      0x00000071UL

/* Double Ratchet */
#define CKM_X2RATCHET_INITIALIZE              0x00000080UL
#define CKM_X2RATCHET_RESPOND                 0x00000081UL
#define CKM_X2RATCHET_ENCRYPT                 0x00000082UL
#define CKM_X2RATCHET_DECRYPT                 0x00000083UL

/* AES */
#define CKM_AES_KEY_GEN                       0x00000090UL
#define CKM_AES_ECB                           0x00000091UL
#define CKM_AES_CBC                           0x00000092UL
#define CKM_AES_MAC                           0x00000093UL
#define CKM_AES_MAC_GENERAL                   0x00000094UL
#define CKM_AES_CBC_PAD                       0x00000095UL
#define CKM_AES_OFB                           0x00000096UL
#define CKM_AES_CFB64                         0x00000097UL
#define CKM_AES_CFB8                          0x00000098UL
#define CKM_AES_CFB128                        0x00000099UL
#define CKM_AES_CFB1                          0x0000009AUL
#define CKM_AES_XCBC_MAC                      0x0000009BUL
#define CKM_AES_XCBC_MAC_96                   0x0000009CUL
#define CKM_AES_CTR                           0x0000009DUL
#define CKM_AES_CTS                           0x0000009EUL
#define CKM_AES_GCM                           0x0000009FUL
#define CKM_AES_CCM                           0x000000A0UL
#define CKM_AES_GMAC                          0x000000A1UL
#define CKM_AES_CMAC_GENERAL                  0x000000A2UL
#define CKM_AES_CMAC                          0x000000A3UL
#define CKM_AES_XTS                           0x000000A4UL
#define CKM_AES_XTS_KEY_GEN                   0x000000A5UL
#define CKM_AES_KEY_WRAP                      0x000000A6UL
#define CKM_AES_KEY_WRAP_PAD                  0x000000A7UL
#define CKM_AES_KEY_WRAP_KWP                  0x000000A8UL
#define CKM_AES_ECB_ENCRYPT_DATA              0x000000A9UL
#define CKM_AES_CBC_ENCRYPT_DATA              0x000000AAUL

/* DES */
#define CKM_DES2_KEY_GEN                      0x000000B0UL
#define CKM_DES3_KEY_GEN                      0x000000B1UL
#define CKM_DES3_ECB                          0x000000B2UL
#define CKM_DES3_CBC                          0x000000B3UL
#define CKM_DES3_MAC                          0x000000B4UL
#define CKM_DES3_MAC_GENERAL                  0x000000B5UL
#define CKM_DES3_CBC_PAD                      0x000000B6UL
#define CKM_DES_OFB64                         0x000000B7UL
#define CKM_DES_OFB8                          0x000000B8UL
#define CKM_DES_CFB64                         0x000000B9UL
#define CKM_DES_CFB8                          0x000000BAUL
#define CKM_DES3_CMAC_GENERAL                 0x000000BBUL
#define CKM_DES3_CMAC                         0x000000BCUL
#define CKM_DES_ECB_ENCRYPT_DATA              0x000000BDUL
#define CKM_DES_CBC_ENCRYPT_DATA              0x000000BEUL
#define CKM_DES3_ECB_ENCRYPT_DATA             0x000000BFUL
#define CKM_DES3_CBC_ENCRYPT_DATA             0x000000C0UL

/* SHA 1/2/3 */
#define CKM_SHA_1                             0x000000D0UL
#define CKM_SHA_1_HMAC                        0x000000D1UL
#define CKM_SHA_1_HMAC_GENERAL                0x000000D2UL
#define CKM_SHA1_KEY_DERIVATION               0x000000D3UL
#define CKM_SHA_1_KEY_GEN                     0x000000D4UL
#define CKM_SHA224                            0x000000D5UL
#define CKM_SHA224_HMAC                       0x000000D6UL
#define CKM_SHA224_HMAC_GENERAL               0x000000D7UL
#define CKM_SHA224_KEY_DERIVATION             0x000000D8UL
#define CKM_SHA224_KEY_GEN                    0x000000D9UL
#define CKM_SHA256                            0x000000DAUL
#define CKM_SHA256_HMAC                       0x000000DBUL
#define CKM_SHA256_HMAC_GENERAL               0x000000DCUL
#define CKM_SHA256_KEY_DERIVATION             0x000000DDUL
#define CKM_SHA256_KEY_GEN                    0x000000DEUL
#define CKM_SHA384                            0x000000DFUL
#define CKM_SHA384_HMAC                       0x000000E0UL
#define CKM_SHA384_HMAC_GENERAL               0x000000E1UL
#define CKM_SHA384_KEY_DERIVATION             0x000000E2UL
#define CKM_SHA384_KEY_GEN                    0x000000E3UL
#define CKM_SHA512                            0x000000E4UL
#define CKM_SHA512_HMAC                       0x000000E5UL
#define CKM_SHA512_HMAC_GENERAL               0x000000E6UL
#define CKM_SHA512_KEY_DERIVATION             0x000000E7UL
#define CKM_SHA512_KEY_GEN                    0x000000E8UL
#define CKM_SHA512_224                        0x000000E9UL
#define CKM_SHA512_224_HMAC                   0x000000EAUL
#define CKM_SHA512_224_HMAC_GENERAL           0x000000EBUL
#define CKM_SHA512_224_KEY_DERIVATION         0x000000ECUL
#define CKM_SHA512_224_KEY_GEN                0x000000EDUL
#define CKM_SHA512_256                        0x000000EEUL
#define CKM_SHA512_256_HMAC                   0x000000EFUL
#define CKM_SHA512_256_HMAC_GENERAL           0x000000F0UL
#define CKM_SHA512_256_KEY_DERIVATION         0x000000F1UL
#define CKM_SHA512_256_KEY_GEN                0x000000F2UL
#define CKM_SHA3_224                          0x000000F3UL
#define CKM_SHA3_224_HMAC                     0x000000F4UL
#define CKM_SHA3_224_HMAC_GENERAL             0x000000F5UL
#define CKM_SHA3_224_KEY_DERIVATION           0x000000F6UL
#define CKM_SHA3_224_KEY_GEN                  0x000000F7UL
#define CKM_SHA3_256                          0x000000F8UL
#define CKM_SHA3_256_HMAC                     0x000000F9UL
#define CKM_SHA3_256_HMAC_GENERAL             0x000000FAUL
#define CKM_SHA3_256_KEY_DERIVATION           0x000000FBUL
#define CKM_SHA3_256_KEY_GEN                  0x000000FCUL
#define CKM_SHA3_384                          0x000000FDUL
#define CKM_SHA3_384_HMAC                     0x000000FEUL
#define CKM_SHA3_384_HMAC_GENERAL             0x000000FFUL
#define CKM_SHA3_384_KEY_DERIVATION           0x00000100UL
#define CKM_SHA3_384_KEY_GEN                  0x00000101UL
#define CKM_SHA3_512                          0x00000102UL
#define CKM_SHA3_512_HMAC                     0x00000103UL
#define CKM_SHA3_512_HMAC_GENERAL             0x00000104UL
#define CKM_SHA3_512_KEY_DERIVATION           0x00000105UL
#define CKM_SHA3_512_KEY_GEN                  0x00000106UL

/* SHAKE */
#define CKM_SHAKE_128_KEY_DERIVATION          0x00000110UL
#define CKM_SHAKE_256_KEY_DERIVATION          0x00000111UL

/* Blake 2B */
#define CKM_BLAKE2B_160                       0x00000120UL
#define CKM_BLAKE2B_160_HMAC                  0x00000121UL
#define CKM_BLAKE2B_160_HMAC_GENERAL          0x00000122UL
#define CKM_BLAKE2B_160_KEY_DERIVE            0x00000123UL
#define CKM_BLAKE2B_160_KEY_GEN               0x00000124UL
#define CKM_BLAKE2B_256                       0x00000125UL
#define CKM_BLAKE2B_256_HMAC                  0x00000126UL
#define CKM_BLAKE2B_256_HMAC_GENERAL          0x00000127UL
#define CKM_BLAKE2B_256_KEY_DERIVE            0x00000128UL
#define CKM_BLAKE2B_256_KEY_GEN               0x00000129UL
#define CKM_BLAKE2B_384                       0x0000012AUL
#define CKM_BLAKE2B_384_HMAC                  0x0000012BUL
#define CKM_BLAKE2B_384_HMAC_GENERAL          0x0000012CUL
#define CKM_BLAKE2B_384_KEY_DERIVE            0x0000012DUL
#define CKM_BLAKE2B_384_KEY_GEN               0x0000012EUL
#define CKM_BLAKE2B_512                       0x0000012FUL
#define CKM_BLAKE2B_512_HMAC                  0x00000130UL
#define CKM_BLAKE2B_512_HMAC_GENERAL          0x00000131UL
#define CKM_BLAKE2B_512_KEY_DERIVE            0x00000132UL
#define CKM_BLAKE2B_512_KEY_GEN               0x00000133UL

/* PKCS#5 PBKDF2 */
#define CKM_PKCS5_PBKD2                       0x00000140UL

/* PKCS#12 PBE */
#define CKM_PBE_SHA1_DES3_EDE_CBC             0x00000150UL
#define CKM_PBE_SHA1_DES2_EDE_CBC             0x00000151UL
#define CKM_PBA_SHA1_WITH_SHA1_HMAC           0x00000152UL

/* Generic Secret Key */
#define CKM_GENERIC_SECRET_KEY_GEN            0x00000160UL
#define CKM_CONCATENATE_BASE_AND_KEY          0x00000161UL
#define CKM_CONCATENATE_BASE_AND_DATA         0x00000162UL
#define CKM_CONCATENATE_DATA_AND_BASE         0x00000163UL
#define CKM_XOR_BASE_AND_DATA                 0x00000164UL
#define CKM_EXTRACT_KEY_FROM_KEY              0x00000165UL

/* SSL 3.0 */
#define CKM_SSL3_PRE_MASTER_KEY_GEN           0x00000170UL
#define CKM_TLS_PRE_MASTER_KEY_GEN            0x00000171UL
#define CKM_SSL3_MASTER_KEY_DERIVE            0x00000172UL
#define CKM_SSL3_KEY_AND_MAC_DERIVE           0x00000173UL
#define CKM_SSL3_MASTER_KEY_DERIVE_DH         0x00000174UL
#define CKM_SSL3_MD5_MAC                      0x00000175UL
#define CKM_SSL3_SHA1_MAC                     0x00000176UL

/* TLS 1.0 / 1.2 */
#define CKM_TLS12_MASTER_KEY_DERIVE           0x00000180UL
#define CKM_TLS12_MASTER_KEY_DERIVE_DH        0x00000181UL
#define CKM_TLS12_KEY_AND_MAC_DERIVE          0x00000182UL
#define CKM_TLS12_KEY_SAFE_DERIVE             0x00000183UL
#define CKM_TLS_KDF                           0x00000184UL
#define CKM_TLS12_MAC                         0x00000185UL
#define CKM_TLS12_KDF                         0x00000186UL
#define CKM_TLS_MASTER_KEY_DERIVE             0x00000187UL
#define CKM_TLS_KEY_AND_MAC_DERIVE            0x00000188UL
#define CKM_TLS_MASTER_KEY_DERIVE_DH          0x00000189UL

/* CMS */
#define CKM_CMS_SIG                           0x00000190UL

/* Blowfish */
#define CKM_BLOWFISH_KEY_GEN                  0x000001A0UL
#define CKM_BLOWFISH_CBC                      0x000001A1UL
#define CKM_BLOWFISH_CBC_PAD                  0x000001A2UL

/* Twofish */
#define CKM_TWOFISH_KEY_GEN                   0x000001B0UL
#define CKM_TWOFISH_CBC                       0x000001B1UL
#define CKM_TWOFISH_CBC_PAD                   0x000001B2UL

/* Camelia */
#define CKM_CAMELLIA_KEY_GEN                  0x000001C0UL
#define CKM_CAMELLIA_ECB                      0x000001C1UL
#define CKM_CAMELLIA_CBC                      0x000001C2UL
#define CKM_CAMELLIA_MAC                      0x000001C3UL
#define CKM_CAMELLIA_MAC_GENERAL              0x000001C4UL
#define CKM_CAMELLIA_CBC_PAD                  0x000001C5UL
#define CKM_CAMELLIA_ECB_ENCRYPT_DATA         0x000001C6UL
#define CKM_CAMELLIA_CBC_ENCRYPT_DATA         0x000001C7UL

/* Aria */
#define CKM_ARIA_KEY_GEN                      0x000001D0UL
#define CKM_ARIA_ECB                          0x000001D1UL
#define CKM_ARIA_CBC                          0x000001D2UL
#define CKM_ARIA_MAC                          0x000001D3UL
#define CKM_ARIA_MAC_GENERAL                  0x000001D4UL
#define CKM_ARIA_CBC_PAD                      0x000001D5UL
#define CKM_ARIA_ECB_ENCRYPT_DATA             0x000001D6UL
#define CKM_ARIA_CBC_ENCRYPT_DATA             0x000001D7UL

/* SEED */
#define CKM_SEED_KEY_GEN                      0x000001E0UL
#define CKM_SEED_ECB                          0x000001E1UL
#define CKM_SEED_CBC                          0x000001E2UL
#define CKM_SEED_MAC                          0x000001E3UL
#define CKM_SEED_MAC_GENERAL                  0x000001E4UL
#define CKM_SEED_CBC_PAD                      0x000001E5UL
#define CKM_SEED_ECB_ENCRYPT_DATA             0x000001E6UL
#define CKM_SEED_CBC_ENCRYPT_DATA             0x000001E7UL

/* GOST (Russian Algorithms) */
#define CKM_GOSTR3410_KEY_PAIR_GEN            0x00000200UL
#define CKM_GOSTR3410                         0x00000201UL
#define CKM_GOSTR3410_WITH_GOSTR3411          0x00000202UL
#define CKM_GOSTR3410_KEY_WRAP                0x00000203UL
#define CKM_GOSTR3410_DERIVE                  0x00000204UL
#define CKM_GOSTR3410_512_KEY_PAIR_GEN        (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000005UL)
#define CKM_GOSTR3410_512                     (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000006UL)
#define CKM_GOSTR3410_12_DERIVE               (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000007UL)
#define CKM_GOSTR3410_WITH_GOSTR3411_12_256   (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000008UL)
#define CKM_GOSTR3410_WITH_GOSTR3411_12_512   (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000009UL)
#define CKM_GOSTR3411                         0x0000020AUL
#define CKM_GOSTR3411_HMAC                    0x0000020BUL
#define CKM_GOSTR3411_12_256                  (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000012)
#define CKM_GOSTR3411_12_512                  (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000013)
#define CKM_GOSTR3411_12_256_HMAC             (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000014)
#define CKM_GOSTR3411_12_512_HMAC             (CK_VENDOR_PKCS11_RU_TEAM_TK26 | 0x00000015)
#define CKM_GOST28147_KEY_GEN                 0x00000210UL
#define CKM_GOST28147_ECB                     0x00000211UL
#define CKM_GOST28147                         0x00000212UL
#define CKM_GOST28147_MAC                     0x00000213UL
#define CKM_GOST28147_KEY_WRAP                0x00000214UL

/* ChaCha20 */
#define CKM_CHACHA20_KEY_GEN                  0x00000230UL
#define CKM_CHACHA20                          0x00000231UL

/* Salsa20 */
#define CKM_SALSA20_KEY_GEN                   0x00000240UL
#define CKM_SALSA20                           0x00000241UL

/* Poly1305 */
#define CKM_POLY1305_KEY_GEN                  0x00000250UL
#define CKM_POLY1305                          0x00000251UL

/* Chacha20/Salsa20 + Poly1305 */
#define CKM_CHACHA20_POLY1305                 0x00000260UL
#define CKM_SALSA20_POLY1305                  0x00000261UL

/* HKDF */
#define CKM_HKDF_DERIVE                       0x00000270UL
#define CKM_HKDF_DATA                         0x00000271UL
#define CKM_HKDF_KEY_GEN                      0x00000272UL

#define CKM_NULL                              0x00000280UL

/* Legacy Algorithms */
#ifdef QNX_PKCS11_LEGACY
#define CKM_RC2_KEY_GEN                       0x00000300UL
#define CKM_RC2_ECB                           0x00000301UL
#define	CKM_RC2_CBC                           0x00000302UL
#define	CKM_RC2_MAC                           0x00000303UL
#define CKM_RC2_MAC_GENERAL                   0x00000304UL
#define CKM_RC2_CBC_PAD                       0x00000305UL
#define CKM_RC4_KEY_GEN                       0x00000306UL
#define CKM_RC4                               0x00000307UL
#define CKM_DES_KEY_GEN                       0x00000308UL
#define CKM_DES_ECB                           0x00000309UL
#define CKM_DES_CBC                           0x0000030AUL
#define CKM_DES_MAC                           0x0000030BUL
#define CKM_DES_MAC_GENERAL                   0x0000030CUL
#define CKM_DES_CBC_PAD                       0x0000030DUL
#define CKM_CDMF_KEY_GEN                      0x0000030EUL
#define CKM_CDMF_ECB                          0x0000030FUL
#define CKM_CDMF_CBC                          0x00000310UL
#define CKM_CDMF_MAC                          0x00000311UL
#define CKM_CDMF_MAC_GENERAL                  0x00000312UL
#define CKM_CDMF_CBC_PAD                      0x00000313UL
#define CKM_MD2                               0x00000314UL
#define CKM_MD2_HMAC                          0x00000315UL
#define CKM_MD2_HMAC_GENERAL                  0x00000316UL
#define CKM_MD5                               0x00000317UL
#define CKM_MD5_HMAC                          0x00000318UL
#define CKM_MD5_HMAC_GENERAL                  0x00000319UL
#define CKM_RIPEMD128                         0x0000031AUL
#define CKM_RIPEMD128_HMAC                    0x0000031BUL
#define CKM_RIPEMD128_HMAC_GENERAL            0x0000031CUL
#define CKM_RIPEMD160                         0x0000031DUL
#define CKM_RIPEMD160_HMAC                    0x0000031EUL
#define CKM_RIPEMD160_HMAC_GENERAL            0x0000031FUL
#define CKM_CAST_KEY_GEN                      0x00000320UL
#define CKM_CAST_ECB                          0x00000321UL
#define CKM_CAST_CBC                          0x00000322UL
#define CKM_CAST_MAC                          0x00000323UL
#define CKM_CAST_MAC_GENERAL                  0x00000324UL
#define CKM_CAST_CBC_PAD                      0x00000325UL
#define CKM_CAST3_KEY_GEN                     0x00000326UL
#define CKM_CAST3_ECB                         0x00000327UL
#define CKM_CAST3_CBC                         0x00000328UL
#define CKM_CAST3_MAC                         0x00000329UL
#define CKM_CAST3_MAC_GENERAL                 0x0000032AUL
#define CKM_CAST3_CBC_PAD                     0x0000032BUL
#define CKM_CAST5_KEY_GEN                     0x0000032CUL
#define CKM_CAST128_KEY_GEN                   0x0000032DUL
#define CKM_CAST5_ECB                         0x0000032EUL
#define CKM_CAST128_ECB                       0x0000032FUL
#define CKM_CAST5_CBC                         0x00000330UL
#define CKM_CAST128_CBC                       0x00000331UL
#define CKM_CAST5_MAC                         0x00000332UL
#define	CKM_CAST128_MAC                       0x00000333UL
#define CKM_CAST5_MAC_GENERAL                 0x00000334UL
#define CKM_CAST128_MAC_GENERAL               0x00000335UL
#define CKM_CAST5_CBC_PAD                     0x00000336UL
#define CKM_CAST128_CBC_PAD                   0x00000337UL
#define CKM_RC5_KEY_GEN                       0x00000338UL
#define CKM_RC5_ECB                           0x00000339UL
#define CKM_RC5_CBC                           0x0000033AUL
#define CKM_RC5_MAC                           0x0000033BUL
#define CKM_RC5_MAC_GENERAL                   0x0000033CUL
#define CKM_RC5_CBC_PAD                       0x0000033DUL
#define CKM_IDEA_KEY_GEN                      0x0000033EUL
#define CKM_IDEA_ECB                          0x0000033FUL
#define	CKM_IDEA_CBC                          0x00000340UL
#define CKM_IDEA_MAC                          0x00000341UL
#define CKM_IDEA_MAC_GENERAL                  0x00000342UL
#define CKM_IDEA_CBC_PAD                      0x00000343UL
#define CKM_MD5_KEY_DERIVATION                0x00000344UL
#define CKM_MD2_KEY_DERIVATION                0x00000345UL
#define CKM_PBE_MD2_DES_CBC                   0x00000346UL
#define CKM_PBE_MD5_DES_CBC                   0x00000346UL
#define CKM_PBE_MD5_CAST_CBC                  0x00000347UL
#define CKM_PBE_MD5_CAST3_CBC                 0x00000348UL
#define CKM_PBE_MD5_CAST5_CBC                 0x00000349UL
#define CKM_PBE_MD5_CAST128_CBC               0x0000034AUL
#define CKM_PBE_SHA1_CAST5_CBC                0x0000034BUL
#define CKM_PBE_SHA1_CAST128_CBC              0x0000034CUL
#define CKM_PBE_SHA1_RC4_128                  0x0000034DUL
#define CKM_PBE_SHA1_RC4_40                   0x0000034EUL
#define CKM_PBE_SHA1_RC2_128_CBC              0x0000034FUL
#define CKM_PBE_SHA1_RC2_40_CBC               0x00000350UL
#define CKM_KEY_WRAP_LYNKS                    0x00000351UL
#define CKM_KEY_WRAP_SET_OAEP                 0x00000352UL
#define CKM_SKIPJACK_KEY_GEN                  0x00000353UL
#define CKM_SKIPJACK_ECB64                    0x00000354UL
#define CKM_SKIPJACK_CBC64                    0x00000355UL
#define CKM_SKIPJACK_OFB64                    0x00000356UL
#define CKM_SKIPJACK_CFB64                    0x00000357UL
#define CKM_SKIPJACK_CFB32                    0x00000358UL
#define CKM_SKIPJACK_CFB16                    0x00000359UL
#define CKM_SKIPJACK_CFB8                     0x0000035AUL
#define CKM_SKIPJACK_WRAP                     0x0000035BUL
#define CKM_SKIPJACK_PRIVATE_WRAP             0x0000035CUL
#define CKM_SKIPJACK_RELAYX                   0x0000035DUL
#define CKM_KEA_KEY_PAIR_GEN                  0x0000035EUL
#define CKM_KEA_KEY_DERIVE                    0x0000035FUL
#define CKM_FORTEZZA_TIMESTAMP                0x00000360UL
#define CKM_BATON_KEY_GEN                     0x00000361UL
#define CKM_BATON_ECB128                      0x00000362UL
#define CKM_BATON_ECB96                       0x00000363UL
#define CKM_BATON_CBC128                      0x00000364UL
#define CKM_BATON_COUNTER                     0x00000365UL
#define CKM_BATON_SHUFFLE                     0x00000366UL
#define CKM_BATON_WRAP                        0x00000367UL
#define CKM_JUNIPER_KEY_GEN                   0x00000368UL
#define CKM_JUNIPER_ECB128                    0x00000369UL
#define CKM_JUNIPER_CBC128                    0x0000036AUL
#define CKM_JUNIPER_COUNTER                   0x0000036BUL
#define CKM_JUNIPER_SHUFFLE                   0x0000036CUL
#define CKM_JUNIPER_WRAP                      0x0000036DUL
#define CKM_FASTHASH                          0x0000036EUL
#endif

#define CKM_VENDOR_DEFINED                    0x80000000UL /*!< Anything >= to this is for vendor specific types */
/** @} */


/**
 * @brief Mechanism object
 */
typedef struct CK_MECHANISM_ {
	CK_MECHANISM_TYPE mechanism; /*!< mechanism type */
	CK_VOID_PTR pParameter; /*!< mechanism parameters */
	CK_ULONG ulParameterLen; /*!< mechanism parameters length in bytes */
} CK_MECHANISM;

typedef CK_MECHANISM* CK_MECHANISM_PTR; /*!< pointer to CK_MECHANISM */


/**
 * @defgroup PKCS11_Mechanism_Flags PKCS#11 mechanism flags
 * @{
 */
#define CKF_HW                 0x00000001UL /*!< Set if the mechanism is performed H/W, else it's software */
#define CKF_MESSAGE_ENCRYPT    0x00000002UL /*!< Set if mechanism supports C_MessageEncryptInit */
#define CKF_MESSAGE_DECRYPT    0x00000004UL /*!< Set if mechanism supports C_MessageDecryptInit */
#define CKF_MESSAGE_SIGN       0x00000008UL /*!< Set if mechanism supports C_MessageSignInit */
#define CKF_MESSAGE_VERIFY     0x00000010UL /*!< Set if mechanism supports C_MessageVerifyInit */
#define CKF_MULTI_MESSAGE      0x00000020UL /*!< Set if mechanism supports C_*MessageBegin. One of CKF_MESSAGE_* flag must also be set */
#define CKF_FIND_OBJECTS       0x00000040UL  /*!< Flag to be used with C_SessionCancel to cancel object search operations */
#define CKF_ENCRYPT            0x00000100UL /*!< Set if mechanism supports C_EncryptInit */
#define CKF_DECRYPT            0x00000200UL /*!< Set if mechanism supports C_DecryptInit */
#define CKF_DIGEST             0x00000400UL /*!< Set if mechanism supports C_DigestInit */
#define CKF_SIGN               0x00000800UL  /*!< Set if mechanism supports C_SignInit */
#define CKF_SIGN_RECOVER       0x00001000UL  /*!< Set if mechanism supports C_SignRecoverInit */
#define CKF_VERIFY             0x00002000UL  /*!< Set if mechanism supports C_VerifyInit */
#define CKF_VERIFY_RECOVER     0x00004000UL  /*!< Set if mechanism supports C_VerifyRecoverInit */
#define CKF_GENERATE           0x00008000UL  /*!< Set if mechanism supports C_GenerateKey */
#define CKF_GENERATE_KEY_PAIR  0x00010000UL  /*!< Set if mechanism supports C_GenerateKeyPair */
#define CKF_WRAP               0x00020000UL  /*!< Set if mechanism supports C_WrapKey */
#define CKF_UNWRAP             0x00040000UL  /*!< Set if mechanism supports C_UnwrapKey */
#define CKF_DERIVE             0x00080000UL  /*!< Set if mechanism supports C_DeriveKey */
#define CKF_EXTENSION          0x80000000UL /*!< Set if there's an extension to the flags, must not be set for 3.0 */
/** @} */

/**
 * @brief Mechanism information
 */
typedef struct CK_MECHANISM_INFO_ {
	CK_ULONG ulMinKeySize; /*!< minimum keysize (bits or bytes, mechanism specific) */
	CK_ULONG ulMaxKeySize; /*!< maximum keysize (bits or bytes, mechanism specific) */
	CK_FLAGS flags; /*!< mechanism flags CKF_* */
} CK_MECHANISM_INFO;

typedef CK_MECHANISM_INFO* CK_MECHANISM_INFO_PTR; /*!< pointer to CK_MECHANISM_INFO */


typedef struct CK_FUNCTION_LIST_ CK_FUNCTION_LIST; /*!< Cryptoki v2.X API definition */
typedef CK_FUNCTION_LIST* CK_FUNCTION_LIST_PTR; /*!< pointer to CK_FUNCTION_LIST */
typedef CK_FUNCTION_LIST_PTR* CK_FUNCTION_LIST_PTR_PTR; /*!< pointer to CK_FUNCTION_LIST_PTR */

typedef struct CK_FUNCTION_LIST_3_0_ CK_FUNCTION_LIST_3_0; /*!< Cryptoki v3.0 API definition */
typedef CK_FUNCTION_LIST_3_0* CK_FUNCTION_LIST_3_0_PTR; /*!< pointer to CK_FUNCTION_LIST_3_0 */
typedef CK_FUNCTION_LIST_3_0_PTR* CK_FUNCTION_LIST_3_0_PTR_PTR; /*!< pointer to CK_FUNCTION_LIST_3_0_PTR */


/**
 * @defgroup PKCS11_Interface_Flags PKCS#11 Library interface flags
 * @{
 */
#define CKF_INTERFACE_FORK_SAFE  0x00000001UL /*!< The library supports forking which will duplicate all objects */
/** @} */

/**
 * @brief Interface information
 */
typedef struct CK_INTERFACE_ {
	CK_UTF8CHAR_PTR pInterfaceName; /*!< Interface name */
	CK_VOID_PTR     pFunctionList; /*!< Pointer to the API's CK_FUNCTION_LIST* object */
	CK_FLAGS        flags; /*!< Interface flags */
} CK_INTERFACE;

typedef CK_INTERFACE* CK_INTERFACE_PTR; /*!< pointer to CK_INTERFACE */
typedef CK_INTERFACE_PTR* CK_INTERFACE_PTR_PTR; /*!< pointer to CK_INTERFACE_PTR */


#endif /* QNX_PKCS11_PKCS11TYPES_H_INCLUDED */
