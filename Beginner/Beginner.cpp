// Basic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Node
{
public:
    int Data;
    Node* pNext;
    Node() :Node(0, nullptr)
    { }

    Node(int oData) :Node(oData, nullptr)
    { }

    Node(int oData, Node* oNext)
    {
        this->Data = oData;
        this->pNext = oNext;
    }
};

/*
Create Linked List from array
*/
Node* CreateLinkedList(vector<int>& oInput, int Idx)
{
    const int nSize = static_cast<int>(oInput.size());
    if (nSize == Idx)
        return nullptr;

    Node* pNewNode = new Node(oInput[Idx]);
    pNewNode->pNext = CreateLinkedList(oInput, Idx + 1);
    return pNewNode;
}

/*
Print Linked List
*/
void PrintLinkedList(Node* pNode)
{
    if (nullptr == pNode)
        return;

    cout << pNode->Data << " ";
    PrintLinkedList(pNode->pNext);
}

/*
Print Linked List Reverse
*/
void PrintLinkedListReverse(Node* pNode)
{
    if (nullptr == pNode)
        return;

    PrintLinkedListReverse(pNode->pNext);
    cout << pNode->Data << " ";
}

/*
Get Length Of Linked List
*/
int GetLengthOfList(Node* pNode)
{
    if (nullptr == pNode)
        return 0;

    return 1 + GetLengthOfList(pNode->pNext);
}

/*
Insert Node at particular position & return Head node
1. If -ve pos, insert at head
2. If out of range, insert at last
(Assume 1 based position)
*/
Node* Insert(Node* pNode, int oPos, int xData)
{
    if (nullptr == pNode)
        return new Node(xData);

    if (1 >= oPos)
    {
        Node* pNewNode = new Node(xData, pNode);
        return pNewNode;
    }

    pNode->pNext = Insert(pNode->pNext, oPos - 1, xData);
    return pNode;
}

/*
Insert Node at sorted singly linked list
*/
Node* Insert(Node* pNode, const int xData)
{
    if (nullptr == pNode)
        return new Node(xData);

    if (xData <= pNode->Data)
    {
        Node* pNewNode = new Node(xData, pNode);
        return pNewNode;
    }

    pNode->pNext = Insert(pNode->pNext, xData);
    return pNode;
}

/*
Delete Node at particular position
If -ve||0||out of range position
don't delete anything
*/
Node* Delete(Node* pNode, int oPos)
{
    if (nullptr == pNode || 1 > oPos)
        return pNode;

    if (1 == oPos)
    {
        Node* pNodeTBD = pNode;
        pNode = pNode->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        return pNode;
    }

    pNode->pNext = Delete(pNode->pNext, oPos - 1);
    return pNode;
}

/*
Delete all occurences of given element
*/
Node* DeleteAll(Node* pNode, const int xData)
{
    if (nullptr == pNode)
        return pNode;

    if (xData == pNode->Data)
    {
        Node* pNodeTBD = pNode;
        pNode = pNode->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        return DeleteAll(pNode, xData);
    }

    pNode->pNext = DeleteAll(pNode->pNext, xData);
    return pNode;
}

/*
Given Singly Sorted Linked List
return the Linked List with distinct
elements.
Initially we can pass INT_MIN as xLastData
*/
Node* Distinct(Node* pNode, const int xLastData)
{
    if (nullptr == pNode)
        return pNode;
        

    if (xLastData == pNode->Data)
    {
        Node* pNodeTBD = pNode;
        pNode = pNode->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        return Distinct(pNode, xLastData);
    }

    pNode->pNext = Distinct(pNode->pNext, pNode->Data);
    return pNode;
}


Node* DistinctIterative(Node* pNode)
{
    if (nullptr == pNode)
        return pNode;

    Node* pHead = nullptr;
    Node* pCurrent = nullptr;
    int oPrevData = INT_MIN;

    do
    {
        if (oPrevData == pNode->Data)
        {
            Node* pNodeTBD = pNode;
            pNode = pNode->pNext;
            delete(pNodeTBD); pNodeTBD = nullptr; 
        }
        else
        {
            if (nullptr == pHead)
                pHead = pCurrent = pNode;
            else
            {
                pCurrent->pNext = pNode;
                pCurrent = pCurrent->pNext; 
            }
            oPrevData = pNode->Data;
            pNode = pNode->pNext;
        }

    } while (nullptr != pNode);
    

    pCurrent->pNext = nullptr;
    return pHead;
}

