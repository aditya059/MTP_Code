#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#include "paillier.h"

#define d 100

int main()
{
    unsigned long seed;
    mpz_t maxRange;
    mpz_init_set_si(maxRange, 999999);

    // initilze the state object for the random generator functions
    gmp_randstate_t state;
    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);

    void *buf = malloc(128);
    void (*get_rand)(void *, int) = paillier_get_rand_devurandom;
    get_rand(buf, 128);

    paillier_pubkey_t *PK;
    paillier_prvkey_t *SK;
    paillier_plaintext_t *plaintext = (paillier_plaintext_t *)malloc(sizeof(paillier_plaintext_t));
    paillier_ciphertext_t *ciphertext;

    clock_t begin = clock();
    paillier_keygen(1024, &PK, &SK, get_rand);
    // gmp_printf("%s = %Zd\n", "Public Key", PK->n);
    // gmp_printf("%s = %Zd\n", "Private Key", SK->lambda);

    for (int i = 0; i < d; i++)
    {
        mpz_init(plaintext->m);
        mpz_urandomm(plaintext->m, state, maxRange);
        ciphertext = paillier_enc(NULL, PK, plaintext, get_rand);
        // plaintext = paillier_dec(NULL, PK, SK, ciphertext);
        // gmp_printf("%s = %Zd\n", "Random No.", rop);
        // gmp_printf("%s = %Zd\n", "PlainText", plaintext->m);
        // gmp_printf("%s = %Zd\n", "CipherText", ciphertext->c);
        // gmp_printf("%s = %Zd\n", "PlainText", plaintext->m);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    free(buf);
    paillier_freepubkey(PK);
    paillier_freeprvkey(SK);
    paillier_freeplaintext(plaintext);
    paillier_freeciphertext(ciphertext);

    // *********************** GARBAGE COLLECTION *********************** //
    // empty the memory location for the random generator state
    gmp_randclear(state);
    // clear the memory locations for the variables used to avoid leaks
    mpz_clear(maxRange);

    return 0;
}