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
 * @file pkcs11mechanisms.h
 *
 * @brief PKCS#11 Mechanism Specific Types
 *
 * These types were derived from the spec: https://docs.oasis-open.org/pkcs11/pkcs11-base/v3.0/csprd01/pkcs11-base-v3.0-csprd01.html
 * Algorithms (Mechanisms) are defined in https://docs.oasis-open.org/pkcs11/pkcs11-curr/v3.0/pkcs11-curr-v3.0.html
 */

#ifndef QNX_PKCS11_PKCS11MECHANISMS_H_INCLUDED
#define QNX_PKCS11_PKCS11MECHANISMS_H_INCLUDED

#ifndef QNX_PKCS11_PKCS11_H_INCLUDED
#error "This header can only be loaded from pkcs11.h"
#endif

/* General */

/**
 * @defgroup PKCS11_KDF PKCS#11 Key Derivation Function Types
 * @{
 */
#define CKD_NULL                  0x00000000UL
#define CKD_SHA1_KDF              0x00000001UL
#define CKD_SHA224_KDF            0x00000002UL
#define CKD_SHA256_KDF            0x00000003UL
#define CKD_SHA384_KDF            0x00000004UL
#define CKD_SHA512_KDF            0x00000005UL
#define CKD_SHA3_224_KDF          0x00000006UL
#define CKD_SHA3_256_KDF          0x00000007UL
#define CKD_SHA3_384_KDF          0x00000008UL
#define CKD_SHA3_512_KDF          0x00000009UL
#define CKD_SHA1_KDF_SP800        0x0000000AUL
#define CKD_SHA224_KDF_SP800      0x0000000BUL
#define CKD_SHA256_KDF_SP800      0x0000000CUL
#define CKD_SHA384_KDF_SP800      0x0000000DUL
#define CKD_SHA512_KDF_SP800      0x0000000EUL
#define CKD_SHA3_224_KDF_SP800    0x0000000FUL
#define CKD_SHA3_256_KDF_SP800    0x00000010UL
#define CKD_SHA3_384_KDF_SP800    0x00000011UL
#define CKD_SHA3_512_KDF_SP800    0x00000012UL
#define CKD_BLAKE2B_160_KDF       0x00000013UL
#define CKD_BLAKE2B_256_KDF       0x00000014UL
#define CKD_BLAKE2B_384_KDF       0x00000015UL
#define CKD_BLAKE2B_512_KDF       0x00000016UL
#define CKD_SHA1_KDF_ASN1         0x00000017UL
#define CKD_SHA1_KDF_CONCATENATE  0x00000018UL
/** @} */

/* RSA */

typedef CK_ULONG CK_RSA_PKCS_MGF_TYPE; /*!< RSA OAEP or PKCS#1 PSS Message Generation Function (MGF) */
typedef CK_RSA_PKCS_MGF_TYPE* CK_RSA_PKCS_MGF_TYPE_PTR; /*!< pointer to CK_RSA_PKCS_MGF_TYPE */

/**
 * @defgroup PKCS11_RSA_MGF PKCS#11 RSA Message Generation Function Types
 * @{
 */
#define CKG_MGF1_SHA1      0x00000001UL
#define CKG_MGF1_SHA224    0x00000005UL
#define CKG_MGF1_SHA256    0x00000002UL
#define CKG_MGF1_SHA384    0x00000003UL
#define CKG_MGF1_SHA512    0x00000004UL
#define CKG_MGF1_SHA3_224  0x00000006UL
#define CKG_MGF1_SHA3_256  0x00000007UL
#define CKG_MGF1_SHA3_384  0x00000008UL
#define CKG_MGF1_SHA3_512  0x00000009UL
/** @} */

typedef CK_ULONG CK_RSA_PKCS_OAEP_SOURCE_TYPE;
typedef CK_RSA_PKCS_OAEP_SOURCE_TYPE* CK_RSA_PKCS_OAEP_SOURCE_TYPE_PTR; /*!< pointer to CK_RSA_PKCS_OAEP_SOURCE_TYPE */


/**
 * @defgroup PKCS11_RSA_OAEP_Source_Type PKCS#11 RSA OAEP Source Types
 * @{
 */
#define CKZ_DATA_SPECIFIED 0x00000001UL
/** @} */

/**
 * @brief RSA OAEP Parameters
 */
typedef struct CK_RSA_PKCS_OAEP_PARAMS_ {
	CK_MECHANISM_TYPE             hashAlg;
	CK_RSA_PKCS_MGF_TYPE          mgf;
	CK_RSA_PKCS_OAEP_SOURCE_TYPE  source;
	CK_VOID_PTR                   pSourceData;
	CK_ULONG                      ulSourceDataLen;
} CK_RSA_PKCS_OAEP_PARAMS;

