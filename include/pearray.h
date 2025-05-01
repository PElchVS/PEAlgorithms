#ifndef PE_ARRAY_H_
#define PE_ARRAY_H_

#include "petypes.h"

typedef struct pearray
{
	PESIZE capacity;
	PESIZE elementSize;
	PESIZE elementCount;
	PEPTRVOID buffer;
}PEARRAY;

PEARRAY* peArrayCreate(PEARRAY* arrPtr, PESIZE elementSize, PESIZE elementCount);
PEARRAY* peArrayCreateEmpty(PEARRAY* arrPtr, PESIZE elementSize);
PEARRAY* peArrayDelete(PEARRAY* arrPtr);

PEARRAY* peArrayAssign(PEARRAY* arrPtrDest, PEARRAY* arrPtrSrc);

PEPTRVOID peArrayAt(PEARRAY* arrPtr, PESIZE index);
PEPTRVOID peArraySafeAt(PEARRAY* arrPtr, PESIZE index);
PEPTRVOID peArrayFront(PEARRAY* arrPtr);
PEPTRVOID peArrayBack(PEARRAY* arrPtr);

PEARRAY* peArrayClear(PEARRAY* arrPtr);
PEARRAY* peArrayInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value);
PEARRAY* peArraySafeInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value);
PEARRAY* peArrayPushBack(PEARRAY* arrPtr, PEPTRVOID value);

PEARRAY* peArrayResize(PEARRAY* arrPtr, PESIZE size);

#endif
