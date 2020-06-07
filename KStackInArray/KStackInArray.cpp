// KStackInArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class KStack
{
public:
    KStack(int oCapacity, int oStacks)
    { 
        this->nCapacity = oCapacity;
        this->nStacks = oStacks;
        this->oFreeTop = 0;
        this->oContainer.resize(nCapacity);
        this->oNext.resize(nCapacity);
        this->oTop.resize(nStacks);
        for (int iCounter = 0; iCounter < nStacks; ++iCounter)
            this->oTop[iCounter] = -1;

        for (int iCounter = 0; iCounter < (nCapacity - 1); ++iCounter)
            this->oNext[iCounter] = iCounter + 1;

        this->oNext[nCapacity - 1] = -1;
    }

    void Push(int oStackIdx, int value)
    {
        if (oFreeTop == -1) {
            cout << "Overflow" << endl;
            return;
        }
        int xIdx = oFreeTop;
        oFreeTop = oNext[xIdx];
        oNext[xIdx] = oTop[oStackIdx];
        oTop[oStackIdx] = xIdx;
        oContainer[xIdx] = value;
    }

    int Pop(int oStackIdx)
    {
        if (this->IsEmpty(oStackIdx))
        {
            cout << "Underflow" << endl;
            return -1;
        }

        int xIdx = oTop[oStackIdx];
        oTop[oStackIdx] = oNext[xIdx];
        oNext[xIdx] = oFreeTop;
        oFreeTop = xIdx;
        return oContainer[xIdx];
    }

    int Top(int oStackIdx)
    {
        if (this->IsEmpty(oStackIdx))
        {
            cout << "Underflow" << endl;
            return -1;
        }

        return oContainer[oTop[oStackIdx]];
    }

    bool IsEmpty(int oStackIdx) {
        return (oTop[oStackIdx] == -1);
    }
         
    //int Size(int oStackIdx)
    //{
    //    // this is wrong
    //    return oTop[oStackIdx] + 1;
    //}

private:
    int nCapacity;
    int nStacks;
    int oFreeTop;
    vector<int> oTop;
    vector<int> oNext;
    vector<int> oContainer; 
};



int main()
{
    KStack oStack(10, 3);
    oStack.Push(0, 300);
    oStack.Push(0, 500);
    oStack.Push(2, 900);
    oStack.Push(1, 800);
    cout << oStack.Pop(0) << endl;
    oStack.Push(2, 1100);
    cout << oStack.Top(2) << endl;
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
