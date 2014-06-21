/**
 *	\file LexVal.h
 *	\brief TODO complete the documentation of LexVal.h
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
