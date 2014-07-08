#include "SchemaType.h"

void printSchemaType(FILE* f,SchemaType schemaType){
	switch (schemaType){
	case SCHEMA_INT: fprintf(f,"int"); break;
	case SCHEMA_ARRAY: fprintf(f,"array"); break;
	case SCHEMA_BOOLEAN: fprintf(f,"boolean"); break;
	case SCHEMA_CHAR: fprintf(f,"char"); break;
	case SCHEMA_REAL: fprintf(f,"real"); break;
	case SCHEMA_RECORD: fprintf(f,"record"); break;
	case SCHEMA_STRING: fprintf(f,"string"); break;
	}
}

bool isSimpleSchema(SchemaType schemaType){
	return (schemaType==SCHEMA_ARRAY || schemaType==SCHEMA_RECORD)?false:true;
}
