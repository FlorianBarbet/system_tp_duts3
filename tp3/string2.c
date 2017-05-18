#include <stdio.h>

int mon_strlen(char s[]){
	int cpt=0;
	while(s[cpt]!='\0'){
		cpt++;
	}

	return cpt;
}

int mon_strlen2(const char *s){
	int i=0;
	while(*s!='\0'){
		s++;
		i++;
	}
	return i;
}

int mon_strcmp(const char * s1, const char * s2){

	int i = 0;
	if(*s1 == '\0')
		i--;
	if(*s2 == '\0')
		i++;
	while(*s1!='\0' && *s2!='\0'){
		
		if(*s1 > *s2){
			i--;
		}
		else if(*s1 < *s2){
			i++;
		}
		s1++;
		s2++;		
	}	
	return i;
}

int mon_strncmp(const char * s1, const char * s2, int n){

	int i = 0;
	int cpt = 0;
	if(*s1 == '\0')
		i--;
	if(*s2 == '\0')
		i++;
	while(*s1!='\0' && *s2!='\0' && cpt < n){
		
		if(*s1 > *s2){
			i--;
		}
		else if(*s1 < *s2){
			i++;
		}
		s1++;
		s2++;	
		cpt++;	
	}	
	return i;
}

char *mon_strcat(char *s1, const char *s2){
	char * s = s1;
	
	while(*s1!='\0'){
		s1++;
	}
	
	while(*s2!='\0'){
		*s1 = *s2;
		s1++;
		s2++;
	}	
	*s1='\0';
	return s;
}

char *mon_strchr(char *s, int c){

	char * resultat = NULL;

	while(*s!='\0'){

		if(*s==c){
			resultat = s;
		}
		s++;
	}
	return resultat;
}

char *mon_strstr(char *haystack, char *needle){
	char * tmp = needle;
	char * save = NULL;
	char * resultat = NULL;
	int sizeN = 0;
	int sizeH = 0;


	sizeN = mon_strlen2(needle);
	sizeH = mon_strlen2(haystack);

	if(sizeN < sizeH){
		while(*haystack!='\0'){
			
			resultat = mon_strchr(haystack,*needle);
			if( resultat != NULL ){
				save = haystack+1;
				if(mon_strncmp(resultat,tmp,sizeN)==0)
				{
					return resultat;
				}
				else{
					haystack= save;
				}
			}
			else{	
				haystack++;
			}
			

		}
		return NULL;

	}else if(sizeN == sizeH){
		if(mon_strcmp(haystack,needle)==0)
			return haystack;
		return NULL;
	}
	

	return NULL;
}



