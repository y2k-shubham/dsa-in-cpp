// LeetCode-834: https://leetcode.com/problems/sum-of-distances-in-tree
// incomplete

#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <list>
#include <stack>

using namespace std;

class Solution {
private:
    vector <list <int> > buildAdjList(int n, vector <vector <int> > &edges) {
        vector <list <int> > adjList(n);

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        return adjList;
    }

    unordered_map<int, int> buildSubtreeSizeMap(int n, vector <list <int> > &adjList) {
        unordered_map <int, int> subtreeSizeMap;

        vector <bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                continue;
            }

            stack <int> stk;
            stk.push(i);

            while (!stk.empty()) {
                int crr = stk.top();
                stk.pop();

                if (visited[crr]) {
                    continue;
                }
                visited[i] = true;


            }
        }
    }

    unordered_map<int, int> buildSubtreeSizeMap(int n, vector <list <int> > &adjList) {
        unordered_map <int, int> subtreeSizeMap;
        stack <pair <int, int> > st;
        st.push(make_pair(0, -1));

        while (!st.empty()) {
            pair <int, int> top = st.top();
            st.pop();

            int node = top.first;
            int parent = top.second;

            subtreeSizeMap[node] = 1;
            for (int child : adjList[node]) {
                if (child != parent) {
                    st.push(make_pair(child, node));
                    subtreeSizeMap[node] += subtreeSizeMap[child];
                }
            }
        }

        return subtreeSizeMap;
    }

public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {

    }
};
