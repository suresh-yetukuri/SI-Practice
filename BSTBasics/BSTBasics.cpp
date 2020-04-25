// BSTBasics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

class Node
{
public:
    int Data;
    Node* pLeft;
    Node* pRight;
    Node(int val)
    {
        this->Data = val;
        this->pLeft = nullptr;
        this->pRight = nullptr;
    }
};

namespace Insert
{
    Node* InsertRecursive(Node* pRoot, const int oData)
    {
        if (nullptr == pRoot)
            pRoot = new Node(oData);
        else if (oData > pRoot->Data)
            pRoot->pRight = InsertRecursive(pRoot->pRight, oData);
        else if (oData < pRoot->Data)
            pRoot->pLeft = InsertRecursive(pRoot->pLeft, oData);

        return pRoot;
    }

    Node* InsertIterative(Node* pRoot, const int oData)
    {
        if (nullptr == pRoot)
            return new Node(oData);

        Node* pNewNode = new Node(oData);
        Node* pCurrent = pRoot;
        Node* pParent = nullptr;
        while (nullptr != pCurrent)
        {
            pParent = pCurrent;
            if (oData > pCurrent->Data)
                pCurrent = pCurrent->pRight;
            else if (oData < pCurrent->Data)
                pCurrent = pCurrent->pLeft;
            else
                return pRoot;
        }

        if (pParent->Data > oData)
            pParent->pLeft = pNewNode;
        else
            pParent->pRight = pNewNode;

        return pRoot;
    }
}

namespace Search
{
    bool SearchRecursive(Node* pRoot, const int oData)
    {
        if (nullptr == pRoot)
            return false;
        else if (oData == pRoot->Data)
            return true;
        else if (oData > pRoot->Data)
            return SearchRecursive(pRoot->pRight, oData);
        else
            return SearchRecursive(pRoot->pLeft, oData);
    }

    bool SearchIterative(Node* pRoot, const int oData)
    {
        Node* pCurrent = pRoot;
        while (nullptr != pCurrent)
        {
            if (oData == pCurrent->Data)
                return true;
            else if (oData > pCurrent->Data)
                pCurrent = pCurrent->pRight;
            else
                pCurrent = pCurrent->pLeft;
        }

        return false;
    }
}

namespace Delete
{
    Node* GetSuccessor(Node* pNode)
    {
        Node* pCurrent = pNode->pRight;
        while (nullptr != pCurrent && nullptr != pCurrent->pLeft)
            pCurrent = pCurrent->pLeft;

        return pCurrent;
    }

    Node* GetPredecessor(Node* pNode)
    {
        Node* pCurrent = pNode->pLeft;
        while (nullptr != pCurrent && nullptr != pCurrent->pRight)
            pCurrent = pCurrent->pRight;

        return pCurrent;
    }

    Node* DeleteRecursive(Node* pRoot, const int oData)
    {
        if (nullptr == pRoot)
            pRoot = nullptr;
        else if (oData > pRoot->Data)
            pRoot->pRight = DeleteRecursive(pRoot->pRight, oData);
        else if (oData < pRoot->Data)
            pRoot->pLeft = DeleteRecursive(pRoot->pLeft, oData);
        else
        {
            if (nullptr == pRoot->pLeft && nullptr == pRoot->pRight)
            {
                delete(pRoot);
                pRoot = nullptr;
            }
            else if (nullptr != pRoot->pLeft && nullptr == pRoot->pRight)
            {
                Node* pNodeTBD = pRoot;
                pRoot = pRoot->pLeft;
                delete(pNodeTBD);
                pNodeTBD = nullptr;
            }
            else if (nullptr == pRoot->pLeft && nullptr != pRoot->pRight)
            {
                Node* pNodeTBD = pRoot;
                pRoot = pRoot->pRight;
                delete(pNodeTBD);
                pNodeTBD = nullptr;
            }
            else
            {
                // Node* pReplaceableNode = GetSuccessor(pRoot);
                // pRoot->Data = pReplaceableNode->Data;
                // pRoot->pRight = DeleteRecursive(pRoot->pRight, pReplaceableNode->Data);

                Node* pReplaceableNode = GetPredecessor(pRoot);
                pRoot->Data = pReplaceableNode->Data;
                pRoot->pLeft = DeleteRecursive(pRoot->pLeft, pReplaceableNode->Data);
            }
        }

        return pRoot;
    }
}

