/*
Дано предложение, состоящее из слов, разделенных запятой
или пробелами. Среди слов встречаются слова,представляющие
код некоторого десятичного числа в 8-ой системе счисления
(признака восьмеричного кода в тексте: число начинается
с символа $: само число составлено из цифр ‘0’..’7’ ).
Сформировать массив из чисел восьмеричного кода
предварительно переведя их в десятичную систему счисления.
*/

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
#include <iostream>
#include <cstdlib>
#include <math.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

// 1 C-string //
// 2. std::string //

char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}

int Convert8To10(int value)
{
    int output = 0, i = 0;
    while(value != 0)
    {
        output += (value % 10) * pow(8,i++);
        value /= 10;
    }
    return output;
}

// 1 //
vector<int> ParseNumbersFromCString(const char* value)
{
    vector<int> numbers;
    int i = 0;
    bool flag = false;
    int startIndex = -1;
    while (value[i] != '\0')
    {
        if (flag)
        {
            if (!isdigit(value[i]))
            {
                flag = false;
                char* number8 = substr(value, startIndex, i);
                numbers.push_back(Convert8To10(atoi(number8)));
                startIndex = -1;
            }
        }
        if (value[i] == '$')
        {
            flag = true;
            startIndex = i + 1;
        }
        i++;
    }
    if (startIndex != -1)
    {
        char *number8 = substr(value, startIndex, i);
        numbers.push_back(Convert8To10(atoi(number8)));
    }
    return numbers;
}

// 2 //
vector<int> ParseNumbersFromCPPString(string value)
{
    vector<int> numbers;
    bool flag = false;
    string output;
    for (auto i : value)
    {
        if (flag)
        {
            if (isdigit(i))
                output += i;
            else
            {
                flag = false;
                numbers.push_back(Convert8To10(stoi(output)));
                output = "";
            }
        }
        if (i == '$')
            flag = true;
    }
    if (!output.empty())
        numbers.push_back(Convert8To10(stoi(output)));
    return numbers;
}

int main()
{
    // 1 C-like string //
    const char* sentence1 = "Ma$640uris nec ligula quis$23125 ipsum volut$5121675pat, laoreet vitae in ex con$12352sectetur adi$45307piscing elit";
    vector<int> mas1 = ParseNumbersFromCString(sentence1); // [416, 9813, 1352637, 5354, 19143]
    for (auto i : mas1)
        std::cout << i << std::endl;
    //

    std::cout << std::endl;

    // 2 CPP-like string //
    string sentence2 = "Ma$640uris nec ligula quis$23125 ipsum volut$5121675pat, laoreet vitae in ex con$12352sectetur adi$45307piscing elit";
    vector<int> mas2 = ParseNumbersFromCPPString(sentence2); // [416, 9813, 1352637, 5354, 19143]
    for (auto i : mas2)
        std::cout << i << std::endl;
    return 0;
    //
}