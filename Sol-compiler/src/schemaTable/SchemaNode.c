#include "SchemaNode.h"

SchemaNode* newSchemaNode(SchemaType _type,char* _fieldname,int _arraySize, SchemaNode* _subSchema, SchemaNode* _nextRecordField){
	SchemaNode* result=malloc(sizeof(SchemaNode));
	if (result==NULL){
		fprintf(stderr,"malloc failed in newSchemaNode function\n");
		exit(EXIT_FAILURE);
	}
	result->type=_type;
	result->fieldName=_fieldname;
	result->arraySize=_arraySize;
	result->subSchema=_subSchema;
	result->nextRecordField=_nextRecordField;
	return result;
}

SchemaNode* newSchemaNodeVector(int length){
	return newSchemaNode(SCHEMA_VECTOR,NULL,length,NULL,NULL);
}

SchemaNode* newSchemaNodeStruct(){
	return newSchemaNode(SCHEMA_STRUCT,NULL,0,NULL,NULL);
}

SchemaNode* cloneSchemaNode(SchemaNode* original){
	SchemaNode* result=malloc(sizeof(SchemaNode));
	if (result==NULL){
		fprintf(stderr,"SchemaNode.c cloneSchemaNode malloc failed");
		exit(EXIT_FAILURE);
	}
	memcpy(result,original,sizeof(SchemaNode));
	return result;
}

SchemaNode* newSchemaNodeID(){
	return newSchemaNode(SCHEMA_SIMPLE,NULL,0,NULL,NULL);
}

SchemaNode* newSchemaNodeInt(){
	return newSchemaNode(SCHEMA_INT,NULL,0,NULL,NULL);
}

SchemaNode* newSchemaNodeReal(){
	return newSchemaNode(SCHEMA_REAL,NULL,0,NULL,NULL);
}

SchemaNode* newSchemaNodeChar(){
	return newSchemaNode(SCHEMA_CHAR,NULL,0,NULL,NULL);
}

SchemaNode* newSchemaNodeString(){
	return newSchemaNode(SCHEMA_STRING,NULL,0,NULL,NULL);
}

SchemaNode* newSchemaNodeBoolean(){
	return newSchemaNode(SCHEMA_BOOLEAN,NULL,0,NULL,NULL);
}


unsigned int hashSchema(SchemaNode* schema){
	unsigned long hash = 5381;
	int i;
	//tmp array length
	int length=sizeof(SchemaNode);

	i=0;
	while (i<length){
		hash = ((hash << 5) + hash) + *((char*)schema+i); /* hash * 33 + c */
		i++;
	}
	return hash;
}
