// LeetCode-2099: https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
private:
    vector<pair<int, int> > buildEleIdxVec(vector<int>& vec) {
        vector<pair<int, int> > eleIdxVec(vec.size());

        for (int i = 0; i < vec.size(); i++) {
            eleIdxVec[i] = make_pair(vec[i], i);
        }

        return eleIdxVec;
    }

    vector<int> buildVecFromIdx(vector<int>& vec, vector<pair<int, int> >& eleIdxVec) {
        vector<int> resultVec(eleIdxVec.size());

        for (int i = 0; i < eleIdxVec.size(); i++) {
            resultVec[i] = vec[eleIdxVec[i].second];
        }

        return resultVec;
    }

public:
    friend class SolutionTest;

    vector<int> maxSubsequence(vector<int>& nums, int k) {
        // build vector of {element, index} pairs
        vector<pair<int, int> > eleIdxVec = buildEleIdxVec(nums);
        // sort the vector in descending order
        sort(eleIdxVec.begin(), eleIdxVec.end(), greater<pair<int, int> >());

        // take first k elements of vector
        vector<pair<int, int>> eleIdxVecTopK(eleIdxVec.begin(), eleIdxVec.begin() + k);

        // calculate sum of first k elements
        int sumTopK = 0;
        for (vector<pair<int, int>>::iterator it = eleIdxVecTopK.begin(); it != eleIdxVecTopK.end(); it++) {
            sumTopK += it->first;
        }

        // sort the vector in ascending order of index
        sort(eleIdxVecTopK.begin(), eleIdxVecTopK.end(), [](auto &left, auto &right) {
            return left.second < right.second;
        });

        // return topmost k values
        return buildVecFromIdx(nums, eleIdxVecTopK);
    }
};

class SolutionTest {
public:

};

int main() {
    SolutionTest soln = SolutionTest();

    return 0;
}
