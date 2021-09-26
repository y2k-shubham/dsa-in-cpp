// LeetCode-621: https://leetcode.com/problems/task-scheduler/
// 1st soln (super-optimal) breaks in following test-case
// ["G","C","A","H","A","G","G","F","G","J","H","C","A","G","E","A","H","E","F","D","B","D","H","H","E","G","F","B","C","G","F","H","J","F","A","C","G","D","I","J","A","G","D","F","B","F","H","I","G","J","G","H","F","E","H","J","C","E","H","F","C","E","F","H","H","I","G","A","G","D","C","B","I","D","B","C","J","I","B","G","C","H","D","I","A","B","A","J","C","E","B","F","B","J","J","D","D","H","I","I","B","A","E","H","J","J","A","J","E","H","G","B","F","C","H","C","B","J","B","A","H","B","D","I","F","A","E","J","H","C","E","G","F","G","B","G","C","G","A","H","E","F","H","F","C","G","B","I","E","B","J","D","B","B","G","C","A","J","B","J","J","F","J","C","A","G","J","E","G","J","C","D","D","A","I","A","J","F","H","J","D","D","D","C","E","D","D","F","B","A","J","D","I","H","B","A","F","E","B","J","A","H","D","E","I","B","H","C","C","C","G","C","B","E","A","G","H","H","A","I","A","B","A","D","A","I","E","C","C","D","A","B","H","D","E","C","A","H","B","I","A","B","E","H","C","B","A","D","H","E","J","B","J","A","B","G","J","J","F","F","H","I","A","H","F","C","H","D","H","C","C","E","I","G","J","H","D","E","I","J","C","C","H","J","C","G","I","E","D","E","H","J","A","H","D","A","B","F","I","F","J","J","H","D","I","C","G","J","C","C","D","B","E","B","E","B","G","B","A","C","F","E","H","B","D","C","H","F","A","I","A","E","J","F","A","E","B","I","G","H","D","B","F","D","B","I","B","E","D","I","D","F","A","E","H","B","I","G","F","D","E","B","E","C","C","C","J","J","C","H","I","B","H","F","H","F","D","J","D","D","H","H","C","D","A","J","D","F","D","G","B","I","F","J","J","C","C","I","F","G","F","C","E","G","E","F","D","A","I","I","H","G","H","H","A","J","D","J","G","F","G","E","E","A","H","B","G","A","J","J","E","I","H","A","G","E","C","D","I","B","E","A","G","A","C","E","B","J","C","B","A","D","J","E","J","I","F","F","C","B","I","H","C","F","B","C","G","D","A","A","B","F","C","D","B","I","I","H","H","J","A","F","J","F","J","F","H","G","F","D","J","G","I","E","B","C","G","I","F","F","J","H","H","G","A","A","J","C","G","F","B","A","A","E","E","A","E","I","G","F","D","B","I","F","A","B","J","F","F","J","B","F","J","F","J","F","I","E","J","H","D","G","G","D","F","G","B","J","F","J","A","J","E","G","H","I","E","G","D","I","B","D","J","A","A","G","A","I","I","A","A","I","I","H","E","C","A","G","I","F","F","C","D","J","J","I","A","A","F","C","J","G","C","C","H","E","A","H","F","B","J","G","I","A","A","H","G","B","E","G","D","I","C","G","J","C","C","I","H","B","D","J","H","B","J","H","B","F","J","E","J","A","G","H","B","E","H","B","F","F","H","E","B","E","G","H","J","G","J","B","H","C","H","A","A","B","E","I","H","B","I","D","J","J","C","D","G","I","J","G","J","D","F","J","E","F","D","E","B","D","B","C","B","B","C","C","I","F","D","E","I","G","G","I","B","H","G","J","A","A","H","I","I","H","A","I","F","C","D","A","C","G","E","G","E","E","H","D","C","G","D","I","A","G","G","D","A","H","H","I","F","E","I","A","D","H","B","B","G","I","C","G","B","I","I","D","F","F","C","C","A","I","E","A","E","J","A","H","C","D","A","C","B","G","H","G","J","G","I","H","B","A","C","H","I","D","D","C","F","G","B","H","E","B","B","H","C","B","G","G","C","F","B","E","J","B","B","I","D","H","D","I","I","A","A","H","G","F","B","J","F","D","E","G","F","A","G","G","D","A","B","B","B","J","A","F","H","H","D","C","J","I","A","H","G","C","J","I","F","J","C","A","E","C","H","J","H","H","F","G","E","A","C","F","J","H","D","G","G","D","D","C","B","H","B","C","E","F","B","D","J","H","J","J","J","A","F","F","D","E","F","C","I","B","H","H","D","E","A","I","A","B","F","G","F","F","I","E","E","G","A","I","D","F","C","H","E","C","G","H","F","F","H","J","H","G","A","E","H","B","G","G","D","D","D","F","I","A","F","F","D","E","H","J","E","D","D","A","J","F","E","E","E","F","I","D","A","F","F","J","E","I","J","D","D","G","A","C","G","G","I","E","G","E","H","E","D","E","J","B","G","I","J","C","H","C","C","A","A","B","C","G","B","D","I","D","E","H","J","J","B","F","E","J","H","H","I","G","B","D"] 1

