// LeetCode-1109: https://leetcode.com/problems/corporate-flight-bookings/
// O(n) approach suggestion: https://medium.com/@yy929058/leetcode-1109-corporate-flight-bookings-81829424305b

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n) {
        vector<int> answer(n);

        for (int i = 0; i < bookings.size(); i++) {
            vector<int> crrBooking = bookings[i];
            int beginIdx = crrBooking[0] - 1;
            int endIdx = crrBooking[1]; // note that we wont decrement from endIdx
            int numSeats = crrBooking[2];

            answer[beginIdx] += numSeats;
            if (endIdx < n) {
                answer[endIdx] -= numSeats;
            }
        }

        for (int i = 1; i < answer.size(); i++) {
            answer[i] = answer[i - 1] + answer[i];
        }

        return answer;
    }
};
