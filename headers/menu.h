#ifndef _H_MENU_
#define _H_MENU_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "alloc.h"

void menu(Bool *show, char *response);
void showWelcome(void);
void showMenu(Bool isHelp);
void definition(void);

//user demands
int scan(char *chaine, int length);
void clearBuffer(void);

int askNumber(void);

// conversion
int chrToInt(char chr);
int strToInt(char *string);
void invert(char *str);
int power(int nbr, int puiss);

//information
void puts_deb(char *message);
void puts_error(char *message);
void puts_success(char *message);
void puts_cl(char *message);

void gestion_cl(char motif);

#endif
