// PostfixEvaluation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


bool IsOperand(string& s)
{
    char *p;
    long oNum = strtol(s.c_str(), &p, 10);
    if (*p)
        return false;

    return true;
}

int ApplyOperator(int a, int b, char& oOperator)
{
    switch (oOperator)
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
        break;
    }

    return -1;
}


/*
For Evaluation of Prefix we have
to scan from right to left
*/
int EvaluatePostfix(vector<string>& oPostfix)
{
    stack<int> pStack;
    oPostfix.push_back(string{")"});
    for (auto& oString : oPostfix)
    {
        if (oString[0] != ')')
        {
            if (IsOperand(oString))
                pStack.push(stoi(oString));
            else
            {
                int oSecondOperand = pStack.top();
                pStack.pop();
                int oFirstOperand = pStack.top();
                pStack.pop();
                pStack.push(ApplyOperator(oFirstOperand, oSecondOperand, oString[0]));
            }
        }
        else {
            break;
        }
    }
    oPostfix.pop_back();
    return pStack.top();
}
 


int main()
{
    vector<string> oInput{ "-+"};
    int oResult = EvaluatePostfix(oInput);
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
