#include "Node.h"

PNode initNode(NodeType type){
	PNode result=malloc(sizeof(Node));
	if (result==NULL){
		fprintf(stderr,"No enough memory to instanciate new Non terminal node. Exiting.");
		exit(EXIT_FAILURE);
	}
	result->type=type;
	//set to 0 all the union struct
	memset(&result->value,0,sizeof(NodeValue));
	result->child=NULL;
	result->brother=NULL;
	return result;
}

void freeSyntaxTree(PNode rootNode){
	//free child
	if (rootNode->child!=NULL){
		freeSyntaxTree(rootNode->child);
	}
	//free first brother
	if (rootNode->brother!=NULL){
		freeSyntaxTree(rootNode->brother);
	}
	//free actual node
	freeNode(rootNode);
}

void freeNode(PNode node){
	//since all the strings are stored inside the lexicalTable,
	//we don't have to free the char* string.
	//Instead, you have to MANUALLY free them by invoking freeLexStringHashTable()
	//		if (node->type==T_STRCONST || node->type==T_ID){
	//			//we have to free the string attached to the node
	//			free(node->value.strValue);
	//		}
	node->type=0;
	memset(&node->value,0,sizeof(NodeValue));
	node->child=NULL;
	node->brother=NULL;
	free(node);
}

PNode initIntNode(int value){
	PNode result=initNode(T_INTCONST);
	result->value.intValue=value;
	return result;
}

PNode initRealNode(float value){
	PNode result=initNode(T_REALCONST);
	result->value.realValue=value;
	return result;
}

PNode initStrNode(char* value){
	PNode result=initNode(T_STRCONST);
	result->value.strValue=value;
	return result;
}

PNode initBoolNode(bool value){
	PNode result=initNode(T_BOOLCONST);
	result->value.boolValue=value;
	return result;
}

PNode initCharNode(char value){
	PNode result=initNode(T_CHARCONST);
	result->value.charValue=value;
	return result;
}

PNode initIDNode(char* value){
	PNode result=initNode(T_ID);
	result->value.strValue=value;
	return result;
}

bool drawSyntaxTreeGraph(const char* filename,PNode root,bool jpgimage,bool removedotfile){
	char buffer[__PARSER_TOOLS_MAX_FILENAME_LENGTH];
	sprintf(buffer,"grp/%s.dot",filename);
	FILE* f=fopen(buffer,"w");
	if (f==NULL){
		fprintf(stderr,"parser-tools.c:buildSyntaxTreeGraph:can't create file grp/%s.dot!\n",filename);
		return false;
	}
	fprintf(f,"digraph %s {\n",filename);
	drawSyntaxNodeRecursive(f,root,0,1);
	fprintf(f,"}");
	fflush(f);
	fclose(f);
	if (jpgimage==true){
		char command[3*__PARSER_TOOLS_MAX_FILENAME_LENGTH];
		sprintf(command,"dot -Tjpg grp/%s.dot -o grp/%s.jpg",filename,filename);
		int result=system(command);
		if (result!=0){
			fprintf(stderr,"parser-tools.c:buidlSyntaxTreeGraph:can't create jpg image %s.jpg!\n",filename);
			return false;
		}
	}
	if (removedotfile==true){
		char command[10+__PARSER_TOOLS_MAX_FILENAME_LENGTH];
		sprintf(command,"rm grp/%s.dot",filename);
		int result=system(command);
		if (result!=0){
			fprintf(stderr,"parser-tools.c:buildSyntaxTreeGraph:can't remove %s.dot!\n",filename);
			return false;
		}
	}
	return true;
}

int drawSyntaxNodeRecursive(FILE* f,PNode pnode,int nodenumber,int childnumber){
	int childNodeUsed=0;
	int brotherNodeUsed=0;
	if (pnode->brother!=NULL && childnumber==1){
		//the node has at least a brother; since every brother has the same dot.rank a subgraph needs to be created
		//this node is the first child. So we need to write the "open subgraph" token
		fprintf(f,"{\n");
		fprintf(f,"rank=same;\n");
	}
	//---------- NODE CREATION -------------
	fprintf(f,"n%02d",nodenumber);
	fprintf(f,"[label=\"");
	printNodeType(f,pnode->type);
	if (isTerminal(pnode->type)){
		fprintf(f,"\\n");
		switch (pnode->type){
		case T_BOOLCONST: fprintf(f,"%s",pnode->value.boolValue==1?"true":"false"); break;
		case T_CHARCONST: fprintf(f,"%c",pnode->value.charValue); break;
		case T_INTCONST: fprintf(f,"%d",pnode->value.intValue); break;
		case T_REALCONST: fprintf(f,"%f",pnode->value.realValue); break;
		case T_STRCONST: fprintf(f,"%s",pnode->value.strValue); break;
		case T_ID: fprintf(f,"%s", pnode->value.strValue); break;
		default: break;
		}
	}
	fprintf(f,"\"");
	if (isTerminal(pnode->type)){
		fprintf(f," style=\"filled\" fillcolor=\"yellow\"");
	}
	fprintf(f,"];\n");
	//--------------END NODE CREATION ------------------

	if (pnode->brother!=NULL){
		fprintf(f,"n%02d -> n%02d [color=blue];\n",nodenumber,nodenumber+1);
		brotherNodeUsed=drawSyntaxNodeRecursive(f,pnode->brother,nodenumber+1,childnumber+1);
	}
	if (pnode->brother==NULL && childnumber!=1){//this node has no further brother; however it is the last children a unknown parent has. So we have to close the subgraph
		fprintf(f,"}\n");
	}
	if (pnode->child!=NULL){
		fprintf(f,"n%02d -> n%02d [color=red];\n",nodenumber,nodenumber+brotherNodeUsed+1);
		childNodeUsed=drawSyntaxNodeRecursive(f,pnode->child,nodenumber+brotherNodeUsed+1,1);//pnode->child is the first child, so the brothernumebr is set to 1
	}
	return childNodeUsed+brotherNodeUsed+1;
}
