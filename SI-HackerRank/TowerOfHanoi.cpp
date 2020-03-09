// TowerOfHanoi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


/*
TC: 2^N + 2^N -1
SC: 1
*/
void TowerOfHanoi(int oDiskCount, char oSource, char oTemp, char oDestination)
{
    if (oDiskCount == 0)
        return;

    TowerOfHanoi(oDiskCount - 1, oSource, oDestination, oTemp);
    cout << "Move " << oDiskCount << " from " << oSource << " to " << oDestination << endl;
    TowerOfHanoi(oDiskCount - 1, oTemp, oSource, oDestination);
}



int main()
{
    cout << (1 << 3) - 1; // Minimum No of Mover 2^n -1
    TowerOfHanoi(3, 'A', 'B', 'C');
    return 0;
}