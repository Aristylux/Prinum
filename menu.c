#include "./headers/menu.h"

/*
 * showWelcome:
 * Display message welcome
 */
void showWelcome(void)
{
    puts("\n\n");
    printf(BOLD);
    printf(BLUE);
    puts("\t/--------------------\\");
    puts("\t|       Prinum       |");
    puts("\t|                    |");
    puts("\t|    prime number    |");
    puts("\t|     calculator     |");
    puts("\t| 2022 - version 2.1 |");
    puts("\t\\--------------------/");
    printf(INIT);
    puts("\n\n");
}

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
        showMenu(False);
        *show = False;
    }
    printf("\n\n > ");
    scan(response, LEN_RESPONSE);
}

/*
 * showMenu:
 * puts_deb : function in develpment
 * if isHelp == True
 * display help messages
 */
void showMenu(Bool isHelp)
{
    if (isHelp == True)
        puts_success("\tHelp : description menu");
    printf("\n\t(0)  Quitter");
    if (isHelp == True)
        puts_cl(":\n\t\t&oExit&/ program.");
    printf("\n\t(1)  Calculer jusqu'à n");
    if (isHelp == True)
        puts_cl(":\n\t\t&oCalculates&/ prime numbers up to given number : n.");
    printf("\n\t(2)  Calculer n nombres premiers");
    if (isHelp == True)
        puts_cl(":\n\t\t&oCalculate&/ the requested number &un&/ of prime number.");
    printf("\n\t(3)  Tester si un nombre est premier");
    if (isHelp == True)
        puts_cl(":\n\t\t&oChecks&/ whether a given number is &uprime or not&/");
    printf("\n\t(4)  Afficher les nombres premiers");
    if (isHelp == True)
        puts_cl(":\n\t\t&oDisplays&/ the list of prime numbers only");
    printf("\n\t(5)  Afficher les nombres premiers avec les nombres");
    if (isHelp == True)
        puts_cl(":\n\t\t&oDisplays&/ the list of prime numbers with other numbers");
    printf("\n\t(6)  Afficher avec les coordonees");
    if (isHelp == True)
        puts_cl(":\n\t\t&oDisplays&/ the coordinates of the points of the prime numbers");
    printf("\n\t(7)  Exporter la liste");
    if (isHelp == True)
        puts_cl(":\n\t\t&oExport&/ the list in format .pnba");
    printf("\n\t(8)  Enregistrer la liste");
    if(isHelp == True)
        puts_cl(":\n\t\t&oExport&/ the list in format .csv");
    printf("\n\t(9)  Importer une liste de nombre premier");
    if (isHelp == True)
        puts_cl(":\n\t\t&oImport&/ the list in format .pnba");
    printf("\n\t(10)  Afficher le graphique");
    if (isHelp == True)
        puts_cl(":\n\t\t&i&mFeature under development&/");
    printf("\n\t(11) Definition d'un nombre premier");
    if (isHelp == True)
        puts_cl(":\n\t\t&oDisplays&/ the definition of a prime number and example.");
    printf("\n\t(12) Aide");
    if (isHelp == True)
        puts_cl(":\n\t\t&oShow&/ help.");
}

/*
 * definition;
 * quesqu'un nombre premier
 */
void definition(void)
{
    puts_success("\tDefinition : prime numbers\n");
    puts_cl("\tA &inatural number&/ (1, 2, 3, 4, 5, 6, etc.) is called a &iprime number&/ (or a prime)");
    puts_cl("\tIf it is &ogreater than 1&/ and cannot be written as the product of two smaller natural numbers.");
    puts_cl("\n\tFor example :");
    puts_cl("\t5 is &oprime&/ because the only ways of writing it as a product,");
    puts_cl("\t1 × 5 or 5 × 1, involve 5 itself.");
    puts_cl("\tHowever, 4 is &ocomposite&/ because it is a product &o(2 × 2)&/");
    puts_cl("\tIn which both numbers are smaller than 4.");
    puts_cl("\nSource : https://en.wikipedia.org/wiki/Prime_number");
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
void clearBuffer(void)
{
    int lastCharater = 0;
    while (lastCharater != '\n' && lastCharater != '\0')
    {
        lastCharater = getchar();
    }
}

/*
 * askNumber:
 * demande un nombre à l'utilisateur
 * return :
 * le nombre
 */
int askNumber(void)
{
    // puts("How many primary numbers would you like ?");
    char *response = (char *)calloc(LEN_RESPONSE, sizeof(char));
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
int strToInt(char *string)
{
    int nombre = 0;
    const unsigned int nombresInt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const char nombresStr[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
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

/*
 * puts_deb:
 * affiche un message
 * avec "$message" en violet
 */
void puts_deb(char *message)
{
    printf(MAGENTA);
    printf("$%s\n", message);
    printf(INIT);
}

/*
 * puts_error:
 * affiche un message
 * avec "/!\ message" en rouge
 */
void puts_error(char *message)
{
    printf(BOLD);
    printf(RED);
    printf("/!\\ %s \n", message);
    printf(INIT);
}

/*
 * puts_success:
 * affiche un message
 * avec "message" en vert
 */
void puts_success(char *message)
{
    printf(BOLD);
    printf(GREEN);
    printf("%s\n", message);
    printf(INIT);
}

/*
 * puts_cl:
 *
 * &b -> blue
 * &r -> red
 * &y -> yellow
 * &g -> green
 * &m -> magenta
 *
 * &i -> italic
 * &u -> underline
 * &o -> bold
 * &l -> blink
 * &e -> reversed
 *
 * &/ -> reset
 * Example :
 * puts_cl("The company &b&iAlice & Co&/ is better than Eve & Co");
 */
void puts_cl(char *message)
{
    for (unsigned int i = 0; i < strlen(message); i++)
    {
        if (message[i] == '&')
        {
            i++;
            gestion_cl(message[i]);
        }
        else
            printf("%c", message[i]);
    }
    printf(INIT);
    printf("\n");
}

/*
 * gestion_cl:
 * modify carcateristics of display
 */
void gestion_cl(char motif)
{
    switch (motif)
    {
    case 'b':
        printf(BLUE);
        break;
    case 'r':
        printf(RED);
        break;
    case 'g':
        printf(GREEN);
        break;
    case 'y':
        printf(YELLOW);
        break;
    case 'm':
        printf(MAGENTA);
        break;
    case 'o':
        printf(BOLD);
        break;
    case 'i':
        printf(ITALIC);
        break;
    case 'u':
        printf(UNDERLINE);
        break;
    case 'l':
        printf(BLINK);
        break;
    case 'e':
        printf(REVERSED);
        break;
    case '/':
        printf(INIT);
        break;
    default:
        printf("& ");
        break;
    }
}