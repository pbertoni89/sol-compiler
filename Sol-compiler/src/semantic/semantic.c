#include "semantic.h"

// INHERITED ATTRIBUTES
/**\brief Current OPeration variable
 *
 * TODO documentation
 */
static COP cop;
static PSymbolTable currentSymbolTable;


void cycleThroughChildren(PNode parent,AG* ag){
	PNode tmp=parent->child;
	while (tmp!=NULL){
		sem(tmp,*ag);
		tmp=tmp->brother;
	}
}

AG sem(PNode node,AG ag){
	PNode tmp;

	switch (node->type){

	// ----------------- NON TERMINALS ----------------------

	case NT_PROGRAM:
		sem(node->child,ag); //func_decl
		break;
		//####################################################################################à
	case NT_FUNC_DECL:
		tmp=node->child;
		do {
			sem(tmp,ag);
		} while ((tmp=tmp->brother)!=NULL);
		break;
		//####################################################################################à
	case NT_DECL_LIST_OPT:
		//####################################################################################à
	case NT_DECL_LIST:
		if (cop==COP_CREATING_NEW_TYPE){
			tmp=node->child;
			do{
				sem(tmp,ag); //every decl
			}while((tmp=tmp->brother)!=NULL);
		} else if (cop==COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE){
			do {
				//for every decl we have to compute the head and the tail of the record fields. Then we have to merge all of them into one big list.
				ag=sem(tmp,createDefaultAG()); //connect the various decl
			} while((tmp=tmp->brother)!=NULL);
			//now in ag.headField we have the first field of the struct just built
		}
		break;
		//#####################################################################################
	case NT_DECL:
		if (cop==COP_CREATING_NEW_TYPE){
			//if we are defining a new type we have to compute first of all the schema to create via "domain"
			cop=COP_COMPUTING_DOMAIN_OF_NEW_TYPE;
			ag=sem(node->child->brother,ag); //domain: now we have the schema of the ids;
			//after calling on domain in schema there is the schema to apply to the id-list
			cop=COP_CREATING_NEW_TYPE;
			sem(node->child,ag); //id-list
		}else if (cop == COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE){
			/* if we're defining some fields in the structure we have to merge every id-list into a hige record list.
			 * To do so we use headField and tailField.
			 */
			SchemaNode* fieldType;
			AG tmpRecordAT;

			cop=COP_COMPUTING_DOMAIN_OF_NEW_TYPE; //first of all we have to compute the domain
			tmpRecordAT=sem(node->child->brother,createDefaultAG()); //domain: now in ag.schema is stored the schema of the id-list
			cop=COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE;
			tmpRecordAT->headField=ag->headField;
			tmpRecordAT=sem(node->child,tmpRecordAT); //id_list
			ag->headField=tmpRecordAT->headField;
			//now we know the pointer of the head and of the tail of this partial record field
		}
		break;
		//#####################################################################################
	case NT_ID_LIST:
		if (cop==COP_CREATING_NEW_TYPE){
			/* we have in schema the type to create.
			 * We need to be sure that there aren't any duplicate ids inside this list
			 * and we need to create in the current symbol table the corrispective types.
			 * The schema table already holds the unique instance of the schema.
			 */
			newStringVectorInMemory(&ag.names);
			tmp=node->child;
			do {
				ag=sem(tmp,ag); //id
			} while ((tmp=tmp->brother)!=NULL);
		} else if (cop==COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE){
			/* every id in the id list is a partial list of records of the on going buildin struct. Foreach of them we have to
			 * assign the schema computated. Then, we have to connect each of the id_list wth the next one: in this way
			 * we create the record list.
			 */
			tmp=node->child;
			do {
				ag=sem(tmp,ag);
			}while((tmp=tmp->brother)!=NULL);
			//now we know the pointe rof the head and of the tail of this partial record field
		}
		break;
		//#####################################################################################
	case NT_DOMAIN:
		/* the cop is COP_COMPUTING_DOMAIN_OF_NEW_TYPE: we need to
		 * create a correct schema inside "schema" variable.
		 * TODO in future we also need to create a schema in schema table
		 */
		ag=sem(node->child,ag);
		//now inside "schema" we have the schema to assign to the id-list
		break;
		//#####################################################################################
	case NT_ATOMIC_DOMAIN:
		ag=sem(node->child,ag);//T_INTCONST T_CHARCONST TSTRCONST T_REALCONST T_BOOLCONST
		break;
		//#####################################################################################
	case NT_STRUCT_DOMAIN:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			SchemaNode* structure=newSchemaNodeStruct();
			cop=COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE;
			ag=sem(node->child,ag); //decl list
			structure->subSchema=ag.schema;
			ag.schema=structure;
		}else {

		}
		break;
		//####################################################################################à
	case NT_VECTOR_DOMAIN:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			if (!(node->child->value.intValue>0)){
				semError("array must have non zero positive length (not %d)",node->child->value.intValue);
			}
			SchemaNode* vector=newSchemaNodeVector(node->child->value.intValue);
			ag=sem(node->child->brother,ag); //computing cell schema
			vector->subSchema=ag.schema;
			ag.schema=vector;
			//TODO if we were to use a schema table, we would have to differentiate between the first time we computer vector domain (insertion in schema table) and all the other following time (update schema in schema table)
		}else {

		}
		break;
		//####################################################################################à
	case NT_TYPE_SECT_OPT:
		//this node may have no children (it is optional)
		if (node->child!=NULL){
			cop=COP_CREATING_NEW_TYPE;
			sem(node->child,createDefaultAG()); //decl_list
		}
		break;
		//####################################################################################à

		// ----------------- TERMINALS --------------------

	case T_ID:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			/* here we are computing an id in "domain" nt. we have to find it inside the current
			 * symbol table. If we find it we have to store the instance in "schema" variable.
			 */
			SchemaNode* result=findType(node->child->value.strValue,&currentSymbolTable);
			if (result==NULL){
				semError("type \"%s\"not found.\n",node->child->value.strValue);
			}
			ag.schema=result;
		} else if (cop==COP_CREATING_NEW_TYPE){
			/*In at.names are stored the ids already computed. So we need to check if this id is already
			 * stored inside names.  If so, we must throw an error. If not, we have to add the id in names.
			 */
			if (isStringInVector(&ag.names,node->value.strValue)){
				semError("duplicate IDs names \"%s\" in the same id-list",node->value.strValue);
			}
			//adds type in symbol table
			addTypeInSymbolTable(node->value.strValue,ag.schema,&currentSymbolTable);
			addStringVector(&ag.names,node->value.strValue);
		} else if (cop==COP_COMPUTING_STRUCT_FIELDS_NEW_TYPE){
			/* schema variable holds the SchemaNode representing the domain type. We have to, for each id in the id-list,
			 * clone that SchemaNode and change it to match the right field name. Note tha in this way the memory trace used by SOL
			 * becomes extremely complex to effectively manage (memory leaks HIGHLY possible!)
			 * TODO this makes harder the freeSchemaNode() phase: a schema table is essential in this.
			 */
			SchemaNode* newField=cloneSchemaNode(ag.schema);
			newField->fieldName=node->value.strValue;
			if (ag.headField==NULL){
				//if there is no headField struct it means this ID is the very head of the id-list. So we have to set it to "firstField"
				ag.headField=newField;
			}else {
				//if headField is not NULL the this id represents a field inside the struct which is not the head field.
				newField->nextRecordField=ag.headField;
				ag.headField=newField;
			}
		}
		break;
		//####################################################################################à
	case T_INTTYPE:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			//If we are creating a new schema (for a variable/type/function) we have to create a new primitive schema
			ag.schema=newSchemaNodeInt();
		} else {

		}
		break;
		//####################################################################################à
	case T_REALTYPE:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			//If we are creating a new schema (for a variable/type/function) we have to create a new primitive schema
			ag.schema=newSchemaNodeReal();
		} else{

		}
		break;
		//####################################################################################à
	case T_CHARTYPE:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			//If we are creating a new schema (for a variable/type/function) we have to create a new primitive schema
			ag.schema=newSchemaNodeChar();
		} else{

		}
		break;
		//####################################################################################à
	case T_STRINGTYPE:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			//If we are creating a new schema (for a variable/type/function) we have to create a new primitive schema
			ag.schema=newSchemaNodeString();
		} else {

		}
		break;
		//####################################################################################à
	case T_BOOLEANTYPE:
		if (cop==COP_COMPUTING_DOMAIN_OF_NEW_TYPE){
			//If we are creating a new schema (for a variable/type/function) we have to create a new primitive schema
			ag.schema=newSchemaNodeBoolean();
		} else {

		}
		break;
		//####################################################################################à
	default: break;

	}
	return ag;
}
