// DequeImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

namespace UsingArray
{
    class Deque
    {
    public:
        Deque(int oCapacity)
        {
            this->oCapacity = oCapacity;
            oContainer.resize(oCapacity);
            oFront = oRear = -1;
            oSize = 0;
        }

        void Push_Front(int value)
        {
            if (IsEmpty())
                oFront = oRear = 0;
            else if (IsFull())
                return;
            else
                oFront = (oFront + oCapacity - 1) % oCapacity;

            oContainer[oFront] = value;
            ++oSize;
        }

        void Push_Back(int value)
        {
            if (IsEmpty())
                oFront = oRear = 0;
            else if (IsFull())
                return;
            else
                oRear = (oRear + 1) % oCapacity;

            oContainer[oRear] = value;
            ++oSize;
        }

        void Pop_Front()
        {
            if (IsEmpty())
                oFront = oRear = -1;
            else {
                oFront = (oFront + 1) % oCapacity;
                --oSize;
            }
        }

        void Pop_Back()
        {
            if (IsEmpty())
                oFront = oRear = -1;
            else {
                oRear = (oRear + oCapacity - 1) % oCapacity;
                --oSize;
            }
        }

        int Get_Front()
        {
            if (IsEmpty())
                return -1;
            else
                return oContainer[oFront];
        }

        int Get_Back()
        {
            if (IsEmpty())
                return -1;
            else
                return oContainer[oRear];
        }

        bool IsEmpty()
        {
            return (0 == oSize);
        }

        bool IsFull()
        {
            return (oSize == oCapacity);
        }

        size_t GetSize()
        {
            return oSize;
        }

    private:
        int oFront;
        int oRear;
        int oCapacity;
        size_t oSize;
        vector<int> oContainer;
    };
}

namespace UsingDoublyLinkedList
{
    class Node
    {
    public:
        int Data;
        Node* pNext;
        Node* pPrev;
        Node() :Node(0, nullptr, nullptr)
        { }

        Node(int oData) :Node(oData, nullptr, nullptr)
        { }

        Node(int oData, Node* oNext) : Node(oData, oNext, nullptr)
        {}

        Node(int oData, Node* oNext, Node* oPrev)
        {
            this->Data = oData;
            this->pNext = oNext;
            this->pPrev = oPrev;
        }
    };

    class Deque
    {
    public:
        Deque()
        {
            pHead = pTail = nullptr;
            oSize = 0;
        }

        void Push_Front(int value)
        {
            Node* pNode = new Node(value);
            if (IsEmpty())
                pHead = pTail = pNode;
            else
            {
                pNode->pNext = pHead;
                pHead->pPrev = pNode;
                pHead = pNode;
            }
            ++oSize;
        }

        void Push_Back(int value)
        {
            Node* pNode = new Node(value);
            if (IsEmpty())
                pHead = pTail = pNode;
            else
            {
                pNode->pPrev = pTail;
                pTail->pNext = pNode;
                pTail = pNode;
            }
            ++oSize;
        }

        void Pop_Front()
        {
            if (IsEmpty())
                pHead = pTail = nullptr;
            else {
                Node* pNodeTBD = pHead;
                pHead = pHead->pNext;
                if(nullptr != pHead)
                    pHead->pPrev = nullptr;

                delete(pNodeTBD); pNodeTBD = nullptr;
                --oSize;
            }
        }

        void Pop_Back()
        {
            if (IsEmpty())
                pHead = pTail = nullptr;
            else {
                Node* pNodeTBD = pTail;
                pTail = pTail->pPrev;
                if(nullptr != pTail)
                    pTail->pNext = nullptr;

                delete(pNodeTBD); pNodeTBD = nullptr;
                --oSize;
            }
        }

        int Get_Front()
        {
            if (IsEmpty())
                return -1;
            else
                return pHead->Data;
        }

        int Get_Back()
        {
            if (IsEmpty())
                return -1;
            else
                return pTail->Data;
        }

        bool IsEmpty()
        {
            return (0 == oSize);
        }
         
        size_t GetSize()
        {
            return oSize;
        }

    private:
        int oSize;
        Node* pHead;
        Node* pTail;
    };
}

int main()
{
    deque<int> oSTLDeque;
    //UsingArray::Deque oDeque(10);
    UsingDoublyLinkedList::Deque oDeque;
    oSTLDeque.push_back(10);
    oDeque.Push_Back(10);
    oSTLDeque.push_front(20);
    oDeque.Push_Front(20);
    oSTLDeque.push_back(30);
    oDeque.Push_Back(30);
    cout << (oSTLDeque.front() == oDeque.Get_Front()) << endl;
    oSTLDeque.pop_back();
    oDeque.Pop_Back();
    oSTLDeque.push_front(90);
    oDeque.Push_Front(90);
    cout << (oSTLDeque.size() == oDeque.GetSize()) << endl;
    cout << (oSTLDeque.back() == oDeque.Get_Back()) << endl;
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
