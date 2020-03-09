// CollectingWater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
N^N, 1
*/
namespace BruteForce
{
    int CollectedWater(vector<int>& oHeights)
    {
        int oVol = 0;
        int nSize = static_cast<int>(oHeights.size());
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            int maxLeft = oHeights[iCounter];
            int maxRight = oHeights[iCounter];
            int pCounter, qCounter;
            pCounter = qCounter = iCounter;
            while (pCounter >= 0) 
                maxLeft = max(maxLeft, oHeights[pCounter--]);

            while (qCounter < nSize)
                maxRight = max(maxRight, oHeights[qCounter++]); 
              
            oVol += (min(maxLeft, maxRight) - oHeights[iCounter]);
        }

        return oVol;
    }
}

/*
N+N, N+N
*/
namespace PrefixSuffixMax
{
    int CollectedWater(vector<int>& oHeights)
    {
        int oVol = 0;
        int nSize = static_cast<int>(oHeights.size());
        vector<int> oPrefixMax(nSize);
        vector<int> oSuffixMax(nSize);
        oPrefixMax[0] = oHeights[0];
        oSuffixMax[nSize - 1] = oHeights[nSize - 1];
        for (int iCounter = 1; iCounter < nSize; ++iCounter)
        { 
            oPrefixMax[iCounter] = max(oPrefixMax[iCounter - 1], oHeights[iCounter]);
            oSuffixMax[nSize - iCounter - 1] = max(oSuffixMax[nSize - iCounter], oHeights[nSize - iCounter - 1]);
        }

        for (int iCounter = 0; iCounter < nSize; ++iCounter)
            oVol += (min(oPrefixMax[iCounter], oSuffixMax[iCounter]) - oHeights[iCounter]);

        return oVol;
    }
}

/*
N+N, N
*/
namespace PrefixSuffixMaxOptimized
{
    int CollectedWater(vector<int>& oHeights)
    {
        int oVol = 0;
        int nSize = static_cast<int>(oHeights.size());
        vector<int> oPrefixMax(nSize);
        oPrefixMax[0] = oHeights[0];
        
        for (int iCounter = 1; iCounter < nSize; ++iCounter)
            oPrefixMax[iCounter] = max(oPrefixMax[iCounter - 1], oHeights[iCounter]);

        int oSuffixMax = oHeights[nSize - 1];
        for (int iCounter = nSize - 1; iCounter >= 0; --iCounter)
        {
            oSuffixMax = max(oSuffixMax, oHeights[iCounter]);
            oVol += (min(oPrefixMax[iCounter], oSuffixMax) - oHeights[iCounter]);
        }
         
        return oVol;
    }
}

int main()
{ 
    vector<int> oInput{ 1, 6, 2, 4, 5, 7, 9 };
    int oResult = PrefixSuffixMaxOptimized::CollectedWater(oInput);
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
