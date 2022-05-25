#ifndef _H_ARR_
#define _H_ARR_
#include <stdio.h>

#define COLUMNS 10

unsigned int arrlen(int *array);
void showArray(int *array);
void fillArray(int *list_numbers, int *odd_numbers, int nbr);
void fillArrayOddNumbers(int *odd_numbers, int nbr);

double maxArray(double tab[], const unsigned int size);
void showArrayD(double tab[], const unsigned int size);

#endif
