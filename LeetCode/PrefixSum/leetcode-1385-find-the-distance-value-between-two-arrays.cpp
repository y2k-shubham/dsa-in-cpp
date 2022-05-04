// LeetCode-1385: https://leetcode.com/problems/find-the-distance-value-between-two-arrays/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define MAX_VAL 1000
#define MIN_VAL -1000

class Solution {
private:
    vector<int> buildFreqVec(vector<int>& vec) {
        vector<int> freqVec(MAX_VAL - MIN_VAL + 1, 0);

        int offset = (int) abs(MIN_VAL);
        for (int i = 0; i < vec.size(); i++) {
            freqVec[vec[i] + offset]++;
        }

        return freqVec;
    }

    vector<int> buildPrefixSumVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> prefSumVec(len, 0);
        prefSumVec[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefSumVec[i] = prefSumVec[i - 1] + vec[i];
        }

        return prefSumVec;
    }

    int findNumValuesInRange(vector<int>& freqVec, int from, int to) {
        int offset = (int) abs(MIN_VAL);

        int preFromFreq = ((from + offset - 1) >= 0) ? freqVec[from + offset - 1] : 0;
        int toFreq = freqVec[to + offset];

        int numValsInRange = toFreq - preFromFreq;
        return numValsInRange;
    }

public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        vector<int> offsetFreqVec = buildFreqVec(arr2);
        vector<int> freqVecPrefSumVec = buildPrefixSumVec(offsetFreqVec);

        int distance = 0;
        for (int i = 0; i < arr1.size(); i++) {
            int crrVal = arr1[i];
            // IMPORTANT: this max / min capping is necessary to prevent SEGFAULT
            int from = max(crrVal - d, MIN_VAL);
            int to = min(crrVal + d, MAX_VAL);

            int numViolatingVals = findNumValuesInRange(
                    freqVecPrefSumVec,
                    from,
                    to
            );
            if (numViolatingVals == 0) {
                distance++;
            }
        }

        return distance;
    }
};

class SolutionTest {
public:
    void testFindTheDistanceValue() {
        Solution soln = Solution();
        vector<int> arr1In;
        vector<int> arr2In;
        int dIn;
        int outExpected, outComputed;

        arr1In = {4, 5, 8};
        arr2In = {10, 9, 1, 8};
        dIn = 2;
        outExpected = 2;
        outComputed = soln.findTheDistanceValue(arr1In, arr2In, dIn);
        assert(outExpected == outComputed);

        arr1In = {1, 4, 2, 3};
        arr2In = {-4, -3, 6, 10, 20, 30};
        dIn = 3;
        outExpected = 2;
        outComputed = soln.findTheDistanceValue(arr1In, arr2In, dIn);
        assert(outExpected == outComputed);

        arr1In = {2, 1, 100, 3};
        arr2In = {-5, -2, 10, -3, 7};
        dIn = 6;
        outExpected = 1;
        outComputed = soln.findTheDistanceValue(arr1In, arr2In, dIn);
        assert(outExpected == outComputed);

        arr1In = {-79, -199, -359, -184, -872, -869, 870, -351, 986, 231, 986, -67, -772, -488, -560, 607, 265, 593,
                  825, 111, 776, 409, -40, 355, -272, -470, -625, 109, -575, -371, -593, -496, -262, -834, 679, -425,
                  -817, 542, -83, -815, 335, 176, 317, -306, 926, -535, -201, 979, -372, -916, -330, -618, -352, 623,
                  734, 185, 829, 886, -380, -497, -316, -794, 114, 252, 185, 653, 220, -812, -499, -550, -959, 655,
                  -501, -178, -852, -452, 128, 776, -855, 493, -847, -956, 301, -980, -405, 537};
        arr2In = {622, -265, 10, -40, 766, 759, -685, -794, 26, 592, 628, -329, -843, 42, 944, 362, -646, -633, 589,
                  -694, -711, 682, 772, -346, -375, -782, 452, 53, 709, 882, 232, -399, -742, 830, -577, -710, 117, 864,
                  479, -935, 596, -353, 681, 849, 276, 646, 376, 857, 132, 721};
        dIn = 95;
        outExpected = 1;
        outComputed = soln.findTheDistanceValue(arr1In, arr2In, dIn);
        cout << outComputed << endl;
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindTheDistanceValue();

    return 0;
}
