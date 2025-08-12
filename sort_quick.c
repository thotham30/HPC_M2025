#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000000   // 1 million elements
#define THRESHOLD 32   // Use insertion sort for partitions smaller than this

// Swap two elements (inline for speed)
static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insertion sort for small partitions
void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Hybrid QuickSort: switches to insertion sort for small partitions
void hybridQuickSort(int arr[], int low, int high) {
    while (low < high) {
        // If the partition size is less than the threshold, use insertion sort
        if (high - low + 1 < THRESHOLD) {
            insertionSort(arr, low, high);
            break;
        } else {
            int pi = partition(arr, low, high);
            // Recur for the smaller half first for optimized stack usage
            if (pi - low < high - pi) {
                hybridQuickSort(arr, low, pi - 1);
                low = pi + 1;
            } else {
                hybridQuickSort(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}

int main() {
    int *arr = (int*)malloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    // Fill array with random integers
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }

    // Measure execution time
    clock_t start, end;
    start = clock();

    hybridQuickSort(arr, 0, SIZE - 1);

    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Hybrid QuickSort of %d elements took %.2f seconds.\n", SIZE, time_taken);

    free(arr);
    return 0;
}
