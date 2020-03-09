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
    Node():Node(0, nullptr)
    { }

    Node(int oData):Node(oData, nullptr)
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

/*
Given Singly Sorted Linked List
return the Linked List with unique
elements.
*/
Node* Unique(Node* pNode)
{

    return nullptr;
}


int main()
{ 
    vector<int> oInput{4, 1, 3, 4, 2, 5, 4, 4, 1, 1, 4, 6, 7 };
    sort(oInput.begin(), oInput.end());
    Node* pHead = CreateLinkedList(oInput, 0);
    PrintLinkedList(pHead);
    cout << endl;
    PrintLinkedListReverse(pHead);
    cout << endl;
    pHead = Distinct(pHead, INT_MIN);



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
