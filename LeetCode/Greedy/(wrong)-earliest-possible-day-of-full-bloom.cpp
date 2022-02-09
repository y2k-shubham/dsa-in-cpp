// LeetCode-2163: https://leetcode.com/problems/earliest-possible-day-of-full-bloom/
// wrong answer (might be incomplete; but likely wrong approach -> not solvable by greedy method)

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

bool comparator(const tuple<int, int, float>& t1, const tuple<int, int, float>& t2) {
    // sort by descending order of float value
    return get<2>(t1) >= get<2>(t2);
}

class Solution {
   private:
    bool debug = true;

    vector<tuple<int, int, float>> zipVecs(
        vector<int>& vecNumr,
        vector<int>& vecDenr) {
        int len = vecNumr.size();

        vector<tuple<int, int, float>> zippedVec(len);
        for (int i = 0; i < len; i++) {
            zippedVec[i] = {vecDenr[i], vecNumr[i], ((vecNumr[i] * 1.0f) / vecDenr[i])};
        }

        return zippedVec;
    }

    void showVec(vector<tuple<int, int, float>>& vec) {
        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Plnt:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", get<0>(vec[i]));
        }
        cout << endl;

        printf("Grth:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", get<1>(vec[i]));
        }
        cout << endl;

        printf("Ratio:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%3.2f\t", get<2>(vec[i]));
        }
        cout << endl;
    }

    int findMinLastBloomDay(vector<tuple<int, int, float>>& zip) {
        sort(zip.begin(), zip.end(), comparator);
        if (debug) {
            showVec(zip);
        }

        int lastBloomDay = 0;
        int crrDay = 0;
        for (int i = 0; i < zip.size(); i++) {
            int plantDays;
            int growthDays;
            float ratio;
            tie(plantDays, growthDays, ratio) = zip[i];

            if (debug) {
                printf("\noriginal crrDay=%d & lastBloomDay=%d\n", crrDay, lastBloomDay);
                printf("at [%d]={plantTime=%d, growthTime=%d, ratio=%3.2f}\n", i, plantDays, growthDays, ratio);
            }

            crrDay += plantDays;

            int crrBloomDay = crrDay + growthDays;
            lastBloomDay = max(lastBloomDay, crrBloomDay);

            if (debug) {
                printf("updated crrDay=%d, crrBloomDay=%d, lastBloomDay=%d\n", crrDay, crrBloomDay, lastBloomDay);
            }
        }

        return lastBloomDay;
    }

   public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        vector<tuple<int, int, float>> zip = zipVecs(plantTime, growTime);
        return findMinLastBloomDay(zip);
    }
};
