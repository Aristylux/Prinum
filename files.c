#include "./headers/files.h"

int saveData(Q_PrimeNumbers * F, const char fileName[]){
	printf("Création du fichier %s\n", fileName);
	FILE *file = fopen(fileName, "w");
	if(file == NULL){
		puts("MESSAGE_ERREUR_FICHER");
		return 1;
	}
	PrimeNumber *E = F->first;
	//fwrite(&F->lastSync, sizeof(time_t), 1, file);
	while (E != NULL) {
		fwrite(E,sizeof(PrimeNumber),1, file);
		E = E->next;
	}
	fclose(file);
	return 0;
}

int backUpData(Q_PrimeNumbers * prime_numbers_queue, const char fileName[]){
	printf("Lecture du fichier %s\n", fileName);
	FILE *file = fopen(fileName, "r");
	if(file == NULL){
		puts("MESSAGE_ERREUR_FICHER");
		return 1;
	}
	PrimeNumber E;
	//fread(&E, sizeof(time_t), 1, file);
	//F->date =
	while(fread(&E,sizeof(PrimeNumber),1,file)){	//tableau
		//addMessage(F, E.message, E.date);
        COORD_polar coordP = {E.coord_polar.r, E.coord_polar.theta};
        COORD_cartesian coordC = {E.coord_cartesian.x, E.coord_cartesian.y};
        enQueue(prime_numbers_queue, E.primeNumber, coordC, coordP);
	}

	fclose(file);
	return 0;
}


int listFiles(void){
    struct dirent *dir;
    DIR *directory = opendir(".");
    if (directory == NULL)
        return 1;

    while ((dir = readdir(directory)) != NULL)
    {
        printf("%s\n", dir->d_name);
    }
    closedir(directory);

    return 0;    
}


/*
 * fileExist:
 * return :
 * 1 if error
 * 2 if file or directory exist
 * 3 if doesn't exist
 */
int fileExist(char * fileName){
    struct dirent *dir;
    DIR *directory = opendir(".");
    if (directory == NULL)
        return 1; //error

    while ((dir = readdir(directory)) != NULL)
    {
        if (strcmp(fileName, dir->d_name) == 0)
        {
            puts("file exist");
            return 2;
        }
        
    }
    closedir(directory);
    puts("file doesn't exist");
    return 3;
}
