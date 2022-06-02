#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "paillier.h"
#define num_of_features 100
#define C 2
#define epsilon 2
#define eta (num_of_features + 1 + C + epsilon)

paillier_plaintext_t *query[num_of_features];
paillier_ciphertext_t *encrypted_query[num_of_features];
mpz_t M[eta][eta];
mpz_t Rq[C];
paillier_ciphertext_t *Aq[eta];
paillier_plaintext_t *decrypted_query[eta];
paillier_plaintext_t *zero, *plainPhi;
paillier_ciphertext_t *temp, *encryptedPhi;

mpz_t maxRange, phi, betaQ;
// initilze the state object for the random generator functions
gmp_randstate_t state;

paillier_pubkey_t *PK;
paillier_prvkey_t *SK;

//-------------------------------------------------------------------------------------------
// QU's Work
void genKeysByQU()
{
    void *buf = malloc(128);
    void (*get_rand)(void *, int) = paillier_get_rand_devurandom;
    get_rand(buf, 128);
    paillier_keygen(1024, &PK, &SK, get_rand);
    free(buf);
}

void genQueryByQU()
{
    FILE *file;
    file = fopen("queryByQU.txt", "w");
    for (int i = 0; i < num_of_features; i++)
    {
        query[i] = (paillier_plaintext_t *)malloc(sizeof(paillier_plaintext_t));
        mpz_init(query[i]->m);
        mpz_urandomm(query[i]->m, state, maxRange);
        gmp_fprintf(file, "%Zd ", query[i]);
    }
    fclose(file);
}

void encryptQueryByQU()
{
    void *buf = malloc(128);
    void (*get_rand)(void *, int) = paillier_get_rand_devurandom;
    get_rand(buf, 128);
    FILE *file;
    file = fopen("encryptedQueryByQU.txt", "w");
    for (int i = 0; i < num_of_features; i++)
    {
        encrypted_query[i] = paillier_enc(NULL, PK, query[i], get_rand);
        gmp_fprintf(file, "%Zd ", encrypted_query[i]);
    }
    fclose(file);
    free(buf);
}
//-----------------------------------------------------------------------------------------------------
// DO's Work
void genKeysByDO()
{
    mpz_init(betaQ);
    mpz_urandomm(betaQ, state, maxRange);
    gmp_printf("%s = %Zd\n", "Beta generated by DO = ", betaQ);
    // pi = TODO
    for (int i = 0; i < C; i++)
    {
        mpz_init(Rq[i]);
        mpz_urandomm(Rq[i], state, maxRange);
    }
    FILE *file;
    file = fopen("M.txt", "r");
    for (int i = 0; i < eta; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            gmp_fscanf(file, "%Zd ", M[i][j]);
        }
    }
    fclose(file);
}

void encryptQueryByDO()
{
    void *buf = malloc(128);
    void (*get_rand)(void *, int) = paillier_get_rand_devurandom;
    get_rand(buf, 128);

    mpz_init(phi);
    zero = (paillier_plaintext_t *)malloc(sizeof(paillier_plaintext_t));
    mpz_init_set_si(zero->m, 0);
    plainPhi = (paillier_plaintext_t *)malloc(sizeof(paillier_plaintext_t));
    mpz_init(plainPhi->m);
    temp = (paillier_ciphertext_t *)malloc(sizeof(paillier_ciphertext_t));
    mpz_init(temp->c);

    for (int i = 0; i < eta; i++)
    {
        Aq[i] = paillier_enc(NULL, PK, zero, get_rand);
        for (int j = 0; j < eta; j++)
        {
            int t = j;
            mpz_mul(phi, M[i][j], betaQ);
            if (t < num_of_features)
            {
                mpz_set(plainPhi->m, phi);
                paillier_exp(PK, temp, encrypted_query[t], plainPhi);
                paillier_mul(PK, Aq[i], Aq[i], temp);
            }
            else if (t == num_of_features)
            {
                mpz_set(plainPhi->m, phi);
                encryptedPhi = paillier_enc(NULL, PK, plainPhi, get_rand);
                paillier_mul(PK, Aq[i], Aq[i], encryptedPhi);
                paillier_freeciphertext(encryptedPhi);
            }
            else if (t <= num_of_features + C)
            {
                mpz_mul(phi, phi, Rq[t - num_of_features - 1]);
                mpz_set(plainPhi->m, phi);
                encryptedPhi = paillier_enc(NULL, PK, plainPhi, get_rand);
                paillier_mul(PK, Aq[i], Aq[i], encryptedPhi);
                paillier_freeciphertext(encryptedPhi);
            }
        }
    }
    free(buf);
}

//---------------------------------------------------------------------------------
// QU's Work
void decryptQueryByQU()
{
    FILE *file;
    file = fopen("finalDecryptedQuery.txt", "w");
    for (int i = 0; i < eta; i++)
    {
        decrypted_query[i] = paillier_dec(NULL, PK, SK, Aq[i]);
    }
    fclose(file);
    mpz_t gcd;
    mpz_init(gcd);
    mpz_set(gcd, decrypted_query[0]->m);
    for (int i = 1; i < eta; i++)
    {
        mpz_gcd(gcd, gcd, decrypted_query[i]->m);
    }
    gmp_printf("%s = %Zd\n", "Calculated Beta at QU = ", gcd);
    mpz_clear(gcd);
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

    paillier_freepubkey(PK);
    paillier_freeprvkey(SK);
    paillier_freeplaintext(zero);
    paillier_freeplaintext(plainPhi);
    paillier_freeciphertext(temp);

    for (int i = 0; i < num_of_features; i++)
    {
        paillier_freeplaintext(query[i]);
        paillier_freeciphertext(encrypted_query[i]);
    }
    for (int i = 0; i < eta; i++)
    {
        paillier_freeplaintext(decrypted_query[i]);
        paillier_freeciphertext(Aq[i]);
    }
    for (int i = 0; i < C; i++)
    {
        mpz_clear(Rq[i]);
    }
    for (int i = 0; i < eta; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpz_clear(M[i][j]);
        }
    }
}

int main()
{
    unsigned long seed;
    mpz_init_set_si(maxRange, 999999);

    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);

    genKeysByQU();
    genQueryByQU();
    encryptQueryByQU();
    genKeysByDO();
    encryptQueryByDO();
    decryptQueryByQU();
    garbageCollection();

    return 0;
}