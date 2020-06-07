// BinaryHeapBasics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class MinHeap
{
public:
    MinHeap(int nCapacity)
    { 
        this->nSize = 0;
        resize(nCapacity);
    }

    MinHeap(vector<int>& oInput)
    {
        this->nSize = static_cast<int>(oInput.size());
        this->nCapacity = nSize; 
        this->oContainer.assign(oInput.begin(), oInput.end());
        buildHeap();
    }

    void push(int oInput)
    {
        if (nSize == nCapacity)
            resize(nCapacity << 1);

        ++nSize;
        oContainer[(nSize - 1ull)] = oInput;
        for (int iCounter = (nSize - 1ull); (iCounter > 0) && (oContainer[iCounter] < oContainer[parent(iCounter)]); iCounter = parent(iCounter)) 
            swap(oContainer[iCounter], oContainer[parent(iCounter)]);
    }

    int top()
    {
        if (empty())
            return INT_MAX;

        return oContainer[0];
    }

    void pop()
    {
        if (nSize == 0)
            return;
        else if (nSize == 1)
            --nSize;
        else
        {
            swap(oContainer[0], oContainer[nSize - 1ull]);
            --nSize;
            heapifyI(0);
        }
    }

    int size()
    {
        return nSize;
    }

    bool empty()
    {
        return nSize == 0;
    }

    void decrease(int Idx, int oData)
    {
        if (Idx >= nSize)
            return;

        oContainer[Idx] = oData;
        while (Idx > 0 && oContainer[Idx] < oContainer[parent(Idx)]) {
            swap(oContainer[Idx], oContainer[parent(Idx)]);
            Idx = parent(Idx);
        }
    }

    void Delete(int Idx)
    {
        if (Idx >= nSize)
            return;

        decrease(Idx, INT_MIN);
        pop();
    }

private:
    int left(int oIdx)
    {
        return  (oIdx << 1) + 1;
    }

    int right(int oIdx)
    {
        return  (oIdx << 1) + 2;
    }

    int parent(int oIdx)
    {
        return  (oIdx - 1) >> 1;
    }

    void resize(int nCapacity)
    {
        this->nCapacity = nCapacity;
        this->oContainer.resize(nCapacity);
    }

    void heapify(int oCurrentIdx)
    { 
        if (oCurrentIdx >= nSize)
            return;

        int oLeftIdx = left(oCurrentIdx);
        int oRightIdx = right(oCurrentIdx);
        int oSmallestIdx = oCurrentIdx;
        if ((oLeftIdx < nSize) && (oContainer[oLeftIdx] < oContainer[oSmallestIdx]))
            oSmallestIdx = oLeftIdx;

        if ((oRightIdx < nSize) && (oContainer[oRightIdx] < oContainer[oSmallestIdx]))
            oSmallestIdx = oRightIdx;

        if (oSmallestIdx != oCurrentIdx)
        {
            swap(oContainer[oCurrentIdx], oContainer[oSmallestIdx]);
            heapify(oSmallestIdx);
        }
    }

    void buildHeap()
    {
        for (int iCounter = ((nSize - 2) >> 1); iCounter >= 0; --iCounter)
            heapify(iCounter);
    }

    // Iterative approach of 
    // Heapify (Space Efficient)
    void heapifyI(int Idx)
    {
        for (int oCurrentIdx = Idx; Idx < nSize;)
        {
            int oLeftIdx = left(oCurrentIdx);
            int oRightIdx = right(oCurrentIdx);
            int oSmallestIdx = oCurrentIdx;
            if ((oLeftIdx < nSize) && (oContainer[oLeftIdx] < oContainer[oSmallestIdx]))
                oSmallestIdx = oLeftIdx;

            if ((oRightIdx < nSize) && (oContainer[oRightIdx] < oContainer[oSmallestIdx]))
                oSmallestIdx = oRightIdx;

            if (oSmallestIdx != oCurrentIdx)
            {
                swap(oContainer[oCurrentIdx], oContainer[oSmallestIdx]);
                oCurrentIdx = oSmallestIdx;
            }
            else 
                break;
        }
    }
private:
    int nSize;
    int nCapacity;
    vector<int> oContainer; 
};


namespace HeapSort
{
    namespace Ascending
    {
        class MaxHeap
        {
        public:
            MaxHeap(int nCapacity)
            {
                this->nSize = 0;
                resize(nCapacity);
            }

            MaxHeap(vector<int>& oInput)
            {
                this->nSize = static_cast<int>(oInput.size());
                this->nCapacity = nSize;
                swap(this->oContainer, oInput);
                //this->oContainer.assign(oInput.begin(), oInput.end());
                buildHeap();
            }

            void push(int oInput)
            {
                if (nSize == nCapacity)
                    resize(nCapacity << 1);

                ++nSize;
                oContainer[(nSize - 1ull)] = oInput;
                for (int iCounter = (nSize - 1ull); (iCounter > 0) && (oContainer[iCounter] > oContainer[parent(iCounter)]); iCounter = parent(iCounter))
                    swap(oContainer[iCounter], oContainer[parent(iCounter)]);
            }

