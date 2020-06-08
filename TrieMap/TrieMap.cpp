// TrieMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;



class PrefixNode
{
public:
    char Key;
    int Id;
    unordered_map<char, PrefixNode*> oChild;
    bool IsEnd;
public:
    PrefixNode():PrefixNode(0, 0)
    {}

    PrefixNode(char Key, int Id)
    {
        this->Key = Key;
        this->Id = Id;
        IsEnd = false;
    }

    bool HasChild(char oChar)
    {
        if (!oChild.empty() && (oChild.find(oChar) != oChild.end()))
            return true;

        return false;
    }

    PrefixNode* GetChild(char oChar)
    {
        if(HasChild(oChar))
            return oChild[oChar];

        return nullptr;
    }

    void AddChild(PrefixNode* pNode)
    {
        if (!HasChild(pNode->Key))
            oChild[pNode->Key] = pNode;
    }

    void RemoveChild(char oChar)
    {
        auto pNode = GetChild(oChar);
        if (nullptr != pNode)
        {
            delete(pNode);
            pNode = nullptr;
            oChild.erase(oChar);
        }
    }

    bool CanDelete()
    {
        return oChild.empty();
    }
};


class PrefixTrie
{
public:
    PrefixNode* pRoot;
    PrefixTrie()
    {
        this->pRoot = new PrefixNode();
    }

    void Insert(string&& oInput, int Id)
    {
        PrefixNode* pCurrent = pRoot;
        for (auto& ch : oInput)
        {
            if (!pCurrent->HasChild(ch))
                pCurrent->AddChild(new PrefixNode(ch, 0));

            pCurrent = pCurrent->GetChild(ch);
        }

        pCurrent->IsEnd = true;
        pCurrent->Id = Id;
    }

    int Search(string&& oInput)
    {
        PrefixNode* pCurrent = pRoot;
        for (auto& ch : oInput)
        {
            if (!pCurrent->HasChild(ch))
                return INT_MIN;

            pCurrent = pCurrent->GetChild(ch);
        }

        if (pCurrent->IsEnd)
            return pCurrent->Id;
        
        return INT_MIN;
    }

    void Delete(string&& oInput)
    {
        Delete(pRoot, oInput, 0);
    }

private:
    bool Delete(PrefixNode* pNode, string& oInput, int Idx)
    {
        if (nullptr == pNode)
            return false;

        if (oInput.length() - 1 == Idx)
        {
            auto oLeafNode = pNode->GetChild(oInput[Idx]);
            oLeafNode->IsEnd = false;
            oLeafNode->Id = 0;
            if (oLeafNode->CanDelete())
            { 
                pNode->RemoveChild(oInput[Idx]);
                return true;
            }
            return false;
        }
        else {
            bool bCanDelete = Delete(pNode->GetChild(oInput[Idx]), oInput, Idx + 1);
            if (bCanDelete)
            {
                if (nullptr != pNode->GetChild(oInput[Idx])
                    && pNode->GetChild(oInput[Idx])->CanDelete()
                    && !(pNode->GetChild(oInput[Idx])->IsEnd))
                {
                    pNode->RemoveChild(oInput[Idx]);
                    return true;
                }
            }
        }

        return false;
    }
};


int main()
{
    PrefixTrie* pTrie = new PrefixTrie();
    pTrie->Insert("bad", 23);
    pTrie->Insert("badass", 54);
    pTrie->Insert("baddy", 89);
    pTrie->Insert("badam", 78);
    pTrie->Insert("qadden", 56);
    pTrie->Insert("bad", 100);
   
    cout << pTrie->Search("baddy") << endl;
    cout << pTrie->Search("badass") << endl;
    cout << pTrie->Search("qadd") << endl;
    cout << pTrie->Search("bad") << endl;

    pTrie->Delete("badas");
    cout << pTrie->Search("badam");

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
