// SubsetSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;


/*
 Recusive Approach
 TC: 2^N + 2^N-1;
 SC: 1
*/

namespace BruteForce
{
    bool IsSubsetSumExit(int* pArray, int nSize, int Idx, int oTargetSum, int oCurrentSum)
    {
        /*Because by this time subset would have
         generated and we can safely check for target sum */
        if (nSize == Idx)
            return oTargetSum == oCurrentSum;

        return IsSubsetSumExit(pArray, nSize, Idx + 1, oTargetSum, oCurrentSum + pArray[Idx])
            || IsSubsetSumExit(pArray, nSize, Idx + 1, oTargetSum, oCurrentSum);
    }
}

/*
We Basically divide array in two
halves and check each time whether
there exist a sum which equivalent 
to K-CurrentSum
(We can also store subset sum in vector
for both halves and sort it and apply two 
pointer technique to check for given sum
. We need to consider the case of null
subset also)

2^(N/2) + 2^(N/2), 2^(N/2) + 2^(N/2)
*/
namespace MeetInTheMiddle_HashSet
{
    bool IsSubsetSumExist(int* pArray, int nSize, int Idx, int oTargetSum, int oCurrentSum, unordered_set<int>& oUSet)
    { 
        if (nSize == Idx) {
            if (oUSet.find(oTargetSum - oCurrentSum) != oUSet.end())
                return true;
            else
                oUSet.insert(oCurrentSum);

            return false;
        }

        return IsSubsetSumExist(pArray, nSize, Idx + 1, oTargetSum, oCurrentSum + pArray[Idx], oUSet)
            || IsSubsetSumExist(pArray, nSize, Idx + 1, oTargetSum, oCurrentSum, oUSet);
    }

    bool IsSubSetSumExist(int* pArray, int nSize, int oTargetSum)
    {
        int Mid = nSize >> 1;
        unordered_set<int> oUSet;
        return IsSubsetSumExist(pArray, Mid, 0, oTargetSum, 0, oUSet) ||
            IsSubsetSumExist(pArray, nSize, Mid, oTargetSum, 0, oUSet);
    }
}

int main()
{
    int pArray[] = { 3, 19, -2, 15, -9, 18, 26, 5 };
    int nSize = 8;
    cout <<"Target Sum = 32: "<< MeetInTheMiddle_HashSet::IsSubSetSumExist(pArray, nSize, 32) << endl;
    cout << "Target Sum = 11: " << MeetInTheMiddle_HashSet::IsSubSetSumExist(pArray, nSize, 11) << endl;
    cout << "Target Sum = -5: " << MeetInTheMiddle_HashSet::IsSubSetSumExist(pArray, nSize, -5) << endl;
    cout << "Target Sum = 27: " << MeetInTheMiddle_HashSet::IsSubSetSumExist(pArray, nSize, 27) << endl;
    cout << "Target Sum = 27: " << BruteForce::IsSubsetSumExit(pArray, nSize, 0, 27, 0) << endl;
    cout << "Target Sum = 17: " << MeetInTheMiddle_HashSet::IsSubSetSumExist(pArray, nSize, 17) << endl;
    cout << "Target Sum = 15: " << MeetInTheMiddle_HashSet::IsSubSetSumExist(pArray, nSize, 15) << endl;
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
