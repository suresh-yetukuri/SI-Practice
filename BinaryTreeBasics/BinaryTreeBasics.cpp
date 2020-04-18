// BinaryTreeBasics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <math.h>
using namespace std;

class Node
{
public:
    int Data;
    Node* pLeft;
    Node* pRight;
    Node(int val)
    {
        this->Data = val;
        this->pLeft = nullptr;
        this->pRight = nullptr;
    }
};

Node* Insert(Node* pRoot, int Data)
{
    if (nullptr == pRoot)
        pRoot = new Node(Data);
    else 
    {
        if (pRoot->Data < Data)
            pRoot->pRight = Insert(pRoot->pRight, Data);
        else
            pRoot->pLeft = Insert(pRoot->pLeft, Data);
    }

    return pRoot;
}

Node* BuildTree(vector<int>& oInput)
{
    Node* pRoot = nullptr;
    for (auto& val : oInput)
        pRoot = Insert(pRoot, val);

    return pRoot;
}

int GetHeight(Node* pRoot)
{
    if (nullptr == pRoot)
        return -1;

    return 1 + max(GetHeight(pRoot->pLeft), GetHeight(pRoot->pRight));
}

int GetMax(Node* pRoot)
{
    if (nullptr == pRoot)
        return INT_MIN;

    return max(pRoot->Data, max(GetMax(pRoot->pLeft), GetMax(pRoot->pRight)));
}

int GetSize(Node* pRoot)
{
    if (nullptr == pRoot)
        return 0;

    return 1 + GetSize(pRoot->pLeft) + GetSize(pRoot->pRight);
}

