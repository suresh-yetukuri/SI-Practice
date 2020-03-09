// Basics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

namespace Pattern
{
    void PrintHollowDiamond(int nSize)
    {
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            // Determines the first position where "*" needs to be marked
            const int oMarker = abs((nSize >> 1) - iCounter);

            for (int jCounter = 0; jCounter < nSize; jCounter++)
            {
                if (oMarker == jCounter || abs(nSize - oMarker - 1) == jCounter)
                {
                    cout << "*";
                }
                else {
                    cout << " ";
                }
            }

            cout << endl;
        }
    }

    void PrintRightAngleTriangle(int nSize)
    {
        for (int iCounter = 1; iCounter <= nSize; ++iCounter)
        {
            // Determines the all position where "*" should not be marked
            const int oMarker = nSize - iCounter;
            for (int jCounter = 1; jCounter <= nSize; ++jCounter)
            {
                if (oMarker >= jCounter)
                    cout << " ";
                else
                    cout << "*";
            }

            cout << endl;
        }
    }
}

void SpiralTraversal(int** ppMatrix, int nSize)
{
    int oTraversalCount = nSize >> 1;
    int oMaxIndex = nSize - 1;
    int oMinIndex = 0;

    while (oMinIndex <= oMaxIndex)
    {
        if (oMaxIndex == oMinIndex)
        {
            cout << ppMatrix[nSize >> 1][nSize >> 1];
            break;
        }

        // Top
        for (int rIndex = oMinIndex, cIndex = oMinIndex; cIndex <= oMaxIndex; ++cIndex)
            cout << ppMatrix[rIndex][cIndex] << " ";

        // Right
        for (int rIndex = oMinIndex + 1, cIndex = oMaxIndex; rIndex <= oMaxIndex; ++rIndex)
            cout << ppMatrix[rIndex][cIndex] << " ";

        // Bottom
        for (int rIndex = oMaxIndex, cIndex = oMaxIndex - 1; cIndex >= oMinIndex; --cIndex)
            cout << ppMatrix[rIndex][cIndex] << " ";

        // Left
        for (int rIndex = oMaxIndex - 1, cIndex = oMinIndex; rIndex > oMinIndex; --rIndex)
            cout << ppMatrix[rIndex][cIndex] << " ";

        --oMaxIndex;
        ++oMinIndex;
    }

}

namespace MatrixRotation
{
    void PrintMatrix(int** ppMatrix, int nSize)
    {
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            for (int jCounter = 0; jCounter < nSize; ++jCounter)
                cout << ppMatrix[iCounter][jCounter] << " ";

            cout << endl;
        }
    }

    void RotationMatrix(int** ppMatrix, int nSize)
    {
        int oMaxIndex = nSize - 1;
        int oMinIndex = 0;

        int** ppTempMatrix = new int* [nSize];
        for (int jCounter = 0; jCounter < nSize; ++jCounter)
            ppTempMatrix[jCounter] = new int[nSize];


        while (oMinIndex <= oMaxIndex)
        {
            if (oMaxIndex == oMinIndex)
            {
                int oMiddle = nSize >> 1;
                ppTempMatrix[oMiddle][oMiddle] = ppMatrix[oMiddle][oMiddle];
                break;
            }

            // Top
            for (int rIndex = oMinIndex, cIndex = oMinIndex; cIndex <= oMaxIndex; ++cIndex)
                ppTempMatrix[cIndex][nSize - rIndex - 1] = ppMatrix[rIndex][cIndex];

            // Right
            for (int rIndex = oMinIndex + 1, cIndex = oMaxIndex; rIndex <= oMaxIndex; ++rIndex)
                ppTempMatrix[cIndex][nSize - rIndex - 1] = ppMatrix[rIndex][cIndex];

            // Bottom
            for (int rIndex = oMaxIndex, cIndex = oMaxIndex - 1; cIndex >= oMinIndex; --cIndex)
                ppTempMatrix[cIndex][nSize - rIndex - 1] = ppMatrix[rIndex][cIndex];

            // Left
            for (int rIndex = oMaxIndex - 1, cIndex = oMinIndex; rIndex > oMinIndex; --rIndex)
                ppTempMatrix[cIndex][nSize - rIndex - 1] = ppMatrix[rIndex][cIndex];

            --oMaxIndex;
            ++oMinIndex;
        }

        PrintMatrix(ppTempMatrix, nSize);

        for (int jCounter = 0; jCounter < nSize; ++jCounter) {
            delete[] ppTempMatrix[jCounter];
            ppTempMatrix[jCounter] = nullptr;
        }

        delete[] ppTempMatrix;
        ppTempMatrix = nullptr;
    }

    void Transpose(int** ppMatrix, int nSize)
    {
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            for (int jCounter = iCounter; jCounter < nSize; ++jCounter)
            {
                int oTemp = ppMatrix[iCounter][jCounter];
                ppMatrix[iCounter][jCounter] = ppMatrix[jCounter][iCounter];
                ppMatrix[jCounter][iCounter] = oTemp;
            }
        }
    }

    void RotateNinety(int** ppMatrix, int nSize)
    {
        for (int oRowCounter = 0; oRowCounter < nSize; ++oRowCounter)
        {
            int pCounter = 0; int qCounter = nSize - 1;
            while (pCounter < qCounter)
            {
                int oTemp = ppMatrix[oRowCounter][pCounter];
                ppMatrix[oRowCounter][pCounter] = ppMatrix[oRowCounter][qCounter];
                ppMatrix[oRowCounter][qCounter] = oTemp;
                ++pCounter;
                --qCounter;
            }
        }
    }
}

