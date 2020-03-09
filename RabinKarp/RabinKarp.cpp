// RabinKarp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;
const long long int M = static_cast<long long int>(1e9 + 7); 

// Need to work on this
//namespace UsingPrefixHash
//{
//     
//    vector<long long int> GetPowerArray(int nSize, int pPrime)
//    {
//        vector<long long int> oPower((nSize + 1), 1); 
//         
//        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
//            oPower[iCounter] = (oPower[iCounter - 1] * pPrime) % M;
//        
//        return oPower;
//    }
//    
//    int GetCountOfOccurences(string& a, string& b, vector<long long int>& oLPower, vector<long long int>& oHPower)
//    {
//        int aSize = static_cast<int>(a.size());
//        int bSize = static_cast<int>(b.size());
//        int oOccurenceCount = 0;
//
//        // Get Hash Value For A
//        long long int oLAPrefixHash = 0;
//        long long int oHAPrefixHash = 0;
//        oLAPrefixHash = a[0] * oLPower[1];
//        oHAPrefixHash = a[0] * oHPower[1];
//
//        for (int iCounter = 1; iCounter < aSize; ++iCounter) 
//        {
//            oLAPrefixHash = (oLAPrefixHash + (a[iCounter] * oLPower[iCounter + 1]) % M) % M;
//            oHAPrefixHash = (oHAPrefixHash + (a[iCounter] * oHPower[iCounter + 1]) % M) % M;
//        }
//
//
//        // Build Prefix Hash Array For B
//        vector<long long int> oLBPrefixHash(bSize, 0);
//        vector<long long int> oHBPrefixHash(bSize, 0); 
//        oLBPrefixHash[0] = b[0] * oLPower[1];
//        oHBPrefixHash[0] = b[0] * oHPower[1];
//
//        for (int iCounter = 1; iCounter < bSize; ++iCounter)
//        {
//            oLBPrefixHash[iCounter] = (oLBPrefixHash[iCounter - 1] + (b[iCounter] * oLPower[iCounter + 1]) % M) % M;
//            oHBPrefixHash[iCounter] = (oHBPrefixHash[iCounter - 1] + (b[iCounter] * oHPower[iCounter + 1]) % M) % M;
//        }
//            
//
//
//        int pCounter = 0;
//        int qCounter = pCounter + (aSize - 1);
//         
//        while (qCounter < bSize)
//        {
//            long long int bHashValue = 0;
//            long long int aHashValue = 0;
//
//            if (pCounter == 0)
//            { 
//                bHashValue = (oLBPrefixHash[qCounter] + oHBPrefixHash[qCounter]) % M;
//            } 
//            else
//            {
//                long long int bLHashValue, bHHashValue; 
//                bLHashValue = oLBPrefixHash[qCounter] - oLBPrefixHash[pCounter - 1];
//                bHHashValue = oHBPrefixHash[qCounter] - oHBPrefixHash[pCounter - 1];
//                bHashValue = (bLHashValue + bHHashValue) % M;
//            }
//                
//
//
//            // Balance Powers
//            int kPowerDiff = pCounter - 0;
//            if (kPowerDiff > 0)
//            {
//                long long int aLHashValue, aHHashValue; 
//                aLHashValue = (oLAPrefixHash * oLPower[kPowerDiff]) % M;
//                aHHashValue = (oHAPrefixHash * oHPower[kPowerDiff]) % M;
//                aHashValue = (aLHashValue + aHHashValue) % M;
//            }
//            
//
//            if (aHashValue == bHashValue)
//                ++oOccurenceCount;
//
//            ++pCounter;
//            ++qCounter;
//        }
//
//        return oOccurenceCount;
//    }
//}

/*
N + (N + M) + (N + M), N + N
*/
namespace UsingPrefixHash
{
    const int K = 1000000007;
    const int pPrime = 199;

    vector<long long int> BuildPowerArray(const int pPrime, int nSize)
    {
        vector<long long int> oPower(nSize + 1, 1);
        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
            oPower[iCounter] = ((oPower[iCounter - 1]) * pPrime) % K;

        return oPower;
    }

    int getOccurences(string& a, string& b, vector<long long int> &oPower)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        //vector<long long int> oPower = BuildPowerArray(pPrime, max(aSize, bSize));

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
                oCount++;
        }

        return oCount;
    }
}

