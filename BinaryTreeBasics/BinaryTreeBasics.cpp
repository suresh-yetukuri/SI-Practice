// BinaryTreeBasics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
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


Node* Insert(Node* pRoot, int Data)
{
    if (nullptr == pRoot)
        pRoot = new Node(Data);
    else 
    {
        if (pRoot->Data < Data)
            pRoot->pRight = Insert(pRoot->pRight, Data);
        else
            pRoot->pLeft = Insert(pRoot->pLeft, Data);
    }

    return pRoot;
}


Node* BuildTree(vector<int>& oInput)
{
    Node* pRoot = nullptr;
    for (auto& val : oInput)
        pRoot = Insert(pRoot, val);

    return pRoot;
}


namespace Traversals
{
    namespace DepthFirst
    {
        void Preorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                pStack.push(pRoot);
                while (!pStack.empty())
                {
                    Node* pCurrent = pStack.top();
                    pStack.pop();

                    if (nullptr != pCurrent->pRight)
                        pStack.push(pCurrent->pRight);

                    if (nullptr != pCurrent->pLeft)
                        pStack.push(pCurrent->pLeft);

                    cout << pCurrent->Data << " ";
                }
            }
        }

        void Inorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                while ((nullptr != pRoot) || (!pStack.empty()))
                {
                    while (nullptr != pRoot)
                    {
                        pStack.push(pRoot);
                        pRoot = pRoot->pLeft;
                    }

                    Node* pCurrent = pStack.top();
                    pStack.pop();
                    cout << pCurrent->Data << " ";
                    if (nullptr != pCurrent->pRight)
                        pRoot = pCurrent->pRight;
                }
            }
        }

        void Postorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                Node* pLastProcessedNode = nullptr;
                while ((nullptr != pRoot) || (!pStack.empty()))
                {
                    while (nullptr != pRoot)
                    {
                        pStack.push(pRoot);
                        pRoot = pRoot->pLeft;
                    }

                    Node* pCurrent = pStack.top();
                    if (nullptr != pCurrent->pRight && pLastProcessedNode != pCurrent->pRight)
                        pRoot = pCurrent->pRight;
                    else {
                        cout << pCurrent->Data << " ";
                        pLastProcessedNode = pCurrent;
                        pStack.pop();
                    }
                }
            }
        }
    }

    namespace BreadthFirst
    {
        void Levelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                pQueue.push(pRoot);
                pQueue.push(nullptr); // act as a marker
                while (pQueue.size() > 1)
                {
                    Node* pCurrent = pQueue.front();
                    pQueue.pop();
                    if (nullptr == pCurrent)
                    {
                        cout << endl;
                        pQueue.push(nullptr);
                        continue;
                    }
                    cout << pCurrent->Data << " ";
                    if (nullptr != pCurrent->pLeft)
                        pQueue.push(pCurrent->pLeft);

                    if (nullptr != pCurrent->pRight)
                        pQueue.push(pCurrent->pRight);
                } 
            }
        }

        void LevelorderII(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                pQueue.push(pRoot);
                while (!pQueue.empty())
                {
                    int nSize = static_cast<int>(pQueue.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pQueue.front();
                        pQueue.pop();
                        cout << pCurrent->Data << " ";
                        if (nullptr != pCurrent->pLeft)
                            pQueue.push(pCurrent->pLeft);

                        if (nullptr != pCurrent->pRight)
                            pQueue.push(pCurrent->pRight);
                    }

                    cout << endl;
                }
            }
        }

        void ZigZagLevelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pProcessStack;
                stack<Node*> pStack;
                pProcessStack.push(pRoot);
                bool IsLRPush = false;          // For reverse ZigZagLevelorder, set IsLRPush = true;
                while (!pProcessStack.empty())
                {
                    int nSize = static_cast<int>(pProcessStack.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pProcessStack.top();
                        pProcessStack.pop();
                        cout << pCurrent->Data << " ";
                        if (IsLRPush) {
                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);

                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);
                        }
                        else 
                        {  
                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);

                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);
                        }
                    }
                    swap(pProcessStack, pStack);
                    IsLRPush = !IsLRPush;
                }
            }
        }

        void BottomUpLevelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                stack<int> pStack;
                pQueue.push(pRoot);
                while (!pQueue.empty())
                {
                    int nSize = static_cast<int>(pQueue.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pQueue.front();
                        pQueue.pop();
                        pStack.push(pCurrent->Data);
                        if (nullptr != pCurrent->pRight)
                            pQueue.push(pCurrent->pRight);

                        if (nullptr != pCurrent->pLeft)
                            pQueue.push(pCurrent->pLeft);
                    }
                    pStack.push(INT_MIN);
                }
                pStack.pop();
                while (!pStack.empty())
                {
                    int oData = pStack.top();
                    pStack.pop();
                    if (oData == INT_MIN) {
                        cout << endl;
                        continue;
                    }
                    cout << oData << " ";
                }
            }
        }

        void ZigZagBottomUpLevelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pProcessStack;
                stack<Node*> pStack;
                stack<int> pFinalStack;
                pProcessStack.push(pRoot);
                bool IsLRPush = true;
                while (!pProcessStack.empty())
                {
                    int nSize = static_cast<int>(pProcessStack.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pProcessStack.top();
                        pProcessStack.pop();
                        pFinalStack.push(pCurrent->Data);
                        if (IsLRPush) {
                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);

                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);
                        }
                        else
                        {
                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);

                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);
                        }
                    }
                    swap(pProcessStack, pStack);
                    IsLRPush = !IsLRPush;
                }

                while (!pFinalStack.empty())
                {
                    cout << pFinalStack.top() << " ";
                    pFinalStack.pop();
                }
            }
        }
    }
}

Node* DeleteTree(Node* pRoot)
{ 
    if (nullptr != pRoot)
    {
        if (nullptr != pRoot->pLeft)
            pRoot->pLeft = DeleteTree(pRoot->pLeft);

        if (nullptr != pRoot->pRight)
            pRoot->pRight = DeleteTree(pRoot->pRight);

        delete(pRoot);
        pRoot = nullptr;
    }
    return pRoot;
}


int main()
{
    vector<int> oInput{ 4, 5, 15, 0, 1, 7, 17 };
    Node* pRoot = BuildTree(oInput);
    Traversals::BreadthFirst::ZigZagBottomUpLevelorder(pRoot);
    //Traversals::DepthFirst::Preorder(pRoot);
    //cout << endl;
    //Traversals::DepthFirst::Inorder(pRoot);
    //cout << endl;
    //Traversals::DepthFirst::Postorder(pRoot);
    //cout << endl;
    pRoot = DeleteTree(pRoot);
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