namespace Traversals
{
    namespace DepthFirst
    {
        void Preorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                pStack.push(pRoot);
                while (!pStack.empty())
                {
                    Node* pCurrent = pStack.top();
                    pStack.pop();

                    if (nullptr != pCurrent->pRight)
                        pStack.push(pCurrent->pRight);

                    if (nullptr != pCurrent->pLeft)
                        pStack.push(pCurrent->pLeft);

                    cout << pCurrent->Data << " ";
                }
            }
        }

        void Inorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                while ((nullptr != pRoot) || (!pStack.empty()))
                {
                    while (nullptr != pRoot)
                    {
                        pStack.push(pRoot);
                        pRoot = pRoot->pLeft;
                    }

                    Node* pCurrent = pStack.top();
                    pStack.pop();
                    cout << pCurrent->Data << " ";
                    if (nullptr != pCurrent->pRight)
                        pRoot = pCurrent->pRight;
                }
            }
        }

        void Postorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                Node* pLastProcessedNode = nullptr;
                while ((nullptr != pRoot) || (!pStack.empty()))
                {
                    while (nullptr != pRoot)
                    {
                        pStack.push(pRoot);
                        pRoot = pRoot->pLeft;
                    }

                    Node* pCurrent = pStack.top();
                    if (nullptr != pCurrent->pRight && pLastProcessedNode != pCurrent->pRight)
                        pRoot = pCurrent->pRight;
                    else {
                        cout << pCurrent->Data << " ";
                        pLastProcessedNode = pCurrent;
                        pStack.pop();
                    }
                }
            }
        }
    }

    namespace BreadthFirst
    {
        void Levelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                pQueue.push(pRoot);
                pQueue.push(nullptr); // act as a marker
                while (pQueue.size() > 1)
                {
                    Node* pCurrent = pQueue.front();
                    pQueue.pop();
                    if (nullptr == pCurrent)
                    {
                        cout << endl;
                        pQueue.push(nullptr);
                        continue;
                    }
                    cout << pCurrent->Data << " ";
                    if (nullptr != pCurrent->pLeft)
                        pQueue.push(pCurrent->pLeft);

                    if (nullptr != pCurrent->pRight)
                        pQueue.push(pCurrent->pRight);
                } 
            }
        }

        void LevelorderII(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                pQueue.push(pRoot);
                while (!pQueue.empty())
                {
                    int nSize = static_cast<int>(pQueue.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pQueue.front();
                        pQueue.pop();
                        cout << pCurrent->Data << " ";
                        if (nullptr != pCurrent->pLeft)
                            pQueue.push(pCurrent->pLeft);

                        if (nullptr != pCurrent->pRight)
                            pQueue.push(pCurrent->pRight);
                    }

                    cout << endl;
                }
            }
        }

        void ZigZagLevelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pProcessStack;
                stack<Node*> pStack;
                pProcessStack.push(pRoot);
                bool IsLRPush = false;          // For reverse ZigZagLevelorder, set IsLRPush = true;
                while (!pProcessStack.empty())
                {
                    int nSize = static_cast<int>(pProcessStack.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pProcessStack.top();
                        pProcessStack.pop();
                        cout << pCurrent->Data << " ";
                        if (IsLRPush) {
                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);

                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);
                        }
                        else 
                        {  
                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);

                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);
                        }
                    }
                    swap(pProcessStack, pStack);
                    IsLRPush = !IsLRPush;
                }
            }
        }

        void BottomUpLevelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                stack<int> pStack;
                pQueue.push(pRoot);
                while (!pQueue.empty())
                {
                    int nSize = static_cast<int>(pQueue.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pQueue.front();
                        pQueue.pop();
                        pStack.push(pCurrent->Data);
                        if (nullptr != pCurrent->pRight)
                            pQueue.push(pCurrent->pRight);

                        if (nullptr != pCurrent->pLeft)
                            pQueue.push(pCurrent->pLeft);
                    }
                    pStack.push(INT_MIN);
                }
                pStack.pop();
                while (!pStack.empty())
                {
                    int oData = pStack.top();
                    pStack.pop();
                    if (oData == INT_MIN) {
                        cout << endl;
                        continue;
                    }
                    cout << oData << " ";
                }
            }
        }

        void ZigZagBottomUpLevelorder(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                stack<Node*> pProcessStack;
                stack<Node*> pStack;
                stack<int> pFinalStack;
                pProcessStack.push(pRoot);
                bool IsLRPush = true;
                while (!pProcessStack.empty())
                {
                    int nSize = static_cast<int>(pProcessStack.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pProcessStack.top();
                        pProcessStack.pop();
                        pFinalStack.push(pCurrent->Data);
                        if (IsLRPush) {
                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);

                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);
                        }
                        else
                        {
                            if (nullptr != pCurrent->pRight)
                                pStack.push(pCurrent->pRight);

                            if (nullptr != pCurrent->pLeft)
                                pStack.push(pCurrent->pLeft);
                        }
                    }
                    swap(pProcessStack, pStack);
                    IsLRPush = !IsLRPush;
                }

                while (!pFinalStack.empty())
                {
                    cout << pFinalStack.top() << " ";
                    pFinalStack.pop();
                }
            }
        }
    }

    /*
    This won't give correct sequetial order
    we have to do level order traversal to get correct order
    */
    void VerticalLevelOrder(Node* pRoot, int oDepth, unordered_map<int, vector<int>>& oResult, int& oMinDepth, int& oMaxDepth)
    {
        if (nullptr == pRoot)
            return;
        
        oMinDepth = min(oDepth, oMinDepth);
        oMaxDepth = max(oDepth, oMaxDepth);
        VerticalLevelOrder(pRoot->pLeft, oDepth - 1, oResult, oMinDepth, oMaxDepth);
        oResult[oDepth].push_back(pRoot->Data);
        VerticalLevelOrder(pRoot->pRight, oDepth + 1, oResult, oMinDepth, oMaxDepth);
    }

    void VerticalLevelOrderSq(Node* pRoot)
    {
        unordered_map<int, vector<int>> oHashMap;
        int oMaxDepth = INT_MIN;
        int oMinDepth = INT_MAX;
        if (nullptr != pRoot)
        {
            queue<pair<Node*, int>> pQueue;
            pQueue.push(make_pair(pRoot, 0));
            while (!pQueue.empty())
            {
                auto pCurrent = pQueue.front();
                pQueue.pop();
                oHashMap[pCurrent.second].push_back(pCurrent.first->Data);
                oMaxDepth = max(oMaxDepth, pCurrent.second);
                oMinDepth = min(oMinDepth, pCurrent.second);

                if (nullptr != pCurrent.first->pLeft)
                    pQueue.push(make_pair(pCurrent.first->pLeft, pCurrent.second - 1));

                if (nullptr != pCurrent.first->pRight)
                    pQueue.push(make_pair(pCurrent.first->pRight, pCurrent.second + 1));
            }
        }

        for (int iCounter = oMinDepth; iCounter <= oMaxDepth; ++iCounter)
        {
            for (auto& oData : oHashMap[iCounter])
                cout << oData << " ";

            cout << endl;
        }
    }
}

