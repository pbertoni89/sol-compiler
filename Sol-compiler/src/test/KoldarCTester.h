/**\file
 *
 */

/**
 * \mainpage Koldar C Tester: a simple C tester
 * 
 * \section section01 Introduction
 *
 * The KoldarCTester is a single header that can be used to quickly implement
 * a test case for C code. C++ pure code is not supported though.
 *
 * \section section02 To All People who want to setup it quickly
 *
 * If you're in a hurry and want to setup KoldarCTester now, here the basic example
 * to make it work:
 *
 * \code
 * 	#include "KoldarCTester.h"
 *
 * 	//All test function must have no formal parameters and void as return type
 * 	void testSomething(){
 * 		//code something here
 * 		if (a!=5){
 * 			failMsg("a is not 5!\n");
 * 		}
 * 	}
 *
 * 	void testSomethingElse(){
 * 		//code something here
 * 		if (a>4){
 * 			fail();
 * 		}
 * 	}
 *
 * 	int main(){
 *		kct_addTest(testSomething);
 *		kct_addTest(testSomethingElse);
 *
 *		kct_runAllTest(stdout);
 * 	}
 * \endcode
 *
 *	\section section03 How to use KoldarCTester
 *
 *	Now that all the guys in a hurry are satisfied we can discuss how to correctly
 *	use this header. To use it you have to copy "KoldarCTester.h" within your header paths. After
 *	that you can create a new .c files that will be used as a single test suite: if you want
 *	more test suites, you'll have to create more .c files. A single test file .c is divided into 2 parts:
 *	 -# some test functions;
 *	 -# a main function;
 *
 *	 Basically KoldarCTester is a function list manager: you create some function and then you use
 *	 some header function to add them in a list. After that you can execute them all in one command: the
 *	 header handles all the work for you.
 *	 So, first of all, you can create a new file (call it TestInteger.c for example) and include the header:
 *
 *	 \code
 *	 	#include "KoldarCTester.h"
 *	 \endcode
 *
 *	 You have to be sure the header is inside in your "include paths" (maybe through the -I compiler directive).
 *	 Secondly you have to create some test functions. For example, I have created these:
 *
 *	 \code
 *	 	//Create 100 random number between 0 and 9 and test whether or
 *	 	//not the upper and lower bound are not violated.
 *	 	void testRandomX(){
 *			int i;
 *			int n;
 *			for (i=0;i<100;i++){
 *				n=rand()%10;
 *				kct_assertExtremis(0,9,true,true,rand()%10);
 *			}
 *	 	}
 *
 *		//Test if the power of 2 is greater than 0
 *	 	void testPower(){
 *	 		int i;
 *	 		int num;
 *	 		for (i=0;i<100;i++){
 *	 			num=rand()%100;
 *				kct_assertCondition(num*num>=0);
 *	 		}
 *	 	}
 *	 \endcode
 *
 *	 Let's skip up for the moment the "kct_assertExtremis" and "kct_assertCondition" part. Now you have created
 *	 all the test you need to verify some feature of your program. Now you need to run these tests... how? The main
 *	 function does exactly that:
 *
 *	 \code
 *	 	int main(){
 *	 		//add tests in the function list
 *	 		kct_addTest(testRandomX);
 *	 		kct_addTest(testPower);
 *	 		//run the tests
 *	 		kct_runAllTest(stdout);
 *	 	}
 *	 \endcode
 *
 *	 Now you can build it. The compiler will probably complaints about "addTest" and "kct_runAllTest" do nothings:
 *	 don't trust him, these function are actually pretty useful!
 *	 Now try to run the program: you should get something like this:
 *
 *	 \image html image01.png
 *
 *	 The tests are stored in a list: though it might be not so fast
 *	 (like Bjame Stroudtrup say in http://www.youtube.com/watch?v=YQs6IC-vgmo),
 *	 the list are quite easy to understand even for programmers beginner, so everyone
 *	 can improve freely the header. Moreover, unlike other test suite, this header
 *	 is totally <b>free of memory leak</b>. Sure, you can say:
 *	 "well, that's should be obvious!"; well, of course it is, but you'll never
 *	 know what you download out in the internet.
 *
 *	\section section04 Basic Elements in the header
 *
 *	In the header there are basically 6 important elements:
 *	 -# assertions;
 *	 -# function kct_addTest();
 *	 -# function kct_addTestImproved();
 *	 -# function kct_runAllTest();
 *	 -# variable currentTest;
 *	 -# variable testList;
 *
 *	 "testList" variable represents the list that will store the functions and some other
 *	 data.
 *
 *	 "currentTest" is the test that is running at the moment; it is mainly
 *	 used to lighten the prototype of the function: in this way the developer
 *	 can <b>focus</b> on the test development insted of wasting time on understand the
 *	 testing suite.
 *
 *	 kct_addTest() is the main function used to add a function in the list.
 *
 *	 kct_addTestImproved() has the same aim of kct_addTest() but with this function
 *	 you can also specify whether or not you want to skip the function.
 *
 *	 kct_runAllTest() is obviously used to execute the test. Note that with this function
 *	 the list is automatically deallocated from the heap: in this way, if you are
 *	 testing memory leak in your code, Koldar C Tester will not produces memory leaks by itself.
 *
 *	\section section05 Assertion
 *
 *	As we have introduce in the previous section, one of the most important things
 *	in the header are assertions. Assertions are shortcuts to test some conditions:
 *	if the condition is met nothing happens; otherwise the test is terminate and the
 *	header alerts you that in the specific test something went wrong.
 *
 *	For example, let assume you want to determinate if a pointer to a FILE returned
 *	by fopen is NULL or not. Normally you do something like this:
 *
 *	\code
 *		FILE* f=fopen("../test/fileToParse.txt","r");
 *		if (f==NULL){
 *			fprintf(stderr,"Cannot open the file!\n");
 *			return;
 *		}
 *	\endcode
 *
 *	This works, but if you have lots of these small control your code readability can
 *	substantly decrease. Assert helps you in that:
 *
 *	\code
 *		FILE* f=fopen("../test/fileToParse.txt","r");
 *		kct_assertNotNullMsg("cannot open the file!\n",f);
 *	\endcode
 *
 *	Smaller and more readable, right? Koldar C Tester let you use a lot of these assertions:
 *	you can read about all of them in the documentation! Generally speaking, however,
 *	assertion are divided into 2 strains:
 *
 *	- <b>pure assertions</b> check only a particular condition;
 *	- <b>message assertion</b> check a particular condition and if it is not met they warn you
 *		with an error message
 *
 *	\section section06 Skip tests
 *
 *	Let assume you have 100 tests regarding a particular big feature of your program.
 *	It is probable that, to execute all 100 tests, your computer needs some time.
 *	If you are sure that some tests (i.e 53 and 67) return a OK status, you might
 *	want to skip them, for not wasting time. Well, you can easily do that using
 *	kct_addTestImproved(someTest,false):
 *
 *	\code
 *		kct_addTestImproved(test51,true);
 *		kct_addTestImproved(test52,true);
 *		kct_addTestImproved(test53,false);
 *		kct_addTestImproved(test54,true);
 *		kct_addTestImproved(test55,true);
 *	\endcode
 *
 *	While the first parameter is again the test function the second
 *	parameter indicates whether or not the computer should actually run
 *	the test: when you want to reexecute the function you can change "false"
 *	to "true".
 *
 *	Sure, you can just comment out the particular "kct_addTest(test53);" line,
 *	but the header let you also handle the skip in this way.
 *
 *	Some notes about how skipping tests influence the result outcomes:
 *	-# the ratio successful tests/Number of tests does count the skipped tests;
 *	-# the ratio failed tests/Number of tests does count the skipped tests;
 *	-# the percentage of successful tests does not count skipped tests;
 *	-# the percentage of failed tests does not count skipped tests;
 *
 *	This means that the percentage of successful tests <b>must always be 100%</b>: if it
 *	isn't, then some tests aren't working. On the other hand the percentage
 *	of failed tests <b>must always be 0%</b>.
 *
 *
 *	\section section07 "Deeper understanding of KoldarCTester.h"
 *
 *	As we have said before, KoldarCTester basically creates a test list and loop over it.
 *
 *	\dot
 *		digraph list {
 *			rankdir="LR";
 *			TestListHead [label="test list head structure\nmetadata"];
 *			A [label="Test 1\n(head)"];
 *			B [label="Test 2"];
 *			C [label="Test 3"];
 *			D [label="Test 4"];
 *			E [label="Test 5"];
 *			F [label="Test 6\n(tail)"];
 *
 *			TestListHead -> A ->B -> C ->D ->E ->F;
 *		}
 *	\enddot
 *
 *	Firstly the list (which in the header has type TestList) is NULL. When someone use the function
 *	kct_addTest() or a similar function, the header automatically initialize the metadata of the list
 *	(stored in a TestList structure). This struct has some metadata like:
 *	 \li head (basilar if you want to loop over the list!);
 *	 \li tail (used to speed up the process of appending test at the tail of the list);
 *	 \li size;
 *
 *	When someone use kct_addTest() (or a similar function) the header automatically initialize a new
 *	element of TestListElement containing a pointer of the test functions (it also contains other small
 *	metadata). The newly created struct is then append at the tail of the list. Some of the metadata stored
 *	in a TestListElement is:
 *	\li the test function;
 *	\li result (the outcome of this test);
 *
 *	The process continue over and over again until the main call kct_runAllTest(): when it happens,
 *	the program	will loop through the TestListElements in the list (starting from the head one);
 *	for each of them the header will run the test function and will update some of the metadata, including
 *	the field result: this result will be important at the end of all tests, when the header has
 *	to generate statistics (like the number of test failures).
 *
 *	To allow such compact APIs, Koldar C Tester uses 2 variables:
 *	\li a default TestList object which is used by every function in the header as default TestList: in this
 *	way there's no need for the developer to manually create and initialize such list;
 *	\li a variable currentTest: while the program iterate through out all the list element, every TestListElement
 *	is stored in a temporary variable. In this way the program can exactly know what TestListElement it is handling;
 *
 *
 * \section section08 "Contacts"
 *
 * If you have suggestions or complains you can email me sending a mail to massimobono1@gmail.com: i won't promise you that you'll receive
 * a quick answer but I hope you understand!
 *
 * \date Nov 27, 2013
 * \author koldar
 * \version 1.0
 */


