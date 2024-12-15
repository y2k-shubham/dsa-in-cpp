// LeetCode-2762: https://leetcode.com/problems/continuous-subarrays/
// incomplete
// NOT an easy problem: just too many edge cases

#include <vector>
#include <map>
#include <cassert>

using namespace std;

#define MAX_DIFF 2

class Solution {
private:
    void showMap(map <int, int>& freqMap) {
        printf("freqMap is:-\n");
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            printf("[%d]: %d\n", it->first, it->second);
        }
        printf("\n");
    }

    inline long long hcf(long long big, long long small) {
        long long rem = big % small;
        if (rem == 0) {
            return small;
        }

        return hcf(small, rem);
    }

    inline long long nCr(long long n, long long r) {
        r = min(r, n - r);

        long long numr = 1;
        long long denr = 1;
        while (r >= 1) {
            numr *= n;
            denr *= r;

            long long gcd = hcf(numr, denr);
            numr /= gcd;
            denr /= gcd;

            n--;
            r--;
        }

        return numr / denr;
    }

    inline void subtractFreq(map <int, int>& freqMap, int val) {
        freqMap[val]--;
        if (freqMap[val] == 0) {
            freqMap.erase(val);
        }
    }

    inline bool isOutOfRange(pair <int, int> range) {
        return (range.second - range.first) > MAX_DIFF;
    }

    inline bool isOutOfRange(map <int, int>& freqMap) {
        return isOutOfRange(findRange(freqMap));
    }

    inline pair <int, int> findRange(map <int, int>& freqMap) {
        if (freqMap.empty()) {
            return {-1, -1};
        }

        int minVal = freqMap.begin()->first;
        int maxVal = freqMap.rbegin()->first;

        return {minVal, maxVal};
    }

    inline int expandWindowTillDiffPermissible(vector <int>& vec, int iHi, map <int, int>& freqMap) {
        int len = vec.size();

        if (isOutOfRange(freqMap) || (iHi >= (len - 1))) {
            // already out of range
            return iHi;
        }

        iHi++;
        do {
            int val = vec[iHi];
            freqMap[val]++;

            if (isOutOfRange(freqMap)) {
                printf("at vec[iHi=%d] = %d; breaking as we went outOfRange\n", iHi, val);
                showMap(freqMap);
                break;
            } else {
                printf("at vec[iHi=%d] = %d; not-breaking yet\n", iHi, val);
                showMap(freqMap);
            }

            iHi++;
        } while (iHi < len);

        return iHi;
    }

    inline int shrinkWindowTillDiffExcessive(vector <int>& vec, int iLo, map <int, int>& freqMap) {
        int len = vec.size();

        if (!isOutOfRange(freqMap) || (iLo >= (len - 1))) {
            // already in range
            return iLo;
        }

        while (iLo < len) {
            int val = vec[iLo];
            subtractFreq(freqMap, val);
            iLo++;

            if (!isOutOfRange(freqMap)) {
                printf("at vec[iLo=%d] = %d; breaking as we are no longer outOfRange\n", (iLo - 1), val);
                showMap(freqMap);
                break;
            } else {
                printf("at vec[iLo=%d] = %d; not-breaking yet\n", (iLo - 1), val);
                showMap(freqMap);
            }
        }

        return iLo;
    }

public:
    friend class SolutionTest;

    long long continuousSubarrays(vector <int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        long long numSubarrays = len;

        int iLo = 0;
        int iHi = 0;
        map <int, int> freqMap = {{nums[0], 1}};
        bool change = true;
        while ((iHi < len) && change) {
            change = false;

            if (!isOutOfRange(freqMap)) {
                // expand window
                int iHiCopy = expandWindowTillDiffPermissible(nums, iHi, freqMap);
                change = iHiCopy != iHi;
                int iHi = iHiCopy;

                int addend;
                if (iLo == iHi) {
                    addend = 0;
                } else if (iLo + 1 == iHi) {
                    addend = 1;
                } else {
                    addend = nCr(iHi - iLo, 2);
                }

                printf("adding %d to result\n\n", addend);
                numSubarrays += addend;
            } else {
                // shrink window
                int iLoCopy = shrinkWindowTillDiffExcessive(nums, iLo, freqMap);
                change = iLoCopy != iLo;
                iLo = iLoCopy;

                int subtrahend = 0;
                if (iLo == iHi) {
                    subtrahend = 0;
                } else if (iLo < iHi) {
                    subtrahend = nCr(iHi - iLo + 1, 2);
                }

                printf("subtracting %d from result\n\n", subtrahend);
                numSubarrays -= subtrahend;
            }

            printf("iLo=%d, iHi=%d\n", iLo, iHi);
        }

        return numSubarrays;
    }
};

class SolutionTest {
public:
    void testExpandWindowTillDiffPermissible() {
        Solution soln = Solution();
        vector <int> vecIn;
        int iHiIn;
        map <int, int> freqMapIn, freqMapOutExpected, freqMapOutComputed;
        int iHiOutExpected, iHiOutComputed;

        vecIn = {5, 4, 2, 4};
        freqMapIn = {
            {4, 1},
            {5, 1}
        };
        iHiIn = 1;
        freqMapOutExpected = {
            {2, 1},
            {4, 1},
            {5, 1}
        };
        iHiOutExpected = 2;
        iHiOutComputed = soln.expandWindowTillDiffPermissible(vecIn, iHiIn, freqMapIn);
        freqMapOutComputed = freqMapIn;
        // soln.showMap(freqMapOutComputed);
        assert(freqMapOutExpected == freqMapOutComputed);
        assert(iHiOutExpected == iHiOutComputed);
    }

    void testShrinkWindowTillDiffExcessive() {
        Solution soln = Solution();
        vector <int> vecIn;
        int iLoIn;
        map <int, int> freqMapIn, freqMapOutExpected, freqMapOutComputed;
        int iLoOutExpected, iLoOutComputed;

        vecIn = {5, 4, 2, 4};
        freqMapIn = {
            {2, 1},
            {4, 1},
            {5, 1}
        };
        iLoIn = 0;
        freqMapOutExpected = {
            {2, 1},
            {4, 1}
        };
        iLoOutExpected = 1;
        iLoOutComputed = soln.shrinkWindowTillDiffExcessive(vecIn, iLoIn, freqMapIn);
        freqMapOutComputed = freqMapIn;
        // soln.showMap(freqMapOutComputed);
        assert(freqMapOutExpected == freqMapOutComputed);
        assert(iLoOutExpected == iLoOutComputed);
    }

    void testContinuousSubarrays() {
        Solution soln = Solution();
        vector <int> vecIn;
        int outExpected, outComputed;

        vecIn = {5, 4, 2, 4};
        outExpected = 8;
        outComputed = soln.continuousSubarrays(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3};
        outExpected = 6;
        outComputed = soln.continuousSubarrays(vecIn);
        assert(outExpected == outComputed);

        vecIn = {65,66,67,66,66,65,64,65,65,64};
        outExpected = 43;
        outComputed = soln.continuousSubarrays(vecIn);
        assert(outExpected == outComputed);

        vecIn = {42,41,42,41,41,40,39,38};
        outExpected = 28;
        outComputed = soln.continuousSubarrays(vecIn);
        printf("outComputed=%d\n", outComputed);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    // solnTest.testExpandWindowTillDiffPermissible();
    // solnTest.testShrinkWindowTillDiffExcessive();
    solnTest.testContinuousSubarrays();

    return 0;
}
