// LeetCode-128: https://leetcode.com/problems/longest-consecutive-sequence/
// Companies: [Google][Amazon][Microsoft][Bloomberg][Infosys][Meta][tcs][Apple][TikTok][Oracle][Walmart Labs][Goldman Sachs][IBM][Uber][Okta][Nvidia][PayPal][Wissen Technology]

// oddly enough (unordered) set based de-duping worsens the runtime instead of improving it, though it simplifies the implementation
// LC runtime: 142 ms

#include <vector>
#include <queue>
#include <functional>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set<int> convertToSet(vector <int>& vec) {
        unordered_set<int> mSet(vec.begin(), vec.end());
        return mSet;
    }

    priority_queue<int, vector<int>, greater<int>> convertToMinHeap(unordered_set<int>& mSet) {
        priority_queue<int, vector<int>, greater<int>> minHeap(mSet.begin(), mSet.end());
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

    int popElesTillConsec(priority_queue<int, vector<int>, greater<int>>& minHeap) {
        int numTotalElesPopped = 0;
        int prevEle, crrEle;
        do {
            prevEle = minHeap.top();
            minHeap.pop();
            numTotalElesPopped++;

            crrEle = minHeap.empty() ? INT_MAX : minHeap.top();
        } while (!minHeap.empty() && isConsec(prevEle, crrEle));

        // somehow now + 1 is needed here, unlike in the non-dedup variant
        return numTotalElesPopped;
    }

public:
    int longestConsecutive(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        unordered_set<int> mSet = convertToSet(nums);
        priority_queue<int, vector<int>, greater<int>> minHeap = convertToMinHeap(mSet);

        int maxConsecSeqLen = 0;
        while (!minHeap.empty()) {
            int crrConsecSeqLen = popElesTillConsec(minHeap);
            maxConsecSeqLen = max(maxConsecSeqLen, crrConsecSeqLen);
        }

        return maxConsecSeqLen;
    }
};
