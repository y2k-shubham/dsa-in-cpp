// http://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/
// https://practice.geeksforgeeks.org/problems/triplet-sum-in-array/0

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

pair<vector<int>, int> input();
void findTriplets1(vector<int> vec, int reqSum);
void findTriplets2(vector<int> vec, int reqSum);
void findTriplets3(vector<int> vec, int reqSum);

int main() {
    int T;

    cin >> T;
    while (T-- > 0) {
        pair<vector<int>, int> inputs = input();
        vector<int> vec = inputs.first;
        int reqSum = inputs.second;

        // hash-based approach; no sorting
        findTriplets1(vec, reqSum);

        // sorting based approach; no extra space (other than sorting)
        // findTriplets2(vec, reqSum);

        // sorting + hash based approach (wrong)
        // findTriplets3(vec, reqSum);
    }

    return 0;
}

pair<vector<int>, int> input() {
    int len, reqSum;
    cin >> len >> reqSum;

    vector<int> vec(len);
    for (int i = 0; i < len; i++) {
        cin >> vec[i];
    }

    return make_pair(vec, reqSum);
}

// Time: O(n^2), Space: O(n)
void findTriplets1(vector<int> vec, int reqSum) {
    int len = vec.size();
    unordered_set<int> mSet;

    for (int i = 0; i < len; i++) {
        unordered_set<int> mSet;
        for (int j = i + 1; j < len; j++) {
            int remSum = reqSum - (vec[i] + vec[j]);

            if (mSet.find(remSum) != mSet.end()) {
                cout << 1 << endl;
                return;
            } else {
                mSet.insert(vec[j]);
            }
        }
    }

    cout << 0 << endl;
}

// Time: O(n^2), Space: whatever sorting takes
void findTriplets2(vector<int> vec, int reqSum) {
    sort(vec.begin(), vec.end());

    int len = vec.size();
    for (int i = 0; i < len - 2; i++) {
        int remSum = reqSum - vec[i];

        int j = i + 1, k = len - 1;
        while (j < k) {
            int crrSum = vec[j] + vec[k];
            if (crrSum < remSum) {
                j++;
            } else if (crrSum == remSum) {
                cout << 1 << endl;
                return;
            } else {
                k--;
            }
        }
    }

    cout << 0 << endl;
}

// wrong
void findTriplets3(vector<int> vec, int reqSum) {
    sort(vec.begin(), vec.end());
    unordered_set<int> mSet(vec.begin(), vec.end());

    int len = vec.size();
    int i = 0;
    int j = len - 1;
    while (i < j) {
        int crrSum = vec[i] + vec[j];
        int remSum = reqSum - crrSum;

        if ((remSum != vec[i]) && (remSum != vec[j]) && (mSet.find(remSum) != mSet.end())) {
            cout << 1 << endl;
            return;
        }

        if (crrSum < reqSum) {
            i++;
        } else {
            j--;
        }
    }

    cout << 0 << endl;
}
