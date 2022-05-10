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
    COORD_polar coord_polar = {3, 30};
    // coord_polar.r = 3;
    // coord_polar.teta = 30;
    COORD_cartesian coord_cart = polToCart(coord_polar);
    printf("polar cordinate : (%d,%f) -> cartesian cordiante : (%f,%f)\n", coord_polar.r, coord_polar.teta, coord_cart.x, coord_cart.y);

    Bool execute = True;
    Bool show_menu = True;

    char *response = (char *)calloc(LEN_RESPONSE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return EXIT_FAILURE;

    int *prime_numbers = (int *)malloc(sizeof(int));
    if (allocTestInt(prime_numbers, "prime_numbers"))
        return 1;

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
            prime_numbers = calculatePrimeNumbers(prime_numbers);
            break;
        case 2:
            puts("primary number mode 2");
            break;
        case 3:
            showArray(prime_numbers);
            break;
        case 4:
            //showArrayPrimeNumber(prime_numbers);
            break;
        case 5:
            //primeNumberCoord(prime_numbers);
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

    return EXIT_SUCCESS;
}