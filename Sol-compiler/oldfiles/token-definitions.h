/**
 *	\file token-definitions.h
 *	\brief Includes a list of lexical token definitions
 *
 *	this file include a list of defines directives. You use them to communicate information betweeen the lexical module and the syntax one.
 *	For example if you the lex module reads a "string constant" you need to send to the syntax module the value of the constant <b>and</b>
 *	the information that you read a <b>strconst</b>: in this way the syntax module first understands whta token the lex read and only after this
 *	operation it handles how to proceed (abstract syntax tree); the action that the syntax module will do <b>strongly</b> depends on
 *	what token the lexical module have just read.
 *
 *	While the information on what symbol has been just read is carried with the return value of the function "yylex()" the exact data
 *	of what constant has been read (avaiable with token like "id" or "boolconst") is carried via the variable lexval.
 *
 *	\note
 *	For example if the lexer reads the char reserved words it only returns TK_CHAR from the yylex() call; the lexval reamins unused. This
 *	will not happen with token like TK_ID: yylex() will return TK_ID but inside yylex will be store the string value of the identifier just read.
 *
 *	\section a01 Symbol token categories
 *
 *	Although tokens are just numbers to return with yylex() funciton we decided to divide them into 4 categories: these
 *	categories are completely transparent to the developer and are only used to better organize this header file. The categories
 *	are:
 *	\li ascii symbols token: tokens composed by only one character which is present inside the first half of the ASCII tables. This
 *	category contains all the sugar tokens, like commas, semicolon or plus.
 *	\li non ascii symbols token: altough the token inside this category are present tokens composed by only ascii symbols (again, commas, exclamation marks, minus, excetera)
 *	they are not composed by only one character, but by many of them (usually 2). Example can be">=", "==" or "!=".
 *	\li reserved words token: this category holds all the reserved words used by SOL. Examples may be "for" or "while".s
 *	\li lexval user token: in this category there are all the token which are described not only with yylex() return value but also by the structure LexVal.
 *	Examples are IDs, realconst or strconst.
 *
 *
 * 	\date Jun 20, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef TOKEN_DEFINITIONS_H_
#define TOKEN_DEFINITIONS_H_

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@ ASCII SYMBOLS TOKENS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define TK_OPENPARENTHESIS		'('
#define TK_CLOSEPARENTHESIS		')'
#define TK_COLON				':'
#define TK_SEMICOLON			';'
#define TK_COMMA				','
#define TK_OPENBRACKET			'['
#define TK_CLOSEBRACKET			']'
#define TK_ASSIGN				'='
#define TK_GT					'>'
#define TK_LT					'<'
#define TK_PLUS					'+'
#define TK_MINUS				'-'
#define TK_TIMES				'*'
#define TK_DIVISION				'/'

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@ NON ASCII SYMBOL TOKENS @@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define TK_EQUAL				301
#define TK_NOTEQUAL				302
#define TK_GE					303
#define TK_LE					304

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@ RESERVED WORDS TOKENS @@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define TK_FUNC					401
#define TK_CHAR					402
#define TK_INT					403
#define TK_REAL					404
#define TK_STRING				405
#define TK_BOOL					406
#define TK_STRUCT				407
#define TK_VECTOR				408
#define TK_OF					409
#define TK_TYPE					410
#define TK_VAR					411
#define TK_CONST				412
#define TK_BEGIN				413
#define TK_END					414
#define TK_IF					415
#define TK_THEN					416
#define TK_ELSIF				417
#define TK_ELSE					418
#define TK_ENDIF				419
#define TK_WHILE				420
#define TK_DO					421
#define TK_ENDWHILE				422
#define TK_FOR					423
#define TK_TO					424
#define TK_ENDFOR				425
#define TK_FOREACH				426
#define TK_IN					427
#define TK_ENDFOREACH			428
#define TK_RETURN				429
#define TK_READ					430
#define TK_WRITE				431
#define TK_AND					432
#define TK_OR					433
#define TK_NOT					434
#define TK_TOINT				435
#define TK_TOREAL				436
#define TK_RD					437
#define TK_WR					438

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@ LEXVAL USER TOKENS @@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define TK_CHARCONST			501
#define TK_INTCONST				502
#define TK_REALCONST			503
#define TK_STRCONST				504
#define TK_BOOLCONST			505
#define TK_ID					506


#endif /* TOKEN_DEFINITIONS_H_ */
