#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

const char NEWLINE = '\n';

uint8_t count_char(char* str, char c)
{
    uint8_t count = 0;
    uint8_t i = 0;
    while (str[i] != '\0')
    {
        if (strncmp(&str[i], &c, 1) == 0)
        {
            count++;
        }
        i++;
    }
    printf("counted %d occurrences of %c\n", count, c);
    return count;
}

// `password` values may change, but not the pointer itself
bool password_valid(char* password)
{
    // parsed from string
    int min_occurrences = 0;
    int max_occurrences = 0;
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
        char* min_token = strtok_r(nums_token, "-", &nums_token_save_state);
        sscanf(nums_token, "%d", &min_occurrences);
        char* max_token = hyphen + 1; // XXX: pointer math: assumes char is 1 byte wide!
        sscanf(max_token, "%d", &max_occurrences);
        printf("min: %d, max %d\n", min_occurrences, max_occurrences);
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
        // count the occurrences of `rule_letter`
        uint8_t count = count_char(password_token, rule_letter);
        if (count >= min_occurrences && count <= max_occurrences)
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