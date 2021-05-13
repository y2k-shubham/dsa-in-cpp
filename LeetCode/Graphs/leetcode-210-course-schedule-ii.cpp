// LeetCode-210: https://leetcode.com/problems/course-schedule-ii/

#include <cstdio>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug;

    void showStack(stack<int> stk) {
        printf("\nStack is:-\n");
        while (!stk.empty()) {
            printf("%d\t", stk.top());
            stk.pop();
        }
        cout << endl;
    }

    void showGraph(vector<unordered_set<int>>& graph) {
        printf("\nGraph is:-\n");

        for (int i = 0; i < graph.size(); i++) {
            printf("[%d] -> ", i);

            unordered_set<int> children = graph[i];
            for (unordered_set<int>::iterator it = children.begin(); it != children.end(); it++) {
                printf("%d ", *it);
            }
            cout << endl;
        }
    }

    vector<unordered_set<int>> createGraph(int numCourses, vector<vector<int>>& prerequisites) {
        vector<unordered_set<int>> adjList(numCourses);

        for (int i = 0; i < prerequisites.size(); i++) {
            int childCourse = prerequisites[i][0];
            int parentCourse = prerequisites[i][1];

            adjList[parentCourse].insert(childCourse);
        }

        return adjList;
    }

    bool hasCycleRec(vector<unordered_set<int>>& adjList, vector<int>& status, int crrVert) {
        status[crrVert] = 1;  // currently being explored

        unordered_set<int> children = adjList[crrVert];
        for (unordered_set<int>::iterator it = children.begin(); it != children.end(); it++) {
            int childVert = *it;

            switch (status[childVert]) {
                case 0:
                    if (hasCycleRec(adjList, status, childVert)) {
                        return true;
                    }
                    break;

                case 1:
                    return true;
                    break;

                case 2:
                    continue;
                    break;

                default:
                    return true;
                    break;
            }
        }

        status[crrVert] = 2;

        return false;
    }

    bool hasCycle(vector<unordered_set<int>>& adjList) {
        int numVerts = adjList.size();

        vector<int> status(numVerts, 0);
        for (int i = 0; i < numVerts; i++) {
            if (status[i] == 0) {
                if (hasCycleRec(adjList, status, i)) {
                    return true;
                }
            }
        }

        return false;
    }

    void buildTopoSortStackRec(
        vector<unordered_set<int>>& graph,
        unordered_set<int>& visitedSet,
        stack<int>& orderStack,
        int crrVert) {
        if (visitedSet.find(crrVert) != visitedSet.end()) {
            return;
        }
        visitedSet.insert(crrVert);

        unordered_set<int> children = graph[crrVert];
        if (!children.empty()) {
            for (unordered_set<int>::iterator it = children.begin(); it != children.end(); it++) {
                if (visitedSet.find(*it) == visitedSet.end()) {
                    buildTopoSortStackRec(graph, visitedSet, orderStack, *it);
                }
            }
        }

        orderStack.push(crrVert);
    }

    // LC submission: speed 11 %tile, memory 5 %tile
    stack<int> buildTopoSortStack(
        int numCourses,
        vector<unordered_set<int>>& graph) {
        stack<int> orderStack;
        unordered_set<int> visitedSet;

        for (int i = 0; i < numCourses; i++) {
            if (visitedSet.find(i) == visitedSet.end()) {
                buildTopoSortStackRec(graph, visitedSet, orderStack, i);
            }
        }

        return orderStack;
    }

    vector<int> convertToVec(stack<int>& stk) {
        vector<int> vec(stk.size());

        int i = 0;
        while (!stk.empty()) {
            vec[i] = stk.top();
            stk.pop();
            i++;
        }

        return vec;
    }

   public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        this->debug = false;

        vector<unordered_set<int>> graph = createGraph(numCourses, prerequisites);
        if (this->debug) {
            showGraph(graph);
        }

        if (hasCycle(graph)) {
            return {};
        }

        stack<int> topoSortStack = buildTopoSortStack(numCourses, graph);
        if (this->debug) {
            showStack(topoSortStack);
        }

        return convertToVec(topoSortStack);
    }
};