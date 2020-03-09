// Backtracking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void Permutation(vector<int>& pArray, 
             vector<bool> &pUsed, 
             vector<int>& oSet, 
             vector<vector<int>>& oResult)
{
    if (pArray.size() == oSet.size())
    {
        oResult.push_back(oSet);
        return;
    }

    for (int iCounter = 0; iCounter < static_cast<int>(pArray.size()); ++iCounter)
    {
        if (!pUsed[iCounter]) {
            pUsed[iCounter] = true;
            oSet.push_back(pArray[iCounter]);
            Permutation(pArray, pUsed, oSet, oResult);
            oSet.pop_back();
            pUsed[iCounter] = false;
        }
    }
}

void Combination(vector<int>& pArray,
                 vector<int>& oSet,
                 vector<vector<int>>& oResult,
                 int Idx,
                 int K)
{
    if (0 == K)
    {
        oResult.push_back(oSet);
        return;
    }

    for (int iCounter = Idx; iCounter < static_cast<int>(pArray.size()); ++iCounter)
    {
        oSet.push_back(pArray[iCounter]);
        Combination(pArray, oSet, oResult, iCounter + 1, K - 1);
        oSet.pop_back();
    }
}


void getSubSet(vector<int> &pArray, 
               vector<int> oSet, 
               vector<vector<int>> &pSubset, int Idx)
{
    if (static_cast<int>(pArray.size()) == Idx) {
        pSubset.push_back(oSet);
        return;
    }

    oSet.push_back(pArray[Idx]);
    getSubSet(pArray, oSet, pSubset, Idx + 1);
    oSet.pop_back();
    getSubSet(pArray, oSet, pSubset, Idx + 1);
}

bool LexographicalCheck(int oLeftCounter, int oRightCounter, vector<vector<int>>& pSubset)
{
    int pLeftSubsetSize =  static_cast<int>(pSubset[oLeftCounter].size());
    int pRightSubsetSize = static_cast<int>(pSubset[oRightCounter].size());

    int iCounter = 0;
    int jCounter = 0;

    while ((iCounter < pLeftSubsetSize) && (jCounter < pRightSubsetSize))
    {
        if (pSubset[oLeftCounter][iCounter] > pSubset[oRightCounter][jCounter]) {
            return true;
        }
        else if (pSubset[oLeftCounter][iCounter] < pSubset[oRightCounter][jCounter]) {
            return false;
        }
        else {
            ++iCounter;
            ++jCounter;
        }
    }

    if (iCounter == pLeftSubsetSize)
        return false;

    if (jCounter == pRightSubsetSize)
        return true;

    return false;
}

void Merge(int* pArray, int* pLeftArray, int* pRightArray, int nLeft, int nRight, vector<vector<int>>& pSubset)
{
    int iCounter = 0;
    int jCounter = 0;
    int kCounter = 0;

    while ((iCounter < nLeft) && (jCounter < nRight))
    {
        if (LexographicalCheck(pLeftArray[iCounter], pRightArray[jCounter], pSubset)) {
            pArray[kCounter] = pRightArray[jCounter];
            ++jCounter;
        }
        else {
            pArray[kCounter] = pLeftArray[iCounter];
            ++iCounter;
        }

        ++kCounter;
    }

    while (iCounter < nLeft)
        pArray[kCounter++] = pLeftArray[iCounter++];

    while (jCounter < nRight)
        pArray[kCounter++] = pRightArray[jCounter++];
}

void MergeSort(int* pArray, int nSize, vector<vector<int>>& pSubset)
{
    if (nSize < 2)
        return;

    int oMid = nSize >> 1;
    int* pLeft = new int[oMid];
    int* pRight = new int[nSize - oMid];

    for (int iCounter = 0; iCounter < oMid; ++iCounter)
        pLeft[iCounter] = pArray[iCounter];

    for (int iCounter = oMid; iCounter < nSize; ++iCounter)
        pRight[iCounter - oMid] = pArray[iCounter];

    MergeSort(pLeft, oMid, pSubset);
    MergeSort(pRight, nSize - oMid, pSubset);
    Merge(pArray, pLeft, pRight, oMid, nSize - oMid, pSubset);
    delete[] pLeft; pLeft = nullptr;
    delete[] pRight; pRight = nullptr;
}

