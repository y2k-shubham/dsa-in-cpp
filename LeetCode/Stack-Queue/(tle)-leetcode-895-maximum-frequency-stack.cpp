// LeetCode-895: https://leetcode.com/problems/maximum-frequency-stack/

#include <climits>
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class FreqStack {
   private:
    map<int, unordered_set<int> > freqEleMap;
    unordered_map<int, int> eleFreqMap;
    unordered_map<int, stack<int> > eleOrdMap;
    int ord;
    bool debug;

    void showSet(int maxFreq, unordered_set<int> mSet) {
        printf("\nMax freq = %d, eles set is:-\n", maxFreq);
        for (unordered_set<int>::iterator it = mSet.begin(); it != mSet.end(); it++) {
            printf("%d\t", *it);
        }
        cout << endl;
    }

    void showFreqEleMap() {
        printf("\nfreqEleMap is:-\n");

        for (map<int, unordered_set<int> >::iterator i = freqEleMap.begin(); i != freqEleMap.end(); i++) {
            int freq = (*i).first;
            printf("[%d] -> ", freq);

            unordered_set<int> eles = (*i).second;
            for (unordered_set<int>::iterator j = eles.begin(); j != eles.end(); j++) {
                printf("%d ", *j);
            }
            cout << endl;
        }
        cout << endl;
    }

    void showEleFreqMap() {
        printf("\beleFreqMap is:-\n");

        for (unordered_map<int, int>::iterator it = eleFreqMap.begin(); it != eleFreqMap.end(); it++) {
            printf("%d -> [%d]\n", (*it).first, (*it).second);
        }
    }

    void showEleOrdMap() {
        printf("\neleOrdMap is:-\n");
        for (unordered_map<int, stack<int> >::iterator it = eleOrdMap.begin(); it != eleOrdMap.end(); it++) {
            printf("%d -> [", (*it).first);

            stack<int> ordStk = it->second;
            while (!ordStk.empty()) {
                printf("%d ", ordStk.top());
                ordStk.pop();
            }
            cout << "]" << endl;
        }
    }

   public:
    FreqStack() {
        ord = 0;
        debug = false;
    }

    void push(int ele) {
        if (debug) {
            printf("\n-----push(%d)-begin-----\n", ele);
        }

        int oldFreq = eleFreqMap[ele];
        if (oldFreq != 0) {
            freqEleMap[oldFreq].erase(ele);
            if (freqEleMap[oldFreq].empty()) {
                freqEleMap.erase(oldFreq);
            }
        }

        int newFreq = oldFreq + 1;
        eleFreqMap[ele] = newFreq;
        freqEleMap[newFreq].insert(ele);

        ord++;
        eleOrdMap[ele].push(ord);

        if (debug) {
            showEleFreqMap();
            showFreqEleMap();
            showEleOrdMap();

            printf("\n-----push(%d)-end-----\n", ele);
        }
    }

    int pop() {
        if (debug) {
            printf("\n-----pop-begin-----\n");
        }

        // find eles with max-freq
        map<int, unordered_set<int> >::reverse_iterator it = freqEleMap.rbegin();
        int maxFreq = (*it).first;
        unordered_set<int> maxFreqEles = (*it).second;
        if (debug) {
            showSet(maxFreq, maxFreqEles);
        }

        int victimEle;
        if (maxFreqEles.size() == 1) {
            // if just one such ele, pop it
            victimEle = *(maxFreqEles.begin());
        } else {
            // otherwise among all max-freq elements, find the latest one
            // (the one with max order)
            int maxOrd = INT_MIN;
            for (unordered_set<int>::iterator it = maxFreqEles.begin(); it != maxFreqEles.end(); it++) {
                int ele = *it;
                int ord = eleOrdMap[ele].top();

                if (ord > maxOrd) {
                    maxOrd = ord;
                    victimEle = ele;
                }
            }
        }

        // now we pop the decided victim ele

        // update frequency
        // determine old & new frequencies
        int oldFreq = eleFreqMap[victimEle];
        int newFreq = oldFreq - 1;
        // update element frequency map
        if (newFreq > 0) {
            eleFreqMap[victimEle] = newFreq;
        } else {
            eleFreqMap.erase(victimEle);
        }
        // update frequency element map
        freqEleMap[oldFreq].erase(victimEle);
        if (freqEleMap[oldFreq].empty()) {
            // dont forget this (otherwise reverse-iterator would initialize with empty freq item)
            freqEleMap.erase(oldFreq);
        }
        if (newFreq > 0) {
            freqEleMap[newFreq].insert(victimEle);
        }

        // update order
        eleOrdMap[victimEle].pop();

        if (debug) {
            showEleFreqMap();
            showFreqEleMap();
            showEleOrdMap();

            printf("\n-----pop(%d)-end-----\n", victimEle);
        }

        return victimEle;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
