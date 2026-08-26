// LeetCode-170: https://leetcode.com/problems/two-sum-iii-data-structure-design/
// Premium
// Companies: [Amazon]
// Not easy : too many edge cases (frustrating)

#include <vector>
#include <map>

using namespace std;

#define MIN_VALUE -200000
#define MAX_VALUE 200000

class TwoSum {
private:
    map<int, int> freqMap;
    int numElements;

    bool haveSeenNumber(int number) {
        return (freqMap.find(number) != freqMap.end()) && (freqMap[number] > 0);
    }

public:
    TwoSum() {
        numElements = 0;
    }

    void add(int number) {
        freqMap[number]++;
        numElements++;
    }

    bool find(int value) {
        if ((value < MIN_VALUE) || (value > MAX_VALUE) || (numElements < 2)) {
            return false;
        }

        bool valueIsEven = (value & 1) == 0;
        if (valueIsEven) {
            int halfOfValue = value / 2;
            if (haveSeenNumber(halfOfValue) && freqMap[halfOfValue] > 1) {
                printf("returned here 1\n");
                return true;
            }
        }

        for (auto it = freqMap.begin(); (it != freqMap.end()) && (it->first < (value - it->first)); it++) {
            int complement = value - it->first;
            if (haveSeenNumber(complement)) {
                printf("returned here 2, where value=%d, it=%d, complement=%d\n", value, it->first, complement);
                return true;
            }
        }

        return false;
    }
};

