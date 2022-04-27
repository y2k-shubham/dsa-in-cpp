// LeetCode-933: https://leetcode.com/problems/number-of-recent-calls/
// pretty easy problem
// this is an application of linked list (not directly linked list problem)

#include <list>

using namespace std;

#define MAX_INTERVAL 3000

class RecentCounter {
private:
    list<int> mList;

    void popUntilPruned() {
        int endTime = mList.back();
        int minBeginTime = endTime - MAX_INTERVAL;

        while (mList.front() < minBeginTime) {
            mList.pop_front();
        }
    }

public:
    RecentCounter() {

    }

    int ping(int t) {
        mList.push_back(t);
        popUntilPruned();
        return mList.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
