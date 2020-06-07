// DistinctBinaryMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Count of Distinct rows in binary matrix
*/

/*
M*(M*N), 1
Simple Compare each row with all other rows for checking uniqueness
*/
namespace BruteForce
{
    /*
    N, 1
    */
    bool IsRowSame(vector<vector<bool>>& pMatrix, int colCount, int oFRowIdx, int oSRowIdx)
    {
        for (int jCounter = 0; jCounter < colCount; ++jCounter)
        {
            if (pMatrix[oFRowIdx][jCounter] != pMatrix[oSRowIdx][jCounter])
                return false;
        }

        return true;
    }

    /*
    M*(M*N), 1
    */
    int Distinct(vector<vector<bool>>& pMatrix, int rowCount, int colCount)
    {
        if (rowCount == 0 || rowCount == 1)
            return rowCount;

        int oDistinctCount = 0;
        for (int iCounter = 0; iCounter < rowCount; ++iCounter)
        {
            bool IsExist = false;
            for (int jCounter = iCounter - 1; jCounter >= 0; --jCounter)
            {
                if (IsRowSame(pMatrix, colCount, iCounter, jCounter)) {
                    IsExist = true;
                    break;
                }
            }

            if (!IsExist)
                ++oDistinctCount;
        }

        return oDistinctCount;
    }

}

namespace UsingTrie
{
    class TrieNode
    {
    public:
        TrieNode* pChild[2];
        TrieNode()
        {
            pChild[0] = nullptr;
            pChild[1] = nullptr;
        }
    };

    bool Insert(TrieNode* pRoot, vector<vector<bool>>& pMatrix, int oRowIdx, int colCount)
    {
        TrieNode* pCurrent = pRoot;
        bool IsUnique = false;
        for (int jCounter = 0; jCounter < colCount; ++jCounter)
        {
            if (nullptr == (pCurrent->pChild[pMatrix[oRowIdx][jCounter]])) {
                pCurrent->pChild[pMatrix[oRowIdx][jCounter]] = new TrieNode();
                IsUnique = true;
            }
            pCurrent = pCurrent->pChild[pMatrix[oRowIdx][jCounter]];
        }

        return IsUnique;
    }

    /*
    M*N, M*N
    */
    int Distinct(vector<vector<bool>>& pMatrix, int rowCount, int colCount)
    {
        if (rowCount == 0 || rowCount == 1)
            return rowCount;

        int oDistinctCount = 0;
        TrieNode* pRoot = new TrieNode();
        for (int iCounter = 0; iCounter < rowCount; ++iCounter)
        {
            if (Insert(pRoot, pMatrix, iCounter, colCount))
                ++oDistinctCount;
        }

        return oDistinctCount;
    }
}

int main()
{
    vector<vector<bool>> pMatrix = { {true, false, false}
                                   ,{true, true, true}
                                   ,{true, false, false}
                                   ,{true, true, true} };

    cout << UsingTrie::Distinct(pMatrix, 4, 3);

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
