#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CHAR_LOWER_A_ASCII_DEC_VALUE 97

int main()
{
    // for each group, go line-by-line
    // and update the mask
    // for each successive line, check the mask
    // -- if the letter does not appear, then
    // eliminate it from the mask
    // at the end of the group, count the masked
    // members

    // the key is realizing that it's all-inclusive,
    // so any letter that does not appear in the first
    // line cannot be part of the answer (or, only
    // the letters in the first line are the *maximum*
    // count for the group)

    // read file
    FILE* fp;
    fp = fopen("../raw/d6p1_input.txt", "r");
    if (fp == NULL)
    {
        printf("error: could not open input file\n");
        return 1;
    }

    // maximum length, plus buffer for newline chars and C string terminator
    char line[30] = {0};
    // total count of answers
    uint32_t total_answers_count = 0;
    const char NEWLINE = '\n';
    // bitmasks for keeping track of letters seen by all members of group
    uint32_t alphabet_bitmask = 0;
    uint32_t first_line_alphabet_bitmask = 0;
    // keep track if we're on the first line
    bool first_line = true;
    while (fgets(&line[0], sizeof(line), fp) != NULL)
    {
        // if the line is empty (just a newline), go to next group
        if (strncmp(&NEWLINE, line, 1) == 0)
        {
            // count up the number of set bits in the group-scoped mask
            for (uint8_t i = 0; i < 26; i++)
            {
                uint32_t mask = 1 << i;
                if (first_line_alphabet_bitmask & mask)
                {
                    printf("letter %d in common among all in group\n", i);
                    total_answers_count++;
                }
            }
            first_line_alphabet_bitmask = 0;
            alphabet_bitmask = 0;
            first_line = true;
            printf("empty line; moving to next group; total count: %d\n", total_answers_count);
            continue;
        }

        printf("processing line: %s\n", line);
        // otherwise parse the line char-by-char
        for (uint8_t i = 0; i < sizeof(line); i++)
        {
            char letter = line[i];
            printf("processing char: %d\n", (int) letter);
            if (strncmp(&NEWLINE, &letter, 1) == 0)
            {
                if (first_line)
                {
                    first_line_alphabet_bitmask = alphabet_bitmask;
                    first_line = false;
                }
                else
                {
                    // only keeps members appearing in both masks
                    first_line_alphabet_bitmask &= alphabet_bitmask;

                }
                // reset line-level mask
                alphabet_bitmask = 0;
                printf("got to end of line\n");
                break;
            }
            else if (letter >= 'a' && letter <= 'z')
            {
                // maps 'a' to 0, 'b' to 1 and so on
                uint8_t mask_shift = (uint8_t) letter - CHAR_LOWER_A_ASCII_DEC_VALUE;
                printf("mask shift for char %c is %d\n", letter, mask_shift);

                // check if we've seen letter before; first mask value is 'a'
                // should shift the mask up to 26 bits and return the least-significant bit
                bool seen_letter = alphabet_bitmask >> mask_shift & 0x00000001;

                if (!seen_letter)
                {
                    // update mask by setting the same bit
                    alphabet_bitmask |= 0x00000001 << mask_shift;
                    printf("have not seen letter: %c, mask:%d\n", letter, alphabet_bitmask);
                }
                else
                {
                    printf("already seen letter: %c\n", letter);
                }
            }
            else
            {
                // unexpected input -- once letters are over, move on
                printf("encountered unexpected input: %c\n", letter);
                break;
            }
        }
    }

    // final iteration at EOF
    for (uint8_t i = 0; i < 26; i++)
    {
        uint32_t mask = 1 << i;
        if (first_line_alphabet_bitmask & mask)
        {
            printf("letter %d in common among all in group\n", i);
            total_answers_count++;
        }
    }

    printf("total count: %d\n", total_answers_count);
    return 0;
}
