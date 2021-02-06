// 2nd part of LC-1353: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
// biweekly contest 45 feb 2021: https://leetcode.com/contest/biweekly-contest-45/problems/maximum-number-of-events-that-can-be-attended-ii/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

class Event {
  public:
  int start;
  int end;
  int val;

  // sorting vector of user defined class https://stackoverflow.com/a/29676323/3679900
  bool operator<(const Event& other) {
    return (this->end < other.end) || (this->start < other.start) || (this->val < other.val);
  }
};

class Solution {
private:
  vector <Event> convertToEvents(vector <vector <int> >& events) {
    int len = events.size();
    vector <Event> parsedEvents(len);

    for (int i = 0; i < len; i++) {
      parsedEvents[i].start = events[i][0];
      parsedEvents[i].end = events[i][1];
      parsedEvents[i].val = events[i][2];
    }

    return parsedEvents;
  }

  int findFloorInd(vector <pair <int, int> >& maxGainTillDay, int lo, int hi, int day) {
    int len = hi - lo + 1;

    if (len <= 0) {
      return -1;
    } else if (len == 1) {
      if (day <= maxGainTillDay[lo].first) {
        return lo;
      } else {
        return -1;
      }
    } else if (len == 2) {
      if (day <= maxGainTillDay[hi].first) {
        return hi;
      } else if (day <= maxGainTillDay[lo].first) {
        return lo;
      } else {
        return -1;
      }
    } else {
      int mid = (lo + hi) / 2;

      if (day < maxGainTillDay[mid].first) {
        return findFloorInd(maxGainTillDay, lo, mid - 1, day);
      } else if (day == maxGainTillDay[mid].first) {
        return mid;
      } else {
        return findFloorInd(maxGainTillDay, mid + 1, hi, day);
      }
    }
  }

public:
    int maxValue(vector<vector<int>>& events, int k) {
        
    }
};
