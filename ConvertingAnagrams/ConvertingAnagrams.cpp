// ConvertingAnagrams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int CountCharacterTBD(string& oFData, string& oSData)
{
    int oFSize = static_cast<int>(oFData.size());
    int oSSize = static_cast<int>(oSData.size());
    int oCharTBD = 0;
    vector<int> oCountArray(26, 0);
    int oFCounter = 0;
    int oSCounter = 0;
    int nMaxCount = max(oFSize, oSSize);
    for (int iCounter = 0; iCounter < nMaxCount; ++iCounter)
    {
        if (oFCounter < oFSize) {
            oCountArray[oFData[oFCounter] - 97]++;
            ++oFCounter;
        }

        if (oSCounter < oSSize) {
            oCountArray[oSData[oSCounter] - 97]--;
            ++oSCounter;
        }
    }
         
    for (auto& oData : oCountArray) 
        oCharTBD += abs(oData);

    return oCharTBD;
}




int main()
{
    string oFData{ "smart" };
    string oSData{ "interviews" };
    cout << CountCharacterTBD(oFData, oSData);
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
