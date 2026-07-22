// LeetCode-281: https://leetcode.com/problems/zigzag-iterator/

// Premium
// Companies: [Coinbase][C3.ai][Amazon][Google]

#include <vector>
#include <climits>

using namespace std;

class ZigzagIterator {
private:
    int i1, i2;
    int len1, len2;
    int turn;
    vector <int> v1, v2;

public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        len1 = v1.size();
        len2 = v2.size();

        i1 = 0;
        i2 = 0;

        turn = (len1 == 0) ? 1 : 0;

        this->v1 = v1;
        this->v2 = v2;
    }

    int next() {
        int ele;

        if (turn == 0) {
            if (i1 >= len1) {
                // error: should never happen
                // throw logic_error("illegal state: v1 finished in it's turn");
                return INT_MIN;
            }

            ele = v1[i1++];
            if (i2 < len2) {
                turn = 1;
            }
        } else {
            if (i2 >= len2) {
                // error: should never happen
                // throw logic_error("illegal state: v2 finished in it's turn");
                return INT_MIN;
            }

            ele = v2[i2++];
            if (i1 < len1) {
                turn = 0;
            }
        }

        return ele;
    }

    bool hasNext() {
        return (i1 < len1) || (i2 < len2);
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */