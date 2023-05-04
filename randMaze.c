#include "random.h"
#include "block.h"

extern int blockState[N];

void randMaze()
{
	int i, k;
	for(k = 0;k < 35 ; k++){
		while(1){
			i = rand()%N;
		    if(blockState[i]){
		    	break;
			}
			blockState[i] = BARRIER;
		}
    }
}

	
	
	
