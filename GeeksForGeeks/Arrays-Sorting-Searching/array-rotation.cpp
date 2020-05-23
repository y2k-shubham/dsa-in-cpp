// https://www.geeksforgeeks.org/array-rotation/#_=_

/*
8 1 3 7 4 2 9 -1
2
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <stdio.h>


using namespace std;

void readVec(vector <int>&);
void showVec(vector <int>);
void showVec(vector <int>, const char *);
int hcf(int, int);
void rotateVec1(vector <int>&, int);
void rotateVec2(vector <int>&, int);
void rotateVec3(vector <int>&, int);

int main() {
  vector <int> vec;
  readVec(vec);
  showVec(vec, "after input");

  int k;
  cout << "Enter rotation steps: ";
  cin >> k;

  rotateVec1(vec, k);
  showVec(vec, "after rotateVec1()");

    rotateVec2(vec, k);
    showVec(vec, "after rotateVec2()");

  return 0;
}

void readVec(vector <int>& vec) {
  int ele;

  cout << "Enter elements of vector:-" << endl;
  cout << "(Enter -1 to terminate)" << endl;
  cin >> ele;
  while (ele != -1) {
    vec.push_back(ele);
    cin >> ele;
  }
}

void showVec(vector <int> vec, const char * when) {
    cout << endl;
    printf("%s, array is:-\n", when);

    cout << "Ind:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "Val:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
}

void showVec(vector <int> vec) {
    printf(", array is:-\n");

    cout << "Ind:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "Val:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
}

void rotateVec1(vector <int>& vec, int k) {
    int len = vec.size();
    for (int i = 1; i <= k; i++) {
        int tmp = vec[0];
        for (int j = 0; j < (len - 1); j++) {
            vec[j] = vec[j + 1];
        }
        vec[len - 1] = tmp;
    }
}

void rotateVec2(vector <int>& vec, int k) {
    int len = vec.size();

    // tmp storage copy
    vector <int> vecTmp;
    for (int i = 0; i < k; i++) {
        vecTmp.push_back(vec[i]);
    }

    // move
    for (int i = 0; (i + k) < len; i++) {
        vec[i] = vec[i + k];
    }

    // revert tmp-storage copy
    for (int i = 0; i < k; i++) {
        vec[(len - k + i)] = vecTmp[i];
    }
}

int hcf(int big, int small) {
    int rem = big % small;
    if (rem == 0) {
        return small;
    } else {
        return hcf(small, rem);
    }
}
