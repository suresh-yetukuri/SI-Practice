// LongestPalindromicString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/*
N*(N*N), 1
*/
namespace BruteForce
{
    bool IsPalindrome(const string& oInput, int startIdx, int endIdx)
    {
        int pCounter = startIdx;
        int qCounter = endIdx;

        while (pCounter <= qCounter)
        {
            if (oInput[pCounter] != oInput[qCounter])
                return false;

            ++pCounter;
            --qCounter;
        }

        return true;
    }

    int GetLengthOfPalindromicString(string& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        int nMaxPalindromicLenght = INT_MIN;

        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            for (int jCounter = iCounter; jCounter < nSize; ++jCounter)
            {
                if (IsPalindrome(oInput, iCounter, jCounter))
                    nMaxPalindromicLenght = max(nMaxPalindromicLenght, (jCounter - iCounter) + 1);
            } 
        }

        return nMaxPalindromicLenght;
    }
}


/*
N*(N + N), 1
*/
namespace BruteForceII
{
    int GetLengthOfPalindromicString(string& oInput)
    {
        int nSize = static_cast<int>(oInput.size());
        int nMaxPalindromicLenght = INT_MIN;

        for (int iCounter = 0; iCounter < (nSize - 1); ++iCounter)
        {
            // Considering each character to be the center of odd length palindromic string
            // expand on both side till we have valid palidrome
            int pCounter = iCounter; int qCounter = iCounter;
            while ((pCounter >= 0) && (qCounter < nSize) && (oInput[pCounter] == oInput[qCounter]))
            {
                nMaxPalindromicLenght = max(nMaxPalindromicLenght, (qCounter - pCounter) + 1);
                --pCounter;
                ++qCounter;
            }

            // Considering each character & adjacent one to be the center of even length palindromic string
            // expand on both side till we have valid palidrome
            pCounter = iCounter; qCounter = iCounter + 1;
            while ((pCounter >= 0) && (qCounter < nSize) && (oInput[pCounter] == oInput[qCounter]))
            {
                nMaxPalindromicLenght = max(nMaxPalindromicLenght, (qCounter - pCounter) + 1);
                --pCounter;
                ++qCounter;
            } 
        }

        return nMaxPalindromicLenght;
    }
}


namespace Hashing
{
    const int K = 1000000007;
    const int pPrime = 101;
     
    vector<long long int> BuildPowerArray(const int pPrime, int nSize)
    {
        vector<long long int> oPower(nSize + 1, 1);
        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
            oPower[iCounter] = ((oPower[iCounter - 1]) * pPrime) % K;

        return oPower;
    }

    bool IsPalindrome(string& oInput,
        int pCounter,
        int qCounter,
        vector<long long int>& oPrefixHash,
        vector<long long int>& oSuffixHash,
        vector<long long int>& oPower)
    {
        int nSize = static_cast<int>(oInput.size());
        long long int oPHashValue = 0;
        long long int oSHashValue = 0;

        if (pCounter > 0 && qCounter < (nSize-1)) 
        {
            oPHashValue = (oPrefixHash[qCounter] - oPrefixHash[pCounter - 1] + K) % K;
            oSHashValue = (oSuffixHash[pCounter] - oSuffixHash[qCounter + 1] + K) % K;

            // Balance Powers
            int kDiff = (qCounter + 1) - (nSize - pCounter);
            if (kDiff > 0)
                oSHashValue = (oSHashValue * oPower[abs(kDiff)]) % K;
            else if (kDiff < 0)
                oPHashValue = (oPHashValue * oPower[abs(kDiff)]) % K;
                
        } 
        else if (pCounter == 0 && qCounter == (nSize - 1))
        {
            oPHashValue = oPrefixHash[qCounter];
            oSHashValue = oSuffixHash[pCounter];
        }
        else if (pCounter == 0 && qCounter < (nSize - 1))
        {
            oPHashValue = oPrefixHash[qCounter];
            oSHashValue = (oSuffixHash[pCounter] - oSuffixHash[qCounter + 1] + K) % K;

            // Balance Powers
            int kDiff = (nSize - pCounter) - (qCounter + 1);
            oPHashValue = (oPHashValue * oPower[kDiff]) % K;
        }
        else if(qCounter == (nSize-1) && pCounter > 0)
        {
            oPHashValue = (oPrefixHash[qCounter] - oPrefixHash[pCounter - 1] + K) % K;
            oSHashValue = oSuffixHash[pCounter];

            // Balance Powers
            int kDiff = (qCounter + 1) - (nSize - pCounter);
            oSHashValue = (oSHashValue * oPower[kDiff]) % K;
        }

        return oPHashValue == oSHashValue && (oPHashValue != 0);
    }

