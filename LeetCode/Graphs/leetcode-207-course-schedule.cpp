// LeetCode-207: https://leetcode.com/problems/course-schedule/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3729/

/**
 * @file leetcode-207-course-schedule.cpp
 * @author Shubham Gupta (y2k-shubham)
 * @brief Cycle detection in directed graph
 *        YouTube: https://www.youtube.com/watch?v=rKQaZuoUR4M&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j&index=11&t=369s
 *        GeeksForGeeks: (simple DFS) https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * @date 2021-05-10
 */

#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
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

   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (numCourses == 1) {
            return true;
        }

        vector<unordered_set<int>> adjList = createGraph(numCourses, prerequisites);

        return !hasCycle(adjList);
    }
};
