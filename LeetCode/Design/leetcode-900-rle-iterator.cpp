// LeetCode-900: https://leetcode.com/problems/rle-iterator/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class RLEIterator {
   private:
    vector<int> encoding;
    int idx1, idx2;

   public:
    RLEIterator(vector<int>& encoding) {
        this->encoding = encoding;
        this->idx1 = 0;
        this->idx2 = 0;
    }

    int next(int n) {
        int ctr = 0;
        int lastEle = -1;
        while ((this->idx1 < this->encoding.size() - 1) && (ctr < n)) {
            int crrEle = this->encoding[this->idx1 + 1];
            int crrFreq = this->encoding[this->idx1];
            int crrIdx = this->idx2;
            while ((ctr < n) && (crrIdx < crrFreq)) {
                ++ctr;
                ++crrIdx;
                lastEle = crrEle;
            }

            this->idx2 = crrIdx;
            if (crrIdx == crrFreq) {
                this->idx1 += 2;
                this->idx2 = 0;
            }

            if (ctr == n) {
                return lastEle;
            }
        }

        return -1;
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */
