// LeetCode-406: https://leetcode.com/problems/queue-reconstruction-by-height/
// wrong

#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
private:
    map<int, list<int> > prepareMap(vector<vector<int> >& people) {
        map<int, list<int> > mMap;

        for (int i = 0; i < people.size(); i++) {
            mMap[people[i][1]].push_back(people[i][0]);
        }

        return mMap;
    }

    // unused fn
    map<int, list<int> > sortMapItems(map<int, list<int> >& mMap) {
        map<int, list<int> > sortedMMap;

        for (auto it = mMap.begin(); it != mMap.end(); it++) {
            int diff = it->first;

            list<int> mList = it->second;
            mList.sort();

            sortedMMap[diff] = mList;
        }

        return sortedMMap;
    }

    vector<vector<int> > constructQue(int len, map<int, list<int> >& mMap) {
        vector<vector<int> > queVec(len);
        int qIdx = 0;

        for (auto it1 = mMap.begin(); it1 != mMap.end(); it1++) {
            int diff = it1->first;

            list<int> mList = it1->second;
            mList.sort();

            for (auto it2 = mList.begin(); it2 != mList.end(); it2++) {
                queVec[qIdx++] = {*it2, diff};
            }
        }

        return queVec;
    }

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int len = people.size();
        if (len <= 1) {
            return people;
        }

        map<int, list<int> > mMap = prepareMap(people);

        vector<vector<int> > queVec = constructQue(len, mMap);
        return queVec;
    }
};

