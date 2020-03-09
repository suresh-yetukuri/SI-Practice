// InterleavingString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Interleaving(string oLeft, 
                  string oRight, 
                  int iCounter, 
                  int jCounter, 
                  string oResult, 
                  int kCounter,
                  vector<string>& oCollection)
{
    if (iCounter == static_cast<int>(oLeft.size()) && jCounter == static_cast<int>(oRight.size())) {
        oCollection.push_back(oResult);
        return;
    }


    if (iCounter < static_cast<int>(oLeft.size()))
    {
        oResult.insert(oResult.begin() + kCounter, oLeft.at(iCounter));
        Interleaving(oLeft, oRight, iCounter + 1, jCounter, oResult, kCounter + 1, oCollection);
        oResult.pop_back();
    }

    if (jCounter < static_cast<int>(oRight.size()))
    {
        oResult.insert(oResult.begin() + kCounter, oRight.at(jCounter));
        Interleaving(oLeft, oRight, iCounter, jCounter + 1, oResult, kCounter + 1, oCollection);
        oResult.pop_back();
    }
}


bool LexographicalCheck(int LeftIdx, int RightIdx, vector<string>& oCollection)
{
    int pCounter = 0;
    int qCounter = 0;
    int nLeftSize = static_cast<int>(oCollection[LeftIdx].size());
    int nRightSize = static_cast<int>(oCollection[RightIdx].size());
    while ((pCounter < nLeftSize) && (qCounter < nRightSize))
    {
        if (oCollection[LeftIdx][pCounter] == oCollection[RightIdx][qCounter])
        {
            ++pCounter;
            ++qCounter;
        }
        else 
        {
            if (oCollection[LeftIdx][pCounter] > oCollection[RightIdx][qCounter])
                return true;
            else
                return false;
        }
    }

    if (qCounter == nRightSize)
        return true;

    return false;
}


void Merge(int* pLeftArray, int* pRightArray, int nLeft, int nRight, int* pArray, vector<string>& oCollection)
{
    int iCounter = 0;
    int jCounter = 0;
    int kCounter = 0;


    while ((iCounter < nLeft) && (jCounter < nRight))
    {
        if (LexographicalCheck(pLeftArray[iCounter], pRightArray[jCounter], oCollection)) {
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


void MergeSort(int* pArray, int nSize, vector<string>& oCollection)
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

    MergeSort(pLeft, oMid, oCollection);
    MergeSort(pRight, nSize - oMid, oCollection);
    Merge(pLeft, pRight, oMid, nSize - oMid, pArray, oCollection);
    delete[] pLeft; pLeft = nullptr;
    delete[] pRight; pRight = nullptr;
}


void LexographicalSort(vector<string>& oCollection)
{
    int nSize = static_cast<int>(oCollection.size());
    int* pOrderArray = new int[nSize];
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        pOrderArray[iCounter] = iCounter;

    MergeSort(pOrderArray, nSize, oCollection);
    for (int iCounter = 0; iCounter < nSize; ++iCounter) 
        cout << oCollection[pOrderArray[iCounter]] << endl;

    delete[] pOrderArray;
    pOrderArray = nullptr;
}




int main()
{
    string oLeft = "bn";
    string oRight = "zh";
    string oResult;
    vector<string> oCollection;
    Interleaving(oRight, oLeft, 0, 0, oResult, 0, oCollection);
    LexographicalSort(oCollection);
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
