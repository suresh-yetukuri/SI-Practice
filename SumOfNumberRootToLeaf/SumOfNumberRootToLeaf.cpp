// SumOfNumberRootToLeaf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const long long int M = static_cast<long long int>(1e9 + 7);

class Node
{
public:
    int Data;
    Node* pLeft;
    Node* pRight;
    Node(int val)
    {
        this->Data = val;
        this->pLeft = nullptr;
        this->pRight = nullptr;
    }
};

Node* InsertRecursive(Node* pRoot, const int oData)
{
    if (nullptr == pRoot)
        pRoot = new Node(oData);
    else if (oData > pRoot->Data)
        pRoot->pRight = InsertRecursive(pRoot->pRight, oData);
    else if (oData < pRoot->Data)
        pRoot->pLeft = InsertRecursive(pRoot->pLeft, oData);

    return pRoot;
}

Node* DeleteTree(Node* pRoot)
{
    if (nullptr != pRoot)
    {
        if (nullptr != pRoot->pLeft)
            pRoot->pLeft = DeleteTree(pRoot->pLeft);

        if (nullptr != pRoot->pRight)
            pRoot->pRight = DeleteTree(pRoot->pRight);

        delete(pRoot);
        pRoot = nullptr;
    }
    return pRoot;
}

long long int CountDigits(long long int oInput)
{
    return static_cast<long long int>(floor(log10(oInput) + 1ll));
}

long long int SumRootToLeaf(Node* pRoot, long long int oCurrent)
{
    if (nullptr == pRoot)
        return 0;

    long long int oMultiplyFactor = static_cast<long long int>(pow(10ll, CountDigits(pRoot->Data)));
    oCurrent = ((oCurrent * oMultiplyFactor) % M + pRoot->Data) % M;

    if (nullptr == pRoot->pLeft && nullptr == pRoot->pRight)
        return oCurrent;
    else
    {
        return SumRootToLeaf(pRoot->pLeft, oCurrent)
             + SumRootToLeaf(pRoot->pRight, oCurrent);
    }
}


int main()
{
    long long int odi = CountDigits(234);
    vector<int> oInput{ 4, 5, 15, 2, 1, 7, 17 };
    Node* pRoot = nullptr;
    for (auto& oData : oInput)
        pRoot = InsertRecursive(pRoot, oData);

    long long int oSum = 0;
    oSum = SumRootToLeaf(pRoot, 0);
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
