/*
 * Copyright (c) 2022-2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/**
 * @file pkcs11api.h
 *
 * @brief PKCS#11 API Functions
 *
 * These functions were derived from the spec: https://docs.oasis-open.org/pkcs11/pkcs11-base/v3.0/csprd01/pkcs11-base-v3.0-csprd01.html
 */

#ifndef QNX_PKCS11_PKCS11API_H_INCLUDED
#define QNX_PKCS11_PKCS11API_H_INCLUDED

#ifndef QNX_PKCS11_PKCS11_H_INCLUDED
#error "This header can only be loaded from pkcs11.h"
#endif

#define CK_DECLARE_FUNCTION(name, args) \
typedef CK_RV (*CK_ ## name) args; \
CK_RV name args

/** Library Initialization */
CK_DECLARE_FUNCTION(C_Initialize,(CK_VOID_PTR pInitArgs));
/** Library Un-initialization */
CK_DECLARE_FUNCTION(C_Finalize,(CK_VOID_PTR pReserved));
/** Retrieve library/module information */
CK_DECLARE_FUNCTION(C_GetInfo,(CK_INFO_PTR pInfo));
/** Retrieve interface API functions */
CK_DECLARE_FUNCTION(C_GetFunctionList,(CK_FUNCTION_LIST_PTR_PTR ppFunctionList));
/** Enumerate the available slots */
CK_DECLARE_FUNCTION(C_GetSlotList,(CK_BBOOL tokenPresent, CK_SLOT_ID_PTR pSlotList, CK_ULONG_PTR pulCount));
/** Retrieve specific slot information */
CK_DECLARE_FUNCTION(C_GetSlotInfo,(CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo));
/** Retrieve token information in specific slot */
CK_DECLARE_FUNCTION(C_GetTokenInfo,(CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo));
/** Retrieve list of support mechanisms by the token in the specified slot */
CK_DECLARE_FUNCTION(C_GetMechanismList,(CK_SLOT_ID slotID, CK_MECHANISM_TYPE_PTR pMechanismList, CK_ULONG_PTR pulCount));
/** Retrieve information about a particular mechanism */
CK_DECLARE_FUNCTION(C_GetMechanismInfo,(CK_SLOT_ID slotID, CK_MECHANISM_TYPE type, CK_MECHANISM_INFO_PTR pInfo));
/** Initialize the token H/W with specific parameters */
CK_DECLARE_FUNCTION(C_InitToken,(CK_SLOT_ID slotID, CK_CHAR_PTR pPin, CK_ULONG ulPinLen, CK_CHAR_PTR pLabel));
/** Initialize normal user's PIN */
CK_DECLARE_FUNCTION(C_InitPIN,(CK_SESSION_HANDLE hSession, CK_CHAR_PTR pPin, CK_ULONG ulPinLen));
/** Modify pin of current user */
CK_DECLARE_FUNCTION(C_SetPIN,(CK_SESSION_HANDLE hSession, CK_CHAR_PTR pOldPin, CK_ULONG ulOldLen, CK_CHAR_PTR pNewPin,
	CK_ULONG ulNewLen));
/** Opens an active session with a particular token */
CK_DECLARE_FUNCTION(C_OpenSession,(CK_SLOT_ID slotID, CK_FLAGS flags, CK_VOID_PTR pApplication, CK_NOTIFY Notify,
	CK_SESSION_HANDLE_PTR phSession));
/** Closes a session with a token */
CK_DECLARE_FUNCTION(C_CloseSession,(CK_SESSION_HANDLE hSession));
/** Closes all open sessions with a token */
CK_DECLARE_FUNCTION(C_CloseAllSessions,(CK_SLOT_ID slotID));
/** Retrieve session information */
CK_DECLARE_FUNCTION(C_GetSessionInfo,(CK_SESSION_HANDLE hSession, CK_SESSION_INFO_PTR pInfo));
/** Retrieve crypto operations state of a session (so you can resume later) */
CK_DECLARE_FUNCTION(C_GetOperationState,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pOperationState,
	CK_ULONG_PTR pulOperationStateLen));
