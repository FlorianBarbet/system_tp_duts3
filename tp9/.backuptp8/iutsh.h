#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

void affiche_prompt();
char *** ligne_commande(int * flag, int * nb);
void execute_ligne_commande();
int lance_commande( int in, int out, char *com, char ** argv);
