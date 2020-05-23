// Uber
// https://www.geeksforgeeks.org/print-all-pairs-in-an-unsorted-array-with-equal-sum/
// https://leetcode.com/discuss/interview-question/306690/uber-onsite-question-pairs-with-equal-sums

/*
6 4 12 10 22 54 32 42 21 11 -1
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

vector <int> input();
void showVec(vector <int>, string);
pair <int, int> findMinMaxPairSums(vector <int>);
set <pair <int, int> > findAllPairsWithSum(vector <int>, int);
void showPairsSet(set <pair <int, int> >, string);;

int main() {
  // input vector
  vector <int> vec = input();
  showVec(vec, "before sorting");

  // sort vector
  sort(vec.begin(), vec.end());
  showVec(vec, "after sorting");

  // find min and max possible sums for any pair
  pair <int, int> minMaxPairSums = findMinMaxPairSums(vec);
  for (int i = minMaxPairSums.first; i <= minMaxPairSums.second; i++) {
    // for each sum in range [minPossibleSum, maxPossibleSum],
    // find and all pairs of elements that add upto that sum (doable in linear time)
    set <pair <int, int> > pairsSet = findAllPairsWithSum(vec, i);
    // if one or more such pair of elements exist, print them
    if (!pairsSet.empty()) {
      ostringstream oss;
      oss << "pairsSet(" << i << ")";
      showPairsSet(pairsSet, oss.str());
    }
  }

  return 0;
}

vector <int> input() {
  vector <int> vec;
  int ele;

  cout << "Enter elements of array:-\n(-1 to terminate)\n";
  cin >> ele;
  do {
    vec.push_back(ele);
    cin >> ele;
  } while (ele != -1);

  return vec;
}

void showVec(vector <int> vec, string when) {
  cout << endl << when << ", the vector is:-" << endl;

  for (int i = 0; i < (int) vec.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  for (int i = 0; i < (int) vec.size(); i++) {
    printf("%d\t", vec[i]);
  }
  cout << endl;
}

pair <int, int> findMinMaxPairSums(vector <int> vec) {
  int minSum = vec[0] + vec[1];
  int len = (int) vec.size();
  int maxSum = vec[len - 2] + vec[len - 1];
  return make_pair(minSum, maxSum);
}

set <pair <int, int> > findAllPairsWithSum(vector <int> vec, int reqSum) {
  set <pair <int, int> > pairsSet;

  int iLo = 0;
  int iHi = ((int) vec.size()) - 1;
  while (iLo < iHi) {
    int crrSum = vec[iLo] + vec[iHi];
    if (crrSum < reqSum) {
      iLo++;
    } else if (crrSum > reqSum) {
      iHi--;
    } else {
      pairsSet.insert(make_pair(vec[iLo], vec[iHi]));
      int crrLoEle = vec[iLo];
      int crrHiEle = vec[iHi];
      while (iLo < iHi && vec[iLo] == crrLoEle) {
        iLo++;
      }
      while (iLo < iHi && vec[iHi] == crrHiEle) {
        iHi--;
      }
    }
  }

  return pairsSet;
}

void showPairsSet(set <pair <int, int> > pairsSet, string name) {
  cout << endl << name << " is:-" << endl;
  for (set <pair <int, int > >::iterator it = pairsSet.begin(); it != pairsSet.end(); it++) {
    printf("(%d, %d)\t", (* it).first, (* it).second);
  }
  cout << endl;
}
