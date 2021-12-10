#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

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
		std::cout << '\n';
	}
}

unsigned char viewToVectorSight(char field)
{
	switch (field)
	{
	case '#':
		return 10;
		break;
	case 'X':
		return 20;
		break;
	case '.':
		return 30;
		break;
	case 'S':
		return 40;
		break;
	}
}

unsigned char vectorToViewSight(char field)
{
	if (field >= 10 && field < 20)
		return '#';
	if (field >= 20 && field < 30)
		return 'X';
	if (field >= 30 && field < 40)
		return '.';
	if (field >= 40 && field < 50)
		return 'S';

	return 'O';
}

void drawField(std::vector<std::vector<unsigned char>>& vectorField)
{
	std::cout << "\033[2J";
	for (int i = 0; i < vectorField.size(); i++)
	{
		for (int j = 0; j < vectorField[0].size(); j++)
		{
			std::cout << vectorToViewSight(vectorField[i][j]);
		}
		std::cout << '\n';
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

#pragma region DecisionMaking

// left		=> 1
// down		=> 2
// right	=> 3
// up		=> 4
std::vector<unsigned char> getAvailableDirections(unsigned char** vectorFieldOfView)
{
	// Next To Finish
	if (vectorFieldOfView[0][1] == 20) // up
		return { 4 };
	if (vectorFieldOfView[2][1] == 20) // down
		return { 2 };
	if (vectorFieldOfView[1][0] == 20) // left
		return { 1 };
	if (vectorFieldOfView[1][2] == 20) // right
		return { 3 };

	// Finish in Corners
	if (vectorFieldOfView[0][0] == 20)
	{
		if (vectorFieldOfView[0][1] % 30 == 0) // up
			return { 4 };
		if (vectorFieldOfView[1][0] % 30 == 0) // left
			return { 1 };
	}
	else if (vectorFieldOfView[0][2] == 20)
	{
		if (vectorFieldOfView[0][1] % 30 == 0) // up
			return { 4 };
		if (vectorFieldOfView[1][2] % 30 == 0) // right
			return { 3 };
	}
	else if (vectorFieldOfView[2][2] == 20)
	{
		if (vectorFieldOfView[1][2] % 30 == 0) // right
			return { 3 };
		if (vectorFieldOfView[2][1] % 30 == 0) // down
			return { 2 };
	}
	else if (vectorFieldOfView[2][0] == 20)
	{
		if (vectorFieldOfView[1][0] % 30 == 0) // left
			return { 1 };
		if (vectorFieldOfView[2][1] % 30 == 0) // down
			return { 2 };
	}

	// No Finish in sight
	std::vector<unsigned char> directions;
	if (vectorFieldOfView[0][1] % 30 == 0) // up
		directions.push_back(4);
	if (vectorFieldOfView[2][1] % 30 == 0) // down
		directions.push_back(2);
	if (vectorFieldOfView[1][0] % 30 == 0) // left
		directions.push_back(1);
	if (vectorFieldOfView[1][2] % 30 == 0) // right
		directions.push_back(3);

	return directions;
}

// left		=> 1
// down		=> 2
// right	=> 3
// up		=> 4
unsigned char getNextStep(unsigned char** vectorFieldOfView)
{
	std::vector<unsigned char> directions = getAvailableDirections(vectorFieldOfView);

	// no unvisited direction was found
	if (directions.size() < 1)
		// go back
		return (vectorFieldOfView[1][1] % 10);
	else if (directions.size() == 1)
		return directions[0];
	else
	{
		std::srand(std::time(0));
		unsigned char randIndex = std::rand() % directions.size();
		return directions[randIndex];
	}
}

#pragma endregion


#pragma region Movement

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

void vectorMoveTo(std::vector<std::vector<unsigned char>>& vectorField, unsigned char direction, int* playerPosition)
{
	drawField(vectorField);
	switch (direction)
	{
	case 1:	// Left
		left();
		playerPosition[1]--;	// X--
		if (playerPosition[1] == 0)	// Resize Vector Front
		{
			for (int i = 0; i < vectorField.size(); i++)
				vectorField[i].insert(vectorField[i].begin(), 0);
			playerPosition[1]++;	// Reset Player Position because adding row led to offset
		}
		vectorField[playerPosition[0] - 1][playerPosition[1] - 1] = (vectorField[playerPosition[0] - 1][playerPosition[1] - 1] == 0)
			? viewToVectorSight(fieldOfView[0][0])
			: vectorField[playerPosition[0] - 1][playerPosition[1] - 1];	// X 0 0
		vectorField[playerPosition[0]][playerPosition[1] - 1] = (vectorField[playerPosition[0]][playerPosition[1] - 1] == 0)
			? viewToVectorSight(fieldOfView[1][0])
			: vectorField[playerPosition[0]][playerPosition[1] - 1];		// X 0 0
		vectorField[playerPosition[0] + 1][playerPosition[1] - 1] = (vectorField[playerPosition[0] + 1][playerPosition[1] - 1] == 0)
			? viewToVectorSight(fieldOfView[2][0])
			: vectorField[playerPosition[0] + 1][playerPosition[1] - 1];	// X 0 0
		if (vectorField[playerPosition[0]][playerPosition[1]] % 10 == 0)
			vectorField[playerPosition[0]][playerPosition[1]] = 43;	// Came from
		break;
	case 2:	// Down
		down();
		playerPosition[0]++;	// Y++
		if (playerPosition[0] == (vectorField.size() - 1))	// Resize Vector Bottom
		{
			vectorField.insert(vectorField.end(), std::vector<unsigned char>(0));
			for (int i = 0; i < vectorField[1].size(); i++)
				vectorField[vectorField.size() - 1].push_back(0);
		}
		vectorField[playerPosition[0] + 1][playerPosition[1] - 1] = (vectorField[playerPosition[0] + 1][playerPosition[1] - 1] == 0)
			? viewToVectorSight(fieldOfView[2][0])
			: vectorField[playerPosition[0] + 1][playerPosition[1] - 1];	// 0 0 0
		vectorField[playerPosition[0] + 1][playerPosition[1]] = (vectorField[playerPosition[0] + 1][playerPosition[1]] == 0)
			? viewToVectorSight(fieldOfView[2][1])
			: vectorField[playerPosition[0] + 1][playerPosition[1]];		// 0 0 0
		vectorField[playerPosition[0] + 1][playerPosition[1] + 1] = (vectorField[playerPosition[0] + 1][playerPosition[1] + 1] == 0)
			? viewToVectorSight(fieldOfView[2][2])
			: vectorField[playerPosition[0] + 1][playerPosition[1] + 1];	// X X X
		if (vectorField[playerPosition[0]][playerPosition[1]] % 10 == 0)
			vectorField[playerPosition[0]][playerPosition[1]] = 44;	// Came from
		break;
	case 3:	// Right
		right();
		playerPosition[1]++;	// X++
		if (playerPosition[1] == (vectorField[0].size() - 1)) // Resize Vector Back
		{
			for (int i = 0; i < vectorField.size(); i++)
				vectorField[i].insert(vectorField[i].end(), 0);
		}
		vectorField[playerPosition[0] - 1][playerPosition[1] + 1] = (vectorField[playerPosition[0] - 1][playerPosition[1] + 1] == 0)
			? viewToVectorSight(fieldOfView[0][2])
			: vectorField[playerPosition[0] - 1][playerPosition[1] + 1];	// 0 0 X
		vectorField[playerPosition[0]][playerPosition[1] + 1] = (vectorField[playerPosition[0]][playerPosition[1] + 1] == 0)
			? viewToVectorSight(fieldOfView[1][2])
			: vectorField[playerPosition[0]][playerPosition[1] + 1];		// 0 0 X
		vectorField[playerPosition[0] + 1][playerPosition[1] + 1] = (vectorField[playerPosition[0] + 1][playerPosition[1] + 1] == 0)
			? viewToVectorSight(fieldOfView[2][2])
			: vectorField[playerPosition[0] + 1][playerPosition[1] + 1];	// 0 0 X
		if (vectorField[playerPosition[0]][playerPosition[1]] % 10 == 0)
			vectorField[playerPosition[0]][playerPosition[1]] = 41;	// Came from
		break;
	case 4:	// Up
		up();
		playerPosition[0]--;	// Y--
		if (playerPosition[0] == 0)	// Resize Vector Top
		{
			vectorField.insert(vectorField.begin(), std::vector<unsigned char>(0));
			for (int i = 0; i < vectorField[1].size(); i++)
				vectorField[0].push_back(0);

			playerPosition[0]++;	// Reset Player Position because adding row led to offset
		}
		vectorField[playerPosition[0] - 1][playerPosition[1] - 1] = (vectorField[playerPosition[0] - 1][playerPosition[1] - 1] == 0)
			? viewToVectorSight(fieldOfView[0][0])
			: vectorField[playerPosition[0] - 1][playerPosition[1] - 1];	// X X X
		vectorField[playerPosition[0] - 1][playerPosition[1]] = (vectorField[playerPosition[0] - 1][playerPosition[1]] == 0)
			? viewToVectorSight(fieldOfView[0][1])
			: vectorField[playerPosition[0] - 1][playerPosition[1]];		// 0 0 0
		vectorField[playerPosition[0] - 1][playerPosition[1] + 1] = (vectorField[playerPosition[0] - 1][playerPosition[1] + 1] == 0)
			? viewToVectorSight(fieldOfView[0][2])
			: vectorField[playerPosition[0] - 1][playerPosition[1] + 1];	// 0 0 0
		if (vectorField[playerPosition[0]][playerPosition[1]] % 10 == 0)
			vectorField[playerPosition[0]][playerPosition[1]] = 42;	// Came from
		break;
	}

	vectorMoveTo(vectorField, getNextStep(vectorFieldOfView(vectorField, playerPosition)), playerPosition);
}

#pragma endregion

void findExit(int subtask, char fieldOfView[3][3])
{
	int playerPosition[] = { 1,1 };

	std::vector<std::vector<unsigned char>> vectorField;
	for (unsigned char i = 0; i < 3; i++)
	{
		std::vector<unsigned char> temp;
		for (unsigned char j = 0; j < 3; j++)
		{
			temp.push_back(0);
			temp[j] = viewToVectorSight(fieldOfView[i][j]);
		}
		vectorField.push_back(temp);
	}

	vectorMoveTo(vectorField, getNextStep(vectorFieldOfView(vectorField, playerPosition)), playerPosition);
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