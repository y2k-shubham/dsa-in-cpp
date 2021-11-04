// LeetCode-1352: https://leetcode.com/problems/product-of-the-last-k-numbers/
// almost brute force; gives TLE

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_LEN 40000

class ProductOfNumbers {
   private:
    int lastZeroIdx;
    int lastIdx;
    vector<int> nums;

   public:
    ProductOfNumbers() {
        this->lastZeroIdx = -1;
        this->lastIdx = -1;

        vector<int> nums(MAX_LEN, -1);
        this->nums = nums;
    }

    void add(int num) {
        ++this->lastIdx;

        if (num == 0) {
            this->lastZeroIdx = this->lastIdx;
        }
        this->nums[this->lastIdx] = num;
    }

    int getProduct(int k) {
        int startIdx = this->lastIdx - k + 1;
        if (startIdx <= this->lastZeroIdx) {
            return 0;
        }

        int prod = 1;
        int idx = this->lastIdx;
        for (int i = 1; i <= k; i++, idx--) {
            prod *= this->nums[idx];
        }

        return prod;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
