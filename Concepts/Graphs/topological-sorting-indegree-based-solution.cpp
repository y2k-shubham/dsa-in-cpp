// https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
// Kahn's algorithm

/*
acyclic graph
5 2     5 0     4 0     4 1     2 3     3 1     -1 -1

cyclic graph: will give proper error message
0 1     0 2     1 3     1 4     2 5     3 0     3 5     4 3     5 4     -1 -1

disconnected graph: will give correct answer
5 2     5 0     4 0     4 1     2 3     3 1     6 7     -1 -1
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <vector>
#include <set>
// g++ -std=c++11 Concepts/Graphs/topological-sorting-indegree-based-solution.cpp
#include <tuple>
#include <utility>

using namespace std;
#define isVisited(visitedSet, crrVert) (visitedSet.find(crrVert) != visitedSet.end())

map <int, set <int> > inputGraph();
void addEdge(map <int, set <int> >&, int, int);
void showGraph(map <int, set <int> >);

set <int> findAllVertices(map <int, set <int> >);
void showVertices(set <int>);
map <int, int> buildInDegreesMap(map <int, set <int> >, set <int>);
void showInDegrees(map <int, int>);

queue <int> findZeroInDegreeVertices(map <int, int>);
tuple <list <int>, bool> findTopoSort(map <int, set <int> >, map <int, int>, queue <int>);
void showTopoList(list <int>);

int main() {
  map <int, set <int> > adjList = inputGraph();
  showGraph(adjList);

  set <int> vertices = findAllVertices(adjList);
  showVertices(vertices);

  map <int, int> inDegrees = buildInDegreesMap(adjList, vertices);
  showInDegrees(inDegrees);

  queue <int> mQue = findZeroInDegreeVertices(inDegrees);
  if (mQue.empty()) {
    printf("\nTopo-sort cannot be determined since graph has cycle\n");
  } else {
    tuple <list <int>, bool> topoSortOutput = findTopoSort(adjList, inDegrees,  mQue);
    list <int> topoList = get <0> (topoSortOutput);
    bool isPossible = get <1> (topoSortOutput);

    if (isPossible) {
      showTopoList(topoList);
    } else {
      printf("\nTopo-sort cannot be determined since there are unvisited vertices left in the graph\n");
    }
  }

  return 0;
}

map <int, set <int> > inputGraph() {
  map <int, set <int> > adjList;
  int src, dst;

  printf("Enter edges of graph:-\n[Enter (-1, -1) to terminate]\n");
  cin >> src >> dst;
  while (src != -1 && dst != -1) {
    addEdge(adjList, src, dst);
    cin >> src >> dst;
  }

  return adjList;
}

void addEdge(map <int, set <int> >& adjList, int src, int dst) {
  if (adjList.find(src) == adjList.end()) {
    set <int> neighbours;
    adjList[src] = neighbours;
  }
  adjList[src].insert(dst);
}

void showGraph(map <int, set <int> > adjList) {
  printf("\ngraph is:-\n");

  for (map <int, set <int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
    printf("[%d]\t->\t", (*i).first);
    set <int> neighbours = (*i).second;
    for (set <int>::iterator j = neighbours.begin(); j != neighbours.end(); j++) {
      printf("%d\t", *j);
    }
    cout << endl;
  }
  cout << endl;
}

set <int> findAllVertices(map <int, set <int> > adjList) {
  set <int> vertices;
  
  for (map <int, set <int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
    vertices.insert((*i).first);
    set <int> neighbours = (*i).second;
    for (set <int>::iterator j = neighbours.begin(); j != neighbours.end(); j++) {
      vertices.insert(*j);
    }
  }

  return vertices;
}

void showVertices(set <int> vertices) {
  printf("\nVertices are:-\n");
  for (set <int>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    printf("%d\t", *i);
  }
  cout << endl;
}

map <int, int> buildInDegreesMap(map <int, set <int> > adjList, set <int> vertices) {
  map <int, int> indegrees;

  // insert all vertices in indegrees map; initialize all to zero
  for (set <int>::iterator i = vertices.begin(); i != vertices.end(); i++) {
    indegrees[*i] = 0;
  }

  // traverse map (all edges) and keep updating in-degrees
  for (map <int, set <int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
    set <int> neighbours = (*i).second;
    for (set <int>::iterator j = neighbours.begin(); j != neighbours.end(); j++) {
      indegrees[*j]++;
    }
  }

  return indegrees;
}

void showInDegrees(map <int, int> inDegrees) {
  printf("\nIn-degrees map is:-\n");
  for (map <int, int>::iterator i = inDegrees.begin(); i != inDegrees.end(); i++) {
    printf("[%d] = %d\n", (*i).first, (*i).second);
  }
}

queue <int> findZeroInDegreeVertices(map <int, int> inDegrees) {
  queue <int> mQue;
  for (map <int, int>::iterator i = inDegrees.begin(); i != inDegrees.end(); i++) {
    if ((*i).second == 0) {
      mQue.push((*i).first);
    }
  }
  return mQue;
}

tuple <list <int>, bool> findTopoSort(map <int, set <int> > adjList, map <int, int> inDegrees, queue <int> mQue) {
  int visitedCount = 0;
  list <int> topoList;

  while (!mQue.empty()) {
    int crrVert = mQue.front();
    mQue.pop();

    visitedCount++;
    topoList.push_back(crrVert);

    if (adjList.find(crrVert) != adjList.end()) {
      set <int> neighbours = adjList[crrVert];
      for (set <int>::iterator i = neighbours.begin(); i != neighbours.end(); i++) {
        int neighbour = *i;

        inDegrees[neighbour]--;
        if (inDegrees[neighbour] == 0) {
          mQue.push(neighbour);
        }
      }
    }
  }

  return make_tuple(topoList, (visitedCount == inDegrees.size()));
}

void showTopoList(list <int> topoList) {
  printf("\nTopo list is:-\n");
  for (list <int>::iterator i = topoList.begin(); i != topoList.end(); i++) {
    printf("%d\t", *i);
  }
  cout << endl;
}
