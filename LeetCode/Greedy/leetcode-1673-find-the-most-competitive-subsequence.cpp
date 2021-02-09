// LeetCode-1673: https://leetcode.com/problems/find-the-most-competitive-subsequence/

#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
   private:
    map<int, vector<int> > buildIndexMap(vector<int>& nums) {
        map<int, vector<int> > indexMap;

        for (int i = 0; i < nums.size(); i++) {
            indexMap[nums[i]].push_back(i);
        }

        return indexMap;
    }

  vector <int> buildCompSubseq(vector <int>& nums, int k, map <int, vector <int> >& indMap) {
    vector <int> compSubseq(k);

    int crrLen = 0;
    for (map <int, vector <int> >::iterator it = indMap.begin(); it != indMap.end(); it++) {
      
    }
  }

   public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
    }
};

int main() {
    return 0;
}
