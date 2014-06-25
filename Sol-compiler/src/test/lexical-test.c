/**
 *	\file lexical-test.c
 *	\brief TODO complete the documentation of lexical-test.c
 *
 * 	\date Jun 21, 2014
 * 	\author koldar
 *	\version 1.0
 */

#ifdef LEXICAL_TEST

#include <stdio.h>
#include "KoldarCTester.h"
#include "lexical.h"

#define TESTPATH "test-files/"

void testLex01(){
	FILE* input;
	int token;

	input=fopen(TESTPATH"lex01.sol","r");
	kct_assertIsNotNull(input);

	yyset_in(input);
	while ((token=yylex())!=0){
		printf("token read: %03d\n",token);
	}
}

int main(){
	kct_addTest(testLex01);
	kct_runAllTests(stdout);
}

#endif