/** Sets the crypto operations state of a session (so you can resume now) */
CK_DECLARE_FUNCTION(C_SetOperationState,(CK_SESSION_HANDLE hSession,CK_BYTE_PTR pOperationState,
	CK_ULONG ulOperationStateLen, CK_OBJECT_HANDLE hEncryptionKey, CK_OBJECT_HANDLE hAuthenticationKey));
/** Log into the token */
CK_DECLARE_FUNCTION(C_Login,(CK_SESSION_HANDLE hSession, CK_USER_TYPE userType, CK_CHAR_PTR pPin, CK_ULONG ulPinLen));
/** Log out of token */
CK_DECLARE_FUNCTION(C_Logout,(CK_SESSION_HANDLE hSession));
/** Creates a token object */
CK_DECLARE_FUNCTION(C_CreateObject,(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount,
	CK_OBJECT_HANDLE_PTR phObject));
/** Copies an object */
CK_DECLARE_FUNCTION(C_CopyObject,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate,
	CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phNewObject));
/** Destroys an object */
CK_DECLARE_FUNCTION(C_DestroyObject,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject));
/** Retrieves the object's size */
CK_DECLARE_FUNCTION(C_GetObjectSize,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ULONG_PTR pulSize));
/** Retrieves an object's attribute value */
CK_DECLARE_FUNCTION(C_GetAttributeValue,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject,
	CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount));
/** Sets an object's attribute value */
CK_DECLARE_FUNCTION(C_SetAttributeValue,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject,
	CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount));
/** Initializes an object search */
CK_DECLARE_FUNCTION(C_FindObjectsInit,(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount));
/** Executes an object search */
CK_DECLARE_FUNCTION(C_FindObjects,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount,
	CK_ULONG_PTR pulObjectCount));
/** Terminates an object search */
CK_DECLARE_FUNCTION(C_FindObjectsFinal,(CK_SESSION_HANDLE hSession));
/** Initializes a multi part encryption operation */
CK_DECLARE_FUNCTION(C_EncryptInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot encryption */
CK_DECLARE_FUNCTION(C_Encrypt,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen,
	CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen));
/** Encrypts a portion of the plaintext */
CK_DECLARE_FUNCTION(C_EncryptUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen,
	CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen));
/** Terminates a multi part encryption operation */
CK_DECLARE_FUNCTION(C_EncryptFinal,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pLastEncryptedPart,
	CK_ULONG_PTR pulLastEncryptedPartLen));
/** Initializes a multi part decryption operation */
CK_DECLARE_FUNCTION(C_DecryptInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot decryption */
CK_DECLARE_FUNCTION(C_Decrypt,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedData, CK_ULONG ulEncryptedDataLen,
	CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen));
/** Decrypts a portion of the ciphertext */
CK_DECLARE_FUNCTION(C_DecryptUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen,
	CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen));
/** Terminates a multi part decryption operation */
CK_DECLARE_FUNCTION(C_DecryptFinal,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pLastPart, CK_ULONG_PTR pulLastPartLen));
/** Initializes a multi part digest operation */
CK_DECLARE_FUNCTION(C_DigestInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism));
/** One shot digest */
CK_DECLARE_FUNCTION(C_Digest,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pDigest,
	CK_ULONG_PTR pulDigestLen));
/** Digests a portion of the input */
CK_DECLARE_FUNCTION(C_DigestUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen));
/** One shot digest of a key */
CK_DECLARE_FUNCTION(C_DigestKey,(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hKey));
/** Terminates a multi part digest operation */
CK_DECLARE_FUNCTION(C_DigestFinal,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen));
/** Initializes a multi part signing operation */
CK_DECLARE_FUNCTION(C_SignInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot signing */
CK_DECLARE_FUNCTION(C_Sign,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature,
	CK_ULONG_PTR pulSignatureLen));
/** Updates signature with a portion of the input */
CK_DECLARE_FUNCTION(C_SignUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen));
/** Terminates a multi part signing operation */
CK_DECLARE_FUNCTION(C_SignFinal,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen));
/** Initializes a signing operation with data recovery */
CK_DECLARE_FUNCTION(C_SignRecoverInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot signing with data recovery */
CK_DECLARE_FUNCTION(C_SignRecover,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen,
	CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen));
