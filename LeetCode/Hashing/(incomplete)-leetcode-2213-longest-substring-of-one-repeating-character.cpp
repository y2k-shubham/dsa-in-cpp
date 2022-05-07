// LeetCode-2213: https://leetcode.com/problems/longest-substring-of-one-repeating-character/

// hard problem
// incomplete

// the way we are implementing it here, it is just too
//  - long (too many edge cases)
//  - & complex (playing with map iterators)
// to even implement

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <utility>
#include <unordered_set>
#include <climits>

using namespace std;

#define NULL_BYTE '\0'

class Solution {
private:
    bool debug = false;

    pair<map<int, char>, map<int, unordered_set<int> >> prepareDomainsMap(string& str) {
        int len = str.size();
        if (len == 0) {
            return {{},
                    {}};
        }

        map<int, char> domainsMap;
        map<int, unordered_set<int> > lenDomainIdxMap;

        char prevChar = NULL_BYTE;
        int prevCharBeginIdx = -1;
        for (int i = 0; i <= len; i++) {
            char ch = (i < len) ? str.at(i) : NULL_BYTE;
            if (ch != prevChar) {
                // whenever a new sequence of character starts,

                // we first record the length of sequence that ended
                if (prevChar != NULL_BYTE) {
                    int prevCharSeqLen = i - prevCharBeginIdx;
                    lenDomainIdxMap[prevCharSeqLen].insert(prevCharBeginIdx);
                }

                // then we'll record the beginning index of sequence that started
                if (i < len) {
                    prevChar = ch;
                    prevCharBeginIdx = i;
                    domainsMap[i] = ch;
                }
            }
        }


        return {domainsMap, lenDomainIdxMap};
    }

    int findDomainIdx(map<int, char>& domainsMap, int idx) {
        if (domainsMap.empty()) {
            return INT_MIN;
        }

        auto it = domainsMap.lower_bound(idx);
        if (debug) {
            if (it == domainsMap.end()) {
                printf("lower_bound of idx=%d is end\n", idx);
            } else {
                printf("lower_bound of idx=%d is [%d] = '%c'\n", idx, it->first, it->second);
            }
        }
        if ((it == domainsMap.end()) || (it->first != idx)) {
            it--;
            if (debug) {
                printf("decremented iterator to [%d] = '%c'\n", it->first, it->second);
            }
        }

        return it->first;
    }

    auto getPrevIter(map<int, char>& mMap, map<int, char>::iterator itCrr) {
        if (itCrr == mMap.begin()) {
            return itCrr;
        }

        auto itPrev = itCrr;
        itPrev--;

        return itPrev;
    }

    auto getNextIter(map<int, char>& mMap, map<int, char>::iterator itCrr) {
        if (itCrr == mMap.end()) {
            return itCrr;
        }

        auto itNext = itCrr;
        itNext++;

        return itNext;
    }

    int getDomainLength(
            int len,
            map<int, char>& domainsMap,
            map<int, unordered_set<int> >& lenDomainIdxMap,
            map<int, char>::iterator it
    ) {

    }

    void fuseDomains(
            map<int, char>& domainsMap,
            map<int, unordered_set<int> >& lenDomainIdxMap,
            map<int, char>::iterator it1,
            map<int, char>::iterator it2
    ) {

    }

    void updateDomains(
            int len,
            map<int, char>& domainsMap,
            map<int, unordered_set<int> >& lenDomainIdxMap,
            char ch,
            int idx
    ) {
        int domainIdx = findDomainIdx(domainsMap, idx);

        auto itCrr = domainsMap.find(domainIdx);
        if (ch == itCrr->second) {
            return;
        }

        auto itPrev = getPrevIter(domainsMap, itCrr);
        auto itNext = getNextIter(domainsMap, itCrr);

        bool prevExists = itCrr != domainsMap.begin();
        bool nextExists = itNext != domainsMap.end();

        bool isPrevDomainSameChar = prevExists && (itPrev->second == ch);
        bool isNextDomainSameChar = nextExists && (itNext->second == ch);

        bool isMapBeginIdx = idx == 0;
        bool isDomainBeginIdx = isMapBeginIdx || (itCrr->first == idx);
        bool isMapEndIdx = idx == (len - 1);
        bool isDomainEndIdx = isMapEndIdx || (nextExists ? ((idx + 1) == itNext->first) : false);
        bool isUnitLengthDomain = isDomainBeginIdx && isDomainEndIdx;

        if (isDomainBeginIdx) {

        }
    }

public:
    friend class SolutionTest;

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {

    }
};

