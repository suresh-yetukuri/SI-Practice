// RearrangeCharacters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
Given a string S with repeated characters (only lowercase). 
The task is to rearrange characters in a string such that no two adjacent characters are same.
*/


namespace Efficient
{
    string Rearrange(string& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        vector<int> oCountArray(26, 0);
        

        for (auto& oData : oInput)
            oCountArray[oData - 97ull]++;
          
        priority_queue<pair<int, char>> oMaxFreqHeap;
        for (int iCounter = 0; iCounter < 26; ++iCounter)
        {
            if (oCountArray[iCounter] > 0)
                oMaxFreqHeap.push(make_pair(oCountArray[iCounter], 'a' + iCounter));
        }

        string oResult;
        pair<int, char> oPrevPair;
        bool IsPrevAvailable = false;
        while (!oMaxFreqHeap.empty())
        {
            pair<int, char> oCurrentPair = oMaxFreqHeap.top();
            oMaxFreqHeap.pop();
            oResult.push_back(oCurrentPair.second);
            oCurrentPair.first--;
            if(IsPrevAvailable)
                oMaxFreqHeap.push(oPrevPair);

            if (oCurrentPair.first > 0) {
                oPrevPair = oCurrentPair;
                IsPrevAvailable = true;
            }
            else
                IsPrevAvailable = false;
        }

        if (oResult.size() == nSize)
            cout << 1 << endl;
        else
            cout << 0 << endl;

        return move(oResult);
    }
}

int main()
{
    vector<int> arr{ 3, 1, 4, 4, 5, 2, 6, 1 };
    int k = 2;
    int n = 8;

    unordered_map<int, int> oHashMap;
    for (int iCounter = 0; iCounter < n; ++iCounter)
        oHashMap[arr[iCounter]]++;

    priority_queue<pair<int, int>> oMaxHeap;
    for (auto& oData : oHashMap)
        oMaxHeap.push(make_pair(oData.second, oData.first));

    int oSumFreq = 0;
    int oCounter = 0;
    while (!oMaxHeap.empty() && oCounter < k)
    {
        oSumFreq += (oMaxHeap.top().first);
        oMaxHeap.pop();
    }


    string oInput{ "bbbbb" };
    cout << Efficient::Rearrange(oInput);

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
