// LeetCode-258: https://leetcode.com/problems/add-digits/
// pretty dumb problem

class Solution {
   public:
    int addDigits(int num) {
        if (num < 10) {
            return num;
        }

        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }

        return addDigits(sum);
    }
};
