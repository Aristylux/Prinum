#ifndef _H_FILES_
#define _H_FILES_
#include "prime_nbr.h"
#include <dirent.h>

#define NAME_DIRECTORY_DATA "data"
#define DIRECTORY_DATA "./" NAME_DIRECTORY_DATA

#define NAME_DIRECTORY_EXPORT "export"
#define DIRECTORY_EXPORT "./" NAME_DIRECTORY_EXPORT

#define PNBA 0
#define CSV 1

int saveDataBinary(Q_PrimeNumbers * prime_numbers_queue, const char fileName[]);
int readDataBinary(Q_PrimeNumbers *prime_numbers_queue, const char filename[]);

int listFiles(char *path);
int countFiles(char *path);
int extractFileName(char *path, unsigned int item, char *fileName);
int fileExist(char * path, char * fileName);

void directoryExist(char *directory);
int exportFile(Q_PrimeNumbers * prime_numbers_queue);
int saveFile(Q_PrimeNumbers *prime_numbers_queue, Bool mode);
void formatingFileName(char *fileName, char *extension);
void formatingPath(char *fileName, char *directory, char *path);

int openFile(Q_PrimeNumbers * prime_numbers_queue);

#endif
