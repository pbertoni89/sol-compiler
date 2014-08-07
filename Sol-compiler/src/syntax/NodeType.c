#include "NodeType.h"

void printNodeType(FILE* f,NodeType nodetype){
	switch (nodetype){
	case NT_PROGRAM: fprintf(f,"PROGRAM"); break;
	case NT_FUNC_DECL: fprintf(f,"FUNC DECL"); break;
	case NT_DECL_LIST_OPT: fprintf(f,"DECL LIST OPT"); break;
	case NT_DECL_LIST: fprintf(f,"DECL LIST"); break;
	case NT_DECL: fprintf(f,"DECL"); break;
	case NT_ID_LIST: fprintf(f,"ID LIST"); break;
	case NT_DOMAIN: fprintf(f,"DOMAIN"); break;
	case NT_ATOMIC_DOMAIN: fprintf(f,"ATOMIC DOMAIN"); break;
	case NT_STRUCT_DOMAIN: fprintf(f,"STRUC DOMAIN"); break;
	case NT_VECTOR_DOMAIN: fprintf(f,"VECTOR DOMAIN"); break;
	case NT_TYPE_SECT_OPT: fprintf(f,"TYPE SECT OPT"); break;
	case NT_VAR_SECT_OPT: fprintf(f,"VAR SECT OPT"); break;
	case NT_CONST_SECT_OPT: fprintf(f,"CONST SECT OPT"); break;
	case NT_CONST_DECL_LIST: fprintf(f,"CONST DECL LIST"); break;
	case NT_CONST_DECL: fprintf(f,"CONST DECL"); break;
	case NT_FUNC_LIST_OPT: fprintf(f,"FUNC LIST OPT"); break;
	case NT_FUNC_LIST: fprintf(f,"FUNC LIST"); break;
	case NT_FUNC_BODY: fprintf(f,"FUNC BODY"); break;
	case NT_STAT_LIST: fprintf(f,"STAT LIST"); break;
	case NT_STAT: fprintf(f,"STAT"); break;
	case NT_ASSIGN_STAT: fprintf(f,"ASSIGN STAT"); break;
	case NT_LEFT_HAND_SIDE: fprintf(f,"LEFT HAND SIDE"); break;
	case NT_FIELDING: fprintf(f,"FIELDING"); break;
	case NT_INDEXING: fprintf(f,"INDEXING"); break;
	case NT_IF_STAT: fprintf(f,"IF STAT"); break;
	case NT_ELSIF_STAT_LIST_OPT: fprintf(f,"ELSIF STAT LIST OPT"); break;
	case NT_ELSIF_STAT_LIST: fprintf(f,"ELSIF STAT LIST"); break;
	case NT_ELSE_STAT_OPT: fprintf(f,"ELSE STAT OPT"); break;
	case NT_WHILE_STAT: fprintf(f,"WHILE STAT"); break;
	case NT_FOR_STAT: fprintf(f,"FOR STAT"); break;
	case NT_FOREACH_STAT: fprintf(f,"FOREACH STAT"); break;
	case NT_RETURN_STAT: fprintf(f,"RETURN STAT"); break;
	case NT_READ_STAT: fprintf(f,"READ STAT"); break;
	case NT_SPECIFIER_OPT: fprintf(f,"SPECIFIER OPT"); break;
	case NT_WRITE_STAT: fprintf(f,"WRITE STAT"); break;
	case NT_EXPR: fprintf(f,"EXPR"); break;
	case NT_BOOL_TERM_LIST: fprintf(f,"BOOL TERM LIST"); break;
	case NT_BOOL_OP: fprintf(f,"BOOL OP"); break;
	case NT_BOOL_TERM: fprintf(f,"BOOL TERM"); break;
	case NT_REL_OP: fprintf(f,"REL OP"); break;
	case NT_REL_TERM: fprintf(f,"REL TERM"); break;
	case NT_LOW_TERM_LIST: fprintf(f,"LOW TERM LIST"); break;
	case NT_LOW_BIN_OP: fprintf(f,"LOW BIN OP"); break;
	case NT_LOW_TERM: fprintf(f,"LOW TERM"); break;
	case NT_HIGH_BIN_OP: fprintf(f,"HIGH BIN OP"); break;
	case NT_FACTOR_LIST: fprintf(f,"FACTOR LIST"); break;
	case NT_FACTOR: fprintf(f,"FACTOR"); break;
	case NT_UNARY_OP: fprintf(f,"UNARY OP"); break;
	case NT_ATOMIC_CONST: fprintf(f,"ATOMIC CONST"); break;
	case NT_INSTANCE_CONSTRUCTION: fprintf(f,"INSTANCE CONSTRUCTION"); break;
	case NT_STRUCT_CONSTRUCTION: fprintf(f,"STRUCT CONSTRUCTION"); break;
	case NT_EXPR_LIST: fprintf(f,"EXPR LIST"); break;
	case NT_VECTOR_CONSTRUCTION: fprintf(f,"VECTOR CONSTRUCTION"); break;
	case NT_FUNC_CALL: fprintf(f,"FUNC CALL"); break;
	case NT_EXPR_LIST_OPT: fprintf(f,"EXPR LIST OPT"); break;
	case NT_COND_EXPR: fprintf(f,"COND EXPR"); break;
	case NT_ELSIF_EXPR_LIST_OPT: fprintf(f,"ELSIF EXPR LIST OPT"); break;
	case NT_BUILT_IN_CALL: fprintf(f,"BUILT IN CALL"); break;
	case NT_TOINT_CALL: fprintf(f,"TOINT CALL"); break;
	case NT_TOREAL_CALL: fprintf(f,"TOREAL CALL"); break;
	case NT_DYNAMIC_INPUT: fprintf(f,"DYNAMIC INPUT"); break;
	case NT_DYNAMIC_OUTPUT: fprintf(f,"DYNAMIC OUTPUT"); break;
	case T_INTCONST: fprintf(f,"INTCONST"); break;
	case T_STRCONST: fprintf(f,"STRCONST"); break;
	case T_REALCONST: fprintf(f,"REALCONST"); break;
	case T_CHARCONST: fprintf(f,"CHARCONST"); break;
	case T_BOOLCONST: fprintf(f,"BOOLCONST"); break;
	case T_INTTYPE: fprintf(f,"INTTYPE"); break;
	case T_STRINGTYPE: fprintf(f,"STRTYPE"); break;
	case T_REALTYPE: fprintf(f,"REALTYPE"); break;
	case T_CHARTYPE: fprintf(f,"CHARTYPE"); break;
	case T_BOOLEANTYPE: fprintf(f,"BOOLTYPE"); break;
	case T_AND: fprintf(f,"AND"); break;
	case T_OR: fprintf(f,"OR"); break;
	case T_NOT: fprintf(f,"NOT"); break;
	case T_PLUS: fprintf(f,"PLUS"); break;
	case T_MINUS: fprintf(f,"MINUS"); break;
	case T_UMINUS: fprintf(f,"UMINUS"); break;
	case T_TIMES: fprintf(f,"TIMES"); break;
	case T_DIVISION: fprintf(f,"DIVISION"); break;
	case T_IN: fprintf(f,"IN"); break;
	case T_EQ: fprintf(f,"EQ"); break;
	case T_NE: fprintf(f,"NE"); break;
	case T_GT: fprintf(f,"GT"); break;
	case T_GE: fprintf(f,"GE"); break;
	case T_LT: fprintf(f,"LT"); break;
	case T_LE: fprintf(f,"LE"); break;
	case T_ID: fprintf(f,"ID"); break;
	}
}

bool isTerminal(NodeType nodetype){
	switch (nodetype){
	case T_INTCONST:
	case T_STRCONST:
	case T_REALCONST:
	case T_CHARCONST:
	case T_BOOLCONST:
	case T_INTTYPE:
	case T_STRINGTYPE:
	case T_REALTYPE:
	case T_CHARTYPE:
	case T_BOOLEANTYPE:
	case T_AND:
	case T_OR:
	case T_NOT:
	case T_PLUS:
	case T_MINUS:
	case T_UMINUS:
	case T_TIMES:
	case T_DIVISION:
	case T_IN:
	case T_EQ:
	case T_NE:
	case T_GT:
	case T_GE:
	case T_LT:
	case T_LE:
	case T_ID: return true;
	default: return false;
	}
}

bool isNonTerminal(NodeType nodetype){
	return !isTerminal(nodetype);
}
