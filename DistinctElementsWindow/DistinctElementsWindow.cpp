// DistinctElementsWindow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
M + (N-M), M
*/
namespace UsingHash
{
    void GetDistinctElements(vector<int>& pArray, int wSize)
    {
        int nSize = static_cast<int>(pArray.size());
        unordered_map<int, int> oHMap;
        for (int iCounter = 0; iCounter < wSize; ++iCounter)
            oHMap[pArray[iCounter]]++;

        // First Window
        cout << oHMap.size()<<" ";

        int pCounter = 1;
        int qCounter = wSize;

        while (qCounter < nSize)
        { 
            oHMap[pArray[pCounter - 1]]--;
            oHMap[pArray[qCounter]]++;

            auto pItr = oHMap.find(pArray[pCounter - 1]);
            if (pItr != oHMap.end() && pItr->second == 0)
                oHMap.erase(oHMap.find(pArray[pCounter - 1]));

            cout << oHMap.size() << " ";

            ++pCounter;
            ++qCounter;
        }
    }
}



int main()
{
    vector<int> pArray{ -5, - 1, 4, 8 ,- 5 ,- 3 ,- 4 ,7, 4, - 4, 0, 8, 0, - 2, 3, 2 ,5 };
    UsingHash::GetDistinctElements(pArray, 13);
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
