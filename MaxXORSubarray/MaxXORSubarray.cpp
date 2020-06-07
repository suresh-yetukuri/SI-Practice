// MaxXORSubarray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
BruteForce:
TC: N^3, 1 (Generating All subarray)
TC: N^2, 1 (Using Carry Forward technique)
*/

/*
TC: N, 2^31
*/
namespace UsingTrie
{
    class TrieNode
    {
    public:
        TrieNode* pLeft;
        TrieNode* pRight;
        int Value;
        int LPrefixIdx;
        TrieNode()
        {
            pLeft = pRight = nullptr;
            Value = INT_MIN;
            LPrefixIdx = -1;
        }

        void Delete()
        {
            if (nullptr != pLeft) {
                pLeft->Delete();
                delete(pLeft);
                pLeft = nullptr;
            }

            if (nullptr != pRight) {
                pRight->Delete();
                delete(pLeft);
                pLeft = nullptr;
            }
        }
    };

    void Insert(TrieNode* pRoot, int oInput, int LPrefixIdx)
    {
        TrieNode* pCurrent = pRoot;
        for (int iCounter = 31; iCounter >= 0; --iCounter)
        {
            int bitValue = (oInput >> iCounter) & 1;
            if (1 == bitValue)
            {
                if (nullptr == pCurrent->pRight)
                    pCurrent->pRight = new TrieNode();

                pCurrent = pCurrent->pRight;
            }
            else {
                if (nullptr == pCurrent->pLeft)
                    pCurrent->pLeft = new TrieNode();

                pCurrent = pCurrent->pLeft;
            }
        }

        pCurrent->Value = oInput;
        pCurrent->LPrefixIdx = LPrefixIdx;
    }

    int FindMaxXOR(vector<int>& oInput)
    {
        TrieNode* pRoot = new TrieNode();
        Insert(pRoot, 0, -1);

        pair<int, int> oMaxXORSubarry;
        int oMaxXORValue = INT_MIN;
        int oPrefixXOR = 0;

        for (int iCounter = 0; iCounter < oInput.size(); ++iCounter)
        {
            oPrefixXOR = oPrefixXOR ^ oInput[iCounter];
            Insert(pRoot, oPrefixXOR, iCounter);

            TrieNode* pCurrent = pRoot;
            int currXORValue = 0;

            for (int iCounter = 31; iCounter >= 0; --iCounter)
            {
                int bitValue = (oPrefixXOR >> iCounter) & 1;
                if (1 == bitValue)
                {
                    if (nullptr != pCurrent->pLeft)
                        pCurrent = pCurrent->pLeft;
                    else
                        pCurrent = pCurrent->pRight;
                }
                else {
                    if (nullptr != pCurrent->pRight)
                        pCurrent = pCurrent->pRight;
                    else
                        pCurrent = pCurrent->pLeft;
                }
            }

            currXORValue = oPrefixXOR ^ (pCurrent->Value);
            if (currXORValue > oMaxXORValue)
            {
                oMaxXORValue = currXORValue;
                oMaxXORSubarry.first = pCurrent->LPrefixIdx + 1;
                oMaxXORSubarry.second = iCounter;
            }
        }

        // Deleting Trie Data structure 
        // once computation is done
        pRoot->Delete();
        delete(pRoot);
        pRoot = nullptr;
        cout << "Subarray:[ " << oMaxXORSubarry.first << " ^ " << oMaxXORSubarry.second << " ] = " << oMaxXORValue << endl;

        return oMaxXORValue;
    }
}


int main()
{
    vector<int> oInput = { 25, 10, 2, 8, 5, 3 };
    cout << UsingTrie::FindMaxXOR(oInput);
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
