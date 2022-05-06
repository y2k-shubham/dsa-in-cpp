// LeetCode-1850: https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/
// this involves an application of LeetCode-31: https://leetcode.com/problems/next-permutation/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <list>
#include <cassert>

using namespace std;

class Solution {
private:
    ////////////
    // LeetCode-31 next-permutation code ::begin::
    ////////////

    bool debug = false;

    int findFirstDipIdxFromLeft(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return -1;
        }

        for (int i = len - 2; i >= 0; i--) {
            if (vec[i] < vec[i + 1]) {
                return i;
            }
        }

        return -1;
    }

    int findOptimalSwapIdxFromLeft(vector<int>& vec, int dipIdx) {
        int len = vec.size();
        if (len <= 1) {
            return -1;
        }

        if ((dipIdx >= len) || (0 > dipIdx)) {
            return -1;
        }

        int dipEle = vec[dipIdx];

        int smallestGreaterEle = INT_MAX;
        int smallestGreaterEleIdx = len;
        for (int i = dipIdx + 1; i < len; i++) {
            int crrEle = vec[i];
            if ((dipEle < crrEle) && (crrEle < smallestGreaterEle)) {
                smallestGreaterEle = crrEle;
                smallestGreaterEleIdx = i;
            }
        }

        return smallestGreaterEleIdx;
    }

    void swapEles(vector<int>& vec, int idx1, int idx2) {
        int tmp = vec[idx1];
        vec[idx1] = vec[idx2];
        vec[idx2] = tmp;
    }

    void debugOutput(vector<int>& vec, int dipIdx, int swapIdx) {
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

        printf("Dip:\t");
        if (dipIdx < 0) {
            printf("%d\n", dipIdx);
        } else {
            for (int i = 0; i < dipIdx; i++) {
                printf("\t");
            }
            cout << '^' << endl;
        }

        printf("Swap:\t");
        if (swapIdx < 0) {
            printf("%d\n", swapIdx);
        } else {
            for (int i = 0; i < swapIdx; i++) {
                printf("\t");
            }
            cout << '^' << endl;
        }
    }

    string convertToStr(vector<int>& vec) {
        if (vec.empty()) {
            return "";
        }

        ostringstream oss;
        oss << vec[0];

        for (int i = 1; i < vec.size(); i++) {
            oss << ',' << vec[i];
        }

        return oss.str();
    }

    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            if (debug) {
                printf("returning because length = %d <= 1\n", len);
            }

            return;
        }

        // find index of first such element from left
        // which is lesser than it's preceding element
        int dipIdx = findFirstDipIdxFromLeft(nums);
        if ((dipIdx < 0) || (len <= dipIdx)) {
            // we are already on greatest permutation

            // next permutation will be the smallest permutation
            // so just sort in ascending order
            sort(nums.begin(), nums.end());
            if (debug) {
                printf("returning smallest permutation = %s because we are already on greatest permutation\n",
                       convertToStr(nums).c_str());
            }

            return;
        }

        // find the index of smallest element on right of dipEle
        // which is still greater than dipEle
        int swapIdx = findOptimalSwapIdxFromLeft(nums, dipIdx);
        if ((swapIdx <= 0) || (swapIdx == dipIdx) || (swapIdx >= len)) {
            // should never happen (some bug in code)
            if (debug) {
                printf("returning because dipIdx = swapIdx = %d\n", dipIdx);
            }
            return;
        }

        if (debug) {
            debugOutput(nums, dipIdx, swapIdx);
        }

        // swap dipEle with swapEle
        swapEles(nums, dipIdx, swapIdx);

        // sort elements beyond dipIdx in ascending order
        sort(nums.begin() + dipIdx + 1, nums.end());
    }

    ////////////
    // LeetCode-31 next-permutation code ::end::
    ////////////

    void kthNextPermutation(vector<int>& vec, int k) {
        for (int i = 1; i <= k; i++) {
            nextPermutation(vec);
        }
    }

    vector<int> convertToVec(string& str) {
        int len = str.size();
        if (len == 0) {
            return {};
        }

        vector<int> vec(len);
        for (int i = 0; i < len; i++) {
            vec[i] = str.at(i) - '0';
        }

        return vec;
    }

    list<int> convertToList(vector<int>& vec) {
        list<int> mList(vec.begin(), vec.end());
        return mList;
    }

    list<int> convertToList(string& str) {
        vector<int> mVec = convertToVec(str);
        return convertToList(mVec);
    }

    int findSwaps(list<int>& targetList, list<int>& sourceList) {
        int targetListLen = targetList.size();
        int sourceListLen = sourceList.size();
        if (sourceListLen != targetListLen) {
            return INT_MAX;
        }
        if (targetList == sourceList) {
            return 0;
        }

        int numSwaps = 0;

        auto itTarget = targetList.begin();
        auto itSource = sourceList.begin();
        while (itTarget != targetList.end()) {
            if (*itTarget == *itSource) {
                // if elements are matching, no swaps to be made for current position
                itTarget++;
                itSource++;
                continue;
            }

            // search for required element (the current element in target list) in source list
            // find: https://stackoverflow.com/a/4604177/3679900
            auto itSourceReqEle = find(itSource, sourceList.end(), *itTarget);
            if (itSourceReqEle == sourceList.end()) {
                return INT_MAX;
            }

            // add no of swaps needed to bring required element to it's correct position
            // distance: https://stackoverflow.com/a/7702834/3679900
            int numSwapsCrrEle = distance(itSource, itSourceReqEle);
            numSwaps += numSwapsCrrEle;

            // remove the required element from the position we found it in
            sourceList.erase(itSourceReqEle);
            // the above is like mimicking the actual re-arranging of elements
            // while in reality we only removed the element from it's found position and never shifted any elements
            // of course this works because we only have to return the number of swaps

            itTarget++;
            // source iterator will NOT be moved as we are already standing at an element that hasn't been 'consumed' yet
        }

        return numSwaps;
    }

