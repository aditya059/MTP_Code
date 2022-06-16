/*
 * Copyright (C) 2011-2021 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Enclave.h"
#include "Enclave_t.h" /* print_string */
#include <stdarg.h>
#include <stdio.h> /* vsnprintf */
#include <string.h>
#include <stdlib.h>

#define num_of_data_points 100
#define num_of_features 10
#define eta (num_of_features + 1)
#define l 5
#define n (eta + l)

/*
 * printf:
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

typedef struct
{
    int index;
    double distance;
} Node;

double Encrypted_DB[num_of_data_points][eta];
double inv_W[n][n];
double Encrypted_Query[n];
double Double_Encrypted_Query[n];
double dist;
int k;

Node node[num_of_data_points];

void decryptDoubleEncryptedQuery()
{
    double temp;
    for (int i = 0; i < n; i++)
    {
        Encrypted_Query[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            temp = inv_W[i][j] * Double_Encrypted_Query[j];
            Encrypted_Query[i] = Encrypted_Query[i] + temp;
        }
    }
}

void calc_distance()
{
    double temp;
    for (int i = 0; i < num_of_data_points; i++)
    {
        node[i].index = i;
        node[i].distance = 0.0;
        for (int j = 0; j < eta; j++)
        {
            temp = Encrypted_DB[i][j] * Encrypted_Query[j];
            node[i].distance = node[i].distance + temp;
        }
        // printf("%d %d %f\n", i, node[i].index, node[i].distance);
    }
}

// Function to swap the the position of two elements
void swap(Node *a, Node *b)
{
    int data = a->index;
    a->index = b->index;
    b->index = data;
    dist = a->distance;
    a->distance = b->distance;
    b->distance = dist;
}

void heapify(int N, int i)
{
    // Find smallest among root, left child and right child
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && node[left].distance < node[smallest].distance)
        smallest = left;

    if (right < N && node[right].distance < node[smallest].distance)
        smallest = right;

    // Swap and continue heapifying if root is not smallest
    if (smallest != i)
    {
        swap(&node[i], &node[smallest]);
        heapify(N, smallest);
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

void ecall_computeKNN(int result[], double A[], double B[], double C[], size_t DB_size, size_t N, size_t W_size, size_t numOfKNN)
{
    k = numOfKNN;

    int c = 0;
    for (int i = 0; i < num_of_data_points; i++)
    {
        for (int j = 0; j < eta; j++)
        {
            Encrypted_DB[i][j] = A[c++];
        }
    }

    for (int i = 0; i < n; i++)
    {
        Double_Encrypted_Query[i] = B[i];
    }

    c = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inv_W[i][j] = C[c++];
        }
    }

    decryptDoubleEncryptedQuery();
    calc_distance();
    heapSort();
    for (int i = 0; i < k; i++)
    {
        result[i] = node[num_of_data_points - i - 1].index;
    }
}