#ifndef KOLDARCTESTER_H_
#define KOLDARCTESTER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* as suggested in the gcc manual http://gcc.gnu.org/onlinedocs/gcc/Function-Names.html
 * I have added this preprocessorn commands to increase portability of the code in order
 * to get a function name.
 */
#if __STDC_VERSION__ < 199901L
#	if __GNUC__ >= 2
#		define __func__ __FUNCTION__
#	else
# 		define __func__ "<unknown>"
#	endif
#endif

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@ CONTROL MACRO DEFINITIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/**This macro controls the string separator between 2 test function.
 * The default one is the string "**************"
 * Compile your test program with KCT_CONTROLMACRO_TESTSEPARATOR enabled to change the
 * separator between test functions:
 * \code
 *	#define KCT_CONTROLMACRO_TESTSEPARATOR "%%%%%%%%%%%%%%%%"
 * \endcode
 *
 * \image html image02.png
 *
 *
 * \warning
 * 	To enable this custom behaviour, define KCT_CONTROLMACRO_TESTSEPARATOR <b>before</b>
 * 	including KoldarCTester header. In alternative, you may compile your test suite with a "-D" flag
 * 	enabled.
 *
 */
#ifndef KCT_CONTROLMACRO_TESTSEPARATOR
/**
 *
 * \brief Represents the string that separates 2 test function in the output
 *
 */
#	define PRIVATE_KCT_TESTSEPARATOR "**************"
#else
#	define PRIVATE_KCT_TESTSEPARATOR KCT_CONTROLMACRO_TESTSEPARATOR
#endif


/**This macro allows you to change the default string that is printed out after the developer message
 * in the event a test fails. This string will printed only when macro functions like kct_assertEqualXXXMsg()
 * are called; the macro isn't influenting failMsg() or AssertCondMsg() assertions like!
 *
 * If you want to change the default value, define KCT_CONTROLMACRO_ERRORMESSAGE_EXPECTED
 * as your custom string, like in this example:
 *
 * \code
 * 	#define KCT_CONTROLMACRO_ERRORMESSAGE_EXPECTED "\nEXPECTED VALUE"
 * \endcode
 *
 * The default value is: "\nExpected value: ".
 *
 * \warning
 * 	To enable this custom behaviour, define KCT_CONTROLMACRO_ERRORMESSAGE_EXPECTED <b>before</b>
 * 	including KoldarCTester header. In alternative, you may compile your test suite with a "-D" flag
 * 	enabled.
 *
 *
 */
#ifndef KCT_CONTROLMACRO_ERRORMESSAGE_EXPECTED
	/**\brief Represents the string to print before the expected value in the error message
	 * 
	 *
	 * The syntax of the error message is shown here:
	 *
	 * !!!ERROR!!! errorMessage KCT_ERRORMESSAGE_EXPECTED value expected KCT_ERRORMESSAGE_ACTUAL actual value
	 *
	 */
#	define PRIVATE_KCT_ERRORMESSAGE_EXPECTED "\nExpected value: "
#else
#	define PRIVATE_KCT_ERRORMESSAGE_EXPECTED KCT_CONTROLMACRO_ERRORMESSAGE_EXPECTED
#endif

/**This macro allows you to change the default string that is printed out after the developer message
 * in the event a test fails. This string will printed only when macro functions like kct_assertEqualXXXMsg()
 * are called; the macro isn't influenting failMsg() or AssertCondMsg() assertion like!
 *
 * If you want to change the default value, define KCT_CONTROLMACRO_ERRORMESSAGE_ACTUAL
 * as your custom string, like in this example:
 *
 * \code
 * 	#define KCT_CONTROLMACRO_ERRORMESSAGE_ACTUAL "\nACTUAL VALUE"
 * \endcode
 *
 * The default value is: "\nActual value:   ".
 *
 * \warning
 * 	To enable this custom behaviour, define KCT_CONTROLMACRO_ERRORMESSAGE_ACTUAL <b>before</b>
 * 	including KoldarCTester header. In alternative, you may compile your test suite with a "-D" flag
 * 	enabled.
 *
 *
 */
#ifndef KCT_CONTROLMACRO_ERRORMESSAGE_ACTUAL
	/**
	 * \brief Represents the string to print before the actual value in the error message
	 *
	 * The syntax of the error message is shown here:
	 *
	 * !!!ERROR!!! userErrorMessage KCT_ERRORMESSAGE_EXPECTED value expected KCT_ERRORMESSAGE_ACTUAL actual value
	 *
	 */
#	define PRIVATE_KCT_ERRORMESSAGE_ACTUAL "\nActual value:   "
#else
#	define PRIVATE_KCT_ERRORMESSAGE_ACTUAL KCT_CONTROLMACRO_ERRORMESSAGE_ACTUAL
#endif

/**This macro allows you to change the default size of the buffer used to convert values into strings.
 * The buffer is useful only in assertions like kct_assertEqualXXXMsg().
 *
 * \note {The default value is 15}
 *
 * For example, let assume you want to convert the number 1234567890123456789. Being this number much
 * longer than 15 the header will stringify will wrongly. By defining this custom value,
 * you can easily increase the buffer size, solving the problem.
 *
 * \warning
 * 	To enable this custom behaviour, define KCT_CONTROLMACRO_STRINGBUFFER <b>before</b>
 * 	including KoldarCTester header. In alternative, you may compile your test suite with a "-D" flag
 * 	enabled.
 *
 */
#ifndef KCT_CONTROLMACRO_STRINGBUFFER
	/**
	 * Represents the size of the buffer used to convert number (float or integer it doesn't matter)
	 * to strings. The constant is mainly used in the macros like PRIVATE_KCT_ITOA or PRIVATE_KCT_FTOA
	 */
#	define PRIVATE_KCT_STRINGBUFFER 15
#else
#	define PRIVATE_KCT_STRINGBUFFER KCT_CONTROLMACRO_STRINGBUFFER
#endif

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@ STRUCTURES DEFINITIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


