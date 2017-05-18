#include "tp6.h"

int lire_deux_octets(int fd, unint16 *val){
	return read(fd,val,2);
}

int lire_quatre_octets(int fd, unint32 *val){
	return read(fd,val,4);
}

int lire_entete(int de, entete_bmp *entete){
	int condition;

	//entete_fichier
	if((condition = lire_deux_octets(de,&(entete->fichier.signature)))<0)
	{		
		perror("erreur lecture signature");
		return -1;
	}
	if((condition = lire_quatre_octets(de,&(entete->fichier.taille_fichier)))<0)
	{		
		perror("erreur lecture taille fichier");
		return -1;
	}
	if((condition = lire_quatre_octets(de,&(entete->fichier.reserve)))<0)
	{		
		perror("erreur lecture reserve");
		return -1;
	}
	if((condition = lire_quatre_octets(de,&(entete->fichier.offset_donnees)))<0)
	{		
		perror("erreur lecture offset donnee");
		return -1;
	}
	//entete_bitmap

	if((condition = lire_quatre_octets(de,&(entete->bitmap.taille_entete)))<0)
	{		
		perror("erreur lecture taille entete");
		return -1;
	}

	if((condition = lire_quatre_octets(de,&(entete->bitmap.largeur)))<0)
	{		
		perror("erreur lecture largeur");
		return -1;
	}

	if((condition = lire_quatre_octets(de,&(entete->bitmap.hauteur)))<0)
	{		
		perror("erreur lecture hauteur");
		return -1;
	}

	if((condition = lire_deux_octets(de,&(entete->bitmap.nombre_plans)))<0)
	{		
		perror("erreur lecture nombre plans");
		return -1;
	}

	if((condition = lire_deux_octets(de,&(entete->bitmap.profondeur)))<0)
	{		
		perror("erreur lecture profondeur");
		return -1;
	}
	if((condition = lire_quatre_octets(de,&(entete->bitmap.compression)))<0)
	{		
		perror("erreur lecture compression");
		return -1;
	}

	if((condition = lire_quatre_octets(de,&(entete->bitmap.taille_donnees_image)))<0)
	{		
		perror("erreur lecture taille donnee image");
		return -1;
	}

	if((condition = lire_quatre_octets(de,&(entete->bitmap.resolution_horizontale)))<0)
	{		
		perror("erreur lecture resolution horizontale");
		return -1;
	}


	if((condition = lire_quatre_octets(de,&(entete->bitmap.resolution_verticale)))<0)
	{		
		perror("erreur lecture resolution verticale");
		return -1;
	}

	if((condition = lire_quatre_octets(de,&(entete->bitmap.taille_palette)))<0)
	{		
		perror("erreur lecture taille palette");
		return -1;
	}

	if((condition = lire_quatre_octets(de,&(entete->bitmap.nombre_de_couleurs_importantes)))<0)
	{		
		perror("erreur lecture nombre de couleur importante");
		return -1;
	}
	return condition;
	
}

int ecrire_deux_octets(int fd, unint16 val){
	return write(fd,&val,2);
}

int ecrire_quatre_octets(int fd, unint32 val){
	return write(fd,&val,4);
}

int ecrire_entete(int vers, entete_bmp *entete){
	int condition;

	//entete_fichier
	if((condition = ecrire_deux_octets(vers,entete->fichier.signature))<0)
	{		
		perror("erreur ecriture signature");
		return -1;
	}
	if((condition = ecrire_quatre_octets(vers,entete->fichier.taille_fichier))<0)
	{		
		perror("erreur ecriture taille fichier");
		return -1;
	}
	if((condition = ecrire_quatre_octets(vers,entete->fichier.reserve))<0)
	{		
		perror("erreur ecriture reserve");
		return -1;
	}
	if((condition = ecrire_quatre_octets(vers,entete->fichier.offset_donnees))<0)
	{		
		perror("erreur ecriture offset donnee");
		return -1;
	}
	//entete_bitmap

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.taille_entete))<0)
	{		
		perror("erreur ecriture taille entete");
		return -1;
	}

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.largeur))<0)
	{		
		perror("erreur ecriture largeur");
		return -1;
	}

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.hauteur))<0)
	{		
		perror("erreur ecriture hauteur");
		return -1;
	}

	if((condition = ecrire_deux_octets(vers,entete->bitmap.nombre_plans))<0)
	{		
		perror("erreur ecriture nombre plans");
		return -1;
	}

	if((condition = ecrire_deux_octets(vers,entete->bitmap.profondeur))<0)
	{		
		perror("erreur ecriture profondeur");
		return -1;
	}
	if((condition = ecrire_quatre_octets(vers,entete->bitmap.compression))<0)
	{		
		perror("erreur ecriture compression");
		return -1;
	}

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.taille_donnees_image))<0)
	{		
		perror("erreur ecriture taille donnee image");
		return -1;
	}

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.resolution_horizontale))<0)
	{		
		perror("erreur ecriture resolution horizontale");
		return -1;
	}


	if((condition = ecrire_quatre_octets(vers,entete->bitmap.resolution_verticale))<0)
	{		
		perror("erreur ecriture resolution verticale");
		return -1;
	}

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.taille_palette))<0)
	{		
		perror("erreur ecriture taille palette");
		return -1;
	}

	if((condition = ecrire_quatre_octets(vers,entete->bitmap.nombre_de_couleurs_importantes))<0)
	{		
		perror("erreur ecriture nombre de couleur importante");
		return -1;
	}
	return condition;
}

int verifier_entete(entete_bmp *entete){
	int condition;
	
	if(entete->bitmap.profondeur == 25)
		condition = 1;
	else{
		condition = 0;
		perror("erreur de profondeur lors de vérification");
	}

	return condition;
}

unsigned char* allouer_pixels(entete_bmp *entete){

	unsigned char* resultat ;
	resultat= malloc(entete->bitmap.taille_donnees_image*sizeof(unsigned char));
	return resultat;
}

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels){
	int lecture;
	lecture = read(de,pixels,entete->bitmap.taille_donnees_image);
	return lecture;


}

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels){
	int ecriture = write(vers,pixels,entete->bitmap.taille_donnees_image);
	return ecriture;
}
