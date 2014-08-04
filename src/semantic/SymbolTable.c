#include "SymbolTable.h"

// INTERNAL GLOBAL VARIABLE DECLARATION
static PSymbolTable symbolTable=NULL;

void addVariableInSymbolTable(char* name,PSymbolTable* symbolTable){
	SymbolCell* add;
	int key=hashString(name);
	//HASH_FIND_INT(*symbolTable,&key,add);
	//FIXME check if variable is already present

	add=malloc(sizeof(SymbolCell));
	if (add==NULL){
		fprintf(stderr,"addVariableToSymbolTable malloc failed\n");
		exit(EXIT_FAILURE);
	}
	//fill the new symbol
	add->key=key;
	add->objectName=name;
	add->oid=0; //FIXME understand if it is useful or not
	add->objectType=ST_VAR;
	add->localEnvironment=NULL;
	add->formalParamNumberFunction=0;
	add->nextFormalParam=NULL;
	HASH_ADD_INT(*symbolTable,key,add);
}

void addConstantInSymbolTable(char* name,PSymbolTable* symbolTable){
	SymbolCell* add;
	int key=hashString(name);
	//HASH_FIND_INT(*symbolTable,&key,add);
	//FIXME check if constant is already present

	add=malloc(sizeof(SymbolCell));
	if (add==NULL){
		fprintf(stderr,"addConstantToSymbolTable malloc failed\n");
		exit(EXIT_FAILURE);
	}
	//fill the new symbol
	add->key=key;
	add->objectName=name;
	add->oid=0; //FIXME understand if it is useful or not
	add->objectType=ST_CONST;
	add->localEnvironment=NULL;
	add->formalParamNumberFunction=0;
	add->nextFormalParam=NULL;
	HASH_ADD_INT(*symbolTable,key,add);
}

void addTypeInSymbolTable(char* name,SchemaNode* pschema, PSymbolTable* symbolTable){
	SymbolCell* add;
	int key=hashString(name);
	//HASH_FIND_INT(*symbolTable,&key,add);
	//FIXME check if type is already present

	add=malloc(sizeof(SymbolCell));
	if (add==NULL){
		fprintf(stderr,"addTypeToSymbolTable malloc failed\n");
		exit(EXIT_FAILURE);
	}
	//fill the new symbol
	add->key=key;
	add->objectName=name;
	add->oid=0; //FIXME understand if it is useful or not
	add->objectType=ST_TYPE;
	add->objectSchema=pschema;
	add->localEnvironment=NULL;
	add->formalParamNumberFunction=0;
	add->nextFormalParam=NULL;
	HASH_ADD_INT(*symbolTable,key,add);
}

SymbolCell* findType(char* name,PSymbolTable* symbolTable){
	SymbolCell* result;
	int key=hashString(name);
	HASH_FIND_INT(*symbolTable,&key,result);
	return result;
}

//TODO testing
void freeSymbolTableRecursive(PSymbolTable* _st){
	SymbolCell* current;
	SymbolCell* reserved;
	HASH_ITER(hh,*_st,current,reserved){
		//free the current SymbolCell
		//current->name has not to be freed here because it is freed by calling freeLexicalTable();
		//current->objectSchema has not to be freed here because it is freed by calling freeSchemaTable();
		//current->localEnvironment must be freed here
		freeSymbolTableRecursive(&current->localEnvironment);
		//current->nextFormalParam has not to be freed here becaus it will be freed anyway since it is retrievable inside the symbolTable
		free(current);
	}
}

//TODO testing
void freeSymbolTable(){
	freeSymbolTableRecursive(&symbolTable);
}
