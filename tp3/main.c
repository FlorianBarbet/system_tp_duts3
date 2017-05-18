#include <stdio.h>
#include "string2.h"

int main(){

	char s[] = "hello word\n";
	char s1[50] = "Bonjour le monde";
	char * s2 = "Bonjour le monde";
	char * s3 = " Clap";
	char * s4 = "";
	char * s5;
	char * s6;
	int size = 0;
	int size2 = 0;
	int equals = 0;
	int equals1 = 0;
	int equals2 = 0;
	int equals3 = 0;
	int equalsN = 0;
	

	size = mon_strlen(s);
	size2 = mon_strlen2(s1);
	equals = mon_strcmp(s1,s2);
	equals1 = mon_strcmp(s2,s3);
	equals2 = mon_strcmp(s3,s2);
	equals3 = mon_strcmp(s1,s4);
	equalsN = mon_strncmp(s1,s3, 2);
	s4 = mon_strcat(s1,s3);
	s6 = mon_strstr("TutorialsPoint","Point");
	s5 = mon_strchr(s3,'a');

	printf("size = %d \nsize2 = %d\n",size,size2);
	printf("comp(s1 ; s2) = %d\ncomp(s2 ; s3) = %d\ncomp(s3 ; s2) = %d\ncomp(s1 ; s4) = %d\n",equals,equals1,equals2,equals3);
	printf("comp(s1 ; s3 ; 2) = %d\n",equalsN);

	printf("Concatenation : %s\n",s4);
	printf("cherche 'a' : %s\n",s5);
	printf("Substring is : %s\n",s6);

	return 0;
}
