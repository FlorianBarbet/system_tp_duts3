#include "iutsh.h"
#include "ligne_commande.h"

#define GRN "\x1B[31m"
#define RESET "\x1B[0m"


void execute_ligne_commande(){

	
	int i=0;
	int in=0;
	int out=1;
	int fd[2];
	int flag = -1;
	int nb = -1;
	pid_t  pid;
	int    status;
	char * buf ;
	char * path ;
	char *** argv =ligne_commande(&flag, &nb);
	
	if(nb>0){
		buf = malloc(250*sizeof(char));
		path = malloc(250*sizeof(char));
	
	
	for(i=0; i < nb;i++){

	     if(strcmp(argv[i][0],"exit")==0){
			printf("Good Bye\n");
			libere(argv);
			exit(0);
	     }else if(strcmp(argv[i][0],"cd")==0){
			if(chdir(argv[0][1])!=0){
				printf("*** ERROR: cd : exec failed\n");
				exit(1);
			}
	     }else if(strcmp(argv[i][0],"mkdir")==0){
			buf = getcwd(buf,250);
			path=strcat(buf,"/");
			path=strcat(path,argv[0][1]);

			if(mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0){
				printf("*** ERROR: mkdir : exec failed\n");
			}

	     }
		

		if(i==nb-1){
		  out=1;
		}else{
			pipe(fd);
		  perror("Pipe : ");
		  out = fd[1];
		}


	     pid = lance_commande(in,out,argv[i][0],argv[i]);
	     in = fd[0];	
	     if (pid != 0 ) {
				if(!flag){
		
		       	 waitpid(pid,&status,0);
	
				}
	    }
	    
			
	}
	libere(argv);
	}
	while(waitpid(0,&status,WNOHANG) > 0 );
        
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

	int pid;
	

	pid=fork();
	if (pid < 0) {
        	 printf("*** ERROR: Creation processus fils\n");
        	 return -1;
	}

	if(pid==0){	
		if(in!=0){
			close(0);
			dup(in);
			close(in);
		}
		if(out!=1){
			close(1);
			dup(out);
			close(out);
		}
		execvp(com,argv);
		perror(com);
		exit(1);
	}else{
		if(in!=0){
			close(in);
		}

		if(out!=1){
			close(out);
		}
	}

	
	return pid;

}



/*
*==========================
*exemple du cours : 
*
*
* ls -l | grep lol | tr ui
* primitive : int pipe(int fd[2]);
*
* tubes côté père mais pas utilisé coté père ne pas fermer avant l'heritage de process
* fermer après duplications
* 
* primitive : int dup(int oldfd);
*
* pour utiliser dup il faut fermer la sortie standard
* close(1);
* dup(fd[1]);
* close(fd[1]);
* 
* 
*
*==========================
*/


