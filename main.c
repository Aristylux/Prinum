#include <stdio.h>
#include <stdlib.h>
#include "./headers/hello.h"
#include "./headers/calcul.h"
#include "./headers/def.h"
#include "./headers/alloc.h"
#include "./headers/menu.h"
#include "./headers/prime_nbr.h"
#include "./headers/arr.h"

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
            puts("primary number mode 1");
            calculatePrimeNumbers(&QueuePrimeNumbers);
            break;
        case 2:
            puts("primary number mode 2");
            //until n primary numbers
            break;
        case 3:
            show_PN(&QueuePrimeNumbers);
            break;
        case 4:
            show_NPN(&QueuePrimeNumbers);
            break;
        case 5:
            calculate_coordinate(&QueuePrimeNumbers);
            show_coordinate(&QueuePrimeNumbers);
            break;
        case 6:
            puts("save data");
            break;
        case 7:
            puts("open graph");
            break;
        case 8:
            testPrimeNumber();
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