class SolutionTest {
public:
    void testPrepareDomainsMap() {
        Solution soln = Solution();
        string strIn;
        pair<map<int, char>, map<int, unordered_set<int> >> outComputed;
        map<int, char> domainsMapOutExpected;
        map<int, unordered_set<int> > lenDomainIdxMapOutExpected;

        strIn = "";
        domainsMapOutExpected = {};
        lenDomainIdxMapOutExpected = {};
        outComputed = soln.prepareDomainsMap(strIn);
        assert(domainsMapOutExpected == outComputed.first);
        assert(lenDomainIdxMapOutExpected == outComputed.second);

        strIn = "p";
        domainsMapOutExpected = {{0, 'p'}};
        lenDomainIdxMapOutExpected = {{1, {0}}};
        outComputed = soln.prepareDomainsMap(strIn);
        assert(domainsMapOutExpected == outComputed.first);
        assert(lenDomainIdxMapOutExpected == outComputed.second);

        strIn = "pp";
        domainsMapOutExpected = {{0, 'p'}};
        lenDomainIdxMapOutExpected = {{2, {0}}};
        outComputed = soln.prepareDomainsMap(strIn);
        assert(domainsMapOutExpected == outComputed.first);
        assert(lenDomainIdxMapOutExpected == outComputed.second);

        strIn = "ppmp";
        domainsMapOutExpected = {{0, 'p'},
                                 {2, 'm'},
                                 {3, 'p'}};
        lenDomainIdxMapOutExpected = {{1, {2, 3}},
                                      {2, {0}}};
        outComputed = soln.prepareDomainsMap(strIn);
        assert(domainsMapOutExpected == outComputed.first);
        assert(lenDomainIdxMapOutExpected == outComputed.second);

        strIn = "babacc";
        domainsMapOutExpected = {{0, 'b'},
                                 {1, 'a'},
                                 {2, 'b'},
                                 {3, 'a'},
                                 {4, 'c'}};
        lenDomainIdxMapOutExpected = {{1, {0, 1, 2, 3}},
                                      {2, {4}}};
        outComputed = soln.prepareDomainsMap(strIn);
        assert(domainsMapOutExpected == outComputed.first);
        assert(lenDomainIdxMapOutExpected == outComputed.second);

        strIn = "abyzz";
        domainsMapOutExpected = {{0, 'a'},
                                 {1, 'b'},
                                 {2, 'y'},
                                 {3, 'z'}};
        lenDomainIdxMapOutExpected = {{1, {0, 1, 2}},
                                      {2, {3}}};
        outComputed = soln.prepareDomainsMap(strIn);
        assert(domainsMapOutExpected == outComputed.first);
        assert(lenDomainIdxMapOutExpected == outComputed.second);
    }

    void testFindDomainIdx() {
        Solution soln = Solution();
        map<int, char> domainsMapIn;
        int idxIn;
        int idxOutExpected, idxOutComputed;

        domainsMapIn = {};
        idxIn = 0;
        idxOutExpected = INT_MIN;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

        domainsMapIn = {{0, 'm'}};

        idxIn = 0;
        idxOutExpected = 0;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

//        soln.debug = true;
        idxIn = 1;
        idxOutExpected = 0;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
//        cout << idxOutComputed << endl;
        assert(idxOutExpected == idxOutComputed);
//        soln.debug = false;

        domainsMapIn = {{0, 'm'},
                        {5, 'k'},
                        {6, 'v'}};

        idxIn = 0;
        idxOutExpected = 0;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

        idxIn = 1;
        idxOutExpected = 0;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

        idxIn = 4;
        idxOutExpected = 0;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

        idxIn = 5;
        idxOutExpected = 5;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

        idxIn = 6;
        idxOutExpected = 6;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);

        idxIn = 7;
        idxOutExpected = 6;
        idxOutComputed = soln.findDomainIdx(domainsMapIn, idxIn);
        assert(idxOutExpected == idxOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testPrepareDomainsMap();
    solnTest.testFindDomainIdx();

    return 0;
}
