#include "tp6.h"

int copier_bmp(int de, int vers)
{
	entete_bmp entete;
	unsigned char *pixels;
	
	/* lecture du fichier source */
	lire_entete(de, &entete);
	pixels = allouer_pixels(&entete);
	lire_pixels(de, &entete, pixels);
	moitie(&entete, pixels,0);
	/* écriture du fichier destination */
	ecrire_entete(vers, &entete);
	ecrire_pixels(vers, &entete, pixels);
	/* on libère les pixels */
	free(pixels);


	return 1; /* on a réussi */
}

//bgr

void rouge(entete_bmp *entete, unsigned char *pixels){
	
	unsigned int i = 0;
	unsigned int offset = 4-entete->bitmap.largeur%4;
	unsigned int c_offset = 0;
	printf("offset: %d\n",offset);
	for( i=0 ; i < entete->bitmap.taille_donnees_image;i=i+3)
	{
		if(i!=0 && (i-c_offset)%((entete->bitmap.largeur*3))==0)
		{
			printf("I: %d %d\n",i,i/3);
			i = i+offset;
			c_offset+=offset;	
		}
			
		// detecter compostante vert et bleu : i+1 =  ; i-1 = 
		pixels[i]=0;
		pixels[i+1]=0;
			
	}

	
}

void moitie(entete_bmp *entete, unsigned char *pixels, int sup){

	unsigned int i;
	int moitie = 0;

	if(sup == 1){
		moitie = (entete->bitmap.taille_donnees_image/2);
	}
	
	for(i = 0 ; i < entete->bitmap.taille_donnees_image/2 ; i++){
		pixels[i]=pixels[i+moitie];
	}

	entete->bitmap.hauteur /=2;
	entete->bitmap.taille_donnees_image/=2;
}

void negatif(entete_bmp *entete, unsigned char *pixels){
	
	unsigned int i = 0;
	while(i < entete->bitmap.taille_donnees_image){
		
		*pixels = 255-(*pixels);
		pixels++;
		
		i++;
		
	}
}

void noir_et_blanc(entete_bmp *entete, unsigned char *pixels){

	unsigned int i;
	int moyenne;

	for(i=0; i < entete->bitmap.taille_donnees_image; i+=3){
		moyenne = (pixels[i]+pixels[i+1]+pixels[i+2]);
		moyenne/=3;
		pixels[i]=moyenne;
		pixels[i+1]=moyenne;
		pixels[i+2]=moyenne;
	}
}



