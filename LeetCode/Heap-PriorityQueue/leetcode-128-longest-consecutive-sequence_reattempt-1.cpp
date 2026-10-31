// LeetCode-128: https://leetcode.com/problems/longest-consecutive-sequence/
// Companies: [Google][Amazon][Microsoft][Bloomberg][Infosys][Meta][tcs][Apple][TikTok][Oracle][Walmart Labs][Goldman Sachs][IBM][Uber][Okta][Nvidia][PayPal][Wissen Technology]

// good question when solved purely with heap (has an edge case around duplicates)
// LC runtime: 65 ms

#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Solution {
private:
    priority_queue<int, vector<int>, greater<int>> convertToMinHeap(vector <int>& vec) {
        priority_queue<int, vector<int>, greater<int>> minHeap(vec.begin(), vec.end());
        return minHeap;
    }

    bool isConsec(int prevEle, int crrEle) {
        if (min(prevEle, crrEle) == INT_MIN) {
            return false;
        }
        if (max(prevEle, crrEle) == INT_MAX) {
            return false;
        }

        return (prevEle + 1) == crrEle;
    }

    bool isEqual(int prevEle, int crrEle) {
        return prevEle == crrEle;
    }

    int popElesTillConsec(priority_queue<int, vector<int>, greater<int>>& minHeap) {
        int numTotalElesPopped = 0;
        int numConsecElesPopped = 0;
        int prevEle, crrEle;
        do {
            prevEle = minHeap.top();
            minHeap.pop();
            numTotalElesPopped++;

            crrEle = minHeap.empty() ? INT_MAX : minHeap.top();

            if (isConsec(prevEle, crrEle)) {
                numConsecElesPopped++;
            }
        } while (!minHeap.empty() && (isConsec(prevEle, crrEle) || isEqual(prevEle, crrEle)));

        // not super-clear why + 1 is needed here, unlike in the deduped variant where its not required
        return numConsecElesPopped + 1;
    }

public:
    int longestConsecutive(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        priority_queue<int, vector<int>, greater<int>> minHeap = convertToMinHeap(nums);

        int maxConsecSeqLen = 0;
        while (!minHeap.empty()) {
            int crrConsecSeqLen = popElesTillConsec(minHeap);
            maxConsecSeqLen = max(maxConsecSeqLen, crrConsecSeqLen);
        }

        return maxConsecSeqLen;
    }
};
