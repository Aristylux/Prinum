#ifndef _H_FILES_
#define _H_FILES_
#include "prime_nbr.h"
#include <dirent.h>

int saveData(Q_PrimeNumbers *prime_numbers_queue , const char filename[]);
int backUpData(Q_PrimeNumbers *prime_numbers_queue, const char filename[]);

int listFiles(void);
int fileExist(char * fileName);

#endif
