#ifndef PE_ERROR_H_
#define PE_ERROR_H_

#include <stdio.h>

#include "petypes.h"

typedef PEULLONG PERROR;

extern PERROR g_PErrorCode;

#ifdef PERROR_MSG_ENABLE
	#define PERROR_MESSAGE(MSG) fprintf(stderr, "%s File:%s Line:%d Function:%s\n", (MSG), __FILE__, __LINE__, __FUNCTION__)
#else
	#define PERROR_MESSAGE(MSG)
#endif

#define PERROR_NULL_PTR_DEREF	0x01
#define PERROR_MEM_ALLOC_FAULT	0x02

#define PERROR_ARRAY					0x8000000000000000
#define PERROR_ARRAY_INDEX_OOB			(PERROR_ARRAY | 0x01)
#define PERROR_ARRAY_INVALID_SIZE		(PERROR_ARRAY | 0x02)
#define PERROR_ARRAY_INVALID_EL_SIZE	(PERROR_ARRAY | 0x03)
#define PERROR_ARRAY_MERGE_DIFF_SIZE	(PERROR_ARRAY | 0x04)

#define PERROR_NULL_PTR_DEREF_MSG	"Null pointer dereferencing"
#define PERROR_MEM_ALLOC_FAULT_MSG	"Memory allocation fault"

#define PERROR_ARRAY_INDEX_OOB_MSG			"Array index out of bounds"
#define PERROR_ARRAY_INVALID_SIZE_MSG		"Array invalid size"
#define PERROR_ARRAY_INVALID_EL_SIZE_MSG	"Array invalid element size"
#define PERROR_ARRAY_MERGE_DIFF_SIZE_MSG	"Merging arrays with different element type sizes"

#endif
