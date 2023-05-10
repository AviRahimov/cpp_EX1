/**
 * @file AdptArray.c
 * @brief Implementation of a general adaptive array in C language.
 *
 * An adaptive array is an array that changes its size so that any reference to a non-negative index is valid.
 * When you refer to an index where no value has been placed then NULL is returned.
 */

#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief A struct representing an adaptive array.
 *
 * An adaptive array is an array that changes its size so that any reference to a non-negative index is valid.
 * When you refer to an index where no value has been placed then NULL is returned.
 *
 * @param ArrSize The current size of the array.
 * @param pElementArr A pointer to an array of PElement pointers.
 * @param copyFunc A function pointer to a function that copies an element.
 * @param delFunc A function pointer to a function that deletes an element.
 * @param printFunc A function pointer to a function that prints an element.
 */ 
typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElementArr;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
} AdptArray, *PAdptArray;

/**
 * @brief Creates a new adaptive array with given copy, delete, and print functions.
 * @param copyFunc A function to copy an element.
 * @param delFunc A function to delete an element.
 * @param printFunc A function to print an element.
 * @return A pointer to a new adaptive array, or NULL if allocation failed.
 */
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    // This is the case when the allocation wasn't succeed
    if (pArr == NULL)
    {
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

/**
 * @brief Deletes an adaptive array and all elements inside it.
 * @param pArr A pointer to the adaptive array to delete.
 */
void DeleteAdptArray(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i)
    {
        if (pArr->pElementArr[i] != NULL)
            pArr->delFunc((pArr->pElementArr)[i]);
    }
    free(pArr->pElementArr);
    free(pArr);
}

/**
 * @brief Sets an element at the given index in the adaptive array.
 * @param pArr A pointer to the adaptive array.
 * @param idx The index to set.
 * @param pNewElement A pointer to the new element.
 * @return SUCCESS if successful, FAIL otherwise.
 */
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElement)
{
    PElement *newpElement;
    if (pArr == NULL)
    {
        return FAIL;
    }
    // handling with the case when the index specified is greater than the array size so, we need to extend the array
    if (idx >= pArr->ArrSize)
    {
        if ((newpElement = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElement, pArr->pElementArr, (pArr->ArrSize) * sizeof(PElement));
        if (pArr->pElementArr != NULL)
            free(pArr->pElementArr);
        pArr->pElementArr = newpElement;
    }

    // Delete Previous Elem
    if (pArr->pElementArr[idx] != NULL)
        pArr->delFunc((pArr->pElementArr)[idx]);
    (pArr->pElementArr)[idx] = pArr->copyFunc(pNewElement);
    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

/**
 * @brief Gets a copy of the element at the given index in the adaptive array.
 * @param pArr A pointer to the adaptive array.
 * @param idx The index to get.
 * @return A copy of the element at the given index, or NULL if the index is out of range or the element is NULL.
 */
PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
    if (idx >= pArr->ArrSize)
        return NULL;
    if (pArr->pElementArr[idx] == NULL)
        return NULL;
    PElement cpy = pArr->copyFunc((pArr->pElementArr)[idx]);
    return cpy;
}

/**
 * @brief Returns the size of the adaptive array.
 * @param arr A pointer to the adaptive array.
 * @return The size of the adaptive array, or -1 if arr is NULL.
 */
int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
        return -1;
    return arr->ArrSize;
}

/**
 * @brief Prints all elements in the adaptive array using the print function.
 * @param pArr A pointer to the adaptive array.
 */
void PrintDB(PAdptArray pArr)
{
    if (pArr == NULL)
    {
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i)
    {
        if (pArr->pElementArr[i] != NULL)
            pArr->printFunc(pArr->pElementArr[i]);
    }
}