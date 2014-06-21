/**
 *	\file utils.h
 *	\brief contains some useful functions that are used through out all the project
 *
 * 	\date Jun 21, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**\brief create a permanent copy of _string inside the memory and return the pointer to it
 *
 *
 * @param _string the string that will be copied inside the memory
 * @return the pointer to the newly created string in the memory
 */
char* initString(char* _string);

#endif /* UTILS_H_ */