/**
 * \brief type of a generic test function.
 *
 * Every test function that has to be added as a test function must have the following prototype:
 *  -* no formal parameters;
 *  -* return type of type "void;
 */
typedef void (*TestFunction)(void);


/**
 * \struct TestListElement
 * \brief Defines a single element of the list.
 *
 */
typedef struct TestListElement {
	/**@brief the test case in the particular cell of the list
	 *
	 */
	TestFunction testFunction;
	/**@brief points to a brief description of what the test does
	 *
	 */
	const char* description;
	/**@brief represents the string to be filled with an error message.
	 *
	 * When an error occurs in the test function pointed by "function" field
	 * this variable points to the error message which can help solving
	 * the problem.
	 */
	char* errorMessage;
	/**@brief holds the result of the test.
	 *
	 * The result of the test can be one the values stored in TestResult.
	 * See the KCT_RESULTOUTCOME_XXX macro set to have further informations.
	 *
	 */
	short result;
	/**@brief controls whether or not you want to skip this test
	 *
	 * Set it to true if you want to skip the test, false otherwise
	 */
	bool skip;
	/**@brief points to the next test function
	 *
	 */
	struct TestListElement* next;
} TestListElement;

/**
 * \struct TestList
 * \brief Represents the entire list of test functions
 *
 */
typedef struct TestList {
	/**@brief represents the first element of the list.
	 *
	 * You can cycle through out the list using the the field "next"
	 * of the TestListElement
	 */
	TestListElement* head;
	/**@brief represents the last element of the list.
	 *
	 * Used to speed up the append operation.
	 */
	TestListElement* tail;
	/**@brief the number of the total test functions in the list
	 *
	 */
	int size;
} TestList;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRIVATE MACRO DEFINITIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/**
 * \brief Represents the outcome of a test function when the test utterly fails
 *
 */
#define PRIVATE_KCT_FAIL 0
/**
 * \brief Represents the outcome of a test function when the test terminates successfully
 *
 */
#define PRIVATE_KCT_SUCCESS 1
/**
 * \brief Represents the outcome of a test function when the test was to be skipped
 *
 */
#define PRIVATE_KCT_SKIPPED 2
/**
 * \brief Represents the outcome of a test function that has not yet been executed
 *
 */
#define PRIVATE_KCT_UNKNOWN 3

/**
 * \brief copy a string in another one
 *
 * It it highly suggested that constantString is a constant String or
 * a simple variable. It is not recommended to use as "constantString" a call to
 * a function because it might decrease performances.
 *
 * \pre
 *  \li destinationpointer has not already been initialized with malloc;
 *  \li destinationpointer has to be of type char*;
 * \post
 *  \li the string in constantString is copied in the heap a the addres destinationpointer
 *
 *  @param [char*]destinationpointer the pointer where the copy of the stirng will be copied
 *  @param [char*]constantString the original string
 *
 */
#define PRIVATE_KCT_COPYSTRING(destinationpointer,constantString) \
	destinationpointer=malloc(strlen(constantString)+1); \
	if (destinationpointer==NULL){ \
		fprintf(stderr,"MaxTester.h:PRIVATE_KCT_COPYSTRING:not enough memory\n"); \
		exit -1; \
	} \
	strcpy((char*)destinationpointer,constantString)

/**
 * \brief convert an integer to string
 *
 * \warning
 * 	It is highly recommended that you use as "string" parameter only a
 * 	simple variable. Complex formula might cause instabilities
 *
 *
 * Some example of this function use might be:
 * \code
 * 	//converts 4 in a string
 *	PRIVATE_KCT_INITSTRING(string,4,"%d");
 *	//converts 4.45 in a string
 *	PRIVATE_KCT_INITSTRING(string,4.45,"%2.3f");
 *	//converts 4 in a string
 *	PRIVATE_KCT_INITSTRING(string,4,"%lu");
 * \endcode
 *
 * \pre
 *  \li string must not be initialized
 *  \li string must be of type char*
 *  \li num must be of type number; it might be:
 *   -* int
 *   -* short
 *   -* long
 *   -* float
 *   -* double
 *   -* various unsigned
 *  \li conversion must be a constant string;
 *  \li conversion must be a conversion printf format string;
 * \post
 *  \li string contains a string representation of num;
 *  \li string lead to an allocated space of memory that <b>must</b> be free manually with PRIVATE_KCT_FREESTRING();
 *
 *  @param string the pointer that will lead to the string representation of num
 *  @param num the integer number to convert
 */
#define PRIVATE_KCT_INITSTRING(string,num,conversion) \
	string=malloc(PRIVATE_KCT_STRINGBUFFER); \
	sprintf(string,conversion,num);

/**
 * \brief free an already allocated string
 *
 * \warning
 * 	It is highly recommended that you use as "string" parameter only a
 * 	simple variable. Complex formula might cause instabilities
 *
 *
 * \pre
 *  \li string was allocated with PRIVATE_KCT_INITSTRING;
 * \post
 *  \li string is freed from the memory;
 *
 * @param string the string to be deallocated;
 *
 */
#define PRIVATE_KCT_FREESTRING(string) \
	free(string);

/**\brief compose a new string by concatenating all the strings in the the given array
 *
 * \pre
 *  \li destination must be a char*;
 *  \li destination must not be already mallocated;
 *  \li destination has to be a simple variable (so not a return value of a function): for example the following call is allowed:
 *  	\code
 *  		char* a;
 *  		char** arraystring={"hello"," ","world!\n"};
 *  		PRIVATE_KCT_STRCAT(a,3,arraystring);
 *  	\endcode
 *  	A variable holding a return value of a function is of course allowed:
 *  	\code
 *  		char* a=magicfunction();
 *  		char** arraystring={"hello"," ","world!\n"};
 *  		PRIVATE_KCT_STRCAT(a,3,arraystring);
 *  	\endcode
 *  	while this call goes to error:
 *  	\code
 *  		char** arraystring={"hello"," ","world!\n"};
 *  		PRIVATE_KCT_STRCAT(magicfunction(),3,arraystring);
 *  	\endcode
 *  \li stringlength must represents the number of elements inside strings;
 *  \li strings must be char**;
 * \post
 *  \li destination is a char* pointing to a string computed by concatenating all the
 *  	strings together.
 *
 * @param destination the pointer linking the strings concatenated
 * @param stringslength the number of elements inside the stirngs parameter
 * @param strings the set of string to be concatenated
 */
#define PRIVATE_KCT_STRCAT(destination,stringslength,strings) { \
	/*represents the value of stringlength: stringlength might be a funciton call (maybe even random) so this step is important to preserve deterministic behaviour*/ \
	int private_kct_strcat_stringslength=(stringslength); \
	/*represents the total length of the string which will be mallocated in destination*/ \
	int private_kct_strcat_length=1; \
	/*represents a iteration variable used in a loop*/ \
	int private_kct_strcat_i; \
	for (private_kct_strcat_i=0; private_kct_strcat_i<private_kct_strcat_stringslength; private_kct_strcat_i++){ \
		private_kct_strcat_length+=strlen(strings[private_kct_strcat_i]); \
	} \
	destination=malloc(private_kct_strcat_length); \
	strcpy(destination,strings[0]); \
	for (private_kct_strcat_i=1; private_kct_strcat_i<private_kct_strcat_stringslength;private_kct_strcat_i++){ \
		strcat(destination,strings[private_kct_strcat_i]); \
	} \
}

/**
 * \brief constructs an empty test list
 *
 * It is highly recommended that you put in list a single variable, not a function
 * returning a TestList*
 *
 * \pre
 *  \li list *has* to be of type TestList*
 *  \li list has not been initialized with malloc
 * \post
 *  \li an empty testlist is allocated in the memory
 *  \li the head of the list is NULL;
 *  \li the tail of the list is NULL;
 *  \li the size of the list is 0;
 *
 *  @param [TestList*] construct a new TestList and store its pointer in this very parameter
 */
#define PRIVATE_KCT_INITTESTLIST(list) \
	list=malloc(sizeof(TestList)); \
	if (list==NULL){ \
		fprintf(stderr,"MaxTester.c:initTestList:1:Not enough memory\n"); \
		exit -1; \
	} \
	list->head=NULL; \
	list->tail=NULL; \
	list->size=0

