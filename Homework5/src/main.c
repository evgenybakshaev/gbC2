#include <stdio.h>
#include <stdlib.h>

void fillArrayRandom(int *array, int size, int max){
    for(int i = 0; i < size; ++i){
        array[i] = rand() % max;
    }
}

void printArray(int *array, int size){
    for(int i = 0; i < size; ++i){
        if((i % 30) == 0)
            printf("\n");
        printf("%2d ", array[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void qSort(int *array, int first, int last){
    int i = first;
    int j = last;
    int m = array[(first + last) / 2];

    do{
        while(array[i] < m) ++i;
        while(array[j] > m) --j;
        if(i <= j){
            swap(&array[i], &array[j]);
            ++i;
            --j;
        }
    }while(i <= j);
    if(i < last) qSort(array, i, last);
    if(j > first) qSort(array, first, j);
}

void insertSort(int *array, int first, int last){
    int tmp, pos;
    for(int i = first + 1; i <= last; ++i){
        tmp = array[i];
        pos = i - 1;
        while(pos >=0 && array[pos] > tmp){
            array[pos + 1] = array[pos];
            --pos;
        }
        array[pos + 1] = tmp;
    }
}

void busketSort(int *array, int len){
    const int max = len;
    const int b = 10;

    int buskets[b][max+1];
    for(int i = 0; i < b; ++i){
        buskets[i][max] = 0;
    }
    for(int digit = 1; digit < 1000000000; digit*=10){
        for(int i = 0; i < max; ++i){
            int d = (array[i] / digit) % b;
            buskets[d][buskets[d][max]++] = array[i];
        }
        int idx = 0;
        for(int i = 0; i < b ; ++i){
            for(int j = 0; j < buskets[i][max]; ++j){
                array[idx++] = buskets[i][j];
            }
            buskets[i][max] = 0;
        }
    }
}

void busketSortEven(int *array, int len){
    const int max = len;
    const int b = 10;

    int buskets[b][max+1];
    for(int i = 0; i < b; ++i){
        buskets[i][max] = 0;
    }
    for(int digit = 1; digit < 1000000000; digit*=10){
        for(int i = 0; i < max; ++i){
            if(array[i] % 2 == 0){
                int d = (array[i] / digit) % b;
                buskets[d][buskets[d][max]++] = array[i];
            }
        }
        int idx = 0;
        for(int i = 0; i < b ; ++i){
            for(int j = 0; j < buskets[i][max]; ++j){
                while(array[idx] % 2 != 0) ++idx;
                array[idx++] = buskets[i][j];
            }
            buskets[i][max] = 0;
        }
    }
}

void qSort2(int *array, int first, int last){

    if((last - first) <= 10) {
        insertSort(array, first, last);
    }
    else{
        int median, min, max;
        int middle = (first + last) / 2;

        if(array[first] > array[middle]){
            min = middle;
            max = first;
        }
        else{
            min = first;
            max = middle;
        }

        if(array[last] < array[min]) median = min;
        else if(array[last] > array[max]) median = max;
        else median = last;

        swap(&array[median], &array[middle]);
        int i = first;
        int j = last;
        int x = array[(first + last) / 2];
        do{
            while(array[i] < x) ++i;
            while(array[j] > x) --j;
            if(i <= j){
                swap(&array[i], &array[j]);
                ++i;
                --j;
            }
        }while(i <= j);
        if(i < last) qSort2(array, i, last);
        if(j > first) qSort2(array, first, j);
    }
}

int main() {
    int SZ = 100;
    int arr[SZ];
    fillArrayRandom(arr, SZ, 101);
    printArray(arr, SZ);

    //qSort(arr, 0, SZ - 1);
    qSort2(arr, 0, SZ - 1);
    printArray(arr, SZ);

    int arr2[] = {0, 2, 8, 3, 4, 6, 5, 9, 8, 2, 7, 3};
    SZ = sizeof(arr2) / sizeof(int);
    printArray(arr2, SZ);
    busketSortEven(arr2, SZ);
    printArray(arr2, SZ);

    return 0;
}
