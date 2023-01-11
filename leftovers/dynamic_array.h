#ifndef _DYNAMIC_ARR_H_
#define _DYNAMIC_ARR_H_

typedef struct {
    int capacity;
    int size;
    int* vals;
} DynamicArr;

void initArr(DynamicArr* arr);
void freeArr(DynamicArr* arr);
void ArrAppend(DynamicArr* arr, int val);


#endif