/**
 * \brief Create a new TestListElement in the memory
 *
 * \pre
 *  \li element has to be of type TestListElement*;
 *  \li element has not already been initialized with malloc;
 *  \li element must be a simple variable (i.e. a,list);
 *  \li testdescription has to be a constant string, like "hello";
 * \post
 *  \li a new TestListElement is allocated in the heap;
 *  \li the field "result" of the newly created TestListElement is KCT_UNKNWON;
 *  \li the field "errorMessage" of the newly created TestListElement is NULL;
 *
 * @param [TestListElement*]element a uninitialized pointer of TestListElement that will be used to point the new structure
 * @param [TestFunction]_function the pointer name of the function that will be used as a test function
 * @param [char*]_description a string representing the description of the test;
 * @param [bool]toberun TRUE if you want to actually use this test during the test run, FALSE if you want to be added to the
 * 	list but you want to skip it
 *
 */
#define PRIVATE_KCT_INITTESTLISTELEMENT(element,_function,_description,toberun) \
	element=malloc(sizeof(TestListElement)); \
	if (element==NULL){ \
		fprintf(stderr,"KoldarCTester.h:PRIVATE_KCT_INITTESTLISTELEMENT:not enough memory"); \
		exit -1; \
	} \
	element->testFunction=_function; \
	PRIVATE_KCT_COPYSTRING(element->description,_description); \
	element->errorMessage=NULL; \
	element->result=PRIVATE_KCT_UNKNOWN; \
	element->skip=!toberun; \
	element->next=NULL

/**
 * \brief adds a new test function in the test list
 *
 * The variable list is best not to be a complex formula, but a simple variable:
 * in this way the macro function is way quicker
 *
 * \pre
 *  \li _test is already been declared
 *  \li _list of type TestList*
 *  \li _test is of type TestFunction
 *  \li _description is a char*
 *  \li _toberun is a bool
 * \post
 *  \li _test function is stored in the test list
 *  \li _errormessage field is set to NULL
 *
 * @param [TestList*]_list the test list where to add the test function
 * @param [TestFunction]_test the function to be added in the test list
 * @param [char*]_description a brief description of what the test verifies.
 * @param [bool]_toberun
 *  \li TRUE if you want to insert the testcase in the list and execute it;
 *  \li FALSE if you want to insert the testcase in the list but you want it to skip it;
 */
#define PRIVATE_KCT_ADDTESTCASE(_list,_test,_description,_toberun) { \
	TestListElement* newadd; \
	PRIVATE_KCT_INITTESTLISTELEMENT(newadd,_test,_description,_toberun); \
	if (_list->head==NULL){ \
		_list->head=newadd; \
		_list->tail=newadd; \
	}else { \
		_list->tail->next=newadd; \
		_list->tail=newadd; \
	} \
	_list->size++; \
}

/**
 * \brief free the memory occupied by the list.
 *
 * \pre
 *  \li _list not NULL;
 *  \li _list is of type TestList*;
 * \post
 *  \li the memory allocated to every TestListElement pointed by the list is freed.
 *
 * @param [TestList*]list the list to be freed
 */
#define PRIVATE_KCT_FREETESTLIST(_list) { \
	TestListElement* tofree=_list->head; \
	TestListElement* next; \
	while (tofree!=NULL){ \
		next=tofree->next; \
		free((char*)tofree->description); \
		free((char*)tofree->errorMessage); \
		free(tofree); \
		tofree=next; \
	} \
	free(_list); \
}

/**
 * @brief run all the test in the list
 *
 * \pre
 *  \li _f open in write mode;
 *  \li _list not NULL;
 *  \li _f is of type FILE*;
 *  \li _list is of type TestList*;
 *  \li _postDelete is of type bool;
 * \post
 *  \li all the tests which have "skip" flag set to FALSE are run
 *
 * @param [FILE*]_f the file to write the output on
 * @param [TestList*]_list the list holding the various test functions
 * @param [bool]_postDelete
 *  \li TRUE if you want to automatically call clearTestCase() function	at the end of the test functions;
 *  \li FALSE otherwise;
 */
#define PRIVATE_KCT_RUNALLTEST(_f,_list,_postDelete) { \
	TestListElement* testToRun=_list->head; \
	int testnumber; \
	int oktest; \
	int skiptest; \
	int failtest; \
	while (testToRun!=NULL){ \
		if (testToRun->skip==true){ \
			testToRun->result=PRIVATE_KCT_SKIPPED; \
			testToRun=testToRun->next; \
			continue; \
		} \
		currentTest=testToRun; \
		fprintf(_f,"%s TEST \"%s\" %s\n",PRIVATE_KCT_TESTSEPARATOR,testToRun->description,PRIVATE_KCT_TESTSEPARATOR); \
		fprintf(_f,"\n"); \
		testToRun->testFunction(); \
		if (testToRun->result == PRIVATE_KCT_UNKNOWN){ \
			testToRun->result=PRIVATE_KCT_SUCCESS; \
		}else { \
			fprintf(_f,"!!!ERROR!!!\n%s",testToRun->errorMessage); \
		} \
		fprintf(_f,"\n"); \
		testToRun=testToRun->next; \
	} \
	fprintf(_f,"%s FINAL RESULTS %s\n",PRIVATE_KCT_TESTSEPARATOR,PRIVATE_KCT_TESTSEPARATOR); \
	fprintf(_f,"\n"); \
	testToRun=_list->head; \
	testnumber=1; \
	oktest=0; \
	failtest=0; \
	skiptest=0; \
	while (testToRun!=NULL){ \
		fprintf(_f,"%i) %s\t",testnumber,testToRun->description); \
		switch (testToRun->result){ \
		case PRIVATE_KCT_SUCCESS: { \
			fprintf(_f,"SUCCESS"); \
			oktest++; \
			break; \
		} \
		case PRIVATE_KCT_FAIL: { \
			fprintf(_f,"FAIL"); \
			failtest++; \
			break; \
		} \
		case PRIVATE_KCT_SKIPPED: { \
			skiptest++; \
			fprintf(_f,"SKIPPED"); \
			break; \
		} \
		case PRIVATE_KCT_UNKNOWN: { \
			fprintf(_f,"UNKNOWN"); \
			break; \
		} \
		} \
		fprintf(_f,"\n"); \
		testToRun=testToRun->next; \
		testnumber++; \
	} \
	fprintf(_f,"\n"); \
	fprintf(_f,"OK\t%d/%d %%run %2.3f\n",oktest,_list->size,(oktest*100.00)/(_list->size-skiptest)); \
	fprintf(_f,"FAIL\t%d/%d %%run %2.3f\n",failtest,_list->size,(failtest*100.00)/(_list->size-skiptest)); \
	fprintf(_f,"SKIPPED\t%d/%d\n",skiptest,_list->size); \
	if (_postDelete){ \
		PRIVATE_KCT_FREETESTLIST(_list); \
		_list=NULL; \
	} \
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PRIVATE VARIABLE USED @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/**
 * Represents the list holding every test.
 * This variable is used to simplify the MACRO prototype
 */
TestList* testList=NULL;
/*FIXME this variable prevents you to create multiple lists:
 * if you have 2 parallel executing lists, with this variable you can't obvously keep
 * trace on what test the 2 lists are executing!
 */
/**
 * Represents the test which is currently running
 *
 */
TestListElement* currentTest;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@ PUBLIC MACRO DEFINITIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

/**
 * \brief adds a new function in the test list
 *
 * \pre
 *  \li function has already been defined;
 *  \li function must have no formal parameters;
 *  \li function must return a void type;
 * \post
 *  \li the function is inside the test list
 *
 * @param [TestFunction]function the function to include in the test list;
 * @param [bool]torun TRUE is you want to actually run the test, FALSE if you want to include it in the list
 * 	but you want to skip it
 *
 */
