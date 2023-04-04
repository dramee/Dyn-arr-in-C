#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* start;
    size_t len;
    size_t cap;
} dynArr;

void dynArrInit(dynArr* arr) {
    arr->start = NULL;
    arr->len = 0;
    arr->cap = 0;
}

void nullCheck(void* ptr){ // check reallocate return for NULL
    if (!(ptr)) {
        printf("Out of memory");
        exit(1);
    }
}

void dynArrAddTail(dynArr* arr, int num) {
    if (arr->cap == 0) {
        arr->cap = 1;
        arr->start = (int*) realloc(arr->start, sizeof(int) * arr->cap);
        nullCheck(arr->start);
        arr->start[arr->len++] = num;
    }
    else {
        if ((arr->len + 1) > arr->cap) {
            arr->cap *= 2;
            arr->start = (int*) realloc(arr->start, sizeof(int) * arr->cap);
            nullCheck(arr->start);
        }
        arr->start[arr->len++] = num;
    }
}

void dynArrDelTail(dynArr* arr) {
    arr->len--;
    if (arr->len <= (arr->cap / 4)) {
        arr->cap /= 2;
        arr->start = (int*) realloc(arr->start, sizeof(int) * arr->cap);
    }
}

void printDynArr(dynArr arr) {
    for (size_t i = 0; i < arr.len; i++) {
        printf("%d ", arr.start[i]);
        printf(" ");
    }
    printf("\n");
}

void freeDynArr(dynArr arr){
    free(arr.start);
}

void printDynArrInfo(dynArr arr){
    printf("%p\n", arr.start);
    printf("%zu\n", arr.len);
    printf("%zu\n", arr.cap);
}



int main() {
    dynArr arr;
    dynArrInit(&arr);
    int num = 1;
    while (num != 0) {
        scanf("%d", &num);
        dynArrAddTail(&arr, num);
        printDynArrInfo(arr);
        printf("\n");
        printDynArr(arr);
    }
    while (arr.len > 2) {
        dynArrDelTail(&arr);
        printDynArrInfo(arr);
        printf("\n");
        printDynArr(arr);
    }
    freeDynArr(arr);
    return 0;
}