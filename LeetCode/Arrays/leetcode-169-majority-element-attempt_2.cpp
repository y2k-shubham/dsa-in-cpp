// LeetCode-169: https://leetcode.com/problems/majority-element/

// Inspired by solution for LeetCode-229: Majority Element II ( https://leetcode.com/problems/majority-element-ii )
// by NeetCode: https://www.youtube.com/watch?v=Eua-UrQ_ANo

// covers one tricky bit about maps in C++: iterating over map while also mutating it

#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
private:
    unordered_map<int, int> freqMap;
    int MAX_FREQ_MAP_SIZE = 1;

    // not clearing the map after test run results in SegmentationFault
    // (since same soln object is being used across all test cases)
    void clearMap() {
        freqMap.clear();
    }

    void incrFreq(int ele) {
        if (freqMap.find(ele) == freqMap.end()) {
            freqMap[ele] = 0;
        }
        freqMap[ele]++;
    }

    void decrFreq(int ele) {
        freqMap[ele]--;
        if (freqMap[ele] <= 0) {
            freqMap.erase(ele);
        }
    }

    void reduceFreqMapIfSizeExceeded() {
        if (freqMap.size() <= MAX_FREQ_MAP_SIZE) {
            return;
        }

        // tricky: iterating over map while also mutating it
        for (auto it = freqMap.begin(); it != freqMap.end();) {
            it->second--;

            if (it->second <= 0) {
                it = freqMap.erase(it); // erase returns iterator to next element
            } else {
                ++it; // only increment if we didn't erase
            }
        }
    }

public:
    friend class SolutionTest;

    int majorityElement(vector<int>& nums) {
        if (nums.empty()) {
            return INT_MIN;
        }
        if (nums.size() == 1) {
            return nums[0];
        }

        for (int num : nums) {
            incrFreq(num);
            reduceFreqMapIfSizeExceeded();
        }

        return (freqMap.begin())->first;
    }
};

class SolutionTest {
public:
    void testMajorityElement() {
        vector<int> vecIn;
        int outExpected, outComputed;
        Solution soln = Solution();

        vecIn = {};
        outExpected = INT_MIN;
        outComputed = soln.majorityElement(vecIn);
        assert(outExpected == outComputed);
        // not clearing the map after test run results in SegmentationFault
        // (since same soln object is being used across all test cases)
        soln.clearMap();

        vecIn = {15};
        outExpected = 15;
        outComputed = soln.majorityElement(vecIn);
        assert(outExpected == outComputed);

        vecIn = {17, 17};
        outExpected = 17;
        outComputed = soln.majorityElement(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3, 2, 3};
        outExpected = 3;
        outComputed = soln.majorityElement(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 1, 1, 1, 2, 2};
        outExpected = 2;
        outComputed = soln.majorityElement(vecIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testMajorityElement();

    return 0;
}
