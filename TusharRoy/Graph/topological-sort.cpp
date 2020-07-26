// https://www.youtube.com/watch?v=ddTC4Zovtbc&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

using namespace std;

vector<set<int> > buildGraph(vector<pair<int, int> > edges);
void addEdge(vector<set<int> >& adjList, int src, int dst);
void topoDfs(vector<set<int> > adjList, stack<int>& completionStk, set<int>& visited, int vert);
void testBuildTopoSort();
vector<int> buildTopoSort(vector<set<int> > adjList);
int findIndex(vector<int> vec, int ele);
bool isValidTopoSort(vector<set<int> > adjList, vector<int> topoSort);

int main() {
  testBuildTopoSort();

  return 0;
}

vector<set<int> > buildGraph(vector<pair<int, int> > edges) {
    vector<set<int> > adjList;

    for (int i = 0; i < edges.size(); i++) {
        addEdge(adjList, edges[i].first, edges[i].second);
    }

    return adjList;
}

void addEdge(vector<set<int> >& adjList, int src, int dst) {
    adjList[src].insert(dst);
}

void topoDfs(vector<set<int> > adjList, stack<int>& completionStk, set<int>& visited, int vert) {
    visited.insert(vert);

    set<int> neighbors = adjList[vert];
    for (set<int>::iterator n = neighbors.begin(); n != neighbors.end(); n++) {
        if (visited.find(*n) != visited.end()) {
            topoDfs(adjList, completionStk, visited, *n);
        }
    }

    completionStk.push(vert);
}

void testBuildTopoSort() {
    vector<set<int> > adjList;
    vector<int> topoSort;

    adjList = {};
    topoSort = buildTopoSort(adjList);
    isValidTopoSort(adjList, topoSort);

    adjList = {{1}};
    topoSort = buildTopoSort(adjList);
    isValidTopoSort(adjList, topoSort);

    adjList = {{1, 2}, {2, 3, 4}, {}, {}, {}};
    topoSort = buildTopoSort(adjList);
    isValidTopoSort(adjList, topoSort);

    adjList = {
      {2},
      {2, 3},
      {4},
      {5},
      {5},
      {6},
      {}
    };
    topoSort = buildTopoSort(adjList);
    isValidTopoSort(adjList, topoSort);

    adjList = {
      {},
      {},
      {3},
      {1},
      {0, 1},
      {0, 2}
    };
    topoSort = buildTopoSort(adjList);
    isValidTopoSort(adjList, topoSort);

    adjList = {};
    topoSort = buildTopoSort(adjList);
    isValidTopoSort(adjList, topoSort);
}

vector<int> buildTopoSort(vector<set<int> > adjList) {
    if (adjList.empty()) {
        return {};
    } else {
        stack<int> completionStk;
        set<int> visited;
        for (int i = 0; i < adjList.size(); i++) {
            if (visited.find(i) != visited.end()) {
                topoDfs(adjList, completionStk, visited, i);
            }
        }

        vector<int> topoSort;
        while (!completionStk.empty()) {
            topoSort.push_back(completionStk.top());
            completionStk.pop();
        }

        return topoSort;
    }
}

int findIndex(vector<int> vec, int ele) {
    // https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
    auto it = find(vec.begin(), vec.end(), ele);

    // If element was found
    if (it != vec.end()) {
        // calculating the index
        // of K
        int index = distance(vec.begin(), it);
        return index;
    } else {
        // If the element is not
        // present in the vector
        return -1;
    }
}

bool isValidTopoSort(vector<set<int> > adjList, vector<int> topoSort) {
    for (int i = 0; i < adjList.size(); i++) {
        int srcInd = findIndex(topoSort, i);
        for (set<int>::iterator j = adjList[i].begin(); j != adjList[i].end(); j++) {
            int dstInd = findIndex(topoSort, *j);
            if (srcInd >= dstInd) {
                return false;
            }
        }
    }
    return true;
}
