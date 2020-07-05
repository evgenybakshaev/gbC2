#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int **init2dIntArray(int **array, const int row, const int col){
    array = (int **)calloc(sizeof(int *), row);
    for(int i = 0; i < row; ++i){
        *(array + i) = (int *)calloc(sizeof(int), col);
    }
    return array;
}

void free2dIntArray(int **array, const int row, const int col){

    for(int i = 0; i < row; ++i){
        free(*(array + i));
    }
    free(array);
}

void print2dArray(int **array, const int row, const int col){
    for(int r = 0; r < row; ++r){
        for(int c = 0; c < col; ++c){
            printf("%4d", *(*(array + c)+r));
        }
        printf("\n");
    }
}

void fill2dIntArray(int **array, const int row, const int col){
    int arr[3][3] = {{1,9,2}, {5,7,6}, {4,3,8}};
    for(int r = 0; r < row; ++r){
        for(int c = 0; c < col; ++c){
            *(*(array + c)+r) = arr[r][c];
        }
    }
}

void bubbleSort(int **a, size_t m, size_t n) {
    int tmp;
    size_t i, j, k, jp, ip;
    size_t size = m*n;
    char flag;

    do {
        flag = 0;
        for (k = 1; k < size; k++) {
            //Вычисляем индексы текущего элемента
            j = k / m;
            i = k - j*m;
            //Вычисляем индексы предыдущего элемента
            jp = (k-1) / m;
            ip = (k-1) - jp*m;
            if (a[i][j] > a[ip][jp]) {
                tmp = a[i][j];
                a[i][j] = a[ip][jp];
                a[ip][jp] = tmp;
                flag = 1;
            }
        }
    } while(flag);
}
void bubbleSort2d(int **array, const int row, const int col){
    int t;
    int *cur, *next;
    for(int i = 0; i < row*col; ++i){
        for(int j = 0; j < row*col - 1; ++j){
            cur = *(array + j % col) + j / row;
            next = *(array + (j + 1) % col) + (j + 1) / row;

            if(*cur > *next)
            {
                t = *cur;
                *cur = *next;
               *next = t;
            }
        }
    }
    return;
}

void algorithmTPK(){

  double P[11],tmp;
  int i;

  printf ("\nPlease enter 11 numbers :");

  for (i = 0; i < 11; i++)
    {
      scanf ("%lf", &P[i]);
    }

  printf ("\n\n\nEvaluating f(x) = |x|^0.5 + 5x^3 for the given inputs :");

  for (i = 10; i >= 0; i--)
    {
      tmp = sqrt (fabs (P[i])) + 5 * pow (P[i], 3);

      printf ("\nf(%lf) = ");

      if (tmp > 400.0)
        {
          printf ("Overflow!");
        }

      else
        {
          printf ("%lf", tmp);
        }
    }

    return;
}

int main() {
    const int row = 3;
    const int col = 3;
    int **arr = init2dIntArray(arr, row, col);
    fill2dIntArray(arr,row,col);
    printf("2d Array:\n");
    print2dArray(arr, row, col);
    printf("bubleSort2d:\n");
    bubbleSort2d(arr, col, row);
    print2dArray(arr, row, col);

    algorithmTPK();
    free2dIntArray(arr, row, col);
    return 0;
}
