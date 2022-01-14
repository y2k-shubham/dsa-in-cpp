// LeetCode-1865: https://leetcode.com/problems/finding-pairs-with-a-certain-sum/

// barely accepted
// LC submission: speed 5 %tile, memory 23 %tile

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class FindSumPairs {
   private:
    vector<int> vec1;
    vector<int> vec2;
    unordered_map<int, int> freqMap2;

    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    void updateFreqMap(unordered_map<int, int>& freqMap, int oldVal, int newVal) {
        freqMap[oldVal]--;
        freqMap[newVal]++;
    }

    int countPairs(vector<int>& vec, unordered_map<int, int>& freqMap, int sum) {
        int count = 0;

        for (int i = 0; i < vec.size(); i++) {
            count += freqMap[sum - vec[i]];
        }

        return count;
    }

   public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this->vec1 = nums1;
        this->vec2 = nums2;
        this->freqMap2 = buildFreqMap(nums2);
    }

    void add(int index, int val) {
        int crrVal = this->vec2[index];
        int newVal = crrVal + val;

        this->vec2[index] = newVal;
        updateFreqMap(this->freqMap2, crrVal, newVal);
    }

    int count(int tot) {
        return countPairs(this->vec1, this->freqMap2, tot);
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
