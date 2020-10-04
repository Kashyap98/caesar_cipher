#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"


HashTable *fill_hash_table_with_values(){

    // open dictionary file and prepare reading buffer
    FILE *fp;
    fp = fopen("dictionary2.txt", "r");
    char buff[128];

    HashTable *hash_table = create_empty_hash_table();

    // read the dictionary and check if it is a valid word
    while(fgets(buff, 128, (FILE*)fp) != NULL){
        buff[strlen(buff) - 1] = '\0';
        int hash_val = add_entry_to_hash_table(hash_table, buff);
    }

    return hash_table;
}

int check_if_word_exists_in_hash_table(HashTable *hash_table, char* word){

    // init word being present to false and get hash of the word
    int word_exists = 0;
    int hash_value = generate_hash_for_string(word);

    // find a potential match in our hash table
    HashEntry *entry = hash_table->hash_entries[hash_value];

    // we have no entry in our table for this word
    if(entry == NULL){
        return word_exists;
    }

    // loop through entries for that hash to see if any of the values match.
    while(entry != NULL){

        // compare values of the strings. If it matches we can exit since we found a match
        if(strcmp(entry->value, word) == 0){
            word_exists = 1;
            break;
        }

        // continue to check next entry.
        HashEntry *new_entry = entry->next_entry;
        entry = new_entry;

    }
    
    return word_exists;
}

HashEntry *create_new_hash_entry(char* hash_value){
    // allocate memory for entry
    HashEntry *hash_entry = malloc(sizeof(HashEntry) * 1);
    hash_entry->value = malloc(1 * sizeof(char));
    hash_entry->next_entry = malloc(1 * sizeof(HashEntry));

    // enter the hash value and init pointer to potential collision
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

        // printf("%s collides with %s with a hash value of %i", previous_entry->value, string_value, hash_value);

        // traverse the singly linked list of collisions until an empty spot is found
        while(previous_entry->next_entry != NULL){

            // check to make sure we have no already added the value.
            if(strcmp(previous_entry->value, string_value) == 0){
                value_added = 1;
                break;
            }

            // continue down the chain to find an empty spot
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

// This hash algo is the djb2 or Times 33 algo. Source is found in README
int generate_hash_for_string(char* string_buffer){
    int hash_value = 5381;

    // for entire string add the previous value, multiply by 33, and add the new char
    for(int i = 0; i < strlen(string_buffer); i++){
        hash_value = (hash_value * 33) + (int)string_buffer[i];
    }

    // modulus by 10,000 to provide a ceiling for our algo. This will lead to collisions, but will allow us to init a smaller table.
    int ceiling_value = hash_value % 10000;
    int final_hash_value = abs(ceiling_value);
    return final_hash_value;
}

HashTable *create_empty_hash_table(){

    // allocate memory for our new hash table
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
