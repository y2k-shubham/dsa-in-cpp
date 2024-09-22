// LeetCode-373: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/

// wrong: very confused, not a medium difficult problem

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <set>
#include <cassert>

using namespace std;

class Solution {
private:
    void showList(list <pair <int, int> >& pairs, const char* name) {
        printf("%s is:-\n", name);
        for (pair <int, int> ele: pairs) {
            printf("(%d,%d) ", ele.first, ele.second);
        }
        printf("\n");
    }

    void showList(vector <vector <int> >& pairs, const char* name) {
        printf("%s is:-\n", name);
        for (vector <int> ele: pairs) {
            printf("(%d, %d) ", ele[0], ele[1]);
        }
        printf("\n");
    }

    unordered_map<int, int> createFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;
        for (int ele: vec) {
            freqMap[ele]++;
        }
        return freqMap;
    }

    set<int> createSet(vector<int>& vec) {
        set<int> mSet(vec.begin(), vec.end());
        return mSet;
    }

    list<pair<int, int> > createPairs(int ele1, int freq1, int ele2, int freq2) {
        list<pair<int, int> > pairs;
        for (int i = 0; i < freq1; i++) {
            for (int j = 0; j < freq2; j++) {
                pairs.push_back({ele1, ele2});
            }
        }
        return pairs;
    }

    list<pair<int, int> > createPairs(int ele, vector<int>& vec, int endIdx, bool eleIsFirstInPair) {
        list<pair<int, int> > pairs;

        for (int i = 0; i <= endIdx; i++) {
            if (eleIsFirstInPair) {
                pairs.push_back(make_pair(ele, vec[i]));
            } else {
                pairs.push_back(make_pair(vec[i], ele));
            }
        }

        return pairs;
    }

    inline bool shouldIncrementI1(vector<int>& vec1, int i1, vector<int>& vec2, int i2) {
        int len1 = vec1.size(), len2 = vec2.size();

        if (i1 >= len1 - 1) {
            return false;
        }
        if (i2 >= len2 - 1) {
            return true;
        }

        return (vec1[i1 + 1] + vec2[i2]) <= (vec1[i1] + vec2[i2 + 1]);
    }

    pair<int, int> swallowSmallestPairs(vector<int>& vec1, vector<int>& vec2, int k) {
        int i1 = 0, i2 = 0;
        int len1 = vec1.size(), len2 = vec2.size();

        int i1Prev = 0, i2Prev = 0;
        int numPairs = 1;
        while ((i1 < len1) && (i2 < len2) && (numPairs < k)) {
            i1Prev = i1;
            i2Prev = i2;

            if (shouldIncrementI1(vec1, i1, vec2, i2)) {
                printf("at i1=%d, i2=%d decided to increment i1\n", i1, i2);
                i1++;
                numPairs += i2 + 1;
            } else {
                printf("at i1=%d, i2=%d decided to increment i2\n", i1, i2);
                i2++;
                numPairs += i1 + 1;
            }
        }

        if (numPairs > k) {
            return {i1Prev, i2Prev};
        } else {
            return {i1, i2};
        }
    }

    list<pair <int, int> > createPairs(vector <int>& vec1, vector <int>& vec2, int k) {
        int i1 = 0, i2 = 0;
        int len1 = vec1.size(), len2 = vec2.size();

        list<pair<int, int> > pairs;
        if (k >= 1) {
            pairs.push_back({vec1[0], vec2[0]});
        }

        int numPairs = 1;
        while ((i1 < len1) && (i2 < len2) && (numPairs < k)) {
            if (shouldIncrementI1(vec1, i1, vec2, i2)) {
//                printf("at i1=%d, i2=%d decided to increment i1\n", i1, i2);
                i1++;
                pairs.splice(pairs.end(), createPairs(vec1[i1], vec2, i2, true));
                numPairs += i2 + 1;
            } else {
//                printf("at i1=%d, i2=%d decided to increment i2\n", i1, i2);
                i2++;
                pairs.splice(pairs.end(), createPairs(vec2[i2], vec1, i1, false));
                numPairs += i1 + 1;
            }
        }

        return pairs;
    }

    void removeExtraPairs(list<pair<int, int> >& pairs, int k) {
        while (pairs.size() > k) {
            pairs.pop_back();
        }
    }

    vector<vector<int>> convertToVec(list<pair<int, int> > pairs) {
        vector<vector<int>> res(pairs.size());
        int i = 0;
        for (pair<int, int> pair: pairs) {
            res[i++] = {pair.first, pair.second};
        }
        return res;
    }

public:
    friend class SolutionTest;

    vector<vector<int>> kSmallestPairs(vector<int>& vec1, vector<int>& vec2, int k) {
        list<pair<int, int> > pairs = createPairs(vec1, vec2, k);
        removeExtraPairs(pairs, k);

        return convertToVec(pairs);
    }
};

class SolutionTest {
public:
    void testSwallowSmallestPairs() {
        Solution soln = Solution();
        vector<int> vec1, vec2;
        int k;
        pair<int, int> resOutExpected, resOutComputed;

        vec1 = {1, 7, 11};
        vec2 = {2, 4, 6};

//        k = 1;
//        resOutExpected = {0, 0};
//        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
//        assert(resOutExpected == resOutComputed);
//
//        k = 2;
//        resOutExpected = {0, 1};
//        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
//        printf("expected=(%d, %d), computed=(%d, %d)\n", resOutExpected.first, resOutExpected.second, resOutComputed.first, resOutComputed.second);
//        assert(resOutExpected == resOutComputed);
//
//        k = 3;
//        resOutExpected = {0, 2};
//        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
//        assert(resOutExpected == resOutComputed);

        k = 4;
        resOutExpected = {1, 2};
        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
        printf("expected=(%d, %d), computed=(%d, %d)\n", resOutExpected.first, resOutExpected.second, resOutComputed.first, resOutComputed.second);
        assert(resOutExpected == resOutComputed);

        k = 5;
        resOutExpected = {1, 2};
        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
        assert(resOutExpected == resOutComputed);

        k = 6;
        resOutExpected = {1, 2};
        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
        assert(resOutExpected == resOutComputed);

        k = 7;
        resOutExpected = {2, 2};
        resOutComputed = soln.swallowSmallestPairs(vec1, vec2, k);
        assert(resOutExpected == resOutComputed);

        printf("[testSwallowSmallestPairs] all test cases passed\n");
    }

    void testKSmallestPairs() {
        Solution soln = Solution();
        vector<int> vec1, vec2;
        int k;
        vector<vector<int>> resOutExpected, resOutComputed;

        vec1 = {1, 7, 11};
        vec2 = {2, 4, 6};
        k = 3;
        resOutExpected = {{1,2},{1,4},{1,6}};
        resOutComputed = soln.kSmallestPairs(vec1, vec2, k);
        assert(resOutExpected == resOutComputed);

        vec1 = {1, 1, 2};
        vec2 = {1, 2, 3};
        k = 2;
        resOutExpected = {{1,1},{1,1}};
        resOutComputed = soln.kSmallestPairs(vec1, vec2, k);
        assert(resOutExpected == resOutComputed);

        vec1 = {1, 2};
        vec2 = {3};
        k = 3;
        resOutExpected = {{1,3},{2,3}};
        resOutComputed = soln.kSmallestPairs(vec1, vec2, k);
        soln.showList(resOutExpected, "resOutExpected");
        soln.showList(resOutComputed, "resOutComputed");
        assert(resOutExpected == resOutComputed);

        printf("[testKSmallestPairs] all test cases passed\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

//    test.testSwallowSmallestPairs();
    test.testKSmallestPairs();

    return 0;
}