// KSortedArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


/*
Simply Copy NK elements into an array and sort it
NKLogNK, NK
*/


/*
  N*K(K + K), K
*/
namespace BruteForce
{
    bool IsAllCounterInvalid(vector<vector<int>>& oInput, vector<int>& oCounter)
    {
        int nSize = static_cast<int>(oCounter.size());
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            if (oCounter[iCounter] < oInput[iCounter].size())
                return false;
        }

        return true;
    }

    pair<int, int> GetMin(vector<vector<int>>& oInput, vector<int>& oCounter)
    {
        int kSize = static_cast<int>(oCounter.size());
        pair<int, int> oMinPair;
        bool IsInitialized = false;
        for (int iCounter = 0; iCounter < kSize; ++iCounter)
        {
            if (oCounter[iCounter] < oInput[iCounter].size())
            {
                if (IsInitialized) {
                    if (oMinPair.first > oInput[iCounter][oCounter[iCounter]]) {
                        oMinPair.first = oInput[iCounter][oCounter[iCounter]];
                        oMinPair.second = iCounter;
                    }
                }
                else { 
                    oMinPair = make_pair(oInput[iCounter][oCounter[iCounter]], iCounter);
                    IsInitialized = true;
                }
            }
        }

        return oMinPair;
    }

    vector<int> Sort(vector<vector<int>>& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        int rSize = 0;
        for (auto& oData : oInput)
            rSize += (static_cast<int>(oData.size()));

        vector<int> oResultant(rSize, 0);
        vector<int> oCounter(nSize, 0);

        int oCurrentIdx = 0;
        while (!IsAllCounterInvalid(oInput, oCounter))
        {
            pair<int, int> oMinPair = GetMin(oInput, oCounter);
            oResultant[oCurrentIdx++] = oMinPair.first;
            oCounter[oMinPair.second]++;
        }

        return oResultant;
    }
}

/*
NKLogK, K
*/
namespace Efficient
{
    struct Node
    {
        int Data;
        int Counter;
        int ArrayIdx;
    };


    vector<int> Sort(vector<vector<int>>& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        int rSize = 0;
        for (auto& oData : oInput)
            rSize += (static_cast<int>(oData.size()));
         
        auto oComparator = [](const Node& FNode, const Node& SNode)->bool
        {
            return FNode.Data > SNode.Data;
        };
        vector<int> oResultant(rSize, 0);
        priority_queue<Node, vector<Node>, bool(*)(const Node&, const Node&)> oMinHeap(oComparator);
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            Node oNode{ oInput[iCounter][0], 0, iCounter };
            oMinHeap.push(move(oNode));
        }

        int oCurrentIdx = 0;
        while (!oMinHeap.empty())
        {
            Node oCurrentNode = oMinHeap.top();
            oMinHeap.pop();
            oResultant[oCurrentIdx++] = oCurrentNode.Data;
             
            if ((oCurrentNode.Counter + 1) < static_cast<int>(oInput[oCurrentNode.ArrayIdx].size())) {
                oCurrentNode.Counter = oCurrentNode.Counter + 1;
                oCurrentNode.Data = oInput[oCurrentNode.ArrayIdx][oCurrentNode.Counter];
                oMinHeap.push(move(oCurrentNode));
            }
        }

        return move(oResultant);
    }
}

int main()
{
    vector<vector<int>> oInput{ {10, 25, 60}, {1, 23, 56, 58}, {9, 12, 20, 21, 28, 30}, {27} };
    auto oResult = Efficient::Sort(oInput);
    for (auto& oData : oResult)
        cout << oData << " ";

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
