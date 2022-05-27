// LeetCode-1497: https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/description/
// incomplete

#include <cassert>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showMap(unordered_map<int, unordered_set<int> >& modMap) {
        printf("modMap is:-\n");

        for (unordered_map<int, unordered_set<int> >::iterator it1 = modMap.begin(); it1 != modMap.end(); it1++) {
            printf("%d -> ", it1->first);

            unordered_set<int> mSet = it1->second;
            for (unordered_set<int>::iterator it2 = mSet.begin(); it2 != mSet.end(); it2++) {
                printf("%d ", *it2);
            }
            cout << endl;
        }
    }

    unordered_map<int, int> createFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    unordered_set<int> createKeySet(unordered_map<int, unordered_set<int> >& mMap) {
        unordered_set<int> mSet;

        for (unordered_map<int, unordered_set<int> >::iterator it = mMap.begin(); it != mMap.end(); it++) {
            mSet.insert(it->first);
        }

        return mSet;
    }

    unordered_map<int, unordered_set<int> > createModMap(vector<int>& vec, int k) {
        unordered_map<int, unordered_set<int> > modMap;

        for (int i = 0; i < vec.size(); i++) {
            modMap[vec[i] % k].insert(vec[i]);
        }

        return modMap;
    }

    int findTotalCount(
        unordered_map<int, unordered_set<int> >& modMap,
        unordered_map<int, int>& freqMap,
        int mod) {
        int count = 0;

        unordered_set<int> modSet = modMap[mod];
        if (modSet.empty()) {
            return 0;
        }

        for (unordered_set<int>::iterator it = modSet.begin(); it != modSet.end(); it++) {
            count += freqMap[*it];
        }

        return count;
    }

    void eraseEles(
        unordered_map<int, int>& freqMap,
        unordered_set<int>& eleSet) {
        for (unordered_set<int>::iterator it = eleSet.begin(); it != eleSet.end(); it++) {
            freqMap.erase(*it);
        }
    }

    bool tryConsumeMod(
        unordered_map<int, unordered_set<int> >& modMap,
        unordered_map<int, int>& freqMap,
        int k,
        int mod) {
        unordered_set<int> modSet = modMap[mod];
        int totalCountMod = findTotalCount(modMap, freqMap, mod);

        int complement = k - mod;
        unordered_set<int> complementSet = modMap[complement];
        int totalCountComplement = findTotalCount(modMap, freqMap, complement);

        if (totalCountMod == totalCountComplement) {
            eraseEles(freqMap, modSet);
            eraseEles(freqMap, complementSet);
            return true;
        } else {
            return false;
        }
    }

    bool canArrangeHelper(
        int k,
        unordered_map<int, int>& freqMap,
        unordered_set<int>& modSet,
        unordered_map<int, unordered_set<int> >& modMap) {
        unordered_set<int> consumedMods;

        for (unordered_set<int>::iterator it = modSet.begin(); it != modSet.end(); it++) {
            int crrMod = *it;
            if (crrMod == 0) {
                consumedMods.insert(0);
                continue;
            }
            if (consumedMods.find(crrMod) != consumedMods.end()) {
                continue;
            }

            if ((crrMod * 2) == k) {
                // if mod is exactly half of k,
                // then it's elements shoud have even frequency so that they can pair up
                int freq = findTotalCount(modMap, freqMap, crrMod);

                if ((freq % 2) == 0) {
                    unordered_set<int> mSet = {crrMod};
                    eraseEles(freqMap, mSet);
                    modMap.erase(crrMod);
                } else {
                    if (debug) {
                        printf("returning false on half crrMod=%d with freq=%d\n", crrMod, freq);
                    }
                    return false;
                }
            } else {
                if (tryConsumeMod(modMap, freqMap, k, crrMod)) {
                    modMap.erase(crrMod);
                    modMap.erase(k - crrMod);
                } else {
                    if (debug) {
                        printf(
                            "returning false on crrMod=%d with crrModFreq=%d and compl=%d and compFreq=%d\n",
                            crrMod, findTotalCount(modMap, freqMap, crrMod), (k - crrMod), findTotalCount(modMap, freqMap, k - crrMod));
                    }
                    return false;
                }
            }

            consumedMods.insert(crrMod);
            consumedMods.insert(k - crrMod);
        }

        return true;
    }

   public:
    friend class SolutionTest;

    bool canArrange(vector<int>& arr, int k) {
        int len = arr.size();
        if ((len % 2) == 1) {
            // odd length array will always return false
            return false;
        }

        unordered_map<int, int> freqMap = createFreqMap(arr);
        unordered_map<int, unordered_set<int> > modMap = createModMap(arr, k);
        unordered_set<int> modSet = createKeySet(modMap);

        return canArrangeHelper(k, freqMap, modSet, modMap);
    }
};

