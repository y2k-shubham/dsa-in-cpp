// LeetCode-2104: https://leetcode.com/problems/sum-of-subarray-ranges/

/**
 * elegant problem
 * - extension of LeetCode-907: https://leetcode.com/problems/sum-of-subarray-minimums/
 * - read explanation of LC-907 solution to understand solution of this problem (LC-2104): https://github.com/y2k-shubham/dsa-in-cpp/blob/master/LeetCode/NumberTheory/leetcode-907-sum-of-subarray-minimums.cpp
 */

/**
 * input
 * [1,2,3]
 * output
 * 4
 *
 * input
 * [1,3,3]
 * output
 * 4
 *
 * input
 * [4,-2,-3,4,1]
 * output
 * 59
 *
 * input
 * [7]
 * output
 * 0
 *
 * input
 * [7,2]
 * output
 * 5
 *
 * input
 * [9,-2,1]
 * output
 * 25
 *
 * input
 * [-20592,-83117,16783,-75446,-27276,84170,-31295,60725,40504,55534,69043,-66679,-37739,59243,33435,-54421,-28323,52328,88286,-8950,-83012,-56787,33721,32043,-82896,-14383,-83955,16283,-61726,-42147,61811,-85513,31713,-1515,73524,18560,83506,-52750,55842,-5015,16664,-61757,44559,-76619,-10654,-68067,-66325,-11056,-27075,-57573,-40458,-20842,-97777,66133,-37575,31086,75837,-41855,-25531,56400,-33690,-39164,66261,-21294,-12404,-33518,93478,71963,-11822,90390,-52285,21353,-84139,-29364,64014,-34432,-82059,-73154,-42019,-15953,-22827,-43816,-40779,-28328,-98246,85909,87644,-44864,-85428,-57242,-82063,33286,68152,-38673,69128,-156,63600,-1288,15353,88223,65697,15022,-43178,89189,49340,-78699,-42045,66750,-55751,16339,31898,-26805,-52744,41579,-51245,-50475,63095,74967,19004,-8199,-76578,-90525,-79107,-48494,131,-33587,23005,89521,-72712,1210,-95145,53575,-49158,-13969,10358,-21825,78978,70410,15822,-79109,39030,-26834,-935,-61020,-86144,59761,-83719,-34522,37703,-43117,39510,49971,82129,7888,13840,-68891,-4570,25392,36337,-61182,61456,46340,32956,-30114,85336,37163,88134,-13770,39635,76952,22120,-31433,31457,70979,11894,47119,-58116,-77836,-19079,-29708,17538,-18605,86884,64608,-49294,-15356,85231,20870,-23490,70947,76657,50403,28211,122,34434,-55828,-82124,39606,73883,22631,-55381,-49969,15555,-34013,-29094,20189,-87109,63481,2203,69698,-86994,-43637,-77345,-40796]
 * expected output
 * 4093888412
 * obtained output
 * 3093888405
 */

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    bool debug = false;

    void showVec(string name, vector<int>& nleRightIdxVec, vector<int>& valVec) {
        int len = nleRightIdxVec.size();

        printf("Idx:\t\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", valVec[i]);
        }
        cout << endl;

        printf("%s-Idx:\t", name.c_str());
        for (int i = 0; i < len; i++) {
            printf("%d\t", nleRightIdxVec[i]);
        }
        cout << endl;

        printf("%s-Val:\t", name.c_str());
        for (int i = 0; i < len; i++) {
            printf("%d\t", ((nleRightIdxVec[i] < len) ? valVec[nleRightIdxVec[i]] : -1));
        }
        cout << endl;
    }

    vector<int> buildNleLeftVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> nleRightVec(len, -1);

        stack<int> stk;
        for (int i = 0; i < len; i++) {
            int crrEle = vec[i];
            // note that here we DONT take equality
            while (!stk.empty() && (vec[stk.top()] > crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleRightVec[i] = stk.top();
            }

            stk.push(i);
        }

        return nleRightVec;
    }

    vector<int> buildNleRightVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> nleRightVec(len, len);

        stack<int> stk;
        for (int i = len - 1; i >= 0; i--) {
            int crrEle = vec[i];
            // note that here we DO take equality
            while (!stk.empty() && (vec[stk.top()] >= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleRightVec[i] = stk.top();
            }

            stk.push(i);
        }

        return nleRightVec;
    }

    long long findSubarrsMinSum(
        vector<int>& vec,
        vector<int>& nleLeftVec,
        vector<int>& nleRightVec) {
        int len = vec.size();

        long long sum = 0;
        for (int i = 0; i < len; i++) {
            int crrEleVal = vec[i];

            int nleLeftIdx = nleLeftVec[i];
            // if ((nleLeftIdx >= 0) && (vec[nleLeftIdx] == crrEleVal)) {
            //     nleLeftIdx++;
            // }
            int nleRightIdx = nleRightVec[i];

            int numSubarrs = (i - nleLeftIdx) * (nleRightIdx - i);
            long long crrEleSumContrib = numSubarrs * ((long long)crrEleVal);

            if (this->debug) {
                printf(
                    "at vec[i=%d]=%d, nleLIdx=%d, nleRIdx=%d, numSubarrs=%d, contrib=%lld\n",
                    i,
                    crrEleVal,
                    nleLeftIdx,
                    nleRightIdx,
                    numSubarrs,
                    crrEleSumContrib);
            }

            sum += crrEleSumContrib;
            // sum %= MOD;
        }

        return sum;
    }

    vector<int> buildNgeLeftVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> ngeRightVec(len, -1);

        stack<int> stk;
        for (int i = 0; i < len; i++) {
            int crrEle = vec[i];
            // note that here we DONT take equality
            while (!stk.empty() && (vec[stk.top()] < crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeRightVec[i] = stk.top();
            }

            stk.push(i);
        }

        return ngeRightVec;
    }

    vector<int> buildNgeRightVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> ngeRightVec(len, len);

        stack<int> stk;
        for (int i = len - 1; i >= 0; i--) {
            int crrEle = vec[i];
            // note that here we DO take equality
            while (!stk.empty() && (vec[stk.top()] <= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeRightVec[i] = stk.top();
            }

            stk.push(i);
        }

        return ngeRightVec;
    }

    long long findSubarrsMaxSum(
        vector<int>& vec,
        vector<int>& ngeLeftVec,
        vector<int>& ngeRightVec) {
        int len = vec.size();

        long long sum = 0;
        for (int i = 0; i < len; i++) {
            int crrEleVal = vec[i];

            int nleLeftIdx = ngeLeftVec[i];
            // if ((nleLeftIdx >= 0) && (vec[nleLeftIdx] == crrEleVal)) {
            //     nleLeftIdx++;
            // }
            int nleRightIdx = ngeRightVec[i];

            int numSubarrs = (i - nleLeftIdx) * (nleRightIdx - i);
            long long crrEleSumContrib = numSubarrs * ((long long)crrEleVal);

            if (this->debug) {
                printf(
                    "at vec[i=%d]=%d, nleLIdx=%d, nleRIdx=%d, numSubarrs=%d, contrib=%lld\n",
                    i,
                    crrEleVal,
                    nleLeftIdx,
                    nleRightIdx,
                    numSubarrs,
                    crrEleSumContrib);
            }

            sum += crrEleSumContrib;
            // sum %= MOD;
        }

        return sum;
    }

   public:
    friend class SolutionTest;

    long long subArrayRanges(vector<int>& arr) {
        int len = arr.size();
        if (len <= 1) {
            return 0;
        }

        vector<int> nleLeftVec = buildNleLeftVec(arr);
        vector<int> nleRightVec = buildNleRightVec(arr);
        // showVec("nleLeft", nleLeftVec, arr);
        // showVec("nleRight", nleRightVec, arr);

        vector<int> ngeLeftVec = buildNgeLeftVec(arr);
        vector<int> ngeRightVec = buildNgeRightVec(arr);
        // showVec("ngeLeft", ngeLeftVec, arr);
        // showVec("ngeRight", ngeRightVec, arr);

        return findSubarrsMaxSum(arr, ngeLeftVec, ngeRightVec) - findSubarrsMinSum(arr, nleLeftVec, nleRightVec);
    }
};

