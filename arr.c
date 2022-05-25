#include "./headers/arr.h"

/*
 * arrlen:
 * return the length of array
 */
unsigned int arrlen(int *array)
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
    // int colums = 10;
    //  printf("\nsize of array : %d - %d\n", array[0], array[0] - 1);
    printf("\nsize of array : %d\n", array[0]);
    printf("\n\n");
    for (unsigned int i = 1, a = 1; i < arrlen(array); i++)
    {
        printf("%4d\t", array[i]);
        if (a == COLUMNS)
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
 * -> 1.2.3.4....nbr
 * -> 1.3.5.7....nbr
 * return:
 * list_numbers / odd_numbers
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

/*
 * fillArrayOddNumbers:
 * fill array
 * -> 1.3.5.7....nbr
 * return:
 * odd_numbers
 */
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

double maxArray(double tab[], const unsigned int size)
{
    for (unsigned int i = 1; i < size; ++i)
        if (tab[0] < tab[i])
            tab[0] = tab[i];
    return tab[0];
}

void showArrayD(double tab[], const unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
        printf("%lf\n", tab[i]);
}