class SolutionTest {
   public:
    void testCreateModMap() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        unordered_map<int, unordered_set<int> > modMapOutExpected;
        unordered_map<int, unordered_set<int> > modMapOutComputed;

        vecIn = {};
        kIn = 12;
        modMapOutExpected = {};
        modMapOutComputed = soln.createModMap(vecIn, kIn);
        assert(modMapOutExpected == modMapOutComputed);

        vecIn = {2, 5, 12, 0, 1, 9, 3, 15, 16, 8, 19, 4, 25};
        kIn = 12;
        modMapOutExpected = {
            {0, {0, 12}},
            {1, {1, 25}},
            {2, {2}},
            {3, {3, 15}},
            {4, {4, 16}},
            {5, {5}},
            {7, {19}},
            {8, {8}},
            {9, {9}},
        };
        modMapOutComputed = soln.createModMap(vecIn, kIn);
        // soln.showMap(modMapOutComputed);
        assert(modMapOutExpected == modMapOutComputed);
    }

    void testFindTotalCount() {
        Solution soln = Solution();
        vector<int> vecIn;
        unordered_map<int, unordered_set<int> > modMapInterim;
        unordered_map<int, int> freqMapInterim;
        int kIn, modIn;
        int countOutExpected, countOutComputed;

        // test case 1

        vecIn = {};
        kIn = 12;
        modIn = 3;
        modMapInterim = soln.createModMap(vecIn, kIn);
        freqMapInterim = soln.createFreqMap(vecIn);
        countOutExpected = 0;
        countOutComputed = soln.findTotalCount(modMapInterim, freqMapInterim, modIn);
        assert(countOutExpected == countOutComputed);

        // test case 2

        vecIn = {2, 5, 12, 4, 0, 1, 9, 3, 12, 15, 16, 8, 19, 3, 4, 25};
        kIn = 12;
        modMapInterim = soln.createModMap(vecIn, kIn);
        freqMapInterim = soln.createFreqMap(vecIn);

        modIn = 3;
        countOutExpected = 3;
        countOutComputed = soln.findTotalCount(modMapInterim, freqMapInterim, modIn);
        assert(countOutExpected == countOutComputed);

        modIn = 2;
        countOutExpected = 1;
        countOutComputed = soln.findTotalCount(modMapInterim, freqMapInterim, modIn);
        assert(countOutExpected == countOutComputed);

        modIn = 4;
        countOutExpected = 3;
        countOutComputed = soln.findTotalCount(modMapInterim, freqMapInterim, modIn);
        assert(countOutExpected == countOutComputed);

        modIn = 0;
        countOutExpected = 3;
        countOutComputed = soln.findTotalCount(modMapInterim, freqMapInterim, modIn);
        assert(countOutExpected == countOutComputed);

        modIn = 7;
        countOutExpected = 1;
        countOutComputed = soln.findTotalCount(modMapInterim, freqMapInterim, modIn);
        // soln.showMap(modMapInterim);
        assert(countOutExpected == countOutComputed);
    }

    void testCanArrange() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        bool outExpected;
        bool outComputed;

        // soln.debug = true;
        vecIn = {1, 2, 3, 4, 5, 10, 6, 7, 8, 9};
        kIn = 5;
        outExpected = true;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);
        // soln.debug = false;

        vecIn = {1, 2, 3, 4, 5, 6};
        kIn = 7;
        outExpected = true;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 4, 5, 6};
        kIn = 10;
        outExpected = false;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {0, 6, 0, 12, 24, 18};
        kIn = 6;
        outExpected = true;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {0, 17, 6, 15, 0, 12, 18, 24, 5, 9};
        kIn = 6;
        outExpected = false;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);

        soln.debug = true;
        vecIn = {-1, -2, -3, -4, -5, -10, -6, -7, -8, -9};
        kIn = 7;
        outExpected = true;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);
        soln.debug = false;

        vecIn = {-1, -2, -3, -4, -5, -6};
        kIn = 10;
        outExpected = false;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {0, -6, 0, -12, -24, -18};
        kIn = 6;
        outExpected = true;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {-0, -17, -6, -15, -0, -12, -18, -24, -5, -94};
        kIn = 6;
        outExpected = false;
        outComputed = soln.canArrange(vecIn, kIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateModMap();
    solnTest.testFindTotalCount();
    solnTest.testCanArrange();

    return 0;
}
