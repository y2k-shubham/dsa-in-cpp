// LeetCode-1636: https://leetcode.com/problems/sort-array-by-increasing-frequency/
// incomplete: mis-understood the question (and too lame a question to correct)
// extremely dumb question; please don't attempt

#include <vector>
#include <cassert>
#include <utility>
#include <list>

using namespace std;

#define MIN_VAL -100
#define MAX_VAL 100

class Solution {
private:
    bool debug = false;

    // unused
    list<int> findVecDiff(vector<int>& vec1, vector<int>& vec2) {
        list<int> diffIdxs;

        for (int i = 0; i < vec1.size(); i++) {
            if (vec1[i] != vec2[i]) {
                diffIdxs.push_back(i);
            }
        }

        return diffIdxs;
    }

    // unused
    void showVecDiff(vector<int>& vec1, vector<int>& vec2) {
        list<int> diffIdxs = findVecDiff(vec1, vec2);

        printf("vec diffs are:-\n");
        for (auto it = diffIdxs.begin(); it != diffIdxs.end(); it++) {
            printf("at [%d], vec1=%d & vec2=%d\n", *it, vec1[*it], vec2[*it]);
        }
    }

    vector<int> buildFreqVec(vector<int>& vec) {
        int freqVecLen = MAX_VAL - MIN_VAL + 1;

        vector<int> freqVec(freqVecLen);
        if (vec.empty()) {
            return freqVec;
        }

        for (auto it = vec.begin(); it != vec.end(); it++) {
            freqVec[*it - MIN_VAL]++;
        }

        return freqVec;
    }

    void fillVecWithFreqVec(vector<int>& vec, vector<int>& freqVec) {
        int freqVecLen = MAX_VAL - MIN_VAL + 1;
        int vecLen = vec.size();

        int idxHi = vecLen - 1;
        for (int i = MIN_VAL; i <= MAX_VAL; i++) {
            int offsetEle = i - MIN_VAL;
            int offsetEleFreq = freqVec[offsetEle];

            if (offsetEleFreq <= 0) {
                continue;
            }

            for (int j = 0; j < offsetEleFreq; j++) {
                vec[idxHi--] = i;
            }

            if (idxHi >= vecLen) {
                break;
            }
        }
    }

public:
    friend class SolutionTest;

    vector<int> frequencySort(vector<int>& nums) {
        vector<int> freqVec = buildFreqVec(nums);
        fillVecWithFreqVec(nums, freqVec);

        return nums;
    }
};

class SolutionTest {
public:
    void testBuildFreqVec() {
        Solution soln = Solution();
        vector<int> vecIn;
        int freqVecLen = MAX_VAL - MIN_VAL + 1;
        vector<int> freqVecOutExpected(freqVecLen, 0);
        vector<int> freqVecOutComputed;

        vecIn = {1, 1, 2, 2, 2, 3};
        fill(freqVecOutExpected.begin(), freqVecOutExpected.end(), 0);
        freqVecOutExpected[1 - MIN_VAL] = 2;
        freqVecOutExpected[2 - MIN_VAL] = 3;
        freqVecOutExpected[3 - MIN_VAL] = 1;
        freqVecOutComputed = soln.buildFreqVec(vecIn);
//        soln.showVecDiff(freqVecOutExpected, freqVecOutComputed);
        assert(freqVecOutExpected == freqVecOutComputed);

        vecIn = {2, 3, 1, 3, 2};
        fill(freqVecOutExpected.begin(), freqVecOutExpected.end(), 0);
        freqVecOutExpected[1 - MIN_VAL] = 1;
        freqVecOutExpected[2 - MIN_VAL] = 2;
        freqVecOutExpected[3 - MIN_VAL] = 2;
        freqVecOutComputed = soln.buildFreqVec(vecIn);
//        soln.showVecDiff(freqVecOutExpected, freqVecOutComputed);
        assert(freqVecOutExpected == freqVecOutComputed);

        vecIn = {-1, 1, -6, 4, 5, -6, 1, 4, 1};
        fill(freqVecOutExpected.begin(), freqVecOutExpected.end(), 0);
        freqVecOutExpected[-6 - MIN_VAL] = 2;
        freqVecOutExpected[-1 - MIN_VAL] = 1;
        freqVecOutExpected[1 - MIN_VAL] = 3;
        freqVecOutExpected[4 - MIN_VAL] = 2;
        freqVecOutExpected[5 - MIN_VAL] = 1;
        freqVecOutComputed = soln.buildFreqVec(vecIn);
//        soln.showVecDiff(freqVecOutExpected, freqVecOutComputed);
        assert(freqVecOutExpected == freqVecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildFreqVec();

    return 0;
}
