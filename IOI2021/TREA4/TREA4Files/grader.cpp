// ATTENTION: Real-Grader might be different
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "treasure.h"

static int N, GRID[101][101], HELP[101][101], RESULT[101][101], ENERGY = 0;
double _getPoints();

int main()
{
	int r, c;
	scanf("%d", &N);
	for(r = 1; r <= N; r++)
		for(c = 1; c <= N; c++)
			scanf("%d", &GRID[r][c]);
	for(r = 1; r <= N; r++)
		for(c = 1; c <= N; c++)
			HELP[r][c] = HELP[r - 1][c] + HELP[r][c - 1] - HELP[r - 1][c - 1] + GRID[r][c];
	
			
	findTreasure(N);
	
	for(int r = 1; r <= N; r++)
	{
		for(int c = 1; c <= N; c++)
		{
			if(GRID[r][c] != RESULT[r][c])
			{
				printf("Wrong - 0.0P\n");
				return 0;
			}
		}
	}
	
	printf("Correct - %lf\n", _getPoints());
	
	return 0;
}
int getNumberOfTreasuresInArea(int r1, int c1, int r2, int c2)
{
	assert(1 <= r1 && r1 <= N); assert(1 <= c1 && c1 <= N); 
	assert(1 <= r2 && r2 <= N); assert(1 <= c2 && c2 <= N);
	assert(r1 <= r2); assert(c1 <= c2);
	ENERGY += 1 + N*N - (r2 - r1 + 1) * (c2 - c1 + 1);
	return HELP[r2][c2] - HELP[r1 - 1][c2] - HELP[r2][c1 - 1] + HELP[r1 - 1][c1 - 1];
}
void reportTreasure(int r, int c)
{
	assert(1 <= r && r <= N); assert(1 <= c && c <= N);
	RESULT[r][c] = 1; 
}
double _getPoints()
{
	double N4 = N*N*N*N, E = ENERGY;
	if(E <= (N4*7)/16 + N*N)
		return 10.0;
	if(E <= (N4*7)/16 + 2*N*N*N)
		return 7.5;
	if(E <= (N4*3)/4)
		return 4.1;
	if(E <= N4)
		return 1.0;
	return 0.0;	
}



