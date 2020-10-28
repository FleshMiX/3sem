#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/sysinfo.h>
#include <pthread.h>


struct Matrix
{
    int m, n;
    double* matrix;
};

void GenerateMatrix(struct Matrix* matrix)
{
    matrix->matrix = (double*)calloc((matrix->n) * (matrix->m), sizeof(double));
    for (int i = 0; i < matrix->n * matrix->m; i++) {
        *(matrix->matrix + i) = rand() % 10;
    }
}

struct Matrix MatrixMultiplication(struct Matrix a, struct Matrix b)
{
    assert(a.m == b.n);
    struct Matrix result;
    result.n = a.n;
    result.m = b.m;

    result.matrix = (double*)calloc(result.n * result.m, sizeof(double));

    for (int i = 0; i < result.m; i++) 
        for (int j = 0; j < result.n; j++)
            for (int i = 0; i < a.m; i++)
                *(result.matrix + j * result.n + i) += *(a.matrix + a.n * i + i) * *(b.matrix + b.n * j + i);
    return result;
}

void PrintMatrix(struct Matrix matrix)
{
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++)
            printf("%lg ", *(matrix.matrix + j * matrix.n + i));
        printf("\n");
    }
}

struct ThreadMultData
{
    struct Matrix *a, *b, *result;

    size_t m_start, m_end;

    pthread_t pthid;
};

void* Separate(void* data)
{
    struct ThreadMultData* dt = (struct ThreadMultData*)data;
    for (size_t i = dt->m_start; i < dt->m_end; i++) 
        for (size_t j = 0; j < dt->result->n; j++)
            for (size_t i = 0; i < dt->a->m; i++)
                dt->result->matrix[j * dt->result->n + i] += dt->a->matrix[dt->a->n * i + i] * dt->b->matrix[dt->b->n * j + i];

    return NULL;
}

struct Matrix MatrixMultThread(struct Matrix a, struct Matrix b)
{
    assert(a.m == b.n);
    struct Matrix result;
    result.n = a.n;
    result.m = b.m;

    result.matrix = (double*)calloc(result.n * result.m, sizeof(double));

    size_t cores = get_nprocs() * 2;
    //printf("cores: %d\n", cores);

    struct ThreadMultData* data = (struct ThreadMultData*)calloc(cores, sizeof(struct ThreadMultData));

    size_t base_len = result.m / cores;
    if (result.m % cores != 0)
        base_len++;
    size_t buf = result.m;

    for (size_t i = 0; i < cores; i++) {
        data[i].a = &a;
        data[i].b = &b;
        data[i].result = &result;

        data[i].m_end = buf;
        buf -= base_len;
        if (buf <= 0) {
            data->m_start = 0;
        }
        data[i].m_start = buf;

        pthread_create(&data[i].pthid, NULL, Separate, &data[i]);
        //printf("Thread %i: from %d to %d\n", i, data[i].m_start, data[i].m_end);
        if (buf <= 0)
            break;
    }

    for(size_t i = 0; i < cores; i++)
        pthread_join(data[i].pthid, NULL);

    return result;
}

int main() {
    struct Matrix a, b, c;
    a.m = a.n = b.m = b.n = 1000;

    GenerateMatrix(&a);
    GenerateMatrix(&b);

    clock_t t = clock();
    c = MatrixMultiplication(a, b);
    t = clock() - t;

    printf("%d clicks ::%f mls\n", (int)t, ((double)t)/ CLOCKS_PER_SEC * 1000.f);

    t = clock();
    c = MatrixMultThread(a, b);
    t = clock() - t;

    printf("%d clicks ::%f mls\n", (int)t, ((double)t)/ CLOCKS_PER_SEC * 1000.f);

   // PrintMatrix(a);
    //PrintMatrix(b);
    //PrintMatrix(c);
}
