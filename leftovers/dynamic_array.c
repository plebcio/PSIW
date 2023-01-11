#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

// my implementation of a dynamic array
// bacause it will be helpful for tracking process state


void initArr(DynamicArr* arr){
    // like in python, base size for dynamic array is 8
    arr->size = 0;
    arr->capacity = 8;
    arr->vals = malloc(8*sizeof(int));
    memset(arr->vals, 0, 8);
}

void freeArr(DynamicArr* arr){
    free(arr->vals);
    free(arr);
}

void ArrAppend(DynamicArr* arr, int val){
    if (arr->size + 1 <= arr->capacity){
        arr->vals[arr->size] = val;
        arr->size++;
        return;
    }

    // grow arr
    arr->vals = realloc(arr->vals, arr->capacity*2);
    arr->vals[arr->size] = val;
    arr->size++;

}


