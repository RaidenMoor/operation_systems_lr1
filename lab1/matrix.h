#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matrix {
    int n;             // Размерность матрицы (n x n)
    int* data;         // Указатель на начало выделенной памяти
    HANDLE heapHandle; // Дескриптор кучи, из которой выделялась память
};



// Выделение памяти для матрицы
struct Matrix* AllocateMatrix(int n, HANDLE heapHandle) {
    if (n <= 0) {
        printf("Ошибка: Размерность матрицы должна быть положительной.\n");
        return NULL;
    }

    if (heapHandle == NULL) {
        heapHandle = GetProcessHeap();
        if (heapHandle == NULL) {
            printf("Ошибка: Не удалось получить дескриптор кучи процесса.\n");
            return NULL;
        }
    }

    // Выделение памяти для данных матрицы
    int* allocatedMemory = (int*)HeapAlloc(heapHandle, HEAP_ZERO_MEMORY, n * n * sizeof(int));
    if (allocatedMemory == NULL) {
        printf("Ошибка: Не удалось выделить память для матрицы размером %dx%d.\n", n, n);
        return NULL;
    }

    // Выделение памяти для структуры Matrix
    struct Matrix* matrix = (struct Matrix*)malloc(sizeof(struct Matrix));
    if (matrix == NULL) {
        printf("Ошибка: Не удалось выделить память для структуры Matrix.\n");
        HeapFree(heapHandle, 0, allocatedMemory);
        return NULL;
    }

    matrix->n = n;
    matrix->data = allocatedMemory;
    matrix->heapHandle = heapHandle;

    printf("Память для матрицы %dx%d успешно выделена.\n", n, n);
    return matrix;
}

// Освобождение памяти матрицы
void FreeMatrix(struct Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }

    if (matrix->data != NULL) {
        if (!HeapFree(matrix->heapHandle, 0, matrix->data)) {
            printf("Предупреждение: Не удалось освободить память для данных матрицы.\n");
        }
        else {
            printf("Память для данных матрицы успешно освобождена.\n");
        }
        matrix->data = NULL;
    }

    free(matrix);
    printf("Структура Matrix успешно освобождена.\n");
}

// Транспонирование матрицы
void transposeMatrix(struct Matrix* matrix) {
    if (matrix == NULL || matrix->data == NULL || matrix->n <= 1) {
        printf("Матрица не содержит данных\n");
        return;
    }

    int n = matrix->n;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int temp = matrix->data[i * n + j];
            matrix->data[i * n + j] = matrix->data[j * n + i];
            matrix->data[j * n + i] = temp;
        }
    }
}

// Вывод матрицы
void printMatrix(const struct Matrix* matrix) {
    if (matrix == NULL || matrix->data == NULL) {
        printf("Матрица пустая\n");
        return;
    }

    int n = matrix->n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d ", matrix->data[i * n + j]);
        }
        printf("\n");
    }
}

// Заполнение матрицы 
void fillMatrixRandom(struct Matrix* matrix) {
    if (matrix == NULL || matrix->data == NULL) {
        return;
    }

    int n = matrix->n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix->data[i * n + j] = rand() % 100;
        }
    }
}
