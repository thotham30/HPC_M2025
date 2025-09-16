#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel for shared(sum)
    for (int i = 0; i < 1000; i++) {
        sum += i;   // all threads update the SAME sum (race condition)
    }

    printf("Shared sum = %d\n", sum);
    return 0;
}
