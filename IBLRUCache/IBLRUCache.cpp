// IBLRUCache.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <set>
using namespace std;


class Node
{
public:
    int key;
    int Data;
    Node* pNext;
    Node* pPrev;

    Node(int oData, int oKey)
    {
        this->key = oKey;
        this->Data = oData;
        this->pNext = nullptr;
        this->pPrev = nullptr;
    }
};

class LRUCache
{
public:
    LRUCache(int capacity);
    int get(int key);
    void set(int key, int value);
private:
    unordered_map<int, Node*> oHashMap;
    Node* pHead;
    Node* pTail;
    int kCapacity;
};

LRUCache::LRUCache(int capacity) {
    pHead = pTail = nullptr;
    kCapacity = capacity;
    while (!oHashMap.empty())
    {
        auto oPair = *(oHashMap.begin());
        delete(oPair.second);
        oHashMap.erase(oPair.first);
    }
}

int LRUCache::get(int key) {
    if (oHashMap.find(key) != oHashMap.end())
    {
        set(key, oHashMap[key]->Data);
        return oHashMap[key]->Data;
    }

    return -1;
}

void LRUCache::set(int key, int value) {
    if (oHashMap.find(key) != oHashMap.end())
    {
        Node* pCurrNode = oHashMap[key];
        pCurrNode->Data = value;
        if (pHead != pCurrNode)
        {
            if (nullptr != pCurrNode->pNext)
            {
                pCurrNode->pPrev->pNext = pCurrNode->pNext;
                pCurrNode->pNext->pPrev = pCurrNode->pPrev;
            }
            else {
                pCurrNode->pPrev->pNext = nullptr;
                pTail = pCurrNode->pPrev;
            }

            pCurrNode->pPrev = nullptr;
            pCurrNode->pNext = pHead;
            pHead->pPrev = pCurrNode;
            pHead = pCurrNode;
        }
    }
    else
    {
        int oCurrentSize = static_cast<int>(oHashMap.size());
        if (oCurrentSize >= kCapacity)
        {
            int oDeleteKey = pTail->key;
            Node* pNodeTBD = pTail;
            pTail = pTail->pPrev;
            if (nullptr != pTail)
                pTail->pNext = nullptr;
            else
                pHead = nullptr;

            delete(pNodeTBD); pNodeTBD = nullptr;
            oHashMap.erase(oDeleteKey);
        }

        // Insert new entry
        Node* pNode = new Node(value, key);
        pNode->pNext = pHead;
        if (nullptr != pHead)
            pHead->pPrev = pNode;
        else
            pTail = pNode;

        pHead = pNode;
        oHashMap.insert(make_pair(key, pNode));
    }
}

int main()
{
  

    LRUCache oCache{7};
    for (int iCounter = 0; iCounter < 59; ++iCounter)
    {
        char oChar;
        cin >> oChar;
        if (oChar == 'S')
        {
            int a, b;
            cin >> a;
            cin >> b;
            oCache.set(a, b);
        }
        else
        {
            int a;
            cin >> a;
            cout << oCache.get(a) << " ";
        }
    }

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
