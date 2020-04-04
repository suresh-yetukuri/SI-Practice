// InfixToPostfix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <unordered_map>
using namespace std;


unordered_map<char, int> GetOperatorPrecedenceHashMap()
{
    unordered_map<char, int> oHashMap;
    oHashMap['*'] = 10;
    oHashMap['/'] = 10;
    oHashMap['+'] = 9;
    oHashMap['-'] = 9;
    return move(oHashMap);
}

bool IsLeftParanthesis(char& oChar)
{
    return '(' == oChar;
}

bool IsRightParanthesis(char& oChar)
{
    return ')' == oChar;
}

bool IsOperand(char& oChar)
{
    return 0 != isdigit(oChar);
}

bool IsOperator(char& oChar, unordered_map<char, int>& oPrecedenceMap)
{
    return oPrecedenceMap.find(oChar) != oPrecedenceMap.end();
}

string ConvertInfixToPostfix(string& oInfix, unordered_map<char, int>& oPrecedenceMap)
{
    string oPostfix;
    stack<char> pStack;
    oInfix.push_back(')'); 
    pStack.push('(');

    for (auto& oChar : oInfix)
    {
        if (IsOperand(oChar))
            oPostfix.push_back(oChar);
        else if (IsOperator(oChar, oPrecedenceMap))
        {
            while (!pStack.empty())
            {
                if (IsOperator(pStack.top(), oPrecedenceMap) && (oPrecedenceMap[pStack.top()] >= oPrecedenceMap[oChar]))
                {
                    oPostfix.push_back(pStack.top());
                    pStack.pop();
                }
                else
                    break;
            }

            pStack.push(oChar);
        }
        else if (IsLeftParanthesis(oChar))
            pStack.push(oChar);
        else if (IsRightParanthesis(oChar))
        {
            while (!pStack.empty())
            {
                if (!IsLeftParanthesis(pStack.top()))
                {
                    oPostfix.push_back(pStack.top());
                    pStack.pop();
                }
                else
                {
                    pStack.pop();
                    break;
                }
            }
        }
        else
            continue; // Some invalid charater that we don't want to consider 
    } 

    return move(oPostfix);
}

int main()
{

    auto oHashMap = GetOperatorPrecedenceHashMap();
    string Infix{ "1+((2+3)+(4+5)*6)/7" };
    cout << Infix << endl;
    cout << ConvertInfixToPostfix(Infix, oHashMap);
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
