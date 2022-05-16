#include "./headers/files.h"

int saveData(Q_PrimeNumbers *prime_numbers_queue, const char fileName[])
{
    printf("Création du fichier %s\n", fileName);
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        puts("MESSAGE_ERREUR_FICHER");
        return 1;
    }
    PrimeNumber *E = prime_numbers_queue->first;
    while (E != NULL)
    {
        fwrite(E, sizeof(PrimeNumber), 1, file);
        E = E->next;
    }
    fclose(file);
    return 0;
}

int backUpData(Q_PrimeNumbers *prime_numbers_queue, const char fileName[])
{
    printf("Lecture du fichier %s\n", fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        puts("MESSAGE_ERREUR_FICHER");
        return 1;
    }
    PrimeNumber E;
    while (fread(&E, sizeof(PrimeNumber), 1, file))
    { // tableau
        COORD_polar coordP = {E.coord_polar.r, E.coord_polar.theta};
        COORD_cartesian coordC = {E.coord_cartesian.x, E.coord_cartesian.y};
        enQueue(prime_numbers_queue, E.primeNumber, coordC, coordP);
    }

    fclose(file);
    return 0;
}

/*
 * listFiles:
 *
 */
int listFiles(char *path)
{
    unsigned int count = 0;
    struct dirent *dir;
    DIR *directory = opendir(path);
    if (directory == NULL)
        return -1;

    while ((dir = readdir(directory)) != NULL)
    {
        if (dir->d_type == 8)   // file -> 8 / directory -> 4
        { 
            printf("\t%d - %s%s%s\n", count, BLUE, dir->d_name, INIT);
            count++;
        }
    }
    if (closedir(directory))
    {
        puts_error("can't close directory");
        return -1;
    }
    return count;
}

/*
 * fileExist:
 * return :
 * -1 if error
 * 1 if file or directory exist
 * 0 if doesn't exist
 */
int fileExist(char *path, char *fileName)
{
    Bool exist = False;
    struct dirent *dir;
    DIR *directory = opendir(path);
    if (directory == NULL)
        return -1; // error

    while ((dir = readdir(directory)) != NULL)
    {
        if (strcmp(fileName, dir->d_name) == 0)
            exist = True;
    }
    if (closedir(directory))
    {
        puts_error("can't close directory");
        return -1;
    }
    return exist;
}

void directoryExist(void)
{
    if (fileExist(".", DIRECTORY_DATA) == False)
    {
        printf("directory \"%s\" doesn't exist\n", DIRECTORY_DATA);
        system("mkdir data");
    }
}

int saveFile(Q_PrimeNumbers *prime_numbers_queue)
{
    directoryExist();
    char *response = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return -1;

    char *path = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(path, "var user path"))
        return -1;

    if(length_queue(prime_numbers_queue) == 0){
        puts("queue empty : no data...");
        return 1;
    }

    while(1){
        printf("file name : ");
        scan(response, LEN_FILE);
        formatingFileName(response);
        if(fileExist("./data", response))
            puts("The name of the file is already exist. chose another one.");
        else{
            printf("final file name : %s\n", response);
            if(request_continue(prime_numbers_queue, 0, "do you validate the name of the file?") == True)
                break;
        }
    }
    formatingPath(response, path);
    printf("path : %s\n", path);
    saveData(prime_numbers_queue, path);

    free(path);
    path = NULL;
    free(response);
    response = NULL;
    return 0;
}

// delete all space
// if detect space
void formatingFileName(char *fileName)
{
    char *fileNameBuffer = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(fileNameBuffer, "var user response"))
        return;

    unsigned int a = 0;
    for (unsigned int i = 0; i < strlen(fileName); i++)
    {
        if (fileName[i] == ' ')
            i++;
        if (fileName[i] == '.')
            break;
        //printf("\t%c\n", fileName[i]);
        fileNameBuffer[a] = fileName[i];
        a++;
    }

    strcat(fileNameBuffer, ".pnba");
    strcpy(fileName, fileNameBuffer);
    free(fileNameBuffer);
    fileNameBuffer = NULL;
}

void formatingPath(char *fileName, char *path)
{
    strcpy(path, DIRECTORY_DATA);
    strcat(path, "/");
    strcat(path, fileName);
}

int openFile(Q_PrimeNumbers *prime_numbers_queue)
{
    char *response = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return -1;
    char *path = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(path, "var user path"))
        return -1;

    printf("files : \n\n");
    if (listFiles("./data") == 0)
    {
        puts("0 files");
        return 1;
    }

    puts("\tcall \"exit\" for cancel.\n");
    while (1)
    {
        printf("Select File : ");
        scan(response, LEN_FILE);
        if (strcmp(response, "exit") == 0)
            break;
        formatingFileName(response);
        if (fileExist("./data", response))
        {
            formatingPath(response, path);
            backUpData(prime_numbers_queue, path);
            puts_success("Data imported");
            break;
        }
        else
            printf("%sthe file : \"%s\" doesn't exist.%s\n", RED, response, INIT);
    }

    free(path);
    path = NULL;
    free(response);
    response = NULL;
    return 0;
}