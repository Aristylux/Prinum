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

int main(void)
{
    Hello();
    COORD_polar coord_polar = {3, 3*10};
    // coord_polar.r = 3;
    // coord_polar.teta = 30;
    COORD_cartesian coord_cart = polToCart(coord_polar);
    printf("polar cordinate : (%d,%f) -> cartesian cordiante : (%f,%f)\n", coord_polar.r, coord_polar.theta, coord_cart.x, coord_cart.y);

    Q_PrimeNumbers QueuePrimeNumbers;
    init_queue(&QueuePrimeNumbers);

    Bool execute = True;
    Bool show_menu = True;

    char *response = (char *)calloc(LEN_RESPONSE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return EXIT_FAILURE;

    char *fileName = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(fileName, "var user response"))
        return-1;

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
            calculatePrimeNumbers(&QueuePrimeNumbers);
            break;
        case 2:
            nPrimeNumbers(&QueuePrimeNumbers);
            break;
        case 3:
            show_PN(&QueuePrimeNumbers);
            break;
        case 4:
            show_NPN(&QueuePrimeNumbers);
            break;
        case 5:
            show_coordinate(&QueuePrimeNumbers);
            break;
        case 6:
            puts("export data");
            saveFile(&QueuePrimeNumbers);
            break;
        case 7:
            openFile(&QueuePrimeNumbers);
            break;
        case 8:
            puts("open graph");
            break;
        case 9:
            puts("Which number ? ");
            unsigned int nbr = askNumber();
            if(testPrimeNumber(nbr))
                printf("%d is a prime number.", nbr);
            else
                printf("%d is not a prime number", nbr);

            break;
        case 10:
            //system("ls");
            listFiles(".");
            printf("\n\n\n");
            listFiles("./data");
            //directoryExist();
            break;
        case 11:
            if(fileExist("data","fr.pnba"))
                puts_deb("exist");
            else
                puts_deb("doesn't exist");
            break;
        case 12:
            //quesqu'un nombre premier
            
            strcpy(fileName, "bonj our.fr");
            formatingFileName(fileName);
            printf(" : %s\n", fileName);
            free(fileName);
            fileName = NULL;
            break;
        default:
            puts("Incorrect command");
            show_menu = True;
            break;
        }
    }

    free_queue(&QueuePrimeNumbers);
    free(response);
    response = NULL;
    return EXIT_SUCCESS;
}