// LeetCode-716: https://leetcode.com/problems/max-stack/
// Premium
// Companies: [LinkedIn][Walmart Labs][Amazon][Lyft][Google][Meta][TikTok][Woven by Toyota][Nutanix]

// not really a Hard problem

// barely passes; LC runtime 419ms, 5 %tile

/**
 * Works on following input also:
 * ["MaxStack","push","peekMax","push","peekMax","push","pop","pop","push","peekMax","push","popMax","top","push","push","peekMax","popMax","popMax"]
 * [[],[92],[],[54],[],[22],[],[],[-57],[],[-24],[],[],[26],[-71],[],[],[]]
 *
 * Expected:
 * [null,null,92,null,92,null,22,54,null,92,null,92,-24,null,null,26,26,-24]
 */

#include <unordered_map>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <stack>

using namespace std;

class MaxStack {
private:
    map <int, int> freqMap;

    // comparator struct geneated by MetaAI
    struct CompareByPosDesc {
        bool operator()(const std::pair<int,int>& a,
                        const std::pair<int,int>& b) const {
            return a.second > b.second;
        }
    };
    set <pair <int, int>, CompareByPosDesc> elePosnSet; // recall that our positions will be unique

    int crrPosn;
    unordered_map<int, stack<int>> elePosnsMap;

    pair <int, int> topElePosn() {
        return *elePosnSet.begin();
    }

    void removeEle(int ele, int posn) {
        freqMap[ele]--;

        elePosnSet.erase({ele, posn});
        elePosnsMap[ele].pop();

        cleanupEleEntriesIfRequired(ele);
    }

    void cleanupEleEntriesIfRequired(int ele) {
        if (freqMap[ele] <= 0) {
            freqMap.erase(ele);
            elePosnsMap.erase(ele);
        }
    }

public:
    MaxStack() {
        freqMap.clear();
        elePosnSet.clear();
        crrPosn = 0;
        elePosnsMap.clear();
    }

    void push(int x) {
        freqMap[x]++;

        elePosnSet.insert({x, crrPosn});
        elePosnsMap[x].push(crrPosn);

        crrPosn++;
    }

    int pop() {
        pair <int, int> elePosn = topElePosn();
        int ele = elePosn.first;
        int posn = elePosn.second;

        removeEle(ele, posn);

        return ele;
    }

    int top() {
        return topElePosn().first;
    }

    int peekMax() {
        return freqMap.rbegin()->first;
    }

    int popMax() {
        int ele = peekMax();
        int eleLatestPosn = elePosnsMap[ele].top();

        removeEle(ele, eleLatestPosn);

        return ele;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
