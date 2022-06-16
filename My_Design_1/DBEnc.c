#include <stdio.h>
#include <gmp.h>
#define num_of_data_points 100
#define num_of_features 10
#define eta (num_of_features + 1)
mpf_t inv_matrix[eta][eta];
mpf_t s_vector[num_of_features + 1];
mpf_t DataBase[num_of_data_points][eta];
mpf_t Encrypted_DataBase[num_of_data_points][eta];

mpz_t maxRange;
// initilze the state object for the random generator functions
gmp_randstate_t state;

void readDataBase()
{
    FILE *file;
    file = fopen("DataBase.txt", "r");
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpf_init(DataBase[i][j]);
        }
    }
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < num_of_features; j++)
        {
            gmp_fscanf(file, "%Ff", DataBase[i][j]);
        }
    }
    fclose(file);
}

void readMatrixInvM()
{
    FILE *file;
    file = fopen("InvM.txt", "r");
    for (int i = 0; i < eta; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpf_init(inv_matrix[i][j]);
            gmp_fscanf(file, "%Ff", inv_matrix[i][j]);
        }
    }
    fclose(file);
}

void readVectorS()
{
    FILE *file;
    file = fopen("s.txt", "r");
    for (int i = 0; i <= num_of_features; i++)
    {
        mpf_init(s_vector[i]);
        gmp_fscanf(file, "%Ff", s_vector[i]);
    }
    fclose(file);
}

void modifyDataBase()
{
    mpf_t squaredSum;
    mpf_t square;
    mpf_t temp;
    mpf_init(temp);
    mpf_init(square);

    for (int i = 0; i < num_of_data_points; i++)
    {
        mpf_init_set_si(squaredSum, 0.0);
        for (int j = 0; j < num_of_features; j++)
        {
            mpf_mul(square, DataBase[i][j], DataBase[i][j]);
            mpf_add(squaredSum, squaredSum, square);
            mpf_mul_ui(temp, DataBase[i][j], 2);
            mpf_sub(DataBase[i][j], s_vector[j], temp);
        }
        mpf_add(DataBase[i][num_of_features], s_vector[num_of_features], squaredSum);
    }
    mpf_clear(squaredSum);
    mpf_clear(square);
    mpf_clear(temp);
}

void writeModifiedDataBase()
{
    FILE *file;
    file = fopen("ModifiedDataBase.txt", "w");
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            gmp_fprintf(file, "%Ff ", DataBase[i][j]);
        }
        gmp_fprintf(file, "\n");
    }
    fclose(file);
}

void sendEncryptedDataBaseToCloud()
{
    FILE *file;
    file = fopen("EncryptedDataBase.txt", "w");
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            gmp_fprintf(file, "%Ff ", Encrypted_DataBase[i][j]);
        }
        gmp_fprintf(file, "\n");
    }
    fclose(file);
}

void multiplyWithMInverse()
{
    mpf_t temp;
    mpf_init(temp);
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpf_init_set_si(Encrypted_DataBase[i][j], 0);
            for (int k = 0; k < eta; k++)
            {
                mpf_mul(temp, DataBase[i][k], inv_matrix[k][j]);
                mpf_add(Encrypted_DataBase[i][j], Encrypted_DataBase[i][j], temp);
            }
        }
    }
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
        for (int j = 0; j < eta; j++)
        {
            mpf_clear(DataBase[i][j]);
            mpf_clear(Encrypted_DataBase[i][j]);
        }
    }
    for (int i = 0; i < eta; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpf_clear(inv_matrix[i][j]);
        }
    }
    for (int i = 0; i <= num_of_features; i++)
    {
        mpf_clear(s_vector[i]);
    }
}

int main()
{
    unsigned long seed;
    mpz_init_set_si(maxRange, 9);

    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);

    // Reading DataBase and Secret Keys From Files
    readDataBase();
    readMatrixInvM();
    readVectorS();

    // Modify DataBase
    modifyDataBase();
    writeModifiedDataBase();

    // Permute DataBase
    // permuteDataBase();     TODO

    // Encrypt DataBase with M inverse
    multiplyWithMInverse();
    sendEncryptedDataBaseToCloud();
    garbageCollection();
    return 0;
}