            int top()
            {
                if (empty())
                    return INT_MAX;

                return oContainer[0];
            }

            void pop()
            {
                if (nSize == 0)
                    return;
                else if (nSize == 1)
                    --nSize;
                else
                {
                    swap(oContainer[0], oContainer[nSize - 1ull]);
                    --nSize;
                    heapify(0);
                }
            }

            int size()
            {
                return nSize;
            }

            bool empty()
            {
                return nSize == 0;
            }

            void decrease(int Idx, int oData)
            {
                if (Idx >= nSize)
                    return;

                oContainer[Idx] = oData;
                while (Idx > 0 && oContainer[Idx] > oContainer[parent(Idx)]) {
                    swap(oContainer[Idx], oContainer[parent(Idx)]);
                    Idx = parent(Idx);
                }
            }

            void Delete(int Idx)
            {
                if (Idx >= nSize)
                    return;

                decrease(Idx, INT_MAX);
                pop();
            }

            vector<int> sort()
            {
                for (int iCounter = (nSize-1ull); iCounter >= 0; --iCounter)
                {
                    swap(oContainer[0], oContainer[iCounter]);
                    --nSize;
                    heapify(0);
                }
                 
                vector<int> oResultContainer;
                swap(oContainer, oResultContainer);
                return move(oResultContainer);
            }

        private:
            int left(int oIdx)
            {
                return  (oIdx << 1) + 1;
            }

            int right(int oIdx)
            {
                return  (oIdx << 1) + 2;
            }

            int parent(int oIdx)
            {
                return  (oIdx - 1) >> 1;
            }

            void resize(int nCapacity)
            {
                this->nCapacity = nCapacity;
                this->oContainer.resize(nCapacity);
            }

            void heapify(int oCurrentIdx)
            {
                int oLeftIdx = left(oCurrentIdx);
                int oRightIdx = right(oCurrentIdx);
                int oLargestIdx = oCurrentIdx;
                if ((oLeftIdx < nSize) && (oContainer[oLeftIdx] > oContainer[oLargestIdx]))
                    oLargestIdx = oLeftIdx;

                if ((oRightIdx < nSize) && (oContainer[oRightIdx] > oContainer[oLargestIdx]))
                    oLargestIdx = oRightIdx;

                if (oLargestIdx != oCurrentIdx)
                { 
                    swap(oContainer[oCurrentIdx], oContainer[oLargestIdx]);
                    heapify(oLargestIdx);
                }
            }

            void buildHeap()
            {
                for (int iCounter = ((nSize - 2) >> 1); iCounter >= 0; --iCounter)
                    heapify(iCounter);
            }

            // Iterative approach of 
            // Heapify (Space Efficient)
            void heapifyI(int Idx)
            {
                for (int oCurrentIdx = Idx; Idx < nSize;)
                {
                    int oLeftIdx = left(oCurrentIdx);
                    int oRightIdx = right(oCurrentIdx);
                    int oLargestIdx = oCurrentIdx;
                    if ((oLeftIdx < nSize) && (oContainer[oLeftIdx] > oContainer[oLargestIdx]))
                        oLargestIdx = oLeftIdx;

                    if ((oRightIdx < nSize) && (oContainer[oRightIdx] > oContainer[oLargestIdx]))
                        oLargestIdx = oRightIdx;

                    if (oLargestIdx != oCurrentIdx)
                    {
                        swap(oContainer[oCurrentIdx], oContainer[oLargestIdx]);
                        oCurrentIdx = oLargestIdx;
                    }
                    else
                        break;
                }
            }
        private:
            int nSize;
            int nCapacity;
            vector<int> oContainer;
        };
    }
}


int main()
{ 
    auto oLambda = [](const pair<int, int>& oFPair, const pair<int, int>& oSPair)->bool {
        return oFPair.first < oSPair.first;
    };

    //priority_queue<pair<int, int>, vector<pair<int, int>>, bool(*)(const pair<int, int>&, const pair<int, int>&)> oPq(oLambda);
    priority_queue < pair<int, int>, greater<pair<int, int>>> oPq;
    oPq.push(make_pair(1, 2));
    oPq.push(make_pair(3, 2));
    oPq.push(make_pair(5, 2));


    vector<int> oInput{ 10, 5, 20, 2, 4, 8 };
    HeapSort::Ascending::MaxHeap oHeap{ oInput };
    auto oResult = oHeap.sort();
    // oHeap.push(78);
    // oHeap.push(99);
    // oHeap.push(10);
    // cout << oHeap.top() << endl;
    // oHeap.push(54);
    // oHeap.push(13);
    // cout << oHeap.top() << endl;
    // oHeap.push(24);
    // oHeap.push(45);
    // oHeap.push(20);
    while (!oHeap.empty())
    {
        cout << oHeap.top() << endl;
        oHeap.pop();
    }


    std::cout << "Hello World!\n";
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
