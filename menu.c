#include "./headers/menu.h"


/*
 * menu:
 * Affichage menu du jeu
 * et demande a l'ultilisateur
 *
 * show = 0 n'affiche pas les options
 * show = 1 affiche les options
 * renvoie une chaine de caractere
 */
void menu(Bool *show, char *response)
{
    if (*show == True)
    {
        // puts("\t(0) Jouer \t\t(1) Quitter");
        showMenu();
        *show = False;
    }
    printf("\n\n > ");
    scan(response, LEN_RESPONSE);
}

/*
 * showMenu:
 */
void showMenu(void)
{
    puts("\t(0) Quitter");
    puts("\t(1) Calculer jusqu'à n");
    puts("\t(2) Calculer n nombres premiers");
    puts("\t(3) Afficher les nombres premiers");
    puts("\t(4) Afficher les nombres premiers avec les nombres");
    puts("\t(5) Afficher coordonees");
    puts("\t(6) Enregistrer les resultat");
    puts("\t(7) Afficher le graphique");
    puts("\t(8) Tester si un nombre est primaire");
}


/*
 * scan:
 * remplace la fonction scanf() pour les chaines de caractères
 * supprime le retour chariot en fin de chaine. (en remplacant par \0)
 */
int scan(char *chaine, int length)
{
    char *positionEntree = NULL;
    if (fgets(chaine, length, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n'); // inclure string.h
        if (positionEntree != NULL)
            *positionEntree = '\0';
        else
            clearBuffer();
        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
    return 0;
}

/*
 * clearBuffer:
 * supprime les caractères qui se trouve dans stdin
 */
void clearBuffer(void) {
    int lastCharater = 0;
    while (lastCharater != '\n' && lastCharater != '\0')
    {
        lastCharater = getchar();
    }
}

// verification if nbr is not too high before calculation
int askNumber(void) {
    //puts("How many primary numbers would you like ?");
    char *response = (char *) calloc(LEN_RESPONSE, sizeof(char));
    if (allocTestChar(response, "var user number response"))
        return -1;
    Bool answer_correct = False;
    int nbr;
    while (answer_correct == False)
    {
        scan(response, LEN_RESPONSE);
        nbr = strToInt(response);
        if (nbr == -1)
            puts("enter only numbers.");
        else
            answer_correct = True;
    }
    free(response);
    response = NULL;
    return nbr;
}

/*
 * strToInt:
 * permet de convertir une chaine de caractere
 * contenant excusivement des nombres
 * en int
 * -> equivalent itoa();
 */
int strToInt(char *string) {
    int nombre = 0;
    const unsigned int nombresInt[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const char nombresStr[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    char *teststr = strpbrk(string, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (teststr == NULL && strlen(string) != 0)
    { // si il n'a pas trouvé de lettre
        invert(string);
        for (unsigned int i = 0; i < strlen(string); i++)
        {
            for (unsigned int j = 0; j < 10; j++)
            {
                if (string[i] == nombresStr[j])
                {
                    nombre += nombresInt[j] * power(10, i);
                }
            }
        }
    }
    else
    {
        nombre = -1; // si il y a une erreur (-1 donc impossible)
    }
    return nombre;
}

/*
 * invert:
 * inverse un tabeau de char
 * renvoie la chaine
 */
void invert(char *str)
{
    char buffer;
    for (int i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        buffer = str[i];
        str[i] = str[j];
        str[j] = buffer;
    }
}

/*
 * power:
 * fonction puissance
 * retourne le resultat
 */
int power(int nbr, int puiss)
{
    int pnbr = 1;
    for (int i = 0; i < puiss; i++)
    {
        pnbr = pnbr * nbr;
    }
    return pnbr;
}
