// LeetCode-846: https://leetcode.com/problems/hand-of-straights/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

map<int, int> prepareFreqMap(vector<int>& vec);
void testPrepareFreqMap();
bool kConseqExist(map<int, int>& freqMap, int k);
void testKConseqExist();
void decFirstKConseq(map<int, int>& freqMap, int k, bool);
void testDecFirstKConseq();
void showMap(map<int, int> freqMap, string);
bool isNStraightHand(vector<int>& hand, int W);
void testIsNStraightHand();

int main() {
    testPrepareFreqMap();
    testKConseqExist();
    testDecFirstKConseq();
    testIsNStraightHand();

    return 0;
}

void testPrepareFreqMap() {
    vector<int> vecIn;
    map<int, int> freqMapOutExp;
    map<int, int> freqMapOutComp;

    vecIn = {};
    freqMapOutExp = {};
    freqMapOutComp = prepareFreqMap(vecIn);
    assert(freqMapOutExp == freqMapOutComp);

    vecIn = {9};
    freqMapOutExp = {{9, 1}};
    freqMapOutComp = prepareFreqMap(vecIn);
    assert(freqMapOutExp == freqMapOutComp);

    vecIn = {9, 9};
    freqMapOutExp = {{9, 2}};
    freqMapOutComp = prepareFreqMap(vecIn);
    assert(freqMapOutExp == freqMapOutComp);

    vecIn = {{8, 9, 8}};
    freqMapOutExp = {{8, 2}, {9, 1}};
    freqMapOutComp = prepareFreqMap(vecIn);
    assert(freqMapOutExp == freqMapOutComp);
}

map<int, int> prepareFreqMap(vector<int>& vec) {
    map<int, int> freqMap;
    for (int i = 0; i < vec.size(); i++) {
        freqMap[vec[i]] += 1;
    }
    return freqMap;
}

void testKConseqExist() {
    map<int, int> freqMap;
    int k;

    freqMap = {};
    k = 0;
    assert(kConseqExist(freqMap, k) == true);

    freqMap = {{9, 1}};
    k = 0;
    assert(kConseqExist(freqMap, k) == false);

    freqMap = {};
    k = 1;
    assert(kConseqExist(freqMap, k) == false);

    freqMap = {{8, 1}, {9, 1}};
    k = 1;
    assert(kConseqExist(freqMap, k) == true);

    freqMap = {{8, 1}, {9, 1}};
    k = 2;
    assert(kConseqExist(freqMap, k) == true);

    freqMap = {{8, 1}, {10, 1}};
    k = 2;
    assert(kConseqExist(freqMap, k) == false);

    freqMap = {{8, 2}, {9, 5}, {10, 1}};
    k = 3;
    assert(kConseqExist(freqMap, k) == true);

    freqMap = {{7, 2}, {9, 5}, {10, 1}, {11, 5}};
    k = 3;
    assert(kConseqExist(freqMap, k) == false);
}

bool kConseqExist(map<int, int>& freqMap, int k) {
    if ((k == 0) || freqMap.empty()) {
        return (k == 0) && freqMap.empty();
    } else {
        int i;
        map<int, int>::iterator it;

        it = freqMap.begin();
        int prevVal = (*it).first - 1;
        for (i = 1; it != freqMap.end() && i <= k; it++, i++) {
            int crrVal = (*it).first;
            if (prevVal + 1 != crrVal) {
                return false;
            } else {
                prevVal = crrVal;
            }
        }

        if (i <= k) {
            return false;
        } else {
            return true;
        }
    }
}

void showMap(map<int, int> freqMap, string caption) {
    printf("\n%s is:-\n", caption.c_str());

    printf("Ind:\t");
    for (map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
        printf("[%d]\t", (*it).first);
    }
    cout << endl;

    printf("Val:\t");
    for (map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
        printf("%d\t", (*it).second);
    }
    cout << endl;
}

void testDecFirstKConseq() {
    map<int, int> freqMapIn;
    int k;
    map<int, int> freqMapOutExp;

    freqMapIn = {};
    k = 0;
    freqMapOutExp = {};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{5, 1}};
    k = 1;
    freqMapOutExp = {};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{5, 4}};
    k = 1;
    freqMapOutExp = {{5, 3}};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{5, 1}, {9, 2}};
    k = 2;
    freqMapOutExp = {{9, 1}};
    // showMap(freqMapIn, "before dec, freqMapIn");
    decFirstKConseq(freqMapIn, k, true);
    // cout << freqMapIn.size() << endl;
    // showMap(freqMapIn, "after  dec, freqMapIn");
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{3, 2}, {4, 1}, {5, 1}, {6, 3}};
    k = 1;
    freqMapOutExp = {{3, 1}, {4, 1}, {5, 1}, {6, 3}};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{3, 2}, {4, 1}, {5, 1}, {6, 3}};
    k = 2;
    freqMapOutExp = {{3, 1}, {5, 1}, {6, 3}};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{3, 2}, {4, 1}, {5, 1}, {6, 3}};
    k = 3;
    freqMapOutExp = {{3, 1}, {6, 3}};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);

    freqMapIn = {{3, 2}, {4, 1}, {5, 1}, {6, 3}};
    k = 4;
    freqMapOutExp = {{3, 1}, {6, 2}};
    decFirstKConseq(freqMapIn, k, false);
    assert(freqMapOutExp == freqMapIn);
}

void decFirstKConseq(map<int, int>& freqMap, int k, bool debug) {
    if (k > 0) {
        map<int, int>::iterator itMap;
        int i;
        int crrVal;

        list<int> firstKKeys;
        for (i = 1, itMap = freqMap.begin(); itMap != freqMap.end() && i <= k; i++, itMap++) {
            firstKKeys.push_back((*itMap).first);
        }

        list<int>::iterator itList;
        for (i = 1, itList = firstKKeys.begin(); itList != firstKKeys.end() && i <= k; i++, itList++) {
            crrVal = (*itList);
            freqMap[crrVal]--;
            if (freqMap[crrVal] == 0) {
                freqMap.erase(crrVal);
            }
        }
    }
}

void testIsNStraightHand() {
    vector<int> vecIn;
    int k;

    vecIn = {};
    k = 0;
    assert(isNStraightHand(vecIn, k) == true);

    vecIn = {1};
    k = 0;
    assert(isNStraightHand(vecIn, k) == false);

    vecIn = {};
    k = 2;
    assert(isNStraightHand(vecIn, k) == false);

    vecIn = {3, 1, 2};
    k = 1;
    assert(isNStraightHand(vecIn, k) == true);

    vecIn = {3, 1, 2};
    k = 2;
    assert(isNStraightHand(vecIn, k) == false);

    vecIn = {3, 1, 2};
    k = 3;
    assert(isNStraightHand(vecIn, k) == true);

    vecIn = {1, 3, 1, 2};
    k = 2;
    assert(isNStraightHand(vecIn, k) == false);

    vecIn = {1, 3, 2, 2};
    k = 2;
    assert(isNStraightHand(vecIn, k) == true);

    vecIn = {2, 1, 3, 2};
    k = 2;
    assert(isNStraightHand(vecIn, k) == true);
}

// LC-submission: speed: 68 %tile, memory: 9 %tile
bool isNStraightHand(vector<int>& hand, int W) {
    if ((W == 0) || hand.empty()) {
        return (W == 0) && (hand.empty());
    } else {
        map<int, int> freqMap = prepareFreqMap(hand);

        while (!freqMap.empty()) {
            if (kConseqExist(freqMap, W)) {
                decFirstKConseq(freqMap, W, false);
            } else {
                return false;
            }
        }

        return true;
    }
}