#define kct_addTestImproved(function,torun) \
	if (testList==NULL){ \
		PRIVATE_KCT_INITTESTLIST(testList); \
	} \
	PRIVATE_KCT_ADDTESTCASE(testList,function,#function,torun)

/**
 * \brief adds a new function in the test list
 *
 * \pre
 *  \li function has already been defined;
 *  \li function must have no formal parameters;
 *  \li function must return a void type;
 * \post
 *  \li the function is inside the test list
 *
 * @param [TestFunction]function the function to include in the test list;
 */
#define kct_addTest(function) \
	kct_addTestImproved(function,true)

/**
 * \brief run all the test added to the test list.
 *
 * The function run all the tests which has been added to the test list.
 * You can add test function in the test list with the function kct_addTest().
 * Not all the tests will be run, but onyly those tests which are appended with the flag "torun"
 * set to "TRUE"
 *
 * \pre
 *  \li outputfile open in write mode
 * \post
 *  \li test outcome is appended to the outputfile
 *
 * @param [FILE*]outputfile where to write the test outcome
 */
#define kct_runAllTests(outputfile) \
	PRIVATE_KCT_RUNALLTEST(outputfile,testList,true)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ASSERTION MACROS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


/**
 * \brief Terminate the test and set the result of it as a failure.
 *
 */
#define kct_fail() \
	currentTest->result=PRIVATE_KCT_FAIL; \
	return;

/**
 * \brief Terminate the test and set the result of it as a failure.
 *
 * @param [char*]message represents the message to
 * 	display just before the ending of the test.
 *
 */
#define kct_failMsg(message) \
	PRIVATE_KCT_COPYSTRING(currentTest->errorMessage,message); \
	kct_fail();

/**
 * \brief terminates successfully the current test
 *
 */
#define kct_ok() \
	return;

/**
 * \brief end the test as a failure if the condition is <b>not</b> met
 *
 *  @param condition represents the condition to be tested
 */
#define kct_assertCondition(condition) \
	if ((condition)==false){ \
		kct_fail(); \
	}

/**
 * \brief end the test as a failure if the condition IS <b>not</b> met
 *
 * In addition to end the test if condition is <b>not</b> met, this
 * function will display an error message.
 *
 * @param [char*]message represents the error message to be display if the condition
 * 	is not met
 * @param condition represents the condition to be test
 */
#define kct_assertConditionMsg(message,condition) \
	if ((condition)==false){ \
		kct_failMsg(message); \
	}

/**
 * \brief end the test as a failure if the condition is met
 *
 *  @param condition represents the condition to be tested
 */
#define kct_assertNotCondition(condition) \
	if ((condition)==true){ \
		kct_fail(); \
	}

/**
 * \brief end the test as a failure if the condition is met
 *
 * In addition to end the test if condition is met, this
 * function will display an error message.
 *
 * @param [char*]message represents the error message to be display if the condition
 * 	is not met
 * @param condition represents the condition to be test
 */
#define kct_assertNotConditionMsg(message,condition) \
	if ((condtion)==true){ \
		kct_failMsg(message); \
	}


/**\brief tests if 2 strings are equal
 *
 * The macro tests wether or not 2 strings are equal: if they are, nothing will happen; otherwise
 * an error will be generated.
 *
 * \pre
 *  \li optmessage is not NULL;
 *  \li optmessage is of type char*;
 *  \li expected is not NULL;
 *  \li expected is of type char*;
 *  \li actual is not NULL;
 *  \li actual is of type char*;
 *
 *  @param optmessage an optional message written by the developer holding useful information about this error
 *  @param expected the string that should be returned from the funciton under test;
 *  @param actual the string that is actually returned by the function under test;
 */
#define kct_assertEqualStrMsg(optmessage,expected,actual){ \
	/*represents the value of optmessage: optmessage might be a funciton call (maybe even random) so this step is important to preserve deterministic behaviour*/ \
	char* private_kct_assertEqualStr_optmessage=(optmessage); \
	/*represents the value of expected: expected might be a funciton call (maybe even random) so this step is important to preserve deterministic behaviour*/ \
	char* private_kct_assertEqualStr_expected=(expected); \
	/*represents the value of actual: actual might be a funciton call (maybe even random) so this step is important to preserve deterministic behaviour*/ \
	char* private_kct_assertEqualStr_actual=(actual); \
	if (strcmp(private_kct_assertEqualStr_expected,private_kct_assertEqualStr_actual)!=0){ \
		char* private_kct_assertEqualStr_array[]={ \
			private_kct_assertEqualStr_optmessage, \
			PRIVATE_KCT_ERRORMESSAGE_EXPECTED, \
			"\"", \
			private_kct_assertEqualStr_expected, \
			"\"", \
			PRIVATE_KCT_ERRORMESSAGE_ACTUAL, \
			"\"", \
			private_kct_assertEqualStr_actual, \
			"\"" \
		}; \
		PRIVATE_KCT_STRCAT( \
			currentTest->errorMessage, \
			9, \
			private_kct_assertEqualStr_array \
		); \
		kct_fail(); \
	} \
}

/**\brief tests if 2 strings are equal
 *
 * The macro tests wether or not 2 strings are equal: if they are, nothing will happen; otherwise
 * an error will be generated.
 *
 * \pre
 *  \li expected is not NULL;
 *  \li expected is of type char*;
 *  \li actual is not NULL;
 *  \li actual is of type char*;
 *
 *  @param expected the string that should be returned from the funciton under test;
 *  @param actual the string that is actually returned by the function under test;
 */
#define kct_assertEqualStr(expected,actual){ \
		kct_assertEqualStrMsg("",expected,actual) \
}


/**
 * \brief Checks if 2 simple values are equal. If not, send an error
 *
 * The function checks if 2 data are equal. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * The function can manage only simple data:
 *  \li int;
 *  \li short;
 *  \li long;
 *  \li float;
 *  \li double;
 *  \li unsigned variations;
 *  \li pointer variations (check the very pointers, not the structure pointed by them);
 *  \li enumerations;
 *
 * \warning While string and structure can be inserted as values to be checked,
 * the function can't compare them with ease. If you have to compare strings or structures,
 * please use kct_assertEqualStrMsg() or PRIVATE_KCT_ASSERTSTRUCTEQUAL
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li type is a simple type;
 *  \li conversion is a formatter string, like "%d";
 *  \li expected is a value of type type;
 *  \li actual is a value of type type;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param type represents the type of expected and actual values;
 * @param conversion represents the formatter string used to format the stirng representations of expected and actual;
 * @param expected the value that the developer expects to get;
 * @param actual the very value received
 */
#define kct_assertEqualPrimitiveMsg(message,type,conversion,expected,actual) { \
	type private_kct_variable_kct_assertEqualPrimitiveMsg_intexpected=(expected); \
	type private_kct_variable_kct_assertEqualPrimitiveMsg_intactual=(actual); \
	if ((private_kct_variable_kct_assertEqualPrimitiveMsg_intactual)!=(private_kct_variable_kct_assertEqualPrimitiveMsg_intexpected)){ \
		/*Represents a string representation of the given primitive type*/ \
		char* private_kct_variable_kct_assertEqualPrimitiveMsg_str_exp; \
		/*Represents a string representation of the given primitive type*/ \
		char* private_kct_variable_kct_assertEqualPrimitiveMsg_str_act; \
		PRIVATE_KCT_INITSTRING(private_kct_variable_kct_assertEqualPrimitiveMsg_str_exp,private_kct_variable_kct_assertEqualPrimitiveMsg_intexpected,conversion); \
		PRIVATE_KCT_INITSTRING(private_kct_variable_kct_assertEqualPrimitiveMsg_str_act,private_kct_variable_kct_assertEqualPrimitiveMsg_intactual,conversion); \
		/*Represents an arrya of string which, concatenated, will generated the error message*/ \
		char* private_kct_assertEqualPrmitiveMsg_array[]={ \
			message, \
			PRIVATE_KCT_ERRORMESSAGE_EXPECTED, \
			private_kct_variable_kct_assertEqualPrimitiveMsg_str_exp, \
			PRIVATE_KCT_ERRORMESSAGE_ACTUAL, \
			private_kct_variable_kct_assertEqualPrimitiveMsg_str_act \
		}; \
		PRIVATE_KCT_STRCAT( \
			currentTest->errorMessage, \
			5, \
			private_kct_assertEqualPrmitiveMsg_array \
		); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertEqualPrimitiveMsg_str_exp); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertEqualPrimitiveMsg_str_act); \
		kct_fail(); \
	} \
}

