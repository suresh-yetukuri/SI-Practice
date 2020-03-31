// KillingDragons.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
N^2, N
*/
namespace BruteForce
{
    int KillingDragon(vector<int>& oDungeon, vector<int>& oDrinks)
    {
        int nSize = static_cast<int>(oDungeon.size());
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            int oDungeonCap = oDungeon[iCounter];
            int oDrinkCap = oDrinks[iCounter];
            vector<int> oPrefixDiff(nSize, (oDrinks[iCounter] - oDungeon[iCounter]));
            int oNegativeCount = oPrefixDiff[iCounter] < 0 ? 1 : 0;
            if (oNegativeCount == 0) {
                for (int jCounter = ((iCounter + 1) % nSize); ((jCounter < nSize) && (jCounter != iCounter)); jCounter = ((jCounter + 1) % nSize)) {
                    oDungeonCap += oDungeon[jCounter];
                    oDrinkCap += oDrinks[jCounter];
                    oPrefixDiff[jCounter] = oPrefixDiff[(jCounter + nSize - 1) % nSize] + (oDrinks[jCounter] - oDungeon[jCounter]);
                    if (oPrefixDiff[jCounter] < 0)
                        ++oNegativeCount;
                }
                if (oDungeonCap > oDrinkCap)
                    return -1;

                if (oNegativeCount == 0)
                    return iCounter + 1;
            }
            else {
                continue;
            }
        }

        return -1;
    }
}


namespace Optimized
{
    int KillingDragon(vector<int>& oDungeon, vector<int>& oDrinks)
    {
        int nSize = static_cast<int>(oDungeon.size());
        int oDungeonCap = oDungeon[0];
        int oDrinkCap = oDrinks[0];
        vector<int> oPrefixDiff(nSize, (oDrinks[0] - oDungeon[0]));
        int LastPositiveIdx = oPrefixDiff[0] < 0 ? -2 : 0;
        for (int jCounter = 1; jCounter < nSize; ++jCounter) {
            oDungeonCap += oDungeon[jCounter];
            oDrinkCap += oDrinks[jCounter];
            oPrefixDiff[jCounter] = oPrefixDiff[(jCounter + nSize - 1) % nSize] + (oDrinks[jCounter] - oDungeon[jCounter]);
            if (oPrefixDiff[jCounter] < 0)
                LastPositiveIdx = -2;
            else
            {
                if (LastPositiveIdx == -2)
                    LastPositiveIdx = jCounter;
            }
        }

        return LastPositiveIdx + 1;
    }
}

int main()
{
    vector<int> oDungeon{ 1, 5, 7 };
    vector<int> oDrink{ 2, 6, 3 };
    cout << Optimized::KillingDragon(oDungeon, oDrink);
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
