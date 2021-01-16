// Є дійсна квадратна матриця A порядку N. Знайти дійсну квадратну
// матрицю B порядку N, кожний з елементів якої дорівнює сумі
// елементів матриці A у відповідній заштрихованій області, що
// визначена індексами i, j:

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matrix_sum(const int *array, int row, int col, int N);

int main() {

    int N, i=0, j=0, x=0, y=0;
    int *ptr;

    puts("Please enter the rank of matrix:");
    scanf("%d", &N);
    puts("Please enter i and j:");
    scanf("%d %d", &i, &j);

    while ((i || j) > N) {
        puts("Please re-enter i and j (should be <= N):");
        scanf("%d %d", &i, &j);
    }

    int A[N][N];

    srand(time(NULL));
    for (x=0;x<N;x++) {
        for (y=0;y<N;y++) {
            A[x][y]=rand()%10;
            printf("%d ", A[x][y]);
        }
        printf("\n");
    }
    printf("\n");

    ptr=&A[0][0];

    int element;

    element = matrix_sum(ptr, i, j, N);

    int B[N][N];
    for (x=0;x<N;x++) {
        for (y=0;y<N;y++) {
            B[x][y] = element;
            printf("%d ", B[x][y]);
        }
        printf("\n");
    }
    printf("\n");
    return (0);
}

int matrix_sum(const int *array, int row, int col, int N) {
    int x, y, sum=0;

    for (x=0;x<row;x++) {
        for (y=0;y<col;y++) {
            sum = sum + *(array + (x*N)+y);
        }
    }
    return (sum);
}