// LeetCode-547: https://leetcode.com/problems/number-of-provinces/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    void showNodeParentMap(unordered_map<int, int>& nodeParentMap, string event) {
        printf("after %s, nodeParentMap is:-\n", event.c_str());
        for (
            unordered_map<int, int>::iterator it = nodeParentMap.begin();
            it != nodeParentMap.end();
            it++) {
            printf("node=%d, immedParent=%d, ultimParent=%d\n", it->first, it->second, findParent(nodeParentMap, it->second));
        }
    }

    int findParent(unordered_map<int, int>& nodeParentMap, int node) {
        if (nodeParentMap.find(node) == nodeParentMap.end()) {
            nodeParentMap[node] = node;
            return node;
        }

        int immediateParent = nodeParentMap[node];
        if (immediateParent == node) {
            return node;
        }

        int ultimateParent = findParent(nodeParentMap, immediateParent);
        nodeParentMap[node] = ultimateParent;

        return ultimateParent;
    }

    unordered_map<int, int> buildNodeParentMap(vector<vector<int>>& isConnected) {
        unordered_map<int, int> nodeParentMap;
        int numNodes = isConnected.size();

        for (int i = 0; i < numNodes; i++) {
            int crrNode = i;
            int crrNodeParent = findParent(nodeParentMap, crrNode);

            // we only scan lower half (triangle) of matrix as it is an undirected graph
            // (meaning that matrix would be symmetric)
            for (int j = 0; j < i; j++) {
                if (i == j) {
                    continue;
                }

                int crrNeighbor = j;
                if (isConnected[crrNode][crrNeighbor] == 1) {
                    int crrNeighborParent = findParent(nodeParentMap, crrNeighbor);
                    // connect the two sub-graphs
                    // (would have any effect only when they are NOT already connected)
                    nodeParentMap[crrNeighborParent] = crrNodeParent;
                }
            }
        }

        return nodeParentMap;
    }

    int countNumComponents(unordered_map<int, int>& nodeParentMap) {
        unordered_set<int> parents;
        for (
            unordered_map<int, int>::iterator it = nodeParentMap.begin();
            it != nodeParentMap.end();
            it++) {
            parents.insert(findParent(nodeParentMap, it->second));
        }

        return parents.size();
    }

   public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int numNodes = isConnected.size();
        if (numNodes <= 1) {
            return numNodes;
        }

        unordered_map<int, int> nodeParentMap = buildNodeParentMap(isConnected);
        // showNodeParentMap(nodeParentMap, "building");

        return countNumComponents(nodeParentMap);
    }
};
