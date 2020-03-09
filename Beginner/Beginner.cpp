// Basic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <algorithm>
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
    if ((nullptr == pNode) || (nullptr == pNode->pNext))
    {
        if (xLastData == pNode->Data)
        {
            delete(pNode);
            pNode = nullptr;
        } 
        return pNode;
    }
        

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



int main()
{
    vector<int> oLeft{ 3, 5, 2, 1, 4, 3, 9, 7, 8, 5, 6 };
    //vector<int> oRight{ 2, 4, 6, 8, 10 };
    // sort(oInput.begin(), oInput.end());
    Node* pLeft = CreateLinkedList(oLeft, 0);
    Node* pHead = MergeSort(pLeft);
    PrintLinkedList(pHead);
    cout << endl;
    pHead = ReverseBetween(pHead, 4, 9);
    PrintLinkedList(pHead);
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