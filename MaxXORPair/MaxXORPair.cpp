// MaxXORPair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
BruteForce Approach
Two Nested loops
TC: N^2, 1
*/

/*
TC: N, 2^31 - 1
*/
namespace UsingTrie
{
    class TrieNode
    {
    public:
        TrieNode* pLeft;
        TrieNode* pRight;
        int Value;
        TrieNode()
        {
            pLeft = pRight = nullptr;
            Value = INT_MIN;
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

    void Insert(TrieNode* pRoot, int oInput)
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
    }

    int FindMaxXORPair(vector<int>& oInput)
    {
        // Insert elements into trie in bitwise form
        TrieNode* pRoot = new TrieNode();
        for (auto value : oInput)
            Insert(pRoot, value);


        pair<int, int> oMaxXORPair;
        int oMaxXORValue = INT_MIN;

        for (auto val : oInput)
        {
            TrieNode* pCurrent = pRoot;
            int currXORValue = 0;

            for (int iCounter = 31; iCounter >= 0; --iCounter)
            {
                int bitValue = (val >> iCounter) & 1;
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

            currXORValue = val ^ (pCurrent->Value);
            if (currXORValue > oMaxXORValue)
            {
                oMaxXORValue = currXORValue;
                oMaxXORPair.first = val;
                oMaxXORPair.second = pCurrent->Value;
            }
        }


        // Deleting Trie Data structure 
        // once computation is done
        pRoot->Delete();
        delete(pRoot);
        pRoot = nullptr;
        // cout << "Pair: " << oMaxXORPair.first << " ^ " << oMaxXORPair.second << " = " << oMaxXORValue << endl;


        return oMaxXORValue;
    }
}


int main()
{
    /*vector<int> oInput = { 25, 10, 2, 8, 5, 3 };*/
    vector<int> oInput = { 1, 2, 3, 4, 5, 6, 7 };
     
    // cout << FindMaxXORPair(oInput) << endl;
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
