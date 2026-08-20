// LeetCode-274: https://leetcode.com/problems/h-index/

#include <vector>

using namespace std;

#define MAX_CITATIONS 1000

class Solution {
private:
    vector <int> populateFreqVec(vector<int>& citations) {
        vector <int> freqVec(MAX_CITATIONS + 1, 0);

        for (int i = 0; i < citations.size(); i++) {
            freqVec[citations[i]]++;
        }

        return freqVec;
    }

    vector <int> createRCumSumVec(vector <int>& vec) {
        int len = vec.size();

        vector <int> cumSumVec(len, 0);
        cumSumVec[len - 1] = vec[len - 1];

        for (int i = len - 2; i >= 0; i--) {
            cumSumVec[i] = cumSumVec[i + 1] + vec[i];
        }

        return cumSumVec;
    }

    int findHIndex(vector <int>& rCumFreqSumVec) {
        for (int i = MAX_CITATIONS; i >= 0; i--) {
            if (rCumFreqSumVec[i] >= i) {
                return i;
            }
        }

        return 0;
    }

public:
    int hIndex(vector<int>& citations) {
        vector <int> freqVec = populateFreqVec(citations);
        vector <int> rCumFreqSumVec = createRCumSumVec(freqVec);
        return findHIndex(rCumFreqSumVec);
    }
};
