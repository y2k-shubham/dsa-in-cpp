// LeetCode-1288: https://leetcode.com/problems/remove-covered-intervals/
// incomplete / wrong

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define MAX_VAL 100001

bool mComparator(const pair<int, int>& p1, const pair<int, int>& p2) {
    if (p1.second > p2.second) {
        return false;
    } else if ((p1.second == p2.second) && (p1.first <= p2.first)) {
        return false;
    } else {
        return true;
    }
}

class Solution {
   private:
    bool debug = false;

    void showList(list<int>& mList, string name) {
        printf("%s list is:-\n", name.c_str());

        for (list<int>::iterator it = mList.begin(); it != mList.end(); it++) {
            printf("%d ", *it);
        }

        cout << endl;
    }

    void showVec(vector<pair<int, int>>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        for (int i = 0; i < vec.size(); i++) {
            printf("(%d,%d) ", vec[i].first, vec[i].second);
        }
        cout << endl;
    }

    void showSet(vector<pair<int, int>>& pairVec, unordered_set<int>& mSet, string name) {
        printf("%s set is:-\n", name.c_str());

        for (unordered_set<int>::iterator it = mSet.begin(); it != mSet.end(); it++) {
            printf("[%d] -> (%d, %d)\n", *it, pairVec[*it].first, pairVec[*it].second);
        }

        cout << endl;
    }

    vector<pair<int, int>> convertToPairVec(vector<vector<int>>& vec) {
        int len = vec.size();

        vector<pair<int, int>> pairVec(len);

        for (int i = 0; i < len; i++) {
            pair<int, int> mPair = {vec[i][0], vec[i][1]};
            pairVec[i] = mPair;
        }

        return pairVec;
    }

    unordered_map<int, list<int>> createBeginIndsMap(vector<pair<int, int>>& sortedIntervals) {
        unordered_map<int, list<int>> beginIndsMap;

        for (int i = 0; i < sortedIntervals.size(); i++) {
            beginIndsMap[sortedIntervals[i].first].push_back(i);
        }

        return beginIndsMap;
    }

    unordered_map<int, list<int>> createEndIndsMap(vector<pair<int, int>>& sortedIntervals) {
        unordered_map<int, list<int>> endIndsMap;

        for (int i = 0; i < sortedIntervals.size(); i++) {
            endIndsMap[sortedIntervals[i].second].push_back(i);
        }

        return endIndsMap;
    }

    list<int> createDuplIntervalCountsList(vector<pair<int, int>>& sortedIntervals) {
        list<int> duplIntervalCounts;

        int crrDuplCount = 0;
        for (int i = 1; i < sortedIntervals.size(); i++) {
            if ((sortedIntervals[i].first == sortedIntervals[i - 1].first) && (sortedIntervals[i].second == sortedIntervals[i - 1].second)) {
                crrDuplCount++;
            } else if (crrDuplCount > 0) {
                duplIntervalCounts.push_back(crrDuplCount);

                crrDuplCount = 0;
            }
        }

        return duplIntervalCounts;
    }

   public:
    friend class SolutionTest;

    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        vector<pair<int, int>> pairVec = convertToPairVec(intervals);
        sort(pairVec.begin(), pairVec.end(), mComparator);

        unordered_map<int, list<int>> beginIndsMap = createBeginIndsMap(pairVec);
        unordered_map<int, list<int>> endIndsMap = createEndIndsMap(pairVec);

        unordered_set<int> openInds;

        int numTotal = pairVec.size();
        int numRemoved = 0;
        for (int i = 0; i < MAX_VAL; i++) {
            list<int> beginInds = beginIndsMap[i];
            list<int> endInds = endIndsMap[i];
            if (!beginInds.empty() || !endInds.empty()) {
                if (debug) {
                    printf("\n========================\n");
                    printf("at i=%d\n", i);
                }
            } else {
                continue;
            }

            for (list<int>::iterator it = beginInds.begin(); it != beginInds.end(); it++) {
                openInds.insert(*it);
            }
            if (debug && !beginInds.empty()) {
                printf("\nafter filling openInds:\n");
                showSet(pairVec, openInds, "openInds");
            }

            int areOpenIntervals = openInds.size() > 0;

            for (list<int>::iterator it = endInds.begin(); it != endInds.end(); it++) {
                int crrClosingIntervalBegin = pairVec[*it].first;

                for (unordered_set<int>::iterator it2 = openInds.begin(); it2 != openInds.end(); it2++) {
                  int crrOpenedIntervalBegin = pairVec[*it2].first;
                  if ((*it != *it2) && (crrClosingIntervalBegin >= crrOpenedIntervalBegin)) {
                    ++numRemoved;
                  }
                }

                // numRemoved += areOpenIntervals ? 1 : 0;
                openInds.erase(*it);
            }
            if (debug && !endInds.empty()) {
                printf("\nafter erasing openInds:\n");
                showSet(pairVec, openInds, "openInds");

                printf("\nnumRemoved=%d\n", numRemoved);
            }
        }

        list<int> duplIntervalCounts = createDuplIntervalCountsList(pairVec);
        int numRemaining = numTotal - numRemoved + ((int)duplIntervalCounts.size());

        return numRemaining;
    }
};

class SolutionTest {
   public:
    void testCreateDuplicateIntervalCountsList() {
        Solution soln = Solution();
        vector<pair<int, int>> vecIn;
        list<int> outExpected;
        list<int> outComputed;

        vecIn = {};
        outExpected = {};
        outComputed = soln.createDuplIntervalCountsList(vecIn);
        assert(outExpected == outComputed);

        vecIn = {{1, 4}, {3, 6}, {2, 8}};
        outExpected = {};
        outComputed = soln.createDuplIntervalCountsList(vecIn);
        assert(outExpected == outComputed);

        vecIn = {{1, 4}, {3, 6}, {2, 8}, {3, 6}};
        sort(vecIn.begin(), vecIn.end(), mComparator);
        outExpected = {1};
        outComputed = soln.createDuplIntervalCountsList(vecIn);
        // soln.showList(outComputed, "outComputed");
        assert(outExpected == outComputed);

        vecIn = {{1, 4}, {3, 6}, {2, 8}, {3, 6}, {1, 4}, {3, 6}};
        sort(vecIn.begin(), vecIn.end(), mComparator);
        // soln.showVec(vecIn, "vecIn");
        outExpected = {1, 2};
        outComputed = soln.createDuplIntervalCountsList(vecIn);
        // soln.showList(outComputed, "outComputed");
        assert(outExpected == outComputed);
    }

    void testRemoveCoveredIntervals() {
        Solution soln = Solution();
        vector<vector<int>> vecIn;
        int outExpected;
        int outComputed;

        // soln.debug = true;
        vecIn = {{1, 4}, {3, 6}, {2, 8}};
        outExpected = 2;
        outComputed = soln.removeCoveredIntervals(vecIn);
        assert(outExpected == outComputed);
        // soln.debug = false;

        // soln.debug = true;
        vecIn = {{1, 4}, {2, 3}};
        outExpected = 1;
        outComputed = soln.removeCoveredIntervals(vecIn);
        assert(outExpected == outComputed);
        // soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateDuplicateIntervalCountsList();
    solnTest.testRemoveCoveredIntervals();

    return 0;
}
