// https://leetcode.com/problems/3sum/
// https://www.geeksforgeeks.org/find-triplets-array-whose-sum-equal-zero/
// https://practice.geeksforgeeks.org/problems/find-triplets-with-zero-sum/1

/*
2
5
0 -1 2 -3 1
3
1 2 3

1
5
0 -1 2 -3 1

1
3
1 2 3

1
5
0 -1 2 -3 1

1
5
1 -2 1 0 5

1
6
-1 0 1 2 -1 -4

1
15
-4 -2 -2 -2 0 1 2 2 2 3 3 4 4 6 6
*/

#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<int> inputGFG(int);
void showVec(vector<int>, const char*);
vector<vector<int> > threeSumLC(vector<int>&);
void outputLC(vector<vector<int> >);
void outputGFG(vector<vector<int> >);
bool findTripletsGFG(int [], int);

int main() {
    int T;

    cin >> T;
    while (T-- > 0) {
        int N;
        cin >> N;

        vector<int> vec = inputGFG(N);
        // showVec(vec, "vec");

        sort(vec.begin(), vec.end());
        // showVec(vec, "sorted vec");

        // LeetCode
        // vector<vector<int> > resTriplets = threeSumLC(vec);
        // outputLC(resTriplets);
        // outputGFG(resTriplets);

        // GeeksForGeeks
        if (findTripletsGFG(vec.data(), N)) {
          printf("1\n");
        } else {
          printf("0\n");
        }
    }

    return 0;
}

vector<vector<int> > threeSumLC(vector<int>& nums) {
    // sort
    sort(nums.begin(), nums.end());

    set<vector <int> > resTripletsSet;
    int lastInd = ((int)nums.size()) - 1;

    // g++ -std=c++11 3sum.cpp
    // vector<int> prevResVec = {INT_MIN, INT_MIN, INT_MIN};
    for (int i = 0; i < lastInd - 1; i++) {
        // showVec(nums, "sorted vec");
        // printf("\n==========\n");
        int Ni = nums[i];
        // printf("at i=%d,\tNi = nums[i=%d] = %d\n", i, i, Ni);

        int j = i + 1;
        int k = lastInd;
        // printf("\n----will run through range j=%d, k=%d----\n", j, k);
        while (j < k) {
            // cout << endl;
            int Nj = nums[j];
            // printf("at j=%d,\tNj = nums[j=%d] = %d\n", j, j, Nj);

            int Nk = nums[k];
            // printf("at k=%d,\tNk = nums[k=%d] = %d\n", k, k, Nk);

            int sum = Ni + Nj + Nk;
            if (sum < 0) {
                // printf("{(Ni=%d + Nj=%d + Nk=%d) = %d} < 0, increasing j\n", Ni, Nj, Nk, sum);
                j++;
            } else if (sum == 0) {
                // printf("{(Ni=%d + Nj=%d + Nk=%d) = %d} = 0, found a solution: (%d, %d, %d)\n", Ni, Nj, Nk, sum, Ni, Nj, Nk);
                vector<int> resVec(3);
                resVec[0] = Ni;
                resVec[1] = Nj;
                resVec[2] = Nk;

                // if (resVec == prevResVec) {
                    // printf("duplicate solution, skipping\n");
                // } else {
                    // printf("new solution, adding to resTriplets");
                    resTripletsSet.insert(resVec);
                    // prevResVec = resVec;
                // }

                j++;
            } else {
                // printf("{(Ni=%d + Nj=%d + Nk=%d) = %d} > 0, decreasing k\n", Ni, Nj, Nk, sum);
                k--;
            }
        }
        // printf("\n==========");
    }

    vector<vector<int> > resTripletsVec;
    resTripletsVec.assign(resTripletsSet.begin(), resTripletsSet.end());

    return resTripletsVec;
}

bool findTripletsGFG(int arr[], int n) {
  sort(arr, arr + n);

  set<vector <int> > resTripletsSet;
    int lastInd = n - 1;

    for (int i = 0; i < lastInd - 1; i++) {
        int Ni = arr[i];

        int j = i + 1;
        int k = lastInd;
        while (j < k) {
            int Nj = arr[j];

            int Nk = arr[k];

            int sum = Ni + Nj + Nk;
            if (sum < 0) {
                j++;
            } else if (sum == 0) {
                return true;

                j++;
            } else {
                k--;
            }
        }
    }

    return false;
}

void outputLC(vector<vector<int> > resTriplets) {
    printf("[\n");
    for (vector<vector<int> >::iterator it = resTriplets.begin(); it != resTriplets.end(); it++) {
        vector<int> resVec = *it;
        printf("  [%d, %d, %d]\n", resVec[0], resVec[1], resVec[2]);
    }
    printf("]\n");
}

void outputGFG(vector<vector<int> > resTriplets) {
    if (!resTriplets.empty()) {
        printf("1\n");
    } else {
        printf("0\n");
    }
}

void showVec(vector<int> vec, const char* name) {
    printf("\nVector %s is:-\n", name);

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
}

vector<int> inputGFG(int N) {
    vector<int> vec(N);
    for (int i = 0; i < N; i++) {
        int ele;
        cin >> ele;
        vec[i] = ele;
    }

    return vec;
}
