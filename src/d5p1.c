#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t get_seat_id(char* bpass)
{
    uint8_t row = 0;
    uint8_t col = 0;
    // parse the row first
    printf("parsing boarding pass: %s\n", bpass);
    for (uint8_t i = 0; i < 7; i++)
    {
        if (strncmp(&bpass[i], "B", 1) == 0)
        {
            row |= 1 << (6 - i);
        }
    }

    // parse column
    for (uint8_t i = 0; i < 3; i++)
    {
        if (strncmp(&bpass[7 + i], "R", 1) == 0)
        {
            col |= 1 << (2 - i);
        }
    }
    
    printf("row %d, col %d\n", row, col);

    return row * 8 + col;
}

int main()
{
    // read input file
    FILE* fp;
    fp = fopen("../raw/d5p1_input.txt", "r");
    if (fp == NULL)
    {
        printf("could not open input!\n");
        return -1;
    }

    // read boarding passes and store the highest
    // seat ID
    char buf[15];
    uint32_t max_seat_id = 0;
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        uint32_t seat_id = get_seat_id(buf);
        if (seat_id > max_seat_id)
        {
            max_seat_id = seat_id;
        }
    }

    printf("max seat ID is %d\n", max_seat_id);

    fclose(fp);
}