//FLORIAN BARBET SAULE 14
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int obtenir_valeur_aleatoire(int borne_superieure);
void lancer_patate(int out, int valeur);
int recevoir_patate(int in);
void demarrer_recepteur_patate(int in, int out);

