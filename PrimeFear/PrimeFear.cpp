// PrimeFear.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


namespace BruteForce
{
    bool IsAfraidPrime(int oInput, vector<bool>& oPrime, vector<int>& oPower)
    {
        int oTotalDigits = static_cast<int>(floor(log10(oInput)));
        while (oTotalDigits != 0)
        {
            int FirstDigit = oInput / oPower[oTotalDigits];
            oInput = oInput - (FirstDigit * oPower[oTotalDigits]);
            int reducedTotalDigits = static_cast<int>(floor(log10(oInput)));
            if (reducedTotalDigits != (oTotalDigits - 1) || (oInput == 0) || !oPrime[oInput])
                return false;

            --oTotalDigits;
        }

        return true;
    }

    vector<bool> GetPrime(int oInput)
    {
        vector<bool> oPrime(oInput + 1, true);
        oPrime[0] = oPrime[1] = false;

        for (int iCounter = 2; (iCounter * iCounter <= oInput); ++iCounter)
        {
            if (oPrime[iCounter])
            {
                for (int jCounter = (iCounter * iCounter); jCounter <= oInput; jCounter += iCounter)
                    oPrime[jCounter] = false;
            }
        }

        return move(oPrime);
    }

    vector<int> GetPowerOf10(int oInput)
    {
        vector<int> oPower(oInput + 1, 1);
        int Result = 10;
        for (int iCounter = 1; iCounter <= oInput; ++iCounter)
        {
            oPower[iCounter] = Result;
            Result = Result * 10;
        }

        return move(oPower);
    }

    vector<int> GetAfraidPrime(int nLimit, vector<bool>& oPrime, vector<int>& oPower)
    {
        vector<int> oAfraidPrime(nLimit + 1, 0);
        int oAfraidPrimeCount = 0;
        for (int iCounter = 1; iCounter <= nLimit; ++iCounter)
        {
            if (oPrime[iCounter] && IsAfraidPrime(iCounter, oPrime, oPower))
            {
                ++oAfraidPrimeCount;
            }

            oAfraidPrime[iCounter] = oAfraidPrimeCount;
        }

        return move(oAfraidPrime);
    }
}



int main()
{
    int nLimit = static_cast<int>(1e6);
    vector<bool> oPrime = BruteForce::GetPrime(nLimit);
    vector<int> oPower = BruteForce::GetPowerOf10(6);
    vector<int> oAfraidPrime = BruteForce::GetAfraidPrime(nLimit, oPrime, oPower);
    vector<int> oQueries{ 5, 100, 30 };
    for_each(oQueries.begin(), oQueries.end(), [&oAfraidPrime](int oVal)->void {
        cout << oAfraidPrime[oVal] << endl;
        });

    return 0;
}
