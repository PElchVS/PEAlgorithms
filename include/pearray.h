#ifndef PE_ARRAY_H_
#define PE_ARRAY_H_

#include "peiterator.h"

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
PEPTRVOID peArrayAtIterator(PEARRAYITERATOR* itPtr);
PEPTRVOID peArrayFront(PEARRAY* arrPtr);
PEPTRVOID peArrayBack(PEARRAY* arrPtr);

PEARRAYITERATOR* peArrayBegin(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr);
PEARRAYITERATOR* peArrayEnd(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr);
PEARRAYITERATOR* peArrayRevBegin(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr);
PEARRAYITERATOR* peArrayRevEnd(PEARRAY* arrPtr, PEARRAYITERATOR* itPtr);

PEARRAYITERATOR* peArrayIteratorInc(PEARRAYITERATOR* itPtr, PELLONG step);
PEARRAYITERATOR* peArrayIteratorDec(PEARRAYITERATOR* itPtr, PELLONG step);
PELLONG peArrayIteratorDiff(PEARRAYITERATOR* firstItPtr, PEARRAYITERATOR* secondItPtr);

PEBOOL peArrayIsFull(PEARRAY* arrPtr);
PEBOOL peArrayIsEmpty(PEARRAY* arrPtr);
PESIZE peArraySize(PEARRAY* arrPtr);
PESIZE peArrayCapacity(PEARRAY* arrPtr);

PEARRAY* peArrayClear(PEARRAY* arrPtr);
PEARRAY* peArrayInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value);
PEARRAY* peArraySafeInsert(PEARRAY* arrPtr, PESIZE index, PEPTRVOID value);
PEARRAY* peArrayInsertIterator(PEARRAYITERATOR* itPtr, PEPTRVOID value);
PEARRAY* peArrayErase(PEARRAY* arrPtr, PESIZE index);
PEARRAY* peArraySafeErase(PEARRAY* arrPtr, PESIZE index);
PEARRAY* peArrayEraseIterator(PEARRAYITERATOR* itPtr);
PEARRAY* peArrayPushBack(PEARRAY* arrPtr, PEPTRVOID value);
PEARRAY* peArrayPopBack(PEARRAY* arrPtr);
PEARRAY* peArrayReverse(PEARRAY* arrPtr, PEARRAYITERATOR* begin, PEARRAYITERATOR* end);
PEARRAY* peArrayMerge(PEARRAY* arrPtrDest, PEARRAY* arrPtrSrc);

PEARRAY* peArrayResize(PEARRAY* arrPtr, PESIZE size);

PEBOOL peArrayContentEqual(PEARRAY* firstArrPtr, PEARRAY* secondArrPtr, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second));
PEBOOL peArrayFullEqual(PEARRAY* firstArrPtr, PEARRAY* secondArrPtr, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second));
PEBOOL peArrayLess(PEARRAY* firstArrPtr, PEARRAY* secondArrPtr, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second));
PEBOOL peArrayLessOrEqual(PEARRAY* firstArrPtr, PEARRAY* secondArrPtr, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second));
PEBOOL peArrayGreater(PEARRAY* firstArrPtr, PEARRAY* secondArrPtr, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second));
PEBOOL peArrayGreaterOrEqual(PEARRAY* firstArrPtr, PEARRAY* secondArrPtr, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second));

PEARRAYITERATOR* peArrayMin(
	PEARRAY* arrPtr,
	PEARRAYITERATOR* begin,
	PEARRAYITERATOR* end,
	PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second)
);
PEARRAYITERATOR* peArrayMax(
	PEARRAY* arrPtr,
	PEARRAYITERATOR* begin,
	PEARRAYITERATOR* end,
	PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second)
);
PEARRAYITERATOR* peArrayLinearSearch(
	PEARRAY* arrPtr,
	PEARRAYITERATOR* begin,
	PEARRAYITERATOR* end,
	PEPTRVOID value, PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second)
);
PEARRAYITERATOR* peArrayBinarySearch(PEARRAY* arrPtr,
	PEARRAYITERATOR* begin,
	PEARRAYITERATOR* end,
	PEPTRVOID value,
	PEINT(*elementCmp)(PEPTRVOID first, PEPTRVOID second)
);

PESIZE peArrayPrint(
	PEFILE* stream,
	PEARRAY* arrPtr,
	PEARRAYITERATOR* begin,
	PEARRAYITERATOR* end,
	PEINT(*elementPrint)(PEPTRVOID element)
);

#endif