namespace UsingDoublePrefixHash
{
    const int K = 1000000007;
    const int pFPrime = 103;
    const int pSPrime = 113;

    vector<long long int> BuildPowerArray(const int pPrime, int nSize)
    {
        vector<long long int> oPower(nSize + 1, 1);
        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
            oPower[iCounter] = ((oPower[iCounter - 1]) * pPrime) % K;

        return oPower;
    }

    int getOccurences(string& a, string& b, vector<long long int>& oFPower, vector<long long int>& oSPower)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        //vector<long long int> oPower = BuildPowerArray(pPrime, max(aSize, bSize));

        // Hash for Substring
        long long int bFHashValue = 0;
        long long int bSHashValue = 0;
        for (int iCounter = 0; iCounter < bSize; ++iCounter)
        {
            bFHashValue = (bFHashValue + (b[iCounter] * oFPower[iCounter + 1]) % K) % K;
            bSHashValue = (bSHashValue + (b[iCounter] * oSPower[iCounter + 1]) % K) % K;
        }
            

        // Build Prefix Hash for MainString
        vector<long long int> oAFPrefixHash(aSize, 0);
        vector<long long int> oASPrefixHash(aSize, 0);

        oAFPrefixHash[0] = a[0] * oFPower[1];
        oASPrefixHash[0] = a[0] * oSPower[1];

        for (int iCounter = 1; iCounter < aSize; ++iCounter)
        {
            oAFPrefixHash[iCounter] = (oAFPrefixHash[iCounter - 1] + (a[iCounter] * oFPower[iCounter + 1]) % K) % K;
            oASPrefixHash[iCounter] = (oASPrefixHash[iCounter - 1] + (a[iCounter] * oSPower[iCounter + 1]) % K) % K;
        }
        

        // Check for First Window
        if ((bFHashValue == oAFPrefixHash[bSize - 1]) && (bSHashValue == oASPrefixHash[bSize - 1]))
            oCount++;

        // From Second window onwards
        for (int iCounter = bSize; iCounter < aSize; ++iCounter)
        {
            bFHashValue = (bFHashValue * oFPower[1]) % K;
            bSHashValue = (bSHashValue * oSPower[1]) % K;

            long long int aFHashValue = (oAFPrefixHash[iCounter] - oAFPrefixHash[iCounter - bSize] + K) % K;
            long long int aSHashValue = (oASPrefixHash[iCounter] - oASPrefixHash[iCounter - bSize] + K) % K;

            if ((aFHashValue == bFHashValue) && (aSHashValue == bSHashValue))
                oCount++;
        }

        return oCount;
    }
}

namespace UsingTriplePrefixHash
{
    const int K = 1000000007;
    const int pFPrime = 103;
    const int pSPrime = 113;
    const int pTPrime = 17389;

    vector<long long int> BuildPowerArray(const int pPrime, int nSize)
    {
        vector<long long int> oPower(nSize + 1, 1);
        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
            oPower[iCounter] = ((oPower[iCounter - 1]) * pPrime) % K;

        return oPower;
    }

    int getOccurences(string& a, string& b, 
        vector<long long int>& oFPower, 
        vector<long long int>& oSPower, 
        vector<long long int>& oTPower)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        //vector<long long int> oPower = BuildPowerArray(pPrime, max(aSize, bSize));

        // Hash for Substring
        long long int bFHashValue = 0;
        long long int bSHashValue = 0;
        long long int bTHashValue = 0;
        for (int iCounter = 0; iCounter < bSize; ++iCounter)
        {
            bFHashValue = (bFHashValue + (b[iCounter] * oFPower[iCounter + 1]) % K) % K;
            bSHashValue = (bSHashValue + (b[iCounter] * oSPower[iCounter + 1]) % K) % K;
            bTHashValue = (bTHashValue + (b[iCounter] * oTPower[iCounter + 1]) % K) % K;
        }


        // Build Prefix Hash for MainString
        vector<long long int> oAFPrefixHash(aSize, 0);
        vector<long long int> oASPrefixHash(aSize, 0);
        vector<long long int> oATPrefixHash(aSize, 0);

        oAFPrefixHash[0] = a[0] * oFPower[1];
        oASPrefixHash[0] = a[0] * oSPower[1];
        oATPrefixHash[0] = a[0] * oTPower[1];

