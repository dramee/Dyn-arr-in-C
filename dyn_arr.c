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
    if ((arr->len + 1) > arr->cap) {
        if (arr->cap == 0) {
            arr->cap = 1;
        } else {
            arr->cap *= 2;
        }
        arr->start = (int*) realloc(arr->start, sizeof(int) * arr->cap);
        nullCheck(arr->start);
    }
    arr->start[arr->len++] = num;
}


void dynArrDelTail(dynArr* arr) {
    if (arr->len > 0) {
        arr->len--;
        if (arr->len <= (arr->cap / 4)) {
            arr->cap /= 2;
            arr->start = (int *) realloc(arr->start, sizeof(int) * arr->cap);
            nullCheck(arr->start);
        }
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

int getElementDynArr(dynArr arr, size_t i){
    if (i < arr.len) {
        return arr.start[i];
    }
    else {
        printf("Index out of range");
        exit(1);
    }
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
    printf("%d\n\n", getElementDynArr(arr, 3));
    while (arr.len > 2) {
        dynArrDelTail(&arr);
        printDynArrInfo(arr);
        printf("\n");
        printDynArr(arr);
    }
    freeDynArr(arr);
    return 0;
}