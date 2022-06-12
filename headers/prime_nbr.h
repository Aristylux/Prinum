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

void PN_calc_test(void);

Bool testPrimeNumber(unsigned int nbr);
Q_PrimeNumbers *PN_calc_until(Q_PrimeNumbers *prime_numbers_queue);
Q_PrimeNumbers *researchPrimeNumber(int nbr, Q_PrimeNumbers *prime_number_queue, int *list_numbers, int *odd_numbers);
Bool isPrimeNumber(int number, int *odd_numbers);

void PN_calc_nPN(Q_PrimeNumbers *prime_numbers_queue);

void calculate_coordinate(Q_PrimeNumbers *queue);
void PN_show_coordinate(Q_PrimeNumbers *queue);

// Queue
void init_queue(Q_PrimeNumbers *queue);
void PN_show(Q_PrimeNumbers *queue);
void PN_show_numbers(Q_PrimeNumbers *queue);
Bool enQueue(Q_PrimeNumbers *queue, int newPrimeNumber, COORD_cartesian coordC, COORD_polar coordP);
Bool deQueue(Q_PrimeNumbers *queue, int *delPrimeNumber);
unsigned int length_queue(Q_PrimeNumbers *queue);
void free_queue(Q_PrimeNumbers *queue);

PrimeNumber *last_element_queue(Q_PrimeNumbers *queue);

Bool request_continue(Q_PrimeNumbers *queue, unsigned int nbr, char *message);

unsigned int refresh(unsigned int max, unsigned int value, unsigned int progress);

#endif
