// LeetCode-1042: https://leetcode.com/problems/flower-planting-with-no-adjacent/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <vector>

using namespace std;

void testBuildGraph();
vector<set<int>> buildGraph(int N, vector<vector<int>>& paths);
pair<list<int>, set<int>> findValidColorsAndUncoloredNeighbors(set<int> neighbors, vector<int> color);
void pushToStack(stack<int>& stk, list<int> eles);
vector<int> colorGraph(int N, vector<set<int>> adjList);
vector<int> gardenNoAdj(int N, vector<vector<int>>& paths);

int main() {
    testBuildGraph();

    return 0;
}

void testBuildGraph() {
    vector<vector<int>> in;
    vector<set<int>> outExpected;
    vector<set<int>> outComputed;

    in = {};
    outExpected = {};
    outComputed = buildGraph(0, in);
    assert(outExpected == outComputed);
}

vector<set<int>> buildGraph(int N, vector<vector<int>>& paths) {
    vector<set<int>> adjList(N);
    // initialize empty adjList (empty set of neighbors per vertex)
    // for (int i = 0; i < N; i++) {
    //     set <int> empSet;
    //     adjList[i] = empSet;
    // }
    // fill up actual neighbors
    for (int i = 0; i < paths.size(); i++) {
        int v1 = paths[i][0];
        int v2 = paths[i][1];
        adjList[v1 - 1].insert(v2 - 1);
        adjList[v2 - 1].insert(v1 - 1);
    }
    return adjList;
}

pair<list<int>, set<int>> findValidColorsAndUncoloredNeighbors(set<int> neighbors, vector<int> color) {
    list<int> uncoloredNeighbors;
    // initialize remainingColors list with all validColors
    set<int> remColors = {1, 2, 3, 4};

    // iterate over neighbours of vtc
    for (set<int>::iterator n = neighbors.begin(); n != neighbors.end(); n++) {
        if (color[*n] == -1) {
            // if neighbour is uncolored, push it to stack
            uncoloredNeighbors.push_back(*n);
        } else {
            // else subtract neighbour's color from remaining colors
            remColors.erase(color[*n]);
        }
    }

    return make_pair(uncoloredNeighbors, remColors);
}

void pushToStack(stack<int>& stk, list<int> eles) {
    for (list<int>::iterator i = eles.begin(); i != eles.end(); i++) {
        stk.push(*i);
    }
}

vector<int> colorGraph(int N, vector<set<int>> adjList) {
    // create data-structures for downstream processing
    vector<int> color(N, -1);
    // traverse over vertices and color them (if not already colored)
    for (int i = 0; i < N; i++) {
        if (color[i] == -1) {
            if (adjList[i].empty()) {
                // if no neighbor, we can give any color
                color[i] = 1;
            } else {
                // else we have to perform DFS
                stack<int> stk;

                // push vertex to stack and begin DFS (continue until stack empty)
                stk.push(i);
                while (!stk.empty()) {
                    // take a vertex from stack, this is the vertex-to-color (vtc)
                    int vtc = stk.top();
                    stk.pop();

                    // find (1) uncolored neighbors (2) valid colors for this vertex
                    set<int> neighbors = adjList[vtc];
                    pair<list<int>, set<int>> unColoredNeighborsAndRemColors = findValidColorsAndUncoloredNeighbors(neighbors, color);

                    // push uncolored neighbors to stack
                    pushToStack(stk, unColoredNeighborsAndRemColors.first);

                    // color current vertex vtc
                    set<int> remColors = unColoredNeighborsAndRemColors.second;
                    if (remColors.empty()) {
                        // if there is no remaining color, there's no solution possible
                        cout << "no solution" << endl;
                        vector<int> empVec;
                        return empVec;
                    } else {
                        // else provide a valid color
                        color[vtc] = *(remColors.begin());
                    }
                }
            }
        }
    }

    return color;
}

vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
    // build the graph
    vector<set<int>> adjList = buildGraph(N, paths);
    vector<int> color = colorGraph(N, adjList);

    return color;
}
