//FLORIAN BARBET SAULE 14
#include "barbetf.h"



int main(){

	//value stock la valeur de base de la patate
	//joueur permettra plus tard de faire tourner les joueurs le joueur 0 puis 1 puis 2 !	
	//i permettra d'incrémenter des boucles for(i=,i<,i++)
	//pid permet de faire des test sur où nous sommes en terme de processus fils?père? etc..
	int pid;
	int i, value, joueur;
	int tubes[3][2];										//les trois pipes et par conséquent les trois processus.


	//indication et declaration de la patate
	printf("[INFO BASE]Patate de base : %d\n",(value=obtenir_valeur_aleatoire(10)));

/*
*
*	Permet de tester la fonction de borne ( si elle est bien correct )
*	for(i=0;i<10;i++)
*	printf("[INFO] patate : %d\n",obtenir_valeur_aleatoire(10));  	
*	
*/
	for(i = 0; i < 3; i++)pipe(tubes[i]); 					//definition des trois tubes
	
	joueur=0;												//identification du processus père
	pid = fork();											//création du premier processus fils
	if(pid == 0)joueur=1;	 								//identification du processus dans le fils qui vient d'être crée ( nouveau joueur )
  	else{													//processus père
		pid = fork();										//création du deuxième processus fils si on se situe dans le père
		joueur=2;											//identification du processus 
	}	

 

	for(i = 0; i < 3; i++){
		if(i != joueur)close(tubes[i][0]);	  				//fermeture des entrées des tubes inutiles on laisse juste celui du joueur courant
		if(i != (joueur + 1) % 3)close(tubes[i][1]);		//fermeture de la sortie des tubes inutiles on laisse juste le tube de sortie du joueur suivant
	}

/*
*
*	lancement de la patate du joueur 2 vers le joueur 3 début de la partie avec une patate aleatoire entre 0 et 10
*
*/  
	if(joueur == 1)lancer_patate(tubes[joueur+1][1], value);

  //Demarrage de l'algorithme
  demarrer_recepteur_patate(tubes[joueur][0], tubes[(joueur+1)%3][1]);

		//on tue les processus zombie
		while(waitpid(0,NULL,0) > 0 );
  return 0;
}
