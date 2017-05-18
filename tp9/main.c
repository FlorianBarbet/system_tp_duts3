#include "iutsh.h"
#include "ligne_commande.h"

int main(void){

	while(1){
		affiche_prompt();
		execute_ligne_commande();
	}

	return 0;
}
