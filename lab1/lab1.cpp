#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "matrix.h"


void demonstrateMatrixOperations(int size) {

    struct Matrix* matrix = AllocateMatrix(size, NULL);
    if (matrix == NULL) {
        return;
    }

    fillMatrixRandom(matrix);

    printf("Исходная матрица:\n");
    printMatrix(matrix);

    transposeMatrix(matrix);

    printf("Матрица после транспонирования:\n");
    printMatrix(matrix);

    FreeMatrix(matrix);
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));

    int matrixSize;

    printf("Введите размер матрицы N x N: ");
    if (scanf("%d", &matrixSize) != 1 || matrixSize <= 0) {
        printf("Ошибка: неверный размер матрицы.\n");
        return 1;
    }

    demonstrateMatrixOperations(matrixSize);

    return 0;
}