// LeetCode-860: https://leetcode.com/problems/lemonade-change

#include <vector>

using namespace std;

#define PRICE 5
#define DEN_5 5
#define DEN_10 10
#define DEN_20 20

class Solution {
private:
    vector<int> denFreqs;

    void initDenFreqs() {
        denFreqs.clear();
        denFreqs.resize(3, 0);
    }

    inline bool canReturn(int amount) {
        if (amount == PRICE) {
            denFreqs[0]++;
            return true;
        }

        if (denFreqs[0] == 0) {
            return false;
        }

        if (amount == DEN_10) {
            denFreqs[1]++;
            denFreqs[0]--;
            return true;
        }

        if (amount == DEN_20) {
            if ((denFreqs[1] == 0) && (denFreqs[0] < 3)) {
                return false;
            }

            denFreqs[2]++;
            if (denFreqs[1] == 0) {
                denFreqs[0] -= 3;
            } else {
                denFreqs[0]--;
                denFreqs[1]--;
            }

            return true;
        }

        return false;
    }

public:
    bool lemonadeChange(vector<int>& bills) {
        initDenFreqs();

        for (int bill: bills) {
            if (!canReturn(bill)) {
                return false;
            }
        }

        return true;
    }
};
