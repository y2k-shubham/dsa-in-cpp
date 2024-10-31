// LeetCode-2279: https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/

#include <cassert>
#include <vector>
#include <map>

using namespace std;

class Solution {
private:
    map<int, int> buildRemCapacityFreqMap(vector<int>& capacity, vector<int>& rocks) {
        map<int, int> remCapFreqMap;

        for (int i = 0; i < capacity.size(); i++) {
            int remCap = capacity[i] - rocks[i];
            remCapFreqMap[remCap]++;
        }

        return remCapFreqMap;
    }

public:
    friend class SolutionTest;

    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        map<int, int> remCapFreqMap = buildRemCapacityFreqMap(capacity, rocks);

        int numFullBags = remCapFreqMap[0];
        remCapFreqMap.erase(0);

        for (auto it = remCapFreqMap.begin(); it != remCapFreqMap.end(); it++) {
            int remCap = it->first;
            int remCapFreq = it->second;

            int reqRocks = remCap * remCapFreq;
            if (reqRocks <= additionalRocks) {
                numFullBags += remCapFreq;
                additionalRocks -= reqRocks;
            } else {
                numFullBags += additionalRocks / remCap;
                break;
            }
        }

        return numFullBags;
    }
};

class SolutionTest {
public:
    void testMaximumBags() {
        Solution sol = Solution();

        vector<int> capacity, rocks;
        int additionalRocks;
        int outExpected, outComputed;

        capacity = {2, 3, 4, 5};
        rocks = {1, 2, 4, 4};
        additionalRocks = 2;
        outExpected = 3;
        outComputed = sol.maximumBags(capacity, rocks, additionalRocks);
        assert(outExpected == outComputed);

        capacity = {10, 2, 2};
        rocks = {2, 2, 0};
        additionalRocks = 100;
        outExpected = 3;
        outComputed = sol.maximumBags(capacity, rocks, additionalRocks);
        assert(outExpected == outComputed);

        capacity = {10, 19, 21};
        rocks = {2, 2, 0};
        additionalRocks = 6;
        outExpected = 0;
        outComputed = sol.maximumBags(capacity, rocks, additionalRocks);
        assert(outExpected == outComputed);

        printf("[testMaximumBags] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest solTest = SolutionTest();

    solTest.testMaximumBags();

    return 0;
}
