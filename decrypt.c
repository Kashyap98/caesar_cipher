#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "decrypt.h"

char* generate_new_string_from_cipher(char* input_string, int count, int shift){

    // prepare string and counter for input phrase
    char* generated_string = malloc(1);
    free(generated_string);
    generated_string = create_pointer(1);
    int generated_count = 0;


    // go through every letter in the string
    for(int letter_pos=0; letter_pos < count; letter_pos++){
        char letter = input_string[letter_pos];

        // check if the letter is a space
        if(letter == ' '){
            generated_string = realloc(generated_string, generated_count+1);
            generated_string[generated_count] = ' ';
            generated_count++;

        } else {
            // calculate shift using algo provided by TA rather than my previous array based approach
            int new_letter = letter - shift;
            if(new_letter < (int)'A'){
                new_letter = new_letter + 26;
            }

            // add the new letter to suspect string
            generated_string = realloc(generated_string, generated_count+1);
            generated_string[generated_count] = (char)new_letter;
            generated_count++;

        }
    }

    return generated_string;

}

char* get_word_from_generated_string(char* generated_string, int starting_pos, int count){

    // prepare variables for processing the current word
    char* current_word = malloc(1);
    free(current_word);
    current_word = create_pointer(1);
    int current_word_pos = 0;
    int first_iteration = 1;

    for(int pos = starting_pos; pos < count; pos++){

         // add to the current word since we have not reached a space or the end of the line
        char letter = generated_string[pos];
        // printf("%c - %i\n", letter, (int)letter != 32);

        // add the letter to the current word since we have not reached an invalid char
        if(letter != ' ' && letter != '\n' && letter != '\0'){
            first_iteration = 0;
            current_word = realloc(current_word, current_word_pos + 1);
            current_word[current_word_pos] = letter;
            current_word_pos++;
        } else {
            // this is necessary to account for the extra spaces in provided file
            if(first_iteration == 1){
                continue;
            }
            break;
        }
    }

    return current_word;

}

int get_caesar_cipher(HashTable *hash_table, char* current_string, int count){
    
    // go through every shift
    for(int shift=0; shift < 26; shift++){

        // prepare variables needed to examine current phrase
        int is_valid = 1;
        int current_pos = 0;
        char* generated_string = generate_new_string_from_cipher(current_string, count, shift);

        // go through newly generated string
        while(current_pos < count){

            // check each word in phrase separately since we are given a dictionary of single words
            char* current_word = get_word_from_generated_string(generated_string, current_pos, count);
            current_pos = current_pos + strlen(current_word) + 1;

            // perform calculation since we have a complete word
            if(current_pos != 0){

                // check if the value is in our hash table
                int word_is_valid = check_if_word_exists_in_hash_table(hash_table, current_word);

                // if a word is not valid, go to the next shift
                if(word_is_valid == 0){
                    is_valid = 0;
                    break;
                }
            }
        }

        // return the shift if the entire line was valid
        if(is_valid == 1){
            return shift;
        }
    }
    // catch all just in case.
    return 0;
}

// helper function given by TA
char* create_pointer(int size){
    char* ret = malloc(size*sizeof(char));
    for(int i = 0; i < size; i++){
        ret[i] = i;
    }
    return ret;
}

// helper function given by TA
void print_matrix(char* x, int size){
    printf("%s\n", x);
}
