#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


int traiter (int f, int *car, int *mot, int *lig){

	char buffer[80];
	int lus;

	

	lus = read(f,buffer,80);
	
	while(lus>0){
		(*car)++;
			
		if(isspace(buffer[lus]) != 0){
			 (*mot)++;
			 if(buffer[lus] == '\n')
				(*lig)++;
             }
			
			lus--;
			if(lus == 0){
				lus = read(f,buffer,80);			
			}
		}

	
	if(lus == -1){
		perror("Erreur lecture");
		return 1;
	}

	return 0;	
}
