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


/**\brief Represents the Attribute Grammar
 *
 */
typedef struct AT {
	PStringVector names;
} AT;

/**\brief represents the possible value of the current operation variable
 *
 */
typedef enum COP {
	COP_TYPEDEFINITION //!< COP_TYPEDEFINITION
} COP;

void cycleThroughChildren(PNode parent,AT* at);

void sem(PNode node,AT at);

#endif /* SEMANTIC_H_ */
