/**
 *	\file NodeType.h
 *	\brief include a list of terminal/non terminal definitions
 *
 * 	\date Jun 22, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef NODETYPE_H_
#define NODETYPE_H_

#include <stdbool.h>
#include <stdio.h>

/* To get all the terminal/non terminal definition in this file
 * cat NodeType.h | sed '/^\s\s*\([A-Z_0-9][A-Z_0-9]*\)/!d' | sed 's/\s\s*\|,//g'
 *
 * //cat NodeType.h | sed '/^\s\s*\([A-Z_0-9][A-Z_0-9]*\)/!d' | sed 's/\s\s*\|,//g' | sed 's/\(.*\)/\1\1/g'
 */


typedef enum {

	// ############### Non terminal ################
	NT_PROGRAM,
	NT_FUNC_DECL,
	NT_DECL_LIST_OPT,
	NT_DECL_LIST,
	NT_DECL,
	NT_ID_LIST,
	NT_DOMAIN,
	NT_ATOMIC_DOMAIN,
	NT_STRUCT_DOMAIN,
	NT_VECTOR_DOMAIN,
	NT_TYPE_SECT_OPT,
	NT_VAR_SECT_OPT,
	NT_CONST_SECT_OPT,
	NT_CONST_DECL_LIST,
	NT_CONST_DECL,
	NT_FUNC_LIST_OPT,
	NT_FUNC_LIST,
	NT_FUNC_BODY,
	NT_STAT_LIST,
	NT_STAT,
	NT_ASSIGN_STAT,
	NT_LEFT_HAND_SIDE,
	NT_FIELDING,
	NT_INDEXING,
	NT_IF_STAT,
	NT_ELSIF_STAT_LIST_OPT,
	NT_ELSIF_STAT_LIST,
	NT_ELSE_STAT_OPT,
	NT_WHILE_STAT,
	NT_FOR_STAT,
	NT_FOREACH_STAT,
	NT_RETURN_STAT,
	NT_READ_STAT,
	NT_SPECIFIER_OPT,
	NT_WRITE_STAT,
	NT_EXPR,
	NT_BOOL_TERM_LIST,
	NT_BOOL_OP,
	NT_BOOL_TERM,
	NT_REL_OP,
	NT_REL_TERM,
	NT_LOW_TERM_LIST,
	NT_LOW_BIN_OP,
	NT_LOW_TERM,
	NT_HIGH_BIN_OP,
	NT_FACTOR_LIST,
	NT_FACTOR,
	NT_UNARY_OP,
	NT_ATOMIC_CONST,
	NT_INSTANCE_CONSTRUCTION,
	NT_STRUCT_CONSTRUCTION,
	NT_EXPR_LIST,
	NT_VECTOR_CONSTRUCTION,
	NT_FUNC_CALL,
	NT_EXPR_LIST_OPT,
	NT_COND_EXPR,
	NT_ELSIF_EXPR_LIST_OPT,
	NT_BUILT_IN_CALL,
	NT_TOINT_CALL,
	NT_TOREAL_CALL,
	NT_DYNAMIC_INPUT,
	NT_DYNAMIC_OUTPUT,

	// ############# Terminal #################

	//const are used for nodes which represents a constant
	T_INTCONST,
	T_STRCONST,
	T_REALCONST,
	T_CHARCONST,
	T_BOOLCONST,
	//type are used in nodes representing a variable/constant type
	T_INTTYPE,
	T_STRINGTYPE,
	T_REALTYPE,
	T_CHARTYPE,
	T_BOOLEANTYPE,
	//operations: a series of operations that can be use inside and expression
	T_AND,
	T_OR,
	T_NOT,
	T_PLUS,
	T_MINUS,
	T_UMINUS,
	T_TIMES,
	T_DIVISION,
	T_IN,
	T_EQ,
	T_NE,
	T_GT,
	T_GE,
	T_LT,
	T_LE,
	//other
	T_ID

} NodeType;

/**\brief Prints a string representation of this object to to file f.
 *
 *
 * The returned string contains no carriage return.
 *
 * \pre
 *  \li f open on write mode
 *  \li f non NULL
 *
 * @param f the file to write on the object
 * @param nodetype the NodeType to write
 */
void printNodeType(FILE* f,NodeType nodetype);

/**\brief TRUE if this node type represents a terminal
 *
 * \verbinclude TerminalList.dox
 *
 * @param nodetype the NodeType to check
 * @return TRUE if the nodetype represents a terminal, false otherwise
 */
bool isTerminal(NodeType nodetype);

/**\brief TRUE if this node type represents a non terminal
 *
 * \verbinclude TerminalList.dox
 *
 * @param nodetype the NodeType to check
 * @return TRUE if the nodetype represents a non terminal, false otherwise
 */
bool isNonTerminal(NodeType nodetype);

#endif /* NODETYPE_H_ */
