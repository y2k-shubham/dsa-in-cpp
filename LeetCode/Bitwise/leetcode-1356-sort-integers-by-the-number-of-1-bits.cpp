// LeetCode-1356: https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/

#include <utility>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    int countSetBits(int n) {
        int count = 0;
        for (int i = 0; i < 14; i++) {
            if ((n & (1 << i)) != 0) {
                count++;
            }
        }

        return count;
    }

    vector<pair<int, int> > convertToBitsValuePairs(vector<int>& vec) {
        int len = vec.size();
        vector<pair<int, int> > bitsValuePairsVec(len);

        for (int i = 0; i < len; i++) {
            bitsValuePairsVec[i] = make_pair(countSetBits(vec[i]), vec[i]);
        }

        return bitsValuePairsVec;
    }

    vector<int> convertToIntegers(vector<pair<int, int> >& vec) {
        int len = vec.size();
        vector<int> integersVec(len);

        for (int i = 0; i < len; i++) {
            integersVec[i] = vec[i].second;
        }

        return integersVec;
    }

public:
    friend class SolutionTest;

    vector<int> sortByBits(vector<int>& arr) {
        if (arr.size() <= 1) {
            return arr;
        }

        vector<pair<int, int> > bitsValuePairsVec = convertToBitsValuePairs(arr);

        sort(bitsValuePairsVec.begin(), bitsValuePairsVec.end());

        vector<int> integersVec = convertToIntegers(bitsValuePairsVec);
        return integersVec;
    }
};

class SolutionTest {
public:
    void testCountSetBits() {
        Solution soln = Solution();
        int n;
        int outExpected, outComputed;

        n = 0;
        outExpected = 0;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 1;
        outExpected = 1;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 2;
        outExpected = 1;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 3;
        outExpected = 2;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 4;
        outExpected = 1;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 5;
        outExpected = 2;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 6;
        outExpected = 2;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);

        n = 10000;
        outExpected = 5;
        outComputed = soln.countSetBits(n);
        assert(outExpected == outComputed);
    }

    void testSortByBits() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected, vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.sortByBits(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {8};
        vecOutExpected = {8};
        vecOutComputed = soln.sortByBits(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {8, 9};
        vecOutExpected = {8, 9};
        vecOutComputed = soln.sortByBits(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {9, 8};
        vecOutExpected = {8, 9};
        vecOutComputed = soln.sortByBits(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {8, 9, 4};
        vecOutExpected = {4, 8, 9};
        vecOutComputed = soln.sortByBits(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCountSetBits();
    solnTest.testSortByBits();

    return 0;
}
