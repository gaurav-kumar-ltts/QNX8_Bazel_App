#ifndef _PARSE_H_
#define _PARSE_H_
/*
 * $QNXLicenseC:
 * Copyright (c) 2012, 2021, 2026 BlackBerry Limited. All Rights Reserved.
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

#include <alloca.h>
#include <string.h>

#include "pci/hw_cfg.h"


#define SLOG_PREFIX_STR			"Parse HW Config File: "

#define COMMENT_CHAR				'#'
#define SECTION_HDR_START_CHAR		'['
#define SECTION_HDR_END_CHAR		']'
#define LINE_CONTINUATION_CHAR		'\\'


/*
 * make a null terminated string 'v_new' out of 'v'
 * temporary local storage for 'v_new' will be provided via alloca however
 * since alloca can be mapped to __builtin_alloca() and that can return
 * NULL, handle that case by returning a pointer to something that will never
 * match anything and will also hint to the failure when logged
*/
#define MAKE_TMP_STRING(v_new, v, v_len) \
		do { \
			(v_new) = alloca((v_len) + 1); \
			if ((v_new) == NULL) (v_new) = "MAKE_TMP_STRING alloca() failed"; \
			else \
			{ \
				memcpy((v_new), (v), (v_len)); \
				(v_new)[(v_len)] = '\0'; \
			} \
		} while(0)

/*
 ===============================================================================
 known_section_types

*/
typedef struct
{
	const char *name;
	const uint_t len;
	void (*section_parser)(const char * const section_start, const char * const eof, hw_cfg_t * const cfg);
} known_section_types_t;

/*
 ===============================================================================
 known_names_t

*/
typedef enum
{
	val_type_e_STRING,
	val_type_e_INTEGER,
	val_type_e_REAL,

} val_type_e;

typedef void (*param_handler_f)(const char * const param, char * const param_val, const val_type_e type, const char delim, void * const extra);

typedef struct
{
	const char *name;
	const uint_t len;
	val_type_e type;		// type of value
	bool_t multi_val;		// whether or not the parameter can have multiple values
	const char delim;		// if multiple values are accepted, this char delimits each entry
	param_handler_f param_handler;
} known_param_names_t;

/*
 ===============================================================================
 valid_char_f

*/
typedef bool_t (*valid_char_f)(const char c);

/*
 ===============================================================================
 section_info_t

*/
typedef struct
{
	const char *start;		// pointer to first byte of section
	struct
	{
		const char *str;	// pointer to the section name
		uint_t len;			// length of the section name
	} name;
	struct
	{
		const char *start;	// pointer to first byte of section parameters
		const char *end;	// pointer to last byte of section
	} params;
} section_info_t;


typedef bool_t (*process_section_hw_specific_f)(const section_info_t * const section_info, hw_cfg_t * const cfg, void *arg);
extern process_section_hw_specific_f process_section_hw_specific;

/*
 ===============================================================================
 server function prototypes
*/
const char *find_eol(const char * const start, const char * const end);
const char *find_token(const char token, const char * const start, const char * const end);
const char *find_name(const char * const start, const char * const end, uint_t * const len, const valid_char_f valid_char);
const char *skip_comment(const char *p);
const char *skip_line_continuation(const char *p);
const known_param_names_t *
find_param(const char * const param_name, const known_param_names_t * const known_params, const uint_t nentries);

#endif	/* _PARSE_H_ */
