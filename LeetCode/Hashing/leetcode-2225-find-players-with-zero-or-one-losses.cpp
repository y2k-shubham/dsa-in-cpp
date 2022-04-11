// LeetCode-2225: https://leetcode.com/problems/find-players-with-zero-or-one-losses/
// stupid time-waster problem; please skip

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> filterKeysWithVal(unordered_map<int, int>& mMap, int val) {
        vector<int> vec;
        for (unordered_map<int, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            if (it->second == val) {
                vec.push_back(it->first);
            }
        }

        sort(vec.begin(), vec.end());
        return vec;
    }

    vector<int> findSetDiff(
            unordered_set<int>& setKeep,
            unordered_set<int>& setRemove
    ) {
        vector<int> diffVec;
        for (unordered_set<int>::iterator it = setKeep.begin(); it != setKeep.end(); it++) {
            if (setRemove.find(*it) == setRemove.end()) {
                diffVec.push_back(*it);
            }
        }

        sort(diffVec.begin(), diffVec.end());
        return diffVec;
    }

public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, int> numLossesMap;
        unordered_set<int> allPlayers;
        unordered_set<int> lostPlayers;

        for (int i = 0; i < matches.size(); i++) {
            int playerWon = matches[i][0];
            int playerLost = matches[i][1];

            allPlayers.insert(playerWon);
            allPlayers.insert(playerLost);
            lostPlayers.insert(playerLost);

            numLossesMap[playerLost]++;
        }

        vector<int> undefeatedPlayers = findSetDiff(allPlayers, lostPlayers);
        vector<int> lost1TimePlayers = filterKeysWithVal(numLossesMap, 1);

        return {undefeatedPlayers, lost1TimePlayers};
    }
};
