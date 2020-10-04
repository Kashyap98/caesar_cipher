#ifndef DECRYPT_H
#define DECRYPT_H


#include "hash_table.h"

// init function headers
char* create_pointer(int size);
void print_matrix(char* x, int size);
char* get_word_from_generated_string(char* generated_string, int starting_pos, int count);
int get_caesar_cipher(HashTable *hash_table, char* current_string, int count);
char* generate_new_string_from_cipher(char* input_string, int count, int shift);


#endif