/**
 * \brief Checks if 2 simple values are not equal. If not, send an error
 *
 * The function checks if 2 data are different. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * The function can manage only simple data: they include:
 *  \li int;
 *  \li short;
 *  \li long;
 *  \li float;
 *  \li double;
 *  \li unsigned variations;
 *  \li pointer variations (check the very pointers, not the structure pointed by them);
 *  \li enumerations;
 *
 * \warning While string and structure can be inserted as values to be checked,
 * the function can't compare them with ease. If you have to compare strings or structures,
 * please use kct_assertEqualStrMsg() or PRIVATE_KCT_ASSERTSTRUCTEQUAL
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li type is a simple type;
 *  \li conversion is a formatter string, like "%d";
 *  \li expected is a value of type type;
 *  \li actual is a value of type type;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param type represents the type of expected and actual values;
 * @param conversion represents the formatter string used to format the string representations of expected and actual;
 * @param expected the value that the developer expects to get;
 * @param actual the very value received
 */
#define kct_assertNotEqualPrimitiveMsg(message,type,conversion,expected,actual) { \
	type private_kct_variable_kct_assertNotEqualPrimitiveMsg_intexpected=(expected); \
	type private_kct_variable_kct_assertNotEqualPrimitiveMsg_intactual=(actual); \
	if ((private_kct_variable_kct_assertNotEqualPrimitiveMsg_intactual)==(private_kct_variable_kct_assertNotEqualPrimitiveMsg_intexpected)){ \
		/*Represents a string representation of the given primitive type*/ \
		char* private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_exp; \
		/*Represents a string representation of the given primitive type*/ \
		char* private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_act; \
		PRIVATE_KCT_INITSTRING(private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_exp,private_kct_variable_kct_assertNotEqualPrimitiveMsg_intexpected,conversion); \
		PRIVATE_KCT_INITSTRING(private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_act,private_kct_variable_kct_assertNotEqualPrimitiveMsg_intactual,conversion); \
		/*Represents an arrya of string which, concatenated, will generated the error message*/ \
		char* private_kct_assertNotEqualPrimitiveMsg_array[]={ \
			message, \
			PRIVATE_KCT_ERRORMESSAGE_EXPECTED, \
			private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_exp, \
			PRIVATE_KCT_ERRORMESSAGE_ACTUAL, \
			private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_act \
		}; \
		PRIVATE_KCT_STRCAT( \
			currentTest->errorMessage, \
			5, \
			private_kct_assertNotEqualPrimitiveMsg_array \
		); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_exp); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertNotEqualPrimitiveMsg_str_act); \
		kct_fail(); \
	} \
}

/**
 * \brief Checks if 2 structured data are equal. If not, send an error
 *
 * The function checks if 2 structure data are equal. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * The function can easily manage structure data (typedef struct). To do so,
 * however, it needs 2 functions:
 *  \li a compare function: this function takes 2 structure value of the same type
 *  	and checks if they are equal; if they are, the function returns 0, otherwise it returns a
 *  	non zero value. Note that the function can be much complex than a equal/different function:
 *  	like strcmp(), it might returns a negative number if the first struct has a less value than the second and/or
 *  	a positive number if the first structure has a greater value than the second one. The important stuff is
 *  	that it returns 0 if the 2 given structs are equal.
 *  \li a string conversion functions: the function has to take only one parameter, the structure to stringify and
 *  	must return a char*. Moreover, <b>it must allocate a new string</b>: this is mandatory because
 *  	the function will automatically free the char pointer returned by the function.
 *
 * \warning {While primitive types can be inserted as values to be checked,
 * the function can't compare them with ease. If you have to compare strings or structures,
 * please use PRIVATE_KCT_ASSERTINTEQUAL or similar}
 *
 * An example of the use of this function:
 * \code
 *	typedef struct Point {
 *		int x;
 *		int y;
 *	} Point;
 *
 *	char* Point2String(Point p){
 *		char* buffer=malloc(100);
 *		sprintf(buffer,"(%d %d)",p.x,p.y);
 *		return buffer;
 *	}
 *
 *	int comparePoints(Point p1,Point p2){
 *		if (p1.x!=p2.x){
 *			return 1;
 *		}
 *		if (p1.y!=p2.y){
 *			return 1;
 *		}
 *		return 0;
 *	}
 *
 *	void testOK(){
 *		Point px;
 *		Point py;
 *		px.x=5;
 *		px.y=4;
 *		py.x=5;
 *		py.y=5;
 *		kct_assertEqualStructMsg(
 *			"the 2 points are different!",
 *			Point,
 *			Point2String,
 *			comparePoints,
 *			px,
 *			py);
 *	}
 *
 *	int main(){
 *		kct_addTest(testOK);
 *		kct_runAllTest(stdout);
 *		return 0;
 *	}
 * \endcode
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li type is a struct type;
 *  \li toStringFunction is a name of a declared function;
 *  \li toStringFunction takes only one parameter of type "type";
 *  \li toStringFunction return a char*;
 *  \li toStringFunction allocates a new string in the heap representing the struct given;
 *  \li compareFunction is a name of a declared function;
 *  \li compareFunction takes only 2 paramters of type "type";
 *  \li compareFunction returns 0 or another value;
 *  \li compareFunction must return 0 if the 2 values are equal;
 *  \li compareFunction must return any other value beside 0 if the 2 values are different;
 *  \li expected is a value of type type;
 *  \li actual is a value of type type;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param type represents the type of expected and actual values and the type
 * 	of the parameters of the functions toStringFunction and compareFunction;
 * @param toStringFunction represents the name
 * @param expected the value that the developer expects to get;
 * @param actual the very value received
 */
#define kct_assertEqualStructMsg(message,type,toStringFunction,compareFunction,expected,actual) { \
	type private_kct_variable_kct_assertEqualStructMsg_structexpected=expected; \
	type private_kct_variable_kct_assertEqualStructMsg_structactual=actual; \
	if (compareFunction(private_kct_variable_kct_assertEqualStructMsg_structexpected,private_kct_variable_kct_assertEqualStructMsg_structactual)!=0){ \
		char* private_kct_variable_kct_assertEqualStructMsg_str_exp=toStringFunction(private_kct_variable_kct_assertEqualStructMsg_structexpected); \
		char* private_kct_variable_kct_assertEqualStructMsg_str_act=toStringFunction(private_kct_variable_kct_assertEqualStructMsg_structactual); \
		char* private_kct_assertEqualStructMsg_array[]={ \
			message, \
			PRIVATE_KCT_ERRORMESSAGE_EXPECTED, \
			"\"", \
			private_kct_variable_kct_assertEqualStructMsg_str_exp, \
			"\"", \
			PRIVATE_KCT_ERRORMESSAGE_ACTUAL, \
			"\"", \
			private_kct_variable_kct_assertEqualStructMsg_str_act, \
			"\"" \
		}; \
		PRIVATE_KCT_STRCAT( \
			currentTest->errorMessage, \
			9, \
			private_kct_assertEqualStructMsg_array \
		); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertEqualStructMsg_str_exp); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertEqualStructMsg_str_act); \
		kct_fail(); \
	} \
}

