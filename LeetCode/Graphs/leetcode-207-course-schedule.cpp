// LeetCode-207: https://leetcode.com/problems/course-schedule/
// Cycle detection in directed graph: https://www.youtube.com/watch?v=rKQaZuoUR4M&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j&index=11&t=369s

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>
#include <cassert>

using namespace std;

void testBuildGraph();
vector <list <int> > buildGraph(int V, vector <vector <int> >& preReqs);

int main() {
  testBuildGraph();

  return 0;
}

void testBuildGraph() {
  int VIn;
  vector <vector <int> > preReqsIn;
  vector <list <int> > adjListOutExpected;
  vector <list <int> > adjListOutComputed;

  VIn = 0;
  preReqsIn = {};
  adjListOutExpected = {};
  adjListOutComputed = buildGraph(VIn, preReqsIn);
  assert(adjListOutExpected == adjListOutComputed);

  VIn = 2;
  preReqsIn = {{1}};
  adjListOutExpected = {{}, {0}};
  adjListOutComputed = buildGraph(VIn, preReqsIn);
  assert(adjListOutExpected == adjListOutComputed);

  VIn = 0;
  preReqsIn = {{1, 2}, {}, {1}};
  adjListOutExpected = {{}, {0, 2}, {0}};
  adjListOutComputed = buildGraph(VIn, preReqsIn);
  assert(adjListOutExpected == adjListOutComputed);

  VIn = 0;
  preReqsIn = {};
  adjListOutExpected = {};
  adjListOutComputed = buildGraph(VIn, preReqsIn);
  assert(adjListOutExpected == adjListOutComputed);

  VIn = 0;
  preReqsIn = {};
  adjListOutExpected = {};
  adjListOutComputed = buildGraph(VIn, preReqsIn);
  assert(adjListOutExpected == adjListOutComputed);

  VIn = 0;
  preReqsIn = {};
  adjListOutExpected = {};
  adjListOutComputed = buildGraph(VIn, preReqsIn);
  assert(adjListOutExpected == adjListOutComputed);
}

vector <list <int> > buildGraph(int V, vector <vector <int> >& preReqs) {
   vector <list <int> > adjList(V);

   for (int i = 0; i < preReqs.size(); i++) {
     vector <int> parents = preReqs[i];
     for (int j = 0; j < parents.size(); j++) {
       adjList[parents[j]].push_back(i);
     }
   }

   return adjList;
}