    int BinarySearch(string& oInput,
        int oLIdx,
        int oHIdx,
        vector<long long int>& oPrefixHash,
        vector<long long int>& oSuffixHash,
        vector<long long int>& oPower)
    {
        int nSize = static_cast<int>(oInput.size());
        int Low = 0;
        int High = min(oLIdx, nSize - oLIdx - 1);

        while (Low < High)
        {
            int Mid = Low + ((High - Low + 1) >> 1);
            if (IsPalindrome(oInput, oLIdx - Mid, oHIdx + Mid, oPrefixHash, oSuffixHash, oPower))
                Low = Mid;
            else
                High = Mid - 1;
        }

        if (Low >= 0 && IsPalindrome(oInput, oLIdx - Low, oHIdx + Low, oPrefixHash, oSuffixHash, oPower))
            return Low;

        return -1;
    }

    int GetLengthOfPalindromicString(string& oInput, 
        vector<long long int>& oPower)
    {
        int nSize = static_cast<int>(oInput.size());
        vector<long long int> oPrefixHash(nSize, 0);
        vector<long long int> oSuffixHash(nSize, 0);

        oPrefixHash[0] = (oInput[0] * oPower[1]);
        for (int iCounter = 1; iCounter < nSize; ++iCounter)
            oPrefixHash[iCounter] = (oPrefixHash[iCounter - 1] + (oInput[iCounter] * oPower[iCounter + 1]) % K) % K;

        oSuffixHash[nSize - 1] = (oInput[nSize - 1] * oPower[1]);
        for (int iCounter = (nSize - 2); iCounter >= 0; --iCounter)
            oSuffixHash[iCounter] = (oSuffixHash[iCounter + 1] + (oInput[iCounter] * oPower[nSize - iCounter]) % K) % K;


        int nMaxPalindromicLenght = 1;
        for (int iCounter = 0; iCounter < (nSize - 1); ++iCounter)
        {
            // Considering each character to be the center of odd length palindromic string
            // expand on both side till we have valid palidrome 
            int OddOffset = BinarySearch(oInput, iCounter, iCounter, oPrefixHash, oSuffixHash, oPower);
            nMaxPalindromicLenght = max(nMaxPalindromicLenght, (2 * OddOffset) + 1);


            // Considering each character & adjacent one to be the center of even length palindromic string
            // expand on both side till we have valid palidrome
            int EvenOffset = BinarySearch(oInput, iCounter, iCounter + 1, oPrefixHash, oSuffixHash, oPower);
            nMaxPalindromicLenght = max(nMaxPalindromicLenght, (2 * EvenOffset) + 2);
        }

        return nMaxPalindromicLenght;
    }
}


int main()
{
    vector<string> oSample{ "a", "sllwffoqq", "yoogvb", "hcch", "mzmqnnrkurfmmfrukrnnqsm" };
    vector<long long int> oPower = Hashing::BuildPowerArray(Hashing::pPrime, 10000);

    for_each(oSample.begin(), oSample.end(), [&oSample, &oPower](string& oInput)->void {
        cout << Hashing::GetLengthOfPalindromicString(oInput, oPower) << endl;
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
