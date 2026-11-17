// LeetCode-2073: https://leetcode.com/problems/time-needed-to-buy-tickets/
// if done the right (optimal way : single pass), this question isn't that easy

#include <vector>

using namespace std;

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int n = tickets.size();
        if (n == 1) {
            return tickets[0];
        }

        int kthPersonNumTicketsToBuy = tickets[k];
        int kthPersonTimeToBuyTickets = 0;

        // waiting time faced by kth person due to persons before him (0 to k-1)
        for (int i = 0; i < k; i++) {
            kthPersonTimeToBuyTickets += min(tickets[i], kthPersonNumTicketsToBuy);
        }

        // time taken by kth person to buy own tickets
        kthPersonTimeToBuyTickets += kthPersonNumTicketsToBuy;

        // waiting time faced by kth person due to persons after him (k to n-1)
        for (int i = k + 1; i < n; i++) {
            kthPersonTimeToBuyTickets += min(tickets[i], kthPersonNumTicketsToBuy - 1);
        }

        return kthPersonTimeToBuyTickets;
    }
};
