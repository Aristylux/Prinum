#ifndef _H_FILES_
#define _H_FILES_
#include "prime_nbr.h"
#include <dirent.h>

#define DIRECTORY_DATA "data"

int saveData(Q_PrimeNumbers * prime_numbers_queue, const char fileName[]);
int backUpData(Q_PrimeNumbers *prime_numbers_queue, const char filename[]);

int listFiles(char *path);
int fileExist(char * path, char * fileName);

void directoryExist(void);
int saveFile(Q_PrimeNumbers * prime_numbers_queue);
void formatingFileName(char *fileName);
void formatingPath(char *fileName, char *path);

int openFile(Q_PrimeNumbers * prime_numbers_queue);

#endif
