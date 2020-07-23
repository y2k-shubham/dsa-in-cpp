// LeetCode-38: https://leetcode.com/problems/count-and-say/
// https://www.geeksforgeeks.org/look-and-say-sequence/
// https://www.interviewbit.com/problems/count-and-say/

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void showVec(vector<int> vec, string name);
vector<int> getNextSeq(vector<int>);
void testGetNextSeq();
vector<int> getNthSeq(int);
void testGetNthSeq();
string toString(vector<int>);
void testToString();
string countAndSay(int);
void testCountAndSay();

int main() {
    testGetNextSeq();
    testGetNthSeq();
    testToString();
    testCountAndSay();

    return 0;
}

void showVec(vector<int> vec, string name) {
    printf("\n%s vec is:-\n", name.c_str());

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == INT_MAX) {
            printf("+inf\t");
        } else if (vec[i] == INT_MIN) {
            printf("-inf\t");
        } else if (vec[i] <= 0) {
            printf("-\t");
        } else {
            printf("%d\t", vec[i]);
        }
    }
    cout << endl;
}

void testGetNextSeq() {
    vector<int> outExpected;

    outExpected = {};
    assert(getNextSeq({}) == outExpected);

    outExpected = {1, 1};
    // showVec(getNextSeq({1}), "");
    assert(getNextSeq({1}) == outExpected);

    outExpected = {2, 1};
    assert(getNextSeq({1, 1}) == outExpected);

    outExpected = {1, 2, 1, 1};
    assert(getNextSeq({2, 1}) == outExpected);

    outExpected = {1, 1, 1, 2, 2, 1};
    assert(getNextSeq({1, 2, 1, 1}) == outExpected);

    outExpected = {3, 1, 2, 2, 1, 1};
    assert(getNextSeq({1, 1, 1, 2, 2, 1}) == outExpected);
}

vector<int> getNextSeq(vector<int> seq) {
    vector<int> nextSeq;

    int i;
    for (i = 0; i < seq.size();) {
        int crrVal = seq[i];
        int freq = 1;

        i++;
        while (i < seq.size() && seq[i] == crrVal) {
            i++;
            freq++;
        }

        nextSeq.push_back(freq);
        nextSeq.push_back(crrVal);
    }

    return nextSeq;
}

void testGetNthSeq() {
    vector<int> outExpected;

    outExpected = {};
    assert(getNthSeq(0) == outExpected);

    outExpected = {1};
    assert(getNthSeq(1) == outExpected);

    outExpected = {1, 1};
    assert(getNthSeq(2) == outExpected);

    outExpected = {2, 1};
    assert(getNthSeq(3) == outExpected);

    outExpected = {1, 2, 1, 1};
    assert(getNthSeq(4) == outExpected);

    outExpected = {1, 1, 1, 2, 2, 1};
    assert(getNthSeq(5) == outExpected);
}

vector<int> getNthSeq(int n) {
    if (n == 0) {
        return {};
    } else {
        vector<int> seq = {1};
        for (int i = 1; i < n; i++) {
            seq = getNextSeq(seq);
        }
        return seq;
    }
}

void testToString() {
    assert(toString({}) == "");
    assert(toString({1}) == "1");
    assert(toString({1, 1}) == "11");
    assert(toString({2, 1}) == "21");
    assert(toString({1, 2, 1, 1}) == "1211");
    assert(toString({1, 1, 1, 2, 2, 1}) == "111221");
}

string toString(vector<int> vec) {
    string str;
    for (int i = 0; i < vec.size(); i++) {
        // int to string https://stackoverflow.com/a/5591169/3679900
        str = str + to_string(vec[i]);
    }
    return str;
}

void testCountAndSay() {
    assert(countAndSay(0) == "");
    assert(countAndSay(1) == "1");
    assert(countAndSay(2) == "11");
    assert(countAndSay(3) == "21");
    assert(countAndSay(4) == "1211");
    assert(countAndSay(5) == "111221");
    assert(countAndSay(6) == "312211");
}

string countAndSay(int n) {
    vector<int> nthSeq = getNthSeq(n);
    return toString(nthSeq);
}
