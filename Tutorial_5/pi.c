#include <stdio.h>
#include <time.h>   // for clock()

static long long num_steps = 100000000;  // 1e8 steps
double step;

int main(void) {
    long long i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double) num_steps;

    clock_t start, end;
    double cpu_time;

    start = clock();   // start measuring

    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    end = clock();   // end measuring

    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("pi is %.15f\n", pi);
    printf("Time taken = %f seconds\n", cpu_time);

    return 0;
}
