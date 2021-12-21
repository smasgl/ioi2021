#include "treasure.h"
#include <iostream>

void mainSearchColumns(unsigned char N, int row, int requiredTreasures)
{
	int lookedUp = 0;

	for (unsigned char i = 1; i <= (N / 2); i++)
	{
		unsigned char restColumnTreasures = getNumberOfTreasuresInArea(row, i+1, row, N);
		unsigned char thisColumnTrasures = requiredTreasures - restColumnTreasures - lookedUp;
		if(thisColumnTrasures == 1)
			reportTreasure(row, i);
		lookedUp += thisColumnTrasures;
	}

	for (unsigned char i = (N / 2) + 1; i <= N; i++)
	{
		if (i == N)
		{
			// last element take allTreasures and subtract lookedUp Trasures
			unsigned char thisColumnTrasures = requiredTreasures - lookedUp;
			if (thisColumnTrasures == 1)
				reportTreasure(row, i);
			lookedUp += thisColumnTrasures;
			continue;
		}

		unsigned char restColumnAndThisColumnTreasures = getNumberOfTreasuresInArea(row, 1, row, i);
		unsigned char thisColumnTrasures = restColumnAndThisColumnTreasures - lookedUp;
		if (thisColumnTrasures == 1)
			reportTreasure(row, i);
		lookedUp += thisColumnTrasures;
	}
}

void mainSearchRows(unsigned char N, int allTreasures)
{
	int lookedUp = 0;

	for (unsigned char i = 1; i <= (N / 2); i++)
	{
		unsigned char restRowTreasures = getNumberOfTreasuresInArea(i + 1, 1, N, N);
		unsigned char thisRowTrasures = allTreasures - restRowTreasures - lookedUp;
		if(thisRowTrasures >= 1)
			mainSearchColumns(N, i, thisRowTrasures);
		lookedUp += thisRowTrasures;
	}

	for (unsigned char i = (N / 2) + 1; i <= N; i++)
	{
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