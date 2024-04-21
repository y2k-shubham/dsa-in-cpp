// LeetCode-1971: https://leetcode.com/problems/find-if-path-exists-in-graph (re-attempt-1)
// incomplete

#include <vector>
#include <list>
#include <cassert>
#include <queue>
#include <unordered_set>

using namespace std;

#define UNEXPLORED 'u'
#define IN_PROGRESS 'i'
#define EXPLORED 'e'

class Solution {
private:
    vector<list<int> > adjList;
    vector<char> srcBFSVertStatus;
    vector<char> dstBFSVertStatus;
    queue<int> srcBFSQue;
    queue<int> dstBFSQue;
    unordered_set<int> reachableVerts;

    void buildAdjList(int numVertices, vector<vector<int>>& edges) {
        adjList = {};
        srcBFSVertStatus = {};

        adjList.resize(numVertices, {});
        srcBFSVertStatus.resize(numVertices, UNEXPLORED);

        for (auto& edge: edges) {
            int src = edge[0];
            int dest = edge[1];

            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
    }

    bool startSrcBFS(int src, int dest) {
        srcBFSQue.push(src);
        return continueSrcBFS(src, dest);
    }

    bool continueSrcBFS(int src, int dest) {
        if (srcBFSQue.empty()) {
            return false;
        }

        // perform exploration of only one vertex

        int currVert = srcBFSQue.front();
        srcBFSQue.pop();

        if (currVert == dest) {
            return true;
        }

        srcBFSVertStatus[currVert] = IN_PROGRESS;

        for (auto& adjVert: adjList[currVert]) {
            if (adjVert == dest) {
                return true;
            }

            if (reachableVerts.find(adjVert) != reachableVerts.end()) {
                return true;
            }
            reachableVerts.insert(adjVert);

            if (srcBFSVertStatus[adjVert] == UNEXPLORED) {
                srcBFSQue.push(adjVert);
            }
        }

        srcBFSVertStatus[currVert] = EXPLORED;

        return false;
    }

    bool startDstBFS(int src, int dest) {
        dstBFSQue.push(dest);
        return continueDstBFS(src, dest);
    }

    bool continueDstBFS(int src, int dest) {
        if (dstBFSQue.empty()) {
            return false;
        }

        // perform exploration of only one vertex

        int currVert = dstBFSQue.front();
        dstBFSQue.pop();

        if (currVert == src) {
            return true;
        }

        dstBFSVertStatus[currVert] = IN_PROGRESS;

        for (auto& adjVert: adjList[currVert]) {
            if (adjVert == src) {
                return true;
            }

            if (reachableVerts.find(adjVert) != reachableVerts.end()) {
                return true;
            }
            reachableVerts.insert(adjVert);

            if (dstBFSVertStatus[adjVert] == UNEXPLORED) {
                dstBFSQue.push(adjVert);
            }
        }

        dstBFSVertStatus[currVert] = EXPLORED;

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

        if (startSrcBFS(source, destination) || startDstBFS(source, destination)) {
            return true;
        }
        while (!srcBFSQue.empty() && !dstBFSQue.empty()) {
            if (continueSrcBFS(source, destination) || continueDstBFS(source, destination)) {
                return true;
            }
        }

        return false;
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
