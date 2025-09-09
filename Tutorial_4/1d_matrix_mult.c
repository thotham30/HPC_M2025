#include <stdio.h>
#include <time.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter the order of the matrix: ");
    scanf("%d", &n);

    long A[n][n];
    long x[n];
    long y[n];

    int ran_var_a = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = ran_var_a;
            ran_var_a++;
        }
    }

    int ran_var_x = 3;
    for (int i = 0; i < n; i++) {
        x[i] = ran_var_x;
        ran_var_x = (ran_var_x * 2) - (ran_var_x % 4);
    }

    double start = omp_get_wtime();

    // Parallel region
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int numThreads = omp_get_num_threads();

        // Compute block size and start/end for this thread
        int rows_per_thread = n / numThreads;
        int remainder = n % numThreads;

        int start_row = tid * rows_per_thread + (tid < remainder ? tid : remainder);
        int end_row   = start_row + rows_per_thread + (tid < remainder ? 1 : 0);

        // Print assignment once per thread
        printf("Thread %d processes rows %d to %d\n", tid, start_row, end_row - 1);

        // Perform computation for assigned rows
        for (int i = start_row; i < end_row; i++) {
            y[i] = 0;
            for (int j = 0; j < n; j++) {
                y[i] += (long)A[i][j] * x[j];
            }
        }
    }

    double end = omp_get_wtime();
    double execution_time = (end - start);

     printf("The resultant matrix y  :\n");
    for(int i=0; i<n; i++){
        printf("%ld\n", y[i]);
    }

    printf("time_1d_parallel = %f\n", execution_time);

    return 0;
}
