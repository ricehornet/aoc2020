#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CHAR_LOWER_A_ASCII_DEC_VALUE 97

int main()
{
    // for each group, go line-by-line
    // and increment the count for each new
    // unique char that is seen
    // every time you encounter a newline, this
    // indicates a new group; restart the unique
    // chars array that you have seen (up to 26)

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
    // bitmask for keeping track of unique chars seen per group
    uint32_t alphabet_bitmask = 0;
    // count per line
    uint8_t line_count = 0;
    while (fgets(&line[0], sizeof(line), fp) != NULL)
    {
        // if the line is empty (just a newline), go to next group
        if (strncmp(&NEWLINE, line, 1) == 0)
        {
            alphabet_bitmask = 0;
            printf("empty line; moving to next group\n");
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
                // got to end of line, add to total and do not continue parsing
                total_answers_count = total_answers_count + line_count;
                line_count = 0;
                printf("got to end of line, total count: %d\n", total_answers_count);
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
                    line_count = line_count + 1;
                    printf("have not seen letter: %c, line count: %d, mask:%d\n", letter, line_count, alphabet_bitmask);
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

    printf("total count: %d\n", total_answers_count);
    return 0;
}
