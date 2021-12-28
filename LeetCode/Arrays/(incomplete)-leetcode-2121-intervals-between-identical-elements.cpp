// LeetCode-2121: https://leetcode.com/problems/intervals-between-identical-elements/
// incomplete

/**
 * [3]
 * [3,5,7]
 * [3,5,3]
 * [3,5,7,6]
 * [3,5,3,2]
 * [10,5,10,10]
 * [2,1,3,1,2,3,3]
 *
 * // failing test case
 * [98816,98816,98818,98815,98819,98816,98819,98816,98824,98824,98819,98821,98818,98821,98818]
 */

#include <cassert>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    void showVec(vector<long long>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%lld\t", vec[i]);
        }
        cout << endl;
    }

    void showMap(unordered_map<int, vector<int> >& mMap, string name) {
        printf("%s map is:-\n", name.c_str());

        for (unordered_map<int, vector<int> >::iterator it = mMap.begin(); it != mMap.end(); it++) {
            printf("%d -> ", it->first);
            for (int i = 0; i < it->second.size(); i++) {
                printf("%d, ", it->second[i]);
            }
            cout << endl;
        }
        cout << endl;
    }

    void showMap(unordered_map<int, vector<long long> >& mMap, string name) {
        printf("%s map is:-\n", name.c_str());

        for (unordered_map<int, vector<long long> >::iterator it = mMap.begin(); it != mMap.end(); it++) {
            printf("%d -> ", it->first);
            for (int i = 0; i < it->second.size(); i++) {
                printf("%lld, ", it->second[i]);
            }
            cout << endl;
        }
        cout << endl;
    }

    unordered_map<int, vector<int> > prepareEleIndsMap(vector<int>& vec) {
        unordered_map<int, vector<int> > eleIndsMap;
        for (int i = 0; i < vec.size(); i++) {
            eleIndsMap[vec[i]].push_back(i);
        }

        return eleIndsMap;
    }

    vector<long long> buildPrefixSum(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {(long long)vec[0]};
        }

        vector<long long> prefSum(len, 0);
        prefSum[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefSum[i] = prefSum[i - 1] + vec[i];
        }

        return prefSum;
    }

    vector<long long> buildSuffixSum(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {(long long)vec[0]};
        }

        vector<long long> suffSum(len, 0);
        suffSum[len - 1] = vec[len - 1];
        for (int i = len - 2; i >= 0; i--) {
            suffSum[i] = suffSum[i + 1] + vec[i];
        }

        return suffSum;
    }

    unordered_map<int, vector<long long> > prepareIndsPrefixSumMap(unordered_map<int, vector<int> >& eleIndsMap) {
        unordered_map<int, vector<long long> > indsPrefixSumMap;
        for (unordered_map<int, vector<int> >::iterator it = eleIndsMap.begin(); it != eleIndsMap.end(); it++) {
            indsPrefixSumMap[it->first] = buildPrefixSum(it->second);
        }

        return indsPrefixSumMap;
    }

    unordered_map<int, vector<long long> > prepareIndsSuffixSumMap(unordered_map<int, vector<int> >& eleIndsMap) {
        unordered_map<int, vector<long long> > indsSuffixSumMap;
        for (unordered_map<int, vector<int> >::iterator it = eleIndsMap.begin(); it != eleIndsMap.end(); it++) {
            indsSuffixSumMap[it->first] = buildSuffixSum(it->second);
        }

        return indsSuffixSumMap;
    }

    int binSearchIdx(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }
        if (len == 1) {
            if (vec[lo] == ele) {
                return lo;
            } else {
                return -1;
            }
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];
        if (ele < midEle) {
            return binSearchIdx(vec, ele, lo, mid - 1);
        } else if (ele == midEle) {
            return mid;
        } else {
            return binSearchIdx(vec, ele, mid + 1, hi);
        }
    }

   public:
    friend class SolutionTest;

    vector<long long> getDistances(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {0};
        }

        unordered_map<int, vector<int> > eleIndsMap = prepareEleIndsMap(vec);
        unordered_map<int, vector<long long> > indsPrefixSumMap = prepareIndsPrefixSumMap(eleIndsMap);
        unordered_map<int, vector<long long> > indsSuffixSumMap = prepareIndsSuffixSumMap(eleIndsMap);

        if (debug) {
            showMap(eleIndsMap, "eleIndsMap");
            showMap(indsPrefixSumMap, "indsPrefixSumMap");
            showMap(indsSuffixSumMap, "indsSuffixSumMap");
        }

        vector<long long> intervals(len, 0);
        unordered_map<int, int> eleCrrFreqMap;
        for (int i = 0; i < len; i++) {
            int ele = vec[i];
            if (debug) {
                printf("\nat vec[i=%d]=%d\n", i, ele);
            }

            int totalFreq = eleIndsMap[ele].size();
            if (totalFreq == 1) {
                if (debug) {
                    printf("totalFreq is 1, intervals[i=%d] = 0\n", i);
                }
                intervals[i] = 0;
                continue;
            }

            vector<long long> indsPrefixSum = indsPrefixSumMap[ele];
            vector<long long> indsSuffixSum = indsSuffixSumMap[ele];

            int crrFreq = eleCrrFreqMap[ele] + 1;
            if (crrFreq == 1) {
                // first occurence -> only suffix sum to be taken
                intervals[i] = indsSuffixSum[0] - (totalFreq * ((long long)i));
                if (debug) {
                    printf("first   occurence, intervals[i=%d] = { suffixSum=%lld - (freq=%d * i=%d) } = %lld\n", i, indsSuffixSum[0], totalFreq, i, intervals[i]);
                }
            } else if (crrFreq == totalFreq) {
                // last occurence -> only prefix sum to be taken
                intervals[i] = (totalFreq * ((long long)i)) - indsPrefixSum[totalFreq - 1];
                if (debug) {
                    printf("last    occurence, intervals[i=%d] = { (freq=%d * i=%d) - prefixSum=%lld } = %lld\n", i, totalFreq, i, indsPrefixSum[totalFreq - 1], intervals[i]);
                }
            } else {
                // interim occurence -> both prefix & suffix sums to be taken
                long long prefixSum = (crrFreq * ((long long)i)) - indsPrefixSum[crrFreq - 1];
                long long suffixSum = indsSuffixSum[crrFreq - 1] - (crrFreq * ((long long)i));
                intervals[i] = prefixSum + suffixSum;
                if (debug) {
                    printf("interim occurence, intervals[i=%d] = { (freq=%d * i=%d) - prefixSum[%d]=%lld } + { suffixSum[%d]=%lld - (freq=%d * i=%d) } = %lld\n", i, crrFreq, i, (crrFreq - 1), indsPrefixSum[crrFreq - 1], (crrFreq - 1), indsSuffixSum[crrFreq - 1], crrFreq, i, intervals[i]);
                }
            }

            eleCrrFreqMap[ele]++;
        }

        return intervals;
    }
};

