#ifndef _H_LINKED_LIST_
#define _H_LINKED_LIST_
#include <string.h>

// node :
typedef struct node
{
    int primeNumber;
    struct COORD_cartesian *coord_cartesian;
    struct COORD_polar *coord_polar;
    struct node *next;
} PrimeNumber;

// linked list
PrimeNumber *create_node(int nbr);
PrimeNumber *insert_node(PrimeNumber *addr_list, PrimeNumber *addr_node);
unsigned int print_linked_list(PrimeNumber *addr_list);
void print_node(PrimeNumber *addr_node);
unsigned int length_node(PrimeNumber *addr_list);
PrimeNumber *delete_node(PrimeNumber *addr_list, int *nbr);
void free_list(PrimeNumber *addr_list_head);

#endif
