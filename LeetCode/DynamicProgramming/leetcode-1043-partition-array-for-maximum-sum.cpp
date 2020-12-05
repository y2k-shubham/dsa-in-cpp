// LeetCode-1043: https://leetcode.com/problems/partition-array-for-maximum-sum/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> maxSumEnding;
    map<int, int> indEleMap;
    map<int, set<int> > eleIndsMap;

    void removeIndFromMaps(int ind) {
        if (indEleMap.find(ind) != indEleMap.end()) {
            int ele = indEleMap[ind];
            indEleMap.erase(ind);

            eleIndsMap[ele].erase(ind);
            if (eleIndsMap[ele].empty()) {
                eleIndsMap.erase(ele);
            }
        }
    }

    void addIndToMaps(int ind) {
        if (ind < vec.size()) {
            int ele = vec[ind];
            indEleMap[ind] = ele;
            eleIndsMap[ele].insert(ind);
        }
    }

    int getMaxEleFromMaps() {
      map <int, set <int> >::iterator it = eleIndsMap.end();
      it--;
      return (*it).first;
    }

   public:
    vector<int> vec;
    int k;

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
      this->vec = arr;
      this->k = k;
      
      // first k elements
      for (int i = 0; i < k; i++) {
        addIndToMaps(i);
        
        int maxEle = getMaxEleFromMaps();
        
        int maxSum = maxEle * (i + 1);
        this->maxSumEnding.push_back(maxSum);
      }

      // subsequent windows of len k
      for (int i = k; i < this->vec.size(); i++) {
        removeIndFromMaps(i - k);
        addIndToMaps(i);

        int maxEleLastK = getMaxEleFromMaps();
        int maxSumLastK = maxEleLastK * (i + 1);
        
      }
    }
};

int main() {
    return 0;
}
