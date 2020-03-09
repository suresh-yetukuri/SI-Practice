// EnclosedString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
M + (N + 26)Log(N + M - 1), 26 + 26
*/
namespace BinarySearch
{
    // 26
    bool CompareCountArray(const vector<int>& oACountArray, const vector<int>& oBCountArray)
    {
        for (int iCounter = 0; iCounter < 26; ++iCounter)
        {
            if (oACountArray[iCounter] > oBCountArray[iCounter])
                return false;
        }

        return true;
    }

    bool IsValid(string& b, int oPossibleAns, vector<int>& oACountArray)
    {
        int bSize = static_cast<int>(b.size());
        vector<int> oBCountArray(26, 0);

        for (int iCounter = 0; iCounter < (oPossibleAns - 1); ++iCounter)
            oBCountArray[b[iCounter] - 'a']++;
         
        int pCounter = 0;
        int qCounter = pCounter + (oPossibleAns - 1);

        while (qCounter < bSize)
        {
            // Add New Element Of Window
            oBCountArray[b[qCounter] - 'a']++;

            if (CompareCountArray(oACountArray, oBCountArray))
                return true;

            // Shed First Element of Window
            oBCountArray[b[pCounter] - 'a']--;
            ++pCounter;
            ++qCounter;
        }
         
        return false;
    }

    int GetLengthOfESS(string& a, string& b)
    {
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());
        if (aSize > bSize)
            return -1;

        // Build Count Array for 'a'

        // 26
        vector<int> oACountArray(26, 0);
        for (int iCounter = 0; iCounter < aSize; ++iCounter)
            oACountArray[a[iCounter] - 'a']++;
         
        int Low = aSize;
        int High = bSize;

        // Log(N-M+1)
        while (Low < High)
        {
            int Mid = Low + ((High - Low) >> 1);
            if (IsValid(b, Mid, oACountArray)) // N * 26
                High = Mid;
            else
                Low = Mid + 1;
        }

        if (Low == High && (IsValid(b, Low, oACountArray)))
            return Low;

        return -1;
    }
}

int main()
{
    string a{"onmwvytbytn"};
    string b{"uqhmfjaqtgngcwkuzyamnerphfmw"};
    cout << BinarySearch::GetLengthOfESS(a, b);
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