typedef CK_RSA_PKCS_OAEP_PARAMS* CK_RSA_PKCS_OAEP_PARAMS_PTR; /*!< pointer to CK_RSA_PKCS_OAEP_PARAMS */


/**
 * @brief RSA PKCS PSS Parameters
 */
typedef struct CK_RSA_PKCS_PSS_PARAMS_ {
	CK_MECHANISM_TYPE     hashAlg;
	CK_RSA_PKCS_MGF_TYPE  mgf;
	CK_ULONG              sLen;
} CK_RSA_PKCS_PSS_PARAMS;

typedef CK_RSA_PKCS_PSS_PARAMS* CK_RSA_PKCS_PSS_PARAMS_PTR; /*!< pointer to CK_RSA_PKCS_OAEP_PARAMS */


/**
 * @brief RSA AES Keywrap Parameters
 */
typedef struct CK_RSA_AES_KEY_WRAP_PARAMS_ {
	CK_ULONG                     ulAESKeyBits;
	CK_RSA_PKCS_OAEP_PARAMS_PTR  pOAEPParams;
} CK_RSA_AES_KEY_WRAP_PARAMS;

typedef CK_RSA_AES_KEY_WRAP_PARAMS* CK_RSA_AES_KEY_WRAP_PARAMS_PTR; /*!< pointer to CK_RSA_AES_KEY_WRAP_PARAMS */


/* DSA */

/**
 * @brief DSA Parameter Generation Parameters
 */
typedef struct CK_DSA_PARAMETER_GEN_PARAM_ {
	CK_MECHANISM_TYPE  hash;
	CK_BYTE_PTR        pSeed;
	CK_ULONG           ulSeedLen;
	CK_ULONG           ulIndex;
}  CK_DSA_PARAMETER_GEN_PARAM;

typedef CK_DSA_PARAMETER_GEN_PARAM* CK_DSA_PARAMETER_GEN_PARAM_PTR; /*!< pointer to CK_DSA_PARAMETER_GEN_PARAM */

/* EC / Edwards */

/**
 * @defgroup PKCS11_EC_MECH_FLAGS PKCS#11 EC Mechanism Flags
 * @{
 */
#define CKF_EC_F_P           0x00100000UL /*!< True if the mechanism can be used with EC domain parameters over Fp */
#define CKF_EC_F_2M          0x00200000UL /*!< True if the mechanism can be used with EC domain parameters over F2m */
#define CKF_EC_ECPARAMETERS  0x00400000UL /*!< True if the mechanism can be used with EC domain parameters of the choice ecParameters */
#define CKF_EC_OID           0x00800000UL /*!< True if the mechanism can be used with EC domain parameters of the choice oId */
#define CKF_EC_NAMEDCURVE    CKF_EC_OID /*!< compat */
#define CKF_EC_UNCOMPRESS    0x01000000UL /*!< True if the mechanism can be used with elliptic curve point uncompressed */
#define CKF_EC_COMPRESS      0x02000000UL /*!< True if the mechanism can be used with elliptic curve point compressed */
#define CKF_EC_CURVENAME     0x04000000UL /*!< True of the mechanism can be used with EC domain parameters of the choice curveName */
/** @} */

/**
 * @brief EdDSA Parameters
 */
typedef struct CK_EDDSA_PARAMS_ {
	CK_BBOOL     phFlag;
	CK_ULONG     ulContextDataLen;
	CK_BYTE_PTR  pContextData;
} CK_EDDSA_PARAMS;

typedef CK_EDDSA_PARAMS* CK_EDDSA_PARAMS_PTR; /*!< pointer to CK_EDDSA_PARAMS */


typedef CK_ULONG CK_XEDDSA_HASH_TYPE; /*!< XEdDSA Hash Algorithm Mechanism */

/**
 * @brief XEdDSA Parameters
 */
typedef struct CK_XEDDSA_PARAMS_ {
	CK_XEDDSA_HASH_TYPE  hash;
} CK_XEDDSA_PARAMS;

typedef CK_XEDDSA_PARAMS* CK_XEDDSA_PARAMS_PTR; /*!< pointer to CK_XEDDSA_PARAMS */


typedef CK_ULONG CK_EC_KDF_TYPE; /*!< EC Key Derivation Function Type */
typedef CK_EC_KDF_TYPE* CK_EC_KDF_TYPE_PTR; /*!< pointer to CK_EC_KDF_TYPE */

/**
 * @brief EC Diffie-Hellman Key Exchange (single key exchange)
 */
typedef struct CK_ECDH1_DERIVE_PARAMS_ {
   CK_EC_KDF_TYPE  kdf;
   CK_ULONG        ulSharedDataLen;
   CK_BYTE_PTR     pSharedData;
   CK_ULONG        ulPublicDataLen;
   CK_BYTE_PTR     pPublicData;
} CK_ECDH1_DERIVE_PARAMS;