/** Initializes a multi part signature verification operation */
CK_DECLARE_FUNCTION(C_VerifyInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot signature verification */
CK_DECLARE_FUNCTION(C_Verify,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature,
	CK_ULONG ulSignatureLen));
/** Updates signature verification with a portion of the input */
CK_DECLARE_FUNCTION(C_VerifyUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen));
/** Terminates a multi part signature verification operation */
CK_DECLARE_FUNCTION(C_VerifyFinal,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen));
/** Initializes a signature verification operation with data recovery */
CK_DECLARE_FUNCTION(C_VerifyRecoverInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot signature verification with data recovery */
CK_DECLARE_FUNCTION(C_VerifyRecover,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen,
	CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen));
/** Digests and encrypts a portion of the plaintext for dual purpose algorithm */
CK_DECLARE_FUNCTION(C_DigestEncryptUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen,
	CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen));
/** Decrypts and digests a portion of the ciphertext for dual purpose algorithm */
CK_DECLARE_FUNCTION(C_DecryptDigestUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedPart,
	CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen));
/** Continues a multi part signing and encryption dual purpose algorithm */
CK_DECLARE_FUNCTION(C_SignEncryptUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen,
	CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen));
/** Continues a multi part signature verification and decryption dual purpose algorithm */
CK_DECLARE_FUNCTION(C_DecryptVerifyUpdate,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedPart,
	CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen));
/** Generate a secret key */
CK_DECLARE_FUNCTION(C_GenerateKey,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pTemplate,
	CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phKey));
/** Generates a key pair */
CK_DECLARE_FUNCTION(C_GenerateKeyPair,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism,
	CK_ATTRIBUTE_PTR pPublicKeyTemplate, CK_ULONG ulPublicKeyAttributeCount, CK_ATTRIBUTE_PTR pPrivateKeyTemplate,
	CK_ULONG ulPrivateKeyAttributeCount, CK_OBJECT_HANDLE_PTR phPrivateKey, CK_OBJECT_HANDLE_PTR phPublicKey));
/** Wraps a key (encrypted) */
CK_DECLARE_FUNCTION(C_WrapKey,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hWrappingKey,
	CK_OBJECT_HANDLE hKey, CK_BYTE_PTR pWrappedKey, CK_ULONG_PTR pulWrappedKeyLen));
/** Unwraps a key (decrypted) */
CK_DECLARE_FUNCTION(C_UnwrapKey,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism,
	CK_OBJECT_HANDLE hUnwrappingKey, CK_BYTE_PTR pWrappedKey, CK_ULONG ulWrappedKeyLen, CK_ATTRIBUTE_PTR pTemplate,
	CK_ULONG ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey));
/** Derives a key from another secret */
CK_DECLARE_FUNCTION(C_DeriveKey,(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hBaseKey,
	CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey));
/** Seeds a random generator algorithm */
CK_DECLARE_FUNCTION(C_SeedRandom,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSeed, CK_ULONG ulSeedLen));
/** Generates random data */
CK_DECLARE_FUNCTION(C_GenerateRandom,(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pRandomData, CK_ULONG ulRandomLen));
/** Legacy unused function, always returns CKR_FUNCTION_NOT_PARALLEL */
CK_DECLARE_FUNCTION(C_GetFunctionStatus,(CK_SESSION_HANDLE hSession));
/** Legacy unused function, always returns CKR_FUNCTION_NOT_PARALLEL */
CK_DECLARE_FUNCTION(C_CancelFunction,(CK_SESSION_HANDLE hSession));
/** Waits for a slot event (token removed, etc.) */
CK_DECLARE_FUNCTION(C_WaitForSlotEvent,(CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pReserved));
/** Retrieve interface listing of all supported APIs */
CK_DECLARE_FUNCTION(C_GetInterfaceList,(CK_INTERFACE *pInterfaceList, CK_ULONG *pulCount));
/** Retrieve a particular interface matching criteria */
CK_DECLARE_FUNCTION(C_GetInterface,(CK_UTF8CHAR *pInterfaceName, CK_VERSION *pVersion, CK_INTERFACE **ppInterface,
	CK_FLAGS flags));
