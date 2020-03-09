#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


unordered_map<int, string> oMonths;
unordered_map<int, string> oWeeks;

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

void ConvertSectoDay(int n)
{
    Component oYear;
    Date oDate;

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

void FillMonthAndWeek()
{
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

    oWeeks[0] = "Sunday";
    oWeeks[1] = "Monday";
    oWeeks[2] = "Tuesday";
    oWeeks[3] = "Wednesday";
    oWeeks[4] = "Thursday";
    oWeeks[5] = "Friday";
    oWeeks[6] = "Saturday";
}

int main() {
    // Fill Months and Weeks
    FillMonthAndWeek();
    ConvertSectoDay(1e9);

    int oCaseCount = 0;
    cin >> oCaseCount;
    /*for (int iCounter = 1; iCounter <= oCaseCount; ++iCounter)
    {
        int oSeconds = 0;
        cin >> oSeconds;
        ConvertSectoDay(1e9);
    }*/
    return 0;
}
