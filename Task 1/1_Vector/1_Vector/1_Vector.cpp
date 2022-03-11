#include <iostream>
#include <vector>
#include <string>
using namespace std;

void FillVector(vector <int>& mas)
{
    cout << "Vector size: ";
    int size;
    cin >> size;
    int x;
    for (int i = 0; i < size; i++)
    {
        cin >> x;
        mas.push_back(x);
    }
}

void PrintVector(vector <int> mas)
{
    for (int i = 0; i < size(mas); i++)
        cout << mas[i] << ' ';
    cout << endl;
}

int MaxAtEvenPos(vector <int> mas)
{
    int maxValue = 0;
    for (int i = 1; i < size(mas); i += 2)
        maxValue = max(mas[i], maxValue);
    return maxValue;
}

void RemoveAllEven(vector <int>& mas)
{
    mas.erase(remove_if(mas.begin(), mas.end(), [](int x) {return x % 2 == 0; }), mas.end());
}

void InsertAfterEvenDigits(vector <int>& mas)
{
    cout << "New element: ";
    int x;
    cin >> x;
    for (int i = 0; i < size(mas); i++)
    {
        if (to_string(mas[i]).length() % 2 == 0)
        {
            mas.insert(mas.begin() + i, x);
            break;
        }
    }
}


int main()
{
    vector <int> mas;
    FillVector(mas);
    cout << "Max at even: " << MaxAtEvenPos(mas) << endl;
    RemoveAllEven(mas);
    cout << "Remove all even: " << endl;
    PrintVector(mas);
    InsertAfterEvenDigits(mas);
    PrintVector(mas);
}