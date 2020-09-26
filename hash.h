#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <stdint.h>

/** 
 * hash_hashCode 
 * @author Paul Hsieh
 * @date 2004-2008
 * @copyright LGPL 2.1 license
 * @brief A hash function
 *
 * @see http://www.azillionmonkeys.com/qed/hash.html
 */
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) || defined(_MSC_VER) || defined(__BORLANDC__) || defined(__TURBOC__)
#define get16bits(d) (*((const uint16_t *)(d)))
#endif

#if !defined(get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8) + (uint32_t)(((const uint8_t *)(d))[0]))
#endif

uint32_t SuperFastHash(const char *data, size_t len);



#endif // __HASH_H__
