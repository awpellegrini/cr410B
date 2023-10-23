#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void initializeRandomGenerator( void );
void seedRandomGenerator( const unsigned long seed );
void generateRandomB( mpz_t n, const size_t nb );
// void clearRandomGenerator( void );
// void generateRandomM( mpz_t n, const mpz_t nmax );
void generatePrime( mpz_t p, const size_t nb );
void generateCoprime( mpz_t x, const mpz_t n);

#endif
