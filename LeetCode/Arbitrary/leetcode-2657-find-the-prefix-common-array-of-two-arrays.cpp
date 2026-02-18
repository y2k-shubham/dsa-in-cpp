// LeetCode-2657: https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/
// Good question

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int len = A.size();
        if (len <= 1) {
            return A;
        }

        vector <int> prefixCommonArray(len);
        prefixCommonArray[len - 1] = len;

        unordered_set<int> seenNums;
        for (int i = len - 1; i >= 1; i--) {
            seenNums.insert(A[i]);
            seenNums.insert(B[i]);

            prefixCommonArray[i - 1] = len - seenNums.size();
        }

        return prefixCommonArray;
    }
};