namespace Views
{
    namespace LeftView
    {
        void Recursive(Node* pRoot, int oCurrentLevel, int& oMaxLevel)
        {
            if (nullptr == pRoot)
                return;

            if (oMaxLevel < oCurrentLevel)
            {
                cout << pRoot->Data << " ";
                oMaxLevel = oCurrentLevel;
            }

            Recursive(pRoot->pLeft, oCurrentLevel + 1, oMaxLevel);
            Recursive(pRoot->pRight, oCurrentLevel + 1, oMaxLevel);
        }

        void Iterative(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                pQueue.push(pRoot);
                while (!pQueue.empty())
                {
                    int nSize = static_cast<int>(pQueue.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pQueue.front();
                        pQueue.pop();
                        if(0 == iCounter)
                            cout << pCurrent->Data << " ";

                        if (nullptr != pCurrent->pLeft)
                            pQueue.push(pCurrent->pLeft);

                        if (nullptr != pCurrent->pRight)
                            pQueue.push(pCurrent->pRight);
                    }
                }
            }
        }
    }

    namespace RightView
    {
        void Recursive(Node* pRoot, int oCurrentLevel, int& oMaxLevel)
        {
            if (nullptr == pRoot)
                return;

            if (oMaxLevel < oCurrentLevel)
            {
                cout << pRoot->Data << " ";
                oMaxLevel = oCurrentLevel;
            }

            Recursive(pRoot->pRight, oCurrentLevel + 1, oMaxLevel);
            Recursive(pRoot->pLeft, oCurrentLevel + 1, oMaxLevel);
        }

        void Iterative(Node* pRoot)
        {
            if (nullptr != pRoot)
            {
                queue<Node*> pQueue;
                pQueue.push(pRoot);
                while (!pQueue.empty())
                {
                    int nSize = static_cast<int>(pQueue.size());
                    for (int iCounter = 0; iCounter < nSize; ++iCounter)
                    {
                        Node* pCurrent = pQueue.front();
                        pQueue.pop();
                        if (0 == iCounter)
                            cout << pCurrent->Data << " ";

                        if (nullptr != pCurrent->pRight)
                            pQueue.push(pCurrent->pRight);

                        if (nullptr != pCurrent->pLeft)
                            pQueue.push(pCurrent->pLeft); 
                    }
                }
            }
        }
    }
}

Node* DeleteTree(Node* pRoot)
{ 
    if (nullptr != pRoot)
    {
        if (nullptr != pRoot->pLeft)
            pRoot->pLeft = DeleteTree(pRoot->pLeft);

        if (nullptr != pRoot->pRight)
            pRoot->pRight = DeleteTree(pRoot->pRight);

        delete(pRoot);
        pRoot = nullptr;
    }
    return pRoot;
}


