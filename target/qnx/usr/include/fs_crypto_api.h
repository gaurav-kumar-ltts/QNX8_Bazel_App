/* $QNXLicenseC$ */

/*  Proto types for the fs_crypto library.
 */
#ifndef _FS_CRYPTO_API_INCLUDED
#define _FS_CRYPTO_API_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>

struct migrate_status_s;
void fs_crypto_set_logging(
    FILE *logfile,
    const int verbosity);
int fs_crypto_domain_add_flags(
    const char *path,
    int domain,
    int type,
    int flags,
    int state,
    int length,
    const uint8_t bytes[],
    int *preply);
int fs_crypto_domain_add(
    const char *path,
    int domain,
    int type,
    int state,
    int length,
    const uint8_t bytes[],
    int *preply);
int fs_crypto_domain_remove(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_domain_lock(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_domain_hard_lock(
    const char *path,
    int domain,
    int *preply,
    unsigned flags);
int fs_crypto_domain_unlock(
    const char *path,
    int domain,
    int length,
    const uint8_t bytes[],
    int *preply);
int fs_crypto_domain_query(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_domain_key_size(void);
int fs_crypto_key_read(
    const char *path,
    int *plength,
    uint8_t bytes[],
    int *preply);
int fs_crypto_key_write(
    const char *path,
    int length,
    const uint8_t bytes[],
    int *preply);
int fs_crypto_check(
    const char *path,
    int *preply);
int fs_crypto_enable(
    const char *path,
    int *preply);
int fs_crypto_enable_option(
    const char *path,
	uint32_t option,
	uint32_t domain,
    int *preply);
int fs_crypto_disable_option(
    const char *path,
    uint32_t option,
    int *preply);
int fs_crypto_file_get_domain(
    const char *path,
    int *pdomain,
    int *preply);
int fs_crypto_file_set_domain(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_file_name_crypt(
    const char *path,
    bool encrypt,
    int *preply);
int fs_crypto_file_move_domain(
    const char *path,
    int  domain,
    bool force,
    bool recurse,
    int *preply);
int fs_crypto_file_remove_domain(
    const char *path,
    bool force,
    bool recurse,
    int *preply);
int fs_crypto_key_gen(
    const char *password,
    int plen,
    const uint8_t *salt,
    int slen,
    uint8_t *key,
    int klen);
int fs_crypto_domain_key_change(
    const char *path,
    int domain,
    int length,
    const uint8_t org_key[],
    const uint8_t new_key[],
    int *preply);
int fs_crypto_domain_key_check(
    const char *path,
    int domain,
    int length,
    const uint8_t bytes[],
    int *preply);
int fs_crypto_migrate_tag(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_migrate_state(
    const char *path,
    uint64_t *premaining,
    int *preply);
int fs_crypto_migrate_control(
    const char *path,
    uint32_t flags,
    uint64_t context,
    int *preply);
int fs_crypto_migrate_path(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_migrate_status(
    const char *path,
    struct migrate_status_s *status,
    int *preply);
int fs_crypto_domain_whitelist_ctrl(
    const char *path,
    int domain,
    unsigned action,
    unsigned type,
    const void *data,
    int *preply);
int fs_crypto_domain_whitelist_ctrl_access_grant(
    const char *path,
    int domain,
    unsigned type,
    const void *data,
    int *preply);
int fs_crypto_domain_whitelist_ctrl_access_revoke(
    const char *path,
    int domain,
    unsigned type,
    const void *data,
    int *preply);
int fs_crypto_domain_whitelist_configure(
    const char *path,
    int domain,
    unsigned type,
    unsigned *flags,
    int *preply);
int fs_crypto_domain_whitelist_get_flags(
    const char *path,
    int domain,
    unsigned type,
    unsigned *flags,
    int *preply);
int fs_crypto_domain_whitelist_set_flags(
    const char *path,
    int domain,
    unsigned type,
    unsigned *flags,
    int *preply);
int fs_crypto_domain_add_dynamic(
    const char *path,
    int type,
    int state,
    int length,
    const uint8_t bytes[],
    int *preply);
int fs_crypto_domain_remove_dynamic(
    const char *path,
    int *preply);
int fs_crypto_domain_lock_dynamic(
    const char *path,
    int *preply);
int fs_crypto_domain_unlock_dynamic(
    const char *path,
    int length,
    const uint8_t bytes[],
    int *preply);

/*	DEPRECATED FUNCTIONS
 */
int fs_crypto_domain_whitelist_pid_add(
    const char *path,
    int domain,
    pid_t pid,
    int *preply);
int fs_crypto_domain_whitelist_pid_remove(
    const char *path,
    int domain,
    pid_t pid,
    int *preply);

#ifdef __cplusplus
}
#endif

#endif /* _FS_CRYPTO_API_INCLUDED */
