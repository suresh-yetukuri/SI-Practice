// ActivitySelection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool IsActivitiesOverlap(pair<int, int>& oLast, pair<int, int>& oCurrent)
{
    if (oCurrent.first >= oLast.second)
        return false;

    return true;
}

int activitySelection(int start[], int end[], int n) {
    vector<pair<int, int>> oActivities(n);
    for (int iCounter = 0; iCounter < n; ++iCounter)
        oActivities[iCounter] = make_pair(start[iCounter], end[iCounter]);

    sort(oActivities.begin(), oActivities.end(), [](pair<int, int>& oFirst, pair<int, int>& oSec)->bool {
        return oFirst.second < oSec.second;
    });

    int nActivityCount = 0;
    pair<int, int> oLastActivity;
    for(auto oPair: oActivities)
    {
        if (!IsActivitiesOverlap(oLastActivity, oPair))
        {
            ++nActivityCount;
            oLastActivity = oPair;
        }
    }

    return nActivityCount;
}

int main()
{
    int n = 8;
    int start[] = { 50, 74, 59, 31, 73, 45, 79, 24 };
    int end[] = { 70, 75, 65, 44, 76, 73, 103, 32 };
    int nActivityCount = activitySelection(start, end, n);
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
