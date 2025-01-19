// LeetCode-944: https://leetcode.com/problems/delete-columns-to-make-sorted/

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    bool isSorted(vector <string>& strs, int posn) {
        for (int i = 1; i < strs.size(); i++) {
            char prevChar = strs[i - 1].at(posn);
            char crrChar = strs[i].at(posn);
            if (prevChar > crrChar) {
                return false;
            }
        }

        return true;
    }

public:
    int minDeletionSize(vector <string>& strs) {
        int singleStrLen = strs[0].size();

        int numDeletions = 0;
        for (int i = 0; i < singleStrLen; i++) {
            if (!isSorted(strs, i)) {
                numDeletions++;
            }
        }

        return numDeletions;
    }
};
