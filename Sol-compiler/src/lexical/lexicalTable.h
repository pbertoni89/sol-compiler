/**
 *	\file lexicalTable.h
 *	\brief represents an hastable where are stored all the strings revealed
 *
 *	Through this header it is possible to reduce memory space.
 *	Let suppose we have a file such this:
 *
 *	\verbinclude WhylexicalTableIsUseful.dox
 *
 *	In this example the string "progTest" is present with different meaning such:
 *	\li program name;
 *	\li local variable name;
 *	\li global variable name;
 *
 *	If this header were to lack, the compiler would have to store the same
 *	string in memory more than once. By using this header the compiler
 *	can efficiently store the stirng only once.
 *
 *	Moreover this header allows the compiler to be <b>much</b>quicker; how?
 *	Since with this method a string is present in memory only once string
 *	comparison can be simply verified through pointer equality. Very long
 *	strings can be compared just with pointer comparison.
 *
 * 	\date Jul 2, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef LEXICALTABLE_H_
#define LEXICALTABLE_H_


//TODO implements this header
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"
#include "utils.h"


//TODO documentation
typedef struct LexString{
	unsigned int id;
	char* str;
	UT_hash_handle hh;
} LexString;

//TODO documentation
typedef LexString* PLexStringHT;


//TODO documentation
char* addLexStringInHashTable(char* str);


//TODO documentation
void freeLexStringHashTable();

#endif /* LEXICALTABLE_H_ */
