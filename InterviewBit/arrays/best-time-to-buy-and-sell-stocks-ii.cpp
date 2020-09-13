// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-ii/
// LeetCode-122: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void testMaxProfit();
int maxProfit1(const vector<int> &price);
int maxProfit2(vector<int> &price);

int main() {
    testMaxProfit();

    return 0;
}

void testMaxProfit() {
    vector<int> price;

    price = {};
    assert(maxProfit1(price) == 0);
    assert(maxProfit2(price) == 0);

    price = {10};
    assert(maxProfit1(price) == 0);
    assert(maxProfit2(price) == 0);

    price = {10, 10};
    assert(maxProfit1(price) == 0);
    assert(maxProfit2(price) == 0);

    price = {10, 9};
    assert(maxProfit1(price) == 0);
    assert(maxProfit2(price) == 0);

    price = {9, 10};
    assert(maxProfit1(price) == 1);
    assert(maxProfit2(price) == 1);

    price = {3, 9};
    assert(maxProfit1(price) == 6);
    assert(maxProfit2(price) == 6);

    price = {9, 3};
    assert(maxProfit1(price) == 0);
    assert(maxProfit2(price) == 0);

    price = {3, 9, 6};
    assert(maxProfit1(price) == 6);
    assert(maxProfit2(price) == 6);

    price = {6, 9, 3};
    assert(maxProfit1(price) == 3);
    assert(maxProfit2(price) == 3);

    price = {3, 9, 6, 7};
    assert(maxProfit1(price) == 7);
    assert(maxProfit2(price) == 7);

    price = {7, 6, 9, 3};
    assert(maxProfit1(price) == 3);
    assert(maxProfit2(price) == 3);

    price = {3, 3, 3, 5, 6, 6, 5, 5, 4, 3, 1, 1, 7, 4, 3};
    assert(maxProfit1(price) == 9);
    assert(maxProfit2(price) == 9);

    price = {3, 4, 7, 1, 1, 3, 4, 5, 5, 6, 6, 5, 3, 3, 3};
    assert(maxProfit1(price) == 9);
    assert(maxProfit2(price) == 9);
}

// submitted on InterviewBit (nested loops)
int maxProfit1(const vector<int> &price) {
    int len = price.size();

    if (len < 2) {
        return 0;
    } else {
        int totProfit = 0;

        int i = 1;
        while (i < len) {
            // initialize both cost & sell price to same value so that even if
            // there's no hill, we end up adding 0 profit
            int crrCost = price[i - 1];
            int crrSell = price[i - 1];

            // climb the hill (increasing prices)
            while ((i < len) && (price[i - 1] <= price[i])) {
                crrSell = price[i];
                i++;
            }

            // update profit made climbing the hill
            totProfit = totProfit + (crrSell - crrCost);
            // cout << totProfit << endl;

            // consume / descend the valley (dropping prices)
            while ((i < len) && (price[i - 1] >= price[i])) {
                i++;
            }
        }

        return totProfit;
    }
}

// submitted on LeetCode (single loop)
int maxProfit2(vector<int> &prices) {
    int len = prices.size();

    if (len < 2) {
        return 0;
    } else {
        int totalProfit = 0;
        int costPrice = INT_MAX;
        int prevPrice = INT_MAX;

        for (int i = 0; i < len; i++) {
            int crrPrice = prices[i];

            if (crrPrice < prevPrice) {
                // then we should've sold stock yesterday and bought it again today
                int crrProfit = prevPrice - costPrice;
                if (crrProfit > 0) {
                    totalProfit += crrProfit;
                }
                costPrice = crrPrice;
            }

            prevPrice = crrPrice;
        }

        if (costPrice < prices[len - 1]) {
            totalProfit += prices[len - 1] - costPrice;
        }

        return totalProfit;
    }
}
