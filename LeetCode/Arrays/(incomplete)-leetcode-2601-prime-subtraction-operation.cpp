// LeetCode-2601: https://leetcode.com/problems/prime-subtraction-operation/
// InComplete

#include <vector>
#include <algorithm>

#define MAX_VAL 1001

using namespace std;

class Solution {
private:
    vector <int> primes;

    inline bool isPrime(int num) {
        for (int i = 2; i < num; i++) {
            if ((num % i) == 0) {
                return false;
            }
        }

        return true;
    }

    void populatePrimesTillMaxVal() {
        for (int i = 2; i <= MAX_VAL; i++) {
            if (isPrime(i)) {
                primes.push_back(i);
            }
        }
    }

    vector <int> buildMinValInLeftVec(vector <int>& nums) {
        if (nums.empty()) {
            return {};
        }

        int len = nums.size();
        vector <int> minValInLeftVec(len);

        int minValInLeft = nums[0];
        minValInLeftVec[0] = minValInLeft;
        for (int i = 1; i < len; i++) {
            minValInLeft = min(minValInLeft, nums[i]);
            minValInLeftVec[i] = minValInLeft;
        }

        return minValInLeftVec;
    }

    // inline int findMax

public:
    bool primeSubOperation(vector<int>& nums) {

    }
};
