#ifndef H_GL_CALCUL
#define H_GL_CALCUL

typedef struct COORD_cartesian
{
    double x;
    double y;
} COORD_cartesian;

typedef struct COORD_polar
{
    int r;
    double theta;
} COORD_polar;

COORD_cartesian polToCart(COORD_polar polarCoord);

#endif