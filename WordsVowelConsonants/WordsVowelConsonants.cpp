// WordsVowelConsonants.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

bool IsValidChar(char& c)
{
    return ('\0' != c) && (32 != c);
}

void CountWVC(string& oInput, unordered_set<char>& oHashVowels)
{
    int oWordCount = 0;
    int oVowelsCount = 0;
    int oConsonantCount = 0;
    oInput.push_back('\0');
    int nSize = static_cast<int>(oInput.size());
    int pCounter = 0;

    // Traverse till u find first valid char
    // because we are not interested in any
    // part which is before valid char
    while (!IsValidChar(oInput[pCounter]))
        ++pCounter;

    while (pCounter < nSize)
    {
        if (IsValidChar(oInput[pCounter]))
        {
            if (oHashVowels.find(oInput[pCounter]) != oHashVowels.end())
                ++oVowelsCount;
            else
                ++oConsonantCount;

            ++pCounter;
        }
        else
        {
            while ((pCounter < nSize) && !IsValidChar(oInput[pCounter]))
                ++pCounter;

            ++oWordCount;
        }
    }
     
    cout << oWordCount << " " << oVowelsCount << " " << oConsonantCount << endl;
}

int main()
{
    string oInput{ "  Exception" };
    unordered_set<char> oHashVowels{ 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
    CountWVC(oInput, oHashVowels);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