void DiagonalTraversalOfMatrix(int** ppMatrix, int nSize)
{
    //https://www.youtube.com/watch?v=IDxaZrrggu0
    int oDiagonalCount = (nSize << 1) - 1; // rowCount + ColumnCount - 1

    for (int iCounter = 0; iCounter < nSize; ++iCounter)
    {
        int rIndex = iCounter;
        int cIndex = nSize - 1; // ColumnCount
        int oSum = 0;
        while ((0 <= rIndex) && (0 <= cIndex))
        {
            oSum += ppMatrix[rIndex][cIndex];
            --rIndex;
            --cIndex;
        }

        cout << oSum << " ";
    }

    // Primary diagonal is already considered in above case
    for (int iCounter = nSize - 2; iCounter >= 0; --iCounter)
    {
        int rIndex = nSize - 1;
        int cIndex = iCounter; // ColumnCount
        int oSum = 0;
        while ((0 <= rIndex) && (0 <= cIndex))
        {
            oSum += ppMatrix[rIndex][cIndex];
            --rIndex;
            --cIndex;
        }

        cout << oSum << " ";
    }
}

long long int TrailingZeroEasy(long long int oNum)
{
    long long int oCount = 0;
    while (oNum >= 5)
    {
        oCount += (oNum / 5);
        oNum = oNum / 5;
    }

    return oCount;
}


int CountBits(long long int oNum)
{
    int oCount = 0;
    while (0 != oNum)
    {
        ++oCount;
        oNum = oNum & (oNum - 1);
    }

    return oCount;
}

int FlipBits(long long int oFirst, long long int oSecond)
{
    long long int oResultant = oFirst ^ oSecond;
    return CountBits(oResultant);
}


bool CheckBit(unsigned int oNum, int oPosition)
{
    return ((1u << oPosition) & oNum) != 0;
}

unsigned int FlipBitsAtPosition(unsigned int oNum, int oPosition)
{
    return (1u << oPosition) ^ oNum;
}

unsigned int ReverseBits(unsigned int oNum)
{
    int pCounter = 31;
    int qCounter = 0;

    while (pCounter > qCounter)
    {
        bool IspSet = CheckBit(oNum, pCounter);
        bool IsqSet = CheckBit(oNum, qCounter);

        if (IspSet != IsqSet)
        {
            oNum = FlipBitsAtPosition(oNum, pCounter);
            oNum = FlipBitsAtPosition(oNum, qCounter);
        }

        --pCounter;
        ++qCounter;
    }

    return oNum;
}

