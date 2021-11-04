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

//0 => not found
//1 => up
//2 => right
//3 => down
//4 => left
//5 => up, right
//6 => down, right
//7 => down, left
//8 => up, left
unsigned char checktarget(char fieldOfView[3][3])
{
	if (fieldOfView[0][0] == 'X')
		return 8;
	else if (fieldOfView[0][1] == 'X')
		return 4;
	else if (fieldOfView[0][2] == 'X')
		return 7;
	else if (fieldOfView[1][0] == 'X')
		return 1;
	else if (fieldOfView[1][2] == 'X')
		return 3;
	else if (fieldOfView[2][0] == 'X')
		return 5;
	else if (fieldOfView[2][1] == 'X')
		return 2;
	else if (fieldOfView[2][2] == 'X')
		return 6;
	else
		return 0;
}



void handleCaseOne()
{
	unsigned char target = checktarget(fieldOfView);

	while (target == 0)
	{
		switch (checkLetter(fieldOfView, '#'))
		{
			case 0:
			case 1:
			case 8:
				right();
				break;
			case 2:
			case 5:
				down();
				break;
			case 3:
			case 6:
				left();
				break;
			case 4:
			case 7:
				up();
		}

		target = checktarget(fieldOfView);
	}

	switch (target)
	{
		case 1:
			up();
			break;
		case 2:
			right();
			break;
		case 3:
			down();
			break;
		case 4:
			left();
			break;
		case 5:
			up();
			right();
			break;
		case 6:
			down();
			right();
			break;
		case 7:
			down();
			left();
			break;
		case 8:
			up();
			left();
	}

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