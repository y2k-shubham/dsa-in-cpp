// LeetCode-743: https://leetcode.com/problems/network-delay-time/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

class Solution {
private:
    bool debug = false;

    void showGraph(vector<list<pair<int, int> > >& adjList) {
        printf("graph is:-\n");
        for (int i = 0; i < adjList.size(); i++) {
            printf("[%d] -> ", i);

            if (!adjList[i].empty()) {
                for (auto it = adjList[i].begin(); it != adjList[i].end(); it++) {
                    printf("%d (%d), ", it->first, it->second);
                }
            }

            cout << endl;
        }
    }

    void showMinTimesVec(vector<int>& minTimes) {
        printf("MinTimes vec is:-\n");

        printf("Ind:\t");
        for (int i = 0; i < minTimes.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < minTimes.size(); i++) {
            if (minTimes[i] == INT_MAX) {
                printf("-\t");
            } else {
                printf("%d\t", minTimes[i]);
            }
        }
        cout << endl;
    }

    void showPQue(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQue) {
        printf("pQue is:-\n");
        while (!pQue.empty()) {
            printf("%d (%d), ", pQue.top().second, pQue.top().first);
            pQue.pop();
        }
        cout << endl;
    }

    vector<list<pair<int, int> > > createGraph(int numVertices, vector<vector<int>>& weights) {
        vector<list<pair<int, int> > > adjList(numVertices);

        for (int i = 0; i < weights.size(); i++) {
            adjList[weights[i][0] - 1].push_back({weights[i][1] - 1, weights[i][2]});
        }

        return adjList;
    }

    vector<int> findMinTimesBFS(vector<list<pair<int, int> > >& adjList, int beginVertex) {
        int numVertices = adjList.size();

        vector<int> minDistances(numVertices, INT_MAX);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQue;
        pQue.push({0, beginVertex});
        while (!pQue.empty()) {
            int vertex = pQue.top().second;
            int distance = pQue.top().first;
            pQue.pop();

            if (distance >= minDistances[vertex]) {
                continue;
            }

            minDistances[vertex] = distance;
            if (adjList[vertex].empty()) {
                continue;
            }

            for (auto it = adjList[vertex].begin(); it != adjList[vertex].end(); it++) {
                if ((distance + it->second) < minDistances[it->first]) {
                    pQue.push({(distance + it->second), it->first});
                }
            }

            if (debug) {
                printf("\n---------\n");

                printf("after processing vertex %d at distance %d\n", vertex, distance);
                cout << endl;

                showMinTimesVec(minDistances);
                cout << endl;

                showPQue(pQue);

                printf("\n---------\n");
            }
        }

        return minDistances;
    }

public:
    // poor performance
    // LC-submission: speed 11 %tile, memory 45 %tile
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<list<pair<int, int> > > adjList = createGraph(n, times);
        if (debug) {
            showGraph(adjList);
        }

        vector<int> minTimes = findMinTimesBFS(adjList, k - 1);

        int maxTime = *max_element(minTimes.begin(), minTimes.end());
        if (maxTime == INT_MAX) {
            return -1;
        } else {
            return maxTime;
        }
    }
};
