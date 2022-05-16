#include "./headers/prime_nbr.h"

Bool testPrimeNumber(unsigned int nbr)
{
    // fill array odd_numbers
    Bool isPrime;
    int *odd_numbers = (int *)malloc((nbr / 2) * sizeof(int));
    if (allocTestInt(odd_numbers, "odd_numbers"))
        return -1;
    fillArrayOddNumbers(odd_numbers, nbr);

    if (isPrimeNumber(nbr, odd_numbers) == 1)
        isPrime = True;
    else
        isPrime = False;
    free(odd_numbers);
    odd_numbers = NULL;
    return isPrime;
}

Q_PrimeNumbers * calculatePrimeNumbers(Q_PrimeNumbers *prime_numbers_queue){
    if(request_continue(prime_numbers_queue, 1, "A queue already exists, do you want to delete it ?") == False)
        return prime_numbers_queue;
    
    puts("Search for prime number up to what number ?");
    unsigned int nbr = askNumber();
    printf("You enter : %d\n", nbr);

    free_queue(prime_numbers_queue);
    puts("Init");
    int *list_numbers = (int *)malloc((nbr + 1) * sizeof(int));
    if (allocTestInt(list_numbers, "list_numbers"))
        return NULL;
    int *odd_numbers = (int *)malloc((nbr / 2) * sizeof(int));
    if (allocTestInt(odd_numbers, "odd_numbers"))
        return NULL;

    fillArray(list_numbers, odd_numbers, nbr);

    prime_numbers_queue = researchPrimeNumber(nbr, prime_numbers_queue, list_numbers, odd_numbers);
    puts("Finish.");
    free(list_numbers);
    list_numbers = NULL;
    free(odd_numbers);
    odd_numbers = NULL;
    return prime_numbers_queue;

}


void nPrimeNumbers(Q_PrimeNumbers *prime_numbers_queue){
    if(request_continue(prime_numbers_queue, 1, "A queue already exists, do you want to delete it ?") == False)
        return;
    puts("How many primary numbers would you like ?");
    unsigned int nbr = askNumber();
    printf("You enter : %d\n", nbr);

    free_queue(prime_numbers_queue);
    puts("Init");
    unsigned int current_nbr = 1, count = 1;
    while (count <= nbr)
    {
        printf("c : %d - \t n : %d\n", current_nbr, count);
        if(testPrimeNumber(current_nbr)){
            COORD_polar coordP = {current_nbr, current_nbr*10};
            COORD_cartesian coordC = polToCart(coordP);
            enQueue(prime_numbers_queue, current_nbr, coordC, coordP);
            count++;
        }
        current_nbr++;
    }
    puts("Finish.");
}

/*
 * researchPrimeNumber:
 *
 */
