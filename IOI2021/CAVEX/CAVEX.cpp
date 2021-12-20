#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

static const int MAX_N = 1005;

static int r, c, steps, max_steps;
static char grid[MAX_N][MAX_N], fieldOfView[3][3];

static char walkedXY[2000][2000] = { 0 };

// Prototypes
void moveToAdapter(unsigned char moveTo, char walkedXY[2000][2000], int& positionX, int& positionY);
void validateAndMove(char fieldOfView[3][3], unsigned char moveTo, char walkedXY[2000][2000], int& positionX, int& positionY);
void findFinish(char fieldOfView[3][3], unsigned char fromDirection, char walkedXY[2000][2000], int& positionX, int& positionY);
unsigned char isDirectionAvailable(char fieldOfView[3][3], unsigned char moveTo, char walkedXY[2000][2000], int& positionX, int& positionY);
unsigned char invertFrom(unsigned char moveTo);

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
unsigned char finishInView(char fieldOfView[3][3])
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

void moveToAdapter(unsigned char moveTo, char walkedXY[2000][2000], int &positionX, int &positionY)
{
	switch (moveTo)
	{
	case 1:
		// Move left.
		positionX--;
		left();
		break;
	case 2:
		// Move down.
		positionY--;
		down();
		break;
	case 3:
		// Move right.
		positionX++;
		right();
		break;
	case 4:
		// Move up.
		positionY++;
		up();
		break;
	}

	walkedXY[positionX][positionY] = 1;
}

void validateAndMove(char fieldOfView[3][3], unsigned char moveTo, char walkedXY[2000][2000], int &positionX, int &positionY)
{
	if (!isDirectionAvailable(fieldOfView, moveTo, walkedXY, positionX, positionY))
		return;

	moveToAdapter(moveTo, walkedXY, positionX, positionY);
	findFinish(fieldOfView, invertFrom(moveTo), walkedXY, positionX, positionY);
}

void findFinish(char fieldOfView[3][3], unsigned char fromDirection, char walkedXY[2000][2000], int &positionX, int &positionY)
{
	// Check if finish is in view
	unsigned char finish = finishInView(fieldOfView);
	if (finish != 0)
	{
		moveToAdapter(finish, walkedXY, positionX, positionY);
		finish = finishInView(fieldOfView);
		moveToAdapter(finish, walkedXY, positionX, positionY);
		throw;	// Throw if this code is reached => Already found finish
	}

	//If there is no next step => return
	validateAndMove(fieldOfView, 1, walkedXY, positionX, positionY);
	validateAndMove(fieldOfView, 2, walkedXY, positionX, positionY);
	validateAndMove(fieldOfView, 3, walkedXY, positionX, positionY);
	validateAndMove(fieldOfView, 4, walkedXY, positionX, positionY);

	moveToAdapter(fromDirection, walkedXY, positionX, positionY);
}

unsigned char isDirectionAvailable(char fieldOfView[3][3], unsigned char moveTo, char walkedXY[2000][2000], int &positionX, int &positionY)
{
	switch (moveTo)
	{
		case 1:
			// Move left.
			if (walkedXY[positionX - 1][positionY] == 1)
				return 0;
			if (fieldOfView[1][0] != '.')
				return 0;
			break;
		case 2:
			// Move down.
			if (walkedXY[positionX][positionY-1] == 1)
				return 0;
			if (fieldOfView[2][1] != '.')
				return 0;
			break;
		case 3:
			// Move right.
			if (walkedXY[positionX + 1][positionY] == 1)
				return 0;
			if (fieldOfView[1][2] != '.')
				return 0;
			break;
		case 4:
			// Move up.
			if (walkedXY[positionX][positionY+1] == 1)
				return 0;
			if (fieldOfView[0][1] != '.')
				return 0;
			break;
	}

	return 1;
}

unsigned char invertFrom(unsigned char moveTo)
{
	switch (moveTo)
	{
		case 1:
			return 3;
		case 2:
			return 4;
		case 3:
			return 1;
		case 4:
			return 2;
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
	int positionX = 1000;
	int positionY = 1000;
	walkedXY[1000][1000] = 1;
	findFinish(fieldOfView, 1, walkedXY, positionX, positionY);
	printf("Ausgang nicht gefunden\n");

	return 0;
}