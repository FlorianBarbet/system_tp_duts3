#include "tab_int.h"
#include "structure.h"
int main(void){
	
	rat n1 = {1,2};
	rat n2 = {1,3};

	rat n3 = {4,2};
	rat n4 = {2,3};
	rat nfin = {0,5};
	rat list_rat[] = {n1,n2,n3,n4,nfin};

    rat tmp;



	int taille_first = 4;
	int taille_second = 8;
	int first_list[taille_first];
	int second_list[taille_second];
	int i;

	for(i= 0; i < taille_first; i++)
		first_list[i]=i+1;
	printf("------tableaux d'entier------\n");
	printf("liste1 : ");
	afficher(first_list, taille_first);
	copie_dans(second_list, first_list, taille_first);
	printf("liste 2 : ");
	afficher(second_list, taille_second);
	first_list[2]=42;
	ajoute_apres(second_list, taille_first, first_list, taille_first);	
	printf("------resultat-------\n");
		printf("liste1 : ");
		afficher(first_list, taille_first);
		printf("liste 2 : ");
		afficher(second_list, taille_second);

		printf("\n>>>SIZE = %d\n",somme(first_list, taille_first));


	tmp = rat_produit(n3,n4);
	printf("------------structure------\nproduit : %d/%d", tmp.den,tmp.num );

	tmp = rat_somme(n1,n2);
	printf("\nsomme : %d/%d\n",tmp.den,tmp.num);

	tmp = rat_plus_petit(list_rat);
	printf("plus petit : %d/%d\n",tmp.den,tmp.num);

	tmp = 	rat_simplification(n4);
	printf("sipplifie : %d/%d\n",tmp.den,tmp.num);
	


	return 0;
}
