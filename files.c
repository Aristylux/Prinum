#include "./headers/files.h"

//----------- FILES Menu -----------

/* ---------- NOT USED -------------
 * exportFile:
 * demand the name of the file
 * create and format path
 * return :
 * -1 if error
 *  1 if no data
 *  0 success
 */
int exportFile(Q_PrimeNumbers *prime_numbers_queue)
{
    if (length_queue(prime_numbers_queue) == 0)
    {
        puts("queue empty : no data...");
        return 1;
    }

    char *response = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return -1;

    char *path = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(path, "var user path"))
        return -1;

    while (1)
    {
        printf("file name : ");
        scan(response, LEN_FILE);
        formatingFileName(response, ".pnba");
        if (fileExist("./data", response))
            puts("The name of the file is already exist. chose another one.");
        else
        {
            printf("final file name : %s\n", response);
            if (request_continue(prime_numbers_queue, 0, "do you validate the name of the file?") == True)
                break;
        }
    }
    formatingPath(response, NAME_DIRECTORY_DATA, path);
    printf("path : %s\n", path);
    saveDataBinary(prime_numbers_queue, path);

    free(path);
    path = NULL;
    free(response);
    response = NULL;
    return 0;
}

/*
 * demandFileName:
 * demande the name of the file
 * return:
 * response
 */
char *demandFileName(Q_PrimeNumbers *prime_numbers_queue, char *response, Bool mode, char *directory_name)
{
    char *directory;
    while (1)
    {
        printf("file name : ");
        scan(response, LEN_FILE);
        if (mode == CSV)
        {
            formatingFileName(response, ".csv");
            directory = DIRECTORY_EXPORT;
            directory_name = NAME_DIRECTORY_EXPORT;
        }
        else
        {
            formatingFileName(response, ".pnba");
            directory = DIRECTORY_DATA;
            directory_name = NAME_DIRECTORY_DATA;
        }

        if (fileExist(directory, response))
            puts("The name of the file is already exist. chose another one.");
        else
        {
            printf("final file name : %s\n", response);
            if (request_continue(prime_numbers_queue, 0, "do you validate the name of the file?") == True)
                break;
        }
    }
    return directory_name;
}

/*
 * saveFile:
 * demand the name of the file
 * create and format path
 * return:
 * -1 if error
 *  1 if no data
 *  0 success
 */
int saveFile(Q_PrimeNumbers *prime_numbers_queue, Bool mode)
{
    if (length_queue(prime_numbers_queue) == 0)
    {
        puts("queue empty : no data...");
        return 1;
    }

    directoryExist(NAME_DIRECTORY_EXPORT);
    directoryExist(NAME_DIRECTORY_DATA);

    char *response = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return -1;

    char *path = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(path, "var user path"))
        return -1;

    char *directory_name = NULL;
    directory_name = demandFileName(prime_numbers_queue, response, mode, directory_name);
    formatingPath(response, directory_name, path);
    printf("path : %s\n", path);
    if(mode == CSV)
        saveData(prime_numbers_queue, path);
    else
        saveDataBinary(prime_numbers_queue, path);

    free(path);
    path = NULL;
    free(response);
    response = NULL;
    return 0;
}

/*
 * openFile:
 *
 * return:
 * prime_numbers_queue
 */
