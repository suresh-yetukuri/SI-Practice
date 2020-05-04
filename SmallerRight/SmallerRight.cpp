// SmallerRight.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
Given an array arr[] of N elements. 
The task is to count maximum number of distinct smaller elements on right side of any array element. 
For example, in {10, 6, 9, 7, 20, 19, 21, 18, 17, 16}, the result is 4.  
Note that 20 has maximum 4 smaller elements on right side. 
Other elements have less count, for example 10 has 3 smaller elements on right side.
*/

/*
NLogN, N (But we can't get distinct count of max smaller elements)
*/
namespace BruteForce
{
    struct Pair
    {
        int oData;
        int oRightCount;
    };

    void Merge(vector<Pair>& oLeft, vector<Pair>& oRight, vector<Pair>& oMainArray)
    {
        int nLeftCount = static_cast<int>(oLeft.size());
        int nRightCount = static_cast<int>(oRight.size());
        int iCounter = 0;
        int jCounter = 0;
        int kCounter = 0;
        int nSmallerRightCount = 0;

        while (iCounter < nLeftCount && jCounter < nRightCount)
        {
            if (oLeft[iCounter].oData > oRight[jCounter].oData) {
                ++nSmallerRightCount;
                oMainArray[kCounter++] = oRight[jCounter++];
            }
            else {
                oLeft[iCounter].oRightCount += nSmallerRightCount;
                oMainArray[kCounter++] = oLeft[iCounter++];
            }
        }

        while (iCounter < nLeftCount)
        {
            oLeft[iCounter].oRightCount += nSmallerRightCount;
            oMainArray[kCounter++] = oLeft[iCounter++];
        }

        while (jCounter < nRightCount)
            oMainArray[kCounter++] = oRight[jCounter++];

        return;
    }

    void MergeSort(vector<Pair>& oArray)
    {
        int nSize = static_cast<int>(oArray.size());
        if (nSize < 2)
            return;

        int oMid = nSize >> 1;
        vector<Pair> oLeft(oArray.begin(), oArray.begin() + oMid);
        vector<Pair> oRight(oArray.begin() + oMid, oArray.end());

        MergeSort(oLeft);
        MergeSort(oRight);
        Merge(oLeft, oRight, oArray);
        return;
    }

    int GetSmallerOnRight(vector<int>& oInput)
    {
        vector<Pair> oArray(oInput.size());
        for (int iCounter = 0; iCounter < oInput.size(); ++iCounter)
            oArray[iCounter] = { oInput[iCounter], 0 };

        MergeSort(oArray);
        auto oMaxSmallerRightPair = (*max_element(oArray.begin(), oArray.end(), [](Pair& oFPair, Pair& oSPair)->bool {
            return oFPair.oRightCount < oSPair.oRightCount;
            })).oRightCount;

        return oMaxSmallerRightPair;
    }
} 

namespace Efficient
{
     
    class Node
    {
    public:
        int Data;
        int Height;
        int Size;
        int BalanceFactor;
        Node* pLeft;
        Node* pRight;

        Node(int val)
        {
            this->Data = val;
            this->Height = 1; 
            this->Size = 1;
            this->BalanceFactor = 0;
            this->pLeft = nullptr;
            this->pRight = nullptr;
        }

        static int GetSize(Node* pNode)
        {
            if (nullptr == pNode)
                return 0;

            return pNode->Size;
        }

        void Update()
        {
            int oLeftHeight = (nullptr == pLeft) ? 0 : pLeft->Height;
            int oRightHeight = (nullptr == pRight) ? 0 : pRight->Height;
            this->Height = 1 + max(oLeftHeight, oRightHeight);
            this->BalanceFactor = oRightHeight - oLeftHeight;
            this->Size = GetSize(pLeft) + GetSize(pRight) + 1;
        }
    };

