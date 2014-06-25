#include "Node.h"

PNode initNode(NodeType type){
	PNode result=malloc(sizeof(Node));
	if (result==NULL){
		fprintf(stderr,"No enough memory to instanciate new Non terminal node. Exiting.");
		exit(EXIT_FAILURE);
	}
	result->type=type;
	result->value=0;
	result->child=NULL;
	result->brother=NULL;
	return result;
}

//TODO testing
void freeTree(PNode rootNode){
	//free child
	if (rootNode->child!=NULL){
		freeTree(rootNode->child);
	}
	//free first brother
	if (rootNode->brother!=NULL){
		freeTree(rootNode->brother);
	}
	//free actual node
	freeNode(rootNode);
}

void freeNode(PNode node){
	free(node);
}

PNode initIntNode(int value){
	PNode result=initNode(T_INT);
	result->value.intValue=value;
	return result;
}

PNode initRealNode(float value){
	PNode result=initNode(T_REAL);
	result->value.realValue=value;
	return result;
}

PNode initStrNode(char* value){
	PNode result=initNode(T_STR);
	result->value.strValue=value;
	return result;
}

PNode initBoolNode(bool value){
	PNode result=initNode(T_BOOL);
	result->value.boolValue=value;
	return result;
}

PNode initCharNode(char value){
	PNode result=initNode(T_CHAR);
	result->value.charValue=value;
	return result;
}

PNode initIDNode(char* value){
	PNode result=initNode(T_ID);
	result->value.strValue=value;
	return result;
}