/*
Given Singly Sorted Linked List
return the Linked List with unique
elements.
*/
Node* Unique(Node* pNode)
{
    if ((nullptr == pNode) || (nullptr == pNode->pNext))
        return pNode;

    if (pNode->Data == pNode->pNext->Data)
    {
        // Look out for next valid node. 
        // Till that time delete all nodes
        const int NonUniqueVal = pNode->Data;
        Node* pValidNode = pNode;
        while ((nullptr != pValidNode) && (NonUniqueVal == pValidNode->Data))
        {
            Node* pNodeTBD = pValidNode;
            pValidNode = pValidNode->pNext;
            delete(pNodeTBD); pNodeTBD = nullptr;
        }

        return Unique(pValidNode);
    }

    pNode->pNext = Unique(pNode->pNext);
    return pNode;
}

Node* UniqueIterative(Node* pNode) {
    if ((nullptr == pNode) || (nullptr == pNode->pNext))
        return pNode;

    Node* pHead = nullptr;
    Node* pCurrent = nullptr;

    do {
        if ((nullptr != pNode->pNext) && (pNode->Data == pNode->pNext->Data))
        {
            const int NonUniqueData = pNode->Data;
            Node* pValidNode = pNode;
            while ((nullptr != pValidNode) && (NonUniqueData == pValidNode->Data))
            {
                Node* pNodeTBD = pValidNode;
                pValidNode = pValidNode->pNext;
                delete(pNodeTBD); pNodeTBD = nullptr;
            }

            pNode = pValidNode;
        }
        else
        {
            if (nullptr == pHead)
                pHead = pCurrent = pNode;
            else {
                pCurrent->pNext = pNode;
                pCurrent = pCurrent->pNext;
            }

            pNode = pNode->pNext;
        }
    } while (nullptr != pNode);

    if (nullptr != pCurrent)
        pCurrent->pNext = nullptr;

    return pHead;
}

/*
Reverse the List
Recursively
*/
Node* Reverse(Node* pNode)
{
    if ((nullptr == pNode) || (nullptr == pNode->pNext))
        return pNode;

    Node* pRHeadNode = Reverse(pNode->pNext);
    pNode->pNext->pNext = pNode;
    pNode->pNext = nullptr;
    return pRHeadNode;
}

/*
Swap In Pairs
*/
Node* SwapInPairs(Node* pNode)
{
    if ((nullptr == pNode) || (nullptr == pNode->pNext))
        return pNode;

    // Swap Nodes
    Node* pPairHeadNode = pNode->pNext;
    pNode->pNext = pPairHeadNode->pNext;
    pPairHeadNode->pNext = pNode;

    pNode->pNext = SwapInPairs(pNode->pNext);
    return pPairHeadNode;
}


Node* SwapNode(Node* pFirst, Node* pSecond)
{
    pSecond->pNext = pFirst;
    pFirst->pNext = nullptr;
    return pSecond;
}

Node* pairWiseSwap(Node* pHead) {
    if (nullptr == pHead ||
        nullptr == pHead->pNext)
        return pHead;

    Node* pCurrent = pHead;
    Node* pPrev = nullptr;
    Node* pFirst = nullptr;
    Node* pSec = nullptr;

    while ((nullptr != pCurrent) || (nullptr != pFirst && nullptr != pSec))
    {
        if (nullptr != pFirst && nullptr != pSec)
        {
            Node* pNode = SwapNode(pFirst, pSec);
            if (nullptr != pPrev)
                pPrev->pNext = pNode;
            else
                pHead = pNode;

            pPrev = pFirst;
            pFirst = pSec = nullptr;
        }

        if (nullptr == pFirst)
            pFirst = pCurrent;
        else
            pSec = pCurrent;

        if (nullptr != pCurrent)
            pCurrent = pCurrent->pNext;
    }

    if (nullptr != pFirst)
        pPrev->pNext = pFirst;

    return pHead;
}

/*
Find Mid of the Linked List
*/
Node* FindMid(Node* pHead, bool IsLower)
{
    Node* pSlow = pHead;
    Node* pFast = pHead;
    Node* pSPrev = nullptr;
    while ((nullptr != pFast) && (nullptr != pFast->pNext))
    {
        pSPrev = pSlow;
        pSlow = pSlow->pNext;
        pFast = pFast->pNext->pNext;
    }

    if(IsLower && (nullptr == pFast))
        return pSPrev;
     
    return pSlow;
}

