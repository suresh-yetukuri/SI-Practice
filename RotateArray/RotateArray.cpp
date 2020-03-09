// RotateArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
N*K, 1
*/
namespace BruteForce
{
    void Rotate(vector<int>& pInput, int kTimes)
    {
        int nSize = static_cast<int>(pInput.size());
        kTimes = kTimes % nSize;
        for (int iCounter = 0; iCounter < kTimes; ++iCounter)
        {
            int Last = pInput[nSize - 1];
            for (int jCounter = nSize - 1; jCounter >= 1; --jCounter)
                pInput[jCounter] = pInput[jCounter - 1];

            pInput[0] = Last;
        }
    }
}

/*
N + N, N
*/
namespace OptimizedI
{
    void Rotate(vector<int>& pInput, int kTimes)
    {
        int nSize = static_cast<int>(pInput.size());
        kTimes = kTimes % nSize;
        vector<int> pCopy(nSize);
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
            pCopy[(iCounter + kTimes) % nSize] = pInput[iCounter];

        for (int iCounter = 0; iCounter < nSize; ++iCounter)
            pInput[iCounter] = pCopy[iCounter];
    }
}

/*
N + N, 1
*/
namespace OptimizedII
{
    void Rotate(vector<int>& pInput, int kTimes)
    {
        int nSize = static_cast<int>(pInput.size());
        kTimes = kTimes % nSize;
        reverse(pInput.begin(), pInput.end());
        reverse(pInput.begin(), pInput.begin() + kTimes);
        reverse(pInput.begin() + kTimes, pInput.end()); 
    }
}

int main()
{
    vector<int> pInput{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    OptimizedII::Rotate(pInput, 3);
    for (auto& val : pInput)
        cout << val << " ";

    cout << endl;

    OptimizedI::Rotate(pInput, 3);
    for (auto& val : pInput)
        cout << val << " ";

    cout << endl;
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
