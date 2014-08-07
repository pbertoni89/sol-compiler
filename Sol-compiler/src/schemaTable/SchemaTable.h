/**
 *	\file SchemaTable.h
 *	\brief include this file to be able to access to the schema  database
 *
 *	The Schema table is an hashtable storing all the Schema used by the compiler.
 *	It is <b>not</b> directly accessible by the abstact syntax tree, but it is a support
 *	module where all the schema used are stored. In this way there will be only
 *	one instance of a particular type, decrease memory waste
 *
 * 	\date Jul 2, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef SCHEMATABLE_H_
#define SCHEMATABLE_H_

#ifndef __SCHEMATABLE_MAX_FILENAME_LENGTH
#define __SCHEMATABLE_MAX_FILENAME_LENGTH 50
#endif

#include "uthash.h"
#include "SchemaNode.h"
#include "utils.h"

/**\brief represents a cell inside a PSchemaTable
 *
 */
typedef struct SchemaCell {
	/**\brief the hashtable key of this cell
	 *
	 * The  use of this field is <b>reserved</b>. Do not change it.
	 */
	unsigned int key;
	/**\brief represents the Schema held inside this cell.
	 *
	 * \note
	 * A SchemaNode may represents only partially a type. <b>Structured</b>
	 * or <b>indirect</b> schemas need more than one SchemaNode to be fully
	 * described.
	 *
	 */
	SchemaNode node;
	/**\brief used by uthash
	 *
	 * \warning
	 * 	use for internal usage. Do <b>not</b> change it.
	 *
	 */
	UT_hash_handle hh;
} SchemaCell;

/**\brief Represents a hashtable indexing identifiers Schemas
 *
 * \note Because of the "uthash" hashtable header file usage,
 * an hashtable can be described only by its pointer, not by its value.
 * However you will never need the actual value of the hashtable (and
 * if you need it, you are probably making a huge mistake).
 *
 */
typedef SchemaCell* PSchemaTable;

void addVectorTypeInSchemaTable();

void addSimpleTypeInSchemaTable(char* name);

/**\brief get the pointer to one of the 5 SOL primitive schema
 *
 * The SOL primitive types are:
 * \li int;
 * \li char;
 * \li string;
 * \li real;
 * \li boolean;
 *
 * \pre
 *  \li initSchemaTable() must be already called;
 *  \li type is not SCHEMA_SIMPLE or SCHEMA_STRUCT or SCHEMA_VECTOR
 *
 * This function returns a pointer to the SchemaNode inside the Schema hash table which
 * represents the requested primitive type
 *
 * @param type the type to be retrieved
 * @return a pointe to the requested type
 */
SchemaNode* getPrimitiveType(SchemaType type);

/**\brief initialize the schema table by adding the 5 primitive types
 *
 */
void initSchemaTable();

void freeSchemaTable();


//TODO documentation
int drawSchemaTableRecursive(FILE* f,SchemaNode* schemaCell,int nodenumber);

#endif /* SCHEMATABLE_H_ */