int openFile(Q_PrimeNumbers *prime_numbers_queue)
{
    if (request_continue(prime_numbers_queue, 1, "A queue already exists, do you want to delete it ?") == False)
        return 1;
    free_queue(prime_numbers_queue);

    printf("files : \n\n");
    puts("\tSelect file with his name or identification number.\n");
    if (listFiles("./data") == 0)
    {
        puts("0 files");
        return 1;
    }

    char *response = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(response, "var user response"))
        return -1;
    char *path = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(path, "var user path"))
        return -1;

    puts("\tCall \"exit\" for cancel.\n");
    while (1)
    {
        printf("Select File : ");
        scan(response, LEN_FILE);
        if (strcmp(response, "exit") == 0)
            break;

        int item = strToInt(response);
        if (item != -1 && countFiles("./data") >= item)
            extractFileName("./data", item, response); // extract file name n°
        else
            formatingFileName(response, ".pnba");
        if (fileExist("./data", response))
        {
            formatingPath(response, NAME_DIRECTORY_DATA, path);
            readDataBinary(prime_numbers_queue, path);
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

//----------- FILES Read/Write -----------

/*
 * saveData:
 * save in file named "xxx.csv"
 * this file is in "export" directory
 * return:
 * 1 if error
 * 0 if success
 */
int saveData(Q_PrimeNumbers *prime_numbers_queue, const char *path)
{

    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        puts_error("MESSAGE_ERREUR_FICHER");
        return 1;
    }

    PrimeNumber *E = prime_numbers_queue->first;
    fprintf(file, "prime number;x;y;r;theta\n");
    while (E != NULL)
    {
        fprintf(file, "%d;%d;%lf;%lf;%lf\n", E->primeNumber, E->coord_polar.r, E->coord_polar.theta, E->coord_cartesian.x, E->coord_cartesian.y);
        E = E->next;
    }
    fclose(file);
    return 0;
}

/*
 * saveDataBinary:
 * save in file named "xxx.pnba"
 * this file is in "data" directory
 * return:
 * 1 if error
 * 0 if success
 */
int saveDataBinary(Q_PrimeNumbers *prime_numbers_queue, const char fileName[])
{
    printf("Création du fichier %s\n", fileName);
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        puts_error("MESSAGE_ERREUR_FICHER");
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

/*
 * readDataBinary:
 * read file in "data" directory
 * return:
 * 1 if error
 * 0 if success
 */
int readDataBinary(Q_PrimeNumbers *prime_numbers_queue, const char fileName[])
{
    printf("Lecture du fichier %s\n", fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        puts_error("MESSAGE_ERREUR_FICHER");
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

//----------- FILES Gestion -----------

/*
 * listFiles:
 * open directory and read files
 * return :
 * number of file in directory
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
        if (dir->d_type == 8) // file -> 8 / directory -> 4
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
 * countFiles:
 * open directory and read
 * return :
 * number of file in directory
 */
int countFiles(char *path)
{
    unsigned int count = 0;
    struct dirent *dir;
    DIR *directory = opendir(path);
    if (directory == NULL)
        return -1;

    while ((dir = readdir(directory)) != NULL)
        if (dir->d_type == 8) // file -> 8 / directory -> 4
            count++;
    if (closedir(directory))
        return -1;
    return count;
}

/*
 * extractFileName:
 *
 * return:
 * filename
 * return:
 * -1 if error
 *  0 if file doesn't
 *  1 if file exist
 */
int extractFileName(char *path, unsigned int item, char *fileName)
{
    unsigned int count = 0;
    struct dirent *dir;
    DIR *directory = opendir(path);
    if (directory == NULL)
        return -1;

    while ((dir = readdir(directory)) != NULL)
    {
        if (dir->d_type == 8) // file -> 8 / directory -> 4
        {
            if (count == item)
            {
                strcpy(fileName, dir->d_name);
                closedir(directory);
                return 1;
            }
            count++;
        }
    }
    if (closedir(directory))
        return -1;
    return 0;
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

/*
 * directoryExist:
 * check if "directory" exist
 * create it if doesn't exist
 */
void directoryExist(char *directory)
{
    char *command = (char *)calloc(LEN_FILE, sizeof(char));
    if (allocTestChar(command, "var command"))
        return;

    if (fileExist(".", directory) == False)
    {
        strcpy(command, "mkdir ");
        strcat(command, directory);
        printf("directory \"%s\" doesn't exist\n", directory);
        system(command);
        puts("directory created");
    }
    free(command);
    command = NULL;
}

//------------------

/*
 * formatingPath:
 * path = "directory"/"fileName.extension"
 * return:
 * path
 */
void formatingPath(char *fileName, char *directory, char *path)
{
    strcpy(path, directory);
    strcat(path, "/");
    strcat(path, fileName);
}

/*
 * formatingFileName:
 * delete all space
 * add extension
 * return:
 * fileName
 */
void formatingFileName(char *fileName, char *extension)
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
        fileNameBuffer[a] = fileName[i];
        a++;
    }

    strcat(fileNameBuffer, extension);
    strcpy(fileName, fileNameBuffer);
    free(fileNameBuffer);
    fileNameBuffer = NULL;
}
