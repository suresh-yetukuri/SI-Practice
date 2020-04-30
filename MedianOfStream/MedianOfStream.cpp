// MedianOfStream.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
N^2, N (This might be required if we are not allowed to modify existing array)
*/
namespace BruteForce
{
    void InsertionSort(vector<int>& oInput, int low, int high)
    {
        int iHole = high;
        int iHoleValue = oInput[high];
        while ((iHole - 1) >= 0 && oInput[iHole - 1] > iHoleValue)
        {
            oInput[iHole] = oInput[iHole - 1];
            --iHole;
        }

        oInput[iHole] = iHoleValue;
    }

    void Median(vector<int>& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            int high = iCounter;
            int low = 0;
            InsertionSort(oInput, low, high);
            int lowerMid = low + ((high - low) >> 1);
            int upperMid = low + ((high - low + 1) >> 1);
            double oMedian = static_cast<double>(oInput[lowerMid] + oInput[upperMid]) / 2.0;
            if (oMedian == static_cast<int>(oMedian))
                cout << static_cast<int>(oMedian) << " ";
            else
                cout << oMedian << " ";
        }
    }
}

/*
We can use SBBST
We can insert element in bst and get median in logN times (Using KthSmallest element in BST method)
But for this we need to augment SBBST
NLogN, N
*/

/*
N*(Log(N/2) + Log(N/2)), N
*/
namespace Efficient
{
    void Median(vector<int>& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        priority_queue<int> oMaxHeap;
        priority_queue<int, vector<int>, greater<int>> oMinHeap;
        for (auto& oData : oInput)
        {
            int oMaxHeapSize = static_cast<int>(oMaxHeap.size());
            int oMinHeapSize = static_cast<int>(oMinHeap.size());
            if (oMaxHeapSize > oMinHeapSize)
            {
                if (oMaxHeap.top() > oData)
                {
                    oMinHeap.push(oMaxHeap.top());
                    oMaxHeap.pop();
                    oMaxHeap.push(oData);
                }
                else
                    oMinHeap.push(oData);

                cout << (oMaxHeap.top() + oMinHeap.top()) / 2.0 << " ";
            }
            else {

                if (!oMaxHeap.empty() && oData <= oMaxHeap.top())
                    oMaxHeap.push(oData);
                else {
                    oMinHeap.push(oData);
                    oMaxHeap.push(oMinHeap.top());
                    oMinHeap.pop();
                }

                cout << oMaxHeap.top() << " ";
            }
        }
    }
}


int main()
{
    vector<int> oInput{ 12, 15, 10, 5, 8, 7, 16 };
    Efficient::Median(oInput);
    cout << endl;
    BruteForce::Median(oInput);
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