unsigned int SwapBits(unsigned int oNum)
{
    short pCounter = 0;
    short qCounter = pCounter + 1;

    while (qCounter <= 31)
    {
        bool IspSet = CheckBit(oNum, pCounter);
        bool IsqSet = CheckBit(oNum, qCounter);

        if (IspSet != IsqSet)
        {
            oNum = FlipBitsAtPosition(oNum, pCounter);
            oNum = FlipBitsAtPosition(oNum, qCounter);
        }

        pCounter = pCounter + 2;
        qCounter = pCounter + 1;
    }

    return oNum;
}

unsigned long long int Compute(unsigned int a, unsigned int b)
{
    unsigned long long int oResult = 1u;
    unsigned long long int pCounter = a;
    const unsigned int oMSBSetBitPos = (unsigned int)log2(b);
    const unsigned int oModulo = (unsigned int)1e9 + 7u;

    for (unsigned int iCounter = 0; iCounter <= oMSBSetBitPos; ++iCounter)
    {
        if (CheckBit(b, iCounter)) {
            oResult = (oResult * pCounter) % oModulo;
        }
        pCounter = (pCounter * pCounter) % oModulo;
    }

    return oResult;
}

void BinaryRepresentation(unsigned int oNum)
{
    if (0 != oNum) {
        char oRepresentation[32];
        short int pCounter = 31;

        while (0 != oNum)
        {
            if ((oNum & 1) == 1)
                oRepresentation[pCounter] = '1';
            else
                oRepresentation[pCounter] = '0';

            oNum = oNum >> 1;
            --pCounter;
        }
        ++pCounter;
        while (pCounter <= 31)
        {
            cout << oRepresentation[pCounter];
            ++pCounter;
        }
    }
    else {
        cout << '0';
    }

    cout << endl;
}

namespace SubsetLexographicalSort
{
    bool IsBitSet(int oNum, int oPos)
    {
        return ((1 << oPos) & oNum) != 0;
    }

    void getSubset(int* pArray, int nSize, int** pSubsetMatrix, int* pSizeArray, int oSubsetCount)
    {

        for (int iCounter = 1; iCounter <= oSubsetCount; ++iCounter)
        {
            int kCounter = 0;
            pSubsetMatrix[iCounter - 1] = new int[nSize];

            for (int jCounter = 0; jCounter < nSize; ++jCounter)
            {
                if (IsBitSet(iCounter, jCounter)) {
                    pSubsetMatrix[iCounter - 1][kCounter] = pArray[jCounter];
                    ++kCounter;
                }
            }

            pSizeArray[iCounter - 1] = kCounter;
        }
    }

    bool LexographicalCheck(int oLeftCounter, int oRightCounter, int** pSubsetMatrix, int* pSizeArray)
    {
        int pLeftSubsetSize = pSizeArray[oLeftCounter];
        int pRightSubsetSize = pSizeArray[oRightCounter];

        int iCounter = 0;
        int jCounter = 0;

        while ((iCounter < pLeftSubsetSize) && (jCounter < pRightSubsetSize))
        {
            if (pSubsetMatrix[oLeftCounter][iCounter] > pSubsetMatrix[oRightCounter][jCounter]) {
                return true;
            }
            else if (pSubsetMatrix[oLeftCounter][iCounter] < pSubsetMatrix[oRightCounter][jCounter]) {
                return false;
            }
            else {
                ++iCounter;
                ++jCounter;
            }
        }

        if (iCounter == pLeftSubsetSize)
            return false;

        if (jCounter == pRightSubsetSize)
            return true;

        return false;
    }

