#include <iostream>
#include <vector>

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

#pragma region Simon

unsigned char** vectorFieldOfView(std::vector<std::vector<unsigned char>> vectorField, int* playerPosition)
{
	unsigned char** newFieldOfView = 0;
	newFieldOfView = new unsigned char* [3];
	for (unsigned char i = 0; i < 3; i++)
		newFieldOfView[i] = new unsigned char[3];

	newFieldOfView[0][0] = vectorField[playerPosition[0] - 1][playerPosition[1] - 1];
	newFieldOfView[0][1] = vectorField[playerPosition[0] - 1][playerPosition[1]];
	newFieldOfView[0][2] = vectorField[playerPosition[0] - 1][playerPosition[1] + 1];
	newFieldOfView[1][0] = vectorField[playerPosition[0]][playerPosition[1] - 1];
	newFieldOfView[1][1] = vectorField[playerPosition[0]][playerPosition[1]];
	newFieldOfView[1][2] = vectorField[playerPosition[0]][playerPosition[1] + 1];
	newFieldOfView[2][0] = vectorField[playerPosition[0] + 1][playerPosition[1] - 1];
	newFieldOfView[2][1] = vectorField[playerPosition[0] + 1][playerPosition[1]];
	newFieldOfView[2][2] = vectorField[playerPosition[0] + 1][playerPosition[1] + 1];
	return newFieldOfView;
}

void vectorMoveTo(std::vector<std::vector<unsigned char>> &vectorField, unsigned char direction, int* playerPosition)
{
	switch (direction)
	{
	case 1:	// Left
		left();
		playerPosition[1]--;	// X--
		if (playerPosition[1] == 0)	// Resize Vector Front
		{
			for (int i = 0; i < vectorField.size(); i++)
				vectorField[i].insert(vectorField[i].begin(), 0);

			vectorField[playerPosition[0] - 1][playerPosition[1] - 1];
		}
		break;
	case 2:	// Down
		down();
		playerPosition[0]++;	// Y++
		if (playerPosition[0] == (vectorField.size() - 1))	// Resize Vector Bottom
		{
			vectorField.insert(vectorField.end(), std::vector<unsigned char>(0));
			for (int i = 0; i < vectorField[1].size(); i++)
				vectorField[vectorField.size()-1].push_back(0);


		}
		break;
	case 3:	// Right
		right();
		playerPosition[1]++;	// X++
		if (playerPosition[1] == (vectorField[0].size() - 1)) // Resize Vector Back
		{
			for (int i = 0; i < vectorField.size(); i++)
				vectorField[i].insert(vectorField[i].end(), 0);


		}
		break;
	case 4:	// Up
		up();
		playerPosition[0]--;	// Y--
		if (playerPosition[0] == 0)	// Resize Vector Top
		{
			vectorField.insert(vectorField.begin(), std::vector<unsigned char>(0));
			for (int i = 0; i < vectorField[1].size(); i++)
				vectorField[0].push_back(0);


		}
		break;
	}
}

#pragma endregion

void findExit(int subtask, char fieldOfView[3][3])
{
	int playerPosition[] = { 1,1 };

	std::vector<std::vector<unsigned char>> vectorField;
	for (unsigned char i = 0; i < 3; i++)
	{
		std::vector<unsigned char> temp;
		for (unsigned char i = 0; i < 3; i++)
		{
			temp.push_back(0);
		}
		vectorField.push_back(temp);
	}

	vectorMoveTo(vectorField, 4, playerPosition);
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