Node* Floor(Node* pRoot, const int oData)
{
    Node* pCurrent = pRoot;
    Node* pFloor = nullptr;
    while (nullptr != pCurrent)
    {
        if (oData == pCurrent->Data)
        {
            pFloor = pCurrent;
            break;
        }
        else if (oData < pCurrent->Data)
            pCurrent = pCurrent->pLeft;
        else
        {
            pFloor = pCurrent;
            pCurrent = pCurrent->pRight;
        }
    }

    return pFloor;
}

Node* Ceil(Node* pRoot, const int oData)
{
    Node* pCurrent = pRoot;
    Node* pCeil = nullptr;
    while (nullptr != pCurrent)
    {
        if (oData == pCurrent->Data)
        {
            pCeil = pCurrent;
            break;
        }
        else if (oData > pCurrent->Data)
            pCurrent = pCurrent->pRight;
        else
        {
            pCeil = pCurrent;
            pCurrent = pCurrent->pLeft;
        }
    }

    return pCeil;
}

/*
For every element of the array, 
one needs to find the Ceiling on Left Side
*/
void CeilOnLeft(vector<int>& oInput)
{ 
    set<int> oSet;
    for (auto& oData : oInput)
    {
        auto oCeil = oSet.lower_bound(oData);
        if (oCeil != oSet.end())
            cout << *oCeil << " ";
        else
            cout << -1 << " ";

        oSet.insert(oData);
    }
}

namespace KthSmallestElement
{
    class Node
    {
    public:
        int Data;
        int oLeftCount;
        Node* pLeft;
        Node* pRight;
        Node(int val)
        {
            this->Data = val;
            this->oLeftCount = 0;
            this->pLeft = nullptr;
            this->pRight = nullptr;
        }
    };

    Node* Insert(Node* pRoot, const int oData)
    {
        if (nullptr == pRoot)
            pRoot = new Node(oData);
        else if (oData > pRoot->Data) {
            pRoot->pRight = Insert(pRoot->pRight, oData);
        }
        else if (oData < pRoot->Data) {
            pRoot->oLeftCount = pRoot->oLeftCount + 1;
            pRoot->pLeft = Insert(pRoot->pLeft, oData); 
        }
        return pRoot;
    }

    /*
    Log(N), 1
    */
    Node* GetKthSmallestElement(Node* pRoot, int k)
    {
        if (nullptr == pRoot)
            return nullptr;
        else if (pRoot->oLeftCount + 1 == k)
            return pRoot;
        else if (pRoot->oLeftCount + 1 > k) {
            return GetKthSmallestElement(pRoot->pLeft, k);
        }
        else {
            return GetKthSmallestElement(pRoot->pRight, k - pRoot->oLeftCount - 1);
        }
    }


    Node* GetKthSmallestElementBF(Node* pRoot, int k, int& nCount)
    {
        if (nullptr == pRoot)
            return nullptr;

        Node* pNode = GetKthSmallestElementBF(pRoot->pLeft, k, nCount);
        if (pNode != nullptr)
            return pNode;

        ++nCount;
        if (nCount == k)
            return pRoot;

        return GetKthSmallestElementBF(pRoot->pRight, k, nCount);
    }
}

namespace CheckBST
{
    bool IsBST(Node* pRoot, int oMin, int oMax)
    {
        if (nullptr == pRoot)
            return true;

        if ((pRoot->Data < oMax && pRoot->Data > oMin)
            && IsBST(pRoot->pLeft, oMin, pRoot->Data)
            && IsBST(pRoot->pRight, pRoot->Data, oMax))
            return true;

        return false;
    }

    /*
    If Inorder traversal is strictly increasing order
    then it is BST
    */
    bool IsBSTII(Node* pRoot, int& oPrev)
    {
        if (nullptr == pRoot)
            return true;

        if (!IsBSTII(pRoot->pLeft, oPrev) || pRoot->Data <= oPrev)
            return false;

        oPrev = pRoot->Data;

        return IsBSTII(pRoot->pRight, oPrev);
    }

    bool CheckBST(Node* pRoot) {
        return IsBST(pRoot, INT_MIN, INT_MAX);
    }
}


