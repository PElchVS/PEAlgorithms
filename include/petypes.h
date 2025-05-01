#ifndef PE_TYPES_H_
#define PE_TYPES_H_

#include <stddef.h>

typedef void PEVOID;

typedef short		PESHORT;
typedef int			PEINT;
typedef long		PELONG;
typedef long long	PELLONG;

typedef unsigned short		PEUSHORT;
typedef unsigned int		PEUINT;
typedef unsigned long		PEULONG;
typedef unsigned long long	PEULLONG;

typedef unsigned char		PEBYTE;
typedef unsigned short		PEWORD;
typedef unsigned long		PEDWORD;
typedef unsigned long long	PEQWORD;

typedef float		PEFLOAT;
typedef double		PEDOUBLE;
typedef long double PELDOUBLE;

typedef char			PECHAR;
typedef unsigned char	PEUCHAR;
typedef wchar_t			PEWCHAR;

typedef void* PEPTRVOID;

typedef size_t PESIZE;

#define PENULL NULL


#endif

