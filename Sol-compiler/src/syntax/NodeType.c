#include "NodeType.h"

void printNodeType(FILE* f,NodeType nodetype){
	switch (nodetype){
	case NT_PROGRAM: fprintf(f,"NT_PROGRAM"); break;
	case NT_FUNC_DECL: fprintf(f,"NT_FUNC_DECL"); break;
	case NT_DECL_LIST_OPT: fprintf(f,"NT_DECL_LIST_OPT"); break;
	case NT_DECL_LIST: fprintf(f,"NT_DECL_LIST"); break;
	case NT_DECL: fprintf(f,"NT_DECL"); break;
	case NT_ID_LIST: fprintf(f,"NT_ID_LIST"); break;
	case NT_DOMAIN: fprintf(f,"NT_DOMAIN"); break;
	case NT_ATOMIC_DOMAIN: fprintf(f,"NT_ATOMIC_DOMAIN"); break;
	case NT_STRUCT_DOMAIN: fprintf(f,"NT_STRUCT_DOMAIN"); break;
	case NT_VECTOR_DOMAIN: fprintf(f,"NT_VECTOR_DOMAIN"); break;
	case NT_TYPE_SECT_OPT: fprintf(f,"NT_TYPE_SECT_OPT"); break;
	case NT_VAR_SECT_OPT: fprintf(f,"NT_VAR_SECT_OPT"); break;
	case NT_CONST_SECT_OPT: fprintf(f,"NT_CONST_SECT_OPT"); break;
	case NT_CONST_DECL_LIST: fprintf(f,"NT_CONST_DECL_LIST"); break;
	case NT_CONST_DECL: fprintf(f,"NT_CONST_DECL"); break;
	case NT_FUNC_LIST_OPT: fprintf(f,"NT_FUNC_LIST_OPT"); break;
	case NT_FUNC_LIST: fprintf(f,"NT_FUNC_LIST"); break;
	case NT_FUNC_BODY: fprintf(f,"NT_FUNC_BODY"); break;
	case NT_STAT_LIST: fprintf(f,"NT_STAT_LIST"); break;
	case NT_STAT: fprintf(f,"NT_STAT"); break;
	case NT_ASSIGN_STAT: fprintf(f,"NT_ASSIGN_STAT"); break;
	case NT_LEFT_HAND_SIDE: fprintf(f,"NT_LEFT_HAND_SIDE"); break;
	case NT_FIELDING: fprintf(f,"NT_FIELDING"); break;
	case NT_INDEXING: fprintf(f,"NT_INDEXING"); break;
	case NT_IF_STAT: fprintf(f,"NT_IF_STAT"); break;
	case NT_ELSIF_STAT_LIST_OPT: fprintf(f,"NT_ELSIF_STAT_LIST_OPT"); break;
	case NT_ELSIF_STAT_LIST: fprintf(f,"NT_ELSIF_STAT_LIST"); break;
	case NT_ELSE_STAT_OPT: fprintf(f,"NT_ELSE_STAT_OPT"); break;
	case NT_WHILE_STAT: fprintf(f,"NT_WHILE_STAT"); break;
	case NT_FOR_STAT: fprintf(f,"NT_FOR_STAT"); break;
	case NT_FOREACH_STAT: fprintf(f,"NT_FOREACH_STAT"); break;
	case NT_RETURN_STAT: fprintf(f,"NT_RETURN_STAT"); break;
	case NT_READ_STAT: fprintf(f,"NT_READ_STAT"); break;
	case NT_SPECIFIER_OPT: fprintf(f,"NT_SPECIFIER_OPT"); break;
	case NT_WRITE_STAT: fprintf(f,"NT_WRITE_STAT"); break;
	case NT_EXPR: fprintf(f,"NT_EXPR"); break;
	case NT_BOOL_TERM_LIST: fprintf(f,"NT_BOOL_TERM_LIST"); break;
	case NT_BOOL_OP: fprintf(f,"NT_BOOL_OP"); break;
	case NT_BOOL_TERM: fprintf(f,"NT_BOOL_TERM"); break;
	case NT_REL_OP: fprintf(f,"NT_REL_OP"); break;
	case NT_REL_TERM: fprintf(f,"NT_REL_TERM"); break;
	case NT_LOW_TERM_LIST: fprintf(f,"NT_LOW_TERM_LIST"); break;
	case NT_LOW_BIN_OP: fprintf(f,"NT_LOW_BIN_OP"); break;
	case NT_LOW_TERM: fprintf(f,"NT_LOW_TERM"); break;
	case NT_HIGH_BIN_OP: fprintf(f,"NT_HIGH_BIN_OP"); break;
	case NT_FACTOR_LIST: fprintf(f,"NT_FACTOR_LIST"); break;
	case NT_FACTOR: fprintf(f,"NT_FACTOR"); break;
	case NT_UNARY_OP: fprintf(f,"NT_UNARY_OP"); break;
	case NT_ATOMIC_CONST: fprintf(f,"NT_ATOMIC_CONST"); break;
	case NT_INSTANCE_CONSTRUCTION: fprintf(f,"NT_INSTANCE_CONSTRUCTION"); break;
	case NT_STRUCT_CONSTRUCTION: fprintf(f,"NT_STRUCT_CONSTRUCTION"); break;
	case NT_EXPR_LIST: fprintf(f,"NT_EXPR_LIST"); break;
	case NT_VECTOR_CONSTRUCTION: fprintf(f,"NT_VECTOR_CONSTRUCTION"); break;
	case NT_FUNC_CALL: fprintf(f,"NT_FUNC_CALL"); break;
	case NT_EXPR_LIST_OPT: fprintf(f,"NT_EXPR_LIST_OPT"); break;
	case NT_COND_EXPR: fprintf(f,"NT_COND_EXPR"); break;
	case NT_ELSIF_EXPR_LIST_OPT: fprintf(f,"NT_ELSIF_EXPR_LIST_OPT"); break;
	case NT_BUILT_IN_CALL: fprintf(f,"NT_BUILT_IN_CALL"); break;
	case NT_TOINT_CALL: fprintf(f,"NT_TOINT_CALL"); break;
	case NT_TOREAL_CALL: fprintf(f,"NT_TOREAL_CALL"); break;
	case NT_DYNAMIC_INPUT: fprintf(f,"NT_DYNAMIC_INPUT"); break;
	case NT_DYNAMIC_OUTPUT: fprintf(f,"NT_DYNAMIC_OUTPUT"); break;
	case T_INTCONST: fprintf(f,"T_INTCONST"); break;
	case T_STRCONST: fprintf(f,"T_STRCONST"); break;
	case T_REALCONST: fprintf(f,"T_REALCONST"); break;
	case T_CHARCONST: fprintf(f,"T_CHARCONST"); break;
	case T_BOOLCONST: fprintf(f,"T_BOOLCONST"); break;
	case T_INTTYPE: fprintf(f,"T_INTTYPE"); break;
	case T_STRTYPE: fprintf(f,"T_STRTYPE"); break;
	case T_REALTYPE: fprintf(f,"T_REALTYPE"); break;
	case T_CHARTYPE: fprintf(f,"T_CHARTYPE"); break;
	case T_BOOLTYPE: fprintf(f,"T_BOOLTYPE"); break;
	case T_AND: fprintf(f,"T_AND"); break;
	case T_OR: fprintf(f,"T_OR"); break;
	case T_NOT: fprintf(f,"T_NOT"); break;
	case T_PLUS: fprintf(f,"T_PLUS"); break;
	case T_MINUS: fprintf(f,"T_MINUS"); break;
	case T_UMINUS: fprintf(f,"T_UMINUS"); break;
	case T_TIMES: fprintf(f,"T_TIMES"); break;
	case T_DIVISION: fprintf(f,"T_DIVISION"); break;
	case T_IN: fprintf(f,"T_IN"); break;
	case T_EQ: fprintf(f,"T_EQ"); break;
	case T_NE: fprintf(f,"T_NE"); break;
	case T_GT: fprintf(f,"T_GT"); break;
	case T_GE: fprintf(f,"T_GE"); break;
	case T_LT: fprintf(f,"T_LT"); break;
	case T_LE: fprintf(f,"T_LE"); break;
	case T_ID: fprintf(f,"T_ID"); break;
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
	case T_STRTYPE:
	case T_REALTYPE:
	case T_CHARTYPE:
	case T_BOOLTYPE:
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
