// LeetCode-1353: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
// Barely accepted; speed 5 %tile, memory  5 %tile

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    pair <unordered_map<int, list < pair < int, int>> >, unordered_map<int, list<pair < int, int> > > >
    buildEventsMap(vector<vector < int>>
    &events) {
        unordered_map < int, list < pair < int, int > > > startMap;
        unordered_map < int, list < pair < int, int > > > endMap;

        for (int i = 0; i < events.size(); i++) {
            pair<int, int> event = make_pair(events[i][0], events[i][1]);
            startMap[event.first].push_back(event);
            endMap[event.second].push_back(event);
        }

        return make_pair(startMap, endMap);
    }

    pair<int, int> findMinMax(vector <vector<int>>& events) {
        int minVal = INT_MAX;
        int maxVal = INT_MIN;

        for (int i = 0; i < events.size(); i++) {
            minVal = min(minVal, events[i][0]);
            maxVal = max(maxVal, events[i][1]);
        }

        return make_pair(minVal, maxVal);
    }

    void showActiveEvents(map<pair<int, int>, int>& activeEvents) {
        cout << "Active Events:-\n";
        for (auto it = activeEvents.begin(); it != activeEvents.end(); it++) {
            printf("(%d, %d) -> %d\n", it->first.second, it->first.first, it->second);
        }
        cout << endl;
    }

    int calcMaxEvents(
            unordered_map<int, list<pair < int, int> >

    > &startMap,
    unordered_map<int, list<pair < int, int> > > &endMap,
    pair<int, int> minMax
    ) {
        int numEvents = 0;

        map<pair<int, int>, int> activeEvents;
        for (int i = minMax.first; i <= minMax.second; i++) {
            if (debug) {
                printf("-----i=%d-----\n", i);
            }

            // add all events starting on day i
            if (startMap.find(i) != startMap.end()) {
                for (auto event: startMap[i]) {
                    activeEvents[{event.second, event.first}]++;
                }
            }

            if (debug) {
                printf("after adding events starting on day: i=%d\n", i);
                showActiveEvents(activeEvents);
            }

            // remove all events ending on day i-1
            if ((i >= 1) && (endMap.find(i - 1) != endMap.end())) {
                for (auto event: endMap[i - 1]) {
                    int freq = activeEvents[{event.second, event.first}];
                    if (freq <= 1) {
                        activeEvents.erase({event.second, event.first});
                    } else {
                        activeEvents[{event.second, event.first}]--;
                    }
                }
            }

            if (debug) {
                printf("after removing events ended on day: i-1=%d\n", (i - 1));
                showActiveEvents(activeEvents);
            }

            // if there are active events, pick the one with earliest end date
            if (activeEvents.size() > 0) {
                auto event = activeEvents.begin()->first;
                activeEvents[event]--;
                if (activeEvents[event] == 0) {
                    activeEvents.erase(event);
                }

                numEvents++;
                if (debug) {
                    printf("took event (%d, %d) from active events\n", event.second, event.first);
                    showActiveEvents(activeEvents);
                    printf("numEvents = %d\n", numEvents);
                }
            }

            if (debug) {
                printf("----------\n\n");
            }
        }

        return numEvents;
    }

public:
    friend class SolutionTest;

    int maxEvents(vector <vector<int>>& events) {
        pair < unordered_map < int, list < pair < int, int > > >, unordered_map < int, list < pair < int,
                int > > > > eventsMap = buildEventsMap(events);
        pair<int, int> minMax = findMinMax(events);
        return calcMaxEvents(eventsMap.first, eventsMap.second, minMax);
    }
};

class SolutionTest {
public:
    void testMaxEvents() {
        Solution soln = Solution();
        vector <vector<int>> events;
        int maxEventsOutExpected;
        int maxEventsOutComputed;

//        soln.debug = true;
        events = {{1, 2},
                  {2, 3},
                  {3, 4}};
        maxEventsOutExpected = 3;
        maxEventsOutComputed = soln.maxEvents(events);
        assert(maxEventsOutComputed == maxEventsOutExpected);

        events = {{1, 2},
                  {2, 3},
                  {3, 4},
                  {1, 2}};
        maxEventsOutExpected = 4;
        maxEventsOutComputed = soln.maxEvents(events);
//        cout << "maxEventsOutComputed = " << maxEventsOutComputed << endl;
        assert(maxEventsOutComputed == maxEventsOutExpected);
//        soln.debug = false;

//        soln.debug = true;
        events = {{25, 26},
                  {19, 19},
                  {9,  13},
                  {16, 17},
                  {17, 18},
                  {20, 21},
                  {22, 25},
                  {11, 12},
                  {19, 23},
                  {7,  9},
                  {1,  1},
                  {21, 23},
                  {14, 14},
                  {4,  7},
                  {16, 16},
                  {24, 28},
                  {16, 18},
                  {4,  5},
                  {18, 20},
                  {16, 16},
                  {25, 26}};
        maxEventsOutExpected = 19;
        maxEventsOutComputed = soln.maxEvents(events);
        assert(maxEventsOutComputed == maxEventsOutExpected);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testMaxEvents();
    return 0;
}
