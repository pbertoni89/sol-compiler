#include "lexicalTable.h"

//variable visible only to this translation unit (see http://stackoverflow.com/questions/1856599/when-to-use-static-keyword-before-global-variables)
static PLexStringHT hashTableLexString=NULL;

char* addLexStringInHashTable(char* str){
	//first of all let's check wheter this string is already contained in the hash table
	unsigned int strID=hashString(str);
	LexString* result;
	HASH_FIND_INT(hashTableLexString,&strID,result);

	if (result!=NULL){
		//the string is already present in the hashtable, so we skip it
		return result->str;
	}

	//the string must be added to the hashtable
	LexString* newStr=malloc(sizeof(LexString));
	if (newStr==NULL){
		fprintf(stderr,"addLexString malloc returned NULL");
		exit(EXIT_FAILURE);
	}
	newStr->id=strID;
	newStr->str=malloc(strlen(str)+1);
	if (newStr==NULL){
			fprintf(stderr,"addLexString malloc returned NULL");
			exit(EXIT_FAILURE);
		}
	strcpy(newStr->str,str);
	HASH_ADD_INT(hashTableLexString,id,newStr);
	return newStr->str;
}

void freeLexStringHashTable(){
	LexString* hashcell;
	LexString* reserved;
	HASH_ITER(hh,hashTableLexString,hashcell,reserved) {
		//free the hashcell->str
		free(hashcell->str);
		//free the entire structure
		free(hashcell);
	}
}
