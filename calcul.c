#include "./headers/calcul.h"
#include <math.h>

/*
 * polToCart:
 * calculate polar coordonate to cartesian
 */
COORD_cartesian polToCart(COORD_polar polarCoord)
{
    COORD_cartesian cartCoord;
    cartCoord.x = polarCoord.r * cos(polarCoord.teta);
    cartCoord.y = polarCoord.r * sin(polarCoord.teta);
    return cartCoord;
}
