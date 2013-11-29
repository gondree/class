/*  combinatorics.h
    ---------------
    A header defining constants used in the combinatorial libraries
*/

#ifndef _COMBINATORICS_H_
#define _COMBINATORICS_H_

#include <limits.h>

//
// type for holding large combinatorial values
//
typedef long int comb_t;

#define COMB_MAX  LONG_MAX
#define COMB_MIN  LONG_MIN

//
// identifiers for supported combinatorial sequences
//
enum comb { BELL, CATALAN, FIB, LUCAS };


#endif
