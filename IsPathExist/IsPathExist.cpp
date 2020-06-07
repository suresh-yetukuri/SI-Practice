// IsPathExist.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <list>
using namespace std;

bool IsMoveValid(int iCounter, int jCounter, vector<vector<int>>& pMatrix, vector<vector<bool>>& pVisited)
{
    int N = pMatrix.size();
    if (iCounter >= 0 && iCounter < N && jCounter >= 0 && jCounter < N
        && false == pVisited[iCounter][jCounter]
        && (pMatrix[iCounter][jCounter] == 3 || pMatrix[iCounter][jCounter] == 2))
        return true;

    return false;
}

bool DFS(int iCounter, int jCounter, vector<vector<int>>& pMatrix, vector<vector<bool>>& pVisited)
{
    if (pMatrix[iCounter][jCounter] == 2)
        return true;

    pVisited[iCounter][jCounter] = true;


    if (IsMoveValid(iCounter, jCounter + 1, pMatrix, pVisited)
        && DFS(iCounter, jCounter + 1, pMatrix, pVisited))
        return true;

    if (IsMoveValid(iCounter, jCounter - 1, pMatrix, pVisited)
        && DFS(iCounter, jCounter - 1, pMatrix, pVisited))
        return true;

    if (IsMoveValid(iCounter + 1, jCounter, pMatrix, pVisited)
        && DFS(iCounter + 1, jCounter, pMatrix, pVisited))
        return true;

    if (IsMoveValid(iCounter - 1, jCounter, pMatrix, pVisited)
        && DFS(iCounter - 1, jCounter, pMatrix, pVisited))
        return true;
     
    return false;
}

bool IsPathExist(vector<vector<int>>& pMatrix, int N, int iCounter, int jCounter)
{
    vector<vector<bool>> pVisited(N, vector<bool>(N, false));
    return DFS(iCounter, jCounter, pMatrix, pVisited);
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

    for (int iCounter = 0; iCounter < nTestCase; ++iCounter)
    {
        int N;
        cin >> N;
        vector<vector<int>> pMatrix(N, vector<int>(N));

        int iSource;
        int jSource;
        for (int jCounter = 0; jCounter < N; ++jCounter) {
            for (int kCounter = 0; kCounter < N; ++kCounter) {
                cin >> pMatrix[jCounter][kCounter];
                if (pMatrix[jCounter][kCounter] == 1)
                {
                    iSource = jCounter;
                    jSource = kCounter;
                }
            }
        }

        if (IsPathExist(pMatrix, N, iSource, jSource))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
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
