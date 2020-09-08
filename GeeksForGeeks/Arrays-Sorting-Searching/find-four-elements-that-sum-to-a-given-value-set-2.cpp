// https://www.geeksforgeeks.org/find-four-elements-that-sum-to-a-given-value-set-2/
// Time: O(n^2 . logn) Space: O(n^2)

// it's O(n^3) time solution is https://www.geeksforgeeks.org/find-four-numbers-with-sum-equal-to-given-sum/
// which is same as LeetCode-18: https://leetcode.com/problems/4sum

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class PairSum {
  public:
  int sum;
  int ind1;
  int ind2;

  PairSum(int sum, int ind1, int ind2) {
    this->sum = sum;
    this->ind1 = ind1;
    this->ind2 = ind2;
  }

  // STL sort comparator for class https://stackoverflow.com/a/1380487/3679900
  bool operator <(const PairSum& rhs) {
    return this->sum < rhs.sum;
  }
};


int main() {
  return 0;
}

pair <vector <int>, int> input() {
  int N;
  cin >> N;
  vector <int> vec(N);
  for (int i = 0; i < N; i++) {
    cin >> vec[i];
  }

  int reqSum;
  cin >> reqSum;

  return make_pair(vec, reqSum);
}

vector <PairSum> buildPairSum(vector <int> vec) {
  int len = vec.size();
  int pairSumLen = (len * (len - 1)) / 2;
  vector <PairSum> pairSum(pairSumLen);

  int k = 0;
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      pairSum[k++] = PairSum(vec[i] + vec[j], i, j);
    }
  }

  return pairSum;
}

bool hasCommonIndex(PairSum p1, PairSum p2) {
  return (
    (p1.ind1 == p2.ind1) ||
    (p1.ind2 == p2.ind2) ||
    (p1.ind1 == p2.ind2) ||
    (p1.ind2 == p2.ind1)
  );
}

vector <vector <int> > findQuads(vector <int> vec, vector <PairSum> pairSum, int reqSum) {
  sort(pairSum.begin(), pairSum.end());
}
