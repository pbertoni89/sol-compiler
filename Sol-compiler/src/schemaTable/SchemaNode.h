/**
 *	\file SchemaNode.h
 *	\brief Represents a single node of a schema.
 *
 *	How the compiler can represents primitive or more complex types such:
 *
 *	\code
 *		t: struct (a:string; b:vector[4] of int; c:real;  d:int;);
 *	\endcode
 *
 *	The answer is via a particular graph called "Schema". A Schema is a Direct Acyclic Graph which synthetizes
 *	the type. in The previous example, it is organized as such:
 *
 *	\dotfile schema_example.dot
 *
 *	As you may know, SOL has types divided into 2 categories:
 *	\li primitive types: int, real, char, string and bool;
 *	\li structured types: id, struct, vector;
 *
 *	While primitive types are represented by a single SchemaNode, structured types
 *	are represented by (generally) a tree of SchemaNode.
 *
 *	The struct schema is handled in the way explained by the figure:
 *
 *	\dotfile schema_struct.dot
 *
 *	TODO list other structure
 *
 * 	\date Jul 11, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef SCHEMANODE_H_
#define SCHEMANODE_H_

#include <stdlib.h>
#include "SchemaType.h"

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

/**\brief initialize a generic SchemaNode
 *
 *	The function does <b>no input parameter checking</b>: so you have to do all the checking yourself.
 *	\warning
 *		Use this function at your own risk. You should only use this method if you are knowing what you are doing.
 *
 * @param _type the SchemaType of this SchemaNode
 * @param _fieldname
 * @param _arraySize
 * @param _subSchema
 * @param _nextRecordField
 * @return
 */
SchemaNode* newSchemaNode(SchemaType _type,char* _fieldname,int _arraySize, SchemaNode* _subSchema, SchemaNode* _nextRecordField);

SchemaNode* cloneSchemaNode(SchemaNode* original);

SchemaNode* newSchemaNodeVector(int length);

SchemaNode* newSchemaNodeStruct();

SchemaNode* newSchemaNodeID();

SchemaNode* newSchemaNodeInt();

SchemaNode* newSchemaNodeChar();

SchemaNode* newSchemaNodeReal();

SchemaNode* newSchemaNodeString();

SchemaNode* newSchemaNodeBoolean();

unsigned int hashSchema(SchemaNode* schema);

#endif /* SCHEMANODE_H_ */
