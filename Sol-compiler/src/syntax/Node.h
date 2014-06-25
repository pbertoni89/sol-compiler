/**
 *	\file Node.h
 *	\brief holds information about a syntax tree node.
 *
 * 	\date Jun 22, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>
#include "LexVal.h"
#include "NodeType.h"

/**\brief the type of the possibles types attached to a syntax node
 *
 */
typedef LexVal NodeValue;

/**\brief represents a syntax tree node
 *
 */
typedef struct Node{
	///\brief The type of the node. Can be "non terminal" or "terminal"
	NodeType type;
	///\brief indicates the optional value attached to the node
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
 * \code
 * 	TODO insert example
 * \endcode
 *
 * \pre
 *  \li enough memory in RAM to instanciate the node;
 * \post
 *  \li a new node is in memory;
 *  \li value field is set to 0;
 *  \li child field is set to 0;
 *  \li brother field is ser to 0;
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
void freeTree(PNode rootNode);

/**\brief free the passed node from the memory
 *
 * Note that if the node is part of a syntax tree the function will <b>not</b> dispose of children or siblings.
 * For that purpose you can use freeTree() function.
 *
 * \pre
 *  \li node not NULL;
 * \post
 *  \li node freed;
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
 * \code
 * 	TODO insert example
 * \endcode
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
 * \code
 * 	TODO insert example
 * \endcode
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
 * \code
 * 	TODO insert example
 * \endcode
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
 * \code
 * 	TODO insert example
 * \endcode
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
 * \code
 * 	TODO insert example
 * \endcode
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
 * \code
 * 	TODO insert example
 * \endcode
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

#endif /* NODE_H_ */
