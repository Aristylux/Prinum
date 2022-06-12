#include <stdio.h>
#include <stdlib.h>
#include "./headers/hello.h"
#include "./headers/calcul.h"
#include "./headers/def.h"
#include "./headers/alloc.h"
#include "./headers/menu.h"
#include "./headers/prime_nbr.h"
#include "./headers/arr.h"
#include "./headers/files.h"
#include "./headers/graph.h"

/*
valgrind --leak-check=full ./prog 
*/

int main(void)
{
    showWelcome();
    Q_PrimeNumbers QueuePrimeNumbers;
    init_queue(&QueuePrimeNumbers);

    Bool execute = True;
    Bool show_menu = True;

    char *response = (char *)calloc(LEN_RESPONSE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return EXIT_FAILURE;

    while (execute)
    {
        menu(&show_menu, response);
        int choice = strToInt(response);
        switch (choice)
        {
        case 0:
            execute = False;
            break;
        case 1:
            PN_calc_until(&QueuePrimeNumbers);
            break;
        case 2:
            PN_calc_nPN(&QueuePrimeNumbers);
            break;
        case 3:
            PN_calc_test();
            break;
        case 4:
            PN_show(&QueuePrimeNumbers);
            break;
        case 5:
            PN_show_numbers(&QueuePrimeNumbers);
            break;
        case 6:
            PN_show_coordinate(&QueuePrimeNumbers);
            break;
        case 7:
            saveFile(&QueuePrimeNumbers, PNBA);
            break;
        case 8:
            saveFile(&QueuePrimeNumbers, CSV);
            break;
        case 9:
            openFile(&QueuePrimeNumbers);
            break;
        case 10:
            openGraph(&QueuePrimeNumbers);
            break;
        case 11:
            free_queue(&QueuePrimeNumbers);
            puts("Queue is clear.");
            break;
        case 12:
            definition();
            break;
        case 13:
            showMenu(True);
            break;
        default:
            puts("Incorrect command");
            show_menu = True;
            break;
        }
    }
    puts("Liberation des elements alloués");
    free_queue(&QueuePrimeNumbers);
    free(response);
    response = NULL;
    return EXIT_SUCCESS;
}