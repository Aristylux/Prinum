#ifndef H_GL_CALCUL
#define H_GL_CALCUL

typedef struct {
    double x;
    double y;
} COORD_cartesian;

typedef struct {
    int r;
    double teta;
} COORD_polar;

COORD_cartesian polToCart(COORD_polar polarCoord);

#endif