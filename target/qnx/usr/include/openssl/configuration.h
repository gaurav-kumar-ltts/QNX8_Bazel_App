/*
 * Copyright (c) 2020-2023, BlackBerry Limited
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#if defined(__X86_64__)
# include <openssl/x86_64/configuration.h>
#elif defined(__aarch64__)
# include <openssl/aarch64le/configuration.h>
#else
# error unsupported platform
#endif
