// https://www.geeksforgeeks.org/topological-sorting/
// https://www.youtube.com/watch?v=Q9PIxaNGnig

/*
acyclic graph
5 2     5 0     4 0     4 1     2 3     3 1     -1 -1

cyclic graph: will give incorrect answer
0 1     0 2     1 3     1 4     2 5     3 0     3 5     4 3     5 4     -1 -1

disconnected graph: will give correct answer
5 2     5 0     4 0     4 1     2 3     3 1     6 7     -1 -1
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <set>

using namespace std;
#define isVisited(visitedSet, crrVert) (visitedSet.find(crrVert) != visitedSet.end())

map <int, list <int> > inputGraph();
void addEdge(map <int, list <int> >&, int, int);
void showGraph(map <int, list <int> >);
stack <int> buildTopoSortStack(map <int, list <int> >);
void performTopoDfs(map <int, list <int> >, int, set <int>&, stack <int>&);
void showTopoSort(stack <int> topoStack);

int main() {
  map <int, list <int> > adjList = inputGraph();
  showGraph(adjList);

  stack <int> topoStack = buildTopoSortStack(adjList);
  showTopoSort(topoStack);

  return 0;
}

map <int, list <int> > inputGraph() {
  map <int, list <int> > adjList;
  int src, dst;

  printf("Enter edges of graph:-\n[Enter (-1, -1) to terminate]\n");
  cin >> src >> dst;
  while (src != -1 && dst != -1) {
    addEdge(adjList, src, dst);
    cin >> src >> dst;
  }

  return adjList;
}

void addEdge(map <int, list <int> >& adjList, int src, int dst) {
  if (adjList.find(src) == adjList.end()) {
    list <int> neighbours;
    adjList[src] = neighbours;
  }
  adjList[src].push_back(dst);
}

void showGraph(map <int, list <int> > adjList) {
  printf("\ngraph is:-\n");

  for (map <int, list <int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
    printf("[%d]\t->\t", (*i).first);
    list <int> neighbours = (*i).second;
    for (list <int>::iterator j = neighbours.begin(); j != neighbours.end(); j++) {
      printf("%d\t", *j);
    }
    cout << endl;
  }
  cout << endl;
}

stack <int> buildTopoSortStack(map <int, list <int> > adjList) {
  stack <int> topoStack;
  set <int> visitedSet;

  // cout << endl;
  for (map <int, list <int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
    int crrVertex = (*i).first;
    if (!isVisited(visitedSet, crrVertex)) {
      // printf("initiating topoDfs for vertex %d\n\n", crrVertex);
      performTopoDfs(adjList, crrVertex, visitedSet, topoStack);
    }
  }

  return topoStack;
}

void performTopoDfs(map <int, list <int> > adjList, int crrVertex, set <int>& visitedSet, stack <int>& topoStack) {
  visitedSet.insert(crrVertex);
  // printf("marked %d as visited\n", crrVertex);
  // this check is needed to handle those vertices that have zero out-degree
  if (adjList.find(crrVertex) != adjList.end()) {
    for (list <int>::iterator i = adjList[crrVertex].begin(); i != adjList[crrVertex].end(); i++) {
      int neighbour = *i;
      if (!isVisited(visitedSet, neighbour)) {
        performTopoDfs(adjList, neighbour, visitedSet, topoStack);
      }
    }
  }
  topoStack.push(crrVertex);
  // printf("pushed %d into topo-stack\n", crrVertex);
}

void showTopoSort(stack <int> topoStack) {
  printf("Topological sort is:-\n");
  while (!topoStack.empty()) {
    printf("%d\t", topoStack.top());
    topoStack.pop();
  }
  cout << endl;
}
