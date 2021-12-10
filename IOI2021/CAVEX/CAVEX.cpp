#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

static const int MAX_N = 1005;

static int r, c, steps, max_steps;
static char grid[MAX_N][MAX_N], fieldOfView[3][3];

static char walkedX[2000], walkedY[2000] = { 0 };

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

// left		=> 1
// down		=> 2
// right	=> 3
// up		=> 4
unsigned char getNextDirection(char fieldOfView[3][3])
{
	// Next To Finish
	if (fieldOfView[0][1] == 'X') // up
		return 4;
	if (fieldOfView[2][1] == 'X') // down
		return 2;
	if (fieldOfView[1][0] == 'X') // left
		return 1;
	if (fieldOfView[1][2] == 'X') // right
		return 3;

	// Finish in Corners
	if (fieldOfView[0][0] == 'X')
	{
		if (fieldOfView[0][1] != '#') // up
			return 4;
		if (fieldOfView[1][0] != '#') // left
			return 1;
	}
	else if (fieldOfView[0][2] == 'X')
	{
		if (fieldOfView[0][1] != '#') // up
			return 4;
		if (fieldOfView[1][2] != '#') // right
			return 3;
	}
	else if (fieldOfView[2][2] == 'X')
	{
		if (fieldOfView[1][2] != '#') // right
			return 3;
		if (fieldOfView[2][1] != '#') // down
			return 2;
	}
	else if (fieldOfView[2][0] == 'X')
	{
		if (fieldOfView[1][0] != '#') // left
			return 1;
		if (fieldOfView[2][1] != '#') // down
			return 2;
	}

	return 0;
}

void findExit(int subtask, char fieldOfView[3][3], unsigned char fromDirection, char walkedX[2000], char walkedY[2000])
{
	// Cod
	
	unsigned char nextDirection = getNextDirection(fieldOfView);

	if (nextDirection != 0)
		moveToAdapter(nextDirection);


	// Finish not Found
	// Rekursiv call
	findExit(subtask, fieldOfView, 1, walkedX, walkedY);
	findExit(subtask, fieldOfView, 2, walkedX, walkedY);
	findExit(subtask, fieldOfView, 3, walkedX, walkedY);
	findExit(subtask, fieldOfView, 4, walkedX, walkedY);

	// Step back


}

void moveToAdapter(unsigned char direction)
{
	switch (direction)
	{
		case 1:
			// Move left.
			left();
			break;
		case 2:
			// Move down.
			down();
			break;
		case 3:
			// Move right.
			right();
			break;
		case 4:
			// Move up.
			up();
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