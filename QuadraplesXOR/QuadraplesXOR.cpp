// QuadraplesXOR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>  
#include <algorithm>    
#include <vector>
#include <unordered_map>
using namespace std;

/*
N^4, 1
*/
namespace BruteForce
{
    int Count(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());
        int cSize = static_cast<int>(c.size());
        int dSize = static_cast<int>(d.size());

        for(int iCounter = 0; iCounter < aSize; ++iCounter)
            for(int jCounter = 0; jCounter < bSize; ++jCounter)
                for(int kCounter = 0; kCounter < cSize; ++kCounter)
                    for (int lCounter = 0; lCounter < dSize; ++lCounter)
                    {
                        if ((a[iCounter] ^ b[jCounter] ^ c[kCounter] ^ d[lCounter]) == 0)
                            oCount++;
                    }


        return oCount;
    }
}

/*
N^2 + N^2 + (N^2)Log(N^2) + (N^2)(Log(N^2) + Log(N^2))
*/
namespace BinarySearch
{

    int Count(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());
        int cSize = static_cast<int>(c.size());
        int dSize = static_cast<int>(d.size());
        vector<int> oABXor;
        vector<int> oCDXor;

        // N^2
        for (int iCounter = 0; iCounter < aSize; ++iCounter)
            for (int jCounter = 0; jCounter < bSize; ++jCounter)
                oABXor.push_back(a[iCounter] ^ b[jCounter]);

        // N^2
        for (int kCounter = 0; kCounter < cSize; ++kCounter)
            for (int lCounter = 0; lCounter < dSize; ++lCounter)
                oCDXor.push_back(c[kCounter] ^ d[lCounter]);

        // (N^2)Log(N^2)
        sort(oABXor.begin(), oABXor.end());

        // N^2
        for (auto& kVal : oCDXor)
        {
            auto low = lower_bound(oABXor.begin(), oABXor.end(), kVal); //Log (N^2)
            auto high = upper_bound(oABXor.begin(), oABXor.end(), kVal); // Log(N^2)
            oCount += static_cast<int>(high - low);
        }

        return oCount;
    }
}


/*
N^2 + N^2, N^2 + N^2
*/
namespace HashMap
{
    int Count(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d)
    {
        int oCount = 0;
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());
        int cSize = static_cast<int>(c.size());
        int dSize = static_cast<int>(d.size());
        vector<int> oABXor;
        unordered_map<int, int> oUHmap;

        // N^2
        for (int iCounter = 0; iCounter < aSize; ++iCounter)
            for (int jCounter = 0; jCounter < bSize; ++jCounter)
            {
                oABXor.push_back(a[iCounter] ^ b[jCounter]);
                oUHmap[c[iCounter] ^ d[jCounter]]++;
            }
             

        // N^2
        for (auto& kVal : oABXor)
        { 
            auto pItr = oUHmap.find(kVal);
            if (oUHmap.end() != pItr)
                oCount += pItr->second;
        }

        return oCount;
    }
}

int main()
{ 
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
