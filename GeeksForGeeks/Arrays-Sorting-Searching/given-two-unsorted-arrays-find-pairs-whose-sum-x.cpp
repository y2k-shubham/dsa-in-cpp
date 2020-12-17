// https://www.geeksforgeeks.org/given-two-unsorted-arrays-find-pairs-whose-sum-x/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<int> input(int len) {
    vector<int> vec(len);

    for (int i = 0; i < len; i++) {
        cin >> vec[i];
    }

    return vec;
}

int countPairsWithSum(vector<int>& vec1, vector<int>& vec2, int reqSum) {
    int len1 = vec1.size();
    int len2 = vec2.size();

    int idx1 = 0;
    int idx2 = len2 - 1;

    int numPairs = 0;
    while ((idx1 < len1) && (idx2 >= 0)) {
        int crrSum = vec1[idx1] + vec2[idx2];

        if (crrSum < reqSum) {
            idx1++;
        } else if (crrSum == reqSum) {
            numPairs++;
            idx1++;
            idx2--;
        } else {
            idx2--;
        }
    }

    return numPairs;
}

void testCountPairsWithSum() {
    vector<int> vec1;
    vector<int> vec2;
    int reqSum;
    int countOutExpected;
    int countOutComputed;

    vec1 = {};
    vec2 = {};
    reqSum = 5;
    countOutExpected = 0;
    countOutComputed = countPairsWithSum(vec1, vec2, reqSum);
    assert(countOutExpected == countOutComputed);

    vec1 = {};
    vec2 = {3};
    reqSum = 5;
    countOutExpected = 0;
    countOutComputed = countPairsWithSum(vec1, vec2, reqSum);
    assert(countOutExpected == countOutComputed);

    vec1 = {3, 4};
    vec2 = {};
    reqSum = 5;
    countOutExpected = 0;
    countOutComputed = countPairsWithSum(vec1, vec2, reqSum);
    assert(countOutExpected == countOutComputed);
}

void showPairs(set<pair<int, int> >& pairs) {
    if (!pairs.empty()) {
        set<pair<int, int> >::iterator it = pairs.begin();
        printf("%d %d", (*it).first, (*it).second);

        it++;
        while (it != pairs.end()) {
            printf(", %d %d", (*it).first, (*it).second);
            it++;
        }

        cout << endl;
    } else {
        cout << -1 << endl;
    }
}

set<pair<int, int> > findPairsWithSum(vector<int>& vec1, vector<int>& vec2, int reqSum, bool debug) {
    int len1 = vec1.size();
    int len2 = vec2.size();

    int idx1 = 0;
    int idx2 = len2 - 1;

    set<pair<int, int> > pairs;
    while ((idx1 < len1) && (idx2 >= 0)) {
        int crrSum = vec1[idx1] + vec2[idx2];

        if (crrSum < reqSum) {
            idx1++;
        } else if (crrSum == reqSum) {
            pairs.insert(make_pair(vec1[idx1], vec2[idx2]));
            idx1++;
            idx2--;
        } else {
            idx2--;
        }
    }

    return pairs;
}

void testFindPairsWithSum() {
    vector<int> vec1;
    vector<int> vec2;
    int reqSum;
    set<pair<int, int> > pairsOutExpected;
    set<pair<int, int> > pairsOutComputed;

    vec1 = {};
    vec2 = {};
    reqSum = 5;
    pairsOutExpected = {};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, false);
    assert(pairsOutExpected == pairsOutComputed);

    vec1 = {};
    vec2 = {3};
    reqSum = 5;
    pairsOutExpected = {};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, false);
    assert(pairsOutExpected == pairsOutComputed);

    vec1 = {3, 7};
    vec2 = {};
    reqSum = 5;
    pairsOutExpected = {};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, false);
    assert(pairsOutExpected == pairsOutComputed);

    vec1 = {1, 2, 4, 5, 7};
    vec2 = {3, 4, 5, 6, 8};
    reqSum = 9;
    pairsOutExpected = {{1, 8}, {4, 5}, {5, 4}};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, true);
    assert(pairsOutExpected == pairsOutComputed);

    vec1 = {-1, 2};
    vec2 = {-4, 5, -7, -11, -17, -24, 25, 39, 42, -43, 44, -48, 54, 55, 64, 69, 70, -72, 82, -83, -86, -88, -90, -96, 97, 99};
    reqSum = 97;
    pairsOutExpected = {};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, false);
    showPairs(pairsOutComputed);
    assert(pairsOutExpected == pairsOutComputed);

    vec1 = {};
    vec2 = {};
    reqSum = 5;
    pairsOutExpected = {};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, false);
    assert(pairsOutExpected == pairsOutComputed);

    vec1 = {};
    vec2 = {};
    reqSum = 5;
    pairsOutExpected = {};
    pairsOutComputed = findPairsWithSum(vec1, vec2, reqSum, false);
    assert(pairsOutExpected == pairsOutComputed);
}

int main() {
    testCountPairsWithSum();
    testFindPairsWithSum();

    int T;

    cin >> T;
    while (T-- > 0) {
        int len1, len2, reqSum;
        cin >> len1 >> len2 >> reqSum;

        vector<int> vec1 = input(len1);
        sort(vec1.begin(), vec1.end());

        vector<int> vec2 = input(len2);
        sort(vec2.begin(), vec2.end());

        set<pair<int, int> > pairs = findPairsWithSum(vec1, vec2, reqSum, false);

        return 0;
    }
}
