#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#define num_of_data_points 100000
#define num_of_features 100
#define c 2
#define epsilon 2
#define eta (num_of_features + 1 + c + epsilon)
int k = 10;

typedef struct
{
    int index;
    mpf_t distance;
} Node;

mpf_t Encrypted_DB[num_of_data_points][eta];
mpf_t Encrypted_Query[eta];

mpf_t dist;
mpz_t maxRange;
// initilze the state object for the random generator functions
gmp_randstate_t state;

Node node[num_of_data_points];

void readEncryptedDB()
{
    FILE *file;
    file = fopen("EncryptedDataBase.txt", "r");
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            mpf_init(Encrypted_DB[i][j]);
            gmp_fscanf(file, "%Ff", Encrypted_DB[i][j]);
        }
    }
    fclose(file);
}

void readEncryptedQuery()
{
    FILE *file;
    file = fopen("finalDecryptedQuery.txt", "r");
    for (int i = 0; i < eta; i++)
    {
        mpf_init(Encrypted_Query[i]);
        gmp_fscanf(file, "%Ff", Encrypted_Query[i]);
    }
    fclose(file);
}

void calc_distance()
{
    mpf_t temp;
    mpf_init(temp);
    for (int i = 0; i < num_of_data_points; i++)
    {
        node[i].index = i;
        mpf_init_set_si(node[i].distance, 0.0);
        for (int j = 0; j < eta; j++)
        {
            mpf_mul(temp, Encrypted_DB[i][j], Encrypted_Query[j]);
            mpf_add(node[i].distance, node[i].distance, temp);
        }
    }
    mpf_clear(temp);
}

// Function to swap the the position of two elements
void swap(Node *a, Node *b)
{
    int data = a->index;
    a->index = b->index;
    b->index = data;
    mpf_set(dist, a->distance);
    mpf_set(a->distance, b->distance);
    mpf_set(b->distance, dist);
}

void heapify(int n, int i)
{
    // Find smallest among root, left child and right child
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && mpf_cmp(node[left].distance, node[smallest].distance) < 0)
        smallest = left;

    if (right < n && mpf_cmp(node[right].distance, node[smallest].distance) < 0)
        smallest = right;

    // Swap and continue heapifying if root is not smallest
    if (smallest != i)
    {
        swap(&node[i], &node[smallest]);
        heapify(n, smallest);
    }
}

// Main function to do heap sort
void heapSort()
{
    // Build min heap
    for (int i = num_of_data_points / 2 - 1; i >= 0; i--)
        heapify(num_of_data_points, i);

    // Heap sort
    int count = 0;
    for (int i = num_of_data_points - 1; count < k && i >= 0; i--)
    {
        swap(&node[0], &node[i]);

        // Heapify root element to get smallest element at root again
        heapify(i, 0);
        count++;
    }
}

void returnTopK()
{
    heapSort();
    FILE *file;
    file = fopen("TopK.txt", "w");
    for (int i = 0; i < k; i++)
    {
        gmp_fprintf(file, "%d\n", node[num_of_data_points - i - 1].index);
        // gmp_fprintf(file, "%Ff %d\n", node[num_of_data_points - i - 1].distance, node[num_of_data_points - i - 1].index);
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
        for (int j = 0; j < eta; j++)
        {
            mpf_clear(Encrypted_DB[i][j]);
        }
    }
    for (int i = 0; i < eta; i++)
    {
        mpf_clear(Encrypted_Query[i]);
    }
    for (int i = 0; i < num_of_data_points; i++)
    {
        mpf_clear(node[i].distance);
    }
    mpf_clear(dist);
}

// Reference: https://stackoverflow.com/questions/30942413/c-gmp-generating-random-number
int main()
{
    unsigned long seed;
    mpz_init_set_si(maxRange, 99);
    mpf_init(dist);

    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(state);
    // create the generator seed for the random engine to reference
    gmp_randseed_ui(state, seed);

    readEncryptedDB();
    readEncryptedQuery();
    calc_distance();
    returnTopK();
    garbageCollection();

    return 0;
}