// LRU Mechanism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
using namespace std;

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

/*
Miss: Constant
Hit: Constant
*/
namespace UsingDoublyLinkedList
{
    class LRU
    {
    public:
        LRU(int Capacity)
        {
            this->Capacity = Capacity;
            this->pHead = nullptr;
            this->pTail = nullptr;
        }

        ~LRU()
        { }

    public:
        int get()
        {
            if (nullptr == pHead)
                return INT_MIN;

            put(pHead->Data);
            return pHead->Data;
        }

        void put(int oVal)
        {
            if (oMap.find(oVal) != oMap.end())
            {
                Node* pNode = oMap[oVal];
                if (pNode != pHead)
                {
                    Node* pNext = pNode->pNext;
                    Node* pPrev = pNode->pPrev;
                    pPrev->pNext = pNext;
                    if (nullptr != pNext)
                        pNext->pPrev = pPrev;
                    else
                        pTail = pPrev;

                    pNode->pPrev = nullptr;
                    pNode->pNext = pHead;
                    pHead->pPrev = pNode;
                    pHead = pNode;
                }
            }
            else
            {
                if (static_cast<int>(oMap.size()) >= this->Capacity)
                {
                    // Delete Tail Element
                    Node* pNodeTBD = pTail;
                    pTail = pTail->pPrev;
                    if (nullptr != pTail)
                        pTail->pNext = nullptr;
                    else
                        pHead = nullptr;

                    oMap.erase(oMap.find(pNodeTBD->Data));
                    delete(pNodeTBD); pNodeTBD = nullptr;
                }

                Node* pNode = new Node(oVal);
                pNode->pNext = pHead;
                if (nullptr != pHead)
                    pHead->pPrev = pNode;
                else
                    pTail = pNode;

                pHead = pNode;
                oMap[oVal] = pNode;
            }
        }

        void print()
        { 
            if (nullptr == pHead)
                cout << "Cache Is Empty" << endl;

            Node* pCurrent = pHead;
            while (nullptr != pCurrent) {
                cout << pCurrent->Data << " ";
                pCurrent = pCurrent->pNext;
            }

            return;
        }
    private:
        int Capacity;
        Node* pHead;
        Node* pTail;
        unordered_map<int, Node*> oMap;
    };
}

/*
Miss: LogK + LogK
Hit: LogK + LogK
Space Complexity: K
*/
namespace UsingMaps
{
    class LRU
    {
    public:
        LRU(int Capacity)
        {
            this->Capacity = Capacity;
            this->pCounter = 1;
        }

        ~LRU()
        { }

    public:
        int get()
        {
            if (static_cast<int>(oHashMap.size()) == 0)
                return INT_MIN;

            return oSortedMap.rbegin()->first;
        }

        void put(int oVal)
        {
            if (oHashMap.find(oVal) != oHashMap.end())
            {
                int oCounter = oHashMap[oVal];
                oSortedMap.erase(oCounter);
                oSortedMap[pCounter] = oVal;
                oHashMap[oVal] = pCounter;
                ++pCounter;
            }
            else {
                if (static_cast<int>(oHashMap.size()) == Capacity)
                {
                    auto oLeastUsed = oSortedMap.begin();
                    oHashMap[oVal] = pCounter;
                    oSortedMap.erase(oLeastUsed);
                    oSortedMap[pCounter] = oVal;
                }
                else {
                    oHashMap[oVal] = pCounter;
                    oSortedMap[pCounter] = oVal;
                }

                ++pCounter;
            }
        }

        void print()
        {
            if (0 == static_cast<int>(oHashMap.size()))
                cout << "Cache Is Empty" << endl;

            for_each(oSortedMap.crbegin(), oSortedMap.crend(), [](auto& Itr)->void {
                cout << Itr.second << " ";
            });
        }
    private:
        int Capacity;
        int pCounter;
        map<int, int> oSortedMap;
        unordered_map<int, int> oHashMap;

    };
}


/*
Apart from above two optimized approaches
we have two bruteforce approach
1. Using simple vector as container
    Miss: K
    Hit : K
    Space Complexit: Constant
2. Using just single hash map
    Miss: K
    Hit: Constant
    Space Complexity: K

    key -> element
    value -> index

    Once size is full, then remove element with least index
    if not full but present, update index with new index
*/
int main()
{
    using namespace UsingMaps;
    int Capacity;
    cout << "Enter Capacity" << endl;
    cin >> Capacity;
    LRU* pCache = new LRU(Capacity);

    for (int iCounter = 0; iCounter < 10; ++iCounter)
    {
        int oVal;
        cin >> oVal;
        pCache->put(oVal);
        pCache->print();
        cout << endl;
    }

    cout << "Cache Done" << endl;
    cin >> Capacity;
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
