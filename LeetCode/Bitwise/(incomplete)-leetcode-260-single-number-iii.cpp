// LeetCode-260: https://leetcode.com/problems/single-number-iii/
// AlgorithmsMadeEasy: https://www.youtube.com/watch?v=paeDhLD814E
// incomplete: fails in cases when XOR of original input set of numbers given zero
// (but then, is such a test-case even legit?)

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <list>

using namespace std;

class Solution {
private:
    int calcXor(vector <int>& vec) {
        int _xor = 0;
        
        for (vector <int>::iterator it = vec.begin(); it != vec.end(); it++) {
            _xor ^= *it;
        }
        
        return _xor;
    }
    
    int calcXor(list <int>& mList) {
        int _xor = 0;
        
        for (list <int>::iterator it = mList.begin(); it != mList.end(); it++) {
            _xor ^= *it;
        }
        
        return _xor;
    }
    
    int findFirstSetBitIdx(int val) {
        int idx;
        for (idx = 0; idx <= 31; idx++) {
            if ((val & (1 << idx)) > 0) {
                return idx;
            }
        }
        
        return -1;
    }
    
    pair <list <int>, list <int> > segregateNumsByBit(vector <int>& vec, int idx) {
        list <int> unsetBitNums;
        list <int> setBitNums;
        
        unsigned int bitMask = 1 << idx;
        for (vector <int>::iterator it = vec.begin(); it != vec.end(); it++) {
            if ((*it & bitMask) > 0) {
                setBitNums.push_back(*it);
            } else {
                unsetBitNums.push_back(*it);
            }
        }
        
        return {unsetBitNums, setBitNums};
    }
    
public:
    vector<int> singleNumber(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) {
            return {};
        }
        if (len == 2) {
            return nums;
        }
        
        int _xor = calcXor(nums);
        int firstSetBitIdx = findFirstSetBitIdx(_xor);
        
        pair <list <int>, list <int> > segregatedNums = segregateNumsByBit(nums, firstSetBitIdx);
        
        int num1 = calcXor(segregatedNums.first);
        int num2 = calcXor(segregatedNums.second);
        
        return {num1, num2};
    }
};
