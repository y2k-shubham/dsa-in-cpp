// LeetCode-1024: https://leetcode.com/problems/video-stitching/
// incomplete

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <unordered_set>
#include <list>
#include <unordered_map>

using namespace std;

bool comparator(const tuple<int, int, int>& t1, const tuple<int, int, int>& t2) {
    int s1 = get<0>(t1);
    int e1 = get<1>(t1);
    int d1 = get<2>(t1);

    int s2 = get<0>(t2);
    int e2 = get<1>(t2);
    int d2 = get<2>(t2);

    // sort by descending order of end time value
    return (e1 < e2) || ((e1 == e2) && (s1 > s2));
}

class Solution {
private:
    bool debug = false;

    void showVec(vector<tuple<int, int, int>>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Begin:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", get<0>(vec[i]));
        }
        cout << endl;

        printf("End:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", get<1>(vec[i]));
        }
        cout << endl;

        printf("Delta:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", get<2>(vec[i]));
        }
        cout << endl;
    }

    void showList(list<tuple<int, int, int> >& mList, string name) {
        printf("%s list is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < mList.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Begin:\t");
        for (auto it: mList) {
            printf("%d\t", get<0>(it));
        }
        cout << endl;

        printf("End:\t");
        for (auto it: mList) {
            printf("%d\t", get<1>(it));
        }
        cout << endl;

        printf("Delta:\t");
        for (auto it: mList) {
            printf("%d\t", get<2>(it));
        }
        cout << endl;
    }

    vector<tuple<int, int, int> > createTupVec(vector<vector<int> >& vec) {
        int len = vec.size();

        vector<tuple<int, int, int> > tupVec(len);
        for (int i = 0; i < len; i++) {
            tupVec[i] = {vec[i][0], vec[i][1], vec[i][1] - vec[i][0]};
        }

        return tupVec;
    }

    vector<tuple<int, int, int> > filterByMaxEnd(vector<tuple<int, int, int> >& vec) {
        unordered_map<int, int> maxEndMap;
        for (int i = 0; i < vec.size(); i++) {
            int crrStart = get<0>(vec[i]);
            int crrEnd = get<1>(vec[i]);

            if (maxEndMap.find(crrStart) == maxEndMap.end()) {
                maxEndMap[crrStart] = crrEnd;
            } else {
                maxEndMap[crrStart] = max(crrEnd, maxEndMap[crrStart]);
            }
        }

        int numUniqueStarts = maxEndMap.size();
        vector<tuple<int, int, int> > maxEndVec(numUniqueStarts);
        int idx = 0;
        for (auto it: maxEndMap) {
            maxEndVec[idx++] = {it.first, it.second, it.second - it.first};
        }

        return maxEndVec;
    }

    vector<tuple<int, int, int> > filterByMinStart(vector<tuple<int, int, int> >& vec) {
        unordered_map<int, int> minStartMap;
        for (int i = 0; i < vec.size(); i++) {
            int crrStart = get<0>(vec[i]);
            int crrEnd = get<1>(vec[i]);

            if (minStartMap.find(crrEnd) == minStartMap.end()) {
                minStartMap[crrEnd] = crrStart;
            } else {
                minStartMap[crrEnd] = min(crrStart, minStartMap[crrEnd]);
            }
        }

        int numUniqueStarts = minStartMap.size();
        vector<tuple<int, int, int> > minStartVec(numUniqueStarts);
        int idx = 0;
        for (auto it: minStartMap) {
            minStartVec[idx++] = {it.second, it.first, it.first - it.second};
        }

        return minStartVec;
    }

    vector <tuple <int, int, int>> filterClipsStartingAfter(vector<tuple<int, int, int> >& vec, int maxStart) {
        vector <tuple <int, int, int>> filteredVec;

        for (auto it: vec) {
            if (get <0> (it) > maxStart) {
                break;
            }

            filteredVec.push_back(it);
        }

        return filteredVec;
    }

    int binSearchEndTimeCeil(vector<tuple<int, int, int> >& vec, int val, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midEle = get<1>(vec[mid]);

        if (midEle < val) {
            return binSearchEndTimeCeil(vec, val, mid + 1, hi);
        } else {
            int lRes = binSearchEndTimeCeil(vec, val, lo, mid - 1);
            return (lRes >= 0) ? lRes : -1;
        }
    }

    int countMinClips(vector<tuple<int, int, int> >& vec, int time) {
        int len = vec.size();
        int idx = len;

        tuple<int, int, int> prevClip = {time, INT_MAX, INT_MAX - time};
        list<tuple<int, int, int> > clips = {prevClip};
        while ((idx >= 0) && (get<0>(prevClip) > 0)) {
            while ((idx >= 1) && (get<1>(vec[idx - 1]) >= get<0>(prevClip))) {
                idx--;
            }

            if (idx >= 1) {
                prevClip = vec[idx];
            } else {
                // first item will always be in the solution
                // as we've already done de-duping
                prevClip = vec[0];
            }
            clips.push_front(prevClip);

            idx--;
        }

        if (debug) {
            showList(clips, "clips");
        }
        return clips.size();
    }

