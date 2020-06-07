// BasicsTrie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class TrieNode
{
public:
    vector<TrieNode*> pChild;
    bool IsEnd;
    TrieNode()
    {
        IsEnd = false;
        pChild.resize(26, nullptr);
    }
};

bool IsEmpty(TrieNode* pNode)
{
    return all_of(pNode->pChild.begin(), pNode->pChild.end(), [](TrieNode* pInput) {
        return pInput == nullptr;
        });
}

/*
N, 1 (Worst Case)
*/
void Insert(TrieNode* pRoot, string&& oInput)
{
    TrieNode* pCurrent = pRoot;
    for (auto& ch : oInput)
    {
        int charIdx = ch - 'a';
        if (nullptr == pCurrent->pChild[charIdx])
            pCurrent->pChild[charIdx] = new TrieNode();

        pCurrent = pCurrent->pChild[charIdx];
    }

    pCurrent->IsEnd = true;
}

/*
N, 1 (Worst Case)
*/
TrieNode* Delete(TrieNode* pNode, string& oInput, int Idx)
{
    if (nullptr == pNode)
        return nullptr;

    if (Idx == oInput.length())
    {
        pNode->IsEnd = false;
        if (IsEmpty(pNode))
        {
            delete(pNode);
            pNode = nullptr;
        }
    }
    else {
        int charIdx = oInput[Idx] - 'a';
        pNode->pChild[charIdx] = Delete(pNode->pChild[charIdx], oInput, Idx + 1);
        if (IsEmpty(pNode) && (!pNode->IsEnd))
        {
            delete(pNode);
            pNode = nullptr;
        }
    }

    return pNode;
}

/*
N, 1 (Worst Case)
*/
bool Search(TrieNode* pRoot, string&& oInput)
{ 
    TrieNode* pCurrent = pRoot;
    for (auto& ch : oInput)
    {
        int charIdx = ch - 'a';
        if (nullptr == pCurrent->pChild[charIdx])
            return false;

        pCurrent = pCurrent->pChild[charIdx];
    }

    return pCurrent->IsEnd;
}


int main()
{
    string oResult;
    oResult.push_back(1 + 48);
    TrieNode* pRoot = new TrieNode();
    Insert(pRoot, "bad");
    Insert(pRoot, "bat");
    Insert(pRoot, "geek");
    Insert(pRoot, "geeks");
    Insert(pRoot, "cat");
    Insert(pRoot, "badass");
    Insert(pRoot, string{ "zoo" });

    string s{ "bad" };
    pRoot = Delete(pRoot, s, 0);
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
