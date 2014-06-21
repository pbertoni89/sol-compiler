/**
 *	\file lex-definitions.h
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
 *
 * 	\date Jun 20, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef LEX_DEFINITIONS_H_
#define LEX_DEFINITIONS_H_

// ************************* RESERVED WORDS TOKENS ********************

#define TK_FUNC					101
#define TK_CHAR					102
#define TK_INT					103
#define TK_REAL					104
#define TK_STRING				105
#define TK_BOOL					106
#define TK_STRUCT				107
#define TK_VECTOR				108
#define TK_OF					109
#define TK_TYPE					110
#define TK_VAR					111
#define TK_CONST				112
#define TK_BEGIN				113
#define TK_END					114
#define TK_IF					115
#define TK_THEN					116
#define TK_ELSIF				117
#define TK_ELSE					118
#define TK_ENDIF				119
#define TK_WHILE				120
#define TK_DO					121
#define TK_ENDWHILE				122
#define TK_FOR					123
#define TK_TO					124
#define TK_ENDFOR				125
#define TK_FOREACH				126
#define TK_IN					127
#define TK_ENDFOREACH			128
#define TK_RETURN				129
#define TK_READ					130
#define TK_WRITE				131
#define TK_AND					132
#define TK_OR					133
#define TK_NOT					134
#define TK_TOINT				135
#define TK_TOREAL				136
#define TK_RD					137
#define TK_WR					138

// ************************* SYMBOLS TOKENS *****************************

#define TK_OPENPARENTHESIS		201
#define TK_CLOSEPARENTHESIS		202
#define TK_COLON				203
#define TK_SEMICOLON			204
#define TK_COMMA				205
#define TK_OPENBRACKET			206
#define TK_CLOSEBRACKET			207
#define TK_ASSIGN				208
#define TK_EQUAL				209
#define TK_NOTEQUAL				210
#define TK_GT					211
#define TK_GE					212
#define TK_LT					213
#define TK_LE					214
#define TK_PLUS					215
#define TK_MINUS				216
#define TK_TIMES				217
#define TK_DIVISION				218

// ************************* LEXVAL USER TOKENS *******************************

#define TK_CHARCONST			301
#define TK_INTCONST				302
#define TK_REALCONST			303
#define TK_STRCONST				304
#define TK_BOOLCONST			305
#define TK_ID					306


#endif /* LEX_DEFINITIONS_H_ */
