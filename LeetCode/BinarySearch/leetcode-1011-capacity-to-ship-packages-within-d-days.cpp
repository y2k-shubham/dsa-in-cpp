// LeetCode-1011: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/

// nice question overall
// once you know that it is an application of BinarySearch, you know how to do it

#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    int calcMinReqShipCapacity(vector<int>& weights, int days) {
        int maxWeight = *std::max_element(weights.begin(), weights.end());
        if (days >= weights.size()) {
            return maxWeight;
        }

        int totalWeight = std::accumulate(weights.begin(), weights.end(), 0);
        if (days == 1) {
            return totalWeight;
        }

        int ceiledAvgBucketWeight = (int) ceil(((float) totalWeight) / days);
        return std::max(maxWeight, ceiledAvgBucketWeight);
    }

    inline bool canShipInShipWithCapacity(vector<int>& weights, int days, int capacity) {
        int idx = 0;
        int daysRequired = 1;
        int currBucketWeight = 0;

//        if (debug) {
//            // print days and capacity
//            printf("days=%d, capacity=%d\n", days, capacity);
//        }

        for (int weight: weights) {
            if (weight > capacity) {
                return false;
            }

            if (currBucketWeight + weight > capacity) {
                daysRequired++;
                currBucketWeight = weight;
            } else {
                currBucketWeight += weight;
            }

            if (daysRequired > days) {
//                if (debug) {
//                    printf("at weights[idx=%d]=%d, daysRequired=%d, currBucketWeight=%d; exiting because it exceeds days=%d\n", idx, weight, daysRequired, currBucketWeight, days);
//                }
                return false;
            } else if (debug) {
//                printf("at weights[idx=%d]=%d, daysRequired=%d, currBucketWeight=%d\n", idx, weight, daysRequired, currBucketWeight);
            }

            idx++;
        }

        return daysRequired <= days;
    }

public:
    friend class SolutionTest;

    int shipWithinDays(vector<int>& weights, int days) {
        int minReqShipCapacity = calcMinReqShipCapacity(weights, days);

        int lo = minReqShipCapacity;
        int hi = std::accumulate(weights.begin(), weights.end(), 0);
        int mid;

        int minCalculatedCapacity = hi;
        while (lo <= hi) {
            mid = (lo + hi) / 2;

            if (canShipInShipWithCapacity(weights, days, mid)) {
                minCalculatedCapacity = min(minCalculatedCapacity, mid);
                hi = mid - 1;
//                if (debug) {
//                    printf("at mid=%d, canShipInShipWithCapacity returned true; setting hi=%d & minCalculatedCapacity=%d\n", mid, hi, minCalculatedCapacity);
//                }
            } else {
                lo = mid + 1;
//                if (debug) {
//                    printf("at mid=%d, canShipInShipWithCapacity returned false; setting lo=%d\n", mid, lo);
//                }
            }
        }

        return minCalculatedCapacity;
    }
};

class SolutionTest {
public:
    void testCalcMinReqShipCapacity() {
        Solution soln = Solution();
        vector<int> weightsIn;
        int daysIn;
        int minReqShipCapacityOutExpected, minReqShipCapacityOutComputed;

        weightsIn = {5};
        daysIn = 1;
        minReqShipCapacityOutExpected = 5;
        minReqShipCapacityOutComputed = soln.calcMinReqShipCapacity(weightsIn, daysIn);
        assert(minReqShipCapacityOutExpected == minReqShipCapacityOutComputed);

        weightsIn = {5};
        daysIn = 3;
        minReqShipCapacityOutExpected = 5;
        minReqShipCapacityOutComputed = soln.calcMinReqShipCapacity(weightsIn, daysIn);
        assert(minReqShipCapacityOutExpected == minReqShipCapacityOutComputed);

        weightsIn = {5, 3};
        daysIn = 2;
        minReqShipCapacityOutExpected = 5;
        minReqShipCapacityOutComputed = soln.calcMinReqShipCapacity(weightsIn, daysIn);
        assert(minReqShipCapacityOutExpected == minReqShipCapacityOutComputed);

        weightsIn = {5, 3};
        daysIn = 1;
        minReqShipCapacityOutExpected = 8;
        minReqShipCapacityOutComputed = soln.calcMinReqShipCapacity(weightsIn, daysIn);
        assert(minReqShipCapacityOutExpected == minReqShipCapacityOutComputed);

        weightsIn = {8, 1, 3, 7, 4, 2, 9};
        daysIn = 3;
        minReqShipCapacityOutExpected = 12;
        minReqShipCapacityOutComputed = soln.calcMinReqShipCapacity(weightsIn, daysIn);
        assert(minReqShipCapacityOutExpected == minReqShipCapacityOutComputed);

        printf("[testCalcMinReqShipCapacity] All test-cases passed\n");
    }

    void testCanShipWithCapacity() {
        Solution soln = Solution();
        vector<int> weights;
        int days, capacity;
        bool outExpected, outComputed;

        weights = {5};
        days = 1;
        capacity = 5;
        outExpected = true;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {5};
        days = 1;
        capacity = 4;
        outExpected = false;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {5};
        days = 3;
        capacity = 4;
        outExpected = false;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {8, 1, 3, 7, 4, 2, 9};
        days = 7;
        capacity = 8;
        outExpected = false;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {8, 1, 3, 7, 4, 2, 9};
        days = 7;
        capacity = 9;
        outExpected = true;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {8, 1, 3, 7, 4, 2, 9};
        days = 3;
        capacity = 11;
        outExpected = false;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {8, 1, 3, 7, 4, 2, 9};
        days = 3;
        capacity = 12;
        outExpected = true;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        weights = {8, 1, 3, 7, 4, 2, 9};
        days = 4;
        capacity = 11;
        outExpected = true;
        outComputed = soln.canShipInShipWithCapacity(weights, days, capacity);
        assert(outExpected == outComputed);

        printf("[testCanShipWithCapacity] All test-cases passed!\n");
    }

    void testShipWithinDays() {
        Solution soln = Solution();
        vector<int> weights;
        int days, outExpected, outComputed;

        weights = {5};
        days = 1;
        outExpected = 5;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

        weights = {5};
        days = 3;
        outExpected = 5;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

//        soln.debug = true;
        weights = {5, 3};
        days = 2;
        outExpected = 5;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);
//        soln.debug = false;

        weights = {5, 3};
        days = 1;
        outExpected = 8;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

        weights = {8, 1, 3, 7, 4, 2, 9};
        days = 3;
        outExpected = 12;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

        weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        days = 5;
        outExpected = 15;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

        weights = {3, 2, 2, 4, 1, 4};
        days = 3;
        outExpected = 6;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

        weights = {1, 2, 3, 1, 1};
        days = 4;
        outExpected = 3;
        outComputed = soln.shipWithinDays(weights, days);
        assert(outExpected == outComputed);

        printf("[testShipWithinDays] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testCalcMinReqShipCapacity();
    test.testCanShipWithCapacity();
    test.testShipWithinDays();

    return 0;
}
