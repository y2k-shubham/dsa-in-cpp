// IDeserve: (much clearer explaination) https://www.youtube.com/watch?v=1RpMc3fv0y4&t=212s
// TusharRoy: https://www.youtube.com/watch?v=S9oUiVYEq7E&t=626s

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

void testSearchGreaterThanOrEqual();
int searchGreaterThanOrEqual(vector<int> vec, int lo, int hi, int ele);
int searchGreaterThanOrEqualInd(vector<int> vec, vector<int> inds, int lo, int hi, int ele);

int main() {
    testSearchGreaterThanOrEqual();

    return 0;
}

void testSearchGreaterThanOrEqual() {
    vector<int> vecIn;
    int lo, hi;
    int ele;

    vecIn = {};
    lo = 1;
    hi = 5;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == -1);

    vecIn = {0, 1, 1, 4};
    lo = 0;
    hi = 3;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == 3);

    vecIn = {};
    lo = 1;
    hi = 5;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == -1);

    vecIn = {};
    lo = 1;
    hi = 5;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == -1);

    vecIn = {};
    lo = 1;
    hi = 5;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == -1);

    vecIn = {};
    lo = 1;
    hi = 5;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == -1);

    vecIn = {};
    lo = 1;
    hi = 5;
    ele = 8;
    assert(searchGreaterThanOrEqual(vecIn, lo, hi, ele) == -1);
}

int searchGreaterThanOrEqual(vector<int> vec, int lo, int hi, int ele) {
    if (vec.empty()) {
        return -1;
    } else {
        int len = hi - lo + 1;

        if (len <= 0) {
            return -1;
        } else if (len == 1) {
            if (vec[lo] < ele) {
                return -1;
            } else {
                return lo;
            }
        } else {
            int mid = (lo + hi) / 2;
            int midEle = vec[mid];

            if (ele < midEle) {
                return max(searchGreaterThanOrEqual(vec, lo, mid - 1, ele), mid);
            } else if (ele == midEle) {
                return max(mid, searchGreaterThanOrEqual(vec, mid + 1, hi, ele));
            } else {
                return searchGreaterThanOrEqual(vec, mid + 1, hi, ele);
            }
        }
    }
}

int searchGreaterThanOrEqualInd(vector<int> vec, vector<int> inds, int lo, int hi, int ele) {
    if (vec.empty() || inds.empty()) {
        return -1;
    } else {
        int len = hi - lo + 1;

        if (len <= 0) {
            return -1;
        } else if (len == 1) {
            if (vec[inds[lo]] < ele) {
                return -1;
            } else {
                return lo;
            }
        } else {
            int mid = (lo + hi) / 2;
            int midEle = vec[inds[mid]];

            if (ele < midEle) {
                return searchGreaterThanOrEqualInd(vec, inds, lo, mid - 1, ele);
            } else if (ele == midEle) {
                return max(mid, searchGreaterThanOrEqualInd(vec, inds, mid + 1, hi, ele));
            } else {
                return searchGreaterThanOrEqualInd(vec, inds, mid + 1, hi, ele);
            }
        }
    }
}
