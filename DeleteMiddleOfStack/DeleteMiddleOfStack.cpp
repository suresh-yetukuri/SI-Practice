// DeleteMiddleOfStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
using namespace std;

void deleteMidUtil(stack<int>& s, int nSize, int oCounter)
{
    if (s.empty())
        return;

    int x = s.top();
    s.pop();
    deleteMidUtil(s, nSize, oCounter - 1);
    if (oCounter != 0)
        s.push(x);
}


//User function Template for C++
//You need to complete this function
stack<int> deleteMid(stack<int> s, int sizeOfStack, int current)
{
    int oCounter = static_cast<int>(ceil(sizeOfStack/2.0));
    deleteMidUtil(s, sizeOfStack, oCounter - 1);
    return s;
}

int main()
{
    stack<int> pStack;
    int nSize = 5;
    for (int iCounter = 1; iCounter <= nSize; ++iCounter)
        pStack.push(iCounter);

    auto oMStack = deleteMid(pStack, nSize, 0);
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
