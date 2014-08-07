#include "SchemaType.h"

void printSchemaType(FILE* f,SchemaType schemaType){
	switch (schemaType){
	case SCHEMA_INT: fprintf(f,"int"); break;
	case SCHEMA_VECTOR: fprintf(f,"vector"); break;
	case SCHEMA_BOOLEAN: fprintf(f,"boolean"); break;
	case SCHEMA_CHAR: fprintf(f,"char"); break;
	case SCHEMA_REAL: fprintf(f,"real"); break;
	case SCHEMA_STRUCT: fprintf(f,"struct"); break;
	case SCHEMA_STRING: fprintf(f,"string"); break;
	}
}

bool isSimpleSchema(SchemaType schemaType){
	return (schemaType==SCHEMA_VECTOR || schemaType==SCHEMA_STRUCT)?false:true;
}
