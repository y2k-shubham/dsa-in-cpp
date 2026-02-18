// LeetCode-2526: https://leetcode.com/problems/find-consecutive-integers-from-a-data-stream/

#include <algorithm>

using namespace std;

class DataStream {
private:
    int value;
    int k;
    int crrNumConsecVals;

public:
    DataStream(int value, int k) {
        this->value = value;
        this->k = k;
        this->crrNumConsecVals = 0;
    }

    bool consec(int num) {
        if (num == value) {
            crrNumConsecVals = min(k, (crrNumConsecVals + 1));
        } else {
            crrNumConsecVals = 0;
        }

        return (crrNumConsecVals == k);
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */
