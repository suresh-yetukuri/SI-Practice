// JobScheduling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
/*
Given a set of N jobs where each job i has a deadline and profit associated to it. 
Each job takes 1 unit of time to complete and only one job can be scheduled at a time. 
We earn the profit if and only if the job is completed by its deadline. The task is to 
find the maximum profit and the number of jobs done.

Input:
The first line of input contains an integer T denoting the number of test cases. 
Each test case consist of an integer N in first line denoting the number of jobs 
and the next line consist of Job id, Deadline and the Profit associated to that Job.

Output:
Output the number of jobs done and the maximum profit.

Constraints:
1 <= T <= 100
1 <= N <= 100
1 <= Deadline <= 100
1 <= Profit <= 500

Example:
Input:
2
4
1 4 20 2 1 10 3 1 40 4 1 30
5
1 2 100 2 1 19 3 2 27 4 1 25 5 1 15

Output:
2 60
2 127

Explanation:
Testcase 1: 2 jobs can be done with maximum profit of 60.
*/

struct Job
{
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};

void printJobScheduling(Job arr[], int n)
{
    int oMaxDeadline = 0;
    sort(arr, arr + n, [&oMaxDeadline](Job& oFJob, Job& oSJob)->bool {
        oMaxDeadline = max(oMaxDeadline, max(oFJob.dead, oSJob.dead));
        return oFJob.profit > oSJob.profit;
        });

    vector<bool> pAvailableSlots(static_cast<unsigned long>(oMaxDeadline) + 1ull, true);
    int oMaxProfit = 0;
    int oJobCount = 0;
    for (int iCounter = 0; iCounter < n; ++iCounter)
    {
        for (int jCounter = arr[iCounter].dead; jCounter >= 1; --jCounter)
        {
            if (pAvailableSlots[jCounter])
            {
                oMaxProfit += (arr[iCounter].profit);
                ++oJobCount;
                pAvailableSlots[jCounter] = false;
                break;
            }
        }
    }

    cout << oJobCount << " " << oMaxProfit << endl;
}

int main()
{
    int c = 1;
    char k = static_cast<char>(c + 48);
    Job arr[] = { {1, 4, 20}, { 2, 1, 10}, {3, 1, 40}, { 4, 1, 30} };
    int n = 4;
    printJobScheduling(arr, n);
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
