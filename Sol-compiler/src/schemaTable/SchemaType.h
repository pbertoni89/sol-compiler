/**
 *	\file SchemaType.h
 *	\brief TODO complete the documentation of SchemaType.h
 *
 * 	\date Jul 2, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef SCHEMATYPE_H_
#define SCHEMATYPE_H_

#include <stdio.h>
#include <stdbool.h>

//TODO documentation
typedef enum SchemaType{
	SCHEMA_INT,
	SCHEMA_REAL,
	SCHEMA_CHAR,
	SCHEMA_STRING,
	SCHEMA_BOOLEAN,
	SCHEMA_SIMPLE,
	SCHEMA_STRUCT,
	SCHEMA_VECTOR
} SchemaType;

void storeSchemaType(const char* buffer, SchemaType schematype);

/**\brief return a string representation of the schema type
 *
 * \pre
 * 	\li f open on write mode
 *
 * @param f the file to write the string representation on
 * @param schemaType the schematype to print out
 */
void printSchemaType(FILE* f,SchemaType schemaType);

/**\brief TRUE if the schema represents a simple type
 *
 * A simple type is a non record or non array type
 *
 * @param schemaType the schema type to test
 * @return TRUE if the schema is anything but SCHEMA_RECORD or SCHEMA_ARRAY, false otherwise
 */
bool isSimpleSchema(SchemaType schemaType);

#endif /* SCHEMATYPE_H_ */
