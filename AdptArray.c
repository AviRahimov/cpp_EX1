#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// create a struct for Dynamic array
typedef struct AdptArray_{
    int ArrSize;
    PElement *pElementArr;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,
                           PRINT_FUNC printFunc){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    // This is the case when the allocation wasn't succeed
    if(pArr == NULL){
        return NULL;
    }
    // Initiate the variables of the array
    pArr->ArrSize = 0;
    pArr->pElementArr = NULL;
    pArr->copyFunc = copyFunc;
    pArr->delFunc = delFunc;
    pArr->printFunc = printFunc;
    return pArr;
}

// Deleting all the array with all elements inside
void DeleteAdptArray(PAdptArray pArr){
    if(pArr == NULL){
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i) {
        if(pArr->pElementArr[i] != NULL)
            pArr->delFunc((pArr->pElementArr)[i]);
    }
    free(pArr->pElementArr);
    free(pArr);
}

// splitting into 2 cases and save a copy of the element specifies as input and insert it into the array
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElement){
    PElement* newpElement;
    if(pArr == NULL){
        return FAIL;
    }
    // handling with the case when the index specified is greater than the array size so, we need to extend the array
    if(idx >= pArr->ArrSize){
        if ((newpElement = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElement, pArr->pElementArr, (pArr->ArrSize) * sizeof(PElement));
        if(pArr->pElementArr != NULL)
            free(pArr->pElementArr);
        pArr->pElementArr = newpElement;
    }

    // Delete Previous Elem
    if(pArr->pElementArr[idx]!=NULL)
        pArr->delFunc((pArr->pElementArr)[idx]);
    (pArr->pElementArr)[idx] = pArr->copyFunc(pNewElement);
    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

// getting the copy of the element that exists in idx index of the array
PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if(idx>=pArr->ArrSize)
        return NULL;
    if(pArr->pElementArr[idx]==NULL)
        return NULL;
    PElement cpy = pArr->copyFunc((pArr->pElementArr)[idx]);
    return cpy;
}

// returning the size of the array
int GetAdptArraySize(PAdptArray arr) {
    if(arr==NULL)
        return -1;
    return arr->ArrSize;
}

//printing all elements in the array with the help of the function: printFunc
void PrintDB(PAdptArray pArr){
    if(pArr == NULL){
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i) {
        if(pArr->pElementArr[i]!=NULL)
            pArr->printFunc(pArr->pElementArr[i]);
    }
}