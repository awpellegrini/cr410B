#include "utils.h"

gmp_randstate_t stat;

/** initializeRandomGenerator
 * Initialises the random generator `stat` as mersenne twister,
 * sets regular seed to time(NULL) and uses it to set `stat`
 **/
void initializeRandomGenerator( void ){
	srand( (unsigned) time (NULL) );
	gmp_randinit_mt( stat );
	gmp_randseed_ui( stat, rand( ) );
	return ;
}

/** seedRandomGenerator
 * Initialises the random generator `stat` as mersenne twister,
 * sets regular seed to `seed' and uses it to set `stat`
 * 
 * @param seed [lu] the seed as unsigned long
 **/
void seedRandomGenerator( const unsigned long seed ){
	srand( seed );
	gmp_randinit_mt( stat );
	gmp_randseed_ui( stat, rand( ) );
	return ;
}

/** generateRandomB
 * Generates a number of at most `nb' bits and stores it in `n'
 * Utility method that wraps mpz_urandomb
 * 
 * @param n  [mpz_t]  the output random number
 * @param nb [size_t] the max number of bits of `n'
 **/
void generateRandomB( mpz_t n, const size_t nb ){
	mpz_urandomb(n, stat, nb);
	return ;
}

/** generatePrime
 * Generates a prime number of `nb' bits and stores it in `p'
 * 
 * @param p  [mpz_t]  the output random prime number
 * @param nb [size_t] the max number of bits of `p'
 **/
void generatePrime( mpz_t p, const size_t nb ){
	generateRandomB( p, nb );
	if (mpz_probab_prime_p(p, 15) == 0){
		mpz_nextprime(p, p);
	}
	return ;
}

/** generateCoprime
 * Generates a number mod `n' coprime with it.
 * 
 * @param x [mpz_t] the output random coprime number
 * @param n [mpz_t] the modulus
 **/
void generateCoprime( mpz_t x, const mpz_t n){
	mpz_t temp;
	mpz_init(temp);
	do {
		mpz_urandomm(x, stat, n);
		mpz_gcd(temp, n, x);
	} while (mpz_cmp_ui(temp, 1) != 0);
	mpz_clear(temp);
	return ;
}