// SubstringCheck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int K = 1000000007;
const int pPrime = 103;
/*
Given Two strings A & B, check if B is a substring of A or not
*/
namespace UsingPrefixHash
{
    vector<long long int> BuildPowerArray(const int pPrime, int nSize)
    {
        vector<long long int> oPower(nSize + 1, 1);
        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
            oPower[iCounter] = ((oPower[iCounter - 1]) * pPrime) % K;

        return oPower;
    }

    int SubstringCount(string& a, string& b)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        vector<long long int> oPower = BuildPowerArray(pPrime, max(aSize, bSize));

        // Hash for Substring
        long long int bHashValue = 0;
        for (int iCounter = 0; iCounter < bSize; ++iCounter)
            bHashValue = (bHashValue + (b[iCounter] * oPower[iCounter + 1]) % K) % K;

        // Build Prefix Hash for MainString
        vector<long long int> oAPrefixHash(aSize, 0);
        oAPrefixHash[0] = a[0] * oPower[1];
        for (int iCounter = 1; iCounter < aSize; ++iCounter)
            oAPrefixHash[iCounter] = (oAPrefixHash[iCounter - 1] + (a[iCounter] * oPower[iCounter + 1]) % K) % K;

        
        // Check for First Window
        if (bHashValue == oAPrefixHash[bSize - 1])
            oCount++;//return true;
         
        // From Second window onwards
        for (int iCounter = bSize; iCounter < aSize; ++iCounter)
        {
            bHashValue = (bHashValue * oPower[1]) % K;
            long long int aHashValue = (oAPrefixHash[iCounter] - oAPrefixHash[iCounter - bSize] + K) % K;

            if (aHashValue == bHashValue)
                oCount++;//return true;
        }

        return oCount;//return false; 
    }
}

namespace UsingKMP
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

    int SubstringCount(const string& oMain, const string& oPattern)
    {
        int oCount = 0;
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
                {
                    ++oCount;
                    jCounter = oLSP[jCounter - 1];
                }
                    
            }
        }

        return oCount;
    }
}

int main()
{
    string a{ "yalgoalgoalgopalgoaxalgoasaxalgolalgoalgoalgo" };
    string b{ "algo" };
    cout << UsingKMP::SubstringCount(a, b);
     
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