void LexographicalSort(vector<vector<int>>& pSubset)
{
    vector<int> pOrderArray(pSubset.size());
    for (int iCounter = 0; iCounter < static_cast<int>(pOrderArray.size()); ++iCounter)
        pOrderArray[iCounter] = iCounter;

    MergeSort(&pOrderArray[0], static_cast<int>(pOrderArray.size()), pSubset);

    vector<vector<int>> pTempSubset(pSubset.size());
    for (int iCounter = 0; iCounter < static_cast<int>(pOrderArray.size()); ++iCounter)
        pTempSubset[iCounter] = pSubset[pOrderArray[iCounter]];

    for (int iCounter = 0; iCounter < static_cast<int>(pOrderArray.size()); ++iCounter) {
        pSubset[iCounter] = pTempSubset[iCounter];
    }
}

void RemoveDuplicates(vector<vector<int>>& pSubset)
{
    int pCounter = 0;
    int nSubsetSize = static_cast<int>(pSubset.size());
    vector<int> oDuplicateIndex;
    while ((pCounter + 1) < nSubsetSize)
    {
        int nLeft = static_cast<int>(pSubset[pCounter].size());
        int nRight = static_cast<int>(pSubset[pCounter + 1].size());

        if (nLeft == nRight)
        {
            int iCounter = 0;
            int jCounter = 0;
            while (iCounter < nLeft && jCounter < nRight)
            {
                if (pSubset[pCounter][iCounter] == pSubset[pCounter + 1][jCounter])
                {
                    ++iCounter;
                    ++jCounter;
                }
                else
                    break;
            }

            if (iCounter == jCounter && jCounter == nLeft)
                oDuplicateIndex.push_back(pCounter);
        }

        ++pCounter;
    }

    vector<vector<int>> pTempSubset;

    for (int iCounter = 0; iCounter < oDuplicateIndex.size(); ++iCounter)
        pSubset[oDuplicateIndex[iCounter]].clear();

    pTempSubset.push_back(vector<int>());
    for (int iCounter = 0; iCounter < pSubset.size(); ++iCounter) {
        if (pSubset[iCounter].size() != 0) {
            pTempSubset.push_back(pSubset[iCounter]);
        }
    }

    swap(pTempSubset, pSubset);
    pTempSubset.clear();
/*   int kCounter = 0;
    for (int iCounter = 0; iCounter < static_cast<int>(pSubset.size()); ++iCounter) {
        if (oDuplicateIndex.find(iCounter) != oDuplicateIndex.end())
            pTempSubset[kCounter++] = pSubset[iCounter];
    }

    swap(pTempSubset, pSubset);*/ 
}

void GenerateParanthesis(const int N,
    int Idx,
    int nOpenCount,
    int nClosedCount,
    string oSet,
    vector<string>& oResult)
{
    if (N == Idx)
    {
        oResult.push_back(oSet);
        return;
    }

    if ((N >> 1) > nOpenCount) {
        oSet[Idx] = '(';
        GenerateParanthesis(N, Idx + 1, nOpenCount + 1, nClosedCount, oSet, oResult);
    }

    if (nOpenCount > nClosedCount) {
        oSet[Idx] = ')';
        GenerateParanthesis(N, Idx + 1, nOpenCount, nClosedCount + 1, oSet, oResult);
    }

    return;
}




int main()
{
    const int N = 6;
    string oSet(N, '\0');
    vector<string> oResult;
    GenerateParanthesis(N, 0, 0, 0, oSet, oResult);






    vector<int> pArray = { 6, 6, 3, 3, 6, 5 };
    //vector<int> oSet;
    vector<vector<int>> pSubset;
    //getSubSet(pArray, oSet, pSubset, 0);
    //pSubset.pop_back();
    LexographicalSort(pSubset);
    //RemoveDuplicates(pSubset);
    for (int iCounter = 0; iCounter < pSubset.size(); ++iCounter)
    { 
        for (int jCounter = 0; jCounter < pSubset[iCounter].size(); ++jCounter)
            cout << pSubset[iCounter][jCounter] << " ";

        cout << endl;
    }
    cout << "Remove" << endl;
    RemoveDuplicates(pSubset);
    for (int iCounter = 0; iCounter < pSubset.size(); ++iCounter)
    { 
        for (int jCounter = 0; jCounter < pSubset[iCounter].size(); ++jCounter)
            cout << pSubset[iCounter][jCounter] << " ";

        cout << endl;
    }




    //vector<vector<int>> oResult;
   // auto oResult = Combine(1,1);
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