namespace Problems
{
    bool IsChildrenSumProperty(Node* pRoot)
    {
        if (nullptr == pRoot)
            return true;

        if ((nullptr == pRoot->pLeft) && (nullptr == pRoot->pRight))
            return true;

        int oSum = 0;
        if (nullptr != pRoot->pLeft) { oSum += pRoot->pLeft->Data; } 
        if (nullptr != pRoot->pRight) { oSum += pRoot->pRight->Data; }

        return (pRoot->Data == oSum)
            && IsChildrenSumProperty(pRoot->pLeft)
            && IsChildrenSumProperty(pRoot->pRight);
    }

    /*
    Difference between height of left subtree and right subtree should not
    be more than 1. And it should be tree for all node, then we can say that
    it is a height balanced tree
    */
    namespace HeightBalancedTree
    {
        pair<bool, int> IsHeightBalancedTree(Node* pRoot)
        {
            if (nullptr == pRoot)
                return move(make_pair(true, -1));

            pair<bool, int> oLeftSubtree = IsHeightBalancedTree(pRoot->pLeft);
            pair<bool, int> oRightSubtree = IsHeightBalancedTree(pRoot->pRight);
            int oCurrentHeight = 1 + max(oLeftSubtree.second, oRightSubtree.second);
            if (oLeftSubtree.first && oRightSubtree.first)
            {
                return move(make_pair(abs(oLeftSubtree.second - oRightSubtree.second) <= 1, oCurrentHeight));
            }

            return move(make_pair(false, oCurrentHeight));;
        }

        /*
        We will return Height of the node if below subtree are balanced otherwise INT_MIN
        */
        int IsHeightBalancedTrees(Node* pRoot)
        {
            if (nullptr == pRoot)
                return -1;

            int oLeftSubtree = IsHeightBalancedTrees(pRoot->pLeft);
            if (INT_MIN == oLeftSubtree)
                return INT_MIN;

            int oRightSubtree = IsHeightBalancedTrees(pRoot->pRight);
            if (INT_MIN == oRightSubtree)
                return INT_MIN;

            if (abs(oLeftSubtree - oRightSubtree) > 1)
                return INT_MIN;

            return 1 + max(oLeftSubtree, oRightSubtree);
        }
    }
    
    /*
    Max nodes that are available at any level(Max width of level available in binary tree )
    */
    int MaxWidthOfBinaryTree(Node* pRoot)
    {
        int oMaxWidth = -1;

        if (nullptr != pRoot)
        { 
            queue<Node*> pQueue;
            pQueue.push(pRoot);

            while (!pQueue.empty())
            {
                int nCount = static_cast<int>(pQueue.size());
                oMaxWidth = max(oMaxWidth, nCount);
                for (int iCounter = 0; iCounter < nCount; ++iCounter)
                {
                    Node* pCurrent = pQueue.front();
                    pQueue.pop();
                    if (nullptr != pCurrent->pLeft)
                        pQueue.push(pCurrent->pLeft);

                    if (nullptr != pCurrent->pRight)
                        pQueue.push(pCurrent->pRight);
                }
            }
        }
        else {
            oMaxWidth = 0;
        }

        return oMaxWidth;
    }

    void NodesAtDistanceKFromRoot(Node* pRoot, int K)
    {
        if (nullptr == pRoot)
            return;

        if (0 == K) {
            cout << pRoot->Data << " ";
            return;
        }

        NodesAtDistanceKFromRoot(pRoot->pLeft, K - 1);
        NodesAtDistanceKFromRoot(pRoot->pRight, K - 1);
    }

    /*
    Inorder conversion of Binary Tree to Doubly Linked List.
    */
    namespace BinaryTreeToDLL
    {
        Node* Iterative(Node* pRoot)
        {
            Node* pHead = nullptr;

            if (nullptr != pRoot)
            {
                stack<Node*> pStack;
                Node* pLastProcessed = nullptr;
                while ((nullptr != pRoot) || (!pStack.empty()))
                {
                    while (nullptr != pRoot)
                    {
                        pStack.push(pRoot);
                        pRoot = pRoot->pLeft;
                    }

                    Node* pCurrent = pStack.top();
                    pStack.pop();
                    if (nullptr != pCurrent->pRight)
                        pRoot = pCurrent->pRight;

                    if (nullptr == pHead) {
                        pHead = pLastProcessed = pCurrent;
                        pCurrent->pLeft = nullptr;
                    }
                    else {
                        pLastProcessed->pRight = pCurrent;
                        pCurrent->pLeft = pLastProcessed;
                        pLastProcessed = pCurrent;
                    }
                }

                pLastProcessed->pRight = nullptr;
            }

            return pHead;
        }

