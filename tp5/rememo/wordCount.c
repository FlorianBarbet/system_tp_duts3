#include "tp5.h"

int main(int argc, char * argv []){

	int fd=0;
	int tr=0;
	int mot = 0;
	int lig = 0;
	int car = 0;
	int i,j;
	int ttmot = 0;
	int ttlig = 0;
	int ttcar = 0;
	int nbc = 0;
	int nbw = 0;
	int nbl = 0;
	int nbtirets = 0;
	int mIndex = 1;
	int nbother = 0;
	
	
	



	 for(i = 1; i < argc; ++i ) {
		
		if(argv[1][0] != '-' ){
			i = argc;
			
		}	
		else{
		
				for(j = 0 ; j < (int)strlen(argv[i]);j++){
					
				
					if(argv[i][j] == 'c')
					{
						nbc++;
					}else if(argv[i][j] == 'w'){	
						nbw++;
					}else if(argv[i][j] == 'l'){
						nbl++;
					}else if(argv[i][j] == '-'){
						if(argv[i][j+1]!='c'&&argv[i][j+1]!='l'&&argv[i][j+1]!='w'){
							printf("erreur option : -%c n'existe pas\n",argv[i][j+1]);
							return -1;
						}
						nbtirets++;
					}else{
						
						if(mIndex == 1)mIndex=i;
						nbother++;
	
					}
				}
			
		}
    }
	
	
	
if(argc == 1|| (argc!=0&&(nbc!=0||nbl!=0||nbw!=0)&&nbother==0)){

	tr = traiter(0,&car,&mot,&lig);
	if(tr!=1)
	printf("\ncar : %d, mot : %d, lig : %d -> STDIN\n",car,mot,lig);
	return tr;
}

	for(i=mIndex ; i<argc ; i++ ){

	
		if(open(argv[i],O_RDONLY) == -1){
			perror(argv[i]);
			
		}else{
		fd = open(argv[i],O_RDONLY);
		tr = traiter(fd,&car,&mot,&lig);
		mot--;
		close(fd);
		if(tr != 1){

			if(nbc != 0){
				printf("car : %d ",car); 
				ttcar += car; car=0;
				
			}
			if(nbw != 0){
				printf("mot : %d ",mot); 
				ttmot += mot; mot=0;

			}
			if(nbl != 0){
				printf("lig : %d ",lig); 
				ttlig += lig; lig=0;

			}
			if(nbc==0 && nbw==0 && nbl==0 && nbtirets == 0){
				printf(" car : %d, mot : %d, lig : %d -> %s \n",car,mot,lig,argv[i]);
				ttmot += mot;
				ttcar += car;
				ttlig += lig;
				mot=0;
				car=0;
				lig=0;
				if(i+1 == argc)
				printf(" car : %d, mot : %d, lig : %d -> total\n",ttcar,ttmot,ttlig);
			}else {
				printf("-> %s\n",argv[i]);
				if(i+1 == argc&&nbc!=0)printf("car : %d ",ttcar);
				if(i+1 == argc&&nbw!=0)printf("mot : %d ",ttmot);
				if(i+1 == argc&&nbl!=0)printf("lig : %d ",ttlig);
				if(i+1 == argc)printf("-> total\n");
				

			}
}
			
		}
	}
	

	return tr;
}