/** Login a particular user */
CK_DECLARE_FUNCTION(C_LoginUser,(CK_SESSION_HANDLE hSession, CK_USER_TYPE userType, CK_UTF8CHAR *pPin,
	CK_ULONG ulPinLen, CK_UTF8CHAR *pUsername, CK_ULONG ulUsernameLen));
/** Terminates active session operations */
CK_DECLARE_FUNCTION(C_SessionCancel,(CK_SESSION_HANDLE hSession, CK_FLAGS flags));
/** Initializes a message based encryption operation */
CK_DECLARE_FUNCTION(C_MessageEncryptInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM *pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot message encryption */
CK_DECLARE_FUNCTION(C_EncryptMessage,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pAssociatedData, CK_ULONG ulAssociatedDataLen, CK_BYTE *pPlaintext, CK_ULONG ulPlaintextLen,
	CK_BYTE *pCiphertext, CK_ULONG *pulCiphertextLen));
/** Initializes a multi-part message encryption operation */
CK_DECLARE_FUNCTION(C_EncryptMessageBegin,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pAssociatedData, CK_ULONG ulAssociatedDataLen));
/** Continues or terminates a multi-part message encryption operation */
CK_DECLARE_FUNCTION(C_EncryptMessageNext,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pPlaintextPart, CK_ULONG ulPlaintextPartLen, CK_BYTE *pCiphertextPart, CK_ULONG *pulCiphertextPartLen,
	CK_ULONG flags));
/** Terminates a message based encryption operation */
CK_DECLARE_FUNCTION(C_MessageEncryptFinal,(CK_SESSION_HANDLE hSession));
/** Initializes a message based decryption operation */
CK_DECLARE_FUNCTION(C_MessageDecryptInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM *pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot message decryption */
CK_DECLARE_FUNCTION(C_DecryptMessage,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pAssociatedData, CK_ULONG ulAssociatedDataLen, CK_BYTE *pCiphertext, CK_ULONG ulCiphertextLen,
	CK_BYTE *pPlaintext, CK_ULONG *pulPlaintextLen));
/** Initializes a multi-part message decryption operation */
CK_DECLARE_FUNCTION(C_DecryptMessageBegin,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pAssociatedData, CK_ULONG ulAssociatedDataLen));
/** Continues or terminates a multi-part message decryption operation */
CK_DECLARE_FUNCTION(C_DecryptMessageNext,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pCiphertextPart, CK_ULONG ulCiphertextPartLen, CK_BYTE *pPlaintextPart, CK_ULONG *pulPlaintextPartLen,
	CK_FLAGS flags));
/** Terminates a message based decryption operation */
CK_DECLARE_FUNCTION(C_MessageDecryptFinal,(CK_SESSION_HANDLE hSession));
/** Initializes a message based signature operation */
CK_DECLARE_FUNCTION(C_MessageSignInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM *pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot message signature */
CK_DECLARE_FUNCTION(C_SignMessage,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pData, CK_ULONG ulDataLen, CK_BYTE *pSignature, CK_ULONG *pulSignatureLen));
/** Initializes a multi-part message signature operation */
CK_DECLARE_FUNCTION(C_SignMessageBegin,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen));
/** Continues or terminates a multi-part message signature operation */
CK_DECLARE_FUNCTION(C_SignMessageNext,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pDataPart, CK_ULONG ulDataPartLen, CK_BYTE *pSignature, CK_ULONG *pulSignatureLen));
/** Termiinates a message based signature operation */
CK_DECLARE_FUNCTION(C_MessageSignFinal,(CK_SESSION_HANDLE hSession));
/** Initializes a message based signature verification operation */
CK_DECLARE_FUNCTION(C_MessageVerifyInit,(CK_SESSION_HANDLE hSession, CK_MECHANISM *pMechanism, CK_OBJECT_HANDLE hKey));
/** One shot message signature verification */
CK_DECLARE_FUNCTION(C_VerifyMessage,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pData, CK_ULONG ulDataLen, CK_BYTE *pSignature, CK_ULONG ulSignatureLen));
/** Initializes a multi-part message signature verification operation */
CK_DECLARE_FUNCTION(C_VerifyMessageBegin,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen));
/** Continues or terminates a multi-part message signature verification operation */
CK_DECLARE_FUNCTION(C_VerifyMessageNext,(CK_SESSION_HANDLE hSession, CK_VOID_PTR pParameter, CK_ULONG ulParameterLen,
	CK_BYTE *pDataPart, CK_ULONG ulDataPartLen, CK_BYTE *pSignature, CK_ULONG ulSignatureLen));
