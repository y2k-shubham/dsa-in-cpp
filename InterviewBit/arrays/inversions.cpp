// https://www.interviewbit.com/problems/inversions/
// https://www.geeksforgeeks.org/counting-inversions/
// https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1
// Tech-Dose: https://www.youtube.com/watch?v=owZhw-A0yWE&t=965s

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
  private:
  vector <int> convertToVec(int arr[]) {
    // convert array to std::vector https://stackoverflow.com/a/8777619/3679900
    vector<int> vec(arr, arr + (sizeof(arr) / sizeof(arr[0])));
    return vec;
  }

  int mergeSort(vector <int>& vec, int lo, int hi) {
    int len = hi - lo + 1;

    int lInv, rInv, crrInv;
    if (len > 1) {
      int mid = (lo + hi) / 2;
      
      lInv = mergeSort(vec, lo, mid);
      rInv = mergeSort(vec, mid + 1, hi);
      
      crrInv = merge(vec, lo, hi);
    }

    return (lInv + crrInv + rInv);
  }

  int merge(vector <int>& vec, int lo, int hi) {
    int len = hi - lo + 1;
    vector <int> aux(len);

    int mid = (lo + hi) / 2;

    int lo1 = 0;
    int hi1 = mid;
    int i1 = lo1;

    int lo2 = 0;
    int hi2 = hi;
    int i2 = lo2;

    int i = 0;

    int numInv = 0;
    while ((i1 <= hi1) && (i2 <= hi2)) {
      if (vec[i1] < vec[i2]) {
        aux[i] = vec[i1];
        i1++;
      } else {
        aux[i] = vec[i2];
        i2++;

        numInv += hi1 - i1 + 1;
      }
      i++;
    }

    while (i1 <= hi1) {
      aux[i] = vec[i1];
      i1++;
      i++;
    }

    while (i2 <= hi2) {
      aux[i] = vec[i2];
      i2++;
      i++;
    }

    return numInv;
  }
};
