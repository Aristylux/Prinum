#include "linked_list.h"

PrimeNumber * create_node(int nbr){
    PrimeNumber * maillon;
    maillon = (PrimeNumber*) malloc(sizeof(PrimeNumber));
    if (maillon == NULL) {
      puts("Allocation error");
    } else {
        //saisir les informations
        maillon->primeNumber = nbr;
        maillon->next = NULL;
    }
    return maillon;
}

PrimeNumber *insert_node(PrimeNumber *addr_list, PrimeNumber *addr_node){

    //T_NOEUD * courant = T, * precedant = T;
    if (addr_list == NULL) addr_list = addr_node; //cas liste vide
    else {      // cas liste non vide
        addr_node->next = addr_list;
        addr_list = addr_node;
    }
    return addr_list;
}

unsigned int print_linked_list(PrimeNumber *addr_list){
    printf("aff_liste\n");
    unsigned int length = 0;
    printf("+-----------+-----------+--------+--------+\n");
    printf("|    Prime numbers |\n");
    printf("+-----------+-----------+--------+--------+\n");
    while (addr_list != NULL) {  //parcour la liste
      //printf("%d : %s\n", compteur+1, T->nom);
      print_node(addr_list);
      length++;
      addr_list = addr_list->next;
    }
    if (length == 0) {
      printf("Liste vide !\n");
    }
    printf("+-----------+-----------+--------+--------+\n");
    return length;
}

void print_node(PrimeNumber *addr_node){
    printf("%4d\n", addr_node->primeNumber);
}

unsigned int length_node(PrimeNumber *addr_list) {
   unsigned int length = 0;
   PrimeNumber *current;
   for(current = addr_list; current != NULL; current = current->next)
      length++;
   return length;
}

/*
 nbr : le nombre à supprimer
*/
PrimeNumber *delete_node(PrimeNumber * addr_list, int *nbr){
  PrimeNumber * current = addr_list, * precedant = addr_list;
  int trouve = 0;
  while (current != NULL) {   //parcour la liste
    //if (strcmp(current->nom, qui) == 0) {
    if (current->primeNumber == *nbr){
      trouve = 1;
      if (current == addr_list) addr_list = current->next;
      else precedant->next = current->next;
      if (current != NULL) {
        free(current);
        current = NULL;
      }
      printf("%d deleted\n", *nbr);
    } else {
      precedant = current;
      current = current->next;
    }
  }
  if (trouve == 0) printf("%d not found\n", *nbr);
  return addr_list;
}

/*
 * fileClear:
 * Tant que la file n'est pas vide.
 * On enlève l'élément courant.
 */
void free_list(PrimeNumber *addr_list_head){
	PrimeNumber *current = addr_list_head;
    PrimeNumber *next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    addr_list_head = NULL;
}