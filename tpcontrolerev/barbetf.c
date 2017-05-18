// Version à finir
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#include <fcntl.h>

#define FILENAME_SIZE 256
typedef struct {
char fichier [ FILENAME_SIZE ];
} job_t;

int afficher_details(const char *fichier){
	struct stat buffer;
	int resultat;

	resultat =  stat(fichier,&buffer);
/*
	if (S_ISREG(buffer.st_mode)) write(1, "-", 1);
	else if (S_ISDIR(buffer.st_mode)) write(1, "d", 1);
	else if (S_ISCHR(buffer.st_mode)) write(1, "c", 1);
	else if (S_ISBLK(buffer.st_mode)) write(1, "b", 1);
	else if (S_ISFIFO(buffer.st_mode)) write(1, "p", 1);
	else if (S_ISLNK(buffer.st_mode)) write(1, "l", 1);
	else if (S_ISSOCK(buffer.st_mode)) write(1, "s", 1);

*/
switch (buffer.st_mode & S_IFMT) {
    case S_IFBLK:  printf("	b"); break;
    case S_IFCHR:  printf("	c"); break;
    case S_IFDIR:  printf("	d"); break;
    case S_IFIFO:  printf("	FIFO/tube\n"); break;
    case S_IFLNK:  printf("	lien symbolique\n"); break;
    case S_IFREG:  printf("	-"); break;
    case S_IFSOCK: printf("	socket\n"); break;
    default: printf(" inconnu "); break;
}
	

	printf(", %s , %ld \n",fichier,buffer.st_size);
	
printf("\n");

	return resultat;
}

int envoyer_job(int fd, const job_t *job){
	int ret;
	ret=write(fd,job,FILENAME_SIZE);
	if(ret<0)perror("[ERROR] Erreur d'ecriture ");
	
	return ret;

}

int recevoir_job(int fd, job_t *job){
	int ret;
	ret=read(fd,job,FILENAME_SIZE);
	if(ret<0)perror("[ERROR] Erreur de lecture ");
	printf("retour lecture : %i fd : %i \n ",ret,fd);
	return ret;
}

void traitement_fils(int fd){

	int isOK;
	job_t *job;
	
	while((isOK = recevoir_job(fd,job))>=0){
		afficher_details(job->fichier); 
		job++;
	}

	close(fd);
	printf("Processus fils de pid %d : Fini \n",getpid());
	exit(EXIT_SUCCESS);
}

int creer_fils(int tube[2]){
	int pid ;
	
	pid=fork();
	
	if(pid==0){
		close(tube[0]);
		perror("Fermeture entree tube ");	
		traitement_fils(tube[1]);

	}else{
		close(tube[1]);
		printf("Pere: fils de %d termine correctement \n",getpid());
	}
	
	return pid;

}

int main(int argvi, char * argv []){

	int i;
	int pid;
	int fd[2];

	printf("\n");
	fd[0]=0;	

	for( i = 1;i<argvi;i++){
			
				if (pipe(fd) == -1) {
					perror("Creation du tube \n");
					exit(1);
				}
				
				write(open("tmp",O_WRONLY | O_CREAT),argv[i],256);

				if((fd[1]=open("tmp",O_RDONLY))<0)perror("Ouverture");
				
			
		pid = creer_fils(fd);
		if(pid!=0)
			waitpid(pid,NULL,0);
	}
	
	printf("Pere de pid %i : fini \n",pid);
	while(waitpid(0,NULL,WNOHANG) > 0 );
	

	printf("\nRECHERCHE\n======================\n");
	for(i = 1 ; i<argvi ; i++)
		afficher_details(argv[i]);
	if(i==1)printf("Il manque un paramètre\n");
	
	return 0;
}














































