// LeetCode-797: https://leetcode.com/problems/all-paths-from-source-to-target
// elementary DFS (dont even need visited set because it is DAG)

#include <list>
#include <vector>

using namespace std;

class Solution {
   private:
    void dfs(
        vector<vector<int>>& graph,
        int dstVert,
        list<list<int>>& allPaths,
        list<int>& crrPath,
        int crrVert) {
        int n = graph.size();
        if ((crrVert < 0) || (n <= crrVert)) {
            return;
        }

        crrPath.push_back(crrVert);
        if (crrVert == dstVert) {
            allPaths.push_back(crrPath);
            crrPath.pop_back();
            return;
        }

        for (vector<int>::iterator it = graph[crrVert].begin(); it != graph[crrVert].end(); it++) {
            dfs(
                graph,
                dstVert,
                allPaths,
                crrPath,
                *it);
        }

        crrPath.pop_back();
    }

    vector<vector<int>> convertToVec(list<list<int>>& allPathsList) {
        int numPaths = allPathsList.size();

        vector<vector<int>> allPathsVec(numPaths);
        int pathIdx = 0;
        for (list<list<int>>::iterator pathList = allPathsList.begin(); pathList != allPathsList.end(); pathList++) {
            vector<int> pathVec((*pathList).begin(), (*pathList).end());
            allPathsVec[pathIdx++] = pathVec;
        }

        return allPathsVec;
    }

    // LC submission - speed 44 ms (15 %tile), memory 20 MB (10 %tile)
    vector<vector<int>> soln1Indirect(vector<vector<int>>& graph) {
        int numNodes = graph.size();

        list<list<int>> allPathsList;
        list<int> crrPath;

        dfs(
            graph,
            numNodes - 1,
            allPathsList,
            crrPath,
            0);

        return convertToVec(allPathsList);
    }

    void dfs(
        vector<vector<int>>& graph,
        int dstVert,
        vector<vector<int>>& allPaths,
        vector<int>& crrPath,
        int crrVert) {
        int n = graph.size();
        if ((crrVert < 0) || (n <= crrVert)) {
            return;
        }

        crrPath.push_back(crrVert);
        if (crrVert == dstVert) {
            allPaths.push_back(crrPath);
            crrPath.pop_back();
            return;
        }

        for (vector<int>::iterator it = graph[crrVert].begin(); it != graph[crrVert].end(); it++) {
            dfs(
                graph,
                dstVert,
                allPaths,
                crrPath,
                *it);
        }

        crrPath.pop_back();
    }

    // LC submission - speed 4 ms (99 %tile), memory 10 MB (85 %tile)
    vector<vector<int>> soln2Direct(vector<vector<int>>& graph) {
        int numNodes = graph.size();

        vector<vector<int>> allPathsVec;
        vector<int> crrPath;

        dfs(
            graph,
            numNodes - 1,
            allPathsVec,
            crrPath,
            0);

        return allPathsVec;
    }

   public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        return soln2Direct(graph);
    }
};
