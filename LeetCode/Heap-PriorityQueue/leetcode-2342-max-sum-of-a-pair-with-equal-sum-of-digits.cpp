// LeetCode-2342: https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits

#include <vector>
#include <unordered_map>
#include <climits>
#include <queue>
#include <utility>

using namespace std;

class Solution {
private:
    inline int getDigSum(int num) {
        int digSum = 0;

        while (num > 0) {
            digSum += (num % 10);
            num /= 10;
        }

        return digSum;
    }

    unordered_map <int, priority_queue <int>> createDigSumToNumMap(vector <int>& nums) {
        unordered_map <int, priority_queue <int, vector <int>>> digSumToNumMap;

        for (int num : nums) {
            int digSum = getDigSum(num);
            digSumToNumMap[digSum].push(num);
        }

        return digSumToNumMap;
    }

    pair <int, int> getTop2Elements(unordered_map <int, priority_queue <int>>& digSumToNumMap, int digSum) {
        auto& pQue = digSumToNumMap[digSum];

        int topEle = pQue.top();
        pQue.pop();
        int secondTopEle = pQue.top();
        pQue.pop();

        return {topEle, secondTopEle};
    }

    int findMaxSum(unordered_map <int, priority_queue <int>>& digSumToNumMap) {
        int maxSum = INT_MIN;

        for (auto it = digSumToNumMap.begin(); it != digSumToNumMap.end(); it++) {
            auto& pQue = it->second;
            if (pQue.size() > 1) {
                pair <int, int> topPair = getTop2Elements(digSumToNumMap, it->first);

                int sum = topPair.first + topPair.second;
                maxSum = max(maxSum, sum);
            }
        }

        return (maxSum == INT_MIN) ? -1 : maxSum;
    }

public:
    int maximumSum(vector <int>& nums) {
        auto digSumToNumMap = createDigSumToNumMap(nums);
        return findMaxSum(digSumToNumMap);
    }
};
