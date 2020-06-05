// https://www.geeksforgeeks.org/longest-span-sum-two-binary-arrays/
// https://practice.geeksforgeeks.org/problems/longest-span-with-same-sum-in-two-binary-arrays/0

/*
0 1 0 0 0 0 -1
1 0 1 0 0 1 -1

0 1 0 1 1 1 1 -1
1 1 1 1 1 0 1 -1

0 0 0 -1
1 1 1 -1

0 0 1 -1
1 0 0 -1

1 -1
0 -1

0 -1
1 -1

1 -1
1 -1

0 1 -1
1 0 -1

0 1 -1
0 1 -1

1 1 -1
0 0 -1

0 0 -1
0 0 -1

1 1 -1
1 1 -1

1 1 0 1 0 0 1 1 -1
1 1 0 0 1 0 1 1 -1

0 1 0 1 0 0 1 1 -1
1 1 0 0 1 0 1 0 -1

0 1 0 0 0 0 -1
1 0 1 0 0 1 -1


1
6
0 1 0 0 0 0
1 0 1 0 0 1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <map>

using namespace std;

void driver();
void driverGfg();
vector <int> input(const char *);
vector <int> inputGfg(int);
void showVec(vector <int>, const char *);
vector <int> findPrefixSum(vector <int>);
void showVecAns(vector <int>, const char *, int, pair <int, int>);
pair <int, pair <int, int> > findLongestSpanSubArr(vector <int>, vector <int>);
void output(vector <int>, vector <int>, pair <int, int>, int);

int main() {
  // driver();
  driverGfg();

  return 0;
}

void driver() {
  vector <int> vec1 = input("vec1");
  vector <int> vec2 = input("vec2");
  showVec(vec1, "vec1");
  showVec(vec2, "vec2");

  vector <int> prefSum1 = findPrefixSum(vec1);
  vector <int> prefSum2 = findPrefixSum(vec2);
  showVec(prefSum1, "prefSum1");
  showVec(prefSum2, "prefSum2");

  pair <int, pair <int, int> > result = findLongestSpanSubArr(prefSum1, prefSum2);
  int maxRangeSum = result.first;
  pair <int, int> maxRangeIndices = result.second;
  output(vec1, vec2, maxRangeIndices, result.first);
}

void driverGfg() {
  int T;
  cin >> T;

  while (T-- > 0) {
    int N;
    cin >> N;

    vector <int> vec1 = inputGfg(N);
    vector <int> vec2 = inputGfg(N);
    // showVec(vec1, "vec1");
    // showVec(vec2, "vec2");

    vector <int> prefSum1 = findPrefixSum(vec1);
    vector <int> prefSum2 = findPrefixSum(vec2);

    pair <int, pair <int, int> > result = findLongestSpanSubArr(prefSum1, prefSum2);

    int maxSpanLength = result.second.second - result.second.first + 1;
    if (result.second.second == -1) {
      printf("0\n");
    } else {
      printf("%d\n", maxSpanLength);
    }
  }
}

pair <int, pair <int, int> > findLongestSpanSubArr(vector <int> prefSum1, vector <int> prefSum2) {
  map <int, int> diffFirstIndMap;
  int maxRangeLen = 0;
  pair <int, int> maxRangeIndices = make_pair(-1, -1);
  int maxRangeSum = 0;

  diffFirstIndMap[0] = -1;
  for (int i = 0; i < prefSum1.size(); i++) {
    int diff = prefSum2[i] - prefSum1[i];

    // printf("\n----------\n");
    // printf("at vec[i=%d] = %d\n", i, vec[i]);
    // printf("1s = %d\t0s = %d\tdiff = %d\n", ones1, zeroes, diff);
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

        int prevVal;
        if (maxRangeIndices.first <= 0) {
          prevVal = 0;
        } else {
          if (prefSum2[maxRangeIndices.first] - prefSum2[maxRangeIndices.first - 1] == 0) {
            prevVal = prefSum2[maxRangeIndices.first];
          } else {
            prevVal = prefSum2[maxRangeIndices.first] + 1;
          }
        }
        maxRangeSum = prefSum2[i] - prevVal;
        // printf("maxRange = crrRange = %d,\tmaxRangeIndices = (%d, %d),\tmaxRangeZeroes = %d\n", maxRangeLen, maxRangeIndices.first, maxRangeIndices.second, maxRangeSum);
      } else {
        // printf("\nexisting maxRange=%d > crrRange=%d, skipping update\n", maxRangeLen, crrRangeLen);
      }
    }
    // printf("----------\n");
  }

  return make_pair(maxRangeSum, maxRangeIndices);
}

void output(vector <int> vec1, vector <int> vec2, pair <int, int> maxRangeIndices, int maxRangeSum) {
  if (maxRangeIndices.second > -1) {
    printf("\nLongest spans having equal sums = %d is [%d]..[%d]\n", maxRangeSum, maxRangeIndices.first, maxRangeIndices.second);
    showVecAns(vec1, "vec1", maxRangeSum, maxRangeIndices);
    showVecAns(vec2, "vec2", maxRangeSum, maxRangeIndices);
  } else {
    printf("\nThere are no spans having equal sums\n");
  }
}

vector <int> findPrefixSum(vector <int> vec) {
  vector <int> prefixSum;
  
  int sum = 0;
  for (int i = 0; i < vec.size(); i++) {
    sum += vec[i];
    prefixSum.push_back(sum);
  }

  return prefixSum;
}

vector <int> input(const char * name) {
  vector <int> vec;
  int ele;

  printf("Enter elements of vector %s\n(-1 to terminate)\n", name);
  cin >> ele;
  while (ele != -1) {
    vec.push_back(ele);
    cin >> ele;
  }

  return vec;
}

vector <int> inputGfg(int N) {
  vector <int> vec;

  for (int i = 1; i <= N; i++) {
    int ele;
    cin >> ele;

    vec.push_back(ele);
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

void showVecAns(vector <int> vec, const char * name, int maxRangeSum, pair <int, int> maxRangeIndices) {
  printf("\nmax max span in %s vector is:-\n", name);

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