        Node* Recursive(Node* pRoot, Node*& pLastProcessed)
        {
            if (nullptr == pRoot)
                return nullptr;

            Node* pHead = Recursive(pRoot->pLeft, pLastProcessed);
            if (nullptr == pLastProcessed) {
                pHead = pRoot;
                pRoot->pLeft = nullptr;
            }
            else {
                pRoot->pLeft = pLastProcessed;
                pLastProcessed->pRight = pRoot;
            }
            pLastProcessed = pRoot;

            Recursive(pRoot->pRight, pLastProcessed);
            return pHead;
        }
    }

    /*
    Build Binary Tree from Preorder and Inorder
    */
    Node* BuildBinaryTreeI(vector<int>& oPreorder, vector<int>& oInorder, int oLow, int oHigh, int& oCurrentIdx)
    {
        if (oLow > oHigh)
            return nullptr;

        Node* pNode = new Node(oPreorder[oCurrentIdx]);
        int oInorderIdx = -1;
        for (int iCounter = oLow; iCounter <= oHigh; ++iCounter)
        {
            if (oInorder[iCounter] == oPreorder[oCurrentIdx]) {
                oInorderIdx = iCounter;
                break;
            }
        }

        ++oCurrentIdx;
        pNode->pLeft = BuildBinaryTreeI(oPreorder, oInorder, oLow, oInorderIdx - 1, oCurrentIdx);
        pNode->pRight = BuildBinaryTreeI(oPreorder, oInorder, oInorderIdx + 1, oHigh, oCurrentIdx);
        return pNode;
    }

    /*
    Build Binary Tree from Postorder and Inorder
    */
    Node* BuildBinaryTreeII(vector<int>& oPostorder, vector<int>& oInorder, int oLow, int oHigh, int& oCurrentIdx)
    {
        if (oLow > oHigh)
            return nullptr;

        Node* pNode = new Node(oPostorder[oCurrentIdx]);
        int oInorderIdx = -1;
        for (int iCounter = oLow; iCounter <= oHigh; ++iCounter)
        {
            if (oInorder[iCounter] == oPostorder[oCurrentIdx]) {
                oInorderIdx = iCounter;
                break;
            }
        }

        --oCurrentIdx;
        pNode->pRight = BuildBinaryTreeII(oPostorder, oInorder, oInorderIdx + 1, oHigh, oCurrentIdx);
        pNode->pLeft = BuildBinaryTreeII(oPostorder, oInorder, oLow, oInorderIdx - 1, oCurrentIdx);
        return pNode;
    }
    
    /*
    Diameter of Tree = No of nodes on longest path in a tree
    Note: Below we calculating height in terms of nodes not edges
    */
    namespace DiameterOfBinaryTree
    {
        /*
        N^2, 1
        */
        namespace BruteForce
        {
            int GetHeightN(Node* pRoot)
            {
                if (nullptr == pRoot)
                    return 0;

                return 1 + max(GetHeightN(pRoot->pLeft), GetHeightN(pRoot->pRight));
            }

            int GetDiameter(Node* pRoot)
            {
                if (nullptr == pRoot)
                    return 0;

                int oLeftSubtreeHt = GetHeightN(pRoot->pLeft);
                int oRightSubtreeHt = GetHeightN(pRoot->pRight);
                // Diameter of tree consider current element to be on 
                // belt of Diameter of tree
                int oCurrentDiameter = 1 + oLeftSubtreeHt + oRightSubtreeHt;

                int oLeftSubtreeDiameter = GetDiameter(pRoot->pLeft);
                int oRightSubtreeDiameter = GetDiameter(pRoot->pRight);
                return max(oCurrentDiameter, max(oLeftSubtreeDiameter, oRightSubtreeDiameter));
            }
        }

