#include "treasure.h"
#include <iostream>

int mainSearchColumns(unsigned char N, int row, int from, int to, int requiredTreasures)
{
	int foundTreasures = 0;
	int fields = (to - from + 1);

	if (foundTreasures == requiredTreasures)
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

	if (foundTreasures == requiredTreasures)
		return foundTreasures;

	int subSearchColumns2 = requiredTreasures - foundTreasures;
	if (subSearchColumns2 != 0)
		foundTreasures += mainSearchColumns(N, row, seperator + 1, to, subSearchColumns2);

	return foundTreasures;
}

void mainSearchRows(unsigned char N, int allTreasures)
{
	int foundTreasures = 0;
	for (unsigned char i = 1; i <= N + 1; i++)
	{
		if (i == N + 1)
		{
			int treasures = getNumberOfTreasuresInArea(N, 1, N, N);
			mainSearchColumns(N, N, 1, N, treasures);
			break;
		}

		int treasures = allTreasures - getNumberOfTreasuresInArea(i, 1, N, N) - foundTreasures;
		if (treasures > 0)
			mainSearchColumns(N, i - 1, 1, N, treasures);

		foundTreasures += treasures;
	}
}


void findTreasure(int N)
{
	int globalTreasures = getNumberOfTreasuresInArea(1, 1, N, N);
	mainSearchRows(N, globalTreasures);
}


