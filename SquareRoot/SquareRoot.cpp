// SquareRoot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


namespace PerfectSquare
{
    /*
     N^(1/2), 1
    */
    namespace BruteForce
    {
        int SquareRoot(int K)
        {
            for (int iCounter = 0; iCounter <= K; ++iCounter)
            {
                if ((static_cast<long long int>(iCounter)* iCounter) == K)
                    return iCounter;
            }

            return -1;
        } 
    }

    /*
    LogN, 1
    */
    namespace BinarySearch
    {
        int SquareRoot(int K)
        {
            int Low = 0;
            int High = K;

            while (Low <= High)
            {
                int Mid = Low + ((High - Low) >> 1);
                long long int oSquare = static_cast<long long int>(Mid)* Mid;

                if (oSquare < K)
                    Low = Mid + 1;
                else if (oSquare > K)
                    High = Mid - 1;
                else
                    return Mid;
            }

            return -1;
        }
    }
}

namespace NonPerfectSquare
{
    /*
     N^(1/2), 1
    */
    namespace BruteForce
    {
        int SquareRoot(int K)
        {
            for (int iCounter = 0; iCounter <= K; ++iCounter)
            {
                long long int oSquare = static_cast<long long int>(iCounter)* iCounter;
                if (oSquare == K)
                    return iCounter;

                if (oSquare > K)
                    return iCounter - 1;
            }

            return -1;
        }
    }

    /*
    LogN, 1
    */
    namespace BinarySearch
    { 
        int SquareRoot(int K)
        {
            long long int Low = 0;
            long long int High = K;
            // Why do we need long long int for Mid. This is because if K = INT_MAX, then expression for
            // calculation of Mid would overflow
            while (Low < High)
            {
                long long int Mid = Low + ((static_cast<long long int>(High) - Low + 1) >> 1);
                long long int oSquare = Mid*Mid;

                if (oSquare <= K)
                    Low = Mid;
                else if (oSquare > K)
                    High = Mid - 1;
            }

            return static_cast<int>(Low);
        }
    }
}


int main()
{ 
     
    cout << NonPerfectSquare::BinarySearch::SquareRoot(2147483647) << endl;
    cout << NonPerfectSquare::BinarySearch::SquareRoot(24)<<endl;
    cout << NonPerfectSquare::BinarySearch::SquareRoot(25)<<endl;
    cout << NonPerfectSquare::BinarySearch::SquareRoot(40)<<endl;
    cout << NonPerfectSquare::BinarySearch::SquareRoot((int)1e9)<<endl;
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