/**
 * \brief Checks if 2 structured data are different. If not, send an error
 *
 * The function checks if 2 structure data are not equal. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * The function can easily manage structure data (typedef struct). To do so,
 * however, it needs 2 functions:
 *  \li a compare function: this function takes 2 structure value of the same type
 *  	and checks if they are equal; if they are, the function returns 0, otherwise it returns a
 *  	non zero value. Note that the function can be much complex than a equal/different function:
 *  	like strcmp(), it might returns a negative number if the first struct has a less value than the second and/or
 *  	a positive number if the first structure has a greater value than the second one. The important stuff is
 *  	that it returns 0 if the 2 given structs are equal.
 *  \li a string conversion functions: the function has to take only one parameter, the structure to stringify and
 *  	must return a char*. Moreover, <b>it must allocate a new string</b>: this is mandatory because
 *  	the function will automatically free the char pointer returned by the function.
 *
 * \warning {While primitive types can be inserted as values to be checked,
 * the function can't compare them with ease. If you have to compare strings or structures,
 * please use PRIVATE_KCT_ASSERTINTEQUAL or similar}
 *
 * An example of the use of this function:
 * \code
 *	typedef struct Point {
 *		int x;
 *		int y;
 *	} Point;
 *
 *	char* Point2String(Point p){
 *		char* buffer=malloc(100);
 *		sprintf(buffer,"(%d %d)",p.x,p.y);
 *		return buffer;
 *	}
 *
 *	int comparePoints(Point p1,Point p2){
 *		if (p1.x!=p2.x){
 *			return 1;
 *		}
 *		if (p1.y!=p2.y){
 *			return 1;
 *		}
 *		return 0;
 *	}
 *
 *	void testOK(){
 *		Point px;
 *		Point py;
 *		px.x=5;
 *		px.y=4;
 *		py.x=5;
 *		py.y=5;
 *		kct_assertNotEqualStructMsg(
 *			"the 2 points are different!",
 *			Point,
 *			Point2String,
 *			comparePoints,
 *			px,
 *			py);
 *	}
 *
 *	int main(){
 *		kct_addTest(testOK);
 *		kct_runAllTest(stdout);
 *		return 0;
 *	}
 * \endcode
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li type is a struct type;
 *  \li toStringFunction is a name of a declared function;
 *  \li toStringFunction takes only one parameter of type "type";
 *  \li toStringFunction return a char*;
 *  \li toStringFunction allocates a new string in the heap representing the struct given;
 *  \li compareFunction is a name of a declared function;
 *  \li compareFunction takes only 2 paramters of type "type";
 *  \li compareFunction returns 0 or another value;
 *  \li compareFunction must return 0 if the 2 values are equal;
 *  \li compareFunction must return any other value beside 0 if the 2 values are different;
 *  \li expected is a value of type type;
 *  \li actual is a value of type type;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param type represents the type of expected and actual values and the type
 * 	of the parameters of the functions toStringFunction and compareFunction;
 * @param toStringFunction represents the name
 * @param expected the value that the developer expects to get;
 * @param actual the very value received
 */
#define kct_assertNotEqualStructMsg(message,type,toStringFunction,compareFunction,expected,actual) { \
	type private_kct_variable_kct_assertNotEqualStructMsg_structexpected=(expected); \
	type private_kct_variable_kct_assertNotEqualStructMsg_structactual=(actual); \
	if (compareFunction(private_kct_variable_kct_aassertNotEqualStructMsg_structexpected,private_kct_variable_kct_assertNotEqualStructMsg_structactual)==0){ \
		char* private_kct_variable_kct_assertNotEqualStructMsg_str_exp=toStringFunction(private_kct_variable_kct_assertNotEqualStructMsg_structexpected); \
		char* private_kct_variable_assertNotEqualStructMsg_str_act=toStringFunction(private_kct_variable_kct_assertNotEqualStructMsg_structactual); \
		char* private_kct_assertNotEqualStructMsg_array[]={ \
			message, \
			PRIVATE_KCT_ERRORMESSAGE_EXPECTED, \
			"\"", \
			private_kct_variable_kct_assertNotEqualStructMsg_str_exp, \
			"\"", \
			PRIVATE_KCT_ERRORMESSAGE_ACTUAL, \
			"\"", \
			private_kct_variable_kct_assertNotEqualStructMsg_str_act, \
			"\"" \
		}; \
		PRIVATE_KCT_STRCAT( \
			currentTest->errorMessage, \
			9, \
			private_kct_assertNotEqualStructMsg_array \
		); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertNotEqualStructMsg_str_exp); \
		PRIVATE_KCT_FREESTRING(private_kct_variable_kct_assertNotEqualStructMsg_str_act); \
		kct_fail(); \
	} \
}

/**\brief Checks if 2 pointers values are equal. If not, send an error
 *
 *
 * The function checks if 2 pointers are equal. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li expected is a value of type void* (or a relative of it);
 *  \li actual is a value of type void* (or a relative of it);
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param [void*]expected the value that the developer expects to get;
 * @param [void*]actual the very value received
 */
#define kct_assertEqualPtrMsg(message,expected,actual) \
	kct_assertEqualPrimitiveMsg(message,void*,"%p",expected,actual)

/**\brief Checks if 2 pointer values are not equal. If not, send an error
 *
 *
 * The function checks if 2 pointers are different. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li expected is a value of type void* (or a relative of it);
 *  \li actual is a value of type void* (or a relative of it);
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param [void*]expected the value that the developer expects to get;
 * @param [void*]actual the very value received
 */
#define kct_assertNotEqualPtrMsg(message,expected,actual) \
	kct_assertNotEqualPrimitiveMsg(message,void*,"%p",expected,actual)

/**\brief Checks if 2 integer values are equal. If not, send an error
 *
 *
 * The function checks if 2 integer are equal. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li expected is a value of type int;
 *  \li actual is a value of type int;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param [int]expected the value that the developer expects to get;
 * @param [int]actual the very value received
 */
#define kct_assertEqualIntMsg(message,expected,actual) \
	kct_assertEqualPrimitiveMsg(message,int,"%d",expected,actual)

/**\brief Checks if 2 integer values are not equal. If not, send an error
 *
 *
 * The function checks if 2 integer are different. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li expected is a value of type int;
 *  \li actual is a value of type int;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param [int]expected the value that the developer expects to get;
 * @param [int]actual the very value received
 */
#define kct_assertNotEqualIntMsg(message,expected,actual) \
	kct_assertNotEqualPrimitiveMsg(message,int,"%d",expected,actual)

/**\brief Checks if 2 float values are not equal. If not, send an error
 *
 *
 * The function checks if 2 integer are equal. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li expected is a value of type float;
 *  \li actual is a value of type float;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param [float]expected the value that the developer expects to get;
 * @param [float]actual the very value received
 */
#define kct_assertEqualFloatMsg(message,expected,actual) \
	kct_assertEqualPrimitiveMsg(message,float,"%2.3f",expected,actual)

/**\brief Checks if 2 float values are not equal. If not, send an error
 *
 *
 * The function checks if 2 float are different. If they are, nothing will happen.
 * If not, the 2 values are converted in string and a error message is thrown
 * at the user. The error is so composed:
 *  -# message parameter;
 *  -# KCT_ERRORMESSAGE_EXPECTED;
 *  -# expected parameter converted into string;
 *  -# KCT_ERRORMESSAGE_ACTUAL;
 *  -# actual parameter converted into string;
 *
 * \pre
 *  \li message is of type char* (or a string);
 *  \li expected is a value of type float;
 *  \li actual is a value of type float;
 *
 * @param [char*]message represents a custom message to prepend to the error message;
 * @param [float]expected the value that the developer expects to get;
 * @param [float]actual the very value received
 */
#define kct_assertNotEqualFloatMsg(message,expected,actual) \
	kct_assertNotEqualPrimitiveMsg(message,float,"%2.3f",expected,actual)

/**\brief test whether or not a pointer is NULL
 *
 *
 * The assertion checks if the pointer passed as parameter is NULL or not.
 * Nothing will happen if pointer is a value different from 0.
 *
 * \pre
 *  \li pointer is void* typed (or a relative of it);
 *
 * @param [void*]pointer the pointer to test
 */
#define kct_assertIsNotNull(pointer) { \
	void* private_kct_variable_kct_assertIsNotNull=(pointer); \
	if (private_kct_variable_kct_assertIsNotNull==NULL){ \
		kct_fail(); \
	} \
}

/**\brief test whether or not a pointer is NULL
 *
 *
 * The assertion checks if the pointer passed as parameter is NULL or not.
 * Nothing will happen if pointer is a value different from 0.
 * The string message will be shown if the pointer is 0.
 *
 * \pre
 *  \li pointer is void* typed (or a relative of it);
 *
 * @param [void*]pointer the pointer to test
 */
#define kct_assertIsNotNullMsg(message,pointer) { \
	void* private_kct_variable_kct_assertIsNotNullMsg=(pointer); \
	if (private_kct_variable_kct_assertIsNotNullMsg==NULL){ \
		kct_failMsg(message); \
	} \
}

