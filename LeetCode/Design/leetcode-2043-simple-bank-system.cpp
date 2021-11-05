// LeetCode-2043: https://leetcode.com/problems/simple-bank-system/
// dont even bother looking, really dumb problem

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Bank {
   private:
    vector<long long> balance;

   public:
    Bank(vector<long long>& balance) {
        this->balance = balance;
    }

    bool transfer(int account1, int account2, long long money) {
        bool minAcNoCheck = min(account1, account2) >= 1;
        bool maxAcNoCheck = max(account1, account2) <= this->balance.size();
        if (!minAcNoCheck || !maxAcNoCheck) {
            return false;
        }

        if (this->balance[account1 - 1] >= money) {
            this->balance[account1 - 1] -= money;
            this->balance[account2 - 1] += money;

            return true;
        } else {
            return false;
        }
    }

    bool deposit(int account, long long money) {
        bool minAcNoCheck = account >= 1;
        bool maxAcNoCheck = account <= this->balance.size();
        if (!minAcNoCheck || !maxAcNoCheck) {
            return false;
        }

        this->balance[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money) {
        bool minAcNoCheck = account >= 1;
        bool maxAcNoCheck = account <= this->balance.size();
        if (!minAcNoCheck || !maxAcNoCheck) {
            return false;
        }

        if (this->balance[account - 1] >= money) {
            this->balance[account - 1] -= money;

            return true;
        } else {
            return false;
        }
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
