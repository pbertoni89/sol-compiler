
#ifdef SYNTAX_TEST

#include <stdio.h>
#include "KoldarCTester.h"
#include "lexical.h"
#include "token-definitions.h"
#include "Node.h"

#define TESTPATH "test-files/"

extern int yyparse();

void testSyn01(){
	FILE* input;
	int result;
	bool grpresult;
	extern PNode root;

	input=fopen(TESTPATH"sol01.sol","r");
	kct_assertIsNotNull(input);
	yylex_destroy();
	yyrestart(input);
	yyset_in(input);
	printf("building syntax tree...\n");
	result=yyparse();
	kct_assertEqualIntMsg("error #1",0,result);
	printf("syntax tree built.\n");
	printf("drawing abstract syntax tree...\n");
	grpresult=buildSyntaxTreeGraph("testSyn01",root,true,true);
	kct_assertEqualIntMsg("graph not created!",1,grpresult);
	printf("abstract syntax tree drawn.\n");
	printf("Freeing the whole abstract syntax tree...\n");
	freeSyntaxTree(root);
	printf("syntax tree freed.\n");
	fclose(input);
}

int main(){
	kct_addTest(testSyn01);
	kct_runAllTests(stdout);
}

#endif
