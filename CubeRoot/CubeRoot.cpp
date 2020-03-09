// CubeRoot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

// As per the C++ datatypes
// Extreme cube root that is possible is for 10^18 i.e 10^6

namespace PerfectCube
{
    /*
     N^(1/3), 1
    */
    namespace BruteForce
    {
        long long int CubeRoot(long long int K)
        {
            const int oMaxCubeRoot = static_cast<int>(1e6);

            for (long long int iCounter = 0; iCounter <= oMaxCubeRoot; ++iCounter)
            {
                long long int oCurrentCubeRoot = iCounter * iCounter * iCounter;
                if (oCurrentCubeRoot == K)
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
        long long int CubeRoot(long long int K)
        {
            long long int Low = 0;
            long long int High = static_cast<long long int>(1e6);

            while (Low <= High)
            {
                long long int Mid = Low + ((High - Low) >> 1);
                long long int oCurrentCubeRoot = Mid * Mid * Mid;

                if (oCurrentCubeRoot < K)
                    Low = Mid + 1;
                else if (oCurrentCubeRoot > K)
                    High = Mid - 1;
                else
                    return Mid;
            }

            return -1;
        }
    }
}

namespace NonPerfectCube
{
    /*
     N^(1/3), 1
    */
    namespace BruteForce
    {
        long long int CubeRoot(long long int K)
        {
            const int oMaxCubeRoot = static_cast<int>(1e6);

            for (long long int iCounter = 0; iCounter <= oMaxCubeRoot; ++iCounter)
            {
                long long int oCurrentCubeRoot = iCounter * iCounter * iCounter;
                if (oCurrentCubeRoot == K)
                    return iCounter;

                if (oCurrentCubeRoot > K)
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
        long long int CubeRoot(long long int K)
        {
            long long int Low = 0;
            long long int High = static_cast<long long int>(1e6);

            while (Low < High)
            {
                long long int Mid = Low + ((High - Low + 1) >> 1);
                long long int oCurrentCubeRoot = Mid * Mid * Mid;

                if (oCurrentCubeRoot <= K)
                    Low = Mid;
                else if (oCurrentCubeRoot > K)
                    High = Mid - 1;
            }

            return Low;
        }
    }
}

int main()
{
    
    cout << PerfectCube::BruteForce::CubeRoot(625) << endl;
    cout << PerfectCube::BruteForce::CubeRoot(500) << endl;

    cout << PerfectCube::BinarySearch::CubeRoot(625) << endl;
    cout << PerfectCube::BinarySearch::CubeRoot(500) << endl;

    cout << NonPerfectCube::BruteForce::CubeRoot(625) << endl;
    cout << NonPerfectCube::BruteForce::CubeRoot(500) << endl;

    cout << NonPerfectCube::BinarySearch::CubeRoot(625) << endl;
    cout << NonPerfectCube::BinarySearch::CubeRoot(500) << endl;
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