Q_PrimeNumbers * researchPrimeNumber(int nbr, Q_PrimeNumbers * prime_numbers_queue, int * list_numbers, int * odd_numbers){
    for (int i = 1; i < nbr + 1; i++)
    {
        if (isPrimeNumber(list_numbers[i], odd_numbers) == 1)
        {
            //Element = create_node(list_numbers[i]);
            //prime_number_list = insert_node(prime_number_list, Element);
            COORD_polar coordP = {list_numbers[i], list_numbers[i]*10};
            COORD_cartesian coordC = polToCart(coordP);
            enQueue(prime_numbers_queue, list_numbers[i], coordC, coordP);
        }
    }
    return prime_numbers_queue;
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
 * primeNumberCoord:
 * calcul and show coordonate for all points.
 * for prime numbers
 * /// not used ///
 */
void calculate_coordinate(Q_PrimeNumbers *queue){
    PrimeNumber *Element = queue->first;
    while (Element != NULL)
    {
        COORD_polar coordP = {Element->primeNumber, Element->primeNumber*10};
        COORD_cartesian coordC = polToCart(coordP);
        Element->coord_polar = coordP;
        Element->coord_cartesian = coordC;
        Element = Element->next;
    }
}

void show_coordinate(Q_PrimeNumbers *queue){
    PrimeNumber *Element = queue->first;
    if(request_continue(queue, 30, "The result is too large. show anyway?") == False)
        return;
    printf("\t/-------------+------------------+----------------------\\\n");
    printf("\t| Prime Nbr   |  ( r ,  θ )      |  ( x   ,   y )       |\n");
    printf("\t+-------------+------------------+----------------------+\n");
    while (Element != NULL)
    {
        printf("\t|%7d      | (%3d,\t%.2f)\t |  (%.2f,\t%.2f)\t|\n", Element->primeNumber, Element->coord_polar.r, Element->coord_polar.theta, Element->coord_cartesian.x, Element->coord_cartesian.y);
        Element = Element->next;
    }
    printf("\t\\-------------+------------------+----------------------/\n");
}

//------------ Queue ------------
void init_queue(Q_PrimeNumbers *queue){
    queue->first = NULL;
    queue->last = NULL;
}

void show_PN(Q_PrimeNumbers *queue){
    PrimeNumber *Element = queue->first;
    unsigned int count = 0, a = 1;
    const unsigned int colums = 10;
    if(request_continue(queue, 30, "The result is too large. show anyway?") == False)
        return;

    printf("\n\n");
    while (Element != NULL)
    {
        printf("%4d\t", Element->primeNumber);
        if (a == colums)
        {
            printf("\n");
            a = 0;
        }
        a++;
        count++;
        Element = Element->next;
    }
    if (count == 0)
        puts("Empty queue !");
    else 
        printf("\n\nNumbers : %d\n", count);
}

/* 
 * show_NPN:
 * show prime numbers with high light
 * with other numbers.
 */
void show_NPN(Q_PrimeNumbers *queue)
{
    PrimeNumber *Element = queue->first, *lastElement = last_element_queue(queue);
    const unsigned int colums = 10;
    unsigned int col_pos = 1, b = 1;
    int i = 1;
    if(length_queue(queue) == 0)
        return;


    unsigned int count = 0;
    while (Element != NULL)
    {
        count++;
    }
    if (count == 0)
    {
        puts_deb("Empty");
        return;
    }
    
// last_element_queue is error
    if(request_continue(queue, 20, "The result is too large. show anyway?") == False)
        return;
    printf("\n\n");
    while(1)
    {
        //printf("%s%d - %d%s\n", RED, i, Element->primeNumber, INIT);
        
        if (i == Element->primeNumber)
        {
            printf("%s%4d%s\t", RED, i, INIT);
            b++;
            if(Element->next != NULL)
                Element = Element->next;
        }
        else
            printf("%4d\t", i);
        if (col_pos == colums)
        {
            printf("\n");
            col_pos = 0;
            if (i >= lastElement->primeNumber)
                break;
        }
        col_pos++;
        i++;
    }
}

/*
 * enQueue:
 * return:
 * 0 if there is an error
 * 1 if the new element is in queue
 */
Bool enQueue(Q_PrimeNumbers *queue, int newPrimeNumber, COORD_cartesian coordC, COORD_polar coordP){
    PrimeNumber *Element = (PrimeNumber*) malloc(sizeof(PrimeNumber));
    if (Element == NULL)
    {
        puts("allocation error");
        return 0;
    } else {
        Element->primeNumber = newPrimeNumber;
        Element->coord_cartesian = coordC;
        Element->coord_polar = coordP;
        Element->next = NULL;
        if (length_queue(queue) == 0)   //Empty queue
            queue->first = Element;
        else    //not empty queue
            queue->last->next = Element;
        queue->last = Element;
        return 1;
    }
    
}

/*
 * deQueue:
 * Renvois:
 * the delete value "delPrimeNumber"
 * return:
 * 0 if empty queue
 * 1 if element is dequeue
 */
Bool deQueue(Q_PrimeNumbers *queue, int *delPrimeNumber){
    PrimeNumber *DelElement;
    if (length_queue(queue) == 0)
    {
        //puts("Empty queue");
        DelElement = NULL;
        return 0;
    }
    else {
        DelElement = queue->first;
        *delPrimeNumber = DelElement->primeNumber;
        queue->first = DelElement->next;
        if (queue->first == NULL)
            queue->last = NULL;
        free(DelElement);
        return 1;
    }
}

unsigned int length_queue(Q_PrimeNumbers *queue){
    PrimeNumber *Element = queue->first;
    unsigned int count = 0;
    while (Element != NULL)
    {
        count++;
        Element = Element->next;
    }
    return count;
}

PrimeNumber *last_element_queue(Q_PrimeNumbers *queue){
    PrimeNumber *Element = queue->first;
    unsigned int nbr = length_queue(queue);
    for (unsigned int i = 0; i < nbr-1; i++)
    {
        Element = Element->next;
    }
    //printf("last nbr : %d", Element->primeNumber);
    return Element;
}

/*
 * free_queue:
 * Tant que la file n'est pas vide.
 * On enlève l'élément courant.
 */
void free_queue(Q_PrimeNumbers *queue){
    int value;
    while(deQueue(queue, &value) == 1);
}

Bool request_continue(Q_PrimeNumbers *queue, unsigned int nbr, char* message){
    char *response = (char *)calloc(LEN_RESPONSE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return 0;

    Bool show = False;
    Bool error = True;

    if (length_queue(queue) > nbr)
    {
        printf("%s%s [Y/n]%s ", REVERSED, message , INIT);
        scan(response, LEN_RESPONSE);
        if (strcasecmp(response, "y") == 0 || strlen(response) == 0)
        {
            show = True;
            error = False;
        }
        if (strcmp(response, "n") == 0)
            error = False;
        if (error == True)
            puts("Abord.");
    }
    else
        show = True;
    free(response);
    response = NULL;
    return show;
}