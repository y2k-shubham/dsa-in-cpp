// LeetCode-239: https://leetcode.com/problems/sliding-window-maximum/
// Companies: [Google][Microsoft][Amazon][Bloomberg][Infosys][JPMorgan Chase][Walmart Labs][Nutanix][Meta][DE Shaw][Nvidia][tcs][Juspay][Expedia][Verily][Faire][Oracle][Citadel][Goldman Sachs][Uber][IBM][TikTok][DoorDash][Booking.com][Aurora][ServiceNow]

// storing only indices in deque : 33 ms, 26 %tile
// storing (value, index) in deque : 56 ms, 18 %tile (WTF?)

// Monotonic Dequeue
// MetaAI discussion: https://www.meta.ai/share/c/vs40dYDoMh

#include <vector>
#include <deque>
#include <utility>

using namespace std;

class Solution {
private:
    void addEleIdxToDeque(
        vector<int>& nums,
        deque<pair <int, int> >& dq,
        int idx) {
        int ele = nums[idx];
        while (!dq.empty() && (dq.back().first < ele)) {
            dq.pop_back();
        }

        dq.push_back({ele, idx});
    }

    vector<int> createMaxSlidingWindowVec(vector<int>& nums, int k, int len) {
        vector <int> res(len - k + 1);
        deque<pair <int, int> > dq;
        int j = 0;
        for (int i = 0; i < len; i++) {
            // add new (incoming) element (index i) to deque
            addEleIdxToDeque(nums, dq, i);

            if (i < (k - 1)) {
                // we just have to maintain (fill-up) our deque right now
                continue;
            }

            if ((i >= k) && (dq.front().second <= (i - k))) {
                // remove outgoing element (index i-k) from deque
                dq.pop_front();
            }

            // store maximum element in window in result array
            res[j++] = dq.front().first;
        }

        return res;
    }

public:

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        if ((len <= 1) || (k == 1)) {
            return nums;
        }
        if (len == k) {
            return {*max_element(nums.begin(), nums.end())};
        }

        vector<int> res = createMaxSlidingWindowVec(nums, k, len);
        return res;
    }
};
