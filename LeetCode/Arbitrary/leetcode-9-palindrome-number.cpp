// LeetCode-9: https://leetcode.com/problems/palindrome-number/

class Solution {
private:
    long long revInt(int n) {
        long long revN = 0;
        
        while (n > 0) {
            revN *= 10;
            revN += n % 10;
            n /= 10;
        }
        
        return revN;
    }
    
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        return ((long long) x) == revInt(x);
    }
};
