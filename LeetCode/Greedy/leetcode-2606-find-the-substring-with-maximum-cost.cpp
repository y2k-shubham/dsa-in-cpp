// LeetCode-2606: https://leetcode.com/problems/find-the-substring-with-maximum-cost/

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define BEGIN_CHAR 'a'
#define MAX_CHAR 'z'

class Solution {
private:
    vector <int> finalCharVals;

    void initFinalCharVals(string chars, vector <int> vals) {
        unordered_map <char, int> providedCharVals;
        for (int i = 0; i < chars.size(); i++) {
            providedCharVals[chars[i]] = vals[i];
        }

        this->finalCharVals.resize(MAX_CHAR + 1);
        for (char ch = BEGIN_CHAR; ch <= MAX_CHAR; ch++) {
            if (providedCharVals.find(ch) != providedCharVals.end()) {
                finalCharVals[ch] = providedCharVals[ch];
            }
            else {
                finalCharVals[ch] = ch - BEGIN_CHAR + 1;
            }
        }
    }

    vector <int> convertStrToCharVals(string& str) {
        vector <int> charVals(str.size());

        int i = 0;
        for (auto ch : str) {
            charVals[i++] = this->finalCharVals[ch];
        }

        return charVals;
    }

    int findMaxSubarraySum(vector <int>& nums) {
        int maxSum = 0;
        int crrSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            crrSum += nums[i];
            maxSum = max(maxSum, crrSum);

            if (crrSum < 0) {
                crrSum = 0;
            }
        }

        return maxSum;
    }

public:
    int maximumCostSubstring(string s, string chars, vector <int>& vals) {
        initFinalCharVals(chars, vals);

        vector <int> charVals = convertStrToCharVals(s);
        return findMaxSubarraySum(charVals);
    }
};