/**\brief test whether or not a pointer is not NULL
 *
 *
 * The assertion checks if the pointer passed as parameter is not NULL.
 * Nothing will happen if pointer is a value equal from 0.
 *
 * \pre
 *  \li pointer is void* typed (or a relative of it);
 *
 * @param [void*]pointer the pointer to test
 */
#define kct_assertIsNull(pointer) { \
	void* private_kct_variable_kct_assertIsNull=(pointer); \
	if (private_kct_variable_kct_assertIsNull!=NULL){ \
		kct_fail(); \
	}

/**\brief test whether or not a pointer is not NULL
 *
 *
 * The assertion checks if the pointer passed as parameter is not NULL.
 * Nothing will happen if pointer is a value equal from 0.
 * A message will be shown if the pointer is not NULL.
 *
 * \pre
 *  \li pointer is void* typed (or a relative of it);
 *  \li message must be char* typed;
 *
 * @param [void*]pointer the pointer to test
 * @param [char*]message the message to show if the pointer is not NULL
 */
#define kct_assertIsNullMsg(message,pointer) { \
	void* private_kct_variable_kct_assertIsNullMsg=(pointer); \
	if (private_kct_variable_kct_assertIsNullMsg!=NULL){ \
		kct_failMsg(message); \
	} \
}

 /**\brief checks if a value is in a given interval
  *
  * The assertion allows you to check if a value (integer of float it doesn't matter)
  * is inside a certain interval. The macro supports all the type of interval:
  *
  * -* both interval inf and sup are <b>not</b> included in the interval itself: for example
  * 	5 is not in the interval \f$]3;5[\f$
  * -* only the interval inf is included in the interval: for example
  * 	5 is in the interval \f$[5;7[\f$
  * -* only the interval sup is cinluded in the interval: for example
  * 	5 is in the interval \f$]3;5]\f$
  * -* both interval inf and sup are included in the interval: for example
  * 	5 is in the interval \f$[3;5]\f$
  *
  * \pre
  *  \li lowerbound is an numeric type (integer, float, signed, unsigned);
  *  \li upperbound is an numeric type (integer, float, signed, unsigned);
  *  \li actualbound is an numeric type(integer, float, signed, unsigned);
  *  \li lowin is a bool;
  *  \li upin is a bool;
  *  \li optmessage is a char*;
  *  \li conversion is a fprintf compatible format expression (like %d, %lu or %2.6f);
  *
  *	The function easily accepts even randomic funcitions: the macro will behave
  *	correctly even if you code:
  *	\code
  *		kct_assertExtremis("randomic numbers",3,5,true,true,rand()%6); //wrong way to do it
  *	\endcode
  *
  *	If you are worry about the behaviour, however, you can always do like this:
  *	\code
  *		int a=rand()%6;
  *		kct_assertExtremis("randomic numbers",int,"%d",3,5,true,true,a); //correct way to do it
  *	\endcode
  *
  * @param optmessage the optional message to show if actual is not in the interval useful to developr to carry additional information
  * @param type the most general type of the number used in the interval. For example if lowerbound and actual are "int" but upperbound
  * 	is a "double" the type should be set to "double". If you uncertain of what type you want to do "double" should be a appropriate choice.
  * @param lowerbound the inf of interval
  * @param upperbound the sup of the interval
  * @param lowin TRUE if the inf is included in the interval
  * @param upin TRUE if the sup is included in the interval
  * @param actual the value to check if is contained between lowerbound and upperbound
  */
#define kct_assertExtremisMsg(optmessage,type,conversion,lowerbound,upperbound,lowin,upin,actual) { \
	type private_kct_assertExtremisMsg_actual=(actual); \
	type private_kct_assertExtremisMsg_lowerbound=(lowerbound); \
	type private_kct_assertExtremisMsg_upperbound=(upperbound); \
	if ((private_kct_assertExtremisMsg_actual<private_kct_assertExtremisMsg_lowerbound) || \
		(private_kct_assertExtremisMsg_actual>private_kct_assertExtremisMsg_upperbound) || \
		((lowin==false) && (private_kct_assertExtremisMsg_actual==private_kct_assertExtremisMsg_lowerbound)) || \
		((upin==false) && (private_kct_assertExtremisMsg_actual==private_kct_assertExtremisMsg_upperbound)) \
	){ \
		char* private_kct_assertExtremisMsg_str_lowerbound; \
		char* private_kct_assertExtremisMsg_str_upperbound; \
		char* private_kct_assertExtremisMsg_str_actual; \
		PRIVATE_KCT_INITSTRING(private_kct_assertExtremisMsg_str_lowerbound,private_kct_assertExtremisMsg_lowerbound,conversion); \
		PRIVATE_KCT_INITSTRING(private_kct_assertExtremisMsg_str_upperbound,private_kct_assertExtremisMsg_upperbound,conversion); \
		PRIVATE_KCT_INITSTRING(private_kct_assertExtremisMsg_str_actual,private_kct_assertExtremisMsg_actual,conversion); \
		char* kct_private_assertExtremisMsg_array[]={ \
			optmessage, \
			PRIVATE_KCT_ERRORMESSAGE_EXPECTED, \
			(lowin==true?"[":"]"), \
			private_kct_assertExtremisMsg_str_lowerbound, \
			"; ", \
			private_kct_assertExtremisMsg_str_upperbound, \
			(upin==true?"]":"["), \
			PRIVATE_KCT_ERRORMESSAGE_ACTUAL, \
			"\"", \
			private_kct_assertExtremisMsg_str_actual, \
			"\"" \
		}; \
		PRIVATE_KCT_STRCAT(currentTest->errorMessage,11,kct_private_assertExtremisMsg_array); \
		PRIVATE_KCT_FREESTRING(private_kct_assertExtremisMsg_str_lowerbound); \
		PRIVATE_KCT_FREESTRING(private_kct_assertExtremisMsg_str_upperbound); \
		PRIVATE_KCT_FREESTRING(private_kct_assertExtremisMsg_str_actual); \
		kct_fail(); \
	} \
}

/**\brief checks if a value is in a given interval
  *
  * The assertion allows you to check if a value (integer of float it doesn't matter)
  * is inside a certain interval. The macro supports all the type of interval:
  *
  * -* both interval inf and sup are <b>not</b> included in the interval itself: for example
  * 	5 is not in the interval \f$]3;5[\f$
  * -* only the interval inf is included in the interval: for example
  * 	5 is in the interval \f$[5;7[\f$
  * -* only the interval sup is cinluded in the interval: for example
  * 	5 is in the interval \f$]3;5]\f$
  * -* both interval inf and sup are included in the interval: for example
  * 	5 is in the interval \f$[3;5]\f$
  *
  * \pre
  *  \li lowerbound is an numeric type (integer, float, signed, unsigned);
  *  \li upperbound is an numeric type (integer, float, signed, unsigned);
  *  \li actualbound is an numeric type(integer, float, signed, unsigned);
  *  \li lowin is a bool;
  *  \li upin is a bool;
  *  \li conversion is a fprintf compatible format expression (like %d, %lu or %2.6f);
  *
  *	The function easily accepts even randomic funcitions: the macro will behave
  *	correctly even if you code:
  *	\code
  *		kct_assertExtremis(int,"%d",3,5,true,true,rand()%6); //wrong way to do it
  *	\endcode
  *
  *	If you are worry about the behaviour, however, you can always do like this:
  *	\code
  *		int a=rand()%6;
  *		kct_assertExtremis(int,"%d",3,5,true,true,a); //correct way to do it
  *	\endcode
  *
  * @param type the most general type of the number used in the interval. For example if lowerbound and actual are "int" but upperbound
  * 	is a "double" the type should be set to "double". If you uncertain of what type you want to do "double" should be a appropriate choice.
  * @param lowerbound the inf of interval
  * @param upperbound the sup of the interval
  * @param lowin TRUE if the inf is included in the interval
  * @param upin TRUE if the sup is included in the interval
  * @param actual the value to check if is contained between lowerbound and upperbound
  */
#define kct_assertExtremis(type,conversion,lowerbound,upperbound,lowin,upin,actual) \
	kct_assertExtremisMsg("",type,conversion,lowerbound,upperbound,lowin,upin,actual);

#endif /* KOLDARCTESTER_H_ */
