#include <iostream>

static const int MAX_N = 1005;

static int r, c, steps, max_steps;
static char grid[MAX_N][MAX_N], fieldOfView[3][3];

static void makeFieldOfView()
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			fieldOfView[1 + i][1 + j] = grid[r + i][c + j];
}

static void move(int dx, int dy)
{
	steps++;
	if (steps > max_steps)
	{
		printf("Zu viele Schritte\n");
		exit(0);
	}
	char& here = grid[r + dy][c + dx];
	if (here == '#')
		return;
	if (here == 'X')
	{
		printf("Richtig, %d Schritte\n", steps);
		exit(0);
	}
	grid[r][c] = '.';
	here = 'S';
	r += dy, c += dx;
	makeFieldOfView();
}

void left() { move(-1, 0); }
void right() { move(1, 0); }
void up() { move(0, -1); }
void down() { move(0, 1); }

void printFielOfView(char fieldOfView[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << fieldOfView[i][j];
		}
		std::cout << std::endl;
	}
}

//bit position
// 1 2 3
// 4 x 5
// 6 7 8  => 1 2 3 4 5 6 7 8
// every bit is responsible for a wall piece begining from up/left to down/right
unsigned char checkObject(char objectLetter)
{
	unsigned char map = 0b00000000;

	if (fieldOfView[0][0] == objectLetter)
		map |= 0b00000001; // 1 (1)
	if (fieldOfView[0][1] == objectLetter)
		map |= 0b00000010; // 2 (2)
	if (fieldOfView[0][2] == objectLetter)
		map |= 0b00000100; // 4 (3)
	if (fieldOfView[1][0] == objectLetter)
		map |= 0b00001000; // 8 (4)
	if (fieldOfView[1][2] == objectLetter)
		map |= 0b00010000; // 16 (5)
	if (fieldOfView[2][0] == objectLetter)
		map |= 0b00100000; // 32 (6)
	if (fieldOfView[2][1] == objectLetter)
		map |= 0b01000000; // 64 (7)
	if (fieldOfView[2][2] == objectLetter)
		map |= 0b10000000; // 128 (8)

	return map;
}

void followTarget(unsigned char targetMap)
{
	if ((targetMap & 7) > 0) // target in one of the three upper locations
	{
		up();

		if ((targetMap & 1) > 0) // up, left
			left();
		else if ((targetMap & 4) > 0) // up, right
			right();
	}
	else if ((targetMap & 224)) // target in one of the three bottom locations
	{
		down();

		if ((targetMap & 32) > 0) // down, left
			left();
		else if ((targetMap & 128) > 0) // down, right
			right();
	}
	else if ((targetMap & 16) > 0) // right
		right();
	else // left
		left();
}


void handleCaseOne()
{
	unsigned char targetMap = checkObject('X');

	while (targetMap == 0)
	{
		unsigned char wallMap = checkObject('#');
		if ((wallMap & 16) > 0) // right wall
		{
			if ((wallMap & 64) > 0) // bottom wall
				left();
			else
				down();
		}
		else if ((wallMap & 8) > 0) // left wall
		{
			if ((wallMap & 2) > 0) // top wall
				right();
			else
				up();
		}
		else if ((wallMap & 64) > 0) // bottom wall
			left();
		else
			right();

		targetMap = checkObject('X');
	}

	followTarget(targetMap);
}

void handleCaseTow()
{
	//0 => didn't start yet
	//1 => right
	//2 => left
	unsigned char direction = 0;

	unsigned char targetMap = checkObject('X');

	while (targetMap == 0)
	{
		unsigned char wallMap = checkObject('#');

		//didn't start yet (Go to corner upper left)
		if (direction == 0)
		{
			//is in upper left corner
			if ((wallMap & 10) == 10)
				direction = 1;
			else if ((wallMap & 8) > 0)
				up();
			else if ((wallMap & 2) > 0)
				left();
			else
			{
				up();
				left();
			}
		}
		else if (direction == 1)
		{
			//wall on the right
			if ((wallMap & 16) > 0)
			{
				down();
				direction = 2;
			}
			else
				right();
		}
		else
		{
			if ((wallMap & 8) > 0)
			{
				down();
				direction = 1;
			}
			else
				left();
		}
	}
	followTarget(targetMap);
}

void handleCaseThree()
{
	unsigned char targetMap = checkObject('X');

	while (targetMap == 0)
	{
		unsigned char wallMap = checkObject('#');


	}
	followTarget(targetMap);
}

void findExit(int subtask, char fieldOfView[3][3])
{
	// Implementiere deine Loesung hier

	// Du kannst mit left(), right(), up() und down() 
	// Dr. Rainer steuern. Das fieldOfView Array
	// aktualisiert sich dann automatisch

	//printFielOfView(fieldOfView);
	switch (subtask) {
	case 1:
		handleCaseOne();
		break;
	case 2:
		handleCaseTow();
		break;
	case 3:
		handleCaseThree();
		break;
	}
}

int main()
{
	int s, n, m;
	std::cin >> s >> n >> m;
	max_steps = 2000000;
	for (int i = 0; i < n; i++)
	{
		std::cin >> grid[i];
		for (int j = 0; j < m; j++)
			if (grid[i][j] == 'S')
				r = i, c = j;
	}
	makeFieldOfView();
	findExit(s, fieldOfView);
	printf("Ausgang nicht gefunden\n");
	return 0;
}