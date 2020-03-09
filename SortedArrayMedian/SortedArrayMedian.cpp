// SortedArrayMedian.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Given Two Sorted Arrays of Sizes N & M, Find Median of Combined Sorted Arrays 
*/

/*
// Approach: 1
1. Create Temp Array[N+M]
2. Copy Elements of both arrays in Temp
3. Sort It
4. Then simply find median

(N+M) + (N+M)Log(N+M), 2(N+M) 
*/


/*
// Approach: 2
1. Create Temp Array[N+M]
2. Use Merge alogorithm to merge two sorted array in sorted manner
3. Then simply find median

N+M, N+M
*/

/*
// Approach: 3
   Two Pointer Technique

N+M, N+M
*/
namespace UsingPointerTechnique
{
    int FindMedian(int* pLeft, int* pRight, int nLeft, int nRight)
    {
        int pCounter = 0;
        int qCounter = 0;
        int High = (nLeft + nRight) - 1;
        int Low = 0;
        int MedianCounter = Low + ((High - Low + 1) >> 1); // UpperMid
        int LowerMedian = INT_MIN;
        int UpperMedian = INT_MIN;

        while (MedianCounter != -1 && pCounter < nLeft && qCounter < nRight)
        {
            if (pLeft[pCounter] > pRight[qCounter])
            {
                LowerMedian = UpperMedian;
                UpperMedian = pRight[qCounter];
                ++qCounter;
                --MedianCounter;
            }
            else
            {
                LowerMedian = UpperMedian;
                UpperMedian = pLeft[pCounter];
                ++pCounter;
                --MedianCounter;
            }
        }

        while (MedianCounter != -1 && pCounter < nLeft)
        {
            LowerMedian = UpperMedian;
            UpperMedian = pLeft[pCounter];
            ++pCounter;
            --MedianCounter;
        }

        while (MedianCounter != -1 && qCounter < nRight)
        {
            LowerMedian = UpperMedian;
            UpperMedian = pRight[qCounter];
            ++qCounter;
            --MedianCounter;
        }


        if ((nLeft + nRight) & 1)
            return UpperMedian;

        return (LowerMedian + UpperMedian) >> 1;
    }
}

/*

Log(Max(A[N-1], B[M-1]) - Min(A[0], B[0]) * (LogM + LogN), 1
This will work only if duplicates are not there
*/
namespace UsingBinarySearch
{
    namespace FloorMedian
    {
        /*
        Get Index of RightMost element which is Lesser than kVal
        */
        int FindFloor(int* pArray, int nSize, int kVal)
        {
            int Low = 0;
            int High = nSize - 1;

            while (Low < High)
            {
                int Mid = Low + ((High - Low + 1) >> 1);
                if (pArray[Mid] >= kVal)
                    High = Mid - 1;
                else
                    Low = Mid;
            }

            if (pArray[Low] < kVal)
                return Low;

            return -1;
        }
         
        /*
        Get Index of LeftMost element which is Greater than kVal
        */
        int FindCeil(int* pArray, int nSize, int kVal)
        {
            int Low = 0;
            int High = nSize - 1;

            while (Low < High)
            {
                int Mid = Low + ((High - Low) >> 1);
                if (pArray[Mid] <= kVal)
                    Low = Mid + 1;
                else
                    High = Mid;
            }

            if (pArray[Low] > kVal)
                return Low;

            return nSize; 
        }

        int FindMedian(int* pLeft, int* pRight, int nLeft, int nRight)
        {
            int Low = min(pLeft[0], pRight[0]);
            int High = max(pLeft[nLeft - 1], pRight[nRight - 1]);

            while (Low <= High)
            {
                int Mid = Low + ((High - Low) >> 1);
                int LesserLeft = FindFloor(pLeft, nLeft, Mid) + 1;
                int LesserRight = FindFloor(pRight, nRight, Mid) + 1;
                int GreaterLeft = nLeft - FindCeil(pLeft, nLeft, Mid);;
                int GreaterRight = nRight - FindCeil(pRight, nRight, Mid);;

                int LesserElementCount = LesserLeft + LesserRight;
                int GreaterElementCount = GreaterLeft + GreaterRight;

                if (LesserElementCount == GreaterElementCount)
                    return Mid;
                else if (LesserElementCount < GreaterElementCount)
                    Low = Mid + 1;
                else
                    High = Mid - 1;
            }

            return -1;
        }
    }
    
    namespace DecimalMedian
    {
        /*
        Get Index of RightMost element which is Lesser than kVal
        */
        int FindFloor(int* pArray, int nSize, int kVal)
        {
            int Low = 0;
            int High = nSize - 1;

            while (Low < High)
            {
                int Mid = Low + ((High - Low + 1) >> 1);
                if (pArray[Mid] >= kVal)
                    High = Mid - 1;
                else
                    Low = Mid;
            }

            if(pArray[Low] < kVal)
                return Low;

            return -1;
        }

        /*
        Get Index of LeftMost element which is Greater than kVal
        */
        int FindCeil(int* pArray, int nSize, int kVal)
        {
            int Low = 0;
            int High = nSize - 1;

            while (Low < High)
            {
                int Mid = Low + ((High - Low) >> 1);
                if (pArray[Mid] <= kVal)
                    Low = Mid + 1;
                else
                    High = Mid;
            }

            if (pArray[Low] > kVal)
                return Low;

            return nSize;
        }

        double FindMedian(int* pLeft, int* pRight, int nLeft, int nRight)
        {
            int Low = min(pLeft[0], pRight[0]);
            int High = max(pLeft[nLeft - 1], pRight[nRight - 1]);

            while (Low <= High)
            {
                int Mid = Low + ((High - Low) >> 1);
                int LesserLeft = FindFloor(pLeft, nLeft, Mid) + 1;
                int LesserRight = FindFloor(pRight, nRight, Mid) + 1;
                int GreaterLeft = nLeft - FindCeil(pLeft, nLeft, Mid);;
                int GreaterRight = nRight - FindCeil(pRight, nRight, Mid);;

                int LesserElementCount = LesserLeft + LesserRight;
                int GreaterElementCount = GreaterLeft + GreaterRight;

                if (LesserElementCount == GreaterElementCount)
                    return (static_cast<double>(High) + Low)/2.0;
                else if (LesserElementCount < GreaterElementCount)
                    Low = Mid + 1;
                else
                    High = Mid - 1;
            }

            return -1;
        }
    }
}


int main()
{
    vector<int> o;
    o.push_back(1);
    o.push_back(2);
    o.push_back(3);
    o.resize(5);
    /*int Left[] = { 2, 3, 5, 8 };
    int Right[] = { 11, 12, 14, 16, 18, 20 }; */
    int Left[] = { 1, 2, 4, 5 };
    int Right[] = { 2, 3 };
   /* int Left[] = { 4, 8, 9, 12 };
    int Right[] = { 7, 11, 13, 14 };*/
    int nLeft = 4;
    int nRight = 2;
    cout << UsingBinarySearch::FloorMedian::FindMedian(Left, Right, nLeft, nRight) << endl;
    cout << UsingBinarySearch::DecimalMedian::FindMedian(Left, Right, nLeft, nRight) << endl;
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