Node* Find(Node* pRoot, int oData)
{
    Node* pCurrent = pRoot;
    while (nullptr != pCurrent)
    {
        if (pCurrent->Data == oData)
            return pCurrent;
        else if (pCurrent->Data > oData)
            pCurrent = pCurrent->pLeft;
        else
            pCurrent = pCurrent->pRight;
    }

    return pCurrent;
}

Node* GetInorderSuccesor(Node* pRoot, int oData)
{
    Node* pTarget = Find(pRoot, oData);
    if (nullptr != pTarget)
    {
        // Case: 1 When rightSubtree Exist
        if (nullptr != pTarget->pRight)
        {
            Node* pSuccesor = pTarget->pRight;
            while (nullptr != pSuccesor->pLeft)
                pSuccesor = pSuccesor->pLeft;

            return pSuccesor;
        }
        // Case: 2 Where we need to look for ancestors
        else
        {
            Node* pAncestor = pRoot;
            Node* pSuccessor = nullptr;
            while (pTarget != pAncestor)
            {
                if (pAncestor->Data > pTarget->Data)
                {
                    pSuccessor = pAncestor; // So far this is deepest node for which Target node is in left
                    pAncestor = pAncestor->pLeft;
                }
                else
                    pAncestor = pAncestor->pRight;
            }

            return pSuccessor;
        }
    }

    return nullptr;
}

Node* GetInorderPredecessor(Node* pRoot, int oData)
{
    Node* pTarget = Find(pRoot, oData);
    if (nullptr != pTarget)
    {
        // Case: 1 When leftSubtree Exist
        if (nullptr != pTarget->pLeft)
        {
            Node* Predecessor = pTarget->pLeft;
            while (nullptr != Predecessor->pRight)
                Predecessor = Predecessor->pRight;

            return Predecessor;
        }
        // Case: 2 Where we need to look for ancestors
        else
        {
            Node* pAncestor = pRoot;
            Node* Predecessor = nullptr;
            while (pTarget != pAncestor)
            {
                if (pAncestor->Data < pTarget->Data)
                {
                    Predecessor = pAncestor; // So far this is deepest node for which Target node is in right
                    pAncestor = pAncestor->pRight;
                }
                else
                    pAncestor = pAncestor->pLeft;
            }

            return Predecessor;
        }
    }

    return nullptr;
}

void GetInorderSuccPred(Node* pRoot, int oData, Node*& pPre, Node*& pSucc)
{
    if (nullptr == pRoot)
        return;

    if (oData == pRoot->Data)
    {
        if (nullptr != pRoot->pLeft)
        {
            Node* pPredecessor = pRoot->pLeft;
            while (nullptr != pPredecessor->pRight)
                pPredecessor = pPredecessor->pRight;

            pPre = pPredecessor;
        }

        if (nullptr != pRoot->pRight)
        {
            Node* pSuccesor = pRoot->pRight;
            while (nullptr != pSuccesor->pLeft)
                pSuccesor = pSuccesor->pLeft;

            pSucc = pSuccesor;
        }
        return;
    }

    if (oData < pRoot->Data)
    {
        pSucc = pRoot;
        GetInorderSuccPred(pRoot->pLeft, oData, pPre, pSucc);
    }
    else
    {
        pPre = pRoot;
        GetInorderSuccPred(pRoot->pRight, oData, pPre, pSucc);
    }

    return;
}

/*
Given a binary search tree with two swapped nodes, 
the task is to fix the binary search tree by swapping them back.
*/
namespace FixBST
{
    void FindDefectivePair(Node* pRoot, Node*& pPrev, Node*& pFirst, Node*& pSecond)
    {
        if (nullptr == pRoot)
            return;

        FindDefectivePair(pRoot->pLeft, pPrev, pFirst, pSecond);
        if ((nullptr != pPrev) && pRoot->Data < pPrev->Data)
        {
            if (nullptr == pFirst)
                pFirst = pPrev;
            
            pSecond = pRoot;
        }
        pPrev = pRoot;
        FindDefectivePair(pRoot->pRight, pPrev, pFirst, pSecond);
    }

