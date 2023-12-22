// LeetCode-1422: https://leetcode.com/problems/maximum-score-after-splitting-a-string

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    vector<char> convertToVec(string& str) {
        vector<char> vec(str.begin(), str.end());
        return vec;
    }

    vector<int> buildSuffixSumNum1s(vector<char>& vec) {
        int n = vec.size();

        vector<int> suffixSumNum1s(n);
        suffixSumNum1s[n - 1] = (vec[n - 1] == '1') ? 1 : 0;

        for (int i = n - 2; i >= 0; i--) {
            suffixSumNum1s[i] = suffixSumNum1s[i + 1] + ((vec[i] == '1') ? 1 : 0);
        }

        return suffixSumNum1s;
    }

    int findMaxScore(vector<char>& vec, vector<int>& suffixSumNum1s) {
        int maxScore = 0;

        int n = vec.size();
        int num0sLeft = 0;
        for (int i = 0; i < n - 1; i++) {
            if (vec[i] == '0') {
                num0sLeft++;
            }

            int num1sRight = suffixSumNum1s[i + 1];
            int crrScore = num0sLeft + num1sRight;

            maxScore = max(maxScore, crrScore);
        }

        return maxScore;
    }

public:
    int maxScore(string s) {
        vector<char> vec = convertToVec(s);
        vector<int> suffixSumNum1s = buildSuffixSumNum1s(vec);
        return findMaxScore(vec, suffixSumNum1s);
    }
};
