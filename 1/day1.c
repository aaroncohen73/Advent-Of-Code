#include <stdio.h>
#include <stdlib.h>

#define NUM_ENTRIES 200

/* Read the puzzle input and return an array of integers
 *
 * RETURNS: The array of integers from the input with length=NUM_ENTRIES
 */
int * read_nums()
{
    int * nums = (int *) malloc(NUM_ENTRIES * sizeof(int));

    FILE *fp = fopen("input.txt", "r");

    int i = 0;

    while (!feof(fp) && i < NUM_ENTRIES)
    {
        int num;
        fscanf(fp, "%d", &num);

        nums[i++] = num;
    }

    fclose(fp);

    return nums;
}

/* Standard quicksort implementation */
int partition(int *nums, int lo, int hi)
{
    int pivot = nums[(hi + lo) / 2];
    int i = lo - 1;
    int j = hi + 1;

    while (1)
    {
        do
        {
            i++;
        } while (nums[i] < pivot);
        do
        {
            j--;
        } while (nums[j] > pivot);

        if (i >= j) return j;

        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}

void quicksort(int *nums, int lo, int hi)
{
    if (lo < hi)
    {
        int p = partition(nums, lo, hi);
        quicksort(nums, lo, p);
        quicksort(nums, p+1, hi);
    }
}

/* Finds a pair of numbers from an array that sum to the desired value
 *
 * int *nums - The array of numbers to search
 * int lo - The first index in the array to search, inclusive
 * int hi - The last index in the array to search, inclusive
 * int sum - The desired sum value to search for
 * int *num1 - Int pointer to store the first number into. If no match found, undefined value
 * int *num2 - Int pointer to store the second number into. If no match found, undefined value
 *
 * RETURNS:
 *      If no pair of numbers could be found, 0
 *      If a pair of numbers was found, the multiplication between the first found pair of numbers
 */
int find_pair(int *nums, int lo, int hi, int sum, int *num1, int *num2)
{
    // Find cutoff point where entries < sum/2
    int cutoff = -1;
    for (int i = lo; i <= hi; i++)
    {
        if (nums[i] >= sum/2)
        {
            cutoff = i;
            break;
        }
    }
    if (cutoff == -1) return 0;

    // Brute force combinations from before and after cutoff until we get answer
    *num1 = 0;
    *num2 = 0;
    int found = 0;
    for (int i = lo; i < cutoff; i++)
    {
        for (int j = cutoff; j <= hi; j++)
        {
            if (nums[i] + nums[j] == sum)
            {
                *num1 = nums[i];
                *num2 = nums[j];
                found = 1;
                break;
            }
        }

        if (found) break;
    }

    return (*num1) * (*num2);
}

/* Finds a triplet of numbers from an array that sum to the desired value
 *
 * int *nums - The array of numbers to search
 * int lo - The first index in the array to search, inclusive
 * int hi - The last index in the array to search, inclusive
 * int sum - The desired sum value to search for
 * int *num1 - Int pointer to store the first number into. If no match found, undefined value
 * int *num2 - Int pointer to store the second number into. If no match found, undefined value
 * int *num3 - Int pointer to store the third number into. If no match found, undefined value
 *
 * RETURNS:
 *      If no triplet of numbers could be found, 0
 *      If a triplet of numbers was found, the multiplication between the first found triplet of numbers
 */
int find_triplet(int *nums, int lo, int hi, int sum, int *num1, int *num2, int *num3)
{
    // Narrow down the search space slightly by eliminating values that cannot belong to a triplet
    int upper_bound = sum - nums[lo] - nums[lo + 1];
    int lower_bound = sum - nums[hi] - nums[hi - 1];

    // Find low cutoff
    int cutoff_lo = -1;
    for (int i = lo; i <= hi; i++)
    {
        if (nums[i] >= lower_bound)
        {
            cutoff_lo = i;
            break;
        }
    }
    if (cutoff_lo == -1) return 0;

    // Find high cutoff
    int cutoff_hi = -1;
    for (int i = hi; i >= lo; i++)
    {
        if (nums[i] <= upper_bound)
        {
            cutoff_hi = i;
            break;
        }
    }
    if (cutoff_hi == -1) return 0;

    // Brute force combinations by picking one number and calling find_pair on the rest. If no triplet
    // found, move on to the next number and repeat
    *num1 = 0;
    *num2 = 0;
    *num3 = 0;
    int found = 0;
    for (int i = cutoff_lo; i <= cutoff_hi - 1; i++)
    {
        *num1 = nums[i];
        int result = find_pair(nums, i, cutoff_hi, sum - *num1, num2, num3);

        if (result) break;
    }
    return (*num1) * (*num2) * (*num3);
}

int main()
{
    int *nums = read_nums();
    quicksort(nums, 0, NUM_ENTRIES - 1);

    int num1, num2, num3;
    int pair_result = find_pair(nums, 0, NUM_ENTRIES - 1, 2020, &num1, &num2);

    printf("First number: %d\n", num1);
    printf("Second number: %d\n", num2);
    printf("Multiplied together: %d\n", pair_result);

    int triplet_result = find_triplet(nums, 0, NUM_ENTRIES - 1, 2020, &num1, &num2, &num3);

    printf("First number: %d\n", num1);
    printf("Second number: %d\n", num2);
    printf("Third number: %d\n", num3);
    printf("Multiplied together: %d\n", triplet_result);

    free(nums);

    return 0;
}
