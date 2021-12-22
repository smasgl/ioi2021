#include "treasure.h"
#include <iostream>

int mainSearchColumns(unsigned char N, int row, int from, int to, int requiredTreasures)
{
	int foundTreasures = 0;
	int fields = (to - from + 1);

	int possibleZeros = fields - requiredTreasures;

	if (foundTreasures >= requiredTreasures)
		return foundTreasures;

	if (requiredTreasures == fields)	// All fields are trasures
	{
		for (int i = from; i <= to; i++)
		{
			reportTreasure(row, i);
		}
		return fields;
	}

	int seperator = from + ((to - from) / 2);

	int subSearchColumns1 = getNumberOfTreasuresInArea(row, from, row, seperator);
	if (subSearchColumns1 != 0)
		foundTreasures += mainSearchColumns(N, row, from, seperator, subSearchColumns1);

	int foundZeros = seperator - from + 1 - subSearchColumns1;

	if (foundZeros == possibleZeros)
	{
		unsigned char foundTreasuresFor = 0;
		for (int i = seperator + 1; i <= to; i++)
		{
			reportTreasure(row, i);
			foundTreasuresFor++;
		}
		return foundTreasuresFor + foundTreasures;
	}

 	if (foundTreasures >= requiredTreasures)
		return foundTreasures;

	int subSearchColumns2 = requiredTreasures - foundTreasures;
	if (subSearchColumns2 != 0)
		foundTreasures += mainSearchColumns(N, row, seperator + 1, to, subSearchColumns2);

	foundZeros += to - seperator + 1 - subSearchColumns2;

	if (foundZeros == possibleZeros)
	{
		unsigned char foundTreasuresFor = 0;
		for (int i = seperator + 1; i <= to; i++)
		{
			reportTreasure(row, i);
			foundTreasuresFor++;
		}
		return foundTreasuresFor + foundTreasures;
	}

	return foundTreasures;
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
		if (thisRowTrasures >= 1)
			mainSearchColumns(N, i, 1, N, thisRowTrasures);
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
				mainSearchColumns(N, i, 1, N, thisRowTrasures);
			lookedUp += thisRowTrasures;
			continue;
		}

		unsigned char restRowAndThisRowTreasures = getNumberOfTreasuresInArea(1, 1, i, N);
		unsigned char thisRowTrasures = restRowAndThisRowTreasures - lookedUp;
		if (thisRowTrasures >= 1)
			mainSearchColumns(N, i, 1, N, thisRowTrasures);
		lookedUp += thisRowTrasures;
	}
}


void findTreasure(int N)
{
	int globalTreasures = getNumberOfTreasuresInArea(1, 1, N, N);
	mainSearchRows(N, globalTreasures);
}


