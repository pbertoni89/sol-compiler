#include "utils.h"

char* initString(char* _string){
	char* result=malloc(strlen(_string)+1);
	if (result==NULL){
		fprintf(stderr,"initString: malloc call NULL");
		return NULL;
	}
	strcpy(result,_string);
	return result;
}

char* initQuotedString(char* _string){
	//length of string plus '\0' character minus the first and the last string character
	char* result=(char*)malloc(strlen(_string)+1-2);
	if (result==NULL){
		fprintf(stderr,"initQuotedString: malloc call NULL");
		return NULL;
	}
	char* strstart=result;
	_string++; //the first quote character must be ignored
	while (!(*_string=='\"'&&(*(_string+1)=='\0'))){
		//must stop if the current char is quote and the char after quote is actually \0
		*result++=*_string++;
	}
	*result++='\0';
	return strstart;
}
