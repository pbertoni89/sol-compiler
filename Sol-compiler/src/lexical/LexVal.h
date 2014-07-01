/**
 *	\file LexVal.h
 *	\brief the structure containing the token data just read
 *
 *	There a some token inside SOL language that holds useful data. For example
 *	an identifier can't be modelled just by saying to the Syntax module: "this is an identifier (TK_ID)":
 *	the syntax module should also know the identifier string value. LexVal is able to store
 *	this information.
 *
 *	\verbinclude tokensHavingLexVal.dox
 *
 *	All those tokens can't be described only by a number but have to be described also by their value.
 *
 * 	\date Jun 20, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef LEXVAL_H_
#define LEXVAL_H_

#include <stdbool.h>

typedef union LexVal {
	char charValue;
	int intValue;
	float realValue;
	char* strValue;
	bool boolValue;
} LexVal;




#endif /* LEXVAL_H_ */