public:
    friend class SolutionTest;

    int videoStitching(vector<vector<int>>& clips, int time) {
        vector<tuple<int, int, int> > tupVec = createTupVec(clips);
        sort(tupVec.begin(), tupVec.end(), comparator);

        vector<tuple<int, int, int> > tmp1 = filterByMinStart(tupVec);
        vector<tuple<int, int, int> > tmp2 = filterByMinStart(tmp1);
        vector <tuple <int, int, int> > tmp3 = filterClipsStartingAfter(tmp2, time);

        return countMinClips(tmp3, time);
    }
};

class SolutionTest {
public:
    void testCreateTupVec() {
        Solution soln = Solution();
        vector<vector<int> > vecIn;
        vector<tuple<int, int, int> > vecOutExpected;
        vector<tuple<int, int, int> > vecOutComputed;

        vecIn = {{0, 2},
                 {4, 6},
                 {8, 10},
                 {1, 9},
                 {1, 5},
                 {5, 9}};
        vecOutExpected = {{0, 2,  2},
                          {4, 6,  2},
                          {8, 10, 2},
                          {1, 9,  8},
                          {1, 5,  4},
                          {5, 9,  4}};
        vecOutComputed = soln.createTupVec(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }

    void testComparator() {
        Solution soln = Solution();
        vector<vector<int> > vecIn;
        vector<tuple<int, int, int> > vecOutExpected;
        vector<tuple<int, int, int> > vecOutComputed;

        vecIn = {{0, 2},
                 {4, 6},
                 {8, 10},
                 {1, 9},
                 {1, 5},
                 {5, 9}};
        vecOutExpected = {{0, 2,  2},
                          {1, 5,  4},
                          {4, 6,  2},
                          {5, 9,  4},
                          {1, 9,  8},
                          {8, 10, 2}};
        vecOutComputed = soln.createTupVec(vecIn);
        sort(vecOutComputed.begin(), vecOutComputed.end(), comparator);
//        soln.showVec(vecOutExpected, "vecOutExpected");
//        soln.showVec(vecOutComputed, "vecOutComputed");
        assert(vecOutExpected == vecOutComputed);
    }

    void testFilterByMaxEnd() {
        Solution soln = Solution();
        vector<tuple<int, int, int> > vecIn;
        vector<tuple<int, int, int> > vecOutExpected;
        vector<tuple<int, int, int> > vecOutComputed;

        vecIn = {
                {1, 3, 2},
                {1, 5, 4},
                {2, 3, 1},
                {3, 9, 6},
                {3, 7, 4}
        };
        vecOutExpected = {
                {1, 5, 4},
                {2, 3, 1},
                {3, 9, 6}
        };
        vecOutComputed = soln.filterByMaxEnd(vecIn);
        sort(vecOutComputed.begin(), vecOutComputed.end(), comparator);
        sort(vecOutExpected.begin(), vecOutExpected.end(), comparator);
        assert(vecOutExpected == vecOutComputed);
    }

    void testFilterByMinStart() {
        Solution soln = Solution();
        vector<tuple<int, int, int> > vecIn;
        vector<tuple<int, int, int> > vecOutExpected;
        vector<tuple<int, int, int> > vecOutComputed;

        vecIn = {
                {3, 5,  2},
                {2, 6,  4},
                {1, 5,  4},
                {8, 11, 3},
                {9, 10, 1},
                {9, 11, 2}
        };
        vecOutExpected = {
                {2, 6,  4},
                {1, 5,  4},
                {8, 11, 3},
                {9, 10, 1}
        };
        vecOutComputed = soln.filterByMinStart(vecIn);
        sort(vecOutComputed.begin(), vecOutComputed.end(), comparator);
        sort(vecOutExpected.begin(), vecOutExpected.end(), comparator);
//        soln.showVec(vecOutExpected, "vecOutExpected");
//        soln.showVec(vecOutComputed, "vecOutComputed");
        assert(vecOutExpected == vecOutComputed);
    }

    void testVideoStitching() {
        Solution soln = Solution();
        vector <vector <int>> clipsIn;
        int timeIn;
        int numClipsOutExpected, numClipsOutComputed;

        clipsIn = {{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}};
        timeIn = 10;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateTupVec();
    solnTest.testComparator();
    solnTest.testFilterByMaxEnd();
    solnTest.testFilterByMinStart();

    return 0;
}
