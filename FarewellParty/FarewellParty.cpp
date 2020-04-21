// FarewellParty.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int GetRoomCountRequired(vector<int>& oStartInterval, vector<int>& oEndInterval, int nTotalGuest)
{ 
    int oMinRoomReq = INT_MIN;
    int oMaxEndInterval = *max_element(oEndInterval.begin(), oEndInterval.end());
    vector<int> oSpace(oMaxEndInterval + 1, 0);
    for (int iCounter = 0; iCounter < nTotalGuest; ++iCounter)
    {
        oSpace[oStartInterval[iCounter]] = 1;
        if(oEndInterval[iCounter] + 1 <= oMaxEndInterval)
            oSpace[oEndInterval[iCounter] + 1] = -1;
    }

    oMinRoomReq = max(oSpace[0], oMinRoomReq);
    for (int iCounter = 1; iCounter <= oMaxEndInterval; ++iCounter) {
        oSpace[iCounter] = oSpace[iCounter] + oSpace[iCounter - 1];
        oMinRoomReq = max(oSpace[iCounter], oMinRoomReq);
    }

    return oMinRoomReq;
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;
    for (int iCounter = 0; iCounter < nTestCase; ++iCounter)
    {
        int nTotalGuest = 0;
        cin >> nTotalGuest;
        vector<int>oStartInterval(nTotalGuest);
        vector<int>oEndInterval(nTotalGuest);

        for (int jCounter = 0; jCounter < nTotalGuest; ++jCounter)
        {
            int oStartInt, oEndInt;
            cin >> oStartInt;
            cin >> oEndInt;
            oStartInterval[jCounter] = oStartInt;
            oEndInterval[jCounter] = oEndInt;
        }

        cout << GetRoomCountRequired(oStartInterval, oEndInterval, nTotalGuest) << endl;
    }


    vector<int> oStart{ 1, 5, 15 };
    vector<int> oEnd{ 5, 10, 20 };
    int nTotal = 3;
    cout << GetRoomCountRequired(oStart, oEnd, nTotal);

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
