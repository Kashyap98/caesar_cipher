#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// init function headers
char* create_pointer(int size);
void print_matrix(char* x, int size);
int get_caesar_cipher(char* current_string, int count);
char* generate_new_string_from_cipher(char* input_string, int count, int shift);

int main(){

    // declare main variables
    char c;
    int count = 0;
    int buffer_size = 256;
    char* current_string = malloc(buffer_size);
    int iter = 1;

    FILE *output_file;

    // This was added to clear the solutions.txt file
    output_file = fopen("solutions.txt", "w");
    fflush(output_file);
    fclose(output_file);


    // continue until no input is detected.
    while((c=getchar()) != EOF){
        if(count%256 == 0 && count > 0 && (c != '\n' && c !=0)){
            current_string = realloc(current_string, ((iter+1)*(buffer_size)*(sizeof(char))));
        } else if(c == '\n' || c == 0){         
            // get the cipher offset because it is the end of the line   
            int cipher_offset = get_caesar_cipher(current_string, count);
            // printf("%d\n", cipher_offset);

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
    int cipher_offset = get_caesar_cipher(current_string, count);
    // printf("%d\n", cipher_offset);
    output_file = fopen("solutions.txt", "a");
    fprintf(output_file, "%d\n", cipher_offset);
    fflush(output_file);
    fclose(output_file);
    free(current_string);
    current_string = calloc(1, sizeof(char));
    count = 0;

}

char* generate_new_string_from_cipher(char* input_string, int count, int shift){

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

            int new_letter = letter - shift;
            if(new_letter < (int)'A'){
                new_letter = new_letter + 26;
            }
            generated_string = realloc(generated_string, generated_count+1);
            generated_string[generated_count] = (char)new_letter;
            generated_count++;

        }
    }

    return generated_string;

}

char* get_word_from_generated_string(char* generated_string, int starting_pos, int count){

    char* current_word = malloc(1);
    free(current_word);
    current_word = create_pointer(1);
    int current_word_pos = 0;
    int first_iteration = 1;

    for(int pos = starting_pos; pos < count; pos++){

         // add to the current word since we have not reached a space or the end of the line
        char letter = generated_string[pos];
        // printf("%c - %i\n", letter, (int)letter != 32);

        if(letter != ' ' && letter != '\n' && letter != '\0'){
            first_iteration = 0;
            current_word = realloc(current_word, current_word_pos + 1);
            current_word[current_word_pos] = letter;
            current_word_pos++;
        } else {
            if((first_iteration == 1)){
                continue;
            }
            break;
        }
    }

    return current_word;

}

int get_caesar_cipher(char* current_string, int count){
    
    // go through every shift
    for(int shift=0; shift < 26; shift++){

        int is_valid = 1;
        int current_pos = 0;
        char* generated_string = generate_new_string_from_cipher(current_string, count, shift);

        // printf("%s - %i - %i\n", generated_string, shift, count);

        // go through newly generated string
        while(current_pos < count){

            char* current_word = get_word_from_generated_string(generated_string, current_pos, count);
            current_pos = current_pos + strlen(current_word) + 1;

            // perform calculation since we have a complete word
            if(current_pos != 0){

                // printf("%s\n", current_word);
                int word_is_valid = 0;
                FILE *fp;
                fp = fopen("dictionary2.txt", "r");
                char buff[128];

                // read the dictionary and check if it is a valid word
                while(fgets(buff, 128, (FILE*)fp) != NULL){
                    buff[strlen(buff) - 1] = '\0';
                    if(strlen(buff) == strlen(current_word)){
                        // printf("%i - %i\n", strlen(buff), strlen(current_word));
                        // printf("%s - %s\n", buff, generated_string);
                        if(strcmp(current_word, buff) == 0){
                            print_matrix(current_word, strlen(current_word));
                            word_is_valid = 1;
                            break;
                        }

                    }
                    
                }

                // prepare for checking a new word
                fclose(fp);

                // if a word is not valid, go to the next shift
                if(word_is_valid == 0){
                    is_valid = 0;
                    break;
                }
            }
        }

        // return the shift if the entire line was valid
        if(is_valid == 1){
            printf("%d\n", shift);
            return shift;
        }
    }
    // catch all just in case.
    return 0;
}

// helper functions given by TA
char* create_pointer(int size){
    char* ret = malloc(size*sizeof(char));
    for(int i = 0; i < size; i++){
        ret[i] = i;
    }
    return ret;
}

void print_matrix(char* x, int size){
    printf("%s\n", x);
}
