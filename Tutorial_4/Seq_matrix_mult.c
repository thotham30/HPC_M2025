#include<stdio.h>
#include<time.h>

int main(){

    int n;
    printf("Enter the order of the matrix: ");
    scanf("%d",&n);
    
    long A[n][n];
    long x[n];
    long y[n];

    clock_t start = clock();

    int ran_var_a = 1;
    printf("Matrix A %dx%d :\n", n, n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            A[i][j] = ran_var_a;
            ran_var_a++;
        }
    }

    int ran_var_x = 3;
    printf("matrix x %dx1 :\n", n);
    for(int i=0; i<n; i++){
        x[i] = ran_var_x;
        ran_var_x = (ran_var_x*2) - (ran_var_x%4);
    }



    for(int i=0; i<n; i++){
        y[i] = 0;
        for(int j=0; j<n; j++){
            y[i] += (long)A[i][j] * x[j];
        }
    }

    clock_t end = clock();

    double execution_time = (double)(end - start)/CLOCKS_PER_SEC;

    printf("time_seq = %f\n", execution_time);

    printf("The resultant matrix y  :\n");
    for(int i=0; i<n; i++){
        printf("%ld\n", y[i]);
    }

    printf("time_seq = %f\n", execution_time);

    return 0;
}