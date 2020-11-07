// LeetCode-352: https://leetcode.com/problems/data-stream-as-disjoint-intervals/
// *Opt methods are untested / incomplete -> see getParentOpt : the intention is to prune intermediate 'dead' nodes

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

class SummaryRanges {
   private:
    set<pair<int, int>> ranges;
    map<pair<int, int>, pair<int, int>> childParentMap;

    bool addNumRange(int num) {
        pair<int, int> numRange = {num, num};
        if (childParentMap.find(numRange) == childParentMap.end()) {
            childParentMap[numRange] = numRange;
            ranges.insert(numRange);
            return true;
        } else {
            return false;
        }
    }

    bool existAndAreAdjacent(int n1, int n2) {
        pair<int, int> r1 = {n1, n1};
        pair<int, int> r2 = {n2, n2};

        return (childParentMap.find(r1) != childParentMap.end()) && (childParentMap.find(r2) != childParentMap.end()) && (abs(n1 - n2) == 1);
    }

    pair<int, int> getParent(pair<int, int> crrRange) {
        if (childParentMap.find(crrRange) == childParentMap.end()) {
            throw new out_of_range("attempting to find parent of non-existent range");
        } else {
            pair<int, int> crrParent = childParentMap[crrRange];

            if (crrParent == crrRange) {
                ranges.insert(crrRange);
                return crrRange;
            } else {
                pair<int, int> finalParent = getParent(crrParent);

                childParentMap[crrRange] = finalParent;
                return finalParent;
            }
        }
    }

    pair<int, int> getParentOpt(pair<int, int> crrRange) {
        if (childParentMap.find(crrRange) == childParentMap.end()) {
            throw new out_of_range("attempting to find parent of non-existent range");
        } else {
            pair<int, int> crrParent = childParentMap[crrRange];

            if (crrParent == crrRange) {
                ranges.insert(crrRange);
                return crrRange;
            } else {
                pair<int, int> finalParent = getParentOpt(crrParent);
                if (crrRange.first != crrRange.second && crrRange != finalParent) {
                    childParentMap.erase(crrRange);
                } else {
                    childParentMap[crrRange] = finalParent;
                }

                return finalParent;
            }
        }
    }

    pair<int, int> mergePairs(pair<int, int> p1, pair<int, int> p2) {
        pair<int, int> p;
        p.first = min(p1.first, p2.first);
        p.second = max(p1.second, p2.second);
        return p;
    }

    pair<int, int> mergeRanges(pair<int, int> r1, pair<int, int> r2) {
        pair<int, int> p1 = getParent(r1);
        pair<int, int> p2 = getParent(r2);

        pair<int, int> pMerged = mergePairs(p1, p2);

        childParentMap[p1] = pMerged;
        childParentMap[p2] = pMerged;
        childParentMap[pMerged] = pMerged;

        ranges.erase(p1);
        ranges.erase(p2);
        ranges.insert(pMerged);

        return pMerged;
    }

    pair<int, int> mergeRangesOpt(pair<int, int> r1, pair<int, int> r2) {
        pair<int, int> p1 = getParentOpt(r1);
        pair<int, int> p2 = getParentOpt(r2);

        pair<int, int> pMerged = mergePairs(p1, p2);

        childParentMap[p1] = pMerged;
        childParentMap[p2] = pMerged;
        childParentMap[pMerged] = pMerged;

        ranges.erase(p1);
        ranges.erase(p2);
        ranges.insert(pMerged);

        return pMerged;
    }

    pair<int, int> mergeNumRanges(int n1, int n2) {
        return mergeRanges({n1, n1}, {n2, n2});
    }

    pair<int, int> mergeNumRangesOpt(int n1, int n2) {
        return mergeRangesOpt({n1, n1}, {n2, n2});
    }

    void showRanges() {
        printf("\nRanges are:-\n");
        for (set<pair<int, int>>::iterator i = ranges.begin(); i != ranges.end(); i++) {
            printf("(%d, %d), ", (*i).first, (*i).second);
        }
        cout << endl;
    }

