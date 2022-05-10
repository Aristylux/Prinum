#ifndef _H_MENU_
#define _H_MENU_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "alloc.h"

/*your declaration here */

void menu(Bool *show, char *response);
void showMenu(void);

//user demands
int scan(char *chaine, int length);
void clearBuffer(void);

int askNumber(void);

// conversion
int strToInt(char *string);
void invert(char *str);
int power(int nbr, int puiss);

void puts_deb(char *message);

#endif
