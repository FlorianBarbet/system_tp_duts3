#include "tp5.h"

int main( int argc, char * argv []){

	int fd;
	int tr;
	int mot = 0;
	int lig = 0;
	int car = 0;
	
	int ttmot = 0;
	int ttlig = 0;
	int ttcar = 0;
	int nbc = 0;
	int nbw = 0;
	int nbl = 0;
	int nbother = 0;
	int nbtiret = 0;
	
	int i ;

    for(i = 1; i < argc; ++i ) {
		
		if(argv[1][0] != '-' && argc < 3)
			i = argc;
		else{
			for(j = 1; j < (int)strlen(argv[i]);j++){
				
				if(argv[i][j] == 'l')
				{
					nbl ++;
			
				} else if(argv[i][j] == 'c')
				{
					nbc ++;
				}else if(argv[i][j] == 'w')
				{	
					nbw ++;
				}else if(argv[i][j] == '-'){
					nbtiret++;
				}else{
					nbother++;
				}
			}
		}        
			
    }
	if(nbl == 0 && nbc == 0 && nbw == 0 && argc >= 1){
		for(i=1;i<argc;i++){		
				fd = open(argv[i],O_RDONLY);
				tr = traiter(fd,&car,&mot,&lig);
				close(fd);	
				printf(" car : %d, mot : %d, lig : %d -> %s\n",car,mot,lig,argv[i]);
				if(tr != -1){
					ttmot += mot;
					ttcar += car;
					ttlig += lig;
					mot =0;
					car=0;
					lig=0;
				}	
				if(i+1 == argc)printf(" car : %d, mot : %d, lig : %d -> total\n",ttcar,ttmot,ttlig);
			}
			
	
	}else if(nbl != 0 || nbc !=0 || nbw !=0 ){
		for(i=nbtiret-1;i<argc;i++){		
				fd = open(argv[i],O_RDONLY);
				tr = traiter(fd,&car,&mot,&lig);
				close(fd);	
			if(tr != -1){
					ttmot += mot;
					ttcar += car;
					ttlig += lig;
					mot =0;
					car=0;
					lig=0;
			}
	
			if(nbl != 0){
				printf(" lig : %d -> %s\n",lig,argv[i]);
			}
			if(nbw !=0){
				printf("mot : %d-> %s\n",mot,argv[i]);
			}
			if(nbc != 0){
				printf(" car : %d-> total\n",car,argv[i]);
			}
		}
			if(nbl != 0){
				printf(" lig : %d -> total\n",ttlig,argv[i]);
			}
			if(nbw !=0){
				printf("mot : %d-> total\n",ttmot,argv[i]);
			}
			if(nbc != 0){
				printf(" car : %d-> total\n",ttcar,argv[i]);
			}

	}
	


	
	

	return tr;
}
