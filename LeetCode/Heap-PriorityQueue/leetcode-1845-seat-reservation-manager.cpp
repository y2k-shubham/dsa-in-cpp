// LeetCode-1845: https://leetcode.com/problems/seat-reservation-manager/

#include <cstdio>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// LC-submission speed 73 %tile, memory 30 %tile
class SeatManager {
   private:
    priority_queue<int, vector<int>, greater<int> > pQue;

    void initSeatsPQue(int n) {
        vector<int> vec(n);
        iota(vec.rbegin(), vec.rend(), 1);

        // initializing pQue with simple for-loop gives TLE
        priority_queue<int, vector<int>, greater<int> > pQue(vec.begin(), vec.end());
        this->pQue = pQue;
    }

   public:
    SeatManager(int n) {
        this->initSeatsPQue(n);
    }

    int reserve() {
        int seatNo = this->pQue.top();
        this->pQue.pop();

        return seatNo;
    }

    void unreserve(int seatNumber) {
        this->pQue.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
