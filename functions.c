#include "include/functions.h"
#include "include/morse_lib.h"

bool plaintext_validity(char text_placeholder){
  
bool is_found = false;

for(unsigned i = 0; i < (sizeof(morse_indexer)/sizeof(morse_indexer[0])); i++){
if(text_placeholder == morse_indexer[i]){
is_found = true;
break;
}
}

if(is_found){
  return true;
}
else{
  return false;
} 

}


const char * encode_char(char text_char){
int index = 0;
bool is_found = false;
for(unsigned i = 0; i < (sizeof(morse_indexer)/sizeof(morse_indexer[0])); i++){
if(text_char == morse_indexer[i]){
index = i;
is_found = true;
break;
}
}

if(is_found){
  return morse[index];
}
else{
  return " ";
} 
}

/*
  1. get the char with the index
  2. if it is "." -> "-"
*/

void error_flipper(char * morse_code_triple, int index){
if(morse_code_triple[index] == '.'){
  morse_code_triple[index] = '-';
}
else{
  morse_code_triple[index] = '.';
}
}


/*
  single error:
  1. generate random number to get the index position
  2. check if index is divider ("/" or "|") or " "
  3. if yes -> generate a new random number (use while loop)
  4. if no -> flip the char 
*/

void single_error(char * morse_code_triple){

int size = strlen(morse_code_triple);
bool is_index_valid = false;
int char_index; 

while(!is_index_valid){

char_index = rand() % size + 1; 

if((morse_code_triple[char_index] == '/') || (morse_code_triple[char_index] == '|') || (morse_code_triple[char_index] == '\0')){
continue;
}
else{
is_index_valid = true;
}

error_flipper(morse_code_triple, char_index);

}

}

/*
  burst error: 
  1. generate random number between 0 and length-1
  2. initialize switch = 0 (goal: switch 3 times)
  3. check if index is divider ("/" or "|") or " "
  4. if no then flip the char
  5. if yes, then go to next index
*/

void burst_error(char * morse_code_triple){

int size = strlen(morse_code_triple);
int switched_amount = 0;
int char_index = rand() % size;

while(switched_amount < 3){

if((morse_code_triple[(char_index % size)] == '/') || (morse_code_triple[(char_index % size)] == '|')){
  char_index++;
  continue;
}
else{
  error_flipper(morse_code_triple, (char_index % size));
  switched_amount++;
  char_index++;
}

}

}


/*
  edac:
  1. get the length of the morse-code triple and divide by 3 (actual length)
  2. perform for-loop 3 times
    a. parse index
    b. count amount of dots
    c. if dots > 1 then replace with "."
    d. else replace with "-" 
*/

void edac(char * morse_code_triple, int * real_size){

  int actual_length = strlen(morse_code_triple) / REPEAT_SIZE;
  *real_size = actual_length;
  int dots;
  int dash;

  for(int i = 0; i < actual_length; i++){

    dots = 0;
    dash = 0;

    if((morse_code_triple[i] == '/') || (morse_code_triple[i] == '|')){
      continue;
    }

    //Performs TMP here!
    for(int j = 0; j < REPEAT_SIZE; j++){
      if(morse_code_triple[actual_length * j + i] == '.'){
        dots++;
      }
      else{
        dash++;
      }
    }

    if(dots > dash){
      morse_code_triple[i] = '.';
    }
    else{
      morse_code_triple[i] = '-';
    }

  }

}

void decode_string(char * morse_string, char * decode_output){

  int index = 0;

  bool is_found = false;


  for(unsigned i = 0; i < (sizeof(morse)/sizeof(morse[0])); i++){
    
    if(!strcmp(morse_string, morse[i])){
    index = i;
    is_found = true;
    break;
    }
  }

  if(is_found){
  strcat(decode_output, plaintext[index]);
  }
  
}


/*
  decoder:
  1. get the morse_code_final as input
  2. separate and add
*/

void decoder(char *morse_code_final, char *decode_output){

  char * temp_morse = strtok(morse_code_final, "|");

  while(temp_morse != NULL){

  int original_length = strlen(temp_morse); //length maybe unstable!

  int idx = 0;

  //for-loop inside

  for (int i = 0; i <= original_length; i++) {

    //transversing the whole string, using i in the for loop
    char * ptr = temp_morse + i;

    //to trace the actual word, using idx outside for loop
    char * morse_letter = temp_morse + idx;

    //if "/" or "\0", then it is end of word

    if(ptr[0] == '/' || ptr[0] =='\0'){

      ptr[0] ='\0';

      //decode here!

      decode_string(morse_letter, decode_output);

      idx = i + 1; //current i -> '/'  i+1 --> start of next word

    }

  }
 
  temp_morse = strtok(NULL, "|");  

  if(temp_morse != NULL){
     strcat(decode_output, " ");
  }

  }

  
}

 





