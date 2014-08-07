/**
 *	\file SymbolTable.h
 *	\brief include this header to be able to use all the function relative to SOL symbol table.
 *
 *	TODO documentation
 *
 * 	\date Jul 5, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <stdlib.h>
#include "uthash.h"
#include "utils.h"
#include "SchemaTable.h"

/**\brief represents what exactly is a particular symbol
 *
 * This field allows the compiler to recognized a symbol indicating
 * a variable from another one representing the name of a function
 *
 */
typedef enum SymbolType{
	ST_TYPE, //!< \brief ST_TYPE set objectType field in SymbolCell to tell the compiler that symbol is a type
	ST_VAR,  //!< \brief ST_VAR set objectType field in SymbolCell to tell the compiler that symbol is a variable
	ST_CONST,//!< \brief ST_CONST set objectType field in SymbolCell to tell the compiler that symbol is a constant
	ST_FUNC  //!< \brief ST_FUNC set objectType field in SymbolCell to tell the compiler that symbol is a function
} SymbolType;

/**\brief represents a single cell inside the Symbol table hashtable
 *
 * The key and hh field are hashtable related. The other
 * fields represent the actual data stored inside a single cell
 * of the symbol table.
 *
 */
typedef struct SymbolCell {
	int key; /// \brief represents the key of the has table cell

	/**\brief represents the name of the symbol described.
	 *
	 * This is only a pointer. The actual string is stored inside the lexicalTable.
	 */
	char* objectName;
	/**\brief represents the object identifier of this symbol.
	 *
	 * The object identifier (oid) is essentially a number that represents the resource in the
	 * hierartical symbol table. It is different from key field because while the
	 * key field should be unique, there are some symbols (it doesn't matter whtther or not they are equal or not equal)
	 * which have same oid. How?
	 * The object identifier (oid) could be:
	 * \li absolute;
	 * \li relative
	 * FIXME understand if this field is really necessary
	 *
	 */
	int oid;
	/**\brief represents the kind of symbol stored
	 *
	 * See SymbolType for further details.
	 */
	SymbolType objectType;
	/**\brief represents the main type of the symbol
	 *
	 * A symbol can be (from SymbolTable enumeration) a variable, a constant,
	 * a type or a function.
	 * \li variable/constant: represents the type of the variable/constant;
	 * \li type: represents the type itself;
	 * \li functions: represents the return type of the function;
	 */
	SchemaNode* objectSchema;
	/**\brief represents a pointer to a SymbolTable representing the particular function.
	 *
	 * Field used only if objectType is ST_FUNC: points
	 * to another SymbolTable containing all the informations
	 * about that function.
	 *
	 */
	struct SymbolCell* localEnvironment;
	/**\brief number of formal parameters required by the function
	 *
	 * Field used only if objectType is ST_FUNC
	 *
	 */
	int formalParamNumberFunction;
	/**\brief points to the next formal parameter required by the function.
	 *
	 * Field used only if objectType is ST_FUNC
	 *
	 */
	struct SymbolCell* nextFormalParam;

	UT_hash_handle hh;
} SymbolCell;


typedef SymbolCell* PSymbolTable;

//extern PSymbolTable symbolTable;

/**\brief Adds a symbol representing a variable inside a symbol table
 *
 * @param name
 * @param symbolTable
 */
void addVariableInSymbolTable(char* name,PSymbolTable* symbolTable);

/**\brief Adds a symbol representing a constant inside a symbol table
 *
 * @param name
 * @param symbolTable
 */
void addConstantInSymbolTable(char* name,PSymbolTable* symbolTable);

/**\brief Adds a symbol representing a type inside a symbol table
 *
 * @param name
 * @param pschema
 * @param symbolTable
 */
void addTypeInSymbolTable(char* name,SchemaNode* pschema, PSymbolTable* symbolTable);

SymbolCell* findType(char* name,PSymbolTable* symbolTable);

void freeSymbolTable();

#endif /* SYMBOLTABLE_H_ */
