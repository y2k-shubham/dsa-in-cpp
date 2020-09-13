// https://www.interviewbit.com/problems/largest-distance-between-nodes-of-a-tree/
// https://www.geeksforgeeks.org/longest-path-undirected-tree/

// simple DFS / disjoint set

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include <list>

using namespace std;


class Depth {
    
    public:
    
    int d1, d2;
    int p1, p2;
    
    Depth() {
        this->d1 = -1;
        this->p1 = -1;
        this->d2 = -1;
        this->p2 = -1;
    }
};

map <int, list <int> > buildAdjList(vector <int>& vec) {
  map <int, list <int> > adjList;

  for (int i = 0; i < vec.size(); i++) {
    int child = i;
    int parent = vec[i];

    if (parent != -1) {
      adjList[parent].push_back(child);
    }
  }

  return adjList;
}

Depth findDepth(map <int, list <int> >& adjList, map <int, Depth>& dMap, int v) {
  if (dMap.find(v) != dMap.end()) {
    // already calculated
    return dMap[v];
  } else if (adjList.find(v) != adjList.end()) {
    // non-leaf node

    Depth pD = Depth();
    list <int> children = adjList[v];
    for (list <int>::iterator i = children.begin(); i != children.end(); i++) {
      Depth cD = findDepth(adjList, dMap, *i);

      if (cD.d1 > pD.d1) {
        // copy 1st depth to 2nd depth
        pD.d2 = pD.d1;
        pD.p2 = pD.p1;

        // update 1st depth
        pD.d1 = cD.d1;
        pD.p1 = cD.p1;
      } else if (cD.d1 > pD.d2) {
        // udpate 2nd depth
        pD.d2 = cD.d1;
        pD.p2 = cD.p1;
      }
    }

    // accomodate addition to height by current node itself
    pD.d1++;
    pD.d2++;

    // update map and return result
    dMap[v] = pD;
    return pD;
  } else {
    // leaf node

    Depth d = Depth();
    d.d1 = 0;
    return d;
  }
}

map <int, Depth> buildDMap(map <int, list <int> >& adjList) {
  map <int, Depth> dMap;
  for (map <int, list <int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
    int v = (*i).first;
    dMap[v] = findDepth(adjList, dMap, v);
  }

  return dMap;
}

int findMaxDist(map <int, Depth>& dMap) {
  int maxDist = 0;
  for (map <int, Depth>::iterator i = dMap.begin(); i != dMap.end(); i++) {
    Depth d = (*i).second;

    int crrDist = d.d1 + max(d.d2, 0);
    maxDist = max(maxDist, crrDist);
  }

  return maxDist;
}

int findResult(vector <int>& vec) {
  map <int, list <int> > adjList = buildAdjList(vec);
  map <int, Depth> dMap = buildDMap(adjList);
  return findMaxDist(dMap);
}

int solve(vector<int> &vec) {
    return findResult(vec);
}