    void Merge(int* pArray, int* pLeftArray, int* pRightArray, int nLeft, int nRight, int** pSubsetMatrix, int* pSizeArray)
    {
        int iCounter = 0;
        int jCounter = 0;
        int kCounter = 0;

        while ((iCounter < nLeft) && (jCounter < nRight))
        {
            if (LexographicalCheck(pLeftArray[iCounter], pRightArray[jCounter], pSubsetMatrix, pSizeArray)) {
                pArray[kCounter] = pRightArray[jCounter];
                ++jCounter;
            }
            else {
                pArray[kCounter] = pLeftArray[iCounter];
                ++iCounter;
            }

            ++kCounter;
        }

        while (iCounter < nLeft)
            pArray[kCounter++] = pLeftArray[iCounter++];

        while (jCounter < nRight)
            pArray[kCounter++] = pRightArray[jCounter++];
    }

    void MergeSort(int* pArray, int nSize, int** pSubsetMatrix, int* pSizeArray)
    {
        if (nSize < 2)
            return;

        int oMid = nSize >> 1;
        int* pLeft = new int[oMid];
        int* pRight = new int[nSize - oMid];

        for (int iCounter = 0; iCounter < oMid; ++iCounter)
            pLeft[iCounter] = pArray[iCounter];

        for (int iCounter = oMid; iCounter < nSize; ++iCounter)
            pRight[iCounter - oMid] = pArray[iCounter];

        MergeSort(pLeft, oMid, pSubsetMatrix, pSizeArray);
        MergeSort(pRight, nSize - oMid, pSubsetMatrix, pSizeArray);
        Merge(pArray, pLeft, pRight, oMid, nSize - oMid, pSubsetMatrix, pSizeArray);
        delete[] pLeft; pLeft = nullptr;
        delete[] pRight; pRight = nullptr;
    }

    void Compute(int* pArray, int nSize)
    {
        sort(pArray, pArray + nSize);
        int oSubsetCount = (1 << nSize) - 1;
        int* pSizeArray = new int[oSubsetCount];
        int** pSubsetMatrix = new int* [oSubsetCount];

        getSubset(pArray, nSize, pSubsetMatrix, pSizeArray, oSubsetCount);

        int* pOrderArray = new int[oSubsetCount];
        for (int iCounter = 0; iCounter < oSubsetCount; ++iCounter)
            pOrderArray[iCounter] = iCounter;

        MergeSort(pOrderArray, oSubsetCount, pSubsetMatrix, pSizeArray);

        for (int iCounter = 0; iCounter < oSubsetCount; ++iCounter)
        {
            for (int jCounter = 0; jCounter < pSizeArray[pOrderArray[iCounter]]; ++jCounter)
            {
                cout << pSubsetMatrix[pOrderArray[iCounter]][jCounter] << " ";
            }

            cout << endl;
        }

        delete[] pOrderArray;
        delete[] pSizeArray;
        pOrderArray = nullptr;
        pSizeArray = nullptr;
        for (int iCounter = 0; iCounter < oSubsetCount; ++iCounter) {
            delete[] pSubsetMatrix[iCounter];
            pSubsetMatrix[iCounter] = nullptr;
        }

        delete[] pSubsetMatrix;
        pSubsetMatrix = nullptr;
    }
}

int CalculateHCF(int a, int b)
{
    if (a == 0)
        return b;
    else if (b == 0)
        return a;
    else if (a > b)
        return CalculateHCF(a % b, b);
    else
        return CalculateHCF(a, b % a);
}

struct Coordinate
{
    int x;
    int y;
};

long long int GetArea(Coordinate b1, Coordinate t1, Coordinate b2, Coordinate t2)
{
    long long int oResultantArea = 0;
    long long int oFirstArea = ((long long int)t1.x - b1.x) * (t1.y - b1.y);
    long long int oSecondArea = ((long long int)t2.x - b2.x) * (t2.y - b2.y);

    // Calculate width and height of overlapping area
    int width = min(t1.x, t2.x) - max(b1.x, b2.x);
    int height = min(t1.y, t2.y) - max(b1.y, b2.y);

    if (width > 0 && height > 0)
    {
        oResultantArea -= ((long long int)width * height);
    }

    oResultantArea += (oFirstArea + oSecondArea);
    return oResultantArea;
}


