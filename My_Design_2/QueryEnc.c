#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#define num_of_features 10
#define eta (num_of_features + 1)

mpz_t query[eta];

mpz_t maxRange, phi, betaQ;
// initilze the state object for the random generator functions
gmp_randstate_t state;

//-------------------------------------------------------------------------------------------
// QU's Work

void genQueryByQU()
{
    FILE *file;
    file = fopen("queryByQU.txt", "w");
    for (int i = 0; i < num_of_features; i++)
    {
        mpz_init(query[i]);
        mpz_urandomm(query[i], state, maxRange);
        gmp_fprintf(file, "%Zd ", query[i]);
    }
    // Added by DO
    mpz_init_set_si(query[num_of_features], 1);
    fclose(file);
}

//---------------------------------------------------------------------------------
// QU's Work
void decryptQueryByQU()
{
    FILE *file;
    file = fopen("finalDecryptedQuery.txt", "w");
    for (int i = 0; i < eta; i++)
    {
        gmp_fprintf(file, "%Zd ", query[i]);
    }
    fclose(file);
}

void garbageCollection()
{
    // *********************** GARBAGE COLLECTION *********************** //
    // empty the memory location for the random generator state
    gmp_randclear(state);
    // clear the memory locations for the variables used to avoid leaks
    mpz_clear(maxRange);
    mpz_clear(phi);
    mpz_clear(betaQ);
    for (int i = 0; i < eta; i++)
    {
        mpz_clear(query[i]);
    }
}

int main()
{
    unsigned long seed;
    mpz_init_set_si(maxRange, 99);

    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);

    genQueryByQU();

    decryptQueryByQU();

    garbageCollection();

    return 0;
}