typedef CK_ECDH1_DERIVE_PARAMS* CK_ECDH1_DERIVE_PARAMS_PTR; /*!< pointer to CK_ECDH1_DERIVE_PARAMS */


/**
 * @brief EC MQV Key Derivation Parameters
 */
typedef struct CK_ECDH2_DERIVE_PARAMS_ {
	CK_EC_KDF_TYPE    kdf;
	CK_ULONG          ulSharedDataLen;
	CK_BYTE_PTR       pSharedData;
	CK_ULONG          ulPublicDataLen;
	CK_BYTE_PTR       pPublicData;
	CK_ULONG          ulPrivateDataLen;
	CK_OBJECT_HANDLE  hPrivateData;
	CK_ULONG          ulPublicDataLen2;
	CK_BYTE_PTR       pPublicData2;
} CK_ECDH2_DERIVE_PARAMS;

typedef CK_ECDH2_DERIVE_PARAMS* CK_ECDH2_DERIVE_PARAMS_PTR; /*!< pointer to CK_ECDH2_DERIVE_PARAMS */


/**
 * @brief EC MQV Key Derivation Parameters
 */
typedef struct CK_ECMQV_DERIVE_PARAMS_ {
	CK_EC_KDF_TYPE    kdf;
	CK_ULONG          ulSharedDataLen;
	CK_BYTE_PTR       pSharedData;
	CK_ULONG          ulPublicDataLen;
	CK_BYTE_PTR       pPublicData;
	CK_ULONG          ulPrivateDataLen;
	CK_OBJECT_HANDLE  hPrivateData;
	CK_ULONG          ulPublicDataLen2;
	CK_BYTE_PTR       pPublicData2;
	CK_OBJECT_HANDLE  publicKey;
} CK_ECMQV_DERIVE_PARAMS;

typedef CK_ECMQV_DERIVE_PARAMS* CK_ECMQV_DERIVE_PARAMS_PTR; /*!< pointer to CK_ECMQV_DERIVE_PARAMS */


/**
 * @brief EC Diffie-Hellman Key Wrap Parameters
 */
typedef struct CK_ECDH_AES_KEY_WRAP_PARAMS_ {
	CK_ULONG        ulAESKeyBits;
	CK_EC_KDF_TYPE  kdf;
	CK_ULONG        ulSharedDataLen;
	CK_BYTE_PTR     pSharedData;
} CK_ECDH_AES_KEY_WRAP_PARAMS;

typedef CK_ECDH_AES_KEY_WRAP_PARAMS* CK_ECDH_AES_KEY_WRAP_PARAMS_PTR; /*!< pointer to CK_ECDH_AES_KEY_WRAP_PARAMS */


/* Diffie-Hellman */

typedef CK_ULONG CK_X9_42_DH_KDF_TYPE; /*!< DH Key Derivation Function Type */
typedef CK_X9_42_DH_KDF_TYPE* CK_X9_42_DH_KDF_TYPE_PTR; /*!< pointer to CK_X9_42_DH_KDF_TYPE */

/**
 * @brief Diffie-Hellman Key Deriviation Parameters (single key exchange)
 */
typedef struct CK_X9_42_DH1_DERIVE_PARAMS_ {
	CK_X9_42_DH_KDF_TYPE  kdf;
	CK_ULONG              ulOtherInfoLen;
	CK_BYTE_PTR           pOtherInfo;
	CK_ULONG              ulPublicDataLen;
	CK_BYTE_PTR           pPublicData;
} CK_X9_42_DH1_DERIVE_PARAMS;

typedef CK_X9_42_DH1_DERIVE_PARAMS* CK_X9_42_DH1_DERIVE_PARAMS_PTR; /*!< pointer to CK_X9_42_DH1_DERIVE_PARAMS */


/**
 * @brief Diffie-Hellman Key Deriviation Parameters (Hybrid/MQV)
 */
typedef struct CK_X9_42_DH2_DERIVE_PARAMS_ {
	CK_X9_42_DH_KDF_TYPE  kdf;
	CK_ULONG              ulOtherInfoLen;
	CK_BYTE_PTR           pOtherInfo;
	CK_ULONG              ulPublicDataLen;
	CK_BYTE_PTR           pPublicData;
	CK_ULONG              ulPrivateDataLen;
	CK_OBJECT_HANDLE      hPrivateData;
	CK_ULONG              ulPublicDataLen2;
	CK_BYTE_PTR           pPublicData2;
} CK_X9_42_DH2_DERIVE_PARAMS;

typedef CK_X9_42_DH2_DERIVE_PARAMS* CK_X9_42_DH2_DERIVE_PARAMS_PTR; /*!< pointer to CK_X9_42_DH2_DERIVE_PARAMS */


/**
 * @brief Diffie-Hellman MQV Key Deriviation Parameters
 */
