#include <gtest/gtest.h>
#include "hash_table.hh"
#include <string.h>


TEST(HashTableTest, CreateEmptyHashTable) {

    HashTable *hash_table = create_empty_hash_table();
    for(int i = 0; i < 10000; i++){
        ASSERT_EQ(hash_table->hash_entries[i], nullptr);
    }
}

TEST(HashTableTest, CalculateHashes) {

    char* health_string = strdup("HEALTH");
    char* piano_string = strdup("PIANO");

    //calculating both hashes twice to prove it is repeatable. 
    ASSERT_EQ(generate_hash_for_string(health_string), 2677);
    ASSERT_EQ(generate_hash_for_string(health_string), 2677);

    ASSERT_EQ(generate_hash_for_string(piano_string), 2748);
    ASSERT_EQ(generate_hash_for_string(piano_string), 2748);
    
}

TEST(HashTableTest, CalculateHashesExpectConflict) {

    char* original_string = strdup("HOUR");
    char* conflict_string = strdup("BOREDOM");

    //calculating both hashes to prove that a collision can happen
    ASSERT_EQ(generate_hash_for_string(original_string), 9987);
    ASSERT_EQ(generate_hash_for_string(conflict_string), 9987);
    
}

TEST(HashTableTest, CreateEntry) {

    // create hash entry
    char* health_string = strdup("HEALTH");
    HashEntry *hash_entry = create_new_hash_entry(health_string);

    // make sure new hash_entry object looks correct
    ASSERT_EQ(strcmp(hash_entry->value, health_string), 0);
    ASSERT_EQ(hash_entry->next_entry, nullptr);
    
    
}

TEST(HashTableTest, AddEntryToHashTable) {

    // init test vars
    char* original_string = strdup("HOUR");
    HashTable *hash_table = create_empty_hash_table();

    // assert the value is empty
    ASSERT_EQ(hash_table->hash_entries[9987], nullptr);

    // add value to table
    add_entry_to_hash_table(hash_table, original_string);

    // make sure new value exists in table
    ASSERT_NE(hash_table->hash_entries[9987], nullptr);
    ASSERT_EQ(strcmp(hash_table->hash_entries[9987]->value, original_string), 0);
    
}

TEST(HashTableTest, AddEntryToHashTableWithCollision) {

    // init test vars
    char* original_string = strdup("HOUR");
    char* conflict_string = strdup("BOREDOM");
    HashTable *hash_table = create_empty_hash_table();
    add_entry_to_hash_table(hash_table, original_string);

    // make sure new value exists in table
    ASSERT_NE(hash_table->hash_entries[9987], nullptr);
    ASSERT_EQ(strcmp(hash_table->hash_entries[9987]->value, original_string), 0);
    ASSERT_EQ(hash_table->hash_entries[9987]->next_entry, nullptr);

    // add collison
    add_entry_to_hash_table(hash_table, conflict_string);

    // make sure collision value is not empty
    ASSERT_NE(hash_table->hash_entries[9987]->next_entry, nullptr);
    ASSERT_EQ(strcmp(hash_table->hash_entries[9987]->next_entry->value, conflict_string), 0);
    
}

TEST(HashTableTest, CheckIfEntryExistsInTable) {

    // init test vars
    char* original_string = strdup("HOUR");
    HashTable *hash_table = create_empty_hash_table();

    // assert the value is empty
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, original_string), 0);

    // add value to table
    add_entry_to_hash_table(hash_table, original_string);

    // make sure new value exists in table
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, original_string), 1);

    
}

TEST(HashTableTest, CheckIfConflictEntryExistsInTable) {

    // init test vars
    char* original_string = strdup("HOUR");
    char* conflict_string = strdup("BOREDOM");
    HashTable *hash_table = create_empty_hash_table();

    // assert the value is empty
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, original_string), 0);
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, conflict_string), 0);

    // add value to table
    add_entry_to_hash_table(hash_table, original_string);

    // make sure new value exists in table
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, original_string), 1);
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, conflict_string), 0);

    // add conflict value to table
    add_entry_to_hash_table(hash_table, conflict_string);

    // make sure conflict exists in table
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, original_string), 1);
    ASSERT_EQ(check_if_word_exists_in_hash_table(hash_table, conflict_string), 1);
    
}

TEST(HashTableTest, EnsureEntireDictionaryIsHashed) {

    // create entire hash table found in the actual program
    HashTable *hash_table = fill_hash_table_with_values();
    FILE *fp;
    char buff[128];

    // go through entire dictionary and make sure every word is found in our hash table
    int found_count = 0;
    fp = fopen("dictionary2.txt", "r");
    while(fgets(buff, 128, (FILE*)fp) != NULL){
        buff[strlen(buff) - 1] = '\0';

        int value_present = check_if_word_exists_in_hash_table(hash_table, buff);
        if(value_present == 1){
            found_count++;
        }
    }
    
    ASSERT_EQ(found_count, 8732);
}