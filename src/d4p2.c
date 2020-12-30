#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

bool validate(char* key, char* val)
{
    // remove newlines -- will be at end
    if (strstr(val, "\n") != NULL)
    {
        char* newline = strstr(val, "\n");
        *newline = '\0';
    }

    if (strncmp(key, "byr", 3) == 0)
    {
        if (strlen(val) != 4)
        {
            return false;
        }
        uint32_t val_int = 0;
        sscanf(val, "%d", &val_int);
        if (val_int >= 1920 && val_int <= 2002)
        {
            printf("byr valid ");
            return true;
        }
    }
    else if (strncmp(key, "iyr", 3) == 0)
    {
        if (strlen(val) != 4)
        {
            return false;
        }
        uint32_t val_int = 0;
        sscanf(val, "%d", &val_int);
        if (val_int >= 2010 && val_int <= 2020)
        {
            printf("iyr valid ");
            return true;
        }
    }
    else if (strncmp(key, "eyr", 3) == 0)
    {
        if (strlen(val) != 4)
        {
            return false;
        }
        uint32_t val_int = 0;
        sscanf(val, "%d", &val_int);
        if (val_int >= 2020 && val_int <= 2030)
        {
            printf("eyr valid ");
            return true;
        }
    }
    else if (strncmp(key, "hgt", 3) == 0)
    {
        if (strstr(val, "cm") != NULL)
        {
            // number starts with "val" and ends at "num_end"
            char* num_end = strstr(val, "cm");
            char num[5];
            memset(num, 0, sizeof(num));
            memcpy(num, val, num_end - val);
            uint32_t val_int = 0;
            sscanf(val, "%d", &val_int);
            if (val_int >= 150 && val_int <= 193)
            {
                printf("hgt valid ");
                return true;
            }
        }
        else if (strstr(val, "in") != NULL)
        {
            // number starts with "val" and ends at "num_end"
            char* num_end = strstr(val, "in");
            char num[5];
            memset(num, 0, sizeof(num));
            memcpy(num, val, num_end - val);
            uint32_t val_int = 0;
            sscanf(val, "%d", &val_int);
            if (val_int >= 59 && val_int <= 76)
            {
                printf("hgt valid ");
                return true;
            }
        }
    }
    else if (strncmp(key, "hcl", 3) == 0)
    {
        if (strncmp(val, "#", 1) != 0)
        {
            return false;
        }
        else
        {
            if (strlen(&val[1]) == 6)
            {
                for (uint8_t i = 0; i < 6; i++)
                {
                    // get char
                    char c = val[1 + i];
                    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
                    {
                        printf("hcl valid ");
                        return true;
                    }
                }
            }
        }
    }
    else if (strncmp(key, "ecl", 3) == 0)
    {
        if (strncmp(val, "amb", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
        else if (strncmp(val, "blu", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
        else if (strncmp(val, "brn", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
        else if (strncmp(val, "gry", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
        else if (strncmp(val, "grn", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
        else if (strncmp(val, "hzl", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
        else if (strncmp(val, "oth", 3) == 0)
        {
            printf("ecl valid ");
            return true;
        }
    }
    else if (strncmp(key, "pid", 3) == 0)
    {
        if (strlen(val) != 9)
        {
            return false;
        }
        uint32_t val_int = 0;
        sscanf(val, "%d", &val_int);
        if (val_int > 0)
        {
            printf("pid valid ");
            return true;
        }
    }
    printf("\n");

    return false;
}

void update_passport(char* passport_line, uint8_t* passport)
{
    char* save;
    char* key = strtok_r(passport_line, " ", &save);
    char* val;
    while (key != NULL)
    {
        printf("processing key: %s ", key);
        char* token_save;
        bool valid = false;
        // based on detected fields, set bits in mask
        if (strncmp(key, "byr", 3) == 0)
        {
            // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 7);
            }
        }
        else if (strncmp(key, "iyr", 3) == 0)
        {
            // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 6);
            }
        }
        else if (strncmp(key, "eyr", 3) == 0)
        {
            // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 5);
            }
        }
        else if (strncmp(key, "hgt", 3) == 0)
        {
                        // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 4);
            }
        }
        else if (strncmp(key, "hcl", 3) == 0)
        {
            // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 3);
            }
        }
        else if (strncmp(key, "ecl", 3) == 0)
        {
            // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 2);
            }
        }
        else if (strncmp(key, "pid", 3) == 0)
        {
            // value is second token when delimiting
            // about ":"
            strtok_r(key, ":", &token_save);
            val = strtok_r(NULL, ":", &token_save);
            valid = validate(key, val);
            if (valid)
            {
                *passport |= (1 << 1);
            }
        }
        else if (strncmp(key, "cid", 3) == 0)
        {
            *passport |= 1;
        }

        // get next token
        key = strtok_r(NULL, " ", &save);
    }
}

int main()
{
    // read input file
    FILE* fp;
    fp = fopen("../raw/d4p1_input.txt", "r");
    if (fp == NULL)
    {
        printf("could not open input file!\n");
        return -1;
    }

    // represent each passport as an 8-bit bitmask
    // bit 7: BYR
    // bit 6: IYR
    // bit 5: EYR
    // bit 4: HGT
    // bit 3: HCL
    // bit 2: ECL
    // bit 1: PID
    // bit 0: CID
    uint8_t passports[1500];
    uint16_t passport_index = 0;

    char buf[100];
    memset(buf, 0, sizeof(buf));
    // assemble passports from input data
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        if (strncmp(buf, "\n", 1) == 0)
        {
            printf("newline; processing next passport\n");
            passport_index++;
            continue;
        }

        // tokenize line and update bitmask
        update_passport(buf, &passports[passport_index]);
        printf("passport %d: %d\n", passport_index, passports[passport_index]);
    }

    // process passport data:
    // since 'cid' is optional and the LSB in the mask,
    // a valid mask has value 255 or 254
    uint16_t valid_passports = 0;
    for (uint16_t i = 0; i < passport_index; i++)
    {
        if (passports[i] == 254 || passports[i] == 255)
        {
            valid_passports++;
        }
    }

    printf("valid passports: %d\n", valid_passports);

    // close file
    fclose(fp);
}