    void FixBSTViolation(Node* pRoot)
    {
        if (nullptr == pRoot)
            return;

        Node* pPrev = nullptr;
        Node* pFirst = nullptr;
        Node* pSecond = nullptr;
        FindDefectivePair(pRoot, pPrev, pFirst, pSecond);
        if(nullptr != pFirst)
            swap(pFirst->Data, pSecond->Data);
    }
}


namespace PairWithGivenSumInBST
{
    /*
    Method:1 Store inorder traversal in an array and do two pointer technique
    N+N, N
    */

    /*
    Method: 2
    N, N
    */
    bool IsPairExist(Node* pRoot, int oSum, unordered_set<int>& oHashSet)
    {
        if (nullptr == pRoot)
            return false;

        if (IsPairExist(pRoot->pLeft, oSum, oHashSet))
            return true;

        if (oHashSet.find(oSum - pRoot->Data) != oHashSet.end())
            return true;
        else
            oHashSet.insert(pRoot->Data);

        return IsPairExist(pRoot->pRight, oSum, oHashSet);
    }
}

/*
Given a Binary Search Tree (BST) and a range, 
print all the numbers in the BST that lie in the given range l-h(inclusive) in non-decreasing order. 
If no such element exists, an empty line will be printed.
*/
void ElementsInRange(Node* pRoot, int l, int h)
{
    if (nullptr == pRoot)
        return;

    if (pRoot->Data > l && pRoot->Data > h) 
        ElementsInRange(pRoot->pLeft, l, h); 
    else if (pRoot->Data < l && pRoot->Data < h) 
        ElementsInRange(pRoot->pRight, l, h); 
    else
    {
        ElementsInRange(pRoot->pLeft, l, h);
        cout << pRoot->Data << " ";
        ElementsInRange(pRoot->pRight, l, h);
    }
}

Node* CreateBSTFromLevelOrderTraversal(vector<int>& oInput)
{
    struct ChildCondition
    {
        pair<int, int> oLeftChild;
        pair<int, int> oRightChild;
    };

    Node* pRoot = nullptr;
    int nSize = static_cast<int>(oInput.size());
    if (nSize > 0)
    {
        int oCurrentIdx = 0;
        pRoot = new Node(oInput[oCurrentIdx++]);
        queue < pair<Node*, ChildCondition>> pQueue;
        pQueue.push(make_pair(pRoot, ChildCondition{ make_pair(INT_MIN, pRoot->Data), make_pair(pRoot->Data, INT_MAX) }));
        while ((oCurrentIdx < nSize) && !pQueue.empty())
        {
            Node* pCurrentParent = pQueue.front().first;
            pair<int, int> oLeftChild = pQueue.front().second.oLeftChild;
            pair<int, int> oRightChild = pQueue.front().second.oRightChild;

            if (oInput[oCurrentIdx] > oLeftChild.first && oInput[oCurrentIdx] < oLeftChild.second)
            {
                Node* pNode = new Node(oInput[oCurrentIdx++]);
                pCurrentParent->pLeft = pNode;
                pQueue.push(make_pair(pNode, ChildCondition{ make_pair(oLeftChild.first, pNode->Data), make_pair(pNode->Data, oLeftChild.second) }));
            }

            if ((oCurrentIdx < nSize) && oInput[oCurrentIdx] > oRightChild.first && oInput[oCurrentIdx] < oRightChild.second)
            {
                Node* pNode = new Node(oInput[oCurrentIdx++]);
                pCurrentParent->pRight = pNode;
                pQueue.push(make_pair(pNode, ChildCondition{ make_pair(oRightChild.first, pNode->Data), make_pair(pNode->Data, oRightChild.second) }));
            }
            pQueue.pop();
        }
    }

    return pRoot;
}


namespace PreOrderToBST
{
    Node* CreateBSTFromPreOrder(vector<int>& oInput, int oCurrentIdx, int oLastIdx)
    {
        if (oCurrentIdx > oLastIdx)
            return nullptr;

        Node* pNode = new Node(oInput[oCurrentIdx]);
        int oRtSubtreeIdx = oCurrentIdx + 1;

        // Find Starting index for rightSubtree
        for (int iCounter = oCurrentIdx + 1; iCounter <= oLastIdx; ++iCounter)
        {
            if (oInput[iCounter] > oInput[oCurrentIdx])
            {
                oRtSubtreeIdx = iCounter;
                break;
            }
        }

        pNode->pLeft = CreateBSTFromPreOrder(oInput, oCurrentIdx + 1, oRtSubtreeIdx - 1);
        pNode->pRight = CreateBSTFromPreOrder(oInput, oRtSubtreeIdx, oLastIdx);
        return pNode;
    }