class SolutionTest {
   public:
    void testFindSubarrsMinSum() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecNleLeftIn, vecNleRightIn;
        long long sumOutExpected, sumOutComputed;

        vecIn = {};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 0;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {5};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 5;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {9, 19};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 37;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {3, 1, 2, 4};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 17;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {11, 81, 94, 43, 3};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 444;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        // soln.debug = true;
        vecIn = {71, 55, 82, 55};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 593;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);
        // soln.debug = false;

        vecIn = {5, 5, 3, 1, 1, 1, 9, 8, 2};
        vecNleLeftIn = soln.buildNleLeftVec(vecIn);
        vecNleRightIn = soln.buildNleRightVec(vecIn);
        sumOutExpected = 88;
        sumOutComputed = soln.findSubarrsMinSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);
    }

    void testFindSubarrsMaxSum() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecNleLeftIn, vecNleRightIn;
        long long sumOutExpected, sumOutComputed;

        vecIn = {};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 0;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {5};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 5;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {9, 19};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 47;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {3, 1, 2, 4};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 30;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {11, 81, 94, 43, 3};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 1108;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);

        // soln.debug = true;
        vecIn = {71, 55, 82, 55};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 744;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);
        // soln.debug = false;

        vecIn = {5, 5, 3, 1, 1, 1, 9, 8, 2};
        vecNleLeftIn = soln.buildNgeLeftVec(vecIn);
        vecNleRightIn = soln.buildNgeRightVec(vecIn);
        sumOutExpected = 280;
        sumOutComputed = soln.findSubarrsMaxSum(vecIn, vecNleLeftIn, vecNleRightIn);
        assert(sumOutExpected == sumOutComputed);
    }

    void testSubArrayRanges() {
        Solution soln = Solution();
        vector<int> vecIn;
        long long sumOutExpected, sumOutComputed;

        vecIn = {};
        sumOutExpected = 0;
        sumOutComputed = soln.subArrayRanges(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {1, 2, 3};
        sumOutExpected = 4;
        sumOutComputed = soln.subArrayRanges(vecIn);

        assert(sumOutExpected == sumOutComputed);

        vecIn = {1, 3, 3};
        sumOutExpected = 4;
        sumOutComputed = soln.subArrayRanges(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {4, -2, -3, 4, 1};
        sumOutExpected = 59;
        sumOutComputed = soln.subArrayRanges(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {-20592, -83117, 16783, -75446, -27276, 84170, -31295, 60725, 40504, 55534, 69043, -66679, -37739, 59243, 33435, -54421, -28323, 52328, 88286, -8950, -83012, -56787, 33721, 32043, -82896, -14383, -83955, 16283, -61726, -42147, 61811, -85513, 31713, -1515, 73524, 18560, 83506, -52750, 55842, -5015, 16664, -61757, 44559, -76619, -10654, -68067, -66325, -11056, -27075, -57573, -40458, -20842, -97777, 66133, -37575, 31086, 75837, -41855, -25531, 56400, -33690, -39164, 66261, -21294, -12404, -33518, 93478, 71963, -11822, 90390, -52285, 21353, -84139, -29364, 64014, -34432, -82059, -73154, -42019, -15953, -22827, -43816, -40779, -28328, -98246, 85909, 87644, -44864, -85428, -57242, -82063, 33286, 68152, -38673, 69128, -156, 63600, -1288, 15353, 88223, 65697, 15022, -43178, 89189, 49340, -78699, -42045, 66750, -55751, 16339, 31898, -26805, -52744, 41579, -51245, -50475, 63095, 74967, 19004, -8199, -76578, -90525, -79107, -48494, 131, -33587, 23005, 89521, -72712, 1210, -95145, 53575, -49158, -13969, 10358, -21825, 78978, 70410, 15822, -79109, 39030, -26834, -935, -61020, -86144, 59761, -83719, -34522, 37703, -43117, 39510, 49971, 82129, 7888, 13840, -68891, -4570, 25392, 36337, -61182, 61456, 46340, 32956, -30114, 85336, 37163, 88134, -13770, 39635, 76952, 22120, -31433, 31457, 70979, 11894, 47119, -58116, -77836, -19079, -29708, 17538, -18605, 86884, 64608, -49294, -15356, 85231, 20870, -23490, 70947, 76657, 50403, 28211, 122, 34434, -55828, -82124, 39606, 73883, 22631, -55381, -49969, 15555, -34013, -29094, 20189, -87109, 63481, 2203, 69698, -86994, -43637, -77345, -40796};
        sumOutExpected = 4093888412;
        sumOutComputed = soln.subArrayRanges(vecIn);
        assert(sumOutExpected == sumOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindSubarrsMinSum();
    solnTest.testFindSubarrsMaxSum();
    solnTest.testSubArrayRanges();

    return 0;
}
