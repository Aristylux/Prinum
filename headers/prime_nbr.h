#ifndef _H_PRIME_NBR_
#define _H_PRIME_NBR_
#include <stdio.h>
#include <string.h>
#include "def.h"
#include "alloc.h"
#include "arr.h"
#include "calcul.h"
#include "menu.h"

// node :
typedef struct node
{
    int primeNumber;
    COORD_cartesian coord_cartesian;
    COORD_polar coord_polar;
    struct node *next;
} PrimeNumber;

// queue :
typedef struct
{
    struct node *first;
    struct node *last;
} Q_PrimeNumbers;

Bool testPrimeNumber(unsigned int nbr);
Q_PrimeNumbers *calculatePrimeNumbers(Q_PrimeNumbers *prime_numbers_queue);
Q_PrimeNumbers *researchPrimeNumber(int nbr, Q_PrimeNumbers *prime_number_queue, int *list_numbers, int *odd_numbers);
Bool isPrimeNumber(int number, int *odd_numbers);

void nPrimeNumbers(Q_PrimeNumbers *prime_numbers_queue);

void calculate_coordinate(Q_PrimeNumbers *queue);
void show_coordinate(Q_PrimeNumbers *queue);

// Queue
void init_queue(Q_PrimeNumbers *queue);
void show_PN(Q_PrimeNumbers *queue);
void show_NPN(Q_PrimeNumbers *queue);
Bool enQueue(Q_PrimeNumbers *queue, int newPrimeNumber, COORD_cartesian coordC, COORD_polar coordP);
Bool deQueue(Q_PrimeNumbers *queue, int *delPrimeNumber);
unsigned int length_queue(Q_PrimeNumbers *queue);
void free_queue(Q_PrimeNumbers *queue);

PrimeNumber *last_element_queue(Q_PrimeNumbers *queue);

Bool request_continue(Q_PrimeNumbers *queue, unsigned int nbr, char* message);

#endif
