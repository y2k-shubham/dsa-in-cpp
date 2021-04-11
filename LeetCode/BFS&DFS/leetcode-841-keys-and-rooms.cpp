// LeetCode-841: https://leetcode.com/problems/keys-and-rooms/

#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int numRooms = rooms.size();
        if (numRooms <= 1) {
            return true;
        }

        unordered_set<int> reachableRooms;
        reachableRooms = {0};

        queue<int> bfsQue;
        bfsQue.push(0);
        while (!bfsQue.empty()) {
            int crrRoom = bfsQue.front();
            bfsQue.pop();

            reachableRooms.insert(crrRoom);  // redundant

            vector<int> crrRoomKeys = rooms[crrRoom];
            for (int i = 0; i < crrRoomKeys.size(); i++) {
                int key = crrRoomKeys[i];

                if (reachableRooms.find(key) == reachableRooms.end()) {
                    reachableRooms.insert(key);
                    bfsQue.push(key);
                }
            }
        }

        for (int i = 0; i < numRooms; i++) {
            if (reachableRooms.find(i) == reachableRooms.end()) {
                return false;
            }
        }

        return true;
    }
};
