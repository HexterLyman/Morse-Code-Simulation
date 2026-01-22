#ifndef FUNCTIONS_H 
#define FUNCTIONS_H //to stop the compiler from yapping

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STRING_LEN 100 //max size of input string length (for plaintext)
#define MAX_OUTPUT_LEN 200 //max size of output string
#define REPEAT_SIZE 3 //repeat size for the TMP
#define MINIMUM_MORSE_LENGTH 3 //minimum size for the morse-code-single
#define MORSE_SIZE_ONE 1 //in-case size of morse is 1
#define ARGUMENT_SIZE 3 //argument size needed in command-line

typedef struct{
int real_size;
int encode_decode;
int error_type;
bool is_encode;
int actual_morse_length;
bool morse_short;
bool morse_one;
} Program;

typedef enum {
SINGLE, 
BURST
} Error_Choice; 

typedef enum {
ENCODE,
DECODE
} Encode_Decode;

/**
 * plaintext_validity(...): checks is the plaintext character valid
 * @param text_placeholder: a character indexed from the plaintext string
*/
bool plaintext_validity(char text_placeholder);


/**
 * encode_char(...): converts plaintext characters into morsecode
 * @param text_char: a character indexed from the plaintext string
*/
const char * encode_char(const char text_char);

/**
 * error_flipper(...): flips a dot into a dash and vice-versa, used for single_error
 * @param morse_code_triple: the tripled morse-code to errorize
 * @param index: the index which will be errorized
*/
void error_flipper(char * morse_code_triple, int index);

/**
 * single_error(...): introduces an error on a single random character
 * @param morse_code_triple: the tripled morse-code to errorize
*/
void single_error(char * morse_code_triple);

/**
 * burst_error(...): introduces an error on a continuous group of 3 characters
 * @param morse_code_triple: the tripled morse-code to errorize
*/
void burst_error(char * morse_code_triple);

/**
 * edac(...): uses TMP to detect the errors in the morse_code_triple and correct them 
 * @param morse_code_triple: the tripled morse-code that is errorized
 * @param real_size: the actual length of the morse-code before tripled
*/
void edac(char * morse_code_triple, int * real_size);

/**
 * decode_string(...): converts one morse-code word into plaintext character, used in decoder(...)
 * @param morse_string: one morse-code word 
 * @param decode_output: empty string to concatenate plaintext output towards 
*/
void decode_string(char * morse_string, char * decode_output);

/**
 * decoder(...): converts overall  morse-code into plaintext
 * @param morse_code_final: a string of morse code
 * @param decode_output: empty string to concatenate plaintext output towards
*/
void decoder(char * morse_code_final, char * decode_output);

#endif