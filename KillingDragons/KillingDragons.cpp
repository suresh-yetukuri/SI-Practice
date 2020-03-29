// KillingDragons.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int KillingDragon(vector<int>& oDungeon, vector<int>& oDrinks)
{
    int nSize = static_cast<int>(oDungeon.size());
    int oDungeonCap = oDungeon[0];
    int oDrinkCap = oDrinks[0];
    vector<int> oPrefixDiff(nSize, (oDrinks[0] - oDungeon[0]));

    for (int iCounter = 1; iCounter < nSize; ++iCounter)
    {
        oDungeonCap += oDungeon[iCounter];
        oDrinkCap += oDrinks[iCounter];
        oPrefixDiff[iCounter] = oPrefixDiff[iCounter - 1] + (oDrinks[iCounter] - oDungeon[iCounter]);
    }

    if (oDungeonCap > oDrinkCap)
        return -1;

    bool IsNegativeExist = false;
    int iCounter = 0;
    for (iCounter = 0; iCounter < nSize; ++iCounter)
    {
        if (oPrefixDiff[iCounter] < 0)
        {
            IsNegativeExist = true;
            break;
        }
    }

    if (IsNegativeExist)
        return ((iCounter + 1) % nSize) + 1;

    return 1;
}

int main()
{
    vector<int> oDungeon{ 7, 10, 6 };
    vector<int> oDrink{ 8, 9, 7 };
    cout << KillingDragon(oDungeon, oDrink);
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
