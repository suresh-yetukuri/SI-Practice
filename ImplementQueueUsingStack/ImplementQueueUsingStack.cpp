// ImplementQueueUsingStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Queue
{
public:
    void Push(int x)
    {
        pMain.push(x);
    }

    void Pop()
    {
        if (empty())
            return;

        if (pAux.empty())
        { 
            while (!pMain.empty())
            {
                pAux.push(pMain.top());
                pMain.pop();
            }
        }
        
        pAux.pop();
    }

    int Front()
    {
        if (empty())
            return -1;

        if (pAux.empty())
        {
            while (!pMain.empty())
            {
                pAux.push(pMain.top());
                pMain.pop();
            }
        }

        return pAux.top();
    }

    size_t Size()
    {
        return pMain.size() + pAux.size();
    }

    bool empty()
    {
        if (pMain.size() == 0u && pAux.size() == 0u)
            return true;

        return false;
    }
     
private:
    stack<int> pMain;
    stack<int> pAux;
};

int main()
{
    Queue pQueue;
    pQueue.Push(1);
    pQueue.Push(2);
    pQueue.Push(3);
    pQueue.Push(4);
    cout << "Front: " << pQueue.Front() << endl;
    pQueue.Pop();
    pQueue.Push(5);
    cout << "Size: " << pQueue.Size() << endl;
    cout << "Front: " << pQueue.Front() << endl;
    pQueue.Pop();
    cout << "Front: " << pQueue.Front() << endl;
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
