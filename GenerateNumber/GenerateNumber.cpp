// GenerateNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Generate n numbers in sorted order containing only digit 5&6
ex: n = 4
5, 6, 55, 56
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

namespace Optimized
{
    void GenerateNumber(vector<string>&& oDigits, int nCount)
    { 
        queue<string> pQueue;
        for (auto& x : oDigits)
            pQueue.push(x);

        while (!pQueue.empty() && (nCount > 0))
        {
            string value = move(pQueue.front());
            pQueue.pop();
            for (auto& x : oDigits)
                pQueue.push(value + x);

            cout << value << " ";
            --nCount;
        }
    }
}

namespace BruteForce
{
    /*
    
    Have a loop
    iCounter = 1;
    while(nCount > 0)
    {
        if(IsValid(oDigits, iCounter)) // this function check whether iCounter contain
                 --nCount;             // only digits available in oDigits vector
            

        ++iCounter;
    }
    */
}



int main()
{
    
    Optimized::GenerateNumber({ "5", "6" }, 10);
    cout << endl;
    Optimized::GenerateNumber({ "5", "6", "7" }, 10);
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