/*
Check  if given Linked List is Palindrome
or not
*/
bool IsPalindrome(Node* pHead)
{
    if ((nullptr == pHead) || (nullptr == pHead->pNext))
        return true;

    Node* pMid = FindMid(pHead, true);
    Node* pLeft = pHead;
    Node* pRight = pMid->pNext;
    pRight = Reverse(pRight);
    Node* pRightCurrent = pRight;

    bool IsPalindrome = true;
    while (nullptr != pRightCurrent)
    {
        if (pLeft->Data != pRightCurrent->Data) {
            IsPalindrome = false;
            break;
        }

        pLeft = pLeft->pNext;
        pRightCurrent = pRightCurrent->pNext;
    }

    pRight = Reverse(pRight);
    pMid->pNext = pRight;
    return IsPalindrome;
}


bool isPalindrome(Node* pHead)
{
    if (nullptr == pHead
        || nullptr == pHead->pNext)
        return pHead;

    unordered_map<Node*, Node*> oHashMap;
    Node* pCurrent = pHead;
    Node* pPrev = nullptr;
    while (nullptr != pCurrent)
    {
        oHashMap[pCurrent] = pPrev;
        pPrev = pCurrent;
        pCurrent = pCurrent->pNext;
    }

    Node* pForward = pHead;
    Node* pBackward = pPrev;

    while (pForward != pBackward)
    {
        if (pForward->Data != pBackward->Data)
            return false;

        pForward = pForward->pNext;
        pBackward = oHashMap[pBackward];
    }

    return true;
}
/*
Merge two sorted linked list
*/
Node* Merge(Node* pLeft, Node* pRight)
{
    if (nullptr == pLeft)
        return pRight;
    
    if (nullptr == pRight)
        return pLeft;

    Node* pHead = nullptr;
    Node* pCurrent = nullptr;
    if (pLeft->Data < pRight->Data) {
        pHead = pLeft;
        pLeft = pLeft->pNext;
    } else {
        pHead = pRight;
        pRight = pRight->pNext;
    }

    pCurrent = pHead;
    while ((nullptr != pLeft) && (nullptr != pRight))
    {
        if (pLeft->Data < pRight->Data) {
            pCurrent->pNext = pLeft;
            pLeft = pLeft->pNext;
        } else {
            pCurrent->pNext = pRight;
            pRight = pRight->pNext;
        }
        pCurrent = pCurrent->pNext;
    }

    if (nullptr != pLeft)
        pCurrent->pNext = pLeft;
    else
        pCurrent->pNext = pRight;

    return pHead;
}

/*
Merge Sort
*/
Node* MergeSort(Node* pHead)
{
    if ((nullptr == pHead) || (nullptr == pHead->pNext))
        return pHead;

    Node* pMid = FindMid(pHead, true);
    Node* pRight = pMid->pNext;
    pMid->pNext = nullptr;
    return Merge(MergeSort(pHead), MergeSort(pRight));
}

/*
Reverse Linked List at m & n position
*/
Node* ReverseBetween(Node* pNode, int m, int n)
{
    if ((nullptr == pNode) || (nullptr == pNode->pNext))
        return pNode;

    if (1 == m)
    {
        Node* pLeft = pNode;
        Node* pRight = pLeft;
        while (1 < n) 
        {
            pRight = pRight->pNext;
            --n;
        }

        Node* pRemaining = pRight->pNext;
        pRight->pNext = nullptr;
        pRight = Reverse(pLeft);
        pLeft->pNext = pRemaining;
        return pRight;
    }

    pNode->pNext = ReverseBetween(pNode->pNext, m - 1, n - 1);
    return pNode;
}