#include <cassert>
#include <climits>
#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <set>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showVec(vector<char>& vec, string name) {
        printf("\n%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%c\t", vec[i]);
        }
        cout << endl;
    }

    unordered_map<char, int> buildFreqMap(vector<char>& vec) {
        unordered_map<char, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    priority_queue<pair<int, char> > convertMapToHeap(unordered_map<char, int>& mMap) {
        int len = mMap.size();

        vector<pair<int, char> > mVec(len);
        int i = 0;
        for (unordered_map<char, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            mVec[i++] = {it->second, it->first};
        }

        priority_queue<pair<int, char> > mHeap(mVec.begin(), mVec.end());
        return mHeap;
    }

    void updateFreqAndPushToWaitQue(int time, char task, int& freq, int cooldownPeriod, queue<tuple<char, int, int> >& waitQue) {
        freq--;
        if (freq > 0) {
            int waitUntil = (cooldownPeriod == 0) ? 0 : (time + cooldownPeriod + 1);
            waitQue.push({task, freq, waitUntil});
        }
    }

    // super-optimal + (super tricky) but WRONG
    vector<char> findOptimalSchedule1(vector<char>& tasks, int cooldownPeriod) {
        int len = tasks.size();
        if (len == 0) {
            if (debug) {
                printf("returning 0\n");
            }
            return {};
        }
        if (len == 1) {
            if (debug) {
                printf("returning 1\n");
            }
            return tasks;
        }
        if (cooldownPeriod == 0) {
            if (debug) {
                printf("returning 2\n");
            }
            return tasks;
        }

        unordered_map<char, int> freqMap = buildFreqMap(tasks);
        priority_queue<pair<int, char> > freqHeap = convertMapToHeap(freqMap);
        queue<tuple<char, int, int> > waitQue;

        vector<char> schedule;
        int time = 0;
        while (!freqHeap.empty() || !waitQue.empty()) {
            if (debug) {
                printf("\n----\n");
            }
            bool hEmpty, qEmpty;
            char hTask, qTask;
            int hFreq, qFreq;
            int hWaitUntil, qWaitUntil;

            // topmost heap task
            hEmpty = freqHeap.empty();
            if (!hEmpty) {
                hTask = freqHeap.top().second;
                hFreq = freqHeap.top().first;
                hWaitUntil = 0;
            }
            // front-most que task
            qEmpty = waitQue.empty();
            if (!qEmpty) {
                tie(qTask, qFreq, qWaitUntil) = waitQue.front();
            }

            // determine if heap's top task should be prioritized above que's front task
            bool heapHasHigherFreqTask = false;
            if (!hEmpty) {
                if (qEmpty) {
                    heapHasHigherFreqTask = true;
                } else if (!hEmpty && !qEmpty) {
                    heapHasHigherFreqTask = hFreq > qFreq;
                }
            }

            if (!hEmpty && heapHasHigherFreqTask) {
                // heap has higher freq task (than que), so schedule that first
                freqHeap.pop();
                schedule.push_back(hTask);

                if (debug) {
                    printf("block1 adding %c in schedule\n", hTask);
                    showVec(schedule, "schedule");
                }

                updateFreqAndPushToWaitQue(time, hTask, hFreq, cooldownPeriod, waitQue);

                time++;
            } else if (!qEmpty && (get<2>(waitQue.front()) <= time)) {
                if (debug) {
                    printf("block2\n");
                }
                // either heap is empty or (que has higher freq-task + it's cooldown period has surpassed)
                waitQue.pop();
                schedule.push_back(qTask);

                updateFreqAndPushToWaitQue(time, qTask, qFreq, cooldownPeriod, waitQue);

                time++;
            } else if (!hEmpty && !heapHasHigherFreqTask) {
                if (debug) {
                    printf("block3\n");
                }
                // either que is empty or it's front task's cooldown period not surpassed yet
                freqHeap.pop();
                schedule.push_back(hTask);

                updateFreqAndPushToWaitQue(time, hTask, hFreq, cooldownPeriod, waitQue);

                time++;
            } else {
                if (debug) {
                    if (debug) {
                        printf("block4\n");
                    }
                    printf(
                        "\ngoing to insert delays hEmpty=%s, qEmpty=%s, hHigherFreq=%s, qWaitUntil=%d, time=%d\n",
                        (hEmpty ? "true" : "false"),
                        (qEmpty ? "true" : "false"),
                        (heapHasHigherFreqTask ? "true" : "false"),
                        qWaitUntil,
                        time);
                }
                // heap is empty and que's front task's cooldown period not surpassed yet (will have to add a wait)
                while (time < qWaitUntil) {
                    schedule.push_back('\0');
                    time++;
                }
                if (debug) {
                    showVec(schedule, "schedule");
                }
            }
        }

        return schedule;
    }

    priority_queue<tuple<int, int, char> > buildFreqHeap(unordered_map<char, int>& mMap) {
        int len = mMap.size();

        vector<tuple<int, int, char> > mVec(len);
        int i = 0;
        for (unordered_map<char, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            mVec[i++] = {it->second, 0, it->first};
        }

        priority_queue<tuple<int, int, char> > mHeap(mVec.begin(), mVec.end());
        return mHeap;
    }

    set <pair <int, char> > buildDelaySet(unordered_map<char, int>& mMap) {
        int len = mMap.size();

        vector<pair<int, char> > mVec(len);
        int i = 0;
        for (unordered_map<char, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            mVec[i++] = {0, it->first};
        }

        set <pair <int, char> > delaySet(mVec.begin(), mVec.end());

        return delaySet;
    }

    void showHeap(priority_queue<tuple<int, int, char> > mHeap) {
        printf("mHeap is:-\n");
        while (!mHeap.empty()) {
            char task;
            int freq;
            int delayUntil;
            tie(freq, delayUntil, task) = mHeap.top();
            printf("[%c] = %d, %d\n", task, freq, delayUntil);

            mHeap.pop();
        }
    }

    // barely accepted, speed 5 %tile, memory 5 %tile
    vector<char> findOptimalSchedule2(vector<char>& tasks, int cooldownPeriod) {
        int len = tasks.size();
        if (len == 0) {
            if (debug) {
                printf("returning 0\n");
            }
            return {};
        }
        if (len == 1) {
            if (debug) {
                printf("returning 1\n");
            }
            return tasks;
        }
        if (cooldownPeriod == 0) {
            if (debug) {
                printf("returning 2\n");
            }
            return tasks;
        }

        unordered_map<char, int> freqMap = buildFreqMap(tasks);
        priority_queue<tuple<int, int, char> > mHeap = buildFreqHeap(freqMap);
        set <pair <int, char> > delaySet = buildDelaySet(freqMap);
        stack<tuple<int, int, char> > mStack;

        vector<char> schedule;
        int time = 0;

        if (debug) {
            printf("before commencing iterations\n\n");
            showHeap(mHeap);
            showVec(schedule, "schedule");
        }

        while (!mHeap.empty()) {
            int minDelay = delaySet.begin()->first;

            if (debug) {
                printf("\n--------\ntime=%d, minDelay=%d\n\n", time, minDelay);
            }

            // check if delay needed
            if ((minDelay != 0) && (time < minDelay)) {
                // add delay
                while (time < minDelay) {
                    schedule.push_back('\0');
                    time++;
                }

                if (debug) {
                    printf("added delay until time=%d\n", time);
                    showHeap(mHeap);
                    showVec(schedule, "schedule");
                }

                continue;
            }

            // pop out items from heap till admissible item found
            while (time < get<1>(mHeap.top())) {
                mStack.push(mHeap.top());
                mHeap.pop();
            }

            char task;
            int freq;
            int delayUntil;
            tie(freq, delayUntil, task) = mHeap.top();
            mHeap.pop();

            schedule.push_back(task);

            delaySet.erase({delayUntil, task});
            freq--;
            if (freq > 0) {
                delayUntil = time + cooldownPeriod + 1;
                delaySet.insert({delayUntil, task});

                if (debug) {
                    printf("pushing into heap at 1, delayUntil = (time=%d + coolP=%d + 1) = %d\n", time, cooldownPeriod, delayUntil);
                }
                mHeap.push({freq, delayUntil, task});
            }

            // push back stack items to heap
            while (!mStack.empty()) {
                if (debug) {
                    printf("pushing into heap at 2\n");
                }
                mHeap.push(mStack.top());
                mStack.pop();
            }

            if (debug) {
                printf("after time=%d iteration\n\n", time);
                showHeap(mHeap);
                showVec(schedule, "schedule");
            }

            time++;
        }

        return schedule;
    }

   public:
    friend class SolutionTest;

    int leastInterval(vector<char>& tasks, int n) {
        vector<char> schedule = findOptimalSchedule2(tasks, n);
        return schedule.size();
    }
};

