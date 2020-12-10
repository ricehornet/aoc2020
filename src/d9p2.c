#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET 1038347917

// descending order comparator from d1p1.c
int desc_comparator(const void* a, const void* b)
{
    // descending because if a > b, a should come
    // first or this function should return negative
    return *((long*) b) - (*(long*) a);
}

// input an array of numbers and length, and try to
// sum them up (from the start) until the cumulative
// sum is `target`. If found, return true; otherwise
// return false
bool find_sequential_sum(long* input_numbers, uint16_t max_length, long target)
{
    long sum = 0;
    for (uint16_t i = 0; i < max_length; i++)
    {
        if (sum == target)
        {
            // sort the target range
            qsort(&input_numbers[0], i, sizeof(long), desc_comparator);

            // first element of sorted sequence
            long first = input_numbers[0];
            // last element of sorted sequence
            long last = input_numbers[i - 1];
            long sum = first + last;
            printf("found sequence! %ld + %ld = %ld\n", first, last, sum);
            return true;
        }
        if (sum > target)
        {
            printf("bust with starting number: %ld, sum = %ld\n", input_numbers[0], sum);
            // we've gone too far; stop looking
            return false;
        }
        sum += input_numbers[i];
    }
    return false;
}

int main()
{
    // goal: find the set of contiguous numbers (could be any size)
    // that, when summed together, add up to a specific number n.

    // to do this we start with the first number and keep on adding
    // sequential numbers until we exceed n.

    // if we exceed, then we start with the next number -- the first
    // number cannot be part of the sequence

    // open the file
    FILE* fp;
    fp = fopen("../raw/d9p1_input.txt", "r");
    if (fp == NULL)
    {
        printf("error: could not open file!\n");
        return 0;
    }
    
    // go through the file line-by-line, converting to
    // long int and adding to the array
    long nums[1000] = {0};
    char buf[20] = {0}; // holds max number in input
    long num = 0;
    uint16_t index = 0;
    const char NEWLINE = '\n';
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        // ignore newlines
        if (strncmp(buf, &NEWLINE, 1) == 0)
        {
            continue;
        }
        sscanf(buf, "%ld", &num);
        nums[index] = num;
        index++;
    }
    printf("read %d numbers to validate\n", index);

    uint16_t offset = 0;
    uint16_t interval_offset = 0;
    while (!find_sequential_sum(&nums[offset], sizeof(nums)/sizeof(nums[0]) - offset, TARGET))
    {
        offset++;
        printf("trying with starting num %ld and length %lu\n", nums[offset], sizeof(nums)/sizeof(nums[0]) - offset);
    }

    (void) fclose(fp);

    return 0;
}