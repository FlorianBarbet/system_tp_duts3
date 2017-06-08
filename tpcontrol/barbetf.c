//FLORIAN BARBET SAULE 14
#include "barbetf.h"

int obtenir_valeur_aleatoire(int borne_superieure){

	unsigned int val = 0;												//permet de ne pas avoir de nombre négatif
	int fd = open("/dev/urandom", O_RDONLY);							//ouverture descripteur de urandom

	if(read(fd, &val, sizeof(int))==-1)perror("[ERREUR] Aleatoire");	//lecture avec gestion d'erreur
	close(fd);															//fermeture descripteur de urandom
  
	while(val > (unsigned int)borne_superieure || val <= 0)				//on veut que val ai une valeur comprise entre 1 et borne_superieure
		val=val%borne_superieure;										//formatage de la valeur aleatoire obtenu

	if(val==0)val++;													//on ne veut pas que le jeu finisse dès le début

	return val;
}


void lancer_patate(int out, int valeur){
	//afin de ne pas faire d'affichage en cas d'erreur ou fin de jeu
	if (valeur > -1)printf("[INFO] %d: Je lance la patate %d dans %d!\n", getpid(), valeur, out);
	//Ecriture et gestion d'erreur dans la valeur
	if(write(out,&valeur, sizeof(int))<0)perror("[ERROR] lancement ");
}

int recevoir_patate(int in){
	//val initialisé à -1 si il y a une erreur val sera toujours égale à -1
	int val=-1;
	//Lecture et gestion d'erreur	
	if (read(in, &val, sizeof(int))<0)perror("[ERROR] Reception patate");
	//pour indication utilisateur on averti plus lors de la fin de la partie
	if (val > -1)printf("[INFO] %d: J'ai reçu la patate %d depuis %d\n",getpid(), val, in);
	return val;
}

void demarrer_recepteur_patate(int in, int out){
	int value;
/*
*	Debut de l'algorithme
*	
*	1.Lire la valeur de la patate depuis une entrée ;
*	2.Décrémenter cette valeur ;
*	3.Si la valeur de la patate est nulle, quitter en affichant un message ;
*	4.Écrire la valeur de la patate dans une sortie ;
*	5.Recommencer en 1 tant qu’il y a des valeurs à lire depuis l’entrée.
*/
	while ((value = recevoir_patate(in)) > 1){											//tant qu'on peut recevoir (1) et (5)
		value--;																		//decrementation (2)
		printf("[INFO] %d: patate à %d, je passe au suivant\n", getpid(), value);		//indication utilisateur
		lancer_patate(out, value);														//lancement de la patate (4)
    }
	
	//si la patate explose indication écrite pour le/les utilisateurs (3)
	if (value > -1) printf("[INFO] %d: Meme pas mal, c'est gagne\n", getpid());
	else printf("[INFO] %d: Explosion, c'est perdu\n", getpid());
  
	//on écrit la valeur -1 dans le descripteur final ( le perdant )
	lancer_patate(out, -1);
	//sortie du programme et fin de l'algorithme (3)
	exit(0);

}