public:
    friend class SolutionTest;

    // barely accepted
    // LC-submission speed: 6 %tile, memory 12 %tile
    int getMinSwaps(string num, int k) {
        vector<int> orgVec = convertToVec(num);

        vector<int> kthNextPermVec = orgVec;
        kthNextPermutation(kthNextPermVec, k);

        list<int> orgList = convertToList(orgVec);
        list<int> kthNextPermList = convertToList(kthNextPermVec);

        int numSwaps = findSwaps(kthNextPermList, orgList);
        return numSwaps;
    }
};

class SolutionTest {
public:
    void testFindSwaps() {
        Solution soln = Solution();
        string sourceStrIn;
        string targetStrIn;
        list<int> sourceListIn;
        list<int> targetListIn;
        int numSwapsOutExpected, numSwapsOutComputed;

        targetListIn = {};
        sourceListIn = {};
        numSwapsOutExpected = 0;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        targetListIn = {4, 5, 5};
        sourceListIn = {4, 5, 5};
        numSwapsOutExpected = 0;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        targetListIn = {5, 4, 5};
        sourceListIn = {4, 5, 5};
        numSwapsOutExpected = 1;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        targetListIn = {5, 4, 8, 5};
        sourceListIn = {4, 5, 8, 5};
        numSwapsOutExpected = 1;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        targetListIn = {5, 4, 5, 8};
        sourceListIn = {4, 5, 8, 5};
        numSwapsOutExpected = 2;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        targetListIn = {8, 5, 5, 4};
        sourceListIn = {4, 5, 8, 5};
        // after moving 8 (2 swaps): 8, 4, 5, 5
        // after moving 5 (1 swap): 8, 5, 4, 5
        // after moving 5 (1 swap): 8, 5, 5, 4
        numSwapsOutExpected = 4;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        targetListIn = {8, 5, 5, 4};
        sourceListIn = {4, 5, 8, 5};
        // after moving 8 (2 swaps): 8, 4, 5, 5
        // after moving 5 (1 swap): 8, 5, 4, 5
        // after moving 5 (1 swap): 8, 5, 5, 4
        numSwapsOutExpected = 4;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        sourceStrIn = "5489355142";
        targetStrIn = "5489355421";
        targetListIn = soln.convertToList(targetStrIn);
        sourceListIn = soln.convertToList(sourceStrIn);
        numSwapsOutExpected = 2;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        sourceStrIn = "11112";
        targetStrIn = "21111";
        targetListIn = soln.convertToList(targetStrIn);
        sourceListIn = soln.convertToList(sourceStrIn);
        numSwapsOutExpected = 4;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);

        sourceStrIn = "00123";
        targetStrIn = "00132";
        targetListIn = soln.convertToList(targetStrIn);
        sourceListIn = soln.convertToList(sourceStrIn);
        numSwapsOutExpected = 1;
        numSwapsOutComputed = soln.findSwaps(targetListIn, sourceListIn);
        assert(numSwapsOutExpected == numSwapsOutComputed);
    }

    void testGetMinSwaps() {
        Solution soln = Solution();
        string numIn;
        int kIn;
        int swapsOutExpected, swapsOutComputed;

        numIn = "5489355142";
        kIn = 4;
        swapsOutExpected = 2;
        swapsOutComputed = soln.getMinSwaps(numIn, kIn);
        assert(swapsOutExpected == swapsOutComputed);

        numIn = "11112";
        kIn = 4;
        swapsOutExpected = 4;
        swapsOutComputed = soln.getMinSwaps(numIn, kIn);
        assert(swapsOutExpected == swapsOutComputed);

        numIn = "00123";
        kIn = 1;
        swapsOutExpected = 1;
        swapsOutComputed = soln.getMinSwaps(numIn, kIn);
        assert(swapsOutExpected == swapsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindSwaps();
    solnTest.testGetMinSwaps();

    return 0;
}
