#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matrix {
    int n;             // ����������� ������� (n x n)
    int* data;         // ��������� �� ������ ���������� ������
    HANDLE heapHandle; // ���������� ����, �� ������� ���������� ������
};



// ��������� ������ ��� �������
struct Matrix* AllocateMatrix(int n, HANDLE heapHandle) {
    if (n <= 0) {
        printf("������: ����������� ������� ������ ���� �������������.\n");
        return NULL;
    }

    if (heapHandle == NULL) {
        heapHandle = GetProcessHeap();
        if (heapHandle == NULL) {
            printf("������: �� ������� �������� ���������� ���� ��������.\n");
            return NULL;
        }
    }

    // ��������� ������ ��� ������ �������
    int* allocatedMemory = (int*)HeapAlloc(heapHandle, HEAP_ZERO_MEMORY, n * n * sizeof(int));
    if (allocatedMemory == NULL) {
        printf("������: �� ������� �������� ������ ��� ������� �������� %dx%d.\n", n, n);
        return NULL;
    }

    // ��������� ������ ��� ��������� Matrix
    struct Matrix* matrix = (struct Matrix*)malloc(sizeof(struct Matrix));
    if (matrix == NULL) {
        printf("������: �� ������� �������� ������ ��� ��������� Matrix.\n");
        HeapFree(heapHandle, 0, allocatedMemory);
        return NULL;
    }

    matrix->n = n;
    matrix->data = allocatedMemory;
    matrix->heapHandle = heapHandle;

    printf("������ ��� ������� %dx%d ������� ��������.\n", n, n);
    return matrix;
}

// ������������ ������ �������
void FreeMatrix(struct Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }

    if (matrix->data != NULL) {
        if (!HeapFree(matrix->heapHandle, 0, matrix->data)) {
            printf("��������������: �� ������� ���������� ������ ��� ������ �������.\n");
        }
        else {
            printf("������ ��� ������ ������� ������� �����������.\n");
        }
        matrix->data = NULL;
    }

    free(matrix);
    printf("��������� Matrix ������� �����������.\n");
}

// ���������������� �������
void transposeMatrix(struct Matrix* matrix) {
    if (matrix == NULL || matrix->data == NULL || matrix->n <= 1) {
        printf("������� �� �������� ������\n");
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

// ����� �������
void printMatrix(const struct Matrix* matrix) {
    if (matrix == NULL || matrix->data == NULL) {
        printf("������� ������\n");
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

// ���������� ������� 
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
