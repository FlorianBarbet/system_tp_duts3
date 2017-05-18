#include<stdio.h>


typedef struct {

	int den;
	int num;
}rat;


rat rat_simplification(rat n){
	rat resultat={1,1};
	
	int pgcd;
	int indice;

	pgcd = (n.den*1.00)-(n.num*1.00);
	indice = (n.den*1.00)-(n.num*1.00)
	while(pgcd!=0){
	
		pgcd-=indice
	}
	
	
	return n;


}

rat rat_produit(rat n1, rat n2){

	rat resultat;

	resultat.den = n1.den * n2.den;
	resultat.num = n1.num * n2.num;

	return resultat;
}

rat rat_somme(rat n1, rat n2){
	
	rat resultat;

	resultat.den = (n1.den * n2.num) + (n2.den * n1.num);
	resultat.num = n1.num * n2.num;

	return resultat;
}

rat rat_plus_petit(rat list[]){

	rat resultat;
	resultat.den = list[0].den;
	resultat.num = list[0].num;
	
	int i = 0;	
	
	while(list[i].den!=0){		

		if((list[i].den*1.0/list[i].num*1.0) < (resultat.den*1.0/resultat.num*1.0)){
			resultat.den = list[i].den;
			resultat.num = list[i].num;
		}
		i++;
	}

	return resultat;	
}
