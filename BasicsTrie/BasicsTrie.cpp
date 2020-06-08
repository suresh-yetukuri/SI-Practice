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
    int nCount;
    int nValue;
    bool IsEnd;
    TrieNode()
    {
        IsEnd = false;
        nCount = 0;
        nValue = INT_MIN;
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
void Insert(TrieNode* pRoot, string&& oInput, int Value)
{
    TrieNode* pCurrent = pRoot;
    for (auto& ch : oInput)
    {
        int charIdx = ch - 'a';
        if (nullptr == pCurrent->pChild[charIdx])
            pCurrent->pChild[charIdx] = new TrieNode();

        pCurrent = pCurrent->pChild[charIdx];
        pCurrent->nCount = pCurrent->nCount + 1;
    }

    pCurrent->nValue = Value;
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

int Search(TrieNode* pRoot, string oInput)
{
    TrieNode* pCurrent = pRoot;
    for (auto& ch : oInput)
    {
        int charIdx = ch - 'a';
        if (nullptr == pCurrent->pChild[charIdx])
            return INT_MIN;

        pCurrent = pCurrent->pChild[charIdx];
    }

    if (pCurrent->IsEnd)
        return pCurrent->nValue;

    return INT_MIN;
}

void PrintLexographicalOrder(TrieNode* pRoot, string& oPrefix)
{
    if (pRoot->IsEnd)
        cout << oPrefix << endl;

    for (int iCounter = 0; iCounter < 26; ++iCounter)
    {
        if (nullptr != pRoot->pChild[iCounter]) {
            oPrefix.push_back('a' + iCounter);
            PrintLexographicalOrder(pRoot->pChild[iCounter], oPrefix);
            oPrefix.pop_back();
        }
    }
}

void PrefixSearch(TrieNode* pRoot, string& oInput)
{
    TrieNode* pCurrent = pRoot;
    for (auto& ch : oInput)
    {
        int oCharIdx = ch - 'a';
        if (nullptr == pCurrent->pChild[oCharIdx])
            return;

        pCurrent = pCurrent->pChild[oCharIdx];
    }

    PrintLexographicalOrder(pCurrent, oInput);
}

int PrefixSearchCount(TrieNode* pRoot, string& oInput)
{
    TrieNode* pCurrent = pRoot;
    for (auto& ch : oInput)
    {
        int oCharIdx = ch - 'a';
        if (nullptr == pCurrent->pChild[oCharIdx])
            return 0;

        pCurrent = pCurrent->pChild[oCharIdx];
    }

    return pCurrent->nCount;
}

string LongestCommonPrefix(TrieNode* pRoot)
{
    TrieNode* pCurrent = pRoot;
    int oSingleChildIdx = -1;
    string oLCP{};

    auto IsSingleChild = [&oSingleChildIdx](TrieNode* pNode)->bool {
        int oCount = 0; 
        oSingleChildIdx = -1;
        for (int iCounter = 0; iCounter < 26; ++iCounter) {
            if (nullptr != pNode->pChild[iCounter]) {
                ++oCount;
                if (oCount == 1)
                    oSingleChildIdx = iCounter;
                else {
                    oSingleChildIdx = -1;
                    return false;
                }
            }
        }

        return true;
    };

    while (!pCurrent->IsEnd && IsSingleChild(pCurrent))
    {
        oLCP.push_back('a' + oSingleChildIdx);
        pCurrent = pCurrent->pChild[oSingleChildIdx];
    }

    return oLCP;
}


int main()
{
    //string oResult;
    //oResult.push_back(1 + 48);
    TrieNode* pRoot = new TrieNode();
    Insert(pRoot, "bad", 23);
    Insert(pRoot, "badass", 54);
    Insert(pRoot, "baddy", 89);
    Insert(pRoot, "badam", 78);
    Insert(pRoot, "qadden", 56);
   /* Insert(pRoot, "badass");
    Insert(pRoot, "aunty");
    Insert(pRoot, "suresh");
    Insert(pRoot, "rekha");
    Insert(pRoot, "can");
    Insert(pRoot, "ba");
    Insert(pRoot, "a");
    Insert(pRoot, "aa");
    Insert(pRoot, string{ "zoo" });*/
    cout << LongestCommonPrefix(pRoot) << endl;
    string oSearchInput{ "cat" };
    cout << Search(pRoot, oSearchInput) << endl;
    oSearchInput = "geeks";
    cout << Search(pRoot, oSearchInput) << endl;
    oSearchInput = "bat";
    cout << Search(pRoot, oSearchInput) << endl;
    oSearchInput = "ca";
    cout << Search(pRoot, oSearchInput) << endl;



    string oPrefix{"ba"};
    PrefixSearch(pRoot, oPrefix);
    // PrintLexographicalOrder(pRoot, oPrefix);
    cout << endl;

    cout << PrefixSearchCount(pRoot, oPrefix);

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
