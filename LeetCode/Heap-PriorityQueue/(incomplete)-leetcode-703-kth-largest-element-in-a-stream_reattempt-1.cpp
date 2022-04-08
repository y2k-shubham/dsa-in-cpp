// LeetCode-703: https://leetcode.com/problems/kth-largest-element-in-a-stream/
// incomplete: problem not clear

#include <map>
#include <vector>
#include <cassert>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

class KthLargest {
private:
    int k;
    priority_queue<int> maxHeap; // smallest k elements

    void createHeap(vector <int>& vec, int k) {
        if (vec.empty()) {
            return;
        }
        sort(vec.begin(), vec.end());

        priority_queue<int> maxHeap(vec.begin(), vec.begin() + k);
        this->maxHeap = maxHeap;
    }

public:
    KthLargest(int k, vector<int>& nums) {
        createHeap(nums, k);
    }

    int add(int val) {
        if (val >= maxHeap.top()) {
            return maxHeap.top();
        }

        this->k = k;

        // add new value in heap
        maxHeap.push(val);
        if (maxHeap.size() > k) {
            // remove k+1th value from heap
            maxHeap.pop();
        }

        return maxHeap.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