typedef struct CK_X9_42_MQV_DERIVE_PARAMS_ {
	CK_X9_42_DH_KDF_TYPE  kdf;
	CK_ULONG             ulOtherInfoLen;
	CK_BYTE_PTR          pOtherInfo;
	CK_ULONG             ulPublicDataLen;
	CK_BYTE_PTR          pPublicData;
	CK_ULONG             ulPrivateDataLen;
	CK_OBJECT_HANDLE     hPrivateData;
	CK_ULONG             ulPublicDataLen2;
	CK_BYTE_PTR          pPublicData2;
	CK_OBJECT_HANDLE     publicKey;
} CK_X9_42_MQV_DERIVE_PARAMS;

typedef CK_X9_42_MQV_DERIVE_PARAMS* CK_X9_42_MQV_DERIVE_PARAMS_PTR; /*!< pointer to CK_X9_42_MQV_DERIVE_PARAMS */


/* Extended Triple Diffie-Hellman */

typedef CK_ULONG CK_X3DH_KDF_TYPE; /*!< X3DH Key Derivation Function Type */
typedef CK_X3DH_KDF_TYPE* CK_X3DH_KDF_TYPE_PTR; /*!< pointer to CK_X3DH_KDF_TYPE */

/**
 * @brief X3DH Initialize Key Exchange Parameters
 */
typedef struct CK_X3DH_INITIATE_PARAMS_ {
	CK_X3DH_KDF_TYPE  kdf;
	CK_OBJECT_HANDLE  pPeer_identity;
	CK_OBJECT_HANDLE  pPeer_prekey;
	CK_BYTE_PTR       pPrekey_signature;
	CK_BYTE_PTR       pOnetime_key;
	CK_OBJECT_HANDLE  pOwn_identity;
	CK_OBJECT_HANDLE  pOwn_ephemeral;
} CK_X3DH_INITIATE_PARAMS;

typedef CK_X3DH_INITIATE_PARAMS* CK_X3DH_INITIATE_PARAMS_PTR; /*!< pointer to CK_X3DH_INITIATE_PARAMS */


/**
 * @brief X3DH Respond Key Exchange Parameters
 */
typedef struct CK_X3DH_RESPOND_PARAMS_ {
   CK_X3DH_KDF_TYPE  kdf;
   CK_BYTE_PTR       pIdentity_id;
   CK_BYTE_PTR       pPrekey_id;
   CK_BYTE_PTR       pOnetime_id;
   CK_OBJECT_HANDLE  pInitiator_identity;
   CK_BYTE_PTR       pInitiator_ephemeral;
} CK_X3DH_RESPOND_PARAMS;

typedef CK_X3DH_RESPOND_PARAMS* CK_X3DH_RESPOND_PARAMS_PTR; /*!< pointer to CK_X3DH_RESPOND_PARAMS */


/* Double Ratchet */

typedef CK_ULONG CK_X2RATCHET_KDF_TYPE; /*!< Double Ratchet Key Derivation Function Type */
typedef CK_X2RATCHET_KDF_TYPE* CK_X2RATCHET_KDF_TYPE_PTR; /*!< pointer to CK_X2RATCHET_KDF_TYPE */


/**
 * @brief Double Ratchet Initialize Key Exchange Parameters
 */
typedef struct CK_X2RATCHET_INITIALIZE_PARAMS_ {
	CK_BYTE_PTR            sk;
	CK_OBJECT_HANDLE       peer_public_prekey;
	CK_OBJECT_HANDLE       peer_public_identity;
	CK_OBJECT_HANDLE       own_public_identity;
	CK_BBOOL               bEncryptedHeader;
	CK_ULONG               eCurve;
	CK_MECHANISM_TYPE      aeadMechanism;
	CK_X2RATCHET_KDF_TYPE  kdfMechanism;
} CK_X2RATCHET_INITIALIZE_PARAMS;

typedef CK_X2RATCHET_INITIALIZE_PARAMS* CK_X2RATCHET_INITIALIZE_PARAMS_PTR; /*!< pointer to CK_X2RATCHET_INITIALIZE_PARAMS */


/**
 * @brief Double Ratchet Initialize Key Exchange Parameters
 */
 typedef struct CK_X2RATCHET_RESPOND_PARAMS_ {
	CK_BYTE_PTR            sk;
	CK_OBJECT_HANDLE       own_prekey;
	CK_OBJECT_HANDLE       initiator_identity;
	CK_OBJECT_HANDLE       own_public_identity;
	CK_BBOOL               bEncryptedHeader;
	CK_ULONG               eCurve;
	CK_MECHANISM_TYPE      aeadMechanism;
	CK_X2RATCHET_KDF_TYPE  kdfMechanism;
} CK_X2RATCHET_RESPOND_PARAMS;

typedef CK_X2RATCHET_RESPOND_PARAMS* CK_X2RATCHET_RESPOND_PARAMS_PTR; /*!< pointer to CK_X2RATCHET_RESPOND_PARAMS */


