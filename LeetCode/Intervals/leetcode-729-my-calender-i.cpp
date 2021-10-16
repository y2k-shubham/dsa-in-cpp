// LeetCode-729: https://leetcode.com/problems/my-calendar-i/
// CodeWithSunny: https://www.youtube.com/watch?v=gMnCGS7230U

#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

class MyCalendar {
   private:
    // {time, 1|-1}; 1=event-start, -1=event-end
    set<pair<int, int> > eventSet;

   public:
    MyCalendar() {
    }

    bool book(int start, int end) {
        pair<int, int> startEvent = {start, 1};
        // check for conflicts in start time
        if (this->eventSet.find(startEvent) != eventSet.end()) {
            return false;
        }

        // insert event in set
        this->eventSet.insert(startEvent);
        // check for overlapping start times
        set<pair<int, int> >::iterator it1 = this->eventSet.find(startEvent);
        set<pair<int, int> >::iterator it1Copy = it1;
        if (it1Copy != eventSet.begin()) {
            it1Copy--;

            if (it1Copy->second == 1) {
                // found two events starting but not ending -> overlap
                this->eventSet.erase(startEvent);
                return false;
            }
        }

        pair<int, int> endEvent = {end, -1};
        // check for conflicts in start time
        if (this->eventSet.find(endEvent) != eventSet.end()) {
            this->eventSet.erase(startEvent);
            return false;
        }

        // insert event in set
        this->eventSet.insert(endEvent);
        // check for overlapping end times
        set<pair<int, int> >::iterator it2 = this->eventSet.find(endEvent);
        set<pair<int, int> >::iterator it2Copy = it2;
        if (it2Copy != eventSet.end()) {
            it2Copy++;

            if (it2Copy->second == -1) {
                // found two events ending but not starting -> overlap
                this->eventSet.erase(startEvent);
                this->eventSet.erase(endEvent);
                return false;
            }
        }

        // check if inserted events (start, end) are adjacent in set or not
        it1++;
        if (it1 != it2) {
            this->eventSet.erase(startEvent);
            this->eventSet.erase(endEvent);
            return false;
        }

        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
