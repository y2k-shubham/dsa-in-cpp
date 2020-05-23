//
// Created by Shubham Gupta on 24/01/20.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;
#define MAX 10000007
#define max(a, b) ((a > b) ? a : b)

void input(int&, vector <int>&, int&);
vector <pair <int, int> > computeSubArrays(vector <int>, int, int);
void inc(vector <int>, int&, int&, int&, bool);
void showSubArrays(vector <int>, vector <pair <int, int> >);

int main() {
    int T;
    int N;
    vector <int> vec(MAX);
    int reqSum;

    cin >> T;
    while (T-- > 0) {
        input(N, vec, reqSum);
    }
}

void input(int& N, vector <int>& vec, int& reqSum) {
    cin >> N >> reqSum;
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
}

vector <pair <int, int> > computeSubArrays(vector <int> vec, int len, int reqSum) {
    vector <pair <int, int> > indices;

    int crrSum = vec[0];
    int iLo = 0;
    int iHi = 0;
    while ((iLo <= iHi) && (iHi < len)) {
        if (crrSum < reqSum) {
            inc(vec, iLo, iHi, crrSum, false);
        } else if (crrSum > reqSum) {
            inc(vec, iLo, iHi, crrSum, true);
        } else {
            indices.emplace_back(iLo, iHi);
            inc(vec, iLo, iHi, crrSum, false);
        }
    }

    return indices;
}

void inc(vector <int> vec, int& iLo, int& iHi, int& crrSum, bool incLo) {
    if (incLo) {
        crrSum -= vec[iLo];
        iLo++;
    } else {
        iHi++;
        crrSum += vec[iHi];
    }
}

void showSubArrays(vector <int> vec, vector <pair <int, int> > indices) {
    for (auto it = indices.begin(); it != indices.end(); it++) {
        cout << endl;

        int iLo = (* it).first;
        int iHi = (* it).second;

        for (int i = iLo; i <= iHi; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = iLo; i <= iHi; i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }
}
