// NearlyKSortedArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


/*
KLogK + (N-K)(LogK + LogK), K
*/
void Sort(vector<int>& oInput, int k)
{
    int nSize = static_cast<int>(oInput.size());
    priority_queue<int, vector<int>, greater<int>> oHeap;
    for (int iCounter = 0; iCounter <= k; ++iCounter)
        oHeap.push(oInput[iCounter]);

    int oCurrentIdx = 0;
    for (int iCounter = k + 1; iCounter < nSize; ++iCounter)
    {
        oInput[oCurrentIdx++] = oHeap.top();
        oHeap.pop();
        oHeap.push(oInput[iCounter]);
    }

    while (!oHeap.empty())
    {
        oInput[oCurrentIdx++] = oHeap.top();
        oHeap.pop();
    }
}

/*
KLogK + (N-K)(LogK + LogK), K
*/
void SortI(vector<int>& oInput, int k)
{
    int nSize = static_cast<int>(oInput.size());
    set<int> oSet;
    for (int iCounter = 0; iCounter <= k; ++iCounter)
        oSet.insert(oInput[iCounter]);

    int oCurrentIdx = 0;
    for (int iCounter = k + 1; iCounter < nSize; ++iCounter)
    {
        auto sItr = oSet.begin();
        oInput[oCurrentIdx++] = *sItr;
        oSet.erase(sItr);
        oSet.insert(oInput[iCounter]);
    }

    while (!oSet.empty())
    {
        auto sItr = oSet.begin();
        oInput[oCurrentIdx++] = *sItr;
        oSet.erase(sItr);
    }
}


/*
Time Complexities are same int both case, 
but auxillary space and some other constant
operation will be more in set. So heap sort will 
me much more efficient compared to SBBST
*/


int main()
{
    vector<int> oInput{ 6, 5, 3, 2 ,8 ,10 ,9 };
    SortI(oInput, 3);
    for (auto& oData : oInput)
        cout << oData << " ";

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
