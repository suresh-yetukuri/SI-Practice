// MinStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

class MinStack
{
public:
    MinStack()
    {
        stack<int> oMainEmpty;
        stack<int> oAuxEmpty;
        swap(oMainStack, oMainEmpty);
        swap(oAuxStack, oAuxEmpty);
    }

    void Push(int val)
    {
        oMainStack.push(val);
        if (oAuxStack.empty() || oAuxStack.top() >= val)
            oAuxStack.push(val);
    }

    void Pop()
    {
        if (oMainStack.empty())
            return;

        if (oMainStack.top() == oAuxStack.top())
            oAuxStack.pop();

        oMainStack.pop();
    }

    int Top()
    {
        if (oMainStack.empty())
            return -1;

        return oMainStack.top();
    }

    int Min()
    {
        if (oMainStack.empty())
            return -1;

        return oAuxStack.top();
    }
private:
    stack<int> oMainStack;
    stack<int> oAuxStack;
};

int main()
{
    return 0;
}
