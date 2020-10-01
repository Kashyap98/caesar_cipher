#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// structs in this class
typedef struct HashEntry HashEntry;
typedef struct HashTable HashTable;

// functions in this class
int check_if_word_exists_in_hash_table(HashTable *hash_table, char* word);
HashEntry *create_new_hash_entry(char* hash_value);
int add_entry_to_hash_table(HashTable *hash_table, char* string_value);
int generate_hash_for_string(char* string_buffer);
HashTable *create_empty_hash_table();


// Define our HashEntry (key value pairs & collisions) and HashTable (multiple HashEntries, limit 10,000)
struct HashEntry{
    char *value;
    struct HashEntry *next_entry;
};

struct HashTable{

    HashEntry **hash_entries;

};

int main(){

    FILE *fp;
    fp = fopen("dictionary2.txt", "r");
    char buff[128];
    int count = 0;
    HashTable *hash_table = create_empty_hash_table();

    // read the dictionary and check if it is a valid word
    while(fgets(buff, 128, (FILE*)fp) != NULL){
        buff[strlen(buff) - 1] = '\0';
        int hash_val = add_entry_to_hash_table(hash_table, buff);
        count++;
        printf("%i\n", count);
        // HashEntry *retrieved_entry = hash_table->hash_entries[hash_val];

        // printf("The Hash: %s matches the key %i\n", retrieved_entry->value, hash_val);

    }

    int found_count = 0;
    fp = fopen("dictionary2.txt", "r");
    while(fgets(buff, 128, (FILE*)fp) != NULL){
        buff[strlen(buff) - 1] = '\0';
        // printf("%s\n", buff);

        int value_present = check_if_word_exists_in_hash_table(hash_table, buff);
        if(value_present == 1){
            found_count++;
        }
        printf("%i\n", found_count);

    }

}

int check_if_word_exists_in_hash_table(HashTable *hash_table, char* word){

    // init word being present to false and get hash of the word
    int word_exists = 0;
    int hash_value = generate_hash_for_string(word);

    HashEntry *entry = hash_table->hash_entries[hash_value];

    // we have no entry in our table for this word
    if(entry == NULL){
        return word_exists;
    }


    // loop through entries for that hash to see if any of the values match.
    while(entry != NULL){

        // printf("Comparing %s to %s\n", entry->value, word);

        if(strcmp(entry->value, word) == 0){
            word_exists = 1;
            break;
        }

        HashEntry *new_entry = entry->next_entry;
        entry = new_entry;

    }
    
    return word_exists;
}

HashEntry *create_new_hash_entry(char* hash_value){

    HashEntry *hash_entry = malloc(sizeof(HashEntry) * 1);
    hash_entry->value = malloc(1 * sizeof(char));
    hash_entry->next_entry = malloc(1 * sizeof(HashEntry));
    strcpy(hash_entry->value, hash_value);
    hash_entry->next_entry = NULL;

    return hash_entry;
}

int add_entry_to_hash_table(HashTable *hash_table, char* string_value){

    // get hash and hash_entry for the string
    int hash_value = generate_hash_for_string(string_value);
    HashEntry *hash_entry = create_new_hash_entry(string_value);

    // check if there will be a collision
    if(hash_table->hash_entries[hash_value] != NULL){
        int value_added = 0;
        HashEntry *previous_entry = hash_table->hash_entries[hash_value];

        // traverse the singly linked list of collisions until an empty spot is found
        while(previous_entry->next_entry != NULL){

            // check to make sure we have no already added the value.
            if(strcmp(previous_entry->value, string_value) == 0){
                value_added = 1;
                break;
            }

            HashEntry *new_previous_entry = previous_entry->next_entry;
            previous_entry = new_previous_entry;

        }

        // add the entry to the singly linked list. Check to make sure we do not already have the value
        if(value_added == 0){
            previous_entry->next_entry = hash_entry;
        }
        
    } else {

        // there was no collison. handle normally
        hash_table->hash_entries[hash_value] = hash_entry;
    }
    
    return hash_value;
}

int generate_hash_for_string(char* string_buffer){
    int hash_value = 5381;

    for(int i = 0; i < strlen(string_buffer); i++){
        hash_value = hash_value * 33 + (int)string_buffer[i];
    }

    int ceiling_value = hash_value % 10000;
    int final_hash_value = abs(ceiling_value);
    return final_hash_value;
}

HashTable *create_empty_hash_table(){

    HashTable *hash_table = malloc(sizeof(HashTable) * 1);

    // init the hash_entries var
    hash_table->hash_entries = malloc(sizeof(HashEntry*) * 10000);

    // init all the entries to null. Doing this allows us to quickly check if an entry is placed there in the future.
    // we have 8732 lines in our dictionary.
    for(int i = 0; i < 10000; i++){

        hash_table->hash_entries[i] = NULL;

    }

    return hash_table;

}



