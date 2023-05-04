#include "random.h"
#include "block.h"

extern int blockState[N];

void randMaze()
{
	int i, k;
	for(k = 0;k < FILLRATIO ; k++){
		while(1){
			i = rand()%N;
		    if(blockState[i] == VACANT){
		    	blockState[i] = BARRIER;
		    	break;
			}
		
		}
    }
}

	
	
	
