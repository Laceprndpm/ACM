#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 10000

// --- 排序算法实现 ---

// 1. 直接插入排序
void insertionSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

// 2. 折半插入排序
void binaryInsertionSort(int arr[], int n)
{
    int i, j, low, high, mid, temp;
    for (i = 1; i < n; i++) {
        temp = arr[i];
        low  = 0;
        high = i - 1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (temp < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i - 1; j >= low; j--) arr[j + 1] = arr[j];
        arr[low] = temp;
    }
}

// 3. 希尔排序
void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 4. 冒泡排序
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp   = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 5. 快速排序
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int i = low, j = high, pivot = arr[low];
        while (i < j) {
            while (i < j && arr[j] >= pivot) j--;
            if (i < j) arr[i++] = arr[j];
            while (i < j && arr[i] <= pivot) i++;
            if (i < j) arr[j--] = arr[i];
        }
        arr[i] = pivot;
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}

// 6. 简单选择排序
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        int temp    = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i]      = temp;
    }
}

// 7. 归并排序辅助函数
void merge(int arr[], int l, int m, int r)
{
    int  n1 = m - l + 1, n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 用于qsort的比较函数
int compareInt(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

// --- 主测试程序 ---

int main()
{
    int     A[MAX_SIZE], tempArr[MAX_SIZE];
    clock_t start, end;

    // 1. 随机生成数据
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++) {
        A[i] = rand() % 10000;
    }

    // 定义排序函数指针和名称，方便循环调用
    const char *names[] = {"直接插入", "折半插入", "希尔排序", "冒泡排序", "简单选择",
                           "快速排序", "归并排序", "qsort",    "sort"};

    for (int i = 0; i < 9; i++) {
        memcpy(tempArr, A, sizeof(A));  // 恢复原始随机数组

        start = clock();
        if (i == 0)
            insertionSort(tempArr, MAX_SIZE);
        else if (i == 1)
            binaryInsertionSort(tempArr, MAX_SIZE);
        else if (i == 2)
            shellSort(tempArr, MAX_SIZE);
        else if (i == 3)
            bubbleSort(tempArr, MAX_SIZE);
        else if (i == 4)
            selectionSort(tempArr, MAX_SIZE);
        else if (i == 5)
            quickSort(tempArr, 0, MAX_SIZE - 1);
        else if (i == 6)
            mergeSort(tempArr, 0, MAX_SIZE - 1);
        else if (i == 7)
            qsort(tempArr, MAX_SIZE - 1, 4, compareInt);
        else if (i == 8)
            std::sort((int *)tempArr, (int *)tempArr + MAX_SIZE - 1);
        end = clock();

        printf("%s耗时: %.2f ms\n", names[i], (double)(end - start) * 1000 / CLOCKS_PER_SEC);
    }

    return 0;
}

