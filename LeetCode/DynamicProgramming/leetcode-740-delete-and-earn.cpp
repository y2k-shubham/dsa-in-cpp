// LeetCode-740: https://leetcode.com/problems/delete-and-earn/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace int;

class Solution {
private:
    unordered_map <int, int> buildFreqMap(vector <int>& vec) {
        unordered_map <int, int> freqMap;
        
        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }
        
        return freqMap;
    }
    
    vector <pair <int, int> > convertToVec(unordered_map <int, int>& mMap) {
        vector <pair <int, int> > mVec(mMap.size());
        
        int i = 0;
        for (unordered_map <int, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            mVec[i++] = {it->first, it->second};
        }
        
        return mVec;
    }
    
    int calcMaxEarn(vector <pair <int, int> >& vec) {
        sort(vec.begin(), vec.end());
        
        int len = vec.size();
        vector <pair <int, int> > memoVec(len);
        
        int maxEarn = 0;
        for (int i = 0; i < len; i++) {
            int crrProd = vec[i].first * vec[i].second;
            
            int prevMaxContrib = (i == 0) ? 0 : max(memoVec[i - 1].first, memoVec[i - 1].second);
            int prevExcEarnContrib = 0;
            if (i > 0) {
                if (vec[i - 1].first == (vec[i].first - 1)) {
                    prevExcEarnContrib = memoVec[i - 1].first;
                } else {
                    prevExcEarnContrib = prevMaxContrib;
                }
            }
            int crrIncEarn = (i == 0) ? crrProd : (crrProd + prevExcEarnContrib);
            int crrExcEarn = prevMaxContrib;
            
            memoVec[i] = {crrExcEarn, crrIncEarn};
            maxEarn = max(maxEarn, max(crrIncEarn, crrExcEarn));
            
            // cout << endl;
            // printf("at vec[i=%d] = (%d: %d)\n", i, vec[i].first, vec[i].second);
            // printf("crrExcEarn=%d, crrIncEarn=%d\n", crrExcEarn, crrIncEarn);
        }
        
        return maxEarn;
    }
    
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map <int, int> freqMap = buildFreqMap(nums);
        vector <pair <int, int> > freqVec = convertToVec(freqMap);
        return calcMaxEarn(freqVec);
    }
};

