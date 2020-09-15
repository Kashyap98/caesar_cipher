#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// init function headers
char* create_pointer(int size);
void print_matrix(char* x, int size);
char** get_all_alphabets(char* ALPHABET);
int get_caesar_cipher(char* current_string, int count, char** alphabets, char* regular_alphabet);

int main(){

    // declare main variables
    char c;
    int count = 0;
    int buffer_size = 256;
    char* current_string = malloc(buffer_size);
    int iter = 1;

    char ALPHABET[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char** all_alphabets = get_all_alphabets(ALPHABET);
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
            int cipher_offset = get_caesar_cipher(current_string, count, all_alphabets, ALPHABET);
            printf("%d\n", cipher_offset);

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
    int cipher_offset = get_caesar_cipher(current_string, count, all_alphabets, ALPHABET);
    printf("%d\n", cipher_offset);
    output_file = fopen("solutions.txt", "a");
    fprintf(output_file, "%d\n", cipher_offset);
    fflush(output_file);
    fclose(output_file);
    free(current_string);
    current_string = calloc(1, sizeof(char));
    count = 0;

}

int get_caesar_cipher(char* current_string, int count, char** alphabets, char* regular_alphabet){
    char* current_word = malloc(1);
    char* generated_string = malloc(1);
    
    // go through every shift
    for(int shift=0; shift < 26; shift++){
        // prepare for generating new string with a new shift
        free(generated_string);
        generated_string = calloc(1, sizeof(char));
        int generated_count = 0;

        // go through every letter in the string
        for(int letter_pos=0; letter_pos < count; letter_pos++){
            char letter = current_string[letter_pos];

            // check if the letter is a space
            if(letter == ' '){
                generated_string = realloc(generated_string, generated_count+1);
                generated_string[generated_count] = ' ';
                generated_count++;
            } else {
                // find position of the letter in the shifted alphabet
                for(int i=0; i < 26; i++){
                    if(letter == alphabets[shift][i]){
                        // once the position is found, find the right letter in the regular alphabet.
                        generated_string = realloc(generated_string, generated_count+1);
                        generated_string[generated_count] = regular_alphabet[i];
                        generated_count++;
                        break;
                    }
                }
            }
        }

        int current_word_pos = 0;
        int is_valid = 1;

        // go through newly generated string
        for(int pos=0; pos < count; pos++){
            
            // add to the current word since we have not reached a space or the end of the line
            char letter = generated_string[pos];
            if(letter != ' ' && letter != '\n'){
                current_word = realloc(current_word, current_word_pos+1);
                current_word[current_word_pos] = letter;
                current_word_pos++;
            }

            // perform calculation since we have a complete word
            if(letter == ' ' || letter == '\n' || pos == (count - 1)){
                if(current_word_pos != 0){

                    // printf("%s\n", current_word);
                    int word_is_valid = 0;
                    FILE *fp;
                    fp = fopen("dictionary2.txt", "r");
                    char buff[128];

                    // read the dictionary and check if it is a valid word
                    while(fgets(buff, 128, (FILE*)fp) != NULL){
                        buff[strlen(buff) - 1] = '\0';
                        // printf("%s - %s\n", buff, generated_string);
                        if(strcmp(current_word, buff) == 0){
                            print_matrix(current_word, generated_count);
                            word_is_valid = 1;
                            break;
                        }
                    }

                    // prepare for checking a new word
                    free(current_word);
                    current_word = calloc(1, sizeof(char));
                    current_word_pos = 0;
                    fclose(fp);

                    // if a word is not valid, go to the next shift
                    if(word_is_valid == 0){
                        is_valid = 0;
                        break;
                    }

                }
            }
        }

        // free the newly created string
        free(generated_string);
        generated_string = calloc(1, sizeof(char));

        // return the shift if the entire line was valid
        if(is_valid == 1){
            // printf("%d\n", shift);
            return shift;
        }
    }
    // catch all just in case.
    return 0;
}

char** get_all_alphabets(char* ALPHABET){
    // create a list of alphabets with all the shifts
    char** all_alphabets = create_pointer(26);
    
    // go through every letter being the first letter
    for(int shift=0; shift < 26; shift++){
        char* current_alphabet = create_pointer(26);
        int current_index = shift;
        int i = 0;

        // go through entire alphabet
        while(i <= 25){

            int final_index = 0;
            // correct in case the index is out of bounds
            if(current_index >= 26){
                final_index = current_index - 26;
            } else {
                final_index = current_index;
            }

            current_alphabet[i] = ALPHABET[final_index];
            
            current_index++;
            i++;
        }
        // add shifted alphabet to current list
        all_alphabets[shift] = current_alphabet;
        // printf("%s\n", current_alphabet);
    }

    return all_alphabets;
}

// helper functions given by TA
char* create_pointer(int size){
    char* ret = malloc(size*sizeof(int));
    for(int i = 0; i < size; i++){
        ret[i] = i;
    }
    return ret;
}

void print_matrix(char* x, int size){
    printf("%s\n", x);
}
