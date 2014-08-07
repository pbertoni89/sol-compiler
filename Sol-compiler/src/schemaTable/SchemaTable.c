#include "SchemaTable.h"

//INTERNAL GLOBAL VARIABLES
static PSchemaTable schemaTable=NULL;
static SchemaNode* primitiveTypes[5];

//FUNCTIONS

void initSchemaTable(){

	SchemaCell* stub;
	int i;
	SchemaNode addPrimitiveTypes[]={
			{SCHEMA_INT,NULL,0,NULL,NULL},
			{SCHEMA_REAL,NULL,0,NULL,NULL},
			{SCHEMA_CHAR,NULL,0,NULL,NULL},
			{SCHEMA_STRING,NULL,0,NULL,NULL},
			{SCHEMA_BOOLEAN,NULL,0,NULL,NULL},
	};

	for (i=0;i<5;i++){
		int key=hashSchema(&(addPrimitiveTypes[i]));
		stub=(SchemaCell*)malloc(sizeof(SchemaCell));
		if (stub==NULL){
			fprintf(stderr,"initSchemaTable malloc failed\n");
			exit(EXIT_FAILURE);
		}
		stub->key=key;
		stub->node=addPrimitiveTypes[i];
		//adds primitive type in hashtable
		HASH_ADD_INT(schemaTable,key,stub);
		//update cache table primitivesType
		primitiveTypes[i]=&(stub->node);
	}
}

SchemaNode* getPrimitiveType(SchemaType type){
	return primitiveTypes[type];
}

void addSimpleTypeInSchemaTable(char* name){
	SchemaCell* add;
	int key=hashString(name);
	//HASH_FIND_INT(*symbolTable,&key,add);
	//FIXME check if type is already present

	add=malloc(sizeof(SchemaCell));
	if (add==NULL){
		fprintf(stderr,"addTypeToSymbolTable malloc failed\n");
		exit(EXIT_FAILURE);
	}
	//fill the new symbol
	add->key=key;
	add->node.type=SCHEMA_SIMPLE;
	add->node.fieldName=name;
	add->node.arraySize=0;
	//FIXME add ID sub schema
	add->node.subSchema=NULL;
	add->node.nextRecordField=NULL;

	HASH_ADD_INT(schemaTable,key,add);
}

void freeSchemaTable(){
	SchemaCell* current;
	SchemaCell* reserved;
	HASH_ITER(hh,schemaTable,current,reserved){
		//free the current SchemaCell
		//current->name has not to be freed here because it is freed by calling freeLexicalTable();
		//current->nextRecordFIeld has not to be freed here because it is retrievable in schemaTable anyway.
		//current->subSchema has not to be freed here because it is freed by calling freeSchemaTable anyway
		free(current);
	}
}

bool buildSchemaTableGraph(const char* filename,bool jpgimage,bool removedotfile){
	char buffer[__SCHEMATABLE_MAX_FILENAME_LENGTH];
	sprintf(buffer,"grp/%s.dot",filename);
	FILE* f=fopen(buffer,"w");
	if (f==NULL){
		fprintf(stderr,"SchemaTable.c:buildSyntaxTreeGraph:can't create file grp/%s.dot!\n",filename);
		return false;
	}
	fprintf(f,"digraph %s {\n",filename);
	SchemaCell* current;
	int nodenumber=0;
	for (current=schemaTable;current!=NULL; current=(SchemaCell*)current->hh.next){
		nodenumber=drawSchemaTableRecursive(f,&(current->node),nodenumber);
	}
	fprintf(f,"}");
	fflush(f);
	fclose(f);
	if (jpgimage==true){
		char command[3*__SCHEMATABLE_MAX_FILENAME_LENGTH];
		sprintf(command,"dot -Tjpg grp/%s.dot -o grp/%s.jpg",filename,filename);
		int result=system(command);
		if (result!=0){
			fprintf(stderr,"SchemaTable.c:buidlSyntaxTreeGraph:can't create jpg image %s.jpg!\n",filename);
			return false;
		}
	}
	if (removedotfile==true){
		char command[10+__SCHEMATABLE_MAX_FILENAME_LENGTH];
		sprintf(command,"rm grp/%s.dot",filename);
		int result=system(command);
		if (result!=0){
			fprintf(stderr,"SchemaTable.c:buildSyntaxTreeGraph:can't remove %s.dot!\n",filename);
			return false;
		}
	}
	return true;
}

/**
 *
 * @param f
 * @param schemaCell
 * @param nodenumber
 * @return the next node number avaiable to use
 */
int drawSchemaTableRecursive(FILE* f,SchemaNode* schemaCell,int nodenumber){

	// -- NODE CREATION --
	fprintf(f,"n%04d",nodenumber);
	fprintf(f,"[label=\"");
	printSchemaType(f,schemaCell->type);
	switch (schemaCell->type){

	case SCHEMA_BOOLEAN:
	case SCHEMA_CHAR:
	case SCHEMA_INT:
	case SCHEMA_REAL:
	case SCHEMA_STRING:
		fprintf(f,"\" style=\"bold\"];\n");
		break;
	case SCHEMA_SIMPLE:
		fprintf(f,"\\n%s\" style=\"filled\" fillcolor=\"yellow\"];\n",schemaCell->fieldName);
		break;
	case SCHEMA_STRUCT:
		fprintf(f,"\"];\n");
		fprintf(f,"{\n");
		fprintf(f,"rank=same;\n");
		SchemaNode* celltmp=schemaCell->subSchema;
		int oldnode=nodenumber+1;
		int newnode=0;
		do {
			newnode=drawSchemaTableRecursive(f,celltmp,oldnode);
			fprintf(f,"n%04d -> n%04d;\n",oldnode,newnode);
			oldnode=newnode;
		} while ((celltmp=celltmp->nextRecordField)!=NULL);
		fprintf(f,"n%04d -> n%04d;\n",nodenumber,nodenumber+1);
		fprintf(f,"}\n");
		return newnode;
		break;
	case SCHEMA_VECTOR:
		fprintf(f,"\\n%d\"];\n",schemaCell->arraySize);
		fprintf(f,"{\n");
		fprintf(f,"rank=same;\n");
		int tmp=drawSchemaTableRecursive(f,schemaCell->subSchema,nodenumber+1);
		fprintf(f,"n%04d -> n%04d;\n",nodenumber,nodenumber+1);
		fprintf(f,"}\n");
		return tmp;
		break;
	}
	// -- END NODE CREATION --

	return nodenumber+1;

}

