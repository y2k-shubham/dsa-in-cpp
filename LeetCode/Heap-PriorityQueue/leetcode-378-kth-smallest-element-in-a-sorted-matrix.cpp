// LeetCode-378: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
// brute-force 'like' approach (poor memory complexity)

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

class Solution {
private:
    vector<vector<bool> > createVisitedMat(int n) {
        vector<vector<bool> > visitedMat(n);
        for (int i = 0; i < n; i++) {
            vector<bool> visitedMatVec(n, false);
            visitedMat[i] = visitedMatVec;
        }

        return visitedMat;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<tuple<int, int, int> > > pQue;
        pQue.push({matrix[0][0], 0, 0});

        vector<vector<bool> > visitedMat = createVisitedMat(n);
        visitedMat[0][0] = true;

        int lastEle = matrix[0][0];
        for (int i = 1; i <= k; i++) {
            tuple<int, int, int> crrEle = pQue.top();
            pQue.pop();

            lastEle = get<0>(crrEle);

            int r = get<1>(crrEle);
            int c = get<2>(crrEle);
            // right ele
            if ((c < n - 1) && !visitedMat[r][c + 1]) {
                pQue.push({matrix[r][c + 1], r, c + 1});
                visitedMat[r][c + 1] = true;
            }
            // bottom ele
            if ((r < n - 1) && !visitedMat[r + 1][c]) {
                pQue.push({matrix[r + 1][c], r + 1, c});
                visitedMat[r + 1][c] = true;
            }
        }

        return lastEle;
    }
};
