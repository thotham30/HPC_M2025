#include <stdio.h>
#include <omp.h>

int main() {
    int sharedVar = 0;

    #pragma omp parallel shared(sharedVar)
    {
        sharedVar += omp_get_thread_num();
    }
    printf("Shared result: %d\n", sharedVar);

    #pragma omp parallel private(sharedVar)
    {
        sharedVar = omp_get_thread_num(); // private copy per thread
        printf("Thread %d privateVar = %d\n",
               omp_get_thread_num(), sharedVar);
    }
}
