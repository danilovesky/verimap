#ifndef _HASH_H_
#define _HASH_H_

//---------------------------------------------------------------------------
typedef unsigned ub4;      // unsigned 4-byte quantities
typedef unsigned char ub1; // unsigned 1-byte quantities
#define HASH_SIZE(n) ((ub4)1<<(n))
#define HASH_MASK(n) (HASH_SIZE(n)-1)

//---------------------------------------------------------------------------
extern ub4 hash(register ub1 *k, register ub4 length, register ub4 initval);
extern ub4 hash_string(register const char* key, register ub4 initval);
extern ub4 hash_unsigned(unsigned key, register ub4 initval);

#endif

