#include <stdlib.h>
#include <string.h>

#include "pearray.h"

PEARRAY* peArrayCreate(PEARRAY* arrPtr, PESIZE elementSize, PESIZE elementCount)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}	

	arrPtr->capacity = elementSize * elementCount;
	arrPtr->elementSize = elementSize;
	arrPtr->elementCount = elementCount;
	arrPtr->buffer = (PEPTRVOID)malloc(arrPtr->capacity);

	if (!arrPtr->buffer)
	{
		g_PErrorCode = PERROR_MEM_ALLOC_FAULT;
		PERROR_MESSAGE(PERROR_MEM_ALLOC_FAULT_MSG);
		return PENULL;
	}

	return arrPtr;
}

PEARRAY* peArrayCreateEmpty(PEARRAY* arrPtr, PESIZE elementSize)
{
	return peArrayCreate(arrPtr, elementSize, 0);
}

PEARRAY* peArrayDelete(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	arrPtr->capacity = 0;
	arrPtr->elementCount = 0;
	free(arrPtr->buffer);
	return arrPtr;
}

PEARRAY* peArrayAssign(PEARRAY* arrPtrDest, PEARRAY* arrPtrSrc)
{
	if ((!arrPtrDest) || (!arrPtrSrc))
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
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
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	return ((PEBYTE*)arrPtr->buffer + index * arrPtr->elementSize);
}

PEPTRVOID peArraySafeAt(PEARRAY* arrPtr, PESIZE index)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (index >= arrPtr->elementCount)
	{
		g_PErrorCode = PERROR_ARRAY_INDEX_OOB;
		PERROR_MESSAGE(PERROR_ARRAY_INDEX_OOB_MSG);
		return PENULL;
	}

	return peArrayAt(arrPtr, index);
}

PEPTRVOID peArrayFront(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (peArrayIsEmpty(arrPtr))
	{
		return PENULL;
	}

	return arrPtr->buffer;
}

PEPTRVOID peArrayBack(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (peArrayIsEmpty(arrPtr))
	{
		return PENULL;
	}

	return (PEBYTE*)arrPtr->buffer + (arrPtr->elementCount - 1) * arrPtr->elementSize;
}

PEBOOL peArrayIsFull(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	return arrPtr->elementCount * arrPtr->elementSize == arrPtr->capacity;
}

PEBOOL peArrayIsEmpty(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	return arrPtr->elementCount == 0;
}

PESIZE peArraySize(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	
	return arrPtr->elementCount;
}

PESIZE peArrayCapacity(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	return arrPtr->capacity;
}


PEARRAY* peArrayClear(PEARRAY* arrPtr)
{
	peArrayDelete(arrPtr);
	return peArrayCreateEmpty(arrPtr, arrPtr->elementSize);
}

PEARRAY* peArrayInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	memcpy(((PEBYTE*)arrPtr->buffer + index * arrPtr->elementSize), value, arrPtr->elementSize);
	return arrPtr;
}

PEARRAY* peArraySafeInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (index >= (arrPtr->capacity / arrPtr->elementSize))
	{
		g_PErrorCode = PERROR_ARRAY_INDEX_OOB;
		PERROR_MESSAGE(PERROR_ARRAY_INDEX_OOB_MSG);
		return PENULL;
	}
	return peArrayInsert(arrPtr, index, value);
}

PEARRAY* peArrayErase(PEARRAY* arrPtr, PESIZE index)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	
	arrPtr->elementCount--;
	memmove((PEBYTE*)arrPtr->buffer + index * arrPtr->elementSize,
		(PEBYTE*)arrPtr->buffer + (index + 1) * arrPtr->elementSize,
		(arrPtr->elementCount - index) * arrPtr->elementSize);
	
	return arrPtr;
}

PEARRAY* peArraySafeErase(PEARRAY* arrPtr, PESIZE index)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (index >= arrPtr->elementCount)
	{
		g_PErrorCode = PERROR_ARRAY_INDEX_OOB;
		PERROR_MESSAGE(PERROR_ARRAY_INDEX_OOB_MSG);
		return PENULL;
	}
	
	return peArrayErase(arrPtr, index);
}

PEARRAY* peArrayPushBack(PEARRAY* arrPtr, PEPTRVOID value)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (peArrayIsFull(arrPtr))
	{
		peArrayResize(arrPtr, (arrPtr->elementCount << 1) + 1);
	}
	return peArrayInsert(arrPtr, arrPtr->elementCount++, value);
	
}

PEARRAY* peArrayPopBack(PEARRAY* arrPtr)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (peArrayIsEmpty(arrPtr))
	{
		return PENULL;
	}

	arrPtr->elementCount--;

	return arrPtr;
}

PEARRAY* peArrayMerge(PEARRAY* arrPtrDest, PEARRAY* arrPtrSrc)
{
	if ((!arrPtrDest) || (!arrPtrSrc))
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (arrPtrDest->elementSize != arrPtrSrc->elementSize)
	{
		g_PErrorCode = PERROR_ARRAY_MERGE_DIFF_SIZE;
		PERROR_MESSAGE(PERROR_ARRAY_MERGE_DIFF_SIZE_MSG);
		return PENULL;
	}

	PESIZE newElementCount = arrPtrDest->elementCount + arrPtrSrc->elementCount;
	PESIZE newCapacity = newElementCount * arrPtrDest->elementSize;

	if (newCapacity > arrPtrDest->capacity)
	{
		peArrayResize(arrPtrDest, newElementCount);
	}

	memcpy((PEBYTE*)arrPtrDest->buffer + arrPtrDest->elementCount * arrPtrDest->elementSize,
		arrPtrSrc->buffer,
		arrPtrSrc->elementCount * arrPtrSrc->elementSize);

	arrPtrDest->elementCount = newElementCount;

	return arrPtrDest;
}

PEARRAY* peArrayResize(PEARRAY* arrPtr, PESIZE size)
{
	if (!arrPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	PESIZE newCapacity = size * arrPtr->elementSize;
	PEPTRVOID newBuffer = malloc(newCapacity);

	if (!newBuffer)
	{
		g_PErrorCode = PERROR_MEM_ALLOC_FAULT;
		PERROR_MESSAGE(PERROR_MEM_ALLOC_FAULT_MSG);
		return PENULL;
	}
	
	memcpy(newBuffer, arrPtr->buffer, min(newCapacity, arrPtr->capacity));
	free(arrPtr->buffer);

	arrPtr->capacity = newCapacity;
	arrPtr->buffer = newBuffer;

	return arrPtr;
}