Node* ReverseBetweenIterative(Node* pHead, int m, int n)
{
    if ((nullptr == pHead) || (nullptr == pHead->pNext) || (m == n))
        return pHead;

    Node* pFBTail = nullptr;
    Node* pMBHead = nullptr;
    Node* pMBTail = nullptr;
    Node* pLBHead = nullptr;

    Node* pCurrent = pHead;
    if (m > 1) {
        for (int iCounter = 1; iCounter < (m - 1); ++iCounter)
            pCurrent = pCurrent->pNext;

        pMBHead = pCurrent->pNext;
        pFBTail = pCurrent;
        pCurrent->pNext = nullptr;
        pCurrent = pMBHead;
    }
    else {
        pMBHead = pCurrent;
    }

    for (int iCounter = m; iCounter < n; ++iCounter)
        pCurrent = pCurrent->pNext;

    pMBTail = pCurrent;
    pLBHead = pCurrent->pNext;
    pCurrent->pNext = nullptr;

    if (nullptr != pFBTail)
        pFBTail->pNext = Reverse(pMBHead);
    else
        pHead = Reverse(pMBHead);

    pMBHead->pNext = pLBHead;
    return pHead;
}


/*
Reorder Linked List
*/
Node* Reorder(Node* pHead)
{
    if ((nullptr == pHead) || (nullptr == pHead->pNext))
        return pHead;

    Node* pMid = FindMid(pHead, true);
    Node* pRight = pMid->pNext;
    pMid->pNext = nullptr;
    pRight = Reverse(pRight);
    Node* pCurrent = pHead;
    while (nullptr != pRight)
    {
        Node* pRightNext = pRight->pNext;
        Node* pCurrentNext = pCurrent->pNext;
        pCurrent->pNext = pRight;
        pRight->pNext = pCurrentNext;
        pCurrent = pCurrentNext;
        pRight = pRightNext;
    }

    return pHead;
}

/*
Remove Nth Node from end of linked list
*/
namespace RemoveRecursive
{
    Node* Remove(Node* pNode, int& oPos, bool& IsDeleted)
    {
        if (nullptr == pNode)
            return pNode;

        pNode->pNext = Remove(pNode->pNext, oPos, IsDeleted);
        if (!IsDeleted && (1 == oPos || (0 >= oPos)))
        {
            Node* pNodeTBD = pNode;
            pNode = pNode->pNext;
            delete(pNodeTBD); pNodeTBD = nullptr;
            --oPos;
            IsDeleted = true;
            return pNode;
        }

        if (!IsDeleted)
            --oPos;

        return pNode;
    }

    Node* RemoveNthNode(Node* pHead, int xPos)
    {
        bool IsDeleted = false;
        Node* pNewHead = Remove(pHead, xPos, IsDeleted);
        if (!IsDeleted)
        {
            Node* pNodeTBD = pNewHead;
            pNewHead = pNewHead->pNext;
            delete(pNodeTBD); pNodeTBD = nullptr;
        }

        return pNewHead;
    }
}

/*
Remove Nth Node from end of linked list
*/
namespace RemoveIterative
{
    Node* RemoveNthNode(Node* pHead, int xPos)
    {
        if (nullptr == pHead)
            return pHead;

        int nSize = GetLengthOfList(pHead);
        Node* pNodeTBD = nullptr;
        if (xPos < nSize)
        {
            Node* pCurrent = pHead;
            for (int iCounter = 1; iCounter < (nSize - xPos); ++iCounter)
                pCurrent = pCurrent->pNext;

            pNodeTBD = pCurrent->pNext;
            pCurrent->pNext = pNodeTBD->pNext;

        }
        else {
            pNodeTBD = pHead;
            pHead = pNodeTBD->pNext;
        }

        delete(pNodeTBD); pNodeTBD = nullptr;
        return pHead;
    }
}

/*
InsertionSort
*/
namespace InsertionSort
{
    Node* Insert(Node* pNode, Node* xNode)
    {
        if (nullptr == pNode)
            return xNode;

        if (xNode->Data <= pNode->Data)
        {
            xNode->pNext = pNode;
            return xNode;
        }

        pNode->pNext = Insert(pNode->pNext, xNode);
        return pNode;
    }

    Node* InsertionSort(Node* pHead)
    {

        Node* pCurrent = pHead->pNext;
        Node* pPrev = pHead;
        while (nullptr != pCurrent)
        {
            Node* pNext = pCurrent->pNext;
            pCurrent->pNext = nullptr;
            pPrev->pNext = nullptr;
            pHead = Insert(pHead, pCurrent);
            if ((nullptr != pPrev->pNext) && (pCurrent == pPrev->pNext))
                pPrev = pCurrent;

            pCurrent = pNext;
        }
        
        return pHead;
    }
}
 
