// https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/
// Hard

/*
1 2 3 4 5 6 7 -1
8 9 10 -1

-1
4 -1

3 5 6 -1
3 5 6 -1

3 5 6 7 -1
3 5 6 -1

3 5 6 7 -1
3 -1

3 5 6 7 -1
9 10 -1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

vector <int> input(string);
pair <vector <int>, vector <int> > getVectorsBySize(vector <int>, vector <int>);
double findMedian(vector <int>, vector <int>);

int main () {
  vector <int> vec1 = input("vec1");
  vector <int> vec2 = input("vec2");

  if (!vec1.empty()) {
    sort(vec1.begin(), vec1.end());
  }
  if (!vec2.empty()) {
    sort(vec2.begin(), vec2.end());
  }

  pair <vector <int>, vector <int> > vecPair = getVectorsBySize(vec1, vec2);
  vector <int> vecShort = vec1;
  vector <int> vecLong = vec2;

  double median = findMedian(vecShort, vecLong);
  printf("median is %f\n", median);

  return 0;
}

vector <int> input(string name) {
  vector <int> vec;
  int ele;

  printf("Enter elements of %s:-\n(-1 to terminate)\n", name.c_str());

  cin >> ele;
  while (ele != -1) {
    vec.push_back(ele);
    cin >> ele;
  }

  return vec;
}

pair <vector <int>, vector <int> > getVectorsBySize(vector <int> vec1, vector <int> vec2) {
  if ((int) vec1.size() <= (int) vec2.size()) {
    return make_pair(vec1, vec2);
  } else {
    return make_pair(vec2, vec1);
  }
}

double findMedian(vector <int> vecShort, vector <int> vecLong) {
  int lenShort = (int) vecShort.size();
  int lenLong = (int) vecLong.size();
  int midInd = (lenShort + lenLong) / 2;

  int iShort = 0, iLong = 0;
  int iMerge = 0;
  int eleCrr, elePrev;
  if (lenShort == 0) {
    elePrev = eleCrr = vecLong[0];
  }

  while (iMerge <= midInd) {
    elePrev = eleCrr;
    iMerge++;
    if ((iLong == ((int) vecLong.size())) || ((iShort < ((int) vecShort.size())) && (vecShort[iShort] <= vecLong[iLong]))) {
      eleCrr = vecShort[iShort++];
    } else {
      eleCrr = vecLong[iLong++];
    }
  }

  double median;
  if (((lenShort + lenLong) % 2) == 0) {
    median = (elePrev + eleCrr) / 2.0;
  } else {
    median = eleCrr;
  }

  return median;
}
