#include "iutsh.h"
#include "ligne_commande.h"

#define GRN "\x1B[31m"
#define RESET "\x1B[0m"


void execute_ligne_commande(){


	int flag = -1;
	int nb = -1;
	pid_t  pid;
	int    status;
	char * buf = malloc(250*sizeof(char));
	char *** argv =ligne_commande(&flag, &nb);
	char * path = malloc(250*sizeof(char));


	if(strcmp(argv[0][0],"exit")==0){
		printf("Good Bye\n");
		free(argv);
		exit(0);
	}


     if ((pid = fork()) < 0 || flag < 0) {
         printf("*** ERROR: forking child process failed\n");
	 libere(argv);
         exit(1);
     }
     else if (pid == 0 ) {

        if(strcmp(argv[0][0],"cd")==0){
		if(chdir(argv[0][1])!=0){
			printf("*** ERROR: cd : exec failed\n");
			exit(1);
		}
	}else if(strcmp(argv[0][0],"mkdir")==0){
		buf = getcwd(buf,250);
		path=strcat(buf,"/");
		path=strcat(path,argv[0][1]);

		if(mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0){
			printf("*** ERROR: mkdir : exec failed\n");
		}

	}else if (execvp(**argv, *argv) < 0) {
              		 printf("*** ERROR: exec failed\n");
        	         exit(1);
        }
    }else {
	 while (wait(&status) != pid)
              ;
    }
    if(flag == 0)
	waitpid(pid,NULL,WUNTRACED);
    else if(flag==1){
		//waitpid(pid,&status,WNOHANG);
		waitpid(pid,&status,WCONTINUED);
    }


    free(argv);
}



void affiche_prompt(){

	char * hostname = NULL;

	char * buf=malloc(250*sizeof(char));
	char * home=malloc(250*sizeof(char));
	size_t size = 250*sizeof(char);
	char * cond;


	buf=getcwd(buf,size);
	hostname=malloc(sizeof(char)); 
	gethostname(hostname,sizeof(hostname));
	hostname=realloc(hostname,sizeof(hostname));
	cond = strstr(buf,getenv("HOME"));

	home = getenv("HOME");

	if(cond!=NULL){
		buf+=strlen(home);

		printf(GRN "%s@%s:~%s$ " RESET,getenv("LOGNAME"),hostname,buf);
	}
	else
	{
		printf(GRN "%s@%s:%s$ " RESET,getenv("LOGNAME"),hostname,buf);
	}

	fflush(stdout);
	free(hostname);
}

int lance_commande( int in, int out, char *com, char ** argv){

	ligne_commande(,)

}

