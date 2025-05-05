#include "pearray.h"
#include "pemem.h"

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

PEPTRVOID peArrayAtIterator(PEARRAYITERATOR* itPtr)
{
	if (!itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	return itPtr->iterator;
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

PEARRAYITERATOR* peArrayBegin(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr)
{
	if (!arrPtr || !itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	itPtr->array = arrPtr;
	itPtr->iterator = arrPtr->buffer;
	itPtr->reversed = PEFALSE;
	return itPtr;
}

PEARRAYITERATOR* peArrayEnd(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr)
{
	if (!arrPtr || !itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	itPtr->array = arrPtr;
	itPtr->iterator = ((PEBYTE*)arrPtr->buffer) + arrPtr->elementCount * arrPtr->elementSize;
	itPtr->reversed = PEFALSE;
	return itPtr;
}

PEARRAYITERATOR* peArrayRevBegin(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr)
{
	if (!arrPtr || !itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	itPtr->array = arrPtr;
	itPtr->iterator = ((PEBYTE*)arrPtr->buffer) + (arrPtr->elementCount - 1) * arrPtr->elementSize;
	itPtr->reversed = PETRUE;
	return itPtr;
}

PEARRAYITERATOR* peArrayRevEnd(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr)
{
	if (!arrPtr || !itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	itPtr->array = arrPtr;
	itPtr->iterator = (PEBYTE*)arrPtr->buffer - arrPtr->elementSize;
	itPtr->reversed = PEFALSE;
	return itPtr;
}

PEARRAYITERATOR* peArrayIteratorInc(PEARRAYITERATOR* itPtr, PELLONG step)
{
	if (!itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	PEINT dir = itPtr->reversed ? -1 : 1;

	(PEBYTE*)itPtr->iterator += dir * step * itPtr->array->elementSize;

	return itPtr;
}

PEARRAYITERATOR* peArrayIteratorDec(PEARRAYITERATOR* itPtr, PELLONG step)
{
	if (!itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	PEINT dir = itPtr->reversed ? -1 : 1;

	(PEBYTE*)itPtr->iterator -= dir * step * itPtr->array->elementSize;

	return itPtr;
}

PELLONG peArrayIteratorDiff(PEARRAYITERATOR* firstItPtr, PEARRAYITERATOR* secondItPtr)
{
	if (!firstItPtr || !secondItPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (firstItPtr->array != secondItPtr->array)
	{
		g_PErrorCode = (PERROR_ARRAY | PERROR_ITERATOR_DIFF);
		PERROR_MESSAGE(PERROR_ITERATOR_DIFF_MSG);
		return PENULL;
	}

	if (firstItPtr->reversed)
	{
		return ((PEBYTE*)firstItPtr->iterator - (PEBYTE*)secondItPtr->iterator) / (PELLONG)firstItPtr->array->elementSize;
	}

	return ((PEBYTE*)secondItPtr->iterator - (PEBYTE*)firstItPtr->iterator) / (PELLONG)firstItPtr->array->elementSize;
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

PEARRAY* peArrayInsertIterator(PEARRAYITERATOR* itPtr, PEPTRVOID value)
{
	if(!itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	memcpy(itPtr->iterator, value, itPtr->array->elementSize);

	return itPtr->array;
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

PEARRAY* peArrayEraseIterator(PEARRAYITERATOR* itPtr)
{
	if (!itPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}
	PEARRAYITERATOR itEnd;
	peArrayEnd(itPtr->array, &itEnd);
	PELLONG diff = peArrayIteratorDiff(itPtr, &itEnd) - 1;

	memmove(itPtr->iterator, (PEBYTE*)itPtr->iterator + itPtr->array->elementSize, diff * itPtr->array->elementSize);	
	itPtr->array->elementCount--;
	
	return itPtr->array;
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

PEINT peSwap(PEPTRVOID firstPtr, PEPTRVOID secondPtr, PESIZE size)
{
	if (!firstPtr || !secondPtr)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PE_FAILURE;
	}

	PEBYTE* tmp = (PEBYTE*)malloc(size);

	if (!tmp)
	{
		g_PErrorCode = PERROR_MEM_ALLOC_FAULT;
		PERROR_MESSAGE(PERROR_MEM_ALLOC_FAULT_MSG);
		return PE_FAILURE;
	}

	memcpy(tmp, firstPtr, size);
	memcpy(firstPtr, secondPtr, size);
	memcpy(secondPtr, tmp, size);
	free(tmp);

	return PE_SUCCESS;
}

PEARRAY* peArrayReverse(PEARRAY* arrPtr, PEARRAYITERATOR* begin, PEARRAYITERATOR* end)
{
	if (!arrPtr || !begin || !end)
	{
		g_PErrorCode = PERROR_NULL_PTR_DEREF;
		PERROR_MESSAGE(PERROR_NULL_PTR_DEREF_MSG);
		return PENULL;
	}

	if (arrPtr != begin->array || arrPtr != end->array)
	{
		return PENULL;
	}

	PEARRAYITERATOR i = *begin;
	PEARRAYITERATOR j = *end;

	peArrayIteratorDec(&j, 1);
	while (i.iterator < j.iterator)
	{
		peSwap(i.iterator, j.iterator, arrPtr->elementSize);
		peArrayIteratorInc(&i, 1);
		peArrayIteratorDec(&j, 1);
	}	

	return arrPtr;
}

PEARRAY* peArrayMerge(PEARRAY* arrPtrDest, PEARRAY* arrPtrSrc)
{
	if (!arrPtrDest || !arrPtrSrc)
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