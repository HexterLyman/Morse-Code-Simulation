#include "include/functions.h"


/**
* TODO: add failsafes to accomodate for invalid command-line input (1) [DONE]
* ex: what if its not 0 or 1

* TODO: create system for error_encoded.txt [DONE]

* TODO: remove unnecessary comments [DONE]

* TODO: think of tests to do [DONE]

*/

int main(int argc, char *argv[])
{

srand(time(NULL));
Program program = {0, 0, 0, false, 0, false, false};


if(argc > ARGUMENT_SIZE){
  printf("Too many arguments!\n");
  return 1;
}
else if(argc < ARGUMENT_SIZE){
  printf("Too few arguments!\n");
  return 1;
}

program.encode_decode = atoi(argv[1]);
program.error_type = atoi(argv[2]);

printf("ENCODE_DECODE: %d\n", program.encode_decode);
printf("ERROR_TYPE: %d\n", program.error_type);

char morse_code_single[MAX_OUTPUT_LEN] = "\0";
bool space_before = true;

//TODO: add failsafes to here in case invalid command-line input (1) [DONE]

if((program.encode_decode != ENCODE) && (program.encode_decode != DECODE)){
  printf("Invalid Encode_Decode Input!\n");
  return 1;
}

if((program.error_type != SINGLE) && (program.error_type != BURST)){
  printf("Invalid Error_Type Input!\n");
  return 1;
}

// 1. get plaintext

char text_placeholder[MAX_STRING_LEN];

FILE * fptr; 
fptr = fopen("input.txt", "r");

if(fptr == NULL){
  printf("Cannot open file!\n");
  return 1;
}

if (fgets(text_placeholder, MAX_STRING_LEN, fptr) == NULL) {
  printf("Empty input.txt!\n");
  return 1;
}

int text_length = strlen(text_placeholder);


if(program.encode_decode == ENCODE){
  program.is_encode = true;
}

if(program.is_encode){

  // 2. convert to morse
/*
  a. parse through each char in text_placeholder
  b. each char compare with lookup table 
  c. copy the result from lookup table into new morse_code var
  d. get the length of the morse code single
*/

for(int i = 0; i < text_length; i++){

  if((!plaintext_validity(text_placeholder[i])) && (text_placeholder[i] != ' ')){
    continue;
  }

  if(space_before || text_placeholder[i] == ' '){
    space_before = false;
  }
  else{
    strcat(morse_code_single, "/");
  }

  if(text_placeholder[i] == ' '){
    space_before = true;
    strcat(morse_code_single, "|");
  }

  if(text_placeholder[i] != ' '){
    strcat(morse_code_single, encode_char(text_placeholder[i]));
    program.actual_morse_length += strlen(encode_char(text_placeholder[i]));
  }
  
}
  
}
else{
  //decode goes directly here!

  for(int i = 0; i < text_length; i++){

  if(text_placeholder[i] == '|' || text_placeholder[i] == '/'){
    continue;
  }
  else{
    program.actual_morse_length++;
  }

  }

  strcat(morse_code_single, text_placeholder);

}

//to check if morse length less than 3 (used to compensate for burst errors)
if((program.actual_morse_length) < MINIMUM_MORSE_LENGTH && (program.actual_morse_length != MORSE_SIZE_ONE)){
  program.morse_short = true;
  strcat(morse_code_single, morse_code_single);
}
else if((program.actual_morse_length) < MINIMUM_MORSE_LENGTH && (program.actual_morse_length == MORSE_SIZE_ONE)){
  program.morse_short = true;
  char temp[MINIMUM_MORSE_LENGTH];
  strcat(temp, morse_code_single);
  strcat(morse_code_single, morse_code_single);
  strcat(morse_code_single, temp);
  program.morse_one = true;
}

int single_morse_length = strlen(morse_code_single);

// 3. repeat 3 times

int triple_morse_length = 3 * single_morse_length;

char * morse_code_triple = malloc(triple_morse_length * sizeof(char));

strcpy(morse_code_triple, "");

for(int i  = 0; i  < REPEAT_SIZE; i++){
  strcat(morse_code_triple, morse_code_single);
}

// 4. create the encoded.txt

FILE * encoded_text;
encoded_text = fopen("encoded.txt", "w");

if(encoded_text == NULL){
  printf("Cannot open file [encoded.txt]!\n");
  free(morse_code_triple);
  fclose(fptr);
  return 1;
}

fprintf(encoded_text, morse_code_triple);

// 5. introduce errors to encoded.txt

if(program.error_type == SINGLE){
  single_error(morse_code_triple);
}
else{
  burst_error(morse_code_triple);
}


// 6. create the error_encoded.txt

FILE * error_encoded_text;
error_encoded_text = fopen("errorized.txt", "w");

if(error_encoded_text == NULL){
  printf("Cannot open file [encoded.txt]!\n");
  free(morse_code_triple);
  fclose(fptr);
  fclose(encoded_text);
  return 1;
}

fprintf(error_encoded_text, morse_code_triple);


/*
  
  RECEIVER'S SIDE!

*/

// 7. do EDAC 

edac(morse_code_triple, &program.real_size);

// 8. create the output.txt
/*
  1. copy from morse_code_triple to morse_code_final up to accepted length
  2. put into output.txt
*/

if(program.morse_short && !program.morse_one){
  program.real_size /= (MINIMUM_MORSE_LENGTH - 1);
}
else if(program.morse_short && program.morse_one){
  program.real_size /= (MINIMUM_MORSE_LENGTH);
}

char * morse_code_final = malloc(program.real_size * sizeof(char));

strncpy(morse_code_final, morse_code_triple, program.real_size);

morse_code_final[program.real_size] = '\0';

FILE * output;
output = fopen("output.txt", "w");

if(output == NULL){
  printf("Cannot open file [output.txt]!\n");
  free(morse_code_final);
  free(morse_code_triple);
  fclose(fptr);
  fclose(encoded_text);
  return 1;
}

if(program.encode_decode == DECODE){
  //9. decoder
/*
  1. take the morse_code_final and put into decoder
    a. parse through each string in 
    b. each char compare with lookup table 
    c. copy the result from lookup table into new morse_code var
    d . get the length of the morse code single

*/
  char decode_output[MAX_OUTPUT_LEN] = "\0";
  decoder(morse_code_final, decode_output);
  fprintf(output, decode_output);
}
else{
  fprintf(output, morse_code_final);
}



//free and fclose
free(morse_code_triple);
free(morse_code_final);
fclose(fptr);
fclose(encoded_text);
fclose(output);


return 0;
}