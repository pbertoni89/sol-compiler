/**
 *	\file semantic.h
 *	\brief TODO complete the documentation of semantic.h
 *
 * 	\date Jul 8, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include <stdlib.h>

#include "StringVector.h"
#include "SchemaTable.h"
#include "SymbolTable.h"
#include "Node.h"

#define semError(message,...) \
		fprintf(stderr,message"\n",__VA_ARGS__); \
		exit(EXIT_FAILURE)




/**\brief represents the possible value of the current operation variable
 *
 */
typedef enum COP {
	/**\brief assigned when the semantic analyzer is computing the fields of a new struct
	 * that will act as a new type inside a symbol table.
	 */
	COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE,
	/**\brief assigned when the semantic analyzer is computing the domain of a new type
	 * that will be added inside a particular symbol table
	 *
	 */
	COP_COMPUTING_DOMAIN_OF_NEW_TYPE,
	/**\brief assigned when the semantic analyzer is computing a TYPE_SECT_OPT
	 *
	 */
	COP_CREATING_NEW_TYPE
} COP;

void cycleThroughChildren(PNode parent,AG* at);

AG sem(PNode node,AG at);

#endif /* SEMANTIC_H_ */
