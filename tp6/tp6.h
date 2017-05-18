#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/* On déclare des types dont on est sûr de la taille.
Si on doit implémenter le TP sur une architecture différente, il
suffit de changer ces déclarations
*/
typedef unsigned short unint16;
typedef unsigned int unint32;

	typedef struct
	{
		unint16 signature;
		unint32 taille_fichier;
		unint32 reserve;
		unint32 offset_donnees;
	} entete_fichier;

	typedef struct
	{
		unint32 taille_entete;
		unint32 largeur;//%4 = nb octet remplissage
		unint32 hauteur;
		unint16 nombre_plans;
		unint16 profondeur;
		unint32 compression;
		unint32 taille_donnees_image;
		unint32 resolution_horizontale;
		unint32 resolution_verticale;
		unint32 taille_palette; /* en nombre de couleurs */
		unint32 nombre_de_couleurs_importantes; /* 0 */
	} entete_bitmap;

	typedef struct
	{
		entete_fichier fichier;
		entete_bitmap bitmap;
	} entete_bmp;

//Lecture
int lire_deux_octes(int fd, unint16 *val);
int lire_quatre_octets(int fd, unint32 *val);
int lire_entete(int de, entete_bmp *entete);

//Ecriture
int ecrire_deux_octets(int fd, unint16 val);
int ecrire_quatre_octets(int fd, unint32 val);
int ecrire_entete(int vers, entete_bmp *entete);

//Exercice 5
int verifier_entete(entete_bmp *entete);
//allocation
unsigned char* allouer_pixels(entete_bmp *entete);
//lecture pixel
int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels);
//ecriture 
int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels);

// tp62

//copier
int copier_bmp(int de, int vers);

//Modification
void rouge(entete_bmp *entete, unsigned char *pixels);
void negatif(entete_bmp *entete, unsigned char *pixels);
void noir_et_blanc(entete_bmp *entete, unsigned char *pixels);
void moitie(entete_bmp *entete, unsigned char *pixels, int sup);

