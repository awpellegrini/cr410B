#include "utils.h"


int main(){
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

   return 0;
}