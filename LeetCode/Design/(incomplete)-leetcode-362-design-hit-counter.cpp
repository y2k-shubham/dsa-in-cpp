// LeetCode-362: https://leetcode.com/problems/design-hit-counter/
// Premium
// Companies: [Apple][Databricks][Bloomberg][Uber][Google][Roblox][Wise][Amazon][Yandex][Microsoft][Snowflake][Walmart Labs][Cloudflare][Affirm][Meta][Reddit][Coupang]
// incomplete

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

#define WINDOW_SECONDS 300

class HitCounter {
private:
    vector <int> hitTimestamps;

public:
    HitCounter() {
        hitTimestamps.clear();
    }

    void hit(int timestamp) {
        hitTimestamps.push_back(timestamp);
    }

    int getHits(int timestamp) {
        // edge-case-1
        if (hitTimestamps.empty()) {
            return 0;
        }

        // edge-case-2: looking too far into future
        int crrTimestamp = hitTimestamps.back();
        if (timestamp > (crrTimestamp + WINDOW_SECONDS)) {
            return 0;
        }

        // get upper bound
        int lowerBoundTimestamp = timestamp - WINDOW_SECONDS;
        auto itUpper = upper_bound(hitTimestamps.begin(), hitTimestamps.end(), timestamp);
        if (itUpper == hitTimestamps.end()) {
            printf("decreasing upper ");
            itUpper--;
        }

        // get lower bound
        auto itLower = lower_bound(hitTimestamps.begin(), hitTimestamps.end(), lowerBoundTimestamp);

        printf("lower=%d, upper=%d\n", *itLower, *itUpper);

        return ((int) (itUpper - itLower));
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
