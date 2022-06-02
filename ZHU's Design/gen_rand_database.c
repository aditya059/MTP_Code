#include <stdio.h>
#include <gmp.h>

#define num_of_data_points 10
#define num_of_features 5
mpz_t DataBase[num_of_data_points][num_of_features];

mpz_t maxRange;
// initilze the state object for the random generator functions
gmp_randstate_t state;

void genRandomDataBase()
{
    FILE *file;
    file = fopen("DataBase.txt", "w");
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < num_of_features; j++)
        {
            // Generate a random matrix containing integer nos. from 0 to maxRange (both inclusive)
            mpz_init(DataBase[i][j]);
            mpz_urandomm(DataBase[i][j], state, maxRange);
            gmp_fprintf(file, "%Zd ", DataBase[i][j]);
        }
        gmp_fprintf(file, "\n");
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
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < num_of_features; j++)
        {
            mpz_clear(DataBase[i][j]);
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

    genRandomDataBase();
    garbageCollection();
    return 0;
}