#include <iostream>

using namespace std;

void FillArray(int mas[], int n)
{
    for (int i = 0; i < n; i++)
        cin >> mas[i];
}

void PrintArray(int mas[], int n)
{
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;
}

int MaxAtEvenPos(int mas[], int n)
{
    int maxValue = 0;
    for (int i = 1; i < n; i += 2)
        maxValue = max(mas[i], maxValue);
    return maxValue;
}

int main()
{
    int size = 10;
    int* mas = new int[size];

    FillArray(mas, size);
    PrintArray(mas, size);
    cout << "Max at even pos: " << MaxAtEvenPos << endl;
}