namespace Partitioning
{ 
    Node* Partition(Node* pCurrent, const int xData, Node* pRightHead)
    {
        if (nullptr == pCurrent)
            return pCurrent;

        if (xData <= pCurrent->Data)
        {
            Node* pNext = pCurrent->pNext;
            pRightHead->pNext = pCurrent;
            pCurrent->pNext = nullptr;
            return Partition(pNext, xData, pRightHead->pNext);
        }

        pCurrent->pNext = Partition(pCurrent->pNext, xData, pRightHead);
        return pCurrent;
    }

    Node* PartitionPreservingOrder(Node* pHead, int xData)
    {
        if (nullptr == pHead || nullptr == pHead->pNext)
            return pHead;

        Node* pGreaterHead = new Node(INT_MIN, nullptr);
        pHead = Partition(pHead, xData, pGreaterHead);
        Node* pNodeTBD = pGreaterHead;
        pGreaterHead = pGreaterHead->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        if (nullptr != pHead)
        {
            Node* pCurrent = pHead;
            while (nullptr != pCurrent->pNext)
                pCurrent = pCurrent->pNext;

            pCurrent->pNext = pGreaterHead;
        }
        else
            pHead = pGreaterHead;
       
        return pHead;
    }
}

namespace PartitioningEasy
{
    Node* Partition(Node* pCurrent, const int xData, Node* pLeftTail, Node* pRightHead)
    {
        if (nullptr == pCurrent) {
            return pCurrent;
        }

        if (xData <= pCurrent->Data)
        {
            Node* pNext = pCurrent->pNext;
            pRightHead->pNext = pCurrent;
            pCurrent->pNext = nullptr;
            return Partition(pNext, xData, pLeftTail, pRightHead->pNext);
        }

        pLeftTail->pNext = pCurrent;
        pCurrent->pNext = Partition(pCurrent->pNext, xData, pLeftTail, pRightHead);
        return pCurrent;
    }

    Node* PartitionPreservingOrder(Node* pHead, int xData)
    {
        if (nullptr == pHead || nullptr == pHead->pNext)
            return pHead;

        Node* pGreaterHead = new Node(INT_MIN, nullptr);
        Node* pLesserTail = new Node(INT_MIN, nullptr);
        pHead = Partition(pHead, xData, pLesserTail, pGreaterHead);

        // Delete Dummy nodes
        Node* pNodeTBD = pGreaterHead;
        pGreaterHead = pGreaterHead->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        pNodeTBD = pLesserTail;
        pLesserTail = pLesserTail->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        if (nullptr != pLesserTail)
            pLesserTail->pNext = pGreaterHead;
        else
            pHead = pGreaterHead;
             
        return pHead;
    }
}

namespace Rotate
{
    Node* RotateIterative(Node* pHead, int kSize)
    {
        if (nullptr == pHead || nullptr == pHead->pNext)
            return pHead;

        int nSize = GetLengthOfList(pHead);
        kSize = kSize % nSize;
        if (0 == kSize)
            return pHead;
         
        Node* pCurrent = pHead;
        for(int iCounter = 1; iCounter < (nSize-kSize); ++iCounter)
            pCurrent = pCurrent->pNext;

        Node* pNewHead = pCurrent->pNext;
        pCurrent->pNext = nullptr;

        pCurrent = pNewHead;
        while (nullptr != pCurrent->pNext)
            pCurrent = pCurrent->pNext;

        pCurrent->pNext = pHead;
        return pNewHead;
    }
}

namespace ReverseInGroup

{
    namespace Recursive
    {
        Node* ReverseIteratively(Node* pHead, Node** pNextHead, int kGroup)
        {
            if (nullptr == pHead || nullptr == pHead->pNext)
                return pHead;

            Node* pCurrent = pHead;
            Node* pNext = nullptr;
            Node* pPrev = nullptr;
            int kCounter = 0;
            while (nullptr != pCurrent && kCounter < kGroup)
            {
                ++kCounter;
                pNext = pCurrent->pNext;
                pCurrent->pNext = pPrev;
                pPrev = pCurrent;
                pCurrent = pNext;
            }

            *pNextHead = pCurrent;
            return pPrev;
        }

        Node* ReverseInGroup(Node* pHead, int kGroup)
        {
            if (nullptr == pHead)
                return pHead;

            Node* pNextHead = nullptr;
            Node* pNode = ReverseIteratively(pHead, &pNextHead, kGroup);
            pHead->pNext = ReverseInGroup(pNextHead, kGroup);
            return pNode;
        }
    }