/* MAC */

typedef CK_ULONG CK_MAC_GENERAL_PARAMS; /*!< General MAC parameters */
typedef CK_MAC_GENERAL_PARAMS* CK_MAC_GENERAL_PARAMS_PTR; /*!< pointer to CK_MAC_GENERAL_PARAMS */

/* AES */

/**
 * @brief AES Counter Mode Parameters
 */
typedef struct CK_AES_CTR_PARAMS_ {
	CK_ULONG  ulCounterBits;
	CK_BYTE   cb[16];
}  CK_AES_CTR_PARAMS;

typedef CK_AES_CTR_PARAMS* CK_AES_CTR_PARAMS_PTR; /*!< pointer to CK_AES_CTR_PARAMS */


typedef CK_ULONG CK_GENERATOR_FUNCTION; /*!< IV and nonce generator function */

/**
 * @defgroup PKCS11_Nonce_Generator PKCS#11 AES GCM/CCM Nonce Generator Functions
 * @{
 */
#define CKG_NO_GENERATE       0x00000000UL
#define CKG_GENERATE          0x00000001UL
#define CKG_GENERATE_COUNTER  0x00000002UL
#define CKG_GENERATE_RANDOM   0x00000003UL
/** @} */


/**
 * @brief AES GCM Parameters
 */
typedef struct CK_GCM_PARAMS_ {
	CK_BYTE_PTR  pIv;
	CK_ULONG     ulIvLen;
	CK_ULONG     ulIvBits;
	CK_BYTE_PTR  pAAD;
	CK_ULONG     ulAADLen;
	CK_ULONG     ulTagBits;
} CK_GCM_PARAMS;

typedef CK_GCM_PARAMS* CK_GCM_PARAMS_PTR; /*!< pointer to CK_GCM_PARAMS */


/**
 * @brief AES GCM Message Parameters
 */
typedef struct CK_GCM_MESSAGE_PARAMS_ {
   CK_BYTE_PTR            pIv;
   CK_ULONG               ulIvLen;
   CK_ULONG               ulIvFixedBits;
   CK_GENERATOR_FUNCTION  ivGenerator;
   CK_BYTE_PTR            pTag;
   CK_ULONG               ulTagBits;
} CK_GCM_MESSAGE_PARAMS;

typedef CK_GCM_MESSAGE_PARAMS* CK_GCM_MESSAGE_PARAMS_PTR; /*!< pointer to CK_GCM_MESSAGE_PARAMS */


/**
 * @brief AES CCM Parameters
 */
 typedef struct CK_CCM_PARAMS_ {
	CK_ULONG     ulDataLen; /*plaintext or ciphertext*/
	CK_BYTE_PTR  pNonce;
	CK_ULONG     ulNonceLen;
	CK_BYTE_PTR  pAAD;
	CK_ULONG     ulAADLen;
	CK_ULONG     ulMACLen;
 } CK_CCM_PARAMS;

typedef CK_CCM_PARAMS* CK_CCM_PARAMS_PTR; /*!< pointer to CK_CCM_PARAMS */


/**
 * @brief AES CCM Message Parameters
 */
 typedef struct CK_CCM_MESSAGE_PARAMS_ {
	CK_ULONG               ulDataLen; /*plaintext or ciphertext*/
	CK_BYTE_PTR            pNonce;
	CK_ULONG               ulNonceLen;
	CK_ULONG               ulNonceFixedBits;
	CK_GENERATOR_FUNCTION  nonceGenerator;
	CK_BYTE_PTR            pMAC;
	CK_ULONG               ulMACLen;
 } CK_CCM_MESSAGE_PARAMS;

typedef CK_CCM_MESSAGE_PARAMS* CK_CCM_MESSAGE_PARAMS_PTR; /*!< pointer to CK_CCM_MESSAGE_PARAMS */


/**
 * @brief AES Encryption Key Derivation Parameters
 */
typedef struct CK_AES_CBC_ENCRYPT_DATA_PARAMS_ {
	CK_BYTE      iv[16];
	CK_BYTE_PTR  pData;
	CK_ULONG     length;
} CK_AES_CBC_ENCRYPT_DATA_PARAMS;

typedef CK_AES_CBC_ENCRYPT_DATA_PARAMS* CK_AES_CBC_ENCRYPT_DATA_PARAMS_PTR; /*!< pointer to CK_AES_CBC_ENCRYPT_DATA_PARAMS */


/* PKCS#5 PBKDF2 */

typedef CK_ULONG CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE; /*!< PKCS#5 PBKDF2 PRF */
typedef CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE* CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE_PTR; /*!< pointer to CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE */

/**
 * @defgroup PKCS11_PBKDF2_PRF PKCS#5 PBKDF2 PRF Types
 * @{
 */