        /*
        N, N
        */
        namespace Better
        {
            int PopulateHeight(Node* pRoot, unordered_map<Node*, int>& oHashMap)
            {
                if (nullptr == pRoot)
                {
                    oHashMap[pRoot] = 0;
                    return 0;
                }

                int oCurrentHeight = 1 + max(PopulateHeight(pRoot->pLeft, oHashMap),
                    PopulateHeight(pRoot->pRight, oHashMap));
                oHashMap[pRoot] = oCurrentHeight;
                return oCurrentHeight;
            }

            int GetDiameter(Node* pRoot, unordered_map<Node*, int>& oHashMap)
            {
                if (nullptr == pRoot)
                    return 0;

                int oLeftSubtreeHt = oHashMap[pRoot->pLeft];
                int oRightSubtreeHt = oHashMap[pRoot->pRight];
                // Diameter of tree consider current element to be on 
                // belt of Diameter of tree
                int oCurrentDiameter = 1 + oLeftSubtreeHt + oRightSubtreeHt;

                int oLeftSubtreeDiameter = GetDiameter(pRoot->pLeft, oHashMap);
                int oRightSubtreeDiameter = GetDiameter(pRoot->pRight, oHashMap);
                return max(oCurrentDiameter, max(oLeftSubtreeDiameter, oRightSubtreeDiameter));
            }
        }
        
        /*
        N, 1
        */
        namespace Efficient
        {
            int GetDiameter(Node* pRoot, int& oMaxDia)
            {
                if (nullptr == pRoot)
                    return 0;

                int oLeftSubtreeHt = GetDiameter(pRoot->pLeft, oMaxDia);
                int oRightSubtreeHt = GetDiameter(pRoot->pRight, oMaxDia);
                
                // Diameter of tree consider current element to be on 
                // belt of Diameter of tree
                int oCurrentDiameter = 1 + oLeftSubtreeHt + oRightSubtreeHt;
                oMaxDia = max(oMaxDia, oCurrentDiameter); 
                return 1+ max(oLeftSubtreeHt, oRightSubtreeHt);
            }

        }
    }

    namespace LowestCommonAncestor
    {
        namespace Better
        { 
            bool FindPath(Node* pRoot, const int oData, deque<Node*>& pStackPath)
            {
                if (nullptr == pRoot)
                    return false;

                pStackPath.push_front(pRoot);
                if (oData == pRoot->Data)
                    return true;

                if (FindPath(pRoot->pLeft, oData, pStackPath) || FindPath(pRoot->pRight, oData, pStackPath))
                    return true;

                pStackPath.pop_front();
                return false;
            }
            
            Node* LCA(Node* pRoot, const int oFData, const int oSData)
            {
                Node* pLCA = nullptr; 
                
                if (nullptr != pRoot)
                {
                    deque<Node*> pFStackPath, pSStackPath;
                    if (FindPath(pRoot, oFData, pFStackPath) && FindPath(pRoot, oSData, pSStackPath))
                    {
                        while (!pFStackPath.empty() && !pSStackPath.empty())
                        {
                            if (pFStackPath.back() == pSStackPath.back())
                            { 
                                pLCA = pFStackPath.back();
                                pFStackPath.pop_back();
                                pSStackPath.pop_back();
                            }
                            else 
                                break;
                        }
                    }
                }

                return pLCA;
            }
        }