    namespace Iterative
    {
        Node* ReverseInGroup(Node* pHead, int kGroup)
        {
            if (nullptr == pHead)
                return pHead;

            Node* pMainHead = nullptr;
            Node* pGroupTail = nullptr;
            Node* pCurrent = pHead;
            while (nullptr != pCurrent)
            {
                int kCounter = 0;
                Node* pPrev = nullptr;
                Node* pCurrentGroupTail = pCurrent;

                while ((nullptr != pCurrent) && (kCounter < kGroup))
                {
                    Node* pNext = pCurrent->pNext;
                    pCurrent->pNext = pPrev;
                    pPrev = pCurrent;
                    pCurrent = pNext;
                    ++kCounter;
                }

                if (nullptr == pMainHead)
                    pMainHead = pPrev;
                else {
                    if(nullptr != pGroupTail)
                        pGroupTail->pNext = pPrev;
                }  

                pGroupTail = pCurrentGroupTail;
            }
             
            return pMainHead;
        }
    }
    
}

Node* ListCycle(Node* pHead)
{
    if (nullptr == pHead || nullptr == pHead->pNext)
        return nullptr;

    Node* pSlow = pHead;
    Node* pFast = pHead;

    while ((nullptr != pFast) && (nullptr != pFast->pNext))
    {
        pSlow = pSlow->pNext;
        pFast = pFast->pNext->pNext;
        if (pSlow == pFast)
            break;
    }

    if (pSlow == pFast && (nullptr != pFast))
    {
        // Cycle is detected
        pSlow = pHead;
        while (pSlow != pFast)
        {
            pSlow = pSlow->pNext;
            pFast = pFast->pNext;
        }

        return pSlow;
    }

    return nullptr;
}

namespace AddList
{
    Node* DeleteTrailingZeroes(Node* pNode)
    {
        if (nullptr == pNode)
            return nullptr;

        pNode->pNext = DeleteTrailingZeroes(pNode->pNext);
        if ((0 == pNode->Data) && (nullptr == pNode->pNext))
        {
            Node* pNodeTBD = pNode;
            delete(pNodeTBD); pNodeTBD = nullptr;
            return nullptr;
        }

        return pNode;
    }

    Node* AddList(Node* pLeft, Node* pRight)
    {
        Node* pResult = nullptr;
        Node* pCurrent = pResult = new Node(-1);
        Node* pPrev = nullptr;
        Node* pLeftCur = pLeft;
        Node* pRightCur = pRight;
        int oCarry = 0;

        while ((nullptr != pLeftCur) && (nullptr != pRightCur))
        {
            int oSum = (pLeftCur->Data) + (pRightCur->Data) + oCarry;
            oCarry = oSum / 10;
            pCurrent->pNext = new Node(oSum % 10);
            pCurrent = pCurrent->pNext;
            pLeftCur = pLeftCur->pNext;
            pRightCur = pRightCur->pNext;
        }

        Node* pRestList = (pLeftCur != nullptr) ? pLeftCur : pRightCur;
        while (nullptr != pRestList)
        {
            int oSum = (pRestList->Data) + oCarry;
            oCarry = oSum / 10;
            pCurrent->pNext = new Node(oSum % 10);
            pCurrent = pCurrent->pNext;
            pRestList = pRestList->pNext;
        }

        if (oCarry > 0) {
            pCurrent->pNext = new Node(oCarry);
            pCurrent = pCurrent->pNext;
        }



        // Delete Dummy node
        Node* pNodeTBD = pResult;
        pResult = pResult->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;

        // Delete Trailing Zeroes
        pResult = DeleteTrailingZeroes(pResult);
        return pResult;
    }

}

Node* NthFromLast(Node* pHead, int& n)
{
    if (nullptr == pHead)
    {
        --n;
        return nullptr;
    }

    auto oResult = NthFromLast(pHead->pNext, n);
    if (nullptr != oResult)
        return oResult;
    else if ((n--) == 0)
        return pHead;

    return nullptr;
}

/* Should return data of n'th node from the end of linked list.
*  head: head of the linked list
*  n: nth node from end to find
*/
int getNthFromLast(Node* head, int n)
{
    auto oResult = NthFromLast(head, n);
    if (nullptr != oResult)
        return oResult->Data;

    return -1;
}