/** Termiinates a message based signature verification operation */
CK_DECLARE_FUNCTION(C_MessageVerifyFinal,(CK_SESSION_HANDLE hSession));

/**
 * @brief Cryptoki version 2.X API functions
 */
struct CK_FUNCTION_LIST_
{
    CK_VERSION version; /*!< API version */
    CK_C_Initialize C_Initialize; /*!< Library Initialization */
    CK_C_Finalize C_Finalize; /*!< Library Un-initialization */
    CK_C_GetInfo C_GetInfo; /*!< Retrieve library/module information */
    CK_C_GetFunctionList C_GetFunctionList; /*!< Retrieve interface API functions */
    CK_C_GetSlotList C_GetSlotList; /*!< Enumerate the available slots */
    CK_C_GetSlotInfo C_GetSlotInfo; /*!< Retrieve information about a slot */
    CK_C_GetTokenInfo C_GetTokenInfo; /*<! Retrieve information about a token inserted in a slot */
    CK_C_GetMechanismList C_GetMechanismList; /** Retrieve list of support mechanisms by the token in the specified slot */
    CK_C_GetMechanismInfo C_GetMechanismInfo; /** Retrieve information about a particular mechanism */
    CK_C_InitToken C_InitToken; /** Initialize the token H/W with specific parameters */
    CK_C_InitPIN C_InitPIN; /** Initialize normal user's PIN */
    CK_C_SetPIN C_SetPIN; /** Modify pin of current user */
    CK_C_OpenSession C_OpenSession; /** Opens an active session with a particular token */
    CK_C_CloseSession C_CloseSession; /** Closes a session with a token */
    CK_C_CloseAllSessions C_CloseAllSessions; /** Closes all open sessions with a token */
    CK_C_GetSessionInfo C_GetSessionInfo; /** Retrieve session information */
    CK_C_GetOperationState C_GetOperationState; /** Retrieve crypto operations state of a session (so you can resume later) */
    CK_C_SetOperationState C_SetOperationState; /** Sets the crypto operations state of a session (so you can resume now) */
    CK_C_Login C_Login; /** Log into the token */
    CK_C_Logout C_Logout; /** Log out of token */
    CK_C_CreateObject C_CreateObject; /** Creates a token object */
    CK_C_CopyObject C_CopyObject; /** Copies an object */
    CK_C_DestroyObject C_DestroyObject; /** Destroys an object */
    CK_C_GetObjectSize C_GetObjectSize; /** Retrieves the object's size */
    CK_C_GetAttributeValue C_GetAttributeValue; /** Retrieves an object's attribute value */
    CK_C_SetAttributeValue C_SetAttributeValue; /** Sets an object's attribute value */
    CK_C_FindObjectsInit C_FindObjectsInit; /** Initializes an object search */
    CK_C_FindObjects C_FindObjects; /** Executes an object search */
    CK_C_FindObjectsFinal C_FindObjectsFinal; /** Terminates an object search */
    CK_C_EncryptInit C_EncryptInit; /** Initializes a multi part encryption operation */
    CK_C_Encrypt C_Encrypt; /** One shot encryption */
    CK_C_EncryptUpdate C_EncryptUpdate; /** Encrypts a portion of the plaintext */
    CK_C_EncryptFinal C_EncryptFinal; /** Terminates a multi part encryption operation */
    CK_C_DecryptInit C_DecryptInit; /** Initializes a multi part decryption operation */
    CK_C_Decrypt C_Decrypt; /** One shot decryption */
    CK_C_DecryptUpdate C_DecryptUpdate; /** Decrypts a portion of the ciphertext */
    CK_C_DecryptFinal C_DecryptFinal; /** Terminates a multi part decryption operation */
    CK_C_DigestInit C_DigestInit; /** Initializes a multi part digest operation */
    CK_C_Digest C_Digest; /** One shot digest */
    CK_C_DigestUpdate C_DigestUpdate; /** Digests a portion of the input */
    CK_C_DigestKey C_DigestKey; /** One shot digest of a key */
    CK_C_DigestFinal C_DigestFinal; /** Terminates a multi part digest operation */
    CK_C_SignInit C_SignInit; /** Initializes a multi part signing operation */
    CK_C_Sign C_Sign; /** One shot signing */
    CK_C_SignUpdate C_SignUpdate; /** Updates signature with a portion of the input */
    CK_C_SignFinal C_SignFinal; /** Terminates a multi part signing operation */
    CK_C_SignRecoverInit C_SignRecoverInit; /** Initializes a signing operation with data recovery */
    CK_C_SignRecover C_SignRecover; /** One shot signing with data recovery */
    CK_C_VerifyInit C_VerifyInit; /** Initializes a multi part signature verification operation */
    CK_C_Verify C_Verify; /** One shot signature verification */
    CK_C_VerifyUpdate C_VerifyUpdate; /** Updates signature verification with a portion of the input */
    CK_C_VerifyFinal C_VerifyFinal; /** Terminates a multi part signature verification operation */
    CK_C_VerifyRecoverInit C_VerifyRecoverInit; /** Initializes a signature verification operation with data recovery */
    CK_C_VerifyRecover C_VerifyRecover; /** One shot signature verification with data recovery */
    CK_C_DigestEncryptUpdate C_DigestEncryptUpdate; /** Digests and encrypts a portion of the plaintext for dual purpose algorithm */
    CK_C_DecryptDigestUpdate C_DecryptDigestUpdate; /** Decrypts and digests a portion of the ciphertext for dual purpose algorithm */
    CK_C_SignEncryptUpdate C_SignEncryptUpdate; /** Continues a multi part signing and encryption dual purpose algorithm */
    CK_C_DecryptVerifyUpdate C_DecryptVerifyUpdate; /** Continues a multi part signature verification and decryption dual purpose algorithm */
    CK_C_GenerateKey C_GenerateKey; /** Generate a secret key */
    CK_C_GenerateKeyPair C_GenerateKeyPair; /** Generates a key pair */
    CK_C_WrapKey C_WrapKey; /** Wraps a key (encrypted) */
    CK_C_UnwrapKey C_UnwrapKey; /** Unwraps a key (decrypted) */
    CK_C_DeriveKey C_DeriveKey; /** Derives a key from another secret */
    CK_C_SeedRandom C_SeedRandom; /** Seeds a random generator algorithm */
    CK_C_GenerateRandom C_GenerateRandom; /** Generates random data */
    CK_C_GetFunctionStatus C_GetFunctionStatus; /** Legacy unused function, always returns CKR_FUNCTION_NOT_PARALLEL */
    CK_C_CancelFunction C_CancelFunction; /** Legacy unused function, always returns CKR_FUNCTION_NOT_PARALLEL */
    CK_C_WaitForSlotEvent C_WaitForSlotEvent; /** Waits for a slot event (token removed, etc.) */
};

