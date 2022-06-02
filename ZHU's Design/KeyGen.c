#include <stdio.h>
#include <gmp.h>
#define num_of_data_points 10
#define num_of_features 5
#define c 2
#define epsilon 2
#define eta (num_of_features + 1 + c + epsilon)
mpz_t matrix[eta][eta];
mpz_t s_vector[num_of_features + 1];
mpz_t tow[c];

mpz_t maxRange;
// initilze the state object for the random generator functions
gmp_randstate_t state;

void genMatrixM()
{
    FILE *file;
    file = fopen("M.txt", "w");
    for (int i = 0; i < eta; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpz_init(matrix[i][j]);
            mpz_urandomm(matrix[i][j], state, maxRange);
            gmp_fprintf(file, "%Zd ", matrix[i][j]);
        }
        gmp_fprintf(file, "\n");
    }
    fclose(file);
}

void genVectorS()
{
    FILE *file;
    file = fopen("s.txt", "w");
    for (int i = 0; i <= num_of_features; i++)
    {
        mpz_init(s_vector[i]);
        mpz_urandomm(s_vector[i], state, maxRange);
        gmp_fprintf(file, "%Zd ", s_vector[i]);
    }
    fclose(file);
}

void genVectorTow()
{
    FILE *file;
    file = fopen("tow.txt", "w");
    for (int i = 0; i < c; i++)
    {
        mpz_init(tow[i]);
        mpz_urandomm(tow[i], state, maxRange);
        gmp_fprintf(file, "%Zd ", tow[i]);
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
    for (int i = 0; i < eta; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpz_clear(matrix[i][j]);
        }
    }
    for (int i = 0; i <= num_of_features; i++)
    {
        mpz_clear(s_vector[i]);
    }
    for (int i = 0; i < c; i++)
    {
        mpz_clear(tow[i]);
    }
}

// Reference: https://stackoverflow.com/questions/30942413/c-gmp-generating-random-number
int main()
{
    unsigned long seed;
    mpz_init_set_si(maxRange, 99);

    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);

    genMatrixM();
    genVectorS();
    genVectorTow();
    garbageCollection();

    return 0;
}