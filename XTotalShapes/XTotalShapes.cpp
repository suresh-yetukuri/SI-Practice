// XTotalShapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <queue>
using namespace std;


bool IsValidMark(int row, int col, int N, int M, vector<vector<char>>& pMatrix, vector<vector<bool>>& pVisited)
{
    if ((row >= 0 && row < N)
        && (col >= 0 && col < M)
        && (pMatrix[row][col] == 'X')
        && (pVisited[row][col] == false))
    {
        return true;
    }

    return false;
}


void BFS(int row, int col, int N, int M, vector<vector<char>>& pMatrix, vector<vector<bool>>& pVisited)
{
    int rowCounter[] = { -1, 0, 0, 1 };
    int colCounter[] = { 0,-1, 1, 0 };

    queue<pair<int, int>> pQueue;
    pQueue.push(make_pair(row, col));
    pVisited[row][col] = true;

    while (!pQueue.empty())
    {
        auto oCurrPair = pQueue.front();
        pQueue.pop();
        row = oCurrPair.first;
        col = oCurrPair.second;

        for (int kCounter = 0; kCounter < 4; ++kCounter)
        {
            int r = row + rowCounter[kCounter];
            int c = col + colCounter[kCounter];
            if (IsValidMark(r, c, N, M, pMatrix, pVisited)) {
                pVisited[r][c] = true;
                pQueue.push(make_pair(r, c));
            }
        }
    }
}

int main()
{
    rsize_t
    int nTestCase = 0;
    cin >> nTestCase;
    for (int kCounter = 0; kCounter < nTestCase; ++kCounter)
    {
        int N, M;
        cin >> N;
        cin >> M;

        vector<vector<char>> pMatrix(N, vector<char>(M, '\0'));
        for (int iCounter = 0; iCounter < N; ++iCounter)
            for (int jCounter = 0; jCounter < M; ++jCounter)
                cin >> pMatrix[iCounter][jCounter];

        int oGroupCount = 0;
        vector<vector<bool>> pVisited(N, vector<bool>(M, false));

        for (int iCounter = 0; iCounter < N; ++iCounter)
        {
            for (int jCounter = 0; jCounter < M; ++jCounter)
            {
                if (pMatrix[iCounter][jCounter] == 'X' && pVisited[iCounter][jCounter]) {
                    BFS(iCounter, jCounter, N, M, pMatrix, pVisited);
                    oGroupCount++;
                }
            }
        }

        cout << oGroupCount << endl;
    }

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
