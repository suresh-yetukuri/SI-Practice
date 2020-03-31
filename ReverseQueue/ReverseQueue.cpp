// ReverseQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

namespace Iterative
{
    void Reverse(queue<int>& pQueue)
    {
        stack<int> pStack;
        while (!pQueue.empty())
        {
            pStack.push(pQueue.front());
            pQueue.pop();
        }

        while (!pStack.empty())
        {
            pQueue.push(pStack.top());
            pStack.pop();
        }
    }
}

namespace Recursive
{
    void Reverse(queue<int>& pQueue)
    {
        if (pQueue.empty())
            return;

        int val = pQueue.front();
        pQueue.pop();
        Reverse(pQueue);
        pQueue.push(val);
    }
}


int main()
{
    queue<int> pQueue;
    pQueue.push(1);
    pQueue.push(2);
    pQueue.push(3);
    pQueue.push(4);
    pQueue.push(5); 
    Iterative::Reverse(pQueue);
    Recursive::Reverse(pQueue);
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
