#include "./headers/arr.h"

/*
 * arrlen:
 * return the length of array
 */
int arrlen(int *array)
{
    return array[0];
}

/*
 * showArray:
 * show value of array,
 * the first value (array[0]) contain the length of the array.
 * +-----+-----
 * | len | values...
 * +-----+-----
 */
void showArray(int *array)
{
    int colums = 10;
    // printf("\nsize of array : %d - %d\n", array[0], array[0] - 1);
    printf("\nsize of array : %d\n", array[0]);
    printf("\n\n");
    for (int i = 1, a = 1; i < arrlen(array); i++)
    {
        printf("%4d\t", array[i]);
        if (a == colums)
        {
            printf("\n");
            a = 0;
        }
        a++;
    }
}

/*
 * fillArray:
 * fill arrays
 * -> 1.2.3.4....
 * -> 1.3.5.7....
 */
void fillArray(int *list_numbers, int *odd_numbers, int nbr)
{
    list_numbers[0] = nbr + 1; //+ length
    odd_numbers[0] = nbr / 2;
    for (int i = 1, a = 1; i < nbr + 1; i++)
    {
        list_numbers[i] = i;
        if (i % 2 && i != 1)
        {
            odd_numbers[a] = i;
            a++;
        }
    }
}

void fillArrayOddNumbers(int *odd_numbers, int nbr)
{
    odd_numbers[0] = nbr / 2; // len
    for (int i = 1, a = 1; i < nbr + 1; i++)
    {
        if (i % 2 && i != 1)
        {
            odd_numbers[a] = i;
            a++;
        }
    }
}