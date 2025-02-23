// LeetCode-870: https://leetcode.com/problems/advantage-shuffle

/**
 * good question
 *  - got it wrong the first time; see file "LeetCode/Greedy/(wrong)-leetcode-870-advantage-shuffle.cpp"
 *  - implemented after seeing solution given in Editorial: https://leetcode.com/problems/advantage-shuffle/editorial/
 */

#include <vector>
#include <map>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
private:
    void showVec(vector <int>& vec, string name, string when) {
        printf("%s, vec %s is:-\n", when.c_str(), name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");
    }

    vector <pair <int, int>> createValIdxVec(vector <int>& vec) {
        vector <pair <int, int>> valIdxVec;
        for (int i = 0; i < vec.size(); i++) {
            valIdxVec.push_back(make_pair(vec[i], i));
        }

        return valIdxVec;
    }

    unordered_map <int, int> buildPairingIndexMappings(
        vector <pair <int, int>> sortedValIdxVec1,
        vector <pair <int, int>> sortedValIdxVec2) {
        int len = sortedValIdxVec1.size();
        unordered_map <int, int> pairingIndexMappings;

        int i1 = 0;
        int i2Lo = 0;
        int i2Hi = len - 1;
        while ((i1 < len) && (i2Lo <= i2Hi)) {
            pair <int, int> valIdx1 = sortedValIdxVec1[i1];
            int val1 = valIdx1.first;
            int idx1 = valIdx1.second;

            pair <int, int> valIdx2 = sortedValIdxVec2[i2Lo];
            int val2 = valIdx2.first;
            int idx2 = valIdx2.second;

            if (val1 > val2) {
                // we can score an advantage, so we'll pair up val1 with val2
                // and this is the most efficient use possible for val1 in all pairings
                pairingIndexMappings[idx2] = idx1;
                i1++;
                i2Lo++;
            } else {
                // we can't score an advantage, so we'll pair up val1 with biggest item of vec2,
                // so as to 'waste' that big item by letting it win over just our (current) smallest item
                pairingIndexMappings[sortedValIdxVec2[i2Hi].second] = idx1;
                i1++;
                i2Hi--;
            }
        }

        return pairingIndexMappings;
    }

    vector <int> constructShuffleAnswer(
        vector <int>& nums1,
        unordered_map <int, int> pairingIndexMappings) {
        int len = nums1.size();
        vector <int> shuffleAnswer(len);

        for (int i = 0; i < len; i++) {
            shuffleAnswer[i] = nums1[pairingIndexMappings[i]];
        }

        return shuffleAnswer;
    }

public:
    friend class SolutionTest;

    vector <int> advantageCount(vector <int>& nums1, vector <int>& nums2) {
        vector <pair <int, int>> valIdxVec1 = createValIdxVec(nums1);
        vector <pair <int, int>> valIdxVec2 = createValIdxVec(nums2);

        sort(valIdxVec1.begin(), valIdxVec1.end());
        sort(valIdxVec2.begin(), valIdxVec2.end());

        unordered_map <int, int> pairingIndexMappings = buildPairingIndexMappings(valIdxVec1, valIdxVec2);
        return constructShuffleAnswer(nums1, pairingIndexMappings);
    }
};

class SolutionTest {
public:
    void testAdvantageCount() {
        Solution soln;
        vector <int> nums1;
        vector <int> nums2;
        vector <int> expected;
        vector <int> actual;

        nums1 = {2, 7, 11, 15};
        nums2 = {1, 10, 4, 11};
        expected = {2, 11, 7, 15};
        actual = soln.advantageCount(nums1, nums2);
        assert(expected == actual);

        nums1 = {12, 24, 8, 32};
        nums2 = {13, 25, 32, 11};
        expected = {24, 32, 8, 12};
        actual = soln.advantageCount(nums1, nums2);
        assert(expected == actual);

        nums1 = {2, 0, 4, 1, 2};
        nums2 = {1, 3, 0, 0, 2};
        expected = {2, 0, 1, 2, 4};
        actual = soln.advantageCount(nums1, nums2);
        // soln.showVec(actual, "actual", "at end");
        assert(expected == actual);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testAdvantageCount();

    return 0;
}