    Node* RightRotation(Node* pNode)
    {
        if (nullptr != pNode)
        {
            Node* pNewParent = pNode->pLeft;
            pNode->pLeft = pNewParent->pRight;
            pNewParent->pRight = pNode;
            pNode->Update();
            pNewParent->Update();
            return pNewParent;
        }

        return pNode;
    }
    
    Node* LeftRotation(Node* pNode)
    {
        if (nullptr != pNode)
        {
            Node* pNewParent = pNode->pRight;
            pNode->pRight = pNewParent->pLeft;
            pNewParent->pLeft = pNode;
            pNode->Update();
            pNewParent->Update();
            return pNewParent;
        }

        return pNode;
    }

    Node* LeftLeft(Node* pNode)
    {
        return RightRotation(pNode);
    }

    Node* LeftRight(Node* pNode)
    {
        if (nullptr != pNode)
        {
            pNode->pLeft = LeftRotation(pNode->pLeft);
            return RightRotation(pNode);
        }

        return pNode;
    }

    Node* RightRight(Node* pNode)
    {
        return LeftRotation(pNode);
    }

    Node* RightLeft(Node* pNode)
    {
        if (nullptr != pNode)
        {
            pNode->pRight = RightRotation(pNode->pRight);
            return LeftRotation(pNode);
        }
        return pNode;
    }

    Node* Balance(Node* pNode)
    {
        if (nullptr != pNode)
        {
            int oCurrentBalanceFactor = pNode->BalanceFactor;
            if (oCurrentBalanceFactor <= 1 && oCurrentBalanceFactor >= -1)
                return pNode;
            else
            {
                if (oCurrentBalanceFactor == -2)
                {
                    // Left Subtree is heavier
                    if (nullptr != pNode->pLeft && pNode->pLeft->BalanceFactor <= -1)
                        return LeftLeft(pNode);
                    else
                        return LeftRight(pNode);
                }
                else
                {
                    // Right Subtree is heavier
                    if (nullptr != pNode->pRight && pNode->pRight->BalanceFactor >= 1)
                        return RightRight(pNode);
                    else
                        return RightLeft(pNode);
                }
            }
        }

        return pNode;
    }

    Node* Insert(Node* pRoot, const int oData, int& oCurrentCount)
    {
        if (nullptr == pRoot) {
            return new Node(oData);
        }
        else if (oData > pRoot->Data) {
            pRoot->pRight = Insert(pRoot->pRight, oData, oCurrentCount);
            oCurrentCount = oCurrentCount + 1 + Node::GetSize(pRoot->pLeft);
        }
        else if (oData < pRoot->Data)
            pRoot->pLeft = Insert(pRoot->pLeft, oData, oCurrentCount);
        else 
            oCurrentCount = oCurrentCount + Node::GetSize(pRoot->pLeft);

        pRoot->Update();
        return Balance(pRoot);
    }
}

/*
Worst Case N^2, N
*/
namespace UsingSet
{
    int GetSmallerOnRight(vector<int>& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        set<int> oSet;
        int oMaxCount = 0;
        oSet.insert(oInput[nSize - 1llu]);
        for (int iCounter = nSize-2; iCounter >= 0; --iCounter)
        {
            int oCurrentValue = oInput[iCounter];
            auto Itr = lower_bound(oSet.begin(), oSet.end(), oCurrentValue);
            int oCount = distance(oSet.begin(), Itr);
            oMaxCount = max(oMaxCount, oCount);
            oSet.insert(oCurrentValue);
        }

        return oMaxCount;
    }
}


int main()
{
    vector<int> oInput{ 1, 2, 3, 2, 1 };
    int oMaxCount = 0;
    using namespace Efficient;
    Node* pRoot = nullptr;
    for (auto Itr = oInput.rbegin(); oInput.rend() != Itr; ++Itr) {
        int oCurrentCount = 0;
        pRoot = Insert(pRoot, *Itr, oCurrentCount);
        oMaxCount = max(oMaxCount, oCurrentCount);
    }

    cout << oMaxCount << endl;
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
