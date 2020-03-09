// AnagramEasy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
N^2, 1
*/
namespace BruteForce
{
    bool IsAnagram(string& a, string& b)
    {
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        if (aSize != bSize)
            return false;
         
        for (int iCounter = 0; iCounter < aSize; ++iCounter)
        {
            bool IsFound = false;
            for (int jCounter = 0; jCounter < bSize; ++jCounter)
            {
                if (a[iCounter] == b[jCounter])
                {
                    IsFound = true;
                    b[jCounter] = '\0';
                    break;
                }
            }

            if (!IsFound)
                return false;
        }

        return true;
    }
}

/*
NLogN + NLogN + N, 1
*/
namespace Sorting
{
    bool IsAnagram(string& a, string& b)
    {
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        if (aSize != bSize)
            return false;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int pCounter = 0;
        int qCounter = 0;

        while (pCounter < aSize && qCounter < bSize)
        {
            if (a[pCounter] != b[qCounter])
                return false;

            ++pCounter;
            ++qCounter;
        }

        return true;
    }
}


namespace CountArray
{
    /*
     N + 26, 26 + 26
    */
    bool IsAnagram(const string& a, const string& b)
    {
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        if (aSize != bSize)
            return false;

        vector<int> aCountArray(26, 0);
        vector<int> bCountArray(26, 0);

        for (int iCounter = 0; iCounter < aSize; ++iCounter)
        {
            aCountArray[a[iCounter]-'a']++;
            bCountArray[b[iCounter]-'a']++;
        }

        for (int iCounter = 0; iCounter < 26; ++iCounter)
        {
            if (aCountArray[iCounter] != bCountArray[iCounter])
                return false;
        }

        return true;
    }

    /*
     N + 26, 26
    */
    bool IsAnagramBetter(const string& a, const string& b)
    {
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        if (aSize != bSize)
            return false;

        vector<int> aCountArray(26, 0); 

        for (int iCounter = 0; iCounter < aSize; ++iCounter)
        {
            aCountArray[a[iCounter] - 'a']++;
            aCountArray[b[iCounter] - 'a']--;
        }

        for (int iCounter = 0; iCounter < 26; ++iCounter)
        {
            if (aCountArray[iCounter] != 0)
                return false;
        }

        return true;
    }
}

/*
N + C, C: Where C is the number of unique elements C<=26
*/
namespace HashMap
{
    bool IsAnagram(const string& a, const string& b)
    {
        int aSize = static_cast<int>(a.size());
        int bSize = static_cast<int>(b.size());

        if (aSize != bSize)
            return false;

        unordered_map<int, int> oMap;

        for (int iCounter = 0; iCounter < aSize; ++iCounter)
        {
            oMap[a[iCounter] - 'a']++;
            oMap[b[iCounter] - 'a']--;
        }

        int cMapSize = static_cast<int>(oMap.size());
        for (auto& kMap : oMap)
        {
            if (kMap.second != 0)
                return false;
        }
         

        return true;
    }
}

int main()
{
    cout << HashMap::IsAnagram("suryeshz", "eshzursx");
    return 0;
}
