%{
	#include "lex-definitions.h"
	#include "LexVal.h"
	#include "utils.h"
	/*represents the token meaning (is a char constant or a comma?)*/
	LexVal lexval;
%}

	/*Disable the default behaviour of flex: when it reads EOF normally it restart reading the input file. By adding this ilne, this behaviour is disabled*/
%option noyywrap

	/*######### REGEX DEFINITIONS #############*/

delimiter	[ \n\t]
spacing		{delimiter}+
letter		[a-zA-Z]
digit		[0-9]
id			{letter}({letter}|{digit})*

charconst		'{letter}|{digit}'
intconst		(\+|-)?{digit}+
realconst		(\+|-)?{digit}+"."{digit}+
strconst		\"[^\"\n]*\"
boolconst		true|false



%%

	/* @@@@@@@@@@ SUGARS @@@@@@@@@@@@@@ */

{spacing}	;
"("			{return TK_OPENPARENTHESIS;}
")"			{return TK_CLOSEPARENTHESIS;}
":"			{return TK_COLON;}
";"			{return TK_SEMICOLON;}
","			{return TK_COMMA;}
"["			{return TK_OPENBRACKET;}
"]"			{return TK_CLOSEBRACKET;}
"="			{return TK_ASSIGN;}
"=="		{return TK_EQUAL;}
"!="		{return TK_NOTEQUAL;}
">"			{return TK_GT;}
">="		{return TK_GE;}
"<"			{return TK_LT;}
"<="		{return TK_LE;}
"+"			{return TK_PLUS;}
"-"			{return TK_MINUS;}
"*"			{return TK_TIMES;}
"/"			{return TK_DIVISION;}

	/* @@@@@@@@@ RESERVED WORDS @@@@@@@@@@@@@@ */

func		{return TK_FUNC;}
char		{return TK_CHAR;}
int			{return TK_INT;}
real		{return TK_REAL;}
string		{return TK_STRING;}
bool		{return TK_BOOL;}
struct		{return TK_STRUCT;}
vector		{return TK_VECTOR;}
of			{return TK_OF;}
type		{return TK_TYPE;}
var			{return TK_VAR;}
const		{return TK_CONST;}
begin		{return TK_BEGIN;}
end			{return TK_END;}
if			{return TK_IF;}
then		{return TK_THEN;}
elsif		{return TK_ELSIF;}
else		{return TK_ELSE;}
endif		{return TK_ENDIF;}
while		{return TK_WHILE;}
do			{return TK_DO;}
endwhile	{return TK_ENDWHILE;}
for			{return TK_FOR;}
to			{return TK_TO;}
endfor		{return TK_ENDFOR;}
foreach		{return TK_FOREACH;}
endforeach	{return TK_ENDFOREACH;}
return		{return TK_RETURN;}
read		{return TK_READ;}
write		{return TK_WRITE;}
and			{return TK_AND;}
or			{return TK_OR;}
not			{return TK_NOT;}
toint		{return TK_TOINT;}
toreal		{return TK_TOREAL;}
rd			{return TK_RD;}
wr			{return TK_WR;}

	/* @@@@@@@@@@@@@ CONSTANTS @@@@@@@@@@@@@ */

{charconst}	{lexval.charValue=yytext[0]; return TK_CHARCONST;}
{intconst}	{lexval.intValue=atoi(yytext); return TK_INTCONST;}
{realconst}	{lexval.realValue=atof(yytext); return TK_REALCONST;}
{strconst}	{lexval.strValue=initString(yytext); return TK_STRCONST;}
{boolconst}	{lexval.boolValue=(yytext[0]=='t'?1:0); return TK_BOOLCONST;}

	/* @@@@@@@@@@@@@@ OTHER @@@@@@@@@@@@@@@@@ */

{id}		{lexval.strValue=initString(yytext); return TK_ID;}

%%