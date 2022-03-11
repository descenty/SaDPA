#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>
#include <map>
#include <iomanip>
#include <fstream>
#include <random>
#include <conio.h>
#include <chrono>
#include <thread>
#include <set>
#include <algorithm>

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
    const int size = 10;
    int mas[size];

    FillArray(mas, size);
    PrintArray(mas, size);
    cout << "Max at even pos: " << MaxAtEvenPos(mas, size) << endl;
}
