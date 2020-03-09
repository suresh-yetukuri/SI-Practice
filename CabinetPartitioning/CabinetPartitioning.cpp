// CabinetPartitioning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
(n-1)C(k-1) * n, (n-1)C(k-1)
*/
namespace BruteForce
{
    int ComputeTimeTaken(vector<int>& oTasks, vector<int>& oPartition)
    {
        int oTotalTime = INT_MIN;
        int oCurrentPartitionTime = 0;
        int jCounter = 0;
        int oPartitionCount = static_cast<int>(oPartition.size());
        int oTaskCount = static_cast<int>(oTasks.size());

        for (int iCounter = 0; iCounter < oPartitionCount; ++iCounter)
        {
            oCurrentPartitionTime = 0;
            while ((jCounter <= oPartition[iCounter]) && (jCounter < oTaskCount))
            {
                oCurrentPartitionTime += oTasks[jCounter];
                ++jCounter;
            }

            oTotalTime = max(oTotalTime, oCurrentPartitionTime);
        }

        oCurrentPartitionTime = 0;
        while (jCounter < oTaskCount)
        {
            oCurrentPartitionTime += oTasks[jCounter];
            ++jCounter;
        }

        oTotalTime = max(oTotalTime, oCurrentPartitionTime);
        return oTotalTime;
    }

    void Combinations(vector<int>& oTasks, int Idx, int K, vector<int>& oPartition, vector<vector<int>>& oResult)
    {
        if (oPartition.size() == K) {
            oResult.push_back(oPartition);
            return;
        }

        for (int iCounter = Idx; iCounter < static_cast<int>(oTasks.size()); ++iCounter)
        {
            oPartition.push_back(iCounter);
            Combinations(oTasks, iCounter + 1, K, oPartition, oResult);
            oPartition.pop_back();
        }
    }

    int CalculateMinimumTimeTaken(vector<int>& oTasks, int kPartition)
    {
        vector<int> oPartition;
        vector<vector<int>> oResult;
        Combinations(oTasks, 0, kPartition - 1, oPartition, oResult);
        int MinimumTime = INT_MAX;
        for_each(oResult.begin(), oResult.end(), [&MinimumTime, &oTasks](vector<int>& oPartition)->void {
            int oPartitionTimeTaken = ComputeTimeTaken(oTasks, oPartition);
            MinimumTime = min(MinimumTime, oPartitionTimeTaken);
        });

        return MinimumTime;
    }
}

namespace BinarySearch
{
    bool IsValidDistribution(vector<int>& oTasks, int kPartition, int oExpectedTime)
    {
        int kPartitionCount = 0;
        int nTaskCount = static_cast<int>(oTasks.size());
        int oCurrentTimeTaken = 0;

        for (int iCounter = 0; iCounter < nTaskCount; ++iCounter)
        {
            if ((oTasks[iCounter] + oCurrentTimeTaken) <= oExpectedTime)
                oCurrentTimeTaken += oTasks[iCounter];
            else
            {
                ++kPartitionCount;
                if (oTasks[iCounter] <= oExpectedTime)
                    oCurrentTimeTaken = oTasks[iCounter];
                else
                    return false;
            } 
        }

        if (oCurrentTimeTaken > 0)
            ++kPartitionCount;

        if (kPartitionCount <= kPartition)
            return true;

        return false;
    }

    int CalculateMinimumTimeTaken(vector<int>& oTasks, int kPartition)
    {
        int oTotalSum = 0;
        for_each(oTasks.begin(), oTasks.end(), [&oTotalSum](int oVal)->void {
            oTotalSum += oVal;
        });

        int Low = oTotalSum / kPartition;
        int High = oTotalSum;

        while (Low < High)
        {
            int Mid = Low + ((High - Low) >> 1);
            if (IsValidDistribution(oTasks, kPartition, Mid))
                High = Mid;
            else
                Low = Mid + 1;
        }

        return Low;
    }
}


int main()
{ 
    vector<int> oTasks{ 1, 10, 13, 4, 5, 12, 23, 12, 18, 8 };
    int K = 3;
    cout << BinarySearch::CalculateMinimumTimeTaken(oTasks, K) << endl;


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
