// LeetCode BiWeekly-Contest-196: https://leetcode.com/contest/biweekly-contest-196/problems/assign-umbrella-on-rainy-days/
// easy: straightforward do-as-directed simulation

#include <vector>

using namespace std;

class Solution {
private:


public:
    vector<string> assignUmbrella(vector<int>& rain) {
        int n = rain.size();

        int aliceCount = 0;
        int bobCount = 0;
        vector <string> answer(n);
        for (int i = 0; i < n; i++) {
            bool aliceNeeds = (i < (n - 1)) && ((rain[i] == 1) && (rain[i + 1] == 1));
            bool bobNeeds = rain[i] == 1;
            bool bobReceivedFewerTimes = aliceCount > bobCount;

            if (aliceNeeds && bobNeeds) {
                if (bobReceivedFewerTimes) {
                    bobCount++;
                    answer[i] = "Bob";
                } else {
                    aliceCount++;
                    answer[i] = "Alice";
                }
            } else if (aliceNeeds) {
                aliceCount++;
                answer[i] = "Alice";
            } else if (bobNeeds) {
                bobCount++;
                answer[i] = "Bob";
            } else {
                answer[i] = "None";
            }
        }

        return answer;
    }
};
