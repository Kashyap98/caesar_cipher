#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "decrypt.h"

int main(){

    // declare main variables
    char c;
    int count = 0;
    int buffer_size = 256;
    char* current_string = malloc(buffer_size);
    int iter = 1;
    HashTable *hash_table = fill_hash_table_with_values();

    FILE *output_file;

    // This was added to clear the solutions.txt file
    output_file = fopen("solutions.txt", "w");
    fflush(output_file);
    fclose(output_file);

    // continue until no input is detected.
    while((c=getchar()) != EOF){
        if(count%256 == 0 && count > 0 && (c != '\n' && c !=0)){
            // add to the current string
            current_string = realloc(current_string, ((iter+1)*(buffer_size)*(sizeof(char))));
        } else if(c == '\n' || c == 0){         
            // get the cipher offset because it is the end of the line   
            int cipher_offset = get_caesar_cipher(hash_table, current_string, count);

            // add cipher offset to solutions file
            output_file = fopen("solutions.txt", "a");
            fprintf(output_file, "%d\n", cipher_offset);
            fflush(output_file);
            fclose(output_file);

            // free string var to be used again
            free(current_string);
            current_string = calloc(buffer_size, sizeof(char));
            count = 0;
        } else {
            // continue adding to the current string
            current_string[count] = c;
            count += 1;
        }
    }

    // perform offset calculation on the last line.
    int cipher_offset = get_caesar_cipher(hash_table, current_string, count);

    // write to output file
    output_file = fopen("solutions.txt", "a");
    fprintf(output_file, "%d\n", cipher_offset);
    fflush(output_file);
    fclose(output_file);
}