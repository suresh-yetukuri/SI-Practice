// AVL-Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node
{
public:
    int Data;
    int Height; 
    int BalanceFactor;
    Node* pLeft;
    Node* pRight;
    Node(int val)
    {
        this->Data = val;
        this->Height = 1; 
        this->BalanceFactor = 0;
        this->pLeft = nullptr;
        this->pRight = nullptr;
    }

    void Update()
    {
        int oLeftHeight = (nullptr == pLeft) ? 0 : pLeft->Height;
        int oRightHeight = (nullptr == pRight) ? 0 : pRight->Height;
        this->Height = 1 + max(oLeftHeight, oRightHeight);
        this->BalanceFactor = oRightHeight - oLeftHeight;
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

Node* Insert(Node* pRoot, const int oData)
{
    if (nullptr == pRoot)
        return new Node(oData);
    else if (oData > pRoot->Data)
        pRoot->pRight = Insert(pRoot->pRight, oData);
    else
        pRoot->pLeft = Insert(pRoot->pLeft, oData);

    pRoot->Update();
    return Balance(pRoot);
}

Node* GetPredecessor(Node* pNode)
{
    Node* pCurrent = pNode->pLeft;
    while (nullptr != pCurrent && nullptr != pCurrent->pRight)
        pCurrent = pCurrent->pRight;

    return pCurrent;
}

Node* GetSuccessor(Node* pNode)
{
    Node* pCurrent = pNode->pRight;
    while (nullptr != pCurrent && nullptr != pCurrent->pLeft)
        pCurrent = pCurrent->pLeft;

    return pCurrent;
}

Node* Delete(Node* pRoot, const int oData)
{

    if (nullptr != pRoot)
    {
        if (oData > pRoot->Data)
            pRoot->pRight = Delete(pRoot->pRight, oData);
        else if (oData < pRoot->Data)
            pRoot->pLeft = Delete(pRoot->pLeft, oData);
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
                if (pRoot->pLeft->Height > pRoot->pRight->Height)
                {
                    Node* pReplaceableNode = GetPredecessor(pRoot);
                    pRoot->Data = pReplaceableNode->Data;
                    pRoot->pLeft = Delete(pRoot->pLeft, pReplaceableNode->Data);
                }
                else
                {
                    Node* pReplaceableNode = GetSuccessor(pRoot);
                    pRoot->Data = pReplaceableNode->Data;
                    pRoot->pRight = Delete(pRoot->pRight, pReplaceableNode->Data);
                }
            }
        }

        if (nullptr != pRoot) {
            pRoot->Update();
            pRoot = Balance(pRoot);
        }
    }
      
    return pRoot;
}

int main()
{
    vector<int> oInput{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 5, 2 };
    Node* pRoot = nullptr;
    for (auto& oData : oInput)
        pRoot = Insert(pRoot, oData);



    pRoot = Delete(pRoot, 40);
    pRoot = Delete(pRoot, 60);
    pRoot = Delete(pRoot, 80);
    pRoot = Delete(pRoot, 40);
    pRoot = Delete(pRoot, 100);
    pRoot = Delete(pRoot, 90);

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