namespace TOY
{
    int LeapYearBefore(int year)
    {
        return (year / 4) - (year / 100) + (year / 400);
    }

    int getNumberOfLeapYear(int start, int end)
    {
        return LeapYearBefore(end) - LeapYearBefore(start + 1);
    }

    bool IsLeapYear(int year)
    {
        // If a year is multiple of 400,  
        // then it is a leap year  
        if (year % 400 == 0)
            return true;

        // Else If a year is muliplt of 100,  
        // then it is not a leap year  
        if (year % 100 == 0)
            return false;

        // Else If a year is muliplt of 4,  
        // then it is a leap year  
        if (year % 4 == 0)
            return true;

        return false;
    }

    string GetDayOfDate(int year, int month, int day)
    {
        int OddDaysCount = 0;
        int oArray[5] = { 0, 5, 3, 1, 0 };
        int oCYear = year - 1;
        int oCMonth = month - 1;
        unordered_map<int, string> oWeeks;
        oWeeks[0] = "Sunday";
        oWeeks[1] = "Monday";
        oWeeks[2] = "Tuesday";
        oWeeks[3] = "Wednesday";
        oWeeks[4] = "Thursday";
        oWeeks[5] = "Friday";
        oWeeks[6] = "Saturday";

        int iCounter = 4;
        while (oCYear >= (iCounter * 100) && (iCounter > 0))
        {
            oCYear = oCYear % (iCounter * 100);
            OddDaysCount = OddDaysCount + oArray[iCounter];
            iCounter--;
        }

        int oLeapYearCount = getNumberOfLeapYear((year / 100) * 100, ((year / 100) * 100) + oCYear);
        int oNonLeapYearCount = oCYear - oLeapYearCount;
        OddDaysCount = OddDaysCount + (oLeapYearCount * 2);
        OddDaysCount = OddDaysCount + oNonLeapYearCount;

        if (oCMonth > 0) {
            OddDaysCount += 31;
            --oCMonth;
        }

        if (oCMonth > 0) {
            if (IsLeapYear(year)) {
                OddDaysCount += 29;
            }
            else {
                OddDaysCount += 28;
            }
            --oCMonth;
        }

        if (oCMonth > 0) {
            int jCounter = 3;
            while (oCMonth > 0)
            {
                OddDaysCount = OddDaysCount + 30 + (jCounter % 2);
                ++jCounter;
                --oCMonth;
            }
        }

        OddDaysCount = OddDaysCount + day;
        return oWeeks[OddDaysCount % 7];
    }

    struct Component
    {
        int years;
        int months;
        int days;
    };

    struct Date
    {
        int Year;
        int Month;
        int Day;
        string WeekDay;
    };




    void ConvertSectoDay(int n)
    {
        Component oYear;
        Date oDate;

        unordered_map<int, string> oMonths;
        oMonths[1] = "JAN";
        oMonths[2] = "FEB";
        oMonths[3] = "MAR";
        oMonths[4] = "APR";
        oMonths[5] = "MAY";
        oMonths[6] = "JUN";
        oMonths[7] = "JUL";
        oMonths[8] = "AUG";
        oMonths[9] = "SEP";
        oMonths[10] = "OCT";
        oMonths[11] = "NOV";
        oMonths[12] = "DEC";

        oYear.days = n / (24 * 3600);
        oYear.years = oYear.days / 365;
        oYear.days = oYear.days % 365;

        int oLeapYearCount = getNumberOfLeapYear(1970, 1970 + oYear.years);
        oYear.days -= oLeapYearCount;

        oDate.Year = 1970 + oYear.years;

        int oMonthCounter = 0;
        if (IsLeapYear(oDate.Year)) {
            oYear.days += 1;

            if (oYear.days >= 31) {
                oYear.days -= 31;
                ++oMonthCounter;

                if (oYear.days >= 29) {
                    oYear.days -= 29;
                    ++oMonthCounter;
                }
            }
        }
        else {
            if (oYear.days >= 31) {
                oYear.days -= 31;
                ++oMonthCounter;

                if (oYear.days >= 28) {
                    oYear.days -= 28;
                    ++oMonthCounter;
                }
            }
        }

        if (oMonthCounter == 2) {
            int iCounter = 3;
            while (oYear.days >= 31)
            {
                oYear.days -= (30) + (iCounter % 2);
                ++iCounter;
                ++oMonthCounter;
            }
        }

        oDate.Month = oMonthCounter + 1;
        oDate.Day = oYear.days + 1;
        oDate.WeekDay = GetDayOfDate(oDate.Year, oDate.Month, oDate.Day);
        if (oDate.Day < 10)
            cout << "0";

        cout << oDate.Day << "-" << oMonths[oDate.Month] << "-" << oDate.Year << " " << oDate.WeekDay << endl;
    }
}

