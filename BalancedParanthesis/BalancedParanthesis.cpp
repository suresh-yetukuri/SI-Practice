// BalancedParanthesis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <unordered_map>
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

unordered_map <char, int> oHashMap;
bool IsInitialized = false;

int ApplyOperator(int a, int b, char ch)
{
    switch (ch)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }

    return 0;
}

bool IsOperator(char ch)
{
    switch (ch)
    {
    case '+':
        return true;
    case '-':
        return true;
    case '*':
        return true;
    case '/':
        return true;
    default:
        return false;
    }

    return false;
}

// The main function that returns value of a given postfix expression
int evaluatePostfix(string& str)
{
    stack<int> pStack;
    for (auto ch : str)
    {
        if (IsOperator(ch)) {
            int op2 = pStack.top(); pStack.pop();
            int op1 = pStack.top(); pStack.pop();
            pStack.push(ApplyOperator(op1, op2, ch));
        }
        else
            pStack.push(atoi(&ch));
    }

    return pStack.top();
}


int main()
{
    char c = '2';
    int a = atoi(&c);
    string oInput{ "231*+9-" };
    cout << evaluatePostfix(oInput);
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
