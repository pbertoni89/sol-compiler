#include "semantic.h"

// INHERITED ATTRIBUTES
/**\brief Current OPeration variable
 *
 * TODO documentation
 */
static COP cop;
static SchemaNode* schema;
static PSymbolTable currentSymbolTable;


void cycleThroughChildren(PNode parent,AT* at){
	PNode tmp=parent->child;
	while (tmp!=NULL){
		sem(tmp,*at);
		tmp=tmp->brother;
	}
}

void sem(PNode node,AT at){
	PNode tmp;

	switch (node->type){
	case NT_PROGRAM:
		sem(node->child,at);
		break;

	case NT_FUNC_DECL:
		cycleThroughChildren(node,&at);
		break;

	case NT_DECL_LIST_OPT:

	case NT_DECL_LIST:

		switch (cop){
		case COP_TYPEDEFINITION:
			cycleThroughChildren(node,&at);
			break;
		default: break;
		}
		break;

	case NT_DECL:
		switch (cop){
		case COP_TYPEDEFINITION:
			sem(node->child->brother,at); //compute domain: now we have the schema of the ids
			sem(node->child,at); //compute id-list
			break;
		}
		break;

	case NT_ID_LIST:
		switch (cop){
		case COP_TYPEDEFINITION:
			//We need to be sure that there aren't any duplicate ids inside this list
			at.names=newStringVector();
			do {
				if (isStringInVector(&at.names,tmp->value.strValue)){
					semError("duplicate IDs names \"%s\" in the same id-list",tmp->value.strValue);
				}
				addStringVector(&at.names,tmp->value.strValue);
				addTypeInSymbolTable(tmp->value.strValue,schema,&currentSymbolTable);
			} while ((tmp=tmp->brother)!=NULL);
			break;
		default: break;
		}
		break;

	case NT_DOMAIN:
		if (node->child->type==T_ID){
			SchemaNode* result=findType(node->child->value.strValue,&currentSymbolTable);
			if (result==NULL){
				semError("type \"%s\"not found.\n",node->child->value.strValue);
			}
			schema=result;
			break;
		}
		sem(node->child,at);
		break;
	case NT_ATOMIC_DOMAIN:
		sem(node->child);
		break;
	case NT_STRUCT_DOMAIN:
	case NT_VECTOR_DOMAIN:
	case NT_TYPE_SECT_OPT:
		//this node may have no children (it is optional)
		if (node->child!=NULL){
			cop=COP_TYPEDEFINITION;
			sem(node->child,at);
		}
		break;
	default: break;

	}
}
