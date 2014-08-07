#include "StringVector.h"

//GLOBAL VARIABLES FOR INTERNAL USE

//reference http://troydhanson.github.io/uthash/utarray.html#_about_ut_icd
static UT_icd charptr_icd = {
		//size of char*
		sizeof(char*),
		//what happen when creating a new element
		NULL,
		//since we need to store only the pointer to the string, we need no additional allocation
		NULL,
		//since strings are freed by the call freeLexicalTable(), here we have to free nothing
		NULL
};

static int strsort(const void *_a, const void *_b) {
  char* a = *(char**)_a;
  char* b = *(char**)_b;
  return strcmp(a,b);
}

StringVector* newStringVector(){
	StringVector* result;
	utarray_new(result,&charptr_icd);
	return result;
}

void newStringVectorInMemory(StringVector* vector){
	utarray_new(vector,&charptr_icd);
}

bool isStringInVector(StringVector* vector,char* str){
	char* result=utarray_find(vector,str,strsort);
	return result!=NULL;
}

void addStringVector(StringVector* vector,char* str){
	utarray_push_back(vector,&str);
	utarray_sort(vector,strsort);
}

void freeStringVector(StringVector* vector){
	utarray_free(vector);
}
