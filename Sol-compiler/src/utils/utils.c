#include "utils.h"

//TODO testing
char* initString(char* _string){
	char* result=malloc(strlen(_string)+1);
	if (result==NULL){
		fprintf(stderr,"initString: malloc call NULL");
		return NULL;
	}
	strcpy(result,_string);
	return result;
}
