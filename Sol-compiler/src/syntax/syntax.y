%{
#include "lex-definitions.h"
#include "Node.h"
#include <stdlib.h>
#define YYSTYPE PNode
extern char* yytext;
extern LexVal lexVal;
extern FILE* yyinput;
Pnode root=NULL;

%}

%token TK_OPENPARENTHESIS TK_CLOSEPARENTHESIS TK_COLON TK_SEMICOLON TK_COMMA TK_OPENBRACKET TK_CLOSEBRACKET TK_ASSIGN TK_GT TK_LT TK_PLUS TK_MINUS TK_TIMES TK_DIVISION 
%token TK_EQUAL TK_NOTEQUAL TK_GE TK_LE 
%token TK_FUNC TK_CHAR TK_INT TK_REAL TK_STRING TK_BOOL TK_STRUCT TK_VECTOR TK_OF TK_TYPE TK_VAR TK_CONST TK_BEGIN TK_END TK_IF TK_THEN TK_ELSIF TK_ELSE TK_ENDIF TK_WHILE TK_DO TK_ENDWHILE TK_FOR TK_TO TK_ENDFOR TK_FOREACH TK_IN TK_ENDFOREACH TK_RETURN TK_READ TK_WRITE TK_AND TK_OR TK_NOT TK_TOINT TK_TOREAL TK_RD TK_WR 
%token TK_CHARCONST TK_INTCONST TK_REALCONST TK_STRCONST TK_BOOLCONST TK_ID

%error-verbose 

%%

	/* ################### DERIVATION RULES ###################### */

program					:	func-decl {root=$$; $$=initNode(NT_PROGRAM); $$->child=$1;}
						;
						
func-decl				:	TK_FUNC TK_ID {$$=initIDNode(lexval.strValue);} '(' decl-list-opt ')' ':' domain type-sect-opt var-sect-opt const-sect-opt func-list-opt func-body
							{$$=initNode(NT_FUNC_DECL); $$->child=$3; $3->brother=$5; $5->brother=$8; $8->brother=$9; $9->brother=$10; $10->brother=$11; $11->brother=$12; $12->brother=$13;}
						;
						
decl-list-opt			:	decl-list {$$=initNode(NT_DECL_LIST_OPT); $$->child=$1;} 
						|	{$$=initNode(NT_DECL_LIST_OPT);}
						;

decl-list				:	decl ';' decl-list {$$=$1; $1->brother=$3;}
						|	decl ';' {$$=$1;}
						;
						
decl					:	id-list ':' domain ';' {$$=initNode(NT_DECL); $$->child=$1; }
						;
						
id-list					:	TK_ID ',' id-list
						|	TK_ID
						;
						
domain					:	atomic-domain
						|	struct-domain
						|	vector-domain
						|	TK_ID
						;
						
atomic-domain			:	TK_CHAR
						|	TK_INT
						|	TK_REAL
						|	TK_STRING
						|	TK_BOOL
						;
						
struct-domain			:	TK_STRUCT '(' decl-list ')'
						;
						
vector-domain			:	TK_VECTOR '[' TK_INTCONST ']' TK_OF domain
						;
						
type-sect-opt			:	TK_TYPE decl-list
						|
						;
						
var-sect-opt			:	TK_VAR decl-list
						|
						;
						
const-sect-opt			:	TK_CONST const-decl-list
						|
						;

const-decl-list			:	const-decl const-decl-list
						|	const-decl
						;
						
const-decl				:	decl '=' expr ';'
						;
						
func-list-opt			:	func-list
						|
						;

func-list				:	func-decl func-list
						|	func-decl
						;
						
func-body				:	TK_BEGIN TK_ID stat-list TK_END TK_ID
						;
						
stat-list				:	stat ';' stat-list
						|	stat ';'
						;
						
stat					:	assign-stat
						|	if-stat
						|	while-stat
						|	for-stat
						|	foreach-stat
						|	return-stat
						|	read-stat
						|	write-stat
						;
						
assign-stat				:	left-hand-side '=' expr
						;
						
left-hand-side			:	TK_ID
						|	fielding
						|	indexing
						;
						
fielding				:	left-hand-side '.' TK_ID
						;

indexing				:	left-hand-side '[' expr ']'
						;
						
if-stat					:	TK_IF expr TK_THEN stat-list elsif-stat-list-opt else-stat-opt TK_ENDIF
						;
						
elsif-stat-list-opt		:	TK_ELSIF expr TK_THEN stat-list elsif-stat-list-opt
						|
						;

else-stat-opt			:	TK_ELSE stat-list
						|
						;

while-stat				:	TK_WHILE expr TK_DO stat-list TK_ENDWHILE
						;
						
for-stat				:	TK_FOR TK_ID '=' expr TK_TO expr TK_DO stat-list TK_ENDFOR
						;
						
foreach-stat			:	TK_FOREACH TK_ID TK_IN expr TK_DO stat-list TK_ENDFOREACH
						;
						
return-stat				:	TK_RETURN expr
						;
						
read-stat				:	TK_READ specifier-opt TK_ID
						;
						
specifier-opt			:	'[' expr ']'
						|
						;
						
write-stat				:	TK_WRITE specifier-opt expr
						;
						
expr					:	expr bool-op bool-term
						|	bool-term
						;
						
bool-op					:	TK_AND
						|	TK_OR
						;
						
bool-term				:	rel-term rel-op rel-term
						|	rel-term
						;
						
rel-op					:	TK_EQUAL
						|	TK_NOTEQUAL
						|	TK_GT
						|	TK_GE
						|	TK_LT
						|	TK_LE
						|	TK_IN
						;
						
rel-term				:	rel-term  low-bin-op low-term
						|	low-term
						;
						
low-bin-op				:	'+'
						|	'-'
						;
						
low-term				:	low-term high-bin-op factor
						|	factor
						;
						
high-bin-op				:	'*'
						|	'/'
						;
						
factor					:	unary-op factor
						|	'(' expr ')'
						|	left-hand-side
						|	atomic-const
						|	instance-construction
						|	func-call
						|	cond-expr
						|	built-in-call
						|	dynamic-input
						;
						
unary-op				:	'-'
						|	TK_NOT
						|	dynamic-output
						;
						
atomic-const			:	TK_CHARCONST
						|	TK_INTCONST
						|	TK_REALCONST
						|	TK_STRCONST
						|	TK_BOOLCONST
						;
						
instance-construction	:	struct-construction
						|	vector-construction
						;
						
struct-construction		:	TK_STRUCT '(' expr-list ')'
						;
						
expr-list				:	expr ',' expr-list
						|	expr
						;
						
vector-construction		:	TK_VECTOR '(' expr-list ')'
						;
						
func-call				:	TK_ID '(' expr-list-opt ')'
						;

expr-list-opt			:	expr-list
						|
						;
						
cond-expr				:	TK_IF expr TK_THEN expr elsif-expr-list-opt TK_ELSE expr TK_ENDIF
						;

elsif-expr-list-opt		:	TK_ELSIF expr TK_THEN expr elsif-expr-list-opt
						|
						;
						
built-in-call			:	toint-call
						|	toreal-call
						;

toint-call				:	TK_TOINT '(' expr ')'
						;

toreal-call				:	TK_TOREAL '(' expr ')'
						;
						
dynamic-input			:	TK_RD specifier-opt domain
						;
						
dynamic-output			:	TK_WR specifier-opt
						;

%%
