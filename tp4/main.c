#include "tp4.h"

int main( int argc, char * argv [] ) {
	int i;
 	int j;
	int nbs = 0;
	int nbm = 0;
	int i_m = 0;
	int nbother = 0;
	int nbtiret = 0;
	char * memory = NULL;

    for(i = 1; i < argc; ++i ) {
		
		if(argv[1][0] != '-' && argc < 3)
			i = argc;
		else{
			for(j = 1; j < (int)strlen(argv[i]);j++){
		
			
				if(argv[i][j] == 's')
				{
					nbs ++;
				}else if(argv[i][j] == 'm')
				{	
					if(i==1)i_m=2;
					else if(i==2) i_m=1;	
					nbm ++;
				}else if(argv[i][j] == '-'){
					nbtiret++;
				}else{
					nbother++;
				}
			}
		}        
			
    }

	if(nbs == 1 && nbm == 0 && argc == 2){
		printf("%s\n",saisie());
	}else if(nbs == 0 && nbm == 1 && argc == 3 && i_m!=3){
		
		printf("%s\n",miroir(argv[argc-1]));

	}else if(nbs !=0 && nbm != 0 && nbother == 0){
		memory = saisie();
		printf("%s\n",memory);
		printf("%s\n",miroir(memory));
					
	}else{
		printf("mauvaise utilisation\n");
	}

	return 0;
}
