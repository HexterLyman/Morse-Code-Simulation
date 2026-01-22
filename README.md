# MORSE-CODE SIMULATION

This is a program to simulate a simplified transmission and receiving of morse-code.

---
## Table of Contents
- [How To Use](#how-to-use)
- [Repository Structure](#repository-structure)
- [Guide to Program Structure](#guide-to-program-structure)
- [Function Explanations](#function-explanations)
    - [Functions](#functions)
    - [Morse Library](#morse-lib)
- [Disclaimers](#disclaimers)  
---

### How To Use
1. Put your input (plain-text or morse-code) to `input.txt` (Make the .txt file first!)
2. Compile the code with makefile
   ```
   make
   ```
3. Run the executable with the following format
   ```
   ./solution [encode/decode mode] [error type]
   ```
   with:
   
   `[encode/decode mode]`: mode encoding or decoding. 0 for encoding, 1 for decoding.

   `[error type]` : type of simulated error. 0 for single error. 1 for burst error.
4. See output.txt for result.

---

## Repository Structure

```
sheet9c
│
├── include
│   ├── functions.h
│   └── morse_lib.h
│
├── tests
│   ├── test_1
│   │     ├── case_1
│   │     ├── ...
│   │     └── test_1.sh
│   │
│   ├── ...
│   └── test_9
│
├── Makefile
├── main.c
├── functions.c
├── morse_lib.c
└── gitlab-ci.yml

```

## Guide to Program Structure

###  main.c :
the main file which initializes all variables and executes the overall program.

### functions.c :
function file containing all the necessary functions in regards to encoding, decoding, adding errors, EDAC, and other auxillary functions.

### morse_lib.c :
custom built-in library used to simulate the morse-code and its equivalents in plaintext characters.

### gitlab-ci.yml :
.yml file to build the pipeline for testing.

### functions.h :
header file containing all function prototypes and structs.

### morse_lib.h :
header file containing extern prototypes for the morse-code library.

### tests/...:
main folder containing all the necessary input.txt, output.txt and also its relevant bash files for testing.

---

## Function Explanations

### Functions 

1. bool plaintext_validity(char text_placeholder):
* plaintext_validity(...): checks is the plaintext character valid
* @param text_placeholder: a character indexed from the plaintext string

2. const char * encode_char(const char text_char):
* encode_char(...): converts plaintext characters into morsecode
* @param text_char: a character indexed from the plaintext string

3. void error_flipper(char * morse_code_triple, int index):
* error_flipper(...): flips a dot into a dash and vice-versa, used for single_error
* @param morse_code_triple: the tripled morse-code to errorize
* @param index: the index which will be errorized

4. void single_error(char * morse_code_triple):
* single_error(...): introduces an error on a single random character
* @param morse_code_triple: the tripled morse-code to errorize

5. burst_error(char * morse_code_triple):
* burst_error(...): introduces an error on a continuous group of 3 characters
* @param morse_code_triple: the tripled morse-code to errorize

6. void edac(char * morse_code_triple, int * real_size):
* edac(...): uses TMP to detect the errors in the morse_code_triple and correct them
* @param morse_code_triple: the tripled morse-code that is errorized
* @param real_size: the actual length of the morse-code before tripled

7. void decode_string(char * morse_string, char * decode_output):
* decode_string(...): converts one morse-code word into plaintext character, used in decoder(...)
* @param morse_string: one morse-code word 
* @param decode_output: empty string to concatenate plaintext output towards

8. void decoder(char * morse_code_final, char * decode_output):
* decoder(...): converts overall  morse-code into plaintext
* @param morse_code_final: a string of morse code
* @param decode_output: empty string to concatenate plaintext output towards


### Morse Library

1. const char * morse[LIB_SIZE]:
* individual morse-codes stored string format

2. const char morse_indexer[LIB_SIZE]:
* individual characters used to compare in plaintext input

3. const char * plaintext[LIB_SIZE]:
* individual characters stored in string format, used in the decoding process

---

### Disclaimers

1. **MAXIMUM_SIZE must be increased for longer inputs!**

2. **To get an "empty" input.txt, first delete the old one! Otherwise, previous one might still linger in memory!**

3. **When decoding, we assume only morse-code will be in the input.txt**
* it would not make sense to have plaintext sent through a transmission cable, hence the assumption

4. **We only use the international version of Morse-Code, thus no special characters (i.e. umlauts) are allowed!**
