// https://www.geeksforgeeks.org/largest-subarray-with-equal-number-of-0s-and-1s/
// https://practice.geeksforgeeks.org/problems/largest-subarray-of-0s-and-1s/1

/*
1 0 1 1 1 0 0 -1
1 0 1 1 -1
1 1 1 1 -1
0 0 1 1 0 -1
1 0 0 0 1 1 -1
1 0 0 0 1 1 0 -1
1 1 0 0 0 1 1 1 0 -1
1 1 0 0 0 1 1 1 -1
1 1 0 0 1 1 1 -1
1 1 0 0 1 1 0 1 -1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <map>

using namespace std;

vector <int> input();
void showVec(vector <int>, const char *);
void showVecAns(vector <int>, const char *, int, pair <int, int>);
void findLongestEql0s1sSubArr(vector <int>);

int main() {
  vector <int> vec = input();
  showVec(vec, "vec");

  findLongestEql0s1sSubArr(vec);

  return 0;
}

void findLongestEql0s1sSubArr(vector <int> vec) {
  int zeroes = 0;
  int ones = 0;
  map <int, int> diffFirstIndMap;
  int maxRangeLen = 0;
  pair <int, int> maxRangeIndices = make_pair(-1, -1);
  int maxRangeNumZeroes = 0;

  diffFirstIndMap[0] = -1;
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == 1) {
      ones++;
    }
    zeroes = i - ones + 1;

    int diff = ones - zeroes;

    // printf("\n----------\n");
    // printf("at vec[i=%d] = %d\n", i, vec[i]);
    // printf("1s = %d\t0s = %d\tdiff = %d\n", ones, zeroes, diff);
    if (diffFirstIndMap.find(diff) == diffFirstIndMap.end()) {
      // printf("\nfirst occurence, setting map[diff=%d] = i=%d\n", diff, i);
      diffFirstIndMap[diff] = i;
    } else {
      int crrRangeLen = i - diffFirstIndMap[diff];
      // printf("\nfound earlier occurence, map[diff=%d] = %d\n", diff, diffFirstIndMap[diff]);
      // printf("crrRange = (i=%d - map[diff=%d]=%d) = %d\n", i, diff, diffFirstIndMap[diff], crrRangeLen);
      if (crrRangeLen > maxRangeLen) {
        // printf("\nexisting maxRange=%d < crrRange=%d, making   updates\n", maxRangeLen, crrRangeLen);
        maxRangeLen = crrRangeLen;
        maxRangeIndices.first = diffFirstIndMap[diff] + 1;
        maxRangeIndices.second = i;
        maxRangeNumZeroes = zeroes;
        // printf("maxRange = crrRange = %d,\tmaxRangeIndices = (%d, %d),\tmaxRangeZeroes = %d\n", maxRangeLen, maxRangeIndices.first, maxRangeIndices.second, maxRangeNumZeroes);
      } else {
        // printf("\nexisting maxRange=%d > crrRange=%d, skipping update\n", maxRangeLen, crrRangeLen);
      }
    }
    // printf("----------\n");
  }

  if (maxRangeLen > 0) {
    printf("\nLongest subarray having equal no of 0s & 1s\nno of 1s: %d\nspan    : arr[%d]=%d .. arr[%d]=%d\n", maxRangeNumZeroes, maxRangeIndices.first, vec[maxRangeIndices.first], maxRangeIndices.second, vec[maxRangeIndices.second]);
    showVecAns(vec, "vec", maxRangeNumZeroes, maxRangeIndices);
  } else {
    printf("\nThere's no subarray having equal no of 0s & 1s\n");
  }
}

vector <int> input() {
  vector <int> vec;
  int ele;

  printf("Enter elements of vector\n(-1 to terminate)\n");
  cin >> ele;
  while (ele != -1) {
    vec.push_back(ele);
    cin >> ele;
  }

  return vec;
}

void showVec(vector <int> vec, const char * name) {
  printf("\n%s vector is:-\n", name);

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

void showVecAns(vector <int> vec, const char * name, int maxRangeNumZeroes, pair <int, int> maxRangeIndices) {
  // printf("\nmax range subarray with equal no (%d) of 0s & 1s in %s vector is:-\n", maxRangeNumZeroes, name);

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

  printf("\t");
  for (int i = 0; i < vec.size(); i++) {
    if (i == maxRangeIndices.first || i == maxRangeIndices.second) {
      printf("^\t");
    } else {
      printf("\t");
    }
  }
  cout << endl;
}