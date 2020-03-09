// RankBooks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
    vector<int> oInput{ 45, 30, 12 };
    unordered_map<int, int> oMap;
    int iCounter = 1;
    for_each(oInput.begin(), oInput.end(), [&oMap, &iCounter](int val)->void {
        if (oMap.find(val) == oMap.end()) {
            oMap[val] = iCounter;
            ++iCounter;
        }
    });

    vector<int> oQueries{ 5, 12, 25, 35, 45, 80 };
    vector<int> oResult;
    for_each(oQueries.begin(), oQueries.end(), [&](int val)->void {
        auto pItr = lower_bound(oInput.rbegin(), oInput.rend(), val);
        if (pItr != oInput.rend()) {
            if (oMap.find(val) != oMap.end())
                cout << oMap[*pItr] << endl;
            else
                cout << oMap[*pItr] + 1 << endl;
        }
        else {
            cout << 1 << endl;
        }
    });

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
