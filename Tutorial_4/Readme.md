gcc -fopenmp 1d_matrix_mult.c -o 1d_matrix_mult
gcc -fopenmp 2d_matrix_mult.c -o 2d_matrix_mult


Size\Type_method    | sequential | 1-d partition | 2-d partition |

100                 |  84e-6     |  88e-6        |               |
200                 |  234e-6    |  147e-6       |               |
300                 |  491e-6    |  394e-6       |               |
400                 |  937e-6    |  497e-6       |               |
500                 |  1443e-6   |  568e-6       |               |
600                 |  1613e-6   |  685e-6       |               |