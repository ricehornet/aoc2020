#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void update_passport(char* passport_line, uint8_t* passport)
{
    char* save;
    char* token = strtok_r(passport_line, " ", &save);
    while (token != NULL)
    {
        // based on detected fields, set bits in mask
        if (strncmp(token, "byr", 3) == 0)
        {
            *passport |= (1 << 7);
        }
        else if (strncmp(token, "iyr", 3) == 0)
        {
            *passport |= (1 << 6);
        }
        else if (strncmp(token, "eyr", 3) == 0)
        {
            *passport |= (1 << 5);
        }
        else if (strncmp(token, "hgt", 3) == 0)
        {
            *passport |= (1 << 4);
        }
        else if (strncmp(token, "hcl", 3) == 0)
        {
            *passport |= (1 << 3);
        }
        else if (strncmp(token, "ecl", 3) == 0)
        {
            *passport |= (1 << 2);
        }
        else if (strncmp(token, "pid", 3) == 0)
        {
            *passport |= (1 << 1);
        }
        else if (strncmp(token, "cid", 3) == 0)
        {
            *passport |= 1;
        }

        // get next token
        token = strtok_r(NULL, " ", &save);
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