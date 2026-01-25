// LeetCode-229: https://leetcode.com/problems/majority-element-ii/
// NeetCodeIO: https://www.youtube.com/watch?v=Eua-UrQ_ANo

// covers one tricky bit about maps in C++: iterating over map while also mutating it

#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
private:
    //////////////////////////////////////
    /// functions used during first pass: frequency tracking
    //////////////////////////////////////

    unordered_map<int, int> freqMap;
    int MAX_FREQ_MAP_SIZE = 2;

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

    void findMajorityElements(vector<int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            incrFreq(vec[i]);
            reduceFreqMapIfSizeExceeded();
        }
    }

    //////////////////////////////////////
    /// functions used during second pass: result confirmation
    //////////////////////////////////////

    int countFreq(vector<int>& vec, int num) {
        int count = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == num) {
                count++;
            }
        }
        return count;
    }

    vector<int> verifyMajorityElements(vector<int>& vec) {
        if (freqMap.empty()) {
            return {};
        }

        int len = vec.size();
        vector<int> majorityElements;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if (countFreq(vec, it->first) > (len / 3)) {
                majorityElements.push_back(it->first);
            }
        }

        return majorityElements;
    }

public:
    vector<int> majorityElement(vector<int>& nums) {
        clearMap();
        findMajorityElements(nums);

        vector<int> majorityElements = verifyMajorityElements(nums);
        if (!majorityElements.empty()) {
            sort(majorityElements.begin(), majorityElements.end());
        }

        return majorityElements;
    }
};

class SolutionTest {
public:
    void testMajorityElement() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> resOutExpected, resOutComputed;

        vecIn = {3, 2, 3};
        resOutExpected = {3};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {1};
        resOutExpected = {1};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {1, 2};
        resOutExpected = {1, 2};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {1, 2, 3};
        resOutExpected = {};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {2, 4, 2, 5, 7, 3};
        resOutExpected = {};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {2, 4, 2, 5, 7, 2};
        resOutExpected = {2};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {2, 4, 2, 5, 7, 2, 4};
        resOutExpected = {2};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {2, 4, 2, 5, 7, 2, 4, 4};
        resOutExpected = {2, 4};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);

        vecIn = {2, 4, 2, 5, 7, 2, 4, 4, 5};
        resOutExpected = {};
        resOutComputed = soln.majorityElement(vecIn);
        assert(resOutComputed == resOutExpected);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testMajorityElement();

    return 0;
}