    Node* CreateBSTFromPreOrderI(vector<int>& oInput, int& oCurrentIdx, int oMin, int oMax)
    {
        if (oCurrentIdx >= static_cast<int>(oInput.size()))
            return nullptr;

        
        if (oInput[oCurrentIdx] > oMin && oInput[oCurrentIdx] < oMax)
        {
            Node* pNode = new Node(oInput[oCurrentIdx++]);
            pNode->pLeft = CreateBSTFromPreOrderI(oInput, oCurrentIdx, oMin, pNode->Data);
            pNode->pRight = CreateBSTFromPreOrderI(oInput, oCurrentIdx, pNode->Data, oMax);
            return pNode;
        }

        return nullptr;
    }
}

 
void PreOrder(Node* pRoot)
{
    if (nullptr != pRoot)
    {
        cout << pRoot->Data << " ";
        PreOrder(pRoot->pLeft);
        PreOrder(pRoot->pRight);
    }
}

void PostOrder(Node* pRoot)
{
    if (nullptr != pRoot)
    { 
        PostOrder(pRoot->pLeft);
        PostOrder(pRoot->pRight);
        cout << pRoot->Data << " ";
    }
}


namespace Iterators
{
    class InorderIterator
    {
    public:
        InorderIterator(const Node* pRoot)
        {
            this->pRoot = pRoot;
            this->pCurrent = pRoot;
        }

        bool End()
        {
            return pStack.empty() && (nullptr == pCurrent);
        }

        bool Next()
        { 
            if (!pStack.empty()) {
                const Node* pNode = pStack.top();
                pStack.pop();
                if (nullptr != pNode->pRight)
                    pCurrent = pNode->pRight;
            }

            while (nullptr != pCurrent) {
                pStack.push(pCurrent);
                pCurrent = pCurrent->pLeft;
            }
             
            return pStack.empty() == false;
        }

        const Node* Current()
        {
            if (!pStack.empty()) 
                return pStack.top();
            else
                return nullptr;
        }

    private:
        stack<const Node*> pStack;
        const Node* pCurrent;
        const Node* pRoot;
    };
}

// Nodes At distance k
// Smaller on Right
// DLL to BST

int main()
{
    vector<int> oInput{ 40, 30, 32, 35, 80, 90, 100, 120 };
    int oCurrentIdx = 0;
    Node* pNode = PreOrderToBST::CreateBSTFromPreOrderI(oInput, oCurrentIdx, INT_MIN, INT_MAX);
    //PostOrder(pNode);
    Iterators::InorderIterator* pItr = new Iterators::InorderIterator(pNode);
    while (pItr->Next())
        cout << pItr->Current()->Data << " ";





   // CeilOnLeft(oInput);

    KthSmallestElement::Node* pRoot = nullptr;
    for (auto& oData : oInput)
        pRoot = KthSmallestElement::Insert(pRoot, oData);

    int nCount = 0;
    KthSmallestElement::Node* k1 = KthSmallestElement::GetKthSmallestElementBF(pRoot, 4, nCount);
    nCount = 0;
    KthSmallestElement::Node* k2 = KthSmallestElement::GetKthSmallestElementBF(pRoot, 8, nCount);
    nCount = 0;
    KthSmallestElement::Node* k3 = KthSmallestElement::GetKthSmallestElementBF(pRoot, 2, nCount);

    // cout << Search::SearchIterative(pRoot, 24) << endl;
    // cout << Search::SearchIterative(pRoot, 15) << endl;
    // cout << Search::SearchIterative(pRoot, 70) << endl;
    // cout << Search::SearchIterative(pRoot, 75) << endl;
    // 
    // pRoot = Delete::DeleteRecursive(pRoot, 24);
    // pRoot = Delete::DeleteRecursive(pRoot, 25);
    // pRoot = Delete::DeleteRecursive(pRoot, 20);

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
