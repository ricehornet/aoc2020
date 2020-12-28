#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

const char NEWLINE = '\n';

// `password` values may change, but not the pointer itself
bool password_valid(char* password)
{
    // parsed from string
    int first_index = 0;
    int second_index = 0;
    char rule_letter;
    char* save_state;
    char* nums_token_save_state;

    // make a copy of the input -- will be mutated!
    char pwd_copy[50];
    char* pwd_copy_ptr = &pwd_copy[0];
    memcpy(pwd_copy_ptr, password, sizeof(pwd_copy));
    printf("processing password: %s\n", pwd_copy_ptr);

    char* nums_token = strtok_r(pwd_copy_ptr, " ", &save_state);

    if (nums_token != NULL)
    {
        printf("nums token: %s\n", nums_token);
        char* hyphen = strchr(nums_token, 45); // '-' character
        char* first_index_token = strtok_r(nums_token, "-", &nums_token_save_state);
        sscanf(nums_token, "%d", &first_index);
        char* second_index_token = hyphen + 1; // XXX: pointer math: assumes char is 1 byte wide!
        sscanf(second_index_token, "%d", &second_index);
        printf("1st index: %d, second index: %d\n", first_index, second_index);
    }
    else
    {
        printf("nums token is null\n");
        return false;
    }

    char* rule_letter_token = strtok_r(NULL, " ", &save_state);
    rule_letter = (char) *rule_letter_token;
    printf("rule letter: %c\n", rule_letter);

    char* password_token = strtok_r(NULL, " ", &save_state);
    if (password_token != NULL)
    {
        // just check if `rule letter` occurs at the first index
        // XOR the second index in the password
        const bool first_index_validated = password_token[first_index - 1] == rule_letter;
        const bool second_index_validated = password_token[second_index - 1] == rule_letter;
        const bool validated = first_index_validated ^ second_index_validated;
        if (validated)
        {
            printf("valid password\n");
            return true;
        }
    }
    return false;
}

int main()
{
    // read file
    FILE* fp;
    fp = fopen("../raw/d2p1_input.txt", "r");
    if (fp == NULL)
    {
        printf("error: could not open input file\n");
        return -1;
    }

    uint16_t valid_passwords_count = 0;
    char buf[50];
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        // ignore newlines
        if (strncmp(buf, &NEWLINE, 1) == 0)
        {
            continue;
        }

        if (password_valid(&buf[0]))
        {
            valid_passwords_count++;
        }

        memset(buf, 0, sizeof(buf));
    }

    printf("valid passwords count: %d\n", valid_passwords_count);

    // close file
    (void) fclose(fp);
    return 0;
}