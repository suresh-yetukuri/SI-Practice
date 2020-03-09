// SubsequenceSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*
2^(N/2) + 2^(N/2) + 2^(N/2)(Log(2^(N/2))) + 2^(N/2)(Log(2^(N/2)) + Log(2^(N/2))), 2^(N/2) + 2^(N/2)
*/
namespace MeetInTheMiddle
{
    void GetSubset(vector<int>& oInput, 
        int sIdx, 
        int eIdx, 
        int oCurrentSum, 
        vector<int>& oSubsetSum)
    {
        if (sIdx == eIdx + 1)
        {
            oSubsetSum.push_back(oCurrentSum);
            return;
        }

        GetSubset(oInput, sIdx + 1, eIdx, oCurrentSum + oInput[sIdx], oSubsetSum);
        GetSubset(oInput, sIdx + 1, eIdx, oCurrentSum, oSubsetSum);
    }

    int GetSubsequenceCount(vector<int>& oInput, int oLeft, int oRight)
    {
        int oCount = 0;
        int nSize = static_cast<int>(oInput.size());
        int nLeftSize = nSize / 2;
        vector<int> oLeftSubsetSum;
        vector<int> oRightSubsetSum;
        GetSubset(oInput, 0, nLeftSize - 1, 0, oLeftSubsetSum);
        GetSubset(oInput, nLeftSize, nSize - 1, 0, oRightSubsetSum);
        sort(oRightSubsetSum.begin(), oRightSubsetSum.end());
        for (auto& val : oLeftSubsetSum)
        {
            auto oLow = lower_bound(oRightSubsetSum.begin(), oRightSubsetSum.end(), oLeft - val);
            auto oHigh = upper_bound(oRightSubsetSum.begin(), oRightSubsetSum.end(), oRight - val);
            oCount += static_cast<int>(oHigh - oLow);
        }

        return oCount;
    }
}

int main()
{
    vector<int> oInput{ 1, - 2, 3 };
    int oLeft = -1;
    int oRight = 2;
    int oResult = MeetInTheMiddle::GetSubsequenceCount(oInput, oLeft, oRight);
    cout << oResult;
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
