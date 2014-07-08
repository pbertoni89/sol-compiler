/**
 *	\file StringVector.h
 *	\brief a face include to UT_array for char*
 *
 *	TODO improve documentation
 *
 * 	\date Jul 8, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef STRINGVECTOR_H_
#define STRINGVECTOR_H_

#include "utarray.h"
#include <stdbool.h>

typedef UT_array* PStringVector;

PStringVector newStringVector();

void addStringVector(PStringVector* vector,char* str);

void freeStringVector(PStringVector* vector);

bool isStringInVector(PStringVector* vector,char* str);

#endif /* STRINGVECTOR_H_ */