#define CKP_PKCS5_PBKD2_HMAC_SHA1        0x00000001UL
#define CKP_PKCS5_PBKD2_HMAC_GOSTR3411   0x00000002UL
#define CKP_PKCS5_PBKD2_HMAC_SHA224      0x00000003UL
#define CKP_PKCS5_PBKD2_HMAC_SHA256      0x00000004UL
#define CKP_PKCS5_PBKD2_HMAC_SHA384      0x00000005UL
#define CKP_PKCS5_PBKD2_HMAC_SHA512      0x00000006UL
#define CKP_PKCS5_PBKD2_HMAC_SHA512_224  0x00000007UL
#define CKP_PKCS5_PBKD2_HMAC_SHA512_256  0x00000008UL
/** @} */


typedef CK_ULONG CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE; /*!< PBKDF2 Salt Source Type */
typedef CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE* CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE_PTR; /*!< pointer to CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE */

/**
 * @defgroup PKCS11_PBKDF2_SALT_TYPE PKCS#5 PBKDF2 Salt Source Types
 * @{
 */
#define CKZ_SALT_SPECIFIED        0x00000001UL
/** @} */


/**
 * @brief PKCS#5 PBKFD2 Parameters
 */
typedef struct CK_PKCS5_PBKD2_PARAMS2_ {
	CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE            saltSource;
	CK_VOID_PTR                                 pSaltSourceData;
	CK_ULONG                                    ulSaltSourceDataLen;
	CK_ULONG                                    iterations;
	CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE  prf;
	CK_VOID_PTR                                 pPrfData;
	CK_ULONG                                    ulPrfDataLen;
	CK_UTF8CHAR_PTR                             pPassword;
	CK_ULONG                                    ulPasswordLen;
} CK_PKCS5_PBKD2_PARAMS2;

typedef CK_PKCS5_PBKD2_PARAMS2* CK_PKCS5_PBKD2_PARAMS2_PTR; /*!< pointer to CK_PKCS5_PBKD2_PARAMS2 */


/* PKCS#12 PBE */

/**
 * @brief PKCS#12 Password Based Encryption Parameters
 */
typedef struct CK_PBE_PARAMS_ {
	CK_BYTE_PTR      pInitVector;
	CK_UTF8CHAR_PTR  pPassword;
	CK_ULONG         ulPasswordLen;
	CK_BYTE_PTR      pSalt;
	CK_ULONG         ulSaltLen;
	CK_ULONG         ulIteration;
} CK_PBE_PARAMS;

typedef CK_PBE_PARAMS* CK_PBE_PARAMS_PTR; /*!< pointer to CK_PBE_PARAMS */


/* SSL 3.0 */

/**
 * @brief SSL 3.0 Random Data
 */
typedef struct CK_SSL3_RANDOM_DATA_ {
	CK_BYTE_PTR  pClientRandom;
	CK_ULONG     ulClientRandomLen;
	CK_BYTE_PTR  pServerRandom;
	CK_ULONG     ulServerRandomLen;
} CK_SSL3_RANDOM_DATA;


/**
 * @brief SSL 3.0 Master Key Derivation Parameters
 */
typedef struct CK_SSL3_MASTER_KEY_DERIVE_PARAMS_ {
	CK_SSL3_RANDOM_DATA  RandomInfo;
	CK_VERSION_PTR       pVersion;
} CK_SSL3_MASTER_KEY_DERIVE_PARAMS;

typedef CK_SSL3_MASTER_KEY_DERIVE_PARAMS* CK_SSL3_MASTER_KEY_DERIVE_PARAMS_PTR; /*!< pointer to CK_SSL3_MASTER_KEY_DERIVE_PARAMS */


/**
 * @brief SSL 3.0 Key Derivation Result
 */
typedef struct CK_SSL3_KEY_MAT_OUT_ {
	CK_OBJECT_HANDLE  hClientMacSecret;
	CK_OBJECT_HANDLE  hServerMacSecret;
	CK_OBJECT_HANDLE  hClientKey;
	CK_OBJECT_HANDLE  hServerKey;
	CK_BYTE_PTR       pIVClient;
	CK_BYTE_PTR       pIVServer;
} CK_SSL3_KEY_MAT_OUT;

typedef CK_SSL3_KEY_MAT_OUT* CK_SSL3_KEY_MAT_OUT_PTR; /*!< pointer to CK_SSL3_KEY_MAT_OUT */

/**
 * @brief SSL 3.0 Key Derivation Parameters
 */
typedef struct CK_SSL3_KEY_MAT_PARAMS_ {
	CK_ULONG                 ulMacSizeInBits;
	CK_ULONG                 ulKeySizeInBits;
	CK_ULONG                 ulIVSizeInBits;
	CK_BBOOL                 bIsExport;
	CK_SSL3_RANDOM_DATA      RandomInfo;
	CK_SSL3_KEY_MAT_OUT_PTR  pReturnedKeyMaterial;
} CK_SSL3_KEY_MAT_PARAMS;

