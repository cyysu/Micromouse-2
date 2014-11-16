#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <Windows.h>
using namespace std;

void printFlood();
void flood();
void mazeGen();
void removeWall();
void printWall();
#define WALL = 1


int b[16][16][4] = {{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 
					{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}};	//maze
int c[16][16];
int main()
{
	srand(time(0));
	mazeGen();	
	flood();
	printFlood();
	

	return 0;
}

void flood()
{
//----------//Flood//----------//
		//fills all flood array spaces with -1
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				c[i][j] = -1;
			}
		}

		//fills the four goal flood array spaces with 0
 	 	c[7][7] = 0;
 	 	c[7][8] = 0;
 	 	c[8][7] = 0;
 	 	c[8][8] = 0;

	  	//fills the flood array with values using flood fill logic
	  	for(int k=0;k<256;k++){
	    	for(int i=0;i<16;i++){
	      		for(int j=0;j<16;j++){
	        		if(c[i][j]==k){  //if the flood array space equals k (starting at 0), place k+1 in adjacent flood array spaces
						if(j<15){
	          				if(!b[i][j+1][2] && (c[i][j+1]==-1)){  //North
	            				c[i][j+1] = c[i][j] + 1;
	     	     			}
						}
						if(j>0){
	          				if(!b[i][j-1][0] && (c[i][j-1]==-1)){  //South
	           					c[i][j-1] = c[i][j] + 1;
		          				}
					}
						if(i<15){
	          				if(!b[i+1][j][3] && (c[i+1][j]==-1)){  //East
	            				c[i+1][j] = c[i][j] + 1;
	          				}
						}
						if(i>0){
	          				if(!b[i-1][j][1] && (c[i-1][j]==-1)){  //West
	            				c[i-1][j] = c[i][j] + 1;
	          				}
						}
	        		}
	      		}
	    	}
		}
}

void printFlood()
{
cout << endl;
for(int ii = 15; ii > -1 ;--ii)
{
	for(int jj = 0; jj < 16; ++jj)
	{
		cout << setw(3) << c[ii][jj];
	}
	cout << endl;
}
}

void mazeGen()
{
	bool unreachable = true;
	for(int row = 0; row < 16; ++row)
	{
		for(int col = 0; col < 16; ++col)
		{
			for(int dir = 0; dir < 4; ++dir)
			{
				b[row][col][dir] = 1;
			}
		}
	}
	
	while(unreachable)
	{
	removeWall();
	flood();

	/*
	unreachable = false;
	for(int row = 0; row < 16; ++row)
	{
		for(int col = 0; col < 16; ++col)
		{
			if(c[row][col] == -1)
			{
				unreachable = true;
				break;
			}
		}
	}*/
	if(c[0][0] > 0 && c[15][0] > 0 && c[0][15] > 0 && c[15][15] > 0)
	{
		unreachable = false;	
	}
	printFlood();
	}
}

void removeWall()
{
	int randRow = rand() % 16;
	int randCol = rand() % 16;
	int randDir = rand() % 4;
	if(randRow == 0 && randDir == 2){}
	else if(randRow == 15 && randDir == 0){}
	else if(randCol == 0 && randDir == 3){}
	else if(randCol == 15 && randDir == 1){}
	else
	{
		b[randRow][randCol][randDir] = 0;
	
		if(randDir == 0)
		{
			b[randRow + 1][randCol][2] = 0;
		}
		else if(randDir == 1)
		{
			b[randRow][randCol + 1][3] = 0;
		}
		else if(randDir == 2)
		{
			b[randRow - 1][randCol][0] = 0;
		}
		else
		{
			b[randRow][randCol - 1][1] = 0;
		}
	}
	
}

void printWall()
{	

	system("cls");
	printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
	for(int row=0; row<16; row++)
	{
		printf("\n|");
		for(int col=0; col<16; col++)
		{
			///visual representation
			if(b[row][col][3]){
				printf("_");}
			else{
				printf(" ");}
			if(b[row][col][1]){
				printf("|");}
			else{
				printf(" ");}

			//printf("%d ", b[i][j][0]+b[i][j][1]+b[i][j][2]+b[i][j][3]);	//wall count

			//printf("%d\t",c[row][col]);	//flood value
			}
	}
}