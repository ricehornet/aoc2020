#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// descending order comparator
int desc_comparator(const void* a, const void* b)
{
    // descending because if a > b, a should come
    // first or this function should return negative
    return *((int*) b) - (*(int*) a);
}

int main()
{
    // open file
    FILE* fp;
    fp = fopen("./d1p1_input.txt", "r");
    if (fp != NULL)
    {
        printf("able to open file successfully\n");
    }

    // go through the file line-by-line, converting to
    // int and adding to the array
    int nums[200] = {0};
    char buf[5] = {0};
    int num = 0;
    int index = 0;
    const char NEWLINE = '\n';
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        // ignore newlines
        if (strncmp(buf, &NEWLINE, 1) == 0)
        {
            continue;
        }
        printf("read line: %s\n", buf);
        sscanf(buf, "%d", &num);
        nums[index] = num;
        printf("stored %d at index %d\n", nums[index], index);
        index++;
    }

    // sort the array desc -- not stable and that is OK, we are
    // only interested in the absolute value, not the relative
    // pre-sort order/relationships
    qsort(nums, index, sizeof(int), desc_comparator);

    // start at the largest entry and add the smallest
    // check if it is 2020; if over 2020, then move to the next-
    // largest and repeat until the items are the same ...
    for (int i = 0; i < index; i++)
    {
        int a = nums[i];
        for (int j = index -1; j > 0; j--)
        {
            if (i == j)
            {
                // no result found
                return -1;
            }
            int b = nums[j];
            int sum = a + b;
            if (sum == 2020)
            {
                printf("found a match, a = %d and b = %d, product = %d\n", a, b, a * b);
                return a * b;
            }
            else if (sum > 2020)
            {
                // go to next value of a
                break;
            }
        }
    }

    printf("closing file safely ...\n");
    (void) fclose(fp);
}
