// StackImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

class Stack
{
public:
    Stack()
    {
        pHead = nullptr;
        oSize = 0;
    }

    void Push(int val)
    {
        ++oSize;
        Node* pNode = new Node(val);
        pNode->pNext = pHead;
        pHead = pNode;
    }

    int Pop()
    {
        if (IsEmpty())
            return INT_MIN;

        --oSize;
        int xVal = pHead->Data;
        Node* pNodeTBD = pHead;
        pHead = pHead->pNext;
        delete(pNodeTBD); pNodeTBD = nullptr;
        return xVal;
    }

    int Top()
    {
        if (IsEmpty())
            return INT_MIN;

        return pHead->Data;
    }

    bool IsEmpty()
    {
        return nullptr == pHead;
    }

    int Size() const
    {
        return oSize;
    }

    ~Stack()
    { 
        while (nullptr != pHead)
        {
            Node* pNodeTBD = pHead;
            pHead = pHead->pNext;
            delete(pNodeTBD); pNodeTBD = nullptr;
        }

        oSize = 0;
    }
private:
    int oSize;
    Node* pHead;
};

int main()
{
    std::cout << "Hello World!\n";
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
