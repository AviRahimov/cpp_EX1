#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <stdlib.h>

// create a struct for Dynamic array
typedef struct AdptArray_{
    int ArrSize;
    PElement *pElementArr;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    // This is the case when the allocation wasn't succeed
    if(pArr == NULL){
        prints("The allocation wasn't made successfully");
        exit(FAIL);
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
        pArr->delFunc(pArr->pElementArr)[i];
    }
    free(pArr->pElementArr);
    free(pArr);
}

// splitting into 2 cases and save a copy of the element specifies as input and insert it into the array
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pElement){
    PElement *newpElement;
    if(pArr == NULL){
        return FAIL;
    }
    // handling with the case when the index specified is greater than the array size so, we need to extend the array
    if(idx >= pArr->ArrSize){
        if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }

    // Delete Previous Elem
    pArr->delFunc((pArr->pElemArr)[idx]);
    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}
// getting the copy of the element that exists in idx index of the array
PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    PElement cpy = pArr->copyFunc((pArr->pElementArr)[idx]);
    return (cpy == NULL) ? NULL : cpy;
}
// returning the size of the array
int GetAdptArraySize(PAdptArray arr) {
    return arr->ArrSize;
}
//printing all elements in the array with the help of the function: printFunc
void PrintDB(PAdptArray pArr){
    if(pArr == NULL){
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i) {
        pArr->printFunc(pArr->pElementArr)[i];
    }
}