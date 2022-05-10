#ifndef _H_PRIME_NBR_
#define _H_PRIME_NBR_
#include <stdio.h>
#include "def.h"
#include "alloc.h"
#include "arr.h"
#include "calcul.h"
#include "menu.h"

typedef struct noeud
{
    int primeNumber;
    struct COORD_cartesian *coord_cartesian;
    struct COORD_polar *coord_polar;
    struct noeud *next;
} PrimeNumbers;

int testPrimeNumber(void);
int *calculatePrimeNumbers(int *prime_numbers);
int *researchPrimeNumber(int nbr, int *prime_numbers, int *list_numbers, int *odd_numbers);
Bool isPrimeNumber(int number, int *odd_numbers);

// linked list
PrimeNumbers *create_node(void);
PrimeNumbers *insert_node(PrimeNumbers *addr_list, PrimeNumbers *addr_node);
int showPrimeNumbers(PrimeNumbers *addr_list);
unsigned int length(PrimeNumbers *addr_list);
PrimeNumbers *delete_node(PrimeNumbers *addr_list, int *nbr);
void free_list(PrimeNumbers *addr_list_head);

#endif
