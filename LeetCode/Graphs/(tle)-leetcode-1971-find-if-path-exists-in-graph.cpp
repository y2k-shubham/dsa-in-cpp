// LeetCode-1971: https://leetcode.com/problems/find-if-path-exists-in-graph
// all test cases passed but time limit exceeded (on an easy problem!)
// constraints are tough: upto 2x10^5 vertices and 2x10^5 edges

#include <vector>
#include <list>
#include <cassert>
#include <queue>

using namespace std;

#define UNEXPLORED 'u'
#define IN_PROGRESS 'i'
#define EXPLORED 'e'

class Solution {
private:
    vector<list<int> > adjList;
    vector<char> vertStatus;

    void buildAdjList(int numVertices, vector<vector<int>>& edges) {
        adjList = {};
        vertStatus = {};

        adjList.resize(numVertices, {});
        vertStatus.resize(numVertices, UNEXPLORED);

        for (auto& edge: edges) {
            int src = edge[0];
            int dest = edge[1];

            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }

    bool doesPathExistBFS(int src, int dest) {
        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int currVert = q.front();
            q.pop();

            if (currVert == dest) {
                return true;
            }

            vertStatus[currVert] = IN_PROGRESS;

            for (auto& adjVert: adjList[currVert]) {
                if (adjVert == dest) {
                    return true;
                }

                if (vertStatus[adjVert] == UNEXPLORED) {
                    q.push(adjVert);
                }
            }

            vertStatus[currVert] = EXPLORED;
        }

        return false;
    }

public:
    friend class SolutionTest;

    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) {
            return true;
        }
        if (n == 1) {
            return false;
        }
        if (edges.empty()) {
            return false;
        }
        if (source < 0 || source >= n || destination < 0 || destination >= n) {
            return false;
        }

        buildAdjList(n, edges);
        return doesPathExistBFS(source, destination);
    }
};

class SolutionTest {
public:
    void testValidPath() {
        Solution soln = Solution();
        int n;
        vector<vector<int>> edges;
        bool outExpected, outComputed;

        n = 3;
        edges = {{0, 1},
                 {1, 2},
                 {2, 0}};
        outExpected = true;
        outComputed = soln.validPath(n, edges, 0, 2);
        assert(outExpected == outComputed);

        n = 6;
        edges = {{0, 1},
                 {0, 2},
                 {3, 5},
                 {5, 4},
                 {4, 3}};
        outExpected = false;
        outComputed = soln.validPath(n, edges, 0, 5);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testValidPath();

    return 0;
}