        namespace Simpler
        {
            bool FindPath(Node* pRoot, const int oData, stack<Node*>& pStackPath)
            {
                if (nullptr != pRoot) 
                {
                    if (oData == pRoot->Data
                        || FindPath(pRoot->pLeft, oData, pStackPath)
                        || FindPath(pRoot->pRight, oData, pStackPath))
                    {
                        pStackPath.push(pRoot);
                        return true;
                    }
                }

                return false;
            }

            Node* LCA(Node* pRoot, const int oFData, const int oSData)
            {
                Node* pLCA = nullptr;

                if (nullptr != pRoot)
                {
                    stack<Node*> pFStackPath, pSStackPath;
                    if (FindPath(pRoot, oFData, pFStackPath) && FindPath(pRoot, oSData, pSStackPath))
                    {
                        while (!pFStackPath.empty() && !pSStackPath.empty())
                        {
                            if (pFStackPath.top() == pSStackPath.top())
                            {
                                pLCA = pFStackPath.top();
                                pFStackPath.pop();
                                pSStackPath.pop();
                            }
                            else
                                break;
                        }
                    }
                }

                return pLCA;
            }
        }

        /*
        This method assumes that both data should be available in tree
        Otherwise, it is going to give wrong result;
        */
        namespace Efficient
        {
            Node* LCA(Node* pRoot, int oFData, int oSData)
            {
                Node* pLCA = nullptr; 
                if (nullptr != pRoot)
                { 
                    if (oFData == pRoot->Data || oSData == pRoot->Data)
                        pLCA = pRoot;
                    else
                    { 
                        Node* pLeftLCA = LCA(pRoot->pLeft, oFData, oSData);
                        Node* pRightLCA = LCA(pRoot->pRight, oFData, oSData);
                         
                        if (nullptr != pLeftLCA && nullptr != pRightLCA)  
                            pLCA = pRoot;
                        else if (nullptr != pLeftLCA)
                            pLCA = pLeftLCA;
                        else
                            pLCA = pRightLCA;
                    }
                }

                return pLCA;
            } 
        }
    }

    /*
    Given a binary tree, our task is to count toal nodes.  
    Efficient method which is O(Log n * Log n)
    */
    int CountCBTNodes(Node* pRoot)
    {
        Node* pCurrent = pRoot;
        int oLeftHeight = 0;
        int oRightHeight = 0;
        while (nullptr != pCurrent)
        {
            ++oLeftHeight;
            pCurrent = pCurrent->pLeft;
        }

        pCurrent = pRoot;
        while (nullptr != pCurrent)
        {
            ++oRightHeight;
            pCurrent = pCurrent->pRight;
        }

        if (oLeftHeight == oRightHeight)
            return static_cast<int>(pow(2, oLeftHeight) - 1); // In case if it is perfect binary tree

        return 1 + CountCBTNodes(pRoot->pLeft) + CountCBTNodes(pRoot->pRight);
    }

    /*
    We are given a binary tree and a leaf node, 
    we need to find time to burn the Binary Tree 
    if we burn the given leaf at 0-th second
    */
    int BurnTime(Node* pRoot, int oLeafData, int& oDistance, int& oMaxBurnTime)
    {
        if (nullptr == pRoot)
            return 0;

        if (pRoot->Data == oLeafData)  {
            oDistance = 0;
            return 1;
        }

        int oLeftDistance = -1;
        int oRightDistance = -1;
        int oLeftHeight = BurnTime(pRoot->pLeft, oLeafData, oLeftDistance, oMaxBurnTime);
        int oRightHeight = BurnTime(pRoot->pRight, oLeafData, oRightDistance, oMaxBurnTime);
        if (oLeftDistance != -1) {
            oDistance = 1 + oLeftDistance;
            oMaxBurnTime = max(oMaxBurnTime, oDistance + oRightHeight);
        } 
        else if (oRightDistance != -1)  {
            oDistance = 1 + oRightDistance;
            oMaxBurnTime = max(oMaxBurnTime, oDistance + oLeftHeight);
        }
        return 1 + max(oLeftHeight, oRightHeight);
    }

