// LeetCode-2870: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/
// decent question

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map <int, int> buildFreqMap(vector <int>& vec) {
        unordered_map <int, int> freqMap;

        for (auto it = vec.begin(); it != vec.end(); it++) {
            freqMap[*it]++;
        }

        return freqMap;
    }

public:
    int minOperations(vector<int>& nums) {
        unordered_map <int, int> freqMap = buildFreqMap(nums);

        int minOps = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            int freq = it->second;
            if (freq == 1) {
                // if frequency of any element is 1, we are dead
                return -1;
            }

            int div3 = freq / 3;
            int mod3 = freq % 3;

            int crrOps = 0;
            switch (mod3) {
                case 0:
                    // frequency of current element is divisible by 3, so we can just remove all instances
                    // of current element in quotient number of steps
                    crrOps = div3;
                    break;

                case 1:
                    // frequency of current element leaves a remainder of 1 (but frequency is not 1 since we already handled that above)
                    // that means if we spare last 1 element and 3 more = total 4, those 4 could be removed two at a time in 2 attempts
                    // and remainder could be removed in (quotient-by-3 - 1) attempts
                    crrOps = (div3 - 1) + 2;
                    break;

                case 2:
                    // frequency of current element leaves a remainder of 2, that means it'll be quotient-by-3 + 1 attempt
                    // (as last two can be removed together)
                    crrOps = div3 + 1;
                    break;

                default:
                    return -1;
            }

            minOps += crrOps;
        }

        return minOps;
    }
};
