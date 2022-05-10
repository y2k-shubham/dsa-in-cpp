// LeetCode-216: https://leetcode.com/problems/combination-sum-iii/

// simple backtracking; can skip looking

// as an optimization, pruning could have been applied at any level by checking if the path remaining to be explored would even be fruitful.
// that is if sum of all numbers from crrNum till maxNum (9) is still lesser than the required residual sum, then we can return early

#include <vector>

using namespace std;

class Solution {
private:
    void combSumRec(
        int reqSum,
        int reqNums,
        int maxNum,
        vector <vector <int> >& allCombs,
        int crrSum,
        int crrNum,
        vector <int>& crrComb
    ) {
        int lenCrr = crrComb.size();
        if ((lenCrr == reqNums) && (crrSum == reqSum)) {
            allCombs.push_back(crrComb);
            return;
        }
        if ((lenCrr > reqNums) || (crrSum > reqSum) || (crrNum > maxNum)) {
            return;
        }
        
        // recurse without including crrNum
        combSumRec(
            reqSum,
            reqNums,
            maxNum,
            allCombs,
            crrSum,
            crrNum + 1,
            crrComb
        );
        
        // recurse with including crrNum
        crrSum += crrNum;
        crrComb.push_back(crrNum);
        combSumRec(
            reqSum,
            reqNums,
            maxNum,
            allCombs,
            crrSum,
            crrNum + 1,
            crrComb
        );
        crrComb.pop_back();
    }
    
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector <vector <int> > allCombs;
        vector <int> crrComb;
        
        combSumRec(
            n, // reqSum
            k, // reqNums
            9, // maxSum
            allCombs,
            0, // crrSum
            1, // crrNum
            crrComb
        );
        
        return allCombs;
    }
};
