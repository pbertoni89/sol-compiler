/**
 *	\file AG.h
 *	\brief Represents the Attribute Grammar used to successfully implement semantic analyzer
 *
 * 	\date Jul 19, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef AG_H_
#define AG_H_

#include <stdlib.h>

/**\brief Represents the Attribute Grammar
 *
 */
typedef struct AG {
	/**\brief keeps track of the first SchemaNode representing a list of field inside a on-building struct.
	 *
	 * Let's suppose we are creating a structure. We need to keep trace of field update: to do so we
	 * need a pointer to the first SchemaNode. Since the SchemaNode holds a pointer to the next SchemaNode representing
	 * a record field, we only need the first SchemaNode to keep trace of the whole list.
	 * headField variable is meant for this very objective.
	 */
	SchemaNode* headField;

	/**\brief represents a list of strings with a semantic meaning.
	 *
	 * The strings can be every thing: IDs, string constants, labels. You can improve performance
	 * by using char pointer instead of strcmp: it is indeed equal if you can assure
	 * the string uniqueness in the string table.
	 * \see lexicalTable
	 */
	StringVector names;
	SchemaNode* schema;
} AG;

AG createDefaultAG();

#endif /* AG_H_ */