/**
 * @brief Cryptoki version 3.0 API functions
 */
struct CK_FUNCTION_LIST_3_0_ {
	/* First grouping is < 3.0 API */
	CK_VERSION version; /*!< API version */
	CK_C_Initialize C_Initialize; /*!< Library Initialization */
	CK_C_Finalize C_Finalize; /*!< Library Un-initialization */
	CK_C_GetInfo C_GetInfo; /*!< Retrieve library/module information */
	CK_C_GetFunctionList C_GetFunctionList; /*!< Retrieve interface API functions */
	CK_C_GetSlotList C_GetSlotList; /*!< Enumerate the available slots */
	CK_C_GetSlotInfo C_GetSlotInfo; /*!< Retrieve information about a slot */
	CK_C_GetTokenInfo C_GetTokenInfo; /*<! Retrieve information about a token inserted in a slot */
	CK_C_GetMechanismList C_GetMechanismList; /** Retrieve list of support mechanisms by the token in the specified slot */
	CK_C_GetMechanismInfo C_GetMechanismInfo; /** Retrieve information about a particular mechanism */
	CK_C_InitToken C_InitToken; /** Initialize the token H/W with specific parameters */
	CK_C_InitPIN C_InitPIN; /** Initialize normal user's PIN */
	CK_C_SetPIN C_SetPIN; /** Modify pin of current user */
	CK_C_OpenSession C_OpenSession; /** Opens an active session with a particular token */
	CK_C_CloseSession C_CloseSession; /** Closes a session with a token */
	CK_C_CloseAllSessions C_CloseAllSessions; /** Closes all open sessions with a token */
	CK_C_GetSessionInfo C_GetSessionInfo; /** Retrieve session information */
	CK_C_GetOperationState C_GetOperationState; /** Retrieve crypto operations state of a session (so you can resume later) */
	CK_C_SetOperationState C_SetOperationState; /** Sets the crypto operations state of a session (so you can resume now) */
	CK_C_Login C_Login; /** Log into the token */
	CK_C_Logout C_Logout; /** Log out of token */
	CK_C_CreateObject C_CreateObject; /** Creates a token object */
	CK_C_CopyObject C_CopyObject; /** Copies an object */
	CK_C_DestroyObject C_DestroyObject; /** Destroys an object */
	CK_C_GetObjectSize C_GetObjectSize; /** Retrieves the object's size */
	CK_C_GetAttributeValue C_GetAttributeValue; /** Retrieves an object's attribute value */
	CK_C_SetAttributeValue C_SetAttributeValue; /** Sets an object's attribute value */
	CK_C_FindObjectsInit C_FindObjectsInit; /** Initializes an object search */
	CK_C_FindObjects C_FindObjects; /** Executes an object search */
	CK_C_FindObjectsFinal C_FindObjectsFinal; /** Terminates an object search */
	CK_C_EncryptInit C_EncryptInit; /** Initializes a multi part encryption operation */
	CK_C_Encrypt C_Encrypt; /** One shot encryption */
	CK_C_EncryptUpdate C_EncryptUpdate; /** Encrypts a portion of the plaintext */
	CK_C_EncryptFinal C_EncryptFinal; /** Terminates a multi part encryption operation */
	CK_C_DecryptInit C_DecryptInit; /** Initializes a multi part decryption operation */
	CK_C_Decrypt C_Decrypt; /** One shot decryption */
	CK_C_DecryptUpdate C_DecryptUpdate; /** Decrypts a portion of the ciphertext */
	CK_C_DecryptFinal C_DecryptFinal; /** Terminates a multi part decryption operation */
	CK_C_DigestInit C_DigestInit; /** Initializes a multi part digest operation */
	CK_C_Digest C_Digest; /** One shot digest */
	CK_C_DigestUpdate C_DigestUpdate; /** Digests a portion of the input */
	CK_C_DigestKey C_DigestKey; /** One shot digest of a key */
	CK_C_DigestFinal C_DigestFinal; /** Terminates a multi part digest operation */
	CK_C_SignInit C_SignInit; /** Initializes a multi part signing operation */
	CK_C_Sign C_Sign; /** One shot signing */
	CK_C_SignUpdate C_SignUpdate; /** Updates signature with a portion of the input */
	CK_C_SignFinal C_SignFinal; /** Terminates a multi part signing operation */
	CK_C_SignRecoverInit C_SignRecoverInit; /** Initializes a signing operation with data recovery */
	CK_C_SignRecover C_SignRecover; /** One shot signing with data recovery */
	CK_C_VerifyInit C_VerifyInit; /** Initializes a multi part signature verification operation */
	CK_C_Verify C_Verify; /** One shot signature verification */
	CK_C_VerifyUpdate C_VerifyUpdate; /** Updates signature verification with a portion of the input */
	CK_C_VerifyFinal C_VerifyFinal; /** Terminates a multi part signature verification operation */
	CK_C_VerifyRecoverInit C_VerifyRecoverInit; /** Initializes a signature verification operation with data recovery */
	CK_C_VerifyRecover C_VerifyRecover; /** One shot signature verification with data recovery */
	CK_C_DigestEncryptUpdate C_DigestEncryptUpdate; /** Digests and encrypts a portion of the plaintext for dual purpose algorithm */
	CK_C_DecryptDigestUpdate C_DecryptDigestUpdate; /** Decrypts and digests a portion of the ciphertext for dual purpose algorithm */
	CK_C_SignEncryptUpdate C_SignEncryptUpdate; /** Continues a multi part signing and encryption dual purpose algorithm */
	CK_C_DecryptVerifyUpdate C_DecryptVerifyUpdate; /** Continues a multi part signature verification and decryption dual purpose algorithm */
	CK_C_GenerateKey C_GenerateKey; /** Generate a secret key */
	CK_C_GenerateKeyPair C_GenerateKeyPair; /** Generates a key pair */
	CK_C_WrapKey C_WrapKey; /** Wraps a key (encrypted) */
	CK_C_UnwrapKey C_UnwrapKey; /** Unwraps a key (decrypted) */
	CK_C_DeriveKey C_DeriveKey; /** Derives a key from another secret */
	CK_C_SeedRandom C_SeedRandom; /** Seeds a random generator algorithm */
	CK_C_GenerateRandom C_GenerateRandom; /** Generates random data */
	CK_C_GetFunctionStatus C_GetFunctionStatus; /** Legacy unused function, always returns CKR_FUNCTION_NOT_PARALLEL */
	CK_C_CancelFunction C_CancelFunction; /** Legacy unused function, always returns CKR_FUNCTION_NOT_PARALLEL */
	CK_C_WaitForSlotEvent C_WaitForSlotEvent; /** Waits for a slot event (token removed, etc.) */

