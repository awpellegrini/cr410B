#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

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


void rsa(){
    //rand seed
    unsigned long seed;
    initializeRandomGenerator();
    seedRandomGenerator(seed);

    //primes p,q
    mpz_t p, q;
    mpz_init(p);
    generatePrime(p, 100);

    gmp_printf("p = %Zd\n", p);

    mpz_init(q);
    generatePrime(q, 100);

    gmp_printf("q = %Zd\n", q);

    //calculate n
    mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q);

    printf("\n");
    gmp_printf("n = %Zd\n", n);

    //calculate phi(n)
    mpz_t p1, q1, phi;
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(phi);

    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);

    printf("\n");
    gmp_printf("p-1 = %Zd\n", p1);
    gmp_printf("q-1 = %Zd\n", q1);
    printf("\n");
    gmp_printf("phi(n) = %Zd\n", phi);

    //generate e coprime with phi(n)
    mpz_t e;
    mpz_init(e);
    generateCoprime(e, phi);

    printf("\n");
    gmp_printf("e = %Zd\n", e);

    //calculate d inverse of e modulo phi(n)
    mpz_t d;
    mpz_init(d);
    mpz_invert(d, e, phi);

    gmp_printf("d = %Zd\n", d);

    //create cipher for message m
    mpz_t m, c;
    mpz_init(m);
    mpz_set_ui(m, 123456789);
    mpz_init(c);
    mpz_powm(c, m, e, n);

    printf("\n");
    gmp_printf("plaintext = %Zd\n", m);
    gmp_printf("ciphertext = %Zd\n", c);

    //decrypt cipher
    mpz_t m2;
    mpz_init(m2);
    mpz_powm(m2, c, d, n);

    printf("\n");
    gmp_printf("decrypted = %Zd\n", m2);
}