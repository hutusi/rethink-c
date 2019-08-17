/**
 * @file def.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Defines.
 *
 * @date 2019-08-11
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_DEF_H
#define RETHINK_C_DEF_H

#ifdef TESTING
#define STATIC
#else
#define STATIC static
#endif

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

#endif /* #ifndef RETHINK_C_DEF_H */
