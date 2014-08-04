/**
 *	\file Node.h
 *	\brief holds information about a syntax tree node.
 *
 * Nodes owns 4 properties:
 * \li type;
 * \li value;
 * \li first child;
 * \li right brother;
 *
 * The type indicate a number representing what the nodes is (and ID, a STAT_LIST or a PLUS).
 * Optionally some nodes might have a value: for example an ID owns also a string representing the
 * actual id while a STAT_LIST does not have a value.
 *
 * \verbinclude nodesHavingValue.dox
 *
 * 	\date Jun 22, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "LexVal.h"
#include "NodeType.h"


#define __PARSER_TOOLS_MAX_FILENAME_LENGTH 50

/**\brief the type of the possibles types attached to a syntax node
 *
 */
typedef LexVal NodeValue;

/**\brief represents a syntax tree node
 *
 */
typedef struct Node{
	///\brief The type of the node. Can be "non terminal (starting with NT_)" or "terminal" (starting with T_)
	NodeType type;
	/**\brief indicates the optional value attached to the node.
	 *
	 * Only some NodeType has a meaningful value; the others have this field set to all zeros.
	 *
	 * \verbinclude nodesHavingValue.dox
	 */
	NodeValue value;
	///\brief indicates the first child of the node in the syntax tree
	struct Node* child;
	///\brief indicates the right brother of the node in the syntax tree
	struct Node* brother;
} Node;

typedef Node* PNode;

/**\brief initialize a new syntax tree Node.
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to all zeros;
 *  \li child field is set to 0;
 *  \li brother field is set to 0;
 *
 * @param type the type of the node
 * @return a pointer of the newly created node
 */
PNode initNode(NodeType type);

/**\brief free the all the children (even non direct) and the brother of this node
 *
 *	\dotfile freetree.dot
 *
 *	For example in the figure calling
 *	\code
 *		freeTree(root);
 *	\endcode
 *
 *	will delete the <b>whole</b> tree. Calling the function on root3 will delete only the direct and undirect children of root3, but it will leave
 *	root and root2 (and their children) intact.
 *
 * @param rootNode the start node to delet
 */
void freeSyntaxTree(PNode rootNode);

/**\brief free the passed node from the memory
 *
 * Note that if the node is part of a syntax tree the function will <b>not</b> dispose of children or siblings.
 * For that purpose you can use freeSyntaxTree() function.
 * Another note: in case value field is representing a strValue, this function
 * will <b>not</b> free it: this because since all those strings are retrieval inside
 * the lexical Table you can free all of them <b>manually</b> y invoking freeLexStringHashTable()
 * function.
 *
 * \pre
 *  \li node not NULL;
 * \post
 *  \li node freed;
 *  \li ValueNode field is <b>not</b> freed;
 *
 * @param node the node to be freed
 */
void freeNode(PNode node);

/**\brief initialize a new syntax node representing a int constant
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to value;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
 *
 * @return a pointer of the newly created node
 */
PNode initIntNode(int value);

/**\brief initialize a new syntax node representing a real constant
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to value;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
 *
 * @return a pointer of the newly created node
 */
PNode initRealNode(float value);

/**\brief initialize a new syntax node representing a ID
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 *  \li the pointer passed must not be temporary. The function <b>will not</b> create a copy of the pointer contents
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to value;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
 *
 * @return a pointer of the newly created node
 */
PNode initStrNode(char* value);

/**\brief initialize a new syntax node representing a bool constant
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to value;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
 *
 * @return a pointer of the newly created node
 */
PNode initBoolNode(bool value);

/**\brief initialize a new syntax node representing a char constant
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to value;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
 *
 * @return a pointer of the newly created node
 */
PNode initCharNode(char value);

/**\brief initialize a new syntax node representing a ID
 *
 * The newly created node is not linked to the en construction syntax tree. You must manually attached it
 * to the tree.
 *
 * The function is particullary useful to instanciate non terminal syntax node in Yacc:
 * \include initNodeExample.dox
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 *  \li the pointer passed must not be temporary. The function <b>will not</b> create a copy of the pointer contents
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to value;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
 *
 * @return a pointer of the newly created node
 */
PNode initIDNode(char* value);

/**generate in the graph directory (grp) a .dot file representing the syntax tree
 *
 *	\pre
 *	 \li filename contains only the name of the file (no extension);
 *	 \li filename does hold no "/" or other directory access tokens;
 *	 \li filename is a correct name for a file in the OS;
 *	 \li root is not NULL;
 *	 \li the syntax tree is correct;
 *	\post
 *	 \li up to 2 files (.jpg and .dot) are created in the directory grp, depending of the current
 *	 	values of jpgimage and removedotfile
 *	 \li the generated files are stored in the directory grp
 *
 * @param filename the name of the file
 * @param root the Node used to represents the root of the syntax tree
 * @param jpgimage if TRUE a jpg image is generated automatically; if FALSE, only .dot file is generated
 * @param removedotfile if TRUE the generated dot file is removed from the file system; this option makes some sense only if jpgimage is set to TRUE
 * @return TRUE if there is no error in the function, FALSE otherwise. Error can be:
 * 	\li cannot create the file
 * 	\li dot can't compile the dot file generated
 * 	\li the dot file cannot be removed from the file system
 */
bool drawSyntaxTreeGraph(const char* filename,PNode root,bool jpgimage,bool removedotfile);

/**\brief recursive function to compute dot abstract syntax tree
 *
 * \warning
 * 	Do not use this function if you don't know what are you doing. Use buildSyntaxTreeGraph() instead
 *
 * The output of this function should be this structure:
 * 	\li every 2 node which are brothers has to have the same graph rank;
 * 	\li a parent has a greater rank than its children;
 * 	\li parent-child relationship is marked by a red arrow;
 * 	\li siblings relationship is marked by a blue arrow;
 *
 * The recursive mechanism works:
 * 	\li node brothers are computated first;
 * 	\li child are computated secondly;
 * 	\li nodes are computated horizontally;
 *
 * @param f the file to write on the dot expression;
 * @param pnode the node to be write
 * @param nodenumber the identifier of the node. Every node must have a different identifier;
 * @param childnumber indicates an additional number that represents the child number. If a parent has 5 childs node, the first one (pnode->child)
 * 	has the number 1, while pnode->child->brother has the number 2 and so on.
 * @return the numebr of node which are (directly or indirectly) children of pnode
 */
int drawSyntaxNodeRecursive(FILE* f,PNode pnode,int nodenumber,int childnumber);

#endif /* NODE_H_ */
