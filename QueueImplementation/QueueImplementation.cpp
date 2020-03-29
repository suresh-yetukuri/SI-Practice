// QueueImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Queue
{
public:
    Queue(int oCap)
    {
        Capacity = oCap;
        oContainer.resize(Capacity);
        oFront = oRear = -1;
    }

    void Enqueue(int val)
    {
        if (IsFull()) {
            cout << "Overflow" << endl;
            return;
        }

        if (IsEmpty()) {
            ++oFront;
            ++oRear;
        }
        else
            oRear = (oRear + 1) % Capacity;

        oContainer[oRear] = val;
    }

    int Dequeue()
    {
        int xValue = INT_MIN;
        if (IsEmpty()) {
            return xValue;
        }
        else
        {
            xValue = oContainer[oFront];
            if (oFront == oRear)
                oFront = oRear = -1;
            else
                oFront = (oFront + 1) % Capacity;
        }
        return xValue;
    }

    int Front()
    {
        if (IsEmpty()) {
            return INT_MIN;
        }

        return oContainer[oFront];
    }

    int Rear()
    {
        if (IsEmpty()) {
            return INT_MIN;
        }

        return oContainer[oRear];
    }

    int Size()
    {
        if (IsEmpty())
            return 0;
        else if (IsFull())
            return Capacity;
        else
            return (((Capacity - oFront) + oRear) + 1) % Capacity;
    }

    bool IsEmpty()
    {
        if ((oFront == oRear) && (-1 == oFront))
            return true;

        return false;
    }

    bool IsFull()
    {
        return ((oRear + 1) % Capacity) == oFront;
    }

private:
    int Capacity;
    int oFront;
    int oRear;
    vector<int> oContainer;
};

int main()
{

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
