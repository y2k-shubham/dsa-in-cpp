// LeetCode-714: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
// written after looking at the editorial solution

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<int> prices;
    int fee;
    vector<int> freeProfit;
    vector<int> holdProfit;

    void init(vector<int> &prices, int fee) {
        this->prices = prices;
        this->fee = fee;

        freeProfit.resize(prices.size());
        holdProfit.resize(prices.size());

        freeProfit[0] = 0;
        holdProfit[0] = -prices[0];
    }

    bool isNonIncreasing(vector<int> &prices) {
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i - 1]) {
                return false;
            }
        }

        return true;
    }

    void calcProfit() {
        for (int i = 1; i < prices.size(); i++) {
            freeProfit[i] = max(freeProfit[i - 1], holdProfit[i - 1] + prices[i] - fee);
            holdProfit[i] = max(holdProfit[i - 1], freeProfit[i - 1] - prices[i]);
        }
    }

public:
    friend class SolutionTest;

    int maxProfit(vector<int> &prices, int fee) {
        if (isNonIncreasing(prices)) {
            return 0;
        }

        init(prices, fee);
        calcProfit();

        return freeProfit[prices.size() - 1];
    }
};


class SolutionTest {
public:
    void testIsNonIncreasing() {
        Solution soln = Solution();
        vector<int> prices;
        bool outExpected, outComputed;

        // empty array
        prices = {};
        outExpected = true;
        outComputed = soln.isNonIncreasing(prices);
        assert(outExpected == outComputed);

        // single length array
        prices = {1};
        outExpected = true;
        outComputed = soln.isNonIncreasing(prices);
        assert(outExpected == outComputed);

        // true case 1
        prices = {1, 1};
        outExpected = true;
        outComputed = soln.isNonIncreasing(prices);
        assert(outExpected == outComputed);

        // true case 2
        prices = {5, 4};
        outExpected = true;
        outComputed = soln.isNonIncreasing(prices);
        assert(outExpected == outComputed);

        // false case 1
        prices = {5, 4, 5};
        outExpected = false;
        outComputed = soln.isNonIncreasing(prices);
        assert(outExpected == outComputed);

        // false case 2
        prices = {1, 2, 3, 4, 5};
        outExpected = false;
        outComputed = soln.isNonIncreasing(prices);
        assert(outExpected == outComputed);
    }

    void testMaxProfit() {
        Solution soln = Solution();
        vector<int> prices;
        int fee;
        int outExpected, outComputed;

        // empty array
        prices = {};
        fee = 0;
        outExpected = 0;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // single length array
        prices = {6};
        fee = 0;
        outExpected = 0;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // non increasing array 1
        prices = {9, 9, 4, 2, 2, 2, 1};
        fee = 0;
        outExpected = 0;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // non increasing array 2
        prices = {5, 4};
        fee = 1;
        outExpected = 0;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // increasing array but no profit due to fee
        prices = {4, 5};
        fee = 1;
        outExpected = 0;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // increasing array and profit due to no fee
        prices = {4, 5};
        fee = 0;
        outExpected = 1;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // LeetCode sample test case 1
        prices = {1, 3, 2, 8, 4, 9};
        fee = 2;
        outExpected = 8;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);

        // LeetCode sample test case 2
        prices = {1, 3, 7, 5, 10, 3};
        fee = 3;
        outExpected = 6;
        outComputed = soln.maxProfit(prices, fee);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testIsNonIncreasing();
    test.testMaxProfit();

    return 0;
}
