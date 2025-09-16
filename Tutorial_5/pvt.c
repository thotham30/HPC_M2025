#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 1000; i++) {
        sum += i;   // each thread keeps a private copy, then reduced
    }

    printf("Private+Reduction sum = %d\n", sum);
    return 0;
}
