/**
 *	\file lexical-test.c
 *	\brief file contaning the test relative to the lexical analysis.
 *
 * 	\date Jun 21, 2014
 * 	\author koldar
 *	\version 1.0
 */

#ifdef LEXICAL_TEST

#include <stdio.h>
#include "KoldarCTester.h"
#include "lexical.h"
#include "token-definitions.h"
#include "LexVal.h"

extern LexVal lexVal;

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

void testLexString(){
	FILE* input;
	int token;

	input=fopen(TESTPATH"lex04.sol","r");
	kct_assertIsNotNull(input);

	yyset_in(input);
	while ((token=yylex())!=0){
		printf("token read: %03d\n",token);
		if (token==TK_STRCONST || token==TK_ID){
			printf("\"%s\"\n",lexVal.strValue);
		}
	}
}

int main(){
	kct_addTest(testLex01);
	kct_addTest(testLexString);
	kct_runAllTests(stdout);
}

#endif
