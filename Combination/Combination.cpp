// Combination.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


void Combination(string& oTarget, int Idx, int K, string& oCurrent, vector<string>& oResult)
{
    if (oCurrent.size() == K) {
        oResult.push_back(oCurrent);
        return;
    }

    for (int iCounter = Idx; iCounter < oTarget.size(); ++iCounter)
    {
        oCurrent.push_back(oTarget[iCounter]);
        Combination(oTarget, iCounter + 1, K, oCurrent, oResult);
        oCurrent.pop_back();
    }
}

void Combinations(vector<int>& oTasks, int Idx, int K, vector<int>& oPartition, vector<vector<int>>& oResult)
{
    if (oPartition.size() == K) {
        oResult.push_back(oPartition);
        return;
    }

    for (int iCounter = Idx; iCounter < oTasks.size(); ++iCounter)
    {
        oPartition.push_back(iCounter);
        Combinations(oTasks, iCounter + 1, K, oPartition, oResult);
        oPartition.pop_back();
    }
}



int main()
{
    string a = "abcdefg";
    string oCurrent;
    //vector<string> oResult;
    int K = 2;

    vector<int> oPartition;
    vector<vector<int>> oResult;
    vector<int> oTasks;
    oTasks.push_back(0);
    oTasks.push_back(1);
    oTasks.push_back(2); 
    oTasks.push_back(3);
    oTasks.push_back(4);
    oTasks.push_back(5);
    oTasks.push_back(6);



    Combinations(oTasks, 0, K, oPartition, oResult);
    //Combination(a, 0, K, oCurrent, oResult);

    for_each(oResult.begin(), oResult.end(), [](vector<int> a)->void {
        for_each(a.begin(), a.end(), [](int a)->void {
            cout << a << " ";
            });
        cout << endl;
    });

    return 0;
}
