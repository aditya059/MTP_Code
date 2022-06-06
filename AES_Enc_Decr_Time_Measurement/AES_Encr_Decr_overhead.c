// Reference: https://stackoverflow.com/questions/50254710/c-encrypt-and-decrypt-a-string-with-aes

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <time.h>
#include <gmp.h>
#include "aes.h"

#define d 1000

mpz_t maxRange;
mpz_t plaintext[d];
// initilze the state object for the random generator functions
gmp_randstate_t state;

char *plaintextString;
mpz_t ciphertext;
uint8_t *in[d];
size_t len[d];

void initialization()
{
    mpz_init_set_si(maxRange, 999999);
    unsigned long seed;

    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);
    mpz_init(ciphertext);
    for (int i = 0; i < d; i++)
    {
        mpz_init(plaintext[i]);
        mpz_urandomm(plaintext[i], state, maxRange); // Random Query Generation
    }
}

void strToByteArray(char *in, uint8_t *out, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        out[i] = in[i];
    }
}

void garbageCollection()
{
    // *********************** GARBAGE COLLECTION *********************** //
    // empty the memory location for the random generator state
    gmp_randclear(state);
    // clear the memory locations for the variables used to avoid leaks
    mpz_clear(maxRange);
    for (int i = 0; i < d; i++)
    {
        mpz_clear(plaintext[i]);
        free(in[i]);
    }
    free(plaintextString);
    mpz_clear(ciphertext);
}

int main()
{
    initialization();

    clock_t begin = clock();
    uint8_t key[] = "secret key 123";
    uint8_t iv[16] = {0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};
    struct AES_ctx ctx;

    plaintextString = (char *)malloc(10 * sizeof(char));
    for (int i = 0; i < d; i++)
    {
        plaintextString = mpz_get_str(plaintextString, 10, plaintext[i]); // 10 is for Base, i.e., Base 10 num

        len[i] = strlen(plaintextString);
        in[i] = (uint8_t *)malloc(len[i] * sizeof(uint8_t));
        strToByteArray(plaintextString, in[i], len[i]);

        // printf("Length: %lu", strlen((char *)in[i]));
        AES_init_ctx_iv(&ctx, key, iv);
        AES_CTR_xcrypt_buffer(&ctx, in[i], len[i]);
        // printf("\nENC: %s", (char *)in[i]); // don't use this string as an input
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Encryption Time = %f\n", time_spent);

    begin = clock();
    for (int i = 0; i < d; i++)
    {
        // gmp_printf("PlainText: %Zd\n", plaintext[i]);
        AES_init_ctx_iv(&ctx, key, iv);
        AES_CTR_xcrypt_buffer(&ctx, in[i], len[i]);
        mpz_set_str(ciphertext, in[i], 10); // 10 is for Base, i.e., Base 10 num
        // printf("\nDEC: %s\n", (char *)in[i]);
        // gmp_printf("CipherText: %Zd\n", ciphertext);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Decryption Time = %f\n", time_spent);
    garbageCollection();
    return 0;
}