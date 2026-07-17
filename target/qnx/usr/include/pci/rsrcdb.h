#ifndef _RSRCDB_H_
#define _RSRCDB_H_
/*
 * Copyright (c) 2025 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Default names for the PCI server resources managed by the RSRCDB
 * When creating non-default pools, the pool ID is appended to one of these
 * depending on the pool type
*/
#define PCI_RSRC_NAME_MSGVEC		"PCI MSG Vectors"
#define PCI_RSRC_NAME_MEM_ASPACE	"PCI Mem ASpace"
#define PCI_RSRC_NAME_IO_ASPACE		"PCI IO ASpace"

/*
 ===============================================================================
 rsrcdb_pool_id_t

 Unique resource database pool identifier returned from a successful call to
 rsrcdb_pool_create()

 This identifier can be used when allocating and freeing resources with the
 rsrcdb_*() API's

*/
typedef uintptr_t	rsrcdb_pool_id_t;
#define rsrcdb_pool_id_NONE		((rsrcdb_pool_id_t)-1)
#define rsrcdb_pool_id_DEFAULT	((rsrcdb_pool_id_t)0)

/*
 ===============================================================================
 rsrcdb_pool_type_e

 These are the currently defined pool types that can be used when creating a
 resource pool

*/
typedef enum
{
rsrcdb_pool_type_first = 100,

	rsrcdb_pool_type_MEM = rsrcdb_pool_type_first,
	rsrcdb_pool_type_IO,
	rsrcdb_pool_type_IRQ,

rsrcdb_pool_type_end,
rsrcdb_pool_type_last = rsrcdb_pool_type_end - 1,
} rsrcdb_pool_type_e;

#endif /* _RSRCDB_H_ */
