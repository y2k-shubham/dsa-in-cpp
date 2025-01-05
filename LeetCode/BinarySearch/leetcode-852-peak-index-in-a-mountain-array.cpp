// LeetCode-852: https://leetcode.com/problems/peak-index-in-a-mountain-array/

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    inline bool isIncreasingIdx(vector <int>& vec, int idx) {
        int len = vec.size();

        if (idx == 0) {
            return vec[0] < vec[1];
        }
        if (idx == len - 1) {
            return vec[len - 2] < vec[len - 1];
        }

        return vec[idx - 1] < vec[idx] && vec[idx] < vec[idx + 1];
    }

    inline bool isDecreasingIdx(vector <int>& vec, int idx) {
        int len = vec.size();

        if (idx == 0) {
            return vec[0] > vec[1];
        }
        if (idx == len - 1) {
            return vec[len - 2] > vec[len - 1];
        }

        return vec[idx - 1] > vec[idx] && vec[idx] > vec[idx + 1];
    }

    inline bool isPeakIdx(vector <int>& vec, int idx) {
        int len = vec.size();

        if (idx == 0 || idx == len - 1) {
            return false;
        }

        return isIncreasingIdx(vec, idx - 1) && isDecreasingIdx(vec, idx + 1);
    }

    int findPeakIdxRec(vector <int>& vec, int lo, int hi) {
        int len = vec.size();
        int mid = (lo + hi) / 2;

        if (isPeakIdx(vec, mid)) {
            return mid;
        } else if (isIncreasingIdx(vec, mid)) {
            return findPeakIdxRec(vec, mid, hi);
        } else if (isDecreasingIdx(vec, mid)) {
            return findPeakIdxRec(vec, lo, mid);
        } else {
            throw invalid_argument("Unexpected error occurred");
        }
    }

public:
    int peakIndexInMountainArray(vector <int>& arr) {
        int len = arr.size();
        if (len < 3) {
            throw invalid_argument("Array length must be at least 3");
        }

        return findPeakIdxRec(arr, 0, len - 1);
    }
};

class SolutionTest {
public:
    void testPeakIndexInMountainArray() {
        Solution soln = Solution();
        vector <int> vecIn;
        int idxOutExpected, idxOutComputed;

        vecIn = {0, 1, 0};
        idxOutExpected = 1;
        idxOutComputed = soln.peakIndexInMountainArray(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {0, 2, 1, 0};
        idxOutExpected = 1;
        idxOutComputed = soln.peakIndexInMountainArray(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {0, 10, 5, 2};
        idxOutExpected = 1;
        idxOutComputed = soln.peakIndexInMountainArray(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {0, 3, 10, 5, 2};
        idxOutExpected = 2;
        idxOutComputed = soln.peakIndexInMountainArray(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {0, 3, 10, 2};
        idxOutExpected = 2;
        idxOutComputed = soln.peakIndexInMountainArray(vecIn);
        assert(idxOutExpected == idxOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testPeakIndexInMountainArray();

    return 0;
}
