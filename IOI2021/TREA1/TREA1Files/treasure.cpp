#include "treasure.h"

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

int mainSearchRows(unsigned char N, int from, int to, int requiredTreasures)
{
	int foundTreasures = 0;

	if (foundTreasures == requiredTreasures)
		return foundTreasures;

	if (from == to)
	{
		// switch to column search
		return mainSearchColumns(N, from, 1, N, requiredTreasures);
	}

	int seperator = from + ((to - from) / 2);

	int subSearchRows1 = getNumberOfTreasuresInArea(from, 1, seperator, N);
	if (subSearchRows1 != 0)
		foundTreasures += mainSearchRows(N, from, seperator, subSearchRows1);

	if (foundTreasures == requiredTreasures)
		return foundTreasures;

	int subSearchRows2 = requiredTreasures - foundTreasures;
	if (subSearchRows2 != 0)
		foundTreasures += mainSearchRows(N, seperator + 1, to, subSearchRows2);

	return foundTreasures;
}


void findTreasure(int N)
{
	int globalTreasures = getNumberOfTreasuresInArea(1, 1, N, N);
	mainSearchRows(N, 1, N, globalTreasures);
}


