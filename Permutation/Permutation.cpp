// Permutation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Permute(string& oInput, int oFixIdx, int oEndIdx)
{
    if (oFixIdx == oEndIdx)
    {
        cout << oInput << endl;
        return;
    }
    
    for (int iCounter = oFixIdx + 1; iCounter <= oEndIdx; ++iCounter)
    {
        swap(oInput[oFixIdx], oInput[iCounter]);
        Permute(oInput, oFixIdx + 1, oEndIdx);
        swap(oInput[oFixIdx], oInput[iCounter]);
    }
}

int main()
{
    // vector<int> oInput{ 1, 2, 3 };
    // vector<vector<int>> oResult;
    // oResult.push_back(vector<int>{oInput});
    // oInput[1] = 90;
   string oInput{ "ABC" };
   Permute(oInput, 0, oInput.size() - 1);
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
