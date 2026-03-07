// LeetCode-487: https://leetcode.com/problems/max-consecutive-ones-ii/
// Linear but slow
// Runtime: bottom 6.25 %tile, Memory: bottom 5.98 %tile

#include <vector>
#include <iostream>

using namespace std;

class Solution {
private:
    bool debug = false;

    vector <int> create1SeqOnLeftLenVec(vector<int>& vec) {
        int len = vec.size();
        if (len <= 0) {
            return {};
        }

        vector <int> _1SeqOnLeftLenVec(len, 0);
        int crr1SeqOnLeftLen = 0;
        for (int i = 0; i < len; i++) {
            if (vec[i] == 1) {
                crr1SeqOnLeftLen++;
            } else {
                crr1SeqOnLeftLen = 0;
            }

            _1SeqOnLeftLenVec[i] = crr1SeqOnLeftLen;
        }

        return _1SeqOnLeftLenVec;
    }

    vector <int> create1SeqOnRightLenVec(vector<int>& vec) {
        int len = vec.size();
        if (len <= 0) {
            return {};
        }

        vector <int> _1SeqOnRightLenVec(len, 0);
        int crr1SeqOnRightLen = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (vec[i] == 1) {
                crr1SeqOnRightLen++;
            } else {
                crr1SeqOnRightLen = 0;
            }

            _1SeqOnRightLenVec[i] = crr1SeqOnRightLen;
        }

        return _1SeqOnRightLenVec;
    }

    void showVec(vector<int>& vec, string name) {
        printf("%s vector is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int len = nums.size();

        vector<int> _1SeqOnLeftLenVec = create1SeqOnLeftLenVec(nums);
        vector<int> _1SeqOnRightLenVec = create1SeqOnRightLenVec(nums);

        if (debug) {
            showVec(_1SeqOnLeftLenVec, "_1SeqOnLeftLenVec");
            showVec(_1SeqOnRightLenVec, "_1SeqOnRightLenVec");
        }

        int maxPossible1SeqLen = 0;
        for (int i = 0; i < len; i++) {
            int _crr1SeqOnLeftLen = (i == 0) ? 0 : _1SeqOnLeftLenVec[i - 1];
            int _crr1SeqOnRightLen = (i == (len - 1)) ? 0 : _1SeqOnRightLenVec[i + 1];
            int _crrPossible1SeqLen = _crr1SeqOnLeftLen + 1 + _crr1SeqOnRightLen;

            if (debug) {
                printf("at vec[i=%d] = %d, _crr1SeqOnLeftLen=%d, _crr1SeqOnRightLen=%d, _crrPossible1SeqLen=%d\n",
                       i, nums[i], _crr1SeqOnLeftLen, _crr1SeqOnRightLen, _crrPossible1SeqLen);
            }

            maxPossible1SeqLen = max(maxPossible1SeqLen, _crrPossible1SeqLen);
        }

        return maxPossible1SeqLen;
    }
};