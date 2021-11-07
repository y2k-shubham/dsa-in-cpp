// LeetCode-836: https://leetcode.com/problems/rectangle-overlap/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    bool numLiesBetween(int val, int lo, int hi) {
        return (lo < val) && (val < hi);
    }
    
    bool doesOverlapX(vector<int>& rec1, vector<int>& rec2) {
        int x11 = rec1[0]; int y11 = rec1[1];
        int x12 = rec1[2]; int y12 = rec1[3];
        
        int x21 = rec2[0]; int y21 = rec2[1];
        int x22 = rec2[2]; int y22 = rec2[3];
        
        return (numLiesBetween(x11, x21, x22) || numLiesBetween(x12, x21, x22));
    }
    
    bool doesOverlapY(vector<int>& rec1, vector<int>& rec2) {
        int x11 = rec1[0]; int y11 = rec1[1];
        int x12 = rec1[2]; int y12 = rec1[3];
        
        int x21 = rec2[0]; int y21 = rec2[1];
        int x22 = rec2[2]; int y22 = rec2[3];
        
        return (numLiesBetween(y11, y21, y22) || numLiesBetween(y12, y21, y22));
    }
    
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        bool _1_overlaps_2 = doesOverlapX(rec1, rec2) && (doesOverlapY(rec1, rec2) || doesOverlapY(rec2, rec1));
        bool _2_overlaps_1 = doesOverlapX(rec2, rec1) && (doesOverlapY(rec2, rec1) || doesOverlapY(rec1, rec2));
        
        return _1_overlaps_2 || _2_overlaps_1;
    }
};