    void showChildParentMap() {
        printf("\nchildParentMap:-\n");
        for (map<pair<int, int>, pair<int, int>>::iterator i = childParentMap.begin(); i != childParentMap.end(); i++) {
            printf("(%d, %d)\t->\t(%d, %d)\n", ((*i).first.first), ((*i).first.second), ((*i).second.first), ((*i).second.second));
        }
    }

   public:
    /** Initialize your data structure here. */

    // friend tester class
    friend class SummaryRangesTester;

    SummaryRanges() {
    }

    // LC submission -> speed: 19 %tile, memory: 6 %tile
    void addNum(int val) {
        addNumRange(val);

        if (existAndAreAdjacent(val - 1, val)) {
            mergeNumRanges(val - 1, val);
        }

        if (existAndAreAdjacent(val, val + 1)) {
            mergeNumRanges(val, val + 1);
        }
    }

    void addNumOpt(int val) {
        addNumRange(val);

        if (existAndAreAdjacent(val - 1, val)) {
            mergeNumRangesOpt(val - 1, val);
        }

        if (existAndAreAdjacent(val, val + 1)) {
            mergeNumRangesOpt(val, val + 1);
        }
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> intervals(ranges.size());

        int i = 0;
        for (set<pair<int, int>>::iterator it = ranges.begin(); it != ranges.end(); it++, i++) {
            pair<int, int> crrRange = *it;
            intervals[i] = {crrRange.first, crrRange.second};
        }

        return intervals;
    }
};

class SummaryRangesTester {
   public:
    void testAddNumRange() {
        SummaryRanges sr = SummaryRanges();

        bool added;
        set<pair<int, int>> rangesOutExpected;

        rangesOutExpected = {};
        assert(rangesOutExpected == sr.ranges);

        added = sr.addNumRange(5);
        rangesOutExpected = {{5, 5}};
        assert(rangesOutExpected == sr.ranges);
        assert(added == true);

        added = sr.addNumRange(7);
        rangesOutExpected = {{5, 5}, {7, 7}};
        assert(rangesOutExpected == sr.ranges);
        assert(added == true);

        added = sr.addNumRange(5);
        rangesOutExpected = {{5, 5}, {7, 7}};
        assert(rangesOutExpected == sr.ranges);
        assert(added == false);

        added = sr.addNumRange(6);
        rangesOutExpected = {{5, 5}, {6, 6}, {7, 7}};
        assert(rangesOutExpected == sr.ranges);
        assert(added == true);
    }

    void testExistAndAreAdjacent() {
        SummaryRanges sr = SummaryRanges();
        // {}

        assert(sr.existAndAreAdjacent(0, 5) == false);
        assert(sr.existAndAreAdjacent(4, 5) == false);

        sr.addNumRange(5);
        // {{5, 5}}

        assert(sr.existAndAreAdjacent(0, 5) == false);
        assert(sr.existAndAreAdjacent(4, 5) == false);

        sr.addNumRange(7);
        // {{5, 5}, {7, 7}}

        assert(sr.existAndAreAdjacent(4, 5) == false);
        assert(sr.existAndAreAdjacent(5, 6) == false);
        assert(sr.existAndAreAdjacent(5, 7) == false);
        assert(sr.existAndAreAdjacent(6, 7) == false);
        assert(sr.existAndAreAdjacent(7, 8) == false);

        sr.addNumRange(5);
        // {{5, 5}, {7, 7}}

        assert(sr.existAndAreAdjacent(4, 5) == false);
        assert(sr.existAndAreAdjacent(5, 6) == false);
        assert(sr.existAndAreAdjacent(5, 7) == false);
        assert(sr.existAndAreAdjacent(6, 7) == false);
        assert(sr.existAndAreAdjacent(7, 8) == false);

        sr.addNumRange(6);
        // {{5, 5}, {6, 6}, {7, 7}}

        assert(sr.existAndAreAdjacent(4, 5) == false);
        assert(sr.existAndAreAdjacent(5, 6) == true);
        assert(sr.existAndAreAdjacent(5, 7) == false);
        assert(sr.existAndAreAdjacent(6, 7) == true);
        assert(sr.existAndAreAdjacent(7, 8) == false);
    }

