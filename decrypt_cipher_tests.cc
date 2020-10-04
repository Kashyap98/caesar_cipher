#include <gtest/gtest.h>
#include "decrypt.hh"
#include <string.h>


TEST(DecryptCipherTest, GenerateStringFromShift) {

    // input strings
    char* input_string = strdup("BUJI");
    char* correct_string = strdup("LETS");

    // get permutation
    ASSERT_EQ(strcmp(generate_new_string_from_cipher(input_string, 4, 0), input_string), 0);
    ASSERT_EQ(strcmp(generate_new_string_from_cipher(input_string, 4, 16), correct_string), 0);
}

TEST(DecryptCipherTest, GenerateStringFromShiftUsingPhrase) {

    // input strings
    char* input_string = strdup("BUJI JHO IECUJXYDW");
    char* correct_string = strdup("LETS TRY SOMETHING");

    // get permutations
    ASSERT_EQ(strcmp(generate_new_string_from_cipher(input_string, 18, 0), input_string), 0);
    ASSERT_EQ(strcmp(generate_new_string_from_cipher(input_string, 18, 16), correct_string), 0);
}

TEST(DecryptCipherTest, GetWordFromNormalSentence) {

    // input string
    char* input_string = strdup("LETS TRY SOMETHING");

    // answer strings
    char* lets_string = strdup("LETS");
    char* try_string = strdup("TRY");
    char* something_string = strdup("SOMETHING");

    // get words
    ASSERT_EQ(strcmp(get_word_from_generated_string(input_string, 0, 18), lets_string), 0);
    ASSERT_EQ(strcmp(get_word_from_generated_string(input_string, 5, 18), try_string), 0);
    ASSERT_EQ(strcmp(get_word_from_generated_string(input_string, 9, 18), something_string), 0);
}

TEST(DecryptCipherTest, GetWordFromSentenceWithDoubleSpace) {

    // input string
    char* input_string = strdup("LETS TRY  SOMETHING");

    // answer strings
    char* lets_string = strdup("LETS");
    char* try_string = strdup("TRY");
    char* something_string = strdup("SOMETHING");

    // get words
    ASSERT_EQ(strcmp(get_word_from_generated_string(input_string, 0, 19), lets_string), 0);
    ASSERT_EQ(strcmp(get_word_from_generated_string(input_string, 5, 19), try_string), 0);
    ASSERT_EQ(strcmp(get_word_from_generated_string(input_string, 9, 19), something_string), 0);
}

TEST(DecryptCipherTest, GetValidCipher) {

    // input string
    char* input_string = strdup("BUJI JHO IECUJXYDW");
    HashTable *hash_table = fill_hash_table_with_values();

    // get cipher
    ASSERT_EQ(get_caesar_cipher(hash_table, input_string, 18), 16);
}

TEST(DecryptCipherTest, GetInvalidCipher) {

    // input string
    char* input_string = strdup("BUJI JHO IECUJXYDW FHDAFKD JFDKASFJDKAJF JFKDAJFKD");
    HashTable *hash_table = fill_hash_table_with_values();

    // get cipher
    ASSERT_EQ(get_caesar_cipher(hash_table, input_string, 50), 0);

}
