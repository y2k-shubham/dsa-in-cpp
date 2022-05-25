// LeetCode-2160: https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/

#include <iostream>
#include <list>
#include <map>

using namespace std;

class Solution {
private:
    map<int, int> findDigFreqs(int n) {
        map<int, int> digFreqs;

        while (n > 0) {
            int dig = n % 10;
            n /= 10;

            digFreqs[dig]++;
        }

        return digFreqs;
    }

    list<int> extractSmallestNums(map<int, int>& freqMap, int count) {
        list<int> smallestNums;

        for (int i = 1; i <= count; i++) {
            auto it = freqMap.begin();
            int smallestVal = it->first;

            smallestNums.push_back(smallestVal);

            freqMap[smallestVal]--;
            if (freqMap[smallestVal] == 0) {
                freqMap.erase(smallestVal);
            }
        }

        return smallestNums;
    }

    void showList(list<int>& mList) {
        printf("list is:-\n");

        for (auto it = mList.begin(); it != mList.end(); it++) {
            printf("%d ", *it);
        }

        cout << endl;
    }

    int calcSum(list<int>& mList, int multiplier) {
        int sum = 0;

        for (auto it = mList.begin(); it != mList.end(); it++) {
            sum += *it;
        }

        return sum * multiplier;
    }

public:
    int minimumSum(int num) {
        map<int, int> digFreqs = findDigFreqs(num);

        list<int> smaller2Nums = extractSmallestNums(digFreqs, 2);
        // showList(smaller2Nums);
        list<int> bigger2Nums = extractSmallestNums(digFreqs, 2);
        // showList(bigger2Nums);

        int sum = 0;
        sum += calcSum(smaller2Nums, 10);
        sum += calcSum(bigger2Nums, 1);

        return sum;
    }
};
