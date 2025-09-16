#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Example function f(i)
int f(int i) {
    return i * i; // square of i
}

int main() {
    int n = 10;
    int *v = (int *)calloc(n, sizeof(int));     // initialize vector with 0
    int *indices = (int *)malloc(n * sizeof(int));

    // Fill indices with unique mapping (identity mapping for demo)
    for (int i = 0; i < n; i++) {
        indices[i] = i;   // unique indices
    }

    // Parallel loop
    #pragma omp parallel for default(none) shared(v, indices, n)
    
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        v[indices[i]] += f(i);
    }

    // Print result
    for (int i = 0; i < n; i++) {
        printf("v[%d] = %d\n", i, v[i]);
    }

    free(v);
    free(indices);
    return 0;
}
