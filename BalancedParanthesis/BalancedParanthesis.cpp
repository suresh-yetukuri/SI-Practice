// BalancedParanthesis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

bool IsBalanced(string& oInput)
{
    if (oInput.empty())
        return true;

    int nSize = static_cast<int>(oInput.size());
    stack<char> pStack;
    auto IsMatching = [](const char& a, const char& b)->bool {
        if (((a == '{') && (b == '}')) ||
            ((a == '[') && (b == ']')) ||
            ((a == '(') && (b == ')')))
            return true;

        return false;
    };

    for (int iCounter = 0; iCounter < nSize; ++iCounter)
    {
        const char oTargetChar = oInput[iCounter];
        if ((oTargetChar == '{') || (oTargetChar == '[') || (oTargetChar == '('))
            pStack.push(oTargetChar);
        else {
            if (pStack.empty())
                return false;
            else if (IsMatching(pStack.top(), oTargetChar))
                pStack.pop();
            else
                return false;
        } 
    }

    return pStack.empty();
}



int main()
{
    string oInput{ "(())}[{}]" };
    cout << IsBalanced(oInput);
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