typedef CK_SSL3_KEY_MAT_PARAMS* CK_SSL3_KEY_MAT_PARAMS_PTR; /*!< pointer to CK_SSL3_KEY_MAT_PARAMS */


/* TLS 1.2 */

/**
 * @brief TLS 1.2 Master Key Derivation Parameters
 */
typedef struct CK_TLS12_MASTER_KEY_DERIVE_PARAMS_ {
	CK_SSL3_RANDOM_DATA  RandomInfo;
	CK_VERSION_PTR       pVersion;
	CK_MECHANISM_TYPE    prfHashMechanism;
} CK_TLS12_MASTER_KEY_DERIVE_PARAMS;

typedef CK_TLS12_MASTER_KEY_DERIVE_PARAMS* CK_TLS12_MASTER_KEY_DERIVE_PARAMS_PTR; /*!< pointer to CK_TLS12_MASTER_KEY_DERIVE_PARAMS */

/**
 * @brief TLS 1.2 Key Material Parameters
 */
typedef struct CK_TLS12_KEY_MAT_PARAMS_ {
	CK_ULONG                 ulMacSizeInBits;
	CK_ULONG                 ulKeySizeInBits;
	CK_ULONG                 ulIVSizeInBits;
	CK_BBOOL                 bIsExport;
	CK_SSL3_RANDOM_DATA      RandomInfo;
	CK_SSL3_KEY_MAT_OUT_PTR  pReturnedKeyMaterial;
	CK_MECHANISM_TYPE        prfHashMechanism;
} CK_TLS12_KEY_MAT_PARAMS;

typedef CK_TLS12_KEY_MAT_PARAMS* CK_TLS12_KEY_MAT_PARAMS_PTR; /*!< pointer to CK_TLS12_KEY_MAT_PARAMS */


/**
 * @brief TLS 1.2 Key Derivation Function Parameters
 */
typedef struct CK_TLS_KDF_PARAMS_ {
	CK_MECHANISM_TYPE    prfMechanism;
	CK_BYTE_PTR          pLabel;
	CK_ULONG             ulLabelLength;
	CK_SSL3_RANDOM_DATA  RandomInfo;
	CK_BYTE_PTR          pContextData;
	CK_ULONG             ulContextDataLength;
} CK_TLS_KDF_PARAMS;

typedef CK_TLS_KDF_PARAMS* CK_TLS_KDF_PARAMS_PTR; /*!< pointer to CK_TLS_KDF_PARAMS */


/**
 * @brief TLS 1.2 MAC Parameters
 */
typedef struct CK_TLS_MAC_PARAMS_ {
	CK_MECHANISM_TYPE  prfMechanism;
	CK_ULONG           ulMacLength;
	CK_ULONG           ulServerOrClient;
} CK_TLS_MAC_PARAMS;

typedef CK_TLS_MAC_PARAMS* CK_TLS_MAC_PARAMS_PTR; /*!< pointer to CK_TLS_MAC_PARAMS */


/**
 * @brief TLS 1.2 PRF Parameters
 */
typedef struct CK_TLS_PRF_PARAMS_ {
  CK_BYTE_PTR    pSeed;
  CK_ULONG       ulSeedLen;
  CK_BYTE_PTR    pLabel;
  CK_ULONG       ulLabelLen;
  CK_BYTE_PTR    pOutput;
  CK_ULONG_PTR   pulOutputLen;
} CK_TLS_PRF_PARAMS;

typedef CK_TLS_PRF_PARAMS* CK_TLS_PRF_PARAMS_PTR; /*!< pointer to CK_TLS_PRF_PARAMS */


/* CMS */


/**
 * @brief CMS Signature Parameters
 */
typedef struct CK_CMS_SIG_PARAMS_ {
	CK_OBJECT_HANDLE  certificateHandle;
	CK_MECHANISM_PTR  pSigningMechanism;
	CK_MECHANISM_PTR  pDigestMechanism;
	CK_UTF8CHAR_PTR   pContentType;
	CK_BYTE_PTR       pRequestedAttributes;
	CK_ULONG          ulRequestedAttributesLen;
	CK_BYTE_PTR       pRequiredAttributes;
	CK_ULONG          ulRequiredAttributesLen;
} CK_CMS_SIG_PARAMS;

typedef CK_CMS_SIG_PARAMS* CK_CMS_SIG_PARAMS_PTR; /*!< pointer to CK_CMS_SIG_PARAMS */

/* Camellia */


/**
 * @brief Camellia Encrypt Parameters
 */
typedef struct CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_ {
	CK_BYTE      iv[16];
	CK_BYTE_PTR  pData;
	CK_ULONG     length;
} CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS;

typedef CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS* CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS_PTR; /*!< pointer to CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS */


/* Aria */


