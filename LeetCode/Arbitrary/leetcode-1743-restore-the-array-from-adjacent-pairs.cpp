// LeetCode-1743: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/

#include <list>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <utility>
#include <tuple>

using namespace std;

class Solution {
private:
    unordered_map<int, list<int>> firstEleListMap;
    unordered_map<int, int> lastEleFirstEleMap;
    unordered_set<int> seenEles;

    inline pair <int, int> getSortedPair(pair <int, int> mPair) {
        return (mPair.first < mPair.second) ? mPair : make_pair(mPair.second, mPair.first);
    }
    
    inline bool isSeenEle(int ele) {
        return (seenEles.find(ele) != seenEles.end());
    }

    inline bool isFirstEle(int ele) {
        return isSeenEle(ele) && (lastEleFirstEleMap.find(ele) != lastEleFirstEleMap.end());
    }

    inline bool isLastEle(int ele) {
        return isSeenEle(ele) && (lastEleFirstEleMap.find(ele) != lastEleFirstEleMap.end());
    }
    
    inline tuple<bool, bool, bool> getMembership(int ele) {
        return {
                isSeenEle(ele),
                isFirstEle(ele),
                isLastEle(ele)
        };
    }

    void addPair(pair <int, int> sortedPair) {
        tuple <bool, bool, bool> memberShipFirst = getMembership(sortedPair.first);
        tuple <bool, bool, bool> memberShipSecond = getMembership(sortedPair.second);
        
        if (!get<0>(memberShipFirst) && !get<0>(memberShipSecond)) {
            // neither elements are members
            firstEleListMap[sortedPair.first] = {sortedPair.first, sortedPair.second};
            lastEleFirstEleMap[sortedPair.second] = sortedPair.first;
        } else if (get<0>(memberShipFirst) && get<0>(memberShipSecond)) {
            // both elements are members
            if (get<1>(memberShipFirst)) {
                list <int> mList = firstEleListMap[sortedPair.first];
                int mListLastEle = mList.back();
            } else {
                
            }
        } else if (get<0>(memberShipFirst) && !get<0>(memberShipSecond)) {
            // first element is member, second is not
        } else {
            // first element is not member, second is member
        }
        
        seenEles.insert(sortedPair.first);
        seenEles.insert(sortedPair.second);
    }

public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {

    }
};
