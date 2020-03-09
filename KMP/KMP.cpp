// KMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
M + (N + M), M
*/
namespace KnuthMorrisPratt
{
    vector<int> GetLSPTable(const string& oPattern)
    {
        int oPatternSize = static_cast<int>(oPattern.size());
        vector<int> oLSP(oPatternSize);
        int iCounter = 0;
        int jCounter = iCounter + 1;
        oLSP[0] = 0;
        while (jCounter < oPatternSize)
        {
            int oCounter = 0;
            while ((jCounter < oPatternSize) && (oPattern[iCounter] == oPattern[jCounter]))
            {
                ++oCounter;
                oLSP[jCounter] = oCounter;
                ++jCounter; ++iCounter;
            }

            if (jCounter < oPatternSize) {
                iCounter = 0;
                if (oPattern[iCounter] != oPattern[jCounter])
                    ++jCounter;
            }
        }

        return move(oLSP);
    }

    int Search(const string& oMain, const string& oPattern)
    {
        int oMainSize = static_cast<int>(oMain.size());
        int oPatternSize = static_cast<int>(oPattern.size());
        vector<int> oLSP = GetLSPTable(oPattern);

        int jCounter = 0;
        for (int iCounter = 0; iCounter < oMainSize; ++iCounter)
        {
            while (jCounter > 0 && oMain[iCounter] != oPattern[jCounter])
                jCounter = oLSP[jCounter - 1];

            if (oMain[iCounter] == oPattern[jCounter])
            {
                ++jCounter;
                if (jCounter == oPatternSize)
                    return (iCounter - jCounter) + 1;
            }
        }

        return -1;
    }
}



int main()
{    
    cout << KnuthMorrisPratt::Search("abazacabababac", "ababac") << endl;
    cout << KnuthMorrisPratt::Search("aabaaabacaz", "aabacaz") << endl;
    cout << KnuthMorrisPratt::Search("this is a test", "is a") << endl;
    cout << KnuthMorrisPratt::Search("cantfindtheindex", "foo") << endl;
     

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