/**
 * @brief Aria Encrypt Parameters
 */
typedef struct CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_ {
	CK_BYTE      iv[16];
	CK_BYTE_PTR  pData;
	CK_ULONG     length;
} CK_ARIA_CBC_ENCRYPT_DATA_PARAMS;

typedef CK_ARIA_CBC_ENCRYPT_DATA_PARAMS* CK_ARIA_CBC_ENCRYPT_DATA_PARAMS_PTR; /*!< pointer to CK_ARIA_CBC_ENCRYPT_DATA_PARAMS */

/* SEED */


/**
 * @brief SEED Encrypt Parameters
 */
typedef struct CK_SEED_CBC_ENCRYPT_DATA_PARAMS_ {
	CK_BYTE      iv[16];
	CK_BYTE_PTR  pData;
	CK_ULONG     length;
} CK_SEED_CBC_ENCRYPT_DATA_PARAMS;

typedef CK_SEED_CBC_ENCRYPT_DATA_PARAMS* CK_SEED_CBC_ENCRYPT_DATA_PARAMS_PTR;  /*!< pointer to CK_SEED_CBC_ENCRYPT_DATA_PARAMS */

/* ChaCha20 */


/**
 * @brief ChaCha20 Encrypt Parameters
 */
typedef struct CK_CHACHA20_PARAMS_ {
	CK_BYTE_PTR  pBlockCounter;
	CK_ULONG     blockCounterBits;
	CK_BYTE_PTR  pNonce;
	CK_ULONG     ulNonceBits;
} CK_CHACHA20_PARAMS;

typedef CK_CHACHA20_PARAMS* CK_CHACHA20_PARAMS_PTR;  /*!< pointer to CK_CHACHA20_PARAMS */

/* Salsa20 */


/**
 * @brief Salsa20 Encrypt Parameters
 */
typedef struct CK_SALSA20_PARAMS_ {
	CK_BYTE_PTR  pBlockCounter;
	CK_BYTE_PTR  pNonce;
	CK_ULONG     ulNonceBits;
} CK_SALSA20_PARAMS;

typedef CK_SALSA20_PARAMS* CK_SALSA20_PARAMS_PTR;  /*!< pointer to CK_SALSA20_PARAMS */

/* Chacha20/Salsa20 + Poly1305 */


/**
 * @brief Chacha20/Salsa20 + Poly1305 Encrypt Parameters
 */
typedef struct CK_SALSA20_CHACHA20_POLY1305_PARAMS_ {
	CK_BYTE_PTR  pNonce;
	CK_ULONG     ulNonceLen;
	CK_BYTE_PTR  pAAD;
	CK_ULONG     ulAADLen;
} CK_SALSA20_CHACHA20_POLY1305_PARAMS;

typedef CK_SALSA20_CHACHA20_POLY1305_PARAMS* CK_SALSA20_CHACHA20_POLY1305_PARAMS_PTR;  /*!< pointer to CK_SALSA20_CHACHA20_POLY1305_PARAMS */


/**
 * @brief Chacha20/Salsa20 + Poly1305 Message Encrypt Parameters
 */
typedef struct CK_SALSA20_CHACHA20_POLY1305_MSG_PARAMS_ {
	CK_BYTE_PTR  pNonce;
	CK_ULONG     ulNonceLen;
	CK_BYTE_PTR  pTag;
} CK_SALSA20_CHACHA20_POLY1305_MSG_PARAMS;

typedef CK_SALSA20_CHACHA20_POLY1305_MSG_PARAMS* CK_SALSA20_CHACHA20_POLY1305_MSG_PARAMS_PTR;  /*!< pointer to CK_SALSA20_CHACHA20_POLY1305_MSG_PARAMS */

/* HKDF */


/**
 * @defgroup PKCS11_HKDF_SALT HKDF Salt Types
 * @{
 */
#define CKF_HKDF_SALT_NULL  0x00000000UL
#define CKF_HKDF_SALT_DATA  0x00000001UL
#define CKF_HKDF_SALT_KEY   0x00000002UL
/** @} */

/**
 * @brief HKDF Parameters
 */
typedef struct CK_HKDF_PARAMS_ {
	CK_BBOOL           bExtract;
	CK_BBOOL           bExpand;
	CK_MECHANISM_TYPE  prfHashMechanism;
	CK_ULONG           ulSaltType;
	CK_BYTE_PTR        pSalt;
	CK_ULONG           ulSaltLen;
	CK_OBJECT_HANDLE   hSaltKey;
	CK_BYTE_PTR        pInfo;
	CK_ULONG           ulInfoLen;
} CK_HKDF_PARAMS;

typedef CK_HKDF_PARAMS* CK_HKDF_PARAMS_PTR;  /*!< pointer to CK_HKDF_PARAMS */

#endif /* QNX_PKCS11_PKCS11MECHANISMS_H_INCLUDED */
