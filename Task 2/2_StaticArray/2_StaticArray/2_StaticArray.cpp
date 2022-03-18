#define MAX_ROWS 3
#define MAX_COLS 3

#include <iostream>

using namespace std;

void InputMatrix(int a[][MAX_COLS], int rows, int cols)
{
	cout << "Matrix fill (1 - random input, 2 - keyboard input): ";
	int c;
	cin >> c;
	switch (c)
	{
	case 1:
		for (int y = 0; y < rows; y++)
			for (int x = 0; x < cols; x++)
				a[y][x] = rand() % (101);
		break;
	case 2:
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				printf("[%d][%d]: ", y, x);
				cin >> a[y][x];
			}
			if (y != rows - 1)
				cout << endl;
		}
		break;
	}
	cout << endl;
}

void PrintMatrix(int a[][MAX_COLS], int rows, int cols)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			cout << a[y][x];
			if (x != cols - 1)
				cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void MultiplyMatrix(int c[][MAX_COLS], int a[][MAX_COLS], int rows1, int cols1, int b[][MAX_COLS], int rows2, int cols2)
{
	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols2; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < cols1; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

int main()
{
	int A_rows = 3;
	int A_cols = 2;
	printf("Matrix A size: %dx%d\n", A_rows, A_cols);
	int a[MAX_ROWS][MAX_COLS];
	InputMatrix(a, A_rows, A_cols);

	int B_rows = 2;
	int B_cols = 3;
	printf("Matrix B size: %dx%d\n", B_rows, B_cols);
	int b[MAX_ROWS][MAX_COLS];
	InputMatrix(b, B_rows, B_cols);

	cout << "Matrix A:\n";
	PrintMatrix(a, A_rows, A_cols);
	cout << "Matrix B:\n";
	PrintMatrix(b, B_rows, B_cols);

	if (A_cols != B_rows)
	{
		cout << "Can't be multiplied\n";
		return 0;
	}

	int C_rows = A_rows;
	int C_cols = B_cols;
	int c[MAX_ROWS][MAX_COLS];

	MultiplyMatrix(c, a, A_rows, A_cols, b, B_rows, B_cols);

	cout << "Matrix C:\n";
	PrintMatrix(c, C_rows, C_cols);
}