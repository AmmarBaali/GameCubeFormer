

//this file contains variables and functions related to he game logic and game events.

//number of frames the game has been running
int tickcount = 0;

//flag to see if game has started
bool gameStarted = false;

//time until next layer drop
int ticksuntildrop = 120;

void resetGame(){
	for(int z=0;z<GRIDSIZE;z++){
		for(int y=0;y<GRIDSIZE;y++){
			for(int x=0;x<GRIDSIZE;x++){
				if(z==0){
					gamegrid[x][y][0]=1;
					fallinggrid[x][y]=0;
				}
				else
					gamegrid[x][y][z]=0;
					
			}
		}
	}

Px=16;
Py=16;
Pz=16;
fallinggridposition=120.0;
}

//function called when player is inside a block when it jins to the main world.
void onPlayerHitByFallingBlock(){
	PlaySound("slap.wav",NULL,SND_FILENAME);
	resetGame();
}

void fallingGridJoin(){
	
	//for each block in the falling grid
		for(int y=0;y<GRIDSIZE;y++){
			for(int x=0;x<GRIDSIZE;x++){
				
				
				//if the falling grid has a block at pos x,y
				if(fallinggrid[x][y]>0){
					if(gamegrid[x][y][clamp(floor(fallinggridposition/32),0,GRIDSIZE-1)]>0){

						gamegrid[x][y][clamp(1+floor(fallinggridposition/32),0,GRIDSIZE-1)]=fallinggrid[x][y];
						fallinggrid[x][y]=0;
						if(playerInsideBlock(x,y,clamp(1+floor(fallinggridposition/32),0,GRIDSIZE-1))){
							onPlayerHitByFallingBlock();
						}
						onFallingGridJoinWithMain();
					}
				}
			}
		}
}
//various game events
void gameLogic(){
	if(!gameStarted)
	{
		initWorld();
		gameStarted = true;
	}
	else
	{
		ticksuntildrop--;
		if(fallinggridposition<=0){
			//make a new falling layer.
			initNewFallingLayer();
			 PlaySound("moving.wav",NULL,SND_FILENAME);
		}

		fallingGridMoveDown();
		fallingGridJoin();
	}
}
