// https://leetcode.com/contest/biweekly-contest-30/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/
// the solution has been created for 'k' moves
// without map empty checks (throughout the code), it was throwing "c++ AddressSanitizer:DEADLYSIGNAL address points to zero page"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

void showMap(map<int, int> mMap) {
    if (mMap.empty()) {
      printf("\nmap is empty\n");
    } else {
      printf("\nmap is:-\n");
      for (map<int, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
          printf("%d->%d ", (*it).first, (*it).second);
      }
      cout << endl;
    }
}

map<int, int> buildFreqMap(vector<int> vec) {
    map<int, int> mMap;
    for (int i = 0; i < vec.size(); i++) {
        if (mMap.find(vec[i]) == mMap.end()) {
            mMap.insert(make_pair(vec[i], 1));
        } else {
            mMap[vec[i]]++;
        }
    }
    return mMap;
}

int findMinMaxDiff(map<int, int> mMap, bool debug) {
  if (mMap.empty()) {
    if (debug) {
      printf("---\nMap is empty, diff = 0\n---\n");
    }
    return 0;
  } else {
    map<int, int>::iterator it = mMap.end();
    it--;
    int maxEle = (*it).first;
    int minEle = (*mMap.begin()).first;
    int diff = (maxEle - minEle);

    if (debug) {
        printf("---\nminEle = %d, maxEle = %d, diff = %d\n---\n", minEle, maxEle, diff);
    }

    return diff;
  }
}

void addEle(map<int, int>& mMap, int ele, const char* which, bool debug) {
    if (mMap.find(ele) == mMap.end()) {
        mMap.insert(make_pair(ele, 1));
    } else {
        mMap[ele]++;
    }
    if (debug) {
        printf("added %s = %d back into map\n", which, ele);
    }
}

void removeEle(map<int, int>& mMap, int ele) {
    mMap[ele]--;
    if (mMap[ele] == 0) {
        mMap.erase(ele);
    }
}

int removeMinEle(map<int, int>& mMap, bool debug) {
    int minEle = (*mMap.begin()).first;
    removeEle(mMap, minEle);
    if (debug) {
        printf("removed minEle = %d from map\n", minEle);
    }
    return minEle;
}

int removeMaxEle(map<int, int>& mMap, bool debug) {
    map<int, int>::iterator it = mMap.end();
    it--;
    int maxEle = (*it).first;
    removeEle(mMap, maxEle);
    if (debug) {
        printf("removed maxEle = %d from map\n", maxEle);
    }
    return maxEle;
}

int minDiffRec(map<int, int>& mMap, int k, bool debug) {
    if (debug) {
        showMap(mMap);
    }

    if (mMap.empty()) {
      if (debug) {
        printf("map became empty, returning diff = 0\n");
      }
      return 0;
    } else if (k == 0) {
        return findMinMaxDiff(mMap, debug);
    } else {
        int minEle = removeMinEle(mMap, debug);
        int res1 = minDiffRec(mMap, k - 1, debug);
        addEle(mMap, minEle, "minEle", debug);

        if (res1 == 0) {
          return res1;
        } else {
          int maxEle = removeMaxEle(mMap, debug);
          int res2 = minDiffRec(mMap, k - 1, debug);
          addEle(mMap, maxEle, "maxEle", debug);

          return min(res1, res2);
        }
    }
}

int minDifference(vector<int>& nums, bool debug) {
    map<int, int> mMap = buildFreqMap(nums);
    return minDiffRec(mMap, 3, debug);
}

int main() {
    vector<int> vec = {1, 3, 8};
    bool debug = true;
    printf("%d\n", minDifference(vec, debug));

    return 0;
}
