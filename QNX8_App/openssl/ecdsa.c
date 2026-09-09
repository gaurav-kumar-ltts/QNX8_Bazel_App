#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ec.h>

typedef enum {
    ALG_UNKNOWN = -1,
    ALG_ECDSA,
    ALG_ECDSA_SHA256,
    ALG_ECDSA_SHA384,
    ALG_ECDSA_SHA512,
    ALG_ECDH1_DERIVE
} ECAlgorithm;

ECAlgorithm get_algorithm(const char *alg_str) {
    if (strcmp(alg_str, "CKM_ECDSA") == 0) return ALG_ECDSA;
    if (strcmp(alg_str, "CKM_ECDSA_SHA256") == 0) return ALG_ECDSA_SHA256;
    if (strcmp(alg_str, "CKM_ECDSA_SHA384") == 0) return ALG_ECDSA_SHA384;
    if (strcmp(alg_str, "CKM_ECDSA_SHA512") == 0) return ALG_ECDSA_SHA512;
    if (strcmp(alg_str, "CKM_ECDH1_DERIVE") == 0) return ALG_ECDH1_DERIVE;
    return ALG_UNKNOWN;
}

int check_ecdsa_with_digest(const EVP_MD *md, int nid_curve, const char *alg_name) {
    if ((md == NULL) && (strcmp(alg_name, "CKM_ECDSA") != 0)) {
        printf("Digest for %s is NOT supported.\n", alg_name);
        return -1;
    } else {
        printf("Digest for %s IS supported.\n", alg_name);
    }

    EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    EVP_PKEY *pkey = NULL;

    if (!pctx || EVP_PKEY_keygen_init(pctx) <= 0 ||
        EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, nid_curve) <= 0 ||
        EVP_PKEY_keygen(pctx, &pkey) <= 0) {
        printf("EC key generation failed.\n");
        EVP_PKEY_CTX_free(pctx);
        return -1;
    }
    EVP_PKEY_CTX_free(pctx);

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        printf("Failed to create EVP_MD_CTX.\n");
        EVP_PKEY_free(pkey);
        return -1;
    }

    if (EVP_DigestSignInit(mdctx, NULL, md, NULL, pkey) <= 0) {
        printf("ECDSA with %s is NOT supported.\n", alg_name);
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(mdctx);
        EVP_PKEY_free(pkey);
        return -1;
    } else {
        printf("ECDSA with %s IS supported.\n", alg_name);
    }

    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    return 0;
}

int check_ecdh(const char *alg_name) {
    EVP_PKEY_CTX *keygen_ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    EVP_PKEY *key1 = NULL, *key2 = NULL;

    if (!keygen_ctx || EVP_PKEY_keygen_init(keygen_ctx) <= 0 ||
        EVP_PKEY_CTX_set_ec_paramgen_curve_nid(keygen_ctx, NID_X9_62_prime256v1) <= 0 ||
        EVP_PKEY_keygen(keygen_ctx, &key1) <= 0 ||
        EVP_PKEY_keygen(keygen_ctx, &key2) <= 0) {
        printf("EC key generation failed.\n");
        EVP_PKEY_CTX_free(keygen_ctx);
        return -1;
    }
    EVP_PKEY_CTX_free(keygen_ctx);

    EVP_PKEY_CTX *derive_ctx = EVP_PKEY_CTX_new(key1, NULL);
    if (!derive_ctx || EVP_PKEY_derive_init(derive_ctx) <= 0 ||
        EVP_PKEY_derive_set_peer(derive_ctx, key2) <= 0) {
        printf("ECDH (%s) is NOT supported.\n", alg_name);
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(derive_ctx);
        EVP_PKEY_free(key1);
        EVP_PKEY_free(key2);
        return -1;
    } else {
        size_t secret_len;
        if (EVP_PKEY_derive(derive_ctx, NULL, &secret_len) <= 0) {
            printf("ECDH (%s) failed to derive.\n", alg_name);
            ERR_print_errors_fp(stderr);
            EVP_PKEY_CTX_free(derive_ctx);
            EVP_PKEY_free(key1);
            EVP_PKEY_free(key2);
            return -1;
        } else {
            printf("ECDH (%s) IS supported.\n", alg_name);
        }
    }

    EVP_PKEY_CTX_free(derive_ctx);
    EVP_PKEY_free(key1);
    EVP_PKEY_free(key2);
    return 0;
}

int main(int argc, char *argv[]) {
    OpenSSL_add_all_algorithms();

    if (argc != 2) {
        printf("Usage: %s <EC mechanism>\n", argv[0]);
        return -1;
    }

    const char *alg = argv[1];
    const EVP_MD *md = NULL;
    int nid_curve = 0;

    ECAlgorithm ec_alg = get_algorithm(alg);

    switch (ec_alg) {
        case ALG_ECDSA:
            md = NULL;
            nid_curve = NID_X9_62_prime256v1;
            check_ecdsa_with_digest(md, nid_curve, alg);
            break;
        case ALG_ECDSA_SHA256:
            md = EVP_sha256();
            nid_curve = NID_X9_62_prime256v1;
            check_ecdsa_with_digest(md, nid_curve, alg);
            break;
        case ALG_ECDSA_SHA384:
            md = EVP_sha384();
            nid_curve = NID_secp384r1;
            check_ecdsa_with_digest(md, nid_curve, alg);
            break;
        case ALG_ECDSA_SHA512:
            md = EVP_sha512();
            nid_curve = NID_secp521r1;
            check_ecdsa_with_digest(md, nid_curve, alg);
            break;
        case ALG_ECDH1_DERIVE:
            check_ecdh(alg);
            break;
        default:
            printf("Unsupported algorithm: %s\n", alg);
            return -1;
    }

    EVP_cleanup();
    return 0;
}