	/* 3.0 additional APIs */
	CK_C_GetInterfaceList C_GetInterfaceList; /** Retrieve interface listing of all supported APIs */
	CK_C_GetInterface C_GetInterface; /** Retrieve a particular interface matching criteria */
	CK_C_LoginUser C_LoginUser; /** Login a particular user */
	CK_C_SessionCancel C_SessionCancel; /** Terminates active session operations */
	CK_C_MessageEncryptInit C_MessageEncryptInit; /** Initializes a message based encryption operation */
	CK_C_EncryptMessage C_EncryptMessage; /** One shot message encryption */
	CK_C_EncryptMessageBegin C_EncryptMessageBegin; /** Initializes a multi-part message encryption operation */
	CK_C_EncryptMessageNext C_EncryptMessageNext; /** Continues or terminates a multi-part message encryption operation */
	CK_C_MessageEncryptFinal C_MessageEncryptFinal; /** Terminates a message based encryption operation */
	CK_C_MessageDecryptInit C_MessageDecryptInit; /** Initializes a message based decryption operation */
	CK_C_DecryptMessage C_DecryptMessage; /** One shot message decryption */
	CK_C_DecryptMessageBegin C_DecryptMessageBegin; /** Initializes a multi-part message decryption operation */
	CK_C_DecryptMessageNext C_DecryptMessageNext; /** Continues or terminates a multi-part message decryption operation */
	CK_C_MessageDecryptFinal C_MessageDecryptFinal; /** Terminates a message based decryption operation */
	CK_C_MessageSignInit C_MessageSignInit; /** Initializes a message based signature operation */
	CK_C_SignMessage C_SignMessage; /** One shot message signature */
	CK_C_SignMessageBegin C_SignMessageBegin; /** Initializes a multi-part message signature operation */
	CK_C_SignMessageNext C_SignMessageNext; /** Continues or terminates a multi-part message signature operation */
	CK_C_MessageSignFinal C_MessageSignFinal; /** Termiinates a message based signature operation */
	CK_C_MessageVerifyInit C_MessageVerifyInit; /** Initializes a message based signature verification operation */
	CK_C_VerifyMessage C_VerifyMessage; /** One shot message signature verification */
	CK_C_VerifyMessageBegin C_VerifyMessageBegin; /** Initializes a multi-part message signature verification operation */
	CK_C_VerifyMessageNext C_VerifyMessageNext; /** Continues or terminates a multi-part message signature verification operation */
	CK_C_MessageVerifyFinal C_MessageVerifyFinal; /** Termiinates a message based signature verification operation */
};

#endif /* QNX_PKCS11_PKCS11API_H_INCLUDED */
