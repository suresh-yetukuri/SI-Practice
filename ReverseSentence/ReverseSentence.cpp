// ReverseSentence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

void ReverseSentence(string& s)
{
    stack<string> pStack;
    string oWord{};
    for (const auto& ch : s)
    {
        if (ch != ' ')
            oWord.push_back(ch);
        else
        {
            pStack.push(move(oWord));
            oWord = string{};
        }
    }

    if (!oWord.empty())
        pStack.push(move(oWord));

    while (!pStack.empty())
    {
        cout << pStack.top() << " ";
        pStack.pop();
    }

    return;
}

int main()
{
    string oInput{ "algorithms and structures data" };
    ReverseSentence(oInput);
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
