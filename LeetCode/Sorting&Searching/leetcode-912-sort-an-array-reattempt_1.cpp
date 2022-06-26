// LeetCode-912: https://leetcode.com/problems/sort-an-array/

// merge-sort
// given the constraints, can also be solved by counting-sort

#include <vector>
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    void showVec(vector<int>& vec, string name, int lo, int hi) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = lo; i <= hi; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = lo; i <= hi; i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    void showVec(vector<int>& vec, string name) {
        int len = vec.size();
        showVec(vec, name, 0, len - 1);
    }

    void mergeSort(vector<int>& vec, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 1) {
            return;
        }

        int mid = (lo + hi) / 2;
        mergeSort(vec, lo, mid);
        mergeSort(vec, mid + 1, hi);

        if (debug) {
            printf("before merging vec[lo=%d] .. vec[hi=%d]\n", lo, hi);
            showVec(vec, "vec", lo, hi);
        }

        merge(vec, lo, hi);
        if (debug) {
            printf("after merging vec[lo=%d] .. vec[hi=%d]\n", lo, hi);
            showVec(vec, "vec", lo, hi);
        }
    }

    void merge(vector<int>& vec, int lo, int hi) {
        int len = hi - lo + 1;
        vector<int> tmpVec(len);

        int mid = (lo + hi) / 2;

        // perform merge
        int i1 = lo;
        int i2 = mid + 1;
        int j = 0;
        while ((i1 <= mid) && (i2 <= hi)) {
            if (vec[i1] <= vec[i2]) {
                tmpVec[j++] = vec[i1++];
            } else {
                tmpVec[j++] = vec[i2++];
            }
        }

        // copy remaining un-merged items from first half
        while (i1 <= mid) {
            tmpVec[j++] = vec[i1++];
        }
        // copy remaining un-merged items from second half
        while (i2 <= hi) {
            tmpVec[j++] = vec[i2++];
        }

        if (debug) {
            showVec(tmpVec, "tmpVec");
        }

        // copy back
        j = 0;
        for (int i = lo; i <= hi; i++) {
            vec[i] = tmpVec[j++];
        }

        if (debug) {
            showVec(vec, "vec", lo, hi);
        }
    }

public:
    friend class SolutionTest;

    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return nums;
        }

        mergeSort(nums, 0, len - 1);
        return nums;
    }
};

class SolutionTest {
public:
    void testSortArray() {
        Solution soln = Solution();
        vector<int> numsIn;
        vector<int> numsOutExpected;

//        soln.debug = true;
        numsIn = {5, 2, 3, 1};
//        soln.showVec(numsIn, "numsIn");
        soln.sortArray(numsIn);
        numsOutExpected = {1, 2, 3, 5};
//        soln.showVec(numsOutExpected, "numsOutExpected");
//        soln.showVec(numsIn, "numsOutComputed");
        assert(numsOutExpected == numsIn);
//        soln.debug = false;

        numsIn = {5, 1, 1, 2, 0, 0};
        soln.sortArray(numsIn);
        numsOutExpected = {0, 0, 1, 1, 2, 5};
        assert(numsOutExpected == numsIn);

        numsIn = {5, 1};
        soln.sortArray(numsIn);
        numsOutExpected = {1, 5};
        assert(numsOutExpected == numsIn);

        numsIn = {1, 5};
        soln.sortArray(numsIn);
        numsOutExpected = {1, 5};
        assert(numsOutExpected == numsIn);

        numsIn = {5, 5};
        soln.sortArray(numsIn);
        numsOutExpected = {5, 5};
        assert(numsOutExpected == numsIn);

        numsIn = {5};
        soln.sortArray(numsIn);
        numsOutExpected = {5};
        assert(numsOutExpected == numsIn);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testSortArray();

    return 0;
}
