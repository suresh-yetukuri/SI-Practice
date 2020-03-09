// FirstRepeatingCharacter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
N^2, 1
*/
namespace BruteForce
{
    char GetFirstRepeatingChar(string& oInput)
    {
        int nSize = static_cast<int>(oInput.size());

        for (int iCounter = 0; iCounter < nSize - 1; ++iCounter)
        {
            char oTargetChar = oInput[iCounter];
            for (int jCounter = iCounter + 1; jCounter < nSize; ++jCounter)
            {
                if (oTargetChar == oInput[jCounter])
                    return oTargetChar;
            }
        }
           
        return '.';
    }
}

/*
N + N, 26
*/
namespace CountArray
{
    char GetFirstRepeatingChar(string& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        vector<int> oCountArray(26, 0);
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
            oCountArray[oInput[iCounter] - 'a']++;

        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            if (oCountArray[oInput[iCounter] - 'a'] > 1)
                return oInput[iCounter];
        }

        return '.';
    }
}

int main()
{
    string s{ "algorithms" };
    cout << CountArray::GetFirstRepeatingChar(s);
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
