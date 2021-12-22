#include "treasure.h"
#include <iostream>

void subSearchColumnsFront(unsigned char N, unsigned char requiredTreasures, unsigned char& otherTreasures, unsigned char allTreasures, unsigned char row, unsigned char from, unsigned char to)
{
	unsigned char fieldCount = to - from + 1;

	if (requiredTreasures == fieldCount)	// All remeining fields are treasures
	{
		for (unsigned char i = from; i <= to; i++)
		{
			reportTreasure(row, i);
			otherTreasures++;
		}

		return;
	}

	unsigned char seperator = (to - from + 1) / 2 + from - 1;

	unsigned char otherRowTreasures = getNumberOfTreasuresInArea(row, seperator + 1, row, N) + otherTreasures;
	unsigned char thisRowTreasures = allTreasures - otherRowTreasures;
	if (thisRowTreasures >= 1)
		subSearchColumnsFront(N, thisRowTreasures, otherTreasures, allTreasures, row, from, seperator);

	if (requiredTreasures == thisRowTreasures)
		return;

	thisRowTreasures = requiredTreasures - thisRowTreasures;
	if (thisRowTreasures >= 1)
		subSearchColumnsFront(N, thisRowTreasures, otherTreasures, allTreasures, row, seperator + 1, to);
}

void subSearchColumnsBack(unsigned char N, unsigned char requiredTreasures, unsigned char& otherTreasures, unsigned char allTreasures, unsigned char row, unsigned char from, unsigned char to)
{
	unsigned char fieldCount = to - from + 1;

	if (requiredTreasures == fieldCount)	// All remeining fields are treasures
	{
		for (unsigned char i = from; i <= to; i++)
		{
			reportTreasure(row, i);
			otherTreasures++;
		}

		return;
	}

	unsigned char seperator = (to - from + 1) / 2 + from - 1;

	unsigned char thisRowTreasures = getNumberOfTreasuresInArea(row, 1, row, seperator) - otherTreasures;
	if (thisRowTreasures >= 1)
		subSearchColumnsBack(N, thisRowTreasures, otherTreasures, allTreasures, row, from, seperator);

	if (requiredTreasures == thisRowTreasures)
		return;

	thisRowTreasures = requiredTreasures - thisRowTreasures;
	if (thisRowTreasures >= 1)
		subSearchColumnsBack(N, thisRowTreasures, otherTreasures, allTreasures, row, seperator + 1, to);
}

void subSearchColumns(unsigned char N, unsigned char requiredTreasures, unsigned char row)
{
	unsigned char seperator = N / 2;

	if (requiredTreasures == N)
	{
		for (unsigned char i = 1; i <= N; i++)
		{
			reportTreasure(row, i);
		}
		return;
	}

	unsigned char otherRowTreasures = getNumberOfTreasuresInArea(row, seperator + 1, row, N);
	unsigned char otherTreasures = 0;
	subSearchColumnsFront(N, requiredTreasures - otherRowTreasures, otherTreasures, requiredTreasures, row, 1, seperator);
	subSearchColumnsBack(N, otherRowTreasures, otherTreasures, requiredTreasures, row, seperator + 1, N);
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
			subSearchColumns(N, thisRowTrasures, i);
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
				subSearchColumns(N, thisRowTrasures, i);
			lookedUp += thisRowTrasures;
			continue;
		}

		unsigned char restRowAndThisRowTreasures = getNumberOfTreasuresInArea(1, 1, i, N);
		unsigned char thisRowTrasures = restRowAndThisRowTreasures - lookedUp;
		if (thisRowTrasures >= 1)
			subSearchColumns(N, thisRowTrasures, i);
		lookedUp += thisRowTrasures;
	}
}


void findTreasure(int N)
{
	int globalTreasures = getNumberOfTreasuresInArea(1, 1, N, N);
	mainSearchRows(N, globalTreasures);
}