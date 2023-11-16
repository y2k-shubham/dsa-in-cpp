// LeetCode-728:  https://leetcode.com/problems/self-dividing-numbers/
// stupid problem, solved using brute force (unsure if there's a smarter way)

#include <list>
#include <set>
#include <vector>

using namespace std;

class Solution {
private:
    int n;
    list<int> digits;
    set<int> digitSet;
    int sumOfDigits;

    inline void init(int n) {
        this->n = n;
        this->digits = extractDigits(n);
        set<int> digitSet(this->digits.begin(), this->digits.end());
        this->digitSet = digitSet;
        this->sumOfDigits = calcSumOfDigits(this->digits);
    }

    inline bool isSelfDividing(int n) {
        init(n);

        if (this->digitSet.find(0) != this->digitSet.end()) {
            return false;
        }

        vector<bool> isDivisible(10, false);
        vector<bool> computed(10, false);

        isDivisible[1] = true;
        computed[0] = computed[1] = true;

        bool isDivisibleFlag = false;
        for (set<int>::iterator dig = digitSet.begin(); dig != digitSet.end(); dig++) {
            if (computed[*dig]) {
                continue;
            }

            bool isDisibleFlag = false;
            switch (*dig) {
                case 2:
                    isDivisibleFlag = isDivisibleBy2();
                    break;

                case 3:
                    isDivisibleFlag = isDivisibleBy3();
                    break;

                case 4:
                    isDivisibleFlag = isDivisibleBy4();
                    break;

                case 5:
                    isDivisibleFlag = isDivisibleBy5();
                    break;

                case 6:
                    isDivisibleFlag = isDivisibleBy6();
                    break;

                case 7:
                    isDivisibleFlag = (n % 7) == 0;
                    break;

                case 8:
                    isDivisibleFlag = isDivisibleBy8();
                    break;

                case 9:
                    isDivisibleFlag = isDivisibleBy9();
                    break;

                default:
                    isDivisibleFlag = true;
            }

            if (!isDivisibleFlag) {
                return false;
            }

            isDivisible[*dig] = isDivisibleFlag;
            computed[*dig] = true;
        }

        return true;
    }

    inline list<int> extractDigits(int n) {
        list<int> digits;

        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }

        return digits;
    }

    inline int calcSumOfDigits(list<int>& digits) {
        int sum = 0;
        for (list<int>::iterator it = digits.begin(); it != digits.end(); it++) {
            sum += *it;
        }

        return sum;
    }

    inline bool isDivisibleBy2() {
        return (n & 1) == 0;
    }

    inline bool isDivisibleBy3() {
        return (sumOfDigits % 3) == 0;
    }

    inline bool isDivisibleBy4() {
        // int last2Digits = n % 100;
        // return (last2Digits % 4) == 0;
        return (n & 3) == 0;
    }

    inline bool isDivisibleBy5() {
        int lastDigit = n % 10;
        return (lastDigit == 0) || (lastDigit == 5);
    }

    inline bool isDivisibleBy6() {
        return isDivisibleBy2() && isDivisibleBy3();
    }

    inline bool isDivisibleBy8() {
        return (n & 7) == 0;
    }

    inline bool isDivisibleBy9() {
        return (sumOfDigits % 9) == 0;
    }

public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> vec;
        for (int i = left; i <= right; i++) {
            if (isSelfDividing(i)) {
                vec.push_back(i);
            }
        }

        return vec;
    }
};
