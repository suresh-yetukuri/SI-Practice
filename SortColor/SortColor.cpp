// SortColor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

void SortColor(vector<int>& oInput)
{
    int nSize = static_cast<int>(oInput.size());
    int xCounter = 0;
    int yCounter = nSize - 1;
    int iCounter = 0;
    
    while (iCounter <= yCounter)
    {
        if (oInput[iCounter] == 0)
        {
            swap(oInput[iCounter], oInput[xCounter]);
            ++xCounter;
            ++iCounter;
        }
        else if (oInput[iCounter] == 2)
        {
            swap(oInput[iCounter], oInput[yCounter]);
            --yCounter;
        }
        else
            ++iCounter;
    }
}

int main()
{
    vector<int> oInput{ 1,2,0,1,2,0,2,1,0,0,2 };
    SortColor(oInput);
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
