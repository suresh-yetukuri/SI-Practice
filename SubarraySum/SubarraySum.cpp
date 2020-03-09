// SubarraySum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Q*N, 1 : Where Q is the number of queries of (i, j) where 0 <= i <= j <= N-1
*/
namespace BruteForce
{
    long long int SubarraySum(vector<long long int>& pArray, int iCounter, int jCounter)
    {
        long long int Sum = 0;
        for (int pCounter = iCounter; pCounter <= jCounter; ++pCounter)
            Sum += pArray[pCounter];

        return Sum;
    }
}

/*
N + Q*1, N 
*/
namespace PrefixSumArray
{ 

    vector<long long int> BuildPrefixSum(vector<long long int>& pArray)
    {
        int nSize = static_cast<int>(pArray.size()); 
        vector<long long int> pPrefixArray(nSize, 0);
        pPrefixArray[0] = pArray[0];
        for (int iCounter = 1; iCounter < nSize; ++iCounter)
            pPrefixArray[iCounter] = pPrefixArray[iCounter - 1] + pArray[iCounter];

        return pPrefixArray;
    }
 
    long long int SubarraySum(vector<long long int>& pArray, 
                              vector<long long int>& pPrefixArray, 
                              int iCounter, 
                              int jCounter)
    {
        return (pPrefixArray[jCounter] - pPrefixArray[iCounter]) + pArray[iCounter];
    }
}


int main()
{
    vector<long long int> oSample{ 5, 1, 3, 4, 8, 2, 7 };
    vector<long long int> oPrefix = PrefixSumArray::BuildPrefixSum(oSample);
    cout << PrefixSumArray::SubarraySum(oSample, oPrefix, 2, 5);

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
