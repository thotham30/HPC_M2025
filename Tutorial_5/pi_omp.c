#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double) num_steps;

    // set threads
    omp_set_num_threads(16);

    double start = omp_get_wtime();   // start time

    #pragma omp parallel for private(x) 
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    double end = omp_get_wtime();     // end time

    printf("pi is %.15f\n", pi);
    printf("Time taken = %f seconds with 16 threads\n", end - start);

    return 0;
}