    /*
    Below method is based on Preorder traversal
    */
    namespace SerializeDeserializeBT
    {
        const int EMPTY = -1;

        void Serialize(Node* pRoot, vector<int>& pStream)
        {
            if (nullptr == pRoot)
            {
                pStream.push_back(EMPTY);
                return;
            }

            pStream.push_back(pRoot->Data);
            Serialize(pRoot->pLeft, pStream);
            Serialize(pRoot->pRight, pStream);
            return;
        }



        Node* Deserialize(vector<int>& pStream, int& oCurrentIdx)
        {
            if ((EMPTY == pStream[oCurrentIdx]) || (oCurrentIdx >= static_cast<int>(pStream.size())))
            {
                ++oCurrentIdx;
                return nullptr;
            }
                

            Node* pNode = new Node(pStream[oCurrentIdx++]); 
            pNode->pLeft = Deserialize(pStream, oCurrentIdx);
            pNode->pRight = Deserialize(pStream, oCurrentIdx);
            return pNode;
        }
    }

    bool IsFBT(Node* pRoot)
    {
        if (nullptr == pRoot)
            return true;

        if ((nullptr != pRoot->pLeft && nullptr == pRoot->pRight)
            || (nullptr != pRoot->pRight && nullptr == pRoot->pLeft))
            return false;

        return IsFBT(pRoot->pLeft) && IsFBT(pRoot->pRight);
    }

    bool IsCBT(Node* pRoot, int oCurrentIdx, int nCount)
    {
        if (nullptr == pRoot)
            return true;

        if (oCurrentIdx >= nCount)
            return false;

        return IsCBT(pRoot->pLeft, (2 * oCurrentIdx) + 1, nCount)
            && IsCBT(pRoot->pRight, (2 * oCurrentIdx) + 2, nCount);
    }
}




int main()
{
    deque<int> oDeque;
    oDeque.push_front(1);
    oDeque.push_front(2);
    oDeque.push_back(3);
    vector<int> oInput{ 50, 20, 10, 30, 60, 80,55, 90 };
    Node* pRoot = BuildTree(oInput);
    Traversals::DepthFirst::Inorder(pRoot);
    cout << endl;
    //Serialize
    vector<int> oStream;
    Problems::SerializeDeserializeBT::Serialize(pRoot, oStream);
    int oCurrentIdx = 0;
    Node* pDeserialized = Problems::SerializeDeserializeBT::Deserialize(oStream, oCurrentIdx);
    Traversals::DepthFirst::Inorder(pDeserialized);
    int oCountNodes = Problems::CountCBTNodes(pRoot);
    Node* pLCA = Problems::LowestCommonAncestor::Simpler::LCA(pRoot, 30, 10);
    int oCount = Problems::MaxWidthOfBinaryTree(pRoot);
    Problems::NodesAtDistanceKFromRoot(pRoot, 2);
    int oSize = GetSize(pRoot);
    int oMx = GetMax(pRoot);
    int oHeight = GetHeight(pRoot);
    unordered_map<int, vector<int>> oResult;
    int oMaxLevel = 0;
    Views::RightView::Recursive(pRoot, 1, oMaxLevel);
    cout << endl;
    Views::RightView::Iterative(pRoot);
    int oMin = INT_MAX;
    int oMax = INT_MIN;
    Traversals::VerticalLevelOrderSq(pRoot);
    cout << endl;
    Traversals::VerticalLevelOrder(pRoot, 0, oResult, oMin, oMax);
    for (int jCounter = oMin; jCounter <= oMax; ++jCounter)
    {
        for (auto& oData : oResult[jCounter])
            cout << oData << " ";

        cout << endl;
    }
    //Traversals::DepthFirst::Preorder(pRoot);
    //cout << endl;
    //Traversals::DepthFirst::Inorder(pRoot);
    //cout << endl;
    //Traversals::DepthFirst::Postorder(pRoot);
    //cout << endl;
    pRoot = DeleteTree(pRoot);
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
