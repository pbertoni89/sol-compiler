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
	SCHEMA_STRING,
	SCHEMA_BOOLEAN,
	SCHEMA_CHAR,
	SCHEMA_SIMPLE,
	SCHEMA_RECORD,
	SCHEMA_ARRAY
} SchemaType;


//TODO documentation
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
