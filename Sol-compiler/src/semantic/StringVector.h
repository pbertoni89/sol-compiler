/**
 *	\file StringVector.h
 *	\brief a face include to UT_array for char*
 *
 *	In semantic analysis you often need a dynamic array of strings: this is the case
 *	when you deal with id-list. Including this header allows you to handle the type PStringVector:
 *	this type represents a vector of pointer of chars (the actual string is stored somewhere else inside the
 *	memory).
 *
 *	This header uses the awesome header-library utarray, retrievable visiting the link http://troydhanson.github.io/uthash/utarray.html.
 *	Actually, this header is just a facade header providing useful API to handle a vector of char*.
 *
 * 	\date Jul 8, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef STRINGVECTOR_H_
#define STRINGVECTOR_H_

#include "utarray.h"
#include <stdbool.h>

typedef UT_array StringVector;

StringVector* newStringVector();

void newStringVectorInMemory(StringVector* vector);

void addStringVector(StringVector* vector,char* str);

void freeStringVector(StringVector* vector);

bool isStringInVector(StringVector* vector,char* str);

#endif /* STRINGVECTOR_H_ */
