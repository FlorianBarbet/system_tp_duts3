#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * miroir(const char *s){
	
	
	char saveChar[strlen(s)];
	char * resultat = (char * )malloc(strlen(s)*sizeof(char));
	char * saveR = resultat;

	int cpt = 0;

	while(*s!='\0'){
		saveChar[cpt] = *s;
		s++;
		cpt++;
	}


	while(cpt > 0 ){
		
		*resultat = saveChar[cpt-1];
		resultat++;
		cpt--;
	
	}
	

	return saveR;

}

char * saisie (){

	int tmp = 0;
	char * save = (char *) malloc(tmp*sizeof(char));
	char * dSave = save;
	char c;
		
	printf("Ecrire : \n>> ");
	c = getchar(); 
	tmp++;		
	
	while(!isspace(c)){
		save = (char *)realloc(save, tmp*sizeof(char));
		dSave = save;
		save[tmp-1] = c;
		c = getchar();
		tmp++;		
	
	}
		

	return dSave;
	

}
