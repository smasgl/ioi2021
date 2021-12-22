#include "treasure.h"
#include <iostream>

void mainSearchColumns(unsigned char N, int row, int allTreasures)
{
	int lookedUp = 0;

	if (allTreasures == N)	// all treasure
	{
		for (unsigned char j = 1; j <= N; j++)
		{
			reportTreasure(row, j);
		}
		return;
	}

	unsigned char globalPossibleZeros = N - allTreasures;

	for (unsigned char i = 1; i <= (N / 2); i++)
	{
		if (lookedUp == allTreasures)
			return;
		unsigned char restColumnTreasures = getNumberOfTreasuresInArea(row, i+1, row, N);
		if (restColumnTreasures == N - i + 1)// All rest is treasure
		{
			for (unsigned char j = 1; j <= N - i + 1; j++)
			{
				reportTreasure(row, j);
			}
			break;
		}
		unsigned char thisColumnTrasures = allTreasures - restColumnTreasures - lookedUp;
		if (thisColumnTrasures >= 1)
			reportTreasure(row, i);
		else
			globalPossibleZeros--;

		lookedUp += thisColumnTrasures;

		if (globalPossibleZeros == 0)
		{
			for (unsigned char k = i+1; k <= N; k++)
			{
				reportTreasure(row, k);
			}
		}
	}

	for (unsigned char i = (N / 2) + 1; i <= N; i++)
	{
		if (lookedUp == allTreasures)
			return;

		if (i == N)
		{
			// last element take allTreasures and subtract lookedUp Trasures
			unsigned char thisColumnTrasures = allTreasures - lookedUp;
			if (thisColumnTrasures >= 1)
				reportTreasure(row, i);
			else
				globalPossibleZeros--;
			lookedUp += thisColumnTrasures;
			continue;
		}

		unsigned char restColumnAndThisColumnTreasures = getNumberOfTreasuresInArea(row, 1, row, i);
		unsigned char thisColumnTrasures = restColumnAndThisColumnTreasures - lookedUp;
		if (thisColumnTrasures >= 1)
			reportTreasure(row, i);
		else
			globalPossibleZeros--;
		lookedUp += thisColumnTrasures;

		if (globalPossibleZeros == 0)
		{
			for (unsigned char k = i+1; k <= N; k++)
			{
				reportTreasure(row, k);
			}
		}
	}
}

void mainSearchRows(unsigned char N, int allTreasures)
{
	int lookedUp = 0;

	for (unsigned char i = 1; i <= (N / 2); i++)
	{
		if (lookedUp == allTreasures)
			return;

		unsigned char restRowTreasures = getNumberOfTreasuresInArea(i + 1, 1, N, N);
		unsigned char thisRowTrasures = allTreasures - restRowTreasures - lookedUp;
		if(thisRowTrasures >= 1)
			mainSearchColumns(N, i, thisRowTrasures);
		lookedUp += thisRowTrasures;
	}

	for (unsigned char i = (N / 2) + 1; i <= N; i++)
	{
		if (lookedUp == allTreasures)
			return;

		if (i == N)
		{
			// last element take allTreasures and subtract lookedUp Trasures
			unsigned char thisRowTrasures = allTreasures - lookedUp;
			if (thisRowTrasures >= 1)
				mainSearchColumns(N, i, thisRowTrasures);
			lookedUp += thisRowTrasures;
			continue;
		}

		unsigned char restRowAndThisRowTreasures = getNumberOfTreasuresInArea(1, 1, i, N);
		unsigned char thisRowTrasures = restRowAndThisRowTreasures - lookedUp;
		if (thisRowTrasures >= 1)
			mainSearchColumns(N, i, thisRowTrasures);
		lookedUp += thisRowTrasures;
	}
}


void findTreasure(int N)
{
	int globalTreasures = getNumberOfTreasuresInArea(1, 1, N, N);
	mainSearchRows(N, globalTreasures);
}