#include "tp6.h"

int main(int argc, char * argv []){


	
	int fd;
	entete_bmp entete;
	unsigned char *pixels;
	
	int j ;
	int i ;

	fd = open(argv[argc-1],O_RDONLY);
	lire_entete(fd, &entete);
	pixels = allouer_pixels(&entete);
	lire_pixels(fd, &entete, pixels);
	
	if(verifier_entete(&entete)==0)	return 0;

	

    for(i = 1; i < argc; ++i ) {
		
		if(argv[1][0] != '-' && argc < 3)
			i = argc;
		else{
			for(j = 1; j < (int)strlen(argv[i]);j++){
				
				
				if(argv[i][0]=='-'){
					if(argv[i][j] == 'r')
					{
						rouge(&entete, pixels);
						
					} else if(argv[i][j] == 'n' )
					{
						negatif(&entete, pixels);
					
					}else if(argv[i][j] == 'b' )
					{	
						noir_et_blanc(&entete, pixels);
					
					}else if(argv[i][j] == 's' )
					{	
						moitie(&entete, pixels,1);
						
					}else if(argv[i][j] == 'i' )
					{	
						moitie(&entete, pixels,0);
					
					
					}
				}
				
			}
		}        
			
    }

	close(fd);

	
	
		fd = open("sortie.bmp",O_WRONLY|O_CREAT,0666);
		ecrire_entete(fd, &entete);
		ecrire_pixels(fd, &entete, pixels);
		close(fd);
	
	

	free(pixels);
	


	return 0;
}