class SolutionTest {
   public:
    void testFindOptimalSchedule1() {
        Solution soln = Solution();
        vector<char> tasks;
        int coolDownPeriod;
        vector<char> scheduleOutExpected;
        vector<char> scheduleOutComputed;

        tasks = {};
        coolDownPeriod = 5;
        scheduleOutExpected = {};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);

        // soln.debug = true;
        tasks = {'a'};
        coolDownPeriod = 5;
        scheduleOutExpected = {'a'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);
        // soln.debug = false;

        tasks = {'a', 'a'};
        coolDownPeriod = 0;
        scheduleOutExpected = {'a', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);

        // soln.debug = true;
        tasks = {'a', 'a'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'a', '\0', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);
        // soln.debug = false;

        tasks = {'a', 'a'};
        coolDownPeriod = 5;
        scheduleOutExpected = {'a', '\0', '\0', '\0', '\0', '\0', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'a', 'a', 'b'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'a', 'b', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'b', 'a', 'a', 'b'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'b', 'a', 'b', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'b', 'c', 'c', 'a', 'a', 'c', 'b', 'c'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'c', 'b', 'c', 'a', 'b', 'c', 'a', 'c'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'b', 'c', 'c', 'a', 'a', 'c', 'b', 'c'};
        coolDownPeriod = 2;
        scheduleOutExpected = {'c', 'b', 'a', 'c', 'b', 'a', 'c', '\0', '\0', 'c'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        coolDownPeriod = 2;
        scheduleOutExpected = {'A', 'G', 'F', 'A', 'E', 'D', 'A', 'C', 'B', 'A', '\0', '\0', 'A', '\0', '\0', 'A'};
        scheduleOutComputed = soln.findOptimalSchedule1(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);
    }

