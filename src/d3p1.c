#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

uint32_t count_trees(uint8_t right, uint8_t down, char* map, uint32_t map_len, uint8_t line_len)
{
    printf("map length: %d, chars in line: %d\n", map_len, line_len);
    // start with the first character and then move 3 right
    // and add line_len to get to the same character one
    // row down; if our move right overflows, then reset
    // from the start of the row (pattern repeats)
    uint32_t map_posn = 0;
    uint32_t trees_count = 0;
    while (map_posn <= map_len)
    {
        printf("trying map posn %d\n", map_posn);
        bool is_tree = map[map_posn] == '#';
        if (is_tree)
        {
            printf("found tree at posn %d\n", map_posn);
            trees_count++;
        }

        // offset from the left side of the pattern
        uint8_t left_offset = map_posn % line_len;
        printf("left offset for this row: %d\n", left_offset);
        // "if the number of elements from the left plus `right`
        // is greater than the greatest offset per row minus 1,
        // (minus 1 because `left_offset` is elements *from* the
        // left, and we need to count the first element), then
        // we've overflowed"
        if (left_offset + right > line_len - 1)
        {
            // overflow the row to next pattern to right
            map_posn -= left_offset;
            map_posn += (left_offset + right) - line_len;
            map_posn += down * line_len;
        }
        else
        {
            map_posn += right + down * line_len;
        }
    }

    return trees_count;
}

int main()
{
    // open file
    FILE* fp;
    fp = fopen("../raw/d3p1_input.txt", "r");
    if (fp == NULL)
    {
        printf("could not open file!\n");
        return -1;
    }

    // get total length of file
    fseek(fp, 0, SEEK_END);
    uint32_t file_length = ftell(fp);

    // rewind to front of file for reading
    fseek(fp, 0, SEEK_SET);

    // allocate memory from heap to hold the file
    printf("attempting to allocate %d-byte buffer\n", file_length);
    char* data_ptr = (char*) calloc(file_length, sizeof(char));
    if (data_ptr == NULL)
    {
        printf("memory allocation error!\n");
        return -1;
    }

    // read file line-by-line and store in buffer (no newlines)
    char buf[50];
    memset(buf, 0, sizeof(buf));
    char* line = fgets(buf, sizeof(buf), fp);
    uint32_t offset = 0; // in bytes
    uint8_t line_len = 0;
    while (line != NULL)
    {
        // line length less newline char
        line_len = strlen(line) - 1;
        printf("copying line length %d to buffer offset %d: %s\n", line_len, offset, line);
        memcpy(data_ptr + offset, line, line_len);
        offset += line_len;
        memset(buf, 0, sizeof(buf));
        line = fgets(buf, sizeof(buf), fp);
    }

    // process map according to pattern: 3 right, 1 down
    uint32_t trees_encountered = count_trees(3, 1, data_ptr, offset, line_len);
    printf("found %d trees in this map\n", trees_encountered);

    free(data_ptr);

    // close file
    fclose(fp);
}