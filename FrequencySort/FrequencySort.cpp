// FrequencySort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
using namespace std;

/*
 N + NLogN, N + N (One for MergeSort & Other for Map)
*/
namespace UsingHashPlusMergeSort
{
    bool FrequencyCheck(int a, int b, unordered_map<int, int>& oFreqMap)
    {
        if (oFreqMap[a] < oFreqMap[b])
            return true;
        else if (oFreqMap[a] == oFreqMap[b])
            return a < b;
        
        return false;
    }

    void Merge(int* pLeft, int* pRight, int* pArray, int nLeft, int nRight, unordered_map<int, int>& oFreqMap)
    {
        int iCounter = 0;
        int jCounter = 0;
        int kCounter = 0;

        while ((iCounter < nLeft) && (jCounter < nRight))
        {
            if (FrequencyCheck(pLeft[iCounter], pRight[jCounter], oFreqMap))
                pArray[kCounter++] = pLeft[iCounter++];
            else
                pArray[kCounter++] = pRight[jCounter++];
        }

        while (iCounter < nLeft)
            pArray[kCounter++] = pLeft[iCounter++];

        while (jCounter < nRight)
            pArray[kCounter++] = pRight[jCounter++];
    }
    
    void MergeSort(int* pArray, int nSize, unordered_map<int, int>& oFreqMap)
    {
        if (nSize < 2)
            return;

        int Mid = nSize >> 1;
        int* pLeft = new int[Mid];
        int* pRight = new int[nSize - Mid];

        for (int iCounter = 0; iCounter < Mid; ++iCounter)
            pLeft[iCounter] = pArray[iCounter];

        for (int iCounter = Mid; iCounter < nSize; ++iCounter)
            pRight[iCounter - Mid] = pArray[iCounter];

        MergeSort(pLeft, Mid, oFreqMap);
        MergeSort(pRight, nSize - Mid, oFreqMap);
        Merge(pLeft, pRight, pArray, Mid, nSize - Mid, oFreqMap);
        delete[] pLeft; pLeft = nullptr;
        delete[] pRight; pRight = nullptr;
    }

    void FrequencySort(int* pArray, int nSize)
    {
        unordered_map<int, int> oFrequencyMap;
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
            oFrequencyMap[pArray[iCounter]]++;

        MergeSort(pArray, nSize, oFrequencyMap);
    }
}


int main()
{
    /*int arr[] = { 176, -272, -272, -45, 269, -327, -945, 176 };
    int nSize = 8;*/
    int arr[] = { 4, - 2, 10 ,12 ,- 8, 4 };
    int nSize = 6;
    UsingHashPlusMergeSort::FrequencySort(arr, nSize);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cout << arr[iCounter] << " ";

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
