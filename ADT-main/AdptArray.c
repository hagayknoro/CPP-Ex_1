#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement *pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 1;
	pArr->pElemArr = (PElement*)malloc(sizeof(PElement));
	if (pArr->pElemArr == NULL)
	{
		free(pArr);
		return NULL;
	}
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	// initialization all the arr to by null
	for (int i = 0 ; i < pArr->ArrSize ; i++)
	{
		pArr->pElemArr[i] = NULL;
	}
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; i++)
	{
		if(pArr->pElemArr[i] != NULL){
			pArr->delFunc((pArr->pElemArr)[i]);
		}
	
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{

	if (pArr == NULL)
	{
		return FAIL;
	}

	if (pNewElem == NULL)
	{
		return FAIL;
	}

	if (idx < 0)
	{
		return FAIL;
	}

	if (idx > pArr->ArrSize)
	{
		pArr->pElemArr = (PElement*)realloc(pArr->pElemArr, (idx + 1)*sizeof(PElement));
		if(pArr->pElemArr == NULL){
			return FAIL;}
		// initialization all the new spsce in the arr to by null
		for (int i = pArr->ArrSize ; i <= idx ; i++){
			pArr->pElemArr[i] = NULL;
		}

		pArr->ArrSize = idx + 1;
	}
	//implement element if the indx isnt' empty
	if(pArr->pElemArr[idx] != NULL){
		pArr->delFunc(pArr->pElemArr[idx]);
	}
	pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);

	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int ind){
	//check if the arr is exsist
	if (pArr == NULL)
	{
		return NULL;
	}
	//check if the asked ind is empty 
	if (pArr->pElemArr[ind] == NULL)
	{
		return NULL;
	}
	//chek if the ind is larger then the arr
	if (ind >= pArr->ArrSize)
	{
		return NULL;
	}

	return pArr->copyFunc(pArr->pElemArr[ind]);	
}

int GetAdptArraySize (PAdptArray pArr){
	if (pArr->ArrSize <0)
	{
		return -1;
	
	}
	return pArr->ArrSize;
}



void PrintDB(PAdptArray pArr){
	//check if the arr is exsist
	if (pArr == NULL)
	{
		return;
	}
	for (int i = 0 ; i < pArr->ArrSize ; ++i)
	{
		if(pArr->pElemArr[i] != NULL)
		{
			pArr->printFunc(pArr->pElemArr[i]);
		}
	}
}