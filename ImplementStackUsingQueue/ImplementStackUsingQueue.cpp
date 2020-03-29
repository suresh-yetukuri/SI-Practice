// ImplementStackUsingQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class Stack
{
public:
    void Push(int val)
    {
        pMain.push(val);
    }

    void Pop()
    {
        if (pMain.empty())
        {
            cout << "Underflow" << endl;
            return;
        }

        while (pMain.size() > 1u)
        {
            int xValue = pMain.front();
            pAux.push(xValue);
            pMain.pop();
        }

        pMain.pop();
        swap(pMain, pAux);
    }

    int Top()
    {
        if (pMain.empty())
            return -1; 

        while (pMain.size() > 1u)
        {
            int xValue = pMain.front();
            pAux.push(xValue);
            pMain.pop();
        }

        int oValue = pMain.front();
        pAux.push(oValue);
        pMain.pop();
        swap(pMain, pAux);
        return oValue;
    }

    size_t Size() const
    {
        return pMain.size();
    }
private:
    queue<int> pMain;
    queue<int> pAux;
};

int main()
{ 
    Stack pStack;
    pStack.Push(1);
    pStack.Push(2);
    pStack.Push(3);
    pStack.Push(4);
    cout << "Size: " << pStack.Size() << endl;
    pStack.Pop();
    cout << "Top: " << pStack.Top() << endl;
    pStack.Push(5);
    cout << "Top: " << pStack.Top() << endl;
    pStack.Pop();
    pStack.Pop();
    cout << "Top: " << pStack.Top() << endl;
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
