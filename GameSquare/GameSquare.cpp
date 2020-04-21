// GameSquare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long int> GetPerfectSqArray(long long int nSize)
{ 
    vector<long long int> oPerfectArray(nSize + 1ll);
    long long int oPerfectSquare = 1ll;
    for (long long int iCounter = 1ll; iCounter <= nSize; ++iCounter)
    { 
        if ((oPerfectSquare * oPerfectSquare) <= iCounter) {
            oPerfectArray[iCounter] = oPerfectSquare;
            ++oPerfectSquare;
        }
        else {
            oPerfectArray[iCounter] = oPerfectArray[iCounter - 1ll];
        } 
    }

    return move(oPerfectArray);
}

vector<bool> GetStrategy(vector<long long int>& oPerfectArray, long long int nSize)
{
    vector<bool> oStrategy(nSize + 1, false);
    for (long long int iCounter = 1ll; iCounter <= nSize; ++iCounter) 
        oStrategy[iCounter] = !oStrategy[iCounter - oPerfectArray[iCounter]];

    return move(oStrategy);
}

//vector<bool> GetPerfectSqArray(long long int nSize)
//{
//    vector<bool> oPerfectArray(nSize + 1ll, false);
//    int oLastPerfectSquare = 1;
//    for (long long int iCounter = 1ll; iCounter <= nSize; ++iCounter)
//    {
//        if ((oLastPerfectSquare * oLastPerfectSquare) == iCounter) {
//            oPerfectArray[iCounter] = true;
//            ++oLastPerfectSquare;
//        }
//    }
//
//    return move(oPerfectArray);
//}


int main()
{
    long long int nSize = static_cast<int>(100);
    auto oPerfectArray = GetPerfectSqArray(nSize);
    //auto oStrategy = GetStrategy(oPerfectArray, nSize);
    //cout << oStrategy[1] << endl;
    //cout << oStrategy[2] << endl;
    //cout << oStrategy[3] << endl;
    //cout << oStrategy[16] << endl;
    //cout << oStrategy[10] << endl;
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