class SolutionTest {
   public:
    void testGetDistances() {
        Solution soln = Solution();
        vector<int> inVec;
        vector<long long> outExpectedVec, outComputedVec;

        // soln.debug = true;
        inVec = {2, 1, 3, 1, 2, 3, 3};
        outExpectedVec = {4, 2, 7, 2, 4, 4, 5};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);

        inVec = {10, 5, 10, 10};
        outExpectedVec = {5, 0, 3, 4};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);
        // soln.debug = false;

        inVec = {3};
        outExpectedVec = {0};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);

        inVec = {3, 5, 7};
        outExpectedVec = {0, 0, 0};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);

        inVec = {3, 5, 3};
        outExpectedVec = {2, 0, 2};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);

        inVec = {3, 5, 7, 6};
        outExpectedVec = {0, 0, 0, 0};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);

        inVec = {3, 5, 3, 2};
        outExpectedVec = {2, 0, 2, 0};
        outComputedVec = soln.getDistances(inVec);
        assert(outExpectedVec == outComputedVec);

        // failing test case
        inVec = {98816, 98816, 98818, 98815, 98819, 98816, 98819, 98816, 98824, 98824, 98819, 98821, 98818, 98821, 98818};
        outExpectedVec = {13, 11, 22, 0, 8, 11, 6, 15, 1, 1, 10, 2, 12, 2, 14};
        outComputedVec = soln.getDistances(inVec);
        soln.showVec(outComputedVec, "outComputedVec");
        assert(outExpectedVec == outComputedVec);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testGetDistances();

    return 0;
}
