#include "functions.h"
#define LIB_SIZE 36 //size of the library

/*
morse: individual morse-codes stored string format

morse_indexer: individual characters used to compare in plaintext input

plaintext: individual characters stored in string format, used in the decoding process
*/

extern const char * morse[LIB_SIZE];
extern const char morse_indexer[LIB_SIZE];
extern const char * plaintext[LIB_SIZE];