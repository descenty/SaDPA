#include <iostream>

using namespace std;

void InputMatrix(int** a, int rows, int cols)
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
		cout << endl;
	}
}

void PrintMatrix(int** a, int rows, int cols)
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

int** MultiplyMatrix(int** a, int A_rows, int A_cols, int** b, int B_rows, int B_cols)
{
	if (A_cols != B_rows)
	{
		cout << "Can't be multiplied\n";
		return 0;
	}

	int** c = new int* [A_rows];
	for (int i = 0; i < A_rows; i++)
		c[i] = new int[B_cols];

	for (int i = 0; i < A_rows; i++)
	{
		for (int j = 0; j < B_cols; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < A_cols; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	return c;
}

int main()
{
	int A_rows, A_cols;
	cout << "Input Matrix A size:\n";
	cout << "Rows: ";
	cin >> A_rows;
	cout << "Cols: ";
	cin >> A_cols;
	int** a = new int* [A_rows];
	for (int i = 0; i < A_rows; i++)
		a[i] = new int[A_cols];
	InputMatrix(a, A_rows, A_cols);
	cout << "Matrix A:\n";
	PrintMatrix(a, A_rows, A_cols);
	
	int B_rows, B_cols;
	cout << "Input Matrix B size:\n";
	cout << "Rows: ";
	cin >> B_rows;
	cout << "Cols: ";
	cin >> B_cols;
	int** b = new int* [B_rows];
	for (int i = 0; i < B_rows; i++)
		b[i] = new int[B_cols];
	InputMatrix(b, B_rows, B_cols);

	cout << "Matrix B:\n";
	PrintMatrix(b, B_rows, B_cols);
	cout << "Matrix c:\n";
	PrintMatrix(MultiplyMatrix(a, A_rows, A_cols, b, B_rows, B_cols), A_rows, B_cols);
}