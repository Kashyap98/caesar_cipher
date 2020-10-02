#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// structs in this class
typedef struct HashEntry HashEntry;
typedef struct HashTable HashTable;

// functions in this class
HashTable *fill_hash_table_with_values();
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

#endif