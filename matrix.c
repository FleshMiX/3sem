#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


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

int main() {
    struct Matrix a, b, c;
    a.m = a.n = b.m = b.n = 10;

    GenerateMatrix(&a);
    GenerateMatrix(&b);

    clock_t t = clock();
    c = MatrixMultiplication(a, b);
    t = clock() - t;

    printf("%d clicks ::%f mls\n", (int)t, ((double)t)/ CLOCKS_PER_SEC * 1000.f);


    PrintMatrix(a);
    PrintMatrix(b);
    PrintMatrix(c);
}