    void testFindOptimalSchedule2() {
        Solution soln = Solution();
        vector<char> tasks;
        int coolDownPeriod;
        vector<char> scheduleOutExpected;
        vector<char> scheduleOutComputed;

        tasks = {};
        coolDownPeriod = 5;
        scheduleOutExpected = {};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);
        // printf("done\n");

        // soln.debug = true;
        tasks = {'a'};
        coolDownPeriod = 5;
        scheduleOutExpected = {'a'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);
        // soln.debug = false;
        // printf("done\n");

        tasks = {'a', 'a'};
        coolDownPeriod = 0;
        scheduleOutExpected = {'a', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);
        // printf("done\n");

        // soln.debug = true;
        tasks = {'a', 'a'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'a', '\0', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);
        // soln.debug = false;
        // printf("done\n");

        tasks = {'a', 'a'};
        coolDownPeriod = 5;
        scheduleOutExpected = {'a', '\0', '\0', '\0', '\0', '\0', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        assert(scheduleOutExpected == scheduleOutComputed);
        // printf("done\n");

        tasks = {'a', 'a', 'b'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'a', 'b', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'b', 'a', 'a', 'b'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'b', 'a', 'b', 'a'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'b', 'c', 'c', 'a', 'a', 'c', 'b', 'c'};
        coolDownPeriod = 1;
        scheduleOutExpected = {'c', 'b', 'c', 'a', 'c', 'a', 'c', 'b'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'b', 'c', 'c', 'a', 'a', 'c', 'b', 'c'};
        coolDownPeriod = 2;
        scheduleOutExpected = {'c', 'b', 'a', 'c', 'b', 'a', 'c', '\0', '\0', 'c'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);

        tasks = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        coolDownPeriod = 2;
        scheduleOutExpected = {'A', 'G', 'F', 'A', 'E', 'D', 'A', 'C', 'B', 'A', '\0', '\0', 'A', '\0', '\0', 'A'};
        scheduleOutComputed = soln.findOptimalSchedule2(tasks, coolDownPeriod);
        // soln.showVec(scheduleOutExpected, "expected");
        // soln.showVec(scheduleOutComputed, "computed");
        assert(scheduleOutExpected == scheduleOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindOptimalSchedule1();
    solnTest.testFindOptimalSchedule2();

    return 0;
}
