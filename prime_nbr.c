#include "./headers/prime_nbr.h"

int testPrimeNumber(void)
{
    puts("Which number ? ");
    unsigned int nbr = askNumber();

    // fill array odd_numbers
    int *odd_numbers = (int *)malloc((nbr / 2) * sizeof(int));
    if (allocTestInt(odd_numbers, "odd_numbers"))
        return -1;
    fillArrayOddNumbers(odd_numbers, nbr);

    if (isPrimeNumber(nbr, odd_numbers) == 1)
    {
        printf("%d is a prime number.", nbr);
        return 1;
    }
    else
    {
        printf("%d is not a prime number", nbr);
        return 0;
    }
    free(odd_numbers);
    odd_numbers = NULL;
}

int *calculatePrimeNumbers(int *prime_numbers)
{
    puts("How many primary numbers would you like ?");
    unsigned int nbr = askNumber();
    printf("You enter : %d\n", nbr);

    int *list_numbers = (int *)malloc((nbr + 1) * sizeof(int));
    if (allocTestInt(list_numbers, "list_numbers"))
        return NULL;
    int *odd_numbers = (int *)malloc((nbr / 2) * sizeof(int));
    if (allocTestInt(odd_numbers, "odd_numbers"))
        return NULL;

    fillArray(list_numbers, odd_numbers, nbr);
    showArray(list_numbers);
    showArray(odd_numbers);

    printf("\n\n");
    prime_numbers = researchPrimeNumber(nbr, prime_numbers, list_numbers, odd_numbers);
    showArray(prime_numbers);

    free(list_numbers);
    list_numbers = NULL;
    free(odd_numbers);
    odd_numbers = NULL;
    return prime_numbers;
}

/*
 * researchPrimeNumber:
 *
 */
int *researchPrimeNumber(int nbr, int *prime_numbers, int *list_numbers, int *odd_numbers)
{
    unsigned int len = 1;
    for (int i = 1, j = 1; i < nbr + 1; i++)
    {
        // printf("%d is a prime number ?\n", list_number[i]);
        if (isPrimeNumber(list_numbers[i], odd_numbers) == 1)
        {
            // printf("%d is a prime number.\n", list_numbers[i]);
            prime_numbers = (int *)realloc(prime_numbers, (len + 1) * sizeof(int));
            if (allocTestInt(prime_numbers, "prime_numbers realloc"))
                return NULL;

            prime_numbers[j] = list_numbers[i];
            len++;
            j++;
        }
    }
    prime_numbers[0] = len; // final length
    return prime_numbers;
}

/*
 * isPrimeNumber:
 * detect if number is a prime number or not
 * definition :
 * number / 1
 * number / number
 */
Bool isPrimeNumber(int number, int *odd_numbers)
{
    int isImpair = number % 2; // detect if number is pair or not
    if (number == 1)
        return 0;
    if (isImpair == True)
    {
        // printf("%d is a impair number\n", number);
        for (int i = 1; i < arrlen(odd_numbers); i++)
        {
            if (number != odd_numbers[i])
            {
                // printf("verif\n");
                Bool isPrimary = number % odd_numbers[i];
                // printf("%d|%d \t %d = %d\n",i, number, odd_numbers[i], isPrimary);
                if (isPrimary == False)
                    return 0;
            }
        }
        return 1;
    }
    else
    {
        // printf("%d is a pair number\n", number);
        //for '2'
        int result = number / 2;
        if (result == 1)
            return 1;
        else
            return 0;
    }
}

/*
int main() {
    T_NOEUD * List, * Element;
    List = NULL;
    printf("-> Enregistrement d'utilisateur\n");
    //saisirUtilisateur(List);
    Element = creer_noeud();
    if (Element != NULL) {
        List = ins_tete(List, Element);
        Element = creer_noeud();
        List = ins_tete(List, Element);
        Element = creer_noeud();
        List = ins_tete(List, Element);
        aff_liste(List);
        aff_liste_mois_nais(List, 2);
        aff_liste_fete(List, 9, 19);
    }
    return 0;
}
*/

PrimeNumbers * create_node(void){
    PrimeNumbers * maillon;
    maillon = (PrimeNumbers*) malloc(sizeof(PrimeNumbers));
    if (maillon == NULL) {
      puts("Allocation error");
    } else {
       //saisir les informations
      
        //maillon->next;
    }
    return maillon;
}

/*
ND *nouveau(){
  ND * E;
  E = (ND*) malloc(sizeof(ND));
  if (E == NULL) {
    printf("Allocation impossible\n");
  } else {
    printf("Saisir un nom : ");
    scanf("%s", E->nom );
    E->suiv;
  }
  return E;
}
*/

PrimeNumbers *insert_node(PrimeNumbers *addr_list, PrimeNumbers *addr_node){

    //T_NOEUD * courant = T, * precedant = T;
    if (addr_list == NULL) addr_list = addr_node; //cas liste vide
    else {      // cas liste non vide
        addr_node->next = addr_list;
        addr_list = addr_node;
    }
    return addr_list;
}

int showPrimeNumbers(PrimeNumbers *addr_list){
    printf("aff_liste\n");
    int compteur = 0;
    printf("+-----------+-----------+--------+--------+\n");
    printf("|    Prenom |       Nom |  Anniv |   Fete |\n");
    printf("+-----------+-----------+--------+--------+\n");
    while (addr_list != NULL) {  //parcour la liste
      //printf("%d : %s\n", compteur+1, T->nom);
      //aff_noeud(addr_list);
      compteur++;
      addr_list = addr_list->next;
    }
    printf("+-----------+-----------+--------+--------+\n");
    if (compteur == 0) {
      printf("Liste vide !");
    }
    return compteur;
}

unsigned int length(PrimeNumbers *addr_list) {
   unsigned int length = 0;
   PrimeNumbers *current;
   for(current = addr_list; current != NULL; current = current->next)
      length++;
   return length;
}

/*
 nbr : le nombre à supprimer
*/
PrimeNumbers *delete_node(PrimeNumbers * addr_list, int *nbr){
  PrimeNumbers * current = addr_list, * precedant = addr_list;
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
      printf("%d supprimee\n", *nbr);
    } else {
      precedant = current;
      current = current->next;
    }
  }
  if (trouve == 0) printf("%d non trouve\n", *nbr);
  return addr_list;
}

/*
 * fileClear:
 * Tant que la file n'est pas vide.
 * On enlève l'élément courant.
 */
void fileClear(PrimeNumbers *addr_list_head){
	PrimeNumbers *current = addr_list_head;
    PrimeNumbers *next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    addr_list_head = NULL;
}