        for (int iCounter = 1; iCounter < aSize; ++iCounter)
        {
            oAFPrefixHash[iCounter] = (oAFPrefixHash[iCounter - 1] + (a[iCounter] * oFPower[iCounter + 1]) % K) % K;
            oASPrefixHash[iCounter] = (oASPrefixHash[iCounter - 1] + (a[iCounter] * oSPower[iCounter + 1]) % K) % K;
            oATPrefixHash[iCounter] = (oATPrefixHash[iCounter - 1] + (a[iCounter] * oTPower[iCounter + 1]) % K) % K;
        }


        // Check for First Window
        if ((bFHashValue == oAFPrefixHash[bSize - 1]) 
         && (bSHashValue == oASPrefixHash[bSize - 1])
         && (bTHashValue == oATPrefixHash[bSize - 1]))
            oCount++;

        // From Second window onwards
        for (int iCounter = bSize; iCounter < aSize; ++iCounter)
        {
            bFHashValue = (bFHashValue * oFPower[1]) % K;
            bSHashValue = (bSHashValue * oSPower[1]) % K;
            bTHashValue = (bTHashValue * oTPower[1]) % K;

            long long int aFHashValue = (oAFPrefixHash[iCounter] - oAFPrefixHash[iCounter - bSize] + K) % K;
            long long int aSHashValue = (oASPrefixHash[iCounter] - oASPrefixHash[iCounter - bSize] + K) % K;
            long long int aTHashValue = (oATPrefixHash[iCounter] - oATPrefixHash[iCounter - bSize] + K) % K;

            if ((aFHashValue == bFHashValue) 
             && (aSHashValue == bSHashValue)
             && (aTHashValue == bTHashValue))
                oCount++;
        }

        return oCount;
    }
}
/*
 N + M + (N+M-1), N
*/
namespace UsingRollingHash
{
    vector<long long int> BuildPowerArray(int Prime, int nSize)
    {
        vector<long long int> pArray(nSize);
        long long int Result = Prime;
        for (int iCounter = 0; iCounter < nSize; iCounter++)
        {
            pArray[iCounter] = Result;
            Result = (Result * Prime) % M;
        }
        return pArray;
    }

    long long int getHashValue(string& pArray, int nSize, vector<long long int>& pPowerArray)
    {
        long long int ResultantHashValue = 0;

        for (int iCounter = 0; iCounter < nSize; iCounter++)
        {
            ResultantHashValue = (ResultantHashValue + (pArray[iCounter] * pPowerArray[nSize - iCounter - 1]) % M) % M;
        }

        return ResultantHashValue;
    }

    int getOccurences(string& pArray, string& pPattern, vector<long long int>& pPowerArray)
    {
        int nSize = static_cast<int>(pArray.size());
        int wSize = static_cast<int>(pPattern.size());

        int iCounter = 0;
        int jCounter = wSize - 1;
        int OccurenceCount = 0;

        long long int pHashValue = getHashValue(pPattern, wSize, pPowerArray);
        long long int wHashValue = getHashValue(pArray, wSize, pPowerArray);

        while (jCounter < nSize)
        {
            if (wHashValue == pHashValue)
                OccurenceCount++;

            wHashValue = ((((wHashValue - (pArray[iCounter] * pPowerArray[wSize - 1]) % M + M) % M + pArray[jCounter + 1]) * pPowerArray[0]) % M);

            iCounter++;
            jCounter++;
        }

        return OccurenceCount;
    }
}


int main()
{
    vector<long long int> oFPower = UsingTriplePrefixHash::BuildPowerArray(UsingTriplePrefixHash::pFPrime, 10000);
    vector<long long int> oSPower = UsingTriplePrefixHash::BuildPowerArray(UsingTriplePrefixHash::pSPrime, 10000);
    vector<long long int> oTPower = UsingTriplePrefixHash::BuildPowerArray(UsingTriplePrefixHash::pTPrime, 10000);

    string a{"algo"};
    string b{ "yalgoalgoalgopalgoaxalgoasaxalgolalgoalgoalgo" };
    cout << UsingTriplePrefixHash::getOccurences(b, a, oFPower, oSPower, oTPower);
     
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
