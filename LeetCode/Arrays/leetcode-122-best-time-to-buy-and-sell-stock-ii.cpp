// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-ii/
// LeetCode-122: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/
// https://www.geeksforgeeks.org/stock-buy-sell/
// GFG problem requires printing all buy and sell price pairs too

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    pair<int, int> findIncWindowProfit(vector<int> &vec, int startIdx) {
        if (vec.size() <= 1) {
            return {vec.size(), 0};
        }

        int startEle = vec[startIdx];
//        printf("for vec[startIdx=%d] = %d, ", startIdx, startEle);

        int i;
        for (i = startIdx + 1; i < vec.size(); i++) {
            if (vec[i - 1] > vec[i]) {
//                printf("broke at vec[i=%d] = %d\n", i, vec[i]);
                break;
            }
        }

        int profit = 0;
        if (i >= vec.size()) {
//            printf("ended\n");
            profit = *(vec.rbegin()) - startEle;
        } else {
            profit = vec[i - 1] - startEle;
        }

        return {i, profit};
    }

public:
    friend class SolutionTest;

    int maxProfit(vector<int> &prices) {
        if (prices.size() <= 1) {
            return 0;
        }

        int profit = 0;
        int i = 0;
        while (i < prices.size()) {
            pair<int, int> incWindowProfit = findIncWindowProfit(prices, i);
//            printf("i: %d, incWindowProfit: (%d, %d)\n", i, incWindowProfit.first, incWindowProfit.second);
            i = incWindowProfit.first;
            profit += incWindowProfit.second;

            // printf i & prices.size()
//            printf("i: %d, prices.size(): %zu\n", i, prices.size());
        }

        return profit;
    }
};

class SolutionTest {
public:
    void testFindIncWindowProfit() {
        Solution soln = Solution();
        vector<int> vec;
        int startIdx;
        pair<int, int> outExpected;
        pair<int, int> outComputed;

        vec = {};
        startIdx = 0;
        outExpected = {0, 0};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

        vec = {10};
        startIdx = 0;
        outExpected = {1, 0};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

        vec = {10, 10};
        startIdx = 0;
        outExpected = {2, 0};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

//         test case for array {10, 9}
        vec = {10, 9};
        startIdx = 0;
        outExpected = {1, 0};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

        vec = {10, 9};
        startIdx = 1;
        outExpected = {2, 0};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

        // test case for array {9, 10}
        vec = {9, 10};
        startIdx = 0;
        outExpected = {2, 1};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

        // test case for array {9, 10, 1, 3}
        vec = {9, 10, 1, 3};
        startIdx = 0;
        outExpected = {2, 1};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);

        vec = {9, 10, 1, 3};
        startIdx = 2;
        outExpected = {4, 2};
        outComputed = soln.findIncWindowProfit(vec, startIdx);
        assert(outExpected == outComputed);
    }

    void testMaxProfit() {
        Solution soln = Solution();
        vector<int> vec;
        int outExpected;
        int outComputed;

        vec = {9, 10, 1, 3};
        outExpected = 3;
        outComputed = soln.maxProfit(vec);
        // printf outExpected and outComputed
//        printf("outExpected: %d, outComputed: %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vec = {7,1,5,3,6,4};
        outExpected = 7;
        outComputed = soln.maxProfit(vec);
        // printf outExpected and outComputed
//        printf("outExpected: %d, outComputed: %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vec = {1,2,3,4,5};
        outExpected = 4;
        outComputed = soln.maxProfit(vec);
        // printf outExpected and outComputed
//        printf("outExpected: %d, outComputed: %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vec = {7,6,4,3,1};
        outExpected = 0;
        outComputed = soln.maxProfit(vec);
        // printf outExpected and outComputed
//        printf("outExpected: %d, outComputed: %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindIncWindowProfit();
    solnTest.testMaxProfit();

    return 0;
}
