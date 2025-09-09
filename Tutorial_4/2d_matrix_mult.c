#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <math.h>

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
            A[i][j] = ran_var_a++;
        }
    }

    int ran_var_x = 3;
    for (int i = 0; i < n; i++) {
        x[i] = ran_var_x;
        ran_var_x = (ran_var_x * 2) - (ran_var_x % 4);
        y[i] = 0;   // initialize result vector
    }

    double start = omp_get_wtime();

    // 2D Partitioning with OpenMP + local accumulation
    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id   = omp_get_thread_num();

        int grid_size   = (int)sqrt(num_threads);
        if (grid_size * grid_size > num_threads) grid_size--;

        int block_size  = (n + grid_size - 1) / grid_size; // ceil division

        int row_block = thread_id / grid_size;
        int col_block = thread_id % grid_size;

        int row_start = row_block * block_size;
        int row_end   = (row_block + 1) * block_size;
        if (row_end > n) row_end = n;

        int col_start = col_block * block_size;
        int col_end   = (col_block + 1) * block_size;
        if (col_end > n) col_end = n;

        // Local storage to avoid atomics
        long local_y[n];
        for (int i = 0; i < n; i++) local_y[i] = 0;

        // Debug info
        #pragma omp critical
        printf("Thread %d handles rows %d–%d, cols %d–%d\n",
               thread_id, row_start, row_end - 1, col_start, col_end - 1);

        // Compute partial results
        for (int i = row_start; i < row_end; i++) {
            long temp = 0;
            for (int j = col_start; j < col_end; j++) {
                temp += A[i][j] * x[j];
            }
            local_y[i] = temp;
        }

        // Reduction phase
        #pragma omp critical
        {
            for (int i = row_start; i < row_end; i++) {
                y[i] += local_y[i];
            }
        }
    }

    double end = omp_get_wtime();
    double execution_time = end - start;

    printf("The resultant matrix y:\n");
    for (int i = 0; i < n; i++) {
        printf("%ld\n", y[i]);
    }

    printf("time_2d_parallel = %f\n", execution_time);

    return 0;
}
