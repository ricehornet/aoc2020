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

    // start with the largest and next-largest as a and b. Move
    // b until it their sum is not over 2020, and then start from
    // the bottom of the list with c until you exceed 2020 or get
    // to b. When this happens, move b one down until you get to the
    // end, and then when that happens, move a.
    for (int i = 0; i < index; i++)
    {
        int a = nums[i];
        for (int j = i + 1; j > 0; j++)
        {
            int b = nums[j];
            int sum = a + b;
            if (sum < 2020)
            {
                for (int k = index - 1; k > j; k--)
                {
                    int c = nums[k];
                    printf("sum before adding c: %d, c = %d\n", a + b, c);
                    // TODO: understand why `sum = sum + c` does not work!
                    sum = a + b + c;
                    printf("sum after adding c: %d\n", sum);
                    if (sum == 2020)
                    {
                        printf("found the solution, a = %d, b = %d, c = %d, product = %d\n", a, b, c, a * b * c);
                        return a * b * c;
                    }
                    else if (sum > 2020)
                    {
                        // go to next value of b
                        break;
                    }
                }
            }
            else if (sum >= 2020)
            {
                // go to next value of a
                break;
            }
        }
    }

    printf("closing file safely ...\n");
    (void) fclose(fp);
}
