// LeetCode-949: https://leetcode.com/problems/largest-time-for-given-digits/
// (incomplete)

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int countFreq(vector <int>& vec, int val) {
        return count(vec.begin(), vec.end(), val);
    }

    bool hasMinFreq(vector <int>& vec, int val, int minFreq) {
        return countFreq(vec, val) >= minFreq;
    }

    bool hasVal(vector <int>& vec, int val) {
        return countFreq(vec, val) > 0;
    }

public:
    string largestTimeFromDigits(vector<int>& digits) {
        // sort digits in descending order
        sort(digits.begin(), digits.end(), greater<int>());

        int smallestDigit = digits[3];
        int secondSmallestDigit = digits[2];
        if ((smallestDigit >= 3) || ((smallestDigit == 2) && (secondSmallestDigit >= 4))) {
            // valid time not possible
            return "";
        }
    }
};