int main()
{
    TOY::ConvertSectoDay(24 * 3601);
    TOY::ConvertSectoDay(86400);
    TOY::ConvertSectoDay(2592000);
    TOY::ConvertSectoDay(2678400);
    TOY::ConvertSectoDay(8639999);
    TOY::ConvertSectoDay(8640000);
    TOY::ConvertSectoDay(31535999);
    TOY::ConvertSectoDay(31536000);
    TOY::ConvertSectoDay(68169599);
    TOY::ConvertSectoDay(68169600);




    TOY::ConvertSectoDay(static_cast<int>(1e9));
    cout << GetArea({ 2, 5 }, { 4, 6 }, { 1, 2 }, { 5, 4 }) << endl;
    cout << GetArea({ -4, -3 }, { -2, 5 }, { -3, -5 }, { 1, 3 }) << endl;
    cout << GetArea({ 1, 0 }, { 3, 5 }, { 2, 3 }, { 5, 8 }) << endl;
    cout << GetArea({ -2, 2 }, { 4, 4 }, { -3, 1 }, { 5, 5 }) << endl;






    long long int HCF = CalculateHCF(605904, 996510762);
    cout << "HCF: " << HCF << " LCM: " << (996510762ll * 605904) / HCF << endl;



    int pArray[3] = { 5, 15, 3 };
    SubsetLexographicalSort::Compute(pArray, 3);



    BinaryRepresentation(10u);
    BinaryRepresentation(15u);
    BinaryRepresentation(7u);
    BinaryRepresentation(1u);
    BinaryRepresentation(120u);

    //int pArray[5] = { 1, 4, 2,6,3 };
    sort(pArray, pArray + 5);


    cout << Compute(5u, 2u) << endl;
    cout << Compute(1u, 10u) << endl;
    cout << Compute(2u, 30u) << endl;
    cout << Compute(10u, 10u) << endl;
    cout << SwapBits(10u) << endl;
    cout << SwapBits(7u) << endl;
    cout << SwapBits(43u) << endl;
    cout << SwapBits(100u) << endl;



    cout << FlipBits(20, 10) << endl;
    cout << FlipBits(16, 8) << endl;
    cout << FlipBits(1, 153) << endl;
    cout << FlipBits(549, 24) << endl;



    cout << TrailingZeroEasy(100);
    cout << TrailingZeroEasy(25);
    int oCaseCount = 0;
    cin >> oCaseCount;
    for (int iCounter = 1; iCounter <= oCaseCount; ++iCounter)
    {
        int nSize = 0;
        cin >> nSize;
        int** ppMatrix = new int* [nSize];
        for (int jCounter = 0; jCounter < nSize; ++jCounter)
            ppMatrix[jCounter] = new int[nSize];

        for (int jCounter = 0; jCounter < nSize; ++jCounter)
        {
            for (int kCounter = 0; kCounter < nSize; ++kCounter)
                cin >> ppMatrix[jCounter][kCounter];
        }

        DiagonalTraversalOfMatrix(ppMatrix, nSize);

        for (int jCounter = 0; jCounter < nSize; ++jCounter) {
            delete[] ppMatrix[jCounter];
            ppMatrix[jCounter] = nullptr;
        }

        delete[] ppMatrix;
        ppMatrix = nullptr;
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
