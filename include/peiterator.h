#ifndef PE_ITERATOR_H_
#define PE_ITERATOR_H_

#include "perror.h"
#include "pebool.h"

typedef struct pearray PEARRAY;

typedef struct pearrayitereator
{
	PEARRAY* array;
	PEPTRVOID iterator;
	PEBOOL reversed;
}PEARRAYITERATOR;

#endif

