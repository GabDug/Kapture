#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int **generateArray(int x, int y);

int deleteArray(int **array, int x);

void displayArray(int **array, int x, int y);

int main() {
    int **board_ptr = generateArray(10, 10);
    printf("PT1 : %d\n", (int) board_ptr);
    displayArray(board_ptr, 10, 10);

//    deleteArray(board_ptr, 20);
    return 0;
}


int **generateArray(int x, int y) {
    /* With VLA and C99:
    int array[x][y];
    int a = (int) &array;
    return a;*/

    int i, j;
    int **T;

    T = (int **) malloc(x * sizeof(int *));

    for (i = 0; i < x; i++)
        T[i] = (int *) malloc(x * sizeof(int));

    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++)
            T[i][j] = 0;

    return T;
}

void displayArray(int **array, int x, int y) {
    int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++)
            printf("%d", array[i][j]);
        printf("\n");
    }
}

int deleteArray(int **array, int x) {
    int i;
    for (i = 0; i < x; i++)
        free(array[i]);
    free(array);
}