    void testGetParent() {
        bool exceptionThrown;
        SummaryRanges sr = SummaryRanges();
        // {}

        exceptionThrown = false;
        try {
            sr.getParent({0, 0});
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        sr.addNumRange(5);
        /**
         * {(5, 5): (5, 5)}
         */

        exceptionThrown = false;
        try {
            sr.getParent({0, 0});
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        assert(sr.getParent({5, 5}) == make_pair(5, 5));

        sr.addNumRange(7);
        /**
         * {(5, 5): (5, 5)},
         * {(7, 7): (7, 7)}
         */

        exceptionThrown = false;
        try {
            sr.getParent({6, 6});
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        assert(sr.getParent({5, 5}) == make_pair(5, 5));
        assert(sr.getParent({7, 7}) == make_pair(7, 7));

        sr.addNumRange(7);
        /**
         * {(5, 5): (5, 5)},
         * {(7, 7): (7, 7)}
         */

        exceptionThrown = false;
        try {
            sr.getParent({6, 6});
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        assert(sr.getParent({5, 5}) == make_pair(5, 5));
        assert(sr.getParent({7, 7}) == make_pair(7, 7));

        sr.addNumRange(8);
        /**
         * {(5, 5): (5, 5)},
         * {(7, 7): (7, 7)}
         * {(8, 8): (8, 8)}
         */

        exceptionThrown = false;
        try {
            sr.getParent({6, 6});
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        assert(sr.getParent({5, 5}) == make_pair(5, 5));
        assert(sr.getParent({7, 7}) == make_pair(7, 7));
        assert(sr.getParent({8, 8}) == make_pair(8, 8));
    }

    void testMergePairs() {
        SummaryRanges sr = SummaryRanges();

        assert(sr.mergePairs(make_pair(1, 1), make_pair(1, 1)) == make_pair(1, 1));
        assert(sr.mergePairs(make_pair(0, 1), make_pair(1, 4)) == make_pair(0, 4));
        assert(sr.mergePairs(make_pair(1, 4), make_pair(3, 5)) == make_pair(1, 5));
        assert(sr.mergePairs(make_pair(0, 4), make_pair(1, 2)) == make_pair(0, 4));
        assert(sr.mergePairs(make_pair(0, 4), make_pair(-1, 3)) == make_pair(-1, 4));
    }

    void testMergeRanges() {
        SummaryRanges sr = SummaryRanges();

        sr.addNumRange(5);
        // {(5, 5): (5, 5)}

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));

        sr.addNumRange(7);
        /**
         * {(5, 5): (5, 5),
         *  (7, 7): (7, 7)}
         */

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(7, 7));

        // sr.showRanges();
        // sr.showChildParentMap();

        sr.mergeRanges({5, 5}, {7, 7});
        /**
         * {(5, 5): (5, 7),
         *  (5, 7): (5, 7),
         *  (7, 7): (5, 7)}
         */

        // sr.showRanges();
        // sr.showChildParentMap();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(5, 7)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 7));

        sr.addNumRange(6);
        /**
         * {(5, 5): (5, 7),
         *  (6, 6): (6, 6),
         *  (5, 7): (5, 7),
         *  (7, 7): (5, 7)}
         */

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(6, 6));
        assert(sr.getParent(make_pair(5, 7)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 7));

        sr.mergeRanges(make_pair(5, 5), make_pair(6, 6));
        /**
         * {(5, 5): (5, 7),
         *  (6, 6): (5, 7),
         *  (5, 7): (5, 7),
         *  (7, 7): (5, 7)}
         */

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(5, 7)) == make_pair(5, 7));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 7));
    }

    void testAddNum() {
        SummaryRanges sr = SummaryRanges();

        sr.addNum(5);
        // {(5, 5): (5, 5)}

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));

        sr.addNum(7);
        /**
         * {(5, 5): (5, 5),
         *  (7, 7): (7, 7)}
         */

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(7, 7));

        sr.addNum(8);
        /**
         * {(5, 5): (5, 5),
         *  (7, 7): (7, 8),
         *  (7, 8): (7, 8),
         *  (8, 8): (7, 8)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(7, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(7, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(7, 8));

        sr.addNum(6);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(5, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        // assert(sr.getParent(make_pair(6, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));

        sr.addNum(6);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));

        sr.addNum(10);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8),
         *  (10, 10): (10, 10)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(10, 10)) == make_pair(10, 10));

        sr.addNum(11);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8),
         *  (10, 10): (10, 11),
         *  (10, 11): (10, 11),
         *  (11, 11): (10, 11)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(10, 10)) == make_pair(10, 11));
        assert(sr.getParent(make_pair(10, 11)) == make_pair(10, 11));
        assert(sr.getParent(make_pair(11, 11)) == make_pair(10, 11));

        sr.addNum(9);
        /**
         * {(5, 5): (5, 11),
         *  (6, 6): (5, 11),
         *  (7, 7): (5, 11),
         *  (7, 8): (5, 11),
         *  (8, 8): (5, 11),
         *  (9, 9): (5, 11),
         *  (10, 10): (5, 11),
         *  (10, 11): (5, 11),
         *  (11, 11): (5, 11)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(9, 9)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(10, 10)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(10, 11)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(11, 11)) == make_pair(5, 11));
    }

    void testAddNumOpt() {
        SummaryRanges sr = SummaryRanges();

        sr.addNum(5);
        // {(5, 5): (5, 5)}

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));

        sr.addNum(7);
        /**
         * {(5, 5): (5, 5),
         *  (7, 7): (7, 7)}
         */

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(7, 7));

        sr.addNum(8);
        /**
         * {(5, 5): (5, 5),
         *  (7, 7): (7, 8),
         *  (7, 8): (7, 8),
         *  (8, 8): (7, 8)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 5));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(7, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(7, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(7, 8));

        sr.addNum(6);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));

        sr.addNum(6);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));

        sr.addNum(10);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8),
         *  (10, 10): (10, 10)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(10, 10)) == make_pair(10, 10));

        sr.addNum(11);
        /**
         * {(5, 5): (5, 8),
         *  (6, 6): (5, 8),
         *  (7, 7): (5, 8),
         *  (7, 8): (5, 8),
         *  (8, 8): (5, 8),
         *  (10, 10): (10, 11),
         *  (10, 11): (10, 11),
         *  (11, 11): (10, 11)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 8));
        assert(sr.getParent(make_pair(10, 10)) == make_pair(10, 11));
        assert(sr.getParent(make_pair(10, 11)) == make_pair(10, 11));
        assert(sr.getParent(make_pair(11, 11)) == make_pair(10, 11));

        sr.addNum(9);
        /**
         * {(5, 5): (5, 11),
         *  (6, 6): (5, 11),
         *  (7, 7): (5, 11),
         *  (7, 8): (5, 11),
         *  (8, 8): (5, 11),
         *  (9, 9): (5, 11),
         *  (10, 10): (5, 11),
         *  (10, 11): (5, 11),
         *  (11, 11): (5, 11)}
         */

        // sr.showRanges();

        assert(sr.getParent(make_pair(5, 5)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(6, 6)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(7, 7)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(7, 8)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(8, 8)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(9, 9)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(10, 10)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(10, 11)) == make_pair(5, 11));
        assert(sr.getParent(make_pair(11, 11)) == make_pair(5, 11));
    }

};

int main() {
    SummaryRangesTester srt = SummaryRangesTester();
    srt.testAddNumRange();
    srt.testExistAndAreAdjacent();
    srt.testGetParent();
    srt.testMergePairs();
    srt.testMergeRanges();
    srt.testAddNum();

    return 0;
}
