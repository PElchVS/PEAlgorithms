#include <stdlib.h>
#include <string.h>

#include "pearray.h"

PEARRAY* peArrayCreate(PEARRAY* arrPtr, PESIZE elementSize, PESIZE elementCount)
{
	arrPtr->capacity = elementSize * elementCount;
	arrPtr->elementSize = elementSize;
	arrPtr->elementCount = elementCount;
	arrPtr->buffer = (PEPTRVOID)malloc(arrPtr->capacity);
	return arrPtr;
}

PEARRAY* peArrayCreateEmpty(PEARRAY* arrPtr, PESIZE elementSize)
{
	return peArrayCreate(arrPtr, elementSize, 0);
}

PEARRAY* peArrayDelete(PEARRAY* arrPtr)
{
	arrPtr->elementCount = 0;
	free(arrPtr->buffer);
	return arrPtr;
}

PEARRAY* peArrayAssign(PEARRAY* arrPtrDest, PEARRAY* arrPtrSrc)
{
	if (arrPtrDest->elementCount < arrPtrSrc->elementCount)
	{
		peArrayResize(arrPtrDest, arrPtrSrc->elementCount);
	}
	memcpy(arrPtrDest->buffer, arrPtrSrc->buffer, arrPtrDest->capacity);

	arrPtrDest->elementCount = arrPtrSrc->elementCount;

	return arrPtrDest;
}

PEPTRVOID peArrayAt(PEARRAY* arrPtr, PESIZE index)
{
	return ((PEBYTE*)arrPtr->buffer + index * arrPtr->elementSize);
}

PEPTRVOID peArraySafeAt(PEARRAY* arrPtr, PESIZE index)
{
	if (index >= 0 && index < arrPtr->elementCount)
	{
		return peArrayAt(arrPtr, index);
	}
	return PENULL;
}

PEPTRVOID peArrayFront(PEARRAY* arrPtr)
{
	return arrPtr->buffer;
}

PEPTRVOID peArrayBack(PEARRAY* arrPtr)
{
	return (PEBYTE*)arrPtr->buffer + (arrPtr->elementCount - 1) * arrPtr->elementSize;
}

PEARRAY* peArrayClear(PEARRAY* arrPtr)
{
	peArrayDelete(arrPtr);
	return peArrayCreateEmpty(arrPtr, arrPtr->elementSize);
}

PEARRAY* peArrayInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value)
{
	memcpy(((PEBYTE*)arrPtr->buffer + index * arrPtr->elementSize), value, arrPtr->elementSize);
	return arrPtr;
}

PEARRAY* peArraySafeInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value)
{
	if (index >= 0 && index < (arrPtr->capacity / arrPtr->elementSize))
	{
		return peArrayInsert(arrPtr, index, value);
	}
	return PENULL;
}

PEARRAY* peArrayPushBack(PEARRAY* arrPtr, PEPTRVOID value)
{
	if (arrPtr->elementCount * arrPtr->elementSize >= arrPtr->capacity)
	{
		peArrayResize(arrPtr, (arrPtr->elementCount << 1) + 1);
	}
	return peArrayInsert(arrPtr, arrPtr->elementCount++, value);
	
}

PEARRAY* peArrayResize(PEARRAY* arrPtr, PESIZE size)
{
	PESIZE newCapacity = size * arrPtr->elementSize;
	PEPTRVOID newBuffer = malloc(newCapacity);
	memcpy(newBuffer, arrPtr->buffer, arrPtr->capacity);
	free(arrPtr->buffer);

	arrPtr->capacity = newCapacity;
	arrPtr->buffer = newBuffer;

	return arrPtr;
}