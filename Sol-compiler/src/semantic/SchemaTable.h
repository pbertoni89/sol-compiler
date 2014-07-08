/**
 *	\file SchemaTable.h
 *	\brief include this file to be able to access to the schema  database
 *
 *	TODO improve documentation
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
#include "SchemaType.h"
#include "utils.h"

/**\brief represents a schema node.
 *
 * Schema nodes are the base to correctly represents a schema.
 * Usually various nodes identify one schema.
 *
 *
 */
typedef struct SchemaNode {
	/**\brief represents the type of the node held
	 *
	 * For further information, please see SchemaType
	 *
	 */
	SchemaType type;
	/**\brief represents a name associated with this node.
	 *
	 * This variable represents the name of a "field" record. For example, if the
	 * type is:
	 *
	 * c: struct ( a: int; b:string;);
	 *
	 * This variable will be "a" in the first SchemaNode and "b" in the second one.
	 * Not all nodes has such value.
	 *
	 * \verbinclude schemaNodesFields.dox
	 */
	char* fieldName;
	/**\brief represents the array size of a SchemaNode representing an array.
	 *
	 * For example:
	 *
	 * c: vector [10] of int;
	 *
	 * This variable will be equal to 10. Not all nodes has such value
	 *
	 * \verbinclude schemaNodesFields.dox
	 */
	int arraySize;
	/**\brief represents an optional SchemaNode pointing to a secondary type.
	 *
	 * This field is essential with <b>structured</b> or <b>indirect</b> types:
	 * \li ARRAY: if you have an array you have to tell to the compiler what is the type of each array cell.
	 * \li STRUCT: if you have a struct you have to tell to the compiler where it can find
	 * 	the list enumerating all the fields owned by the struct itself;
	 * \li ID: if you have a named type you have to tell to the compiler where it can find
	 * 	the definition of that type.
	 *
	 * Not all nodes has this field.
	 *
	 * \verbinclude schemaNodesFields.dox
	 *
	 */
	struct SchemaNode* subSchema;
	/**\brief represents the next record field owned by a struct
	 *
	 * Let's suppose we want to create the struct:
	 *
	 * c: struct ( a: int; b:string;);
	 *
	 * to do that we need to create a SchemaNode typed SCHEMA_STRUCT. Then, we need to create a list
	 * of SchemaNodes. This field represents the next SchemaNode representing the next record field type.Not all nodes has this field.
	 *
	 * \verbinclude schemaNodesFields.dox
	 *
	 */
	struct SchemaNode* nextRecordField;
} SchemaNode;

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

void addSimpleTypeInSchemaTable(char* name);

void freeSchemaTable();

//TODO documentation
int drawSchemaTableRecursive(FILE* f,SchemaNode* schemaCell,int nodenumber);

#endif /* SCHEMATABLE_H_ */
