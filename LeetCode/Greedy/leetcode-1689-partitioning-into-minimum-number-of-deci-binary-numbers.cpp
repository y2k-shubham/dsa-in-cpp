// LeetCode-1689: https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
// a bit of a brain teaser; pretty straightforward once you get it
// (i had to check the hints)

#include <iostream>

using namespace std;

class Solution {
private:
    int findMaxDig(string n) {
        int maxDig = -1;

        for (auto it = n.begin(); it != n.end(); it++) {
            int crrDig = *it - '0';
            maxDig = max(maxDig, crrDig);
        }

        return maxDig;
    }

public:
    int minPartitions(string n) {
        return findMaxDig(n);
    }
};
