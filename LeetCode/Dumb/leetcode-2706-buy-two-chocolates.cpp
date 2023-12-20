// LeetCode-2706: https://leetcode.com/problems/buy-two-chocolates

#include <vector>
#include <climits>
#include <utility>

using namespace std;

class Solution {
private:
    pair<int, int> findMin2Eles(vector<int>& vec) {
        int min1Ele = INT_MAX;
        int min2Ele = INT_MAX;

        for (int i = 0; i < vec.size(); i++) {
            int ele = vec[i];
            if (ele <= min1Ele) {
                min2Ele = min1Ele;
                min1Ele = ele;
            } else if (ele < min2Ele) {
                min2Ele = ele;
            }
        }

        return {min1Ele, min2Ele};
    }

public:
    int buyChoco(vector<int>& prices, int money) {
        pair<int, int> min2Eles = findMin2Eles(prices);

        int totalCost = min2Eles.first + min2Eles.second;
        if (totalCost > money) {
            return money;
        } else {
            return money - totalCost;
        }
    }
};
