/**
 *	\file utils.h
 *	\brief TODO complete the documentation of utils.h
 *
 * 	\date Jul 5, 2014
 * 	\author koldar
 *	\version 1.0
 */
#ifndef UTILS_H_
#define UTILS_H_

/**\brief compute tha hash of the given string
 *
 * The algorithm used to compute the hash is djb2: you can learn more about it
 * by visiting the page http://www.cse.yorku.ca/~oz/hash.html.
 *
 * This hash is used inside the lexicalTable.
 *
 * @param str the string which compute the hash on
 * @return the hash
 */
unsigned int hashString(char* str);

#endif /* UTILS_H_ */
