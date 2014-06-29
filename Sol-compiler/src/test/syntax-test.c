#ifdef SYNTAX_TEST

#include <stdio.h>
#include "KoldarCTester.h"
#include "lexical.h"
#include "token-definitions.h"

#define TESTPATH "test-files/"

void testSyn01(){
	FILE* input;
	int result;
	input=fopen(TESTPATH"sol01.sol","r");
	kct_assertIsNotNull(input);
	yylex_destroy();
	yyrestart(input);
	yyset_in(input);
	printf("building syntax tree...\n");
	result=yyparse();
	printf("syntax tree built.\n");
	fclose(input);
	kct_assertEqualIntMsg("error #1",0,result);
}

int main(){
	kct_addTest(testSyn01);
	kct_runAllTests(stdout);
}

#endif