/* Should return data of n'th node from the end of linked list.
*  head: head of the linked list
*  n: nth node from end to find
*/
//int getNthFromLast(Node* head, int n)
//{
//    auto oResult = NthFromLast(head, n);
//    if (nullptr != oResult)
//        return oResult->Data;
//
//    return -1;
//}

Node* Update(pair<Node*, Node*>& oTargetPair, Node* pCurrent)
{
    auto pNext = pCurrent->pNext;
    if (nullptr == oTargetPair.first)
        oTargetPair.first = oTargetPair.second = pCurrent;
    else
    {
        oTargetPair.second->pNext = pCurrent;
        oTargetPair.second = oTargetPair.second->pNext;
    }

    oTargetPair.second->pNext = nullptr;
    pCurrent = pNext;
    return pCurrent;
}

Node* segregate(Node* pHead) {
    if (nullptr == pHead
        || nullptr == pHead->pNext)
        return pHead;

    pair<Node*, Node*> oFrontPair;
    pair<Node*, Node*> oMiddlePair;
    pair<Node*, Node*> oBackPair;

    Node* pCurrent = pHead;
    while (nullptr != pCurrent)
    {  
        if (pCurrent->Data == 0)
            pCurrent = Update(oFrontPair, pCurrent);
        else if (pCurrent->Data == 1)
            pCurrent = Update(oMiddlePair, pCurrent);
        else
            pCurrent = Update(oBackPair, pCurrent);
    }

    pHead = new Node(-1);
    pCurrent = pHead;
    if (nullptr != oFrontPair.first) {
        pCurrent->pNext = oFrontPair.first;
        pCurrent = oFrontPair.second;
    }

    if (nullptr != oMiddlePair.first) {
        pCurrent->pNext = oMiddlePair.first;
        pCurrent = oMiddlePair.second;
    }

    if (nullptr != oBackPair.first) {
        pCurrent->pNext = oBackPair.first;
        pCurrent = oBackPair.second;
    }

    auto pNodeTBD = pHead;
    pHead = pHead->pNext;
    delete(pNodeTBD); pNodeTBD = nullptr;
    return pHead;
}

int main()
{
    unordered_map<Node*, Node*> oHash;
    oHash[nullptr] = nullptr;
    oHash.clear();
    vector<int> oLeft{ 1, 2, 2, 1, 2, 0, 2, 2 };
    vector<int> oRight{ 1};
    Node* pLeft = CreateLinkedList(oLeft, 0);
    auto oSort = segregate(pLeft);
    PrintLinkedList(oSort);


    int nth = 2;
    //auto oREsult = getNthFromLast(pLeft, nth);
    Node* oSwap = pairWiseSwap(pLeft);
    Node* pRight = CreateLinkedList(oRight, 0);
    PrintLinkedList(oSwap);
    cout << endl;
    pLeft = DistinctIterative(pLeft);
    PrintLinkedList(pLeft);
   Node* pResult = AddList::AddList(pLeft, pRight);
    cout << endl;
    PrintLinkedList(pResult);
    pLeft = ReverseInGroup::Iterative::ReverseInGroup(pLeft, 4);
    PrintLinkedList(pLeft);
    cout << endl;

    int k = 90; 
    Node* pCycle = ListCycle(pLeft);
    pLeft = Rotate::RotateIterative(pLeft, k);
    //int x = 1;
    Node* pHead = nullptr;
    PrintLinkedList(pLeft);
    cout << endl;



    cout << IsPalindrome(pHead);
    pHead = SwapInPairs(pHead);
    PrintLinkedList(pHead);
    cout << endl;
    PrintLinkedListReverse(pHead);
    cout << endl;
    pHead = Distinct(pHead, INT_MAX);
    PrintLinkedList(pHead);
    cout << endl;

    pHead = DeleteAll(pHead, 4);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = DeleteAll(pHead, 5);
    PrintLinkedList(pHead);
    cout << endl;


    pHead = Insert(pHead, 3, 3);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 6, 6);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 5, 13);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 8);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 1);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 4, -4);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 5, 1);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, -1);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Insert(pHead, 4);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Delete(pHead, 3);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Delete(pHead, 5);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = Delete(pHead, 2);
    PrintLinkedList(pHead);
    return 0;
}