#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// descending order comparator from d1p1.c
int desc_comparator(const void* a, const void* b)
{
    // descending because if a > b, a should come
    // first or this function should return negative
    return *((long*) b) - (*(long*) a);
}

// basically the solution in d1p1.c
bool preamble_has_weakness(long* preamble, uint8_t preamble_length, long value_to_check)
{
    for (uint8_t i = 0; i < preamble_length; i++)
    {
        long a = preamble[i];
        for (uint8_t j = preamble_length - 1; j > 0; j--)
        {
            if (i == j)
            {
                // no result found
                printf("could not find match in preamble, %ld is the weakness\n", value_to_check);
                return true;
            }
            long b = preamble[j];
            long sum = a + b;
            if (sum == value_to_check)
            {
                printf("value validated, %ld + %ld = %ld\n", a, b, value_to_check);
                return false;
            }
            else if (sum > value_to_check)
            {
                // go to next value of a
                break;
            }
        }
    }
    printf("iterated through entire array, no match, %ld is the weakness\n", value_to_check);
    return true;
}

uint32_t find_xmas_weakness(uint8_t preamble_length)
{
    long preamble[25] = {0};
    uint8_t preamble_length_bytes = sizeof(long) * preamble_length;

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
        // printf("read line: %s\n", buf);
        sscanf(buf, "%ld", &num);
        nums[index] = num;
        // printf("stored %ld at index %d\n", nums[index], index);
        index++;
    }
    printf("read in %d numbers to validate\n", index);

    for (uint16_t offset = 0; offset < sizeof(nums); offset++)
    {
        // copy first n nums into preamble, offset by 0 to start
        // printf("address of preamble: %p, address of nums: %p, address of buf: %p\n", &preamble[0], &nums[1000], &buf[0]);
        (void) memset(&preamble[0], 0, preamble_length_bytes);
        (void) memcpy(&preamble[0], &nums[offset], preamble_length_bytes);
        //printf("first n nums:\n");
        //for (uint8_t i = 0; i < preamble_length; i++)
        //{
        //    printf("%ld\n", nums[i]);
        //}
        //printf("preamble to check:\n");
        //for (uint8_t j = 0; j < preamble_length; j++)
        //{
        //    printf("%ld\n", preamble[j]);
        //}
        long value_to_check = nums[preamble_length + offset];
        printf("value to check: %ld\n", value_to_check);

        // sort the preamble to do the check
        qsort(preamble, preamble_length, sizeof(long), desc_comparator);

        // do the check -- if it returns a result, we can move on
        if (preamble_has_weakness(preamble, preamble_length, value_to_check))
        {
            return value_to_check;
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    // goal: find the first number in a sequence that is not the sum of two
    // of the n numbers that came before it.
    // start with n = 25

    // start by reading the preamble and storing it in an array
    // then read in the next number and check: do any of the previous 25
    // numbers add up to it?

    // we can do this check by using the solution from day 1: which two
    // numbers in a list add up to this number? If there is a solution,
    // then we move on and update the rolling array of n numbers

    if (argc == 2)
    {
        // first arg is n, preamble length
        int input = 0;
        sscanf(argv[1], "%d", &input);
        printf("preamble length: %d\n", (uint8_t) input);
        uint32_t first_weakness_num = find_xmas_weakness((uint8_t) input);
        if (first_weakness_num == 0)
        {
            printf("could not find a solution, exiting with error\n");
            return -1;
        }
        printf("first weakness: %d\n", first_weakness_num);
        return first_weakness_num;
    }
    else
    {
        printf("expected 1 parameter (preamble length)\n");
        return -1;
    }
}