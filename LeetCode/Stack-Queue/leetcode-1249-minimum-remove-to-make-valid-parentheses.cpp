// LeetCode-1249: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
// LC Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3645/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    stack<pair<int, char> > findRemoveIndices(string& str) {
        stack<pair<int, char> > stk;

        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);

            switch (ch) {
                case '(':
                    stk.push({i, ch});
                    break;

                case ')':
                    if (!stk.empty() && stk.top().second == '(') {
                        stk.pop();
                    } else {
                        stk.push({i, ch});
                    }
                    break;

                default:
                    break;
            }
        }

        return stk;
    }

    vector<pair<int, char> > convertToVec(stack<pair<int, char> >& stk) {
        int len = stk.size();
        vector<pair<int, char> > vec(len);

        int i = len - 1;
        while (!stk.empty()) {
            vec[i] = stk.top();
            stk.pop();

            i--;
        }

        return vec;
    }

    int advanceTillNonConsec(vector<pair<int, char> >& vec, int idx) {
        int len = vec.size();
        if (idx >= len - 1) {
            return idx;
        }

        int i = idx;
        while (((i + 1) < len) && ((vec[i].first + 1) == vec[i + 1].first)) {
            i++;
        }

        return i;
    }

    string eraseChars(string& str, vector<pair<int, char> >& vec) {
        int len = vec.size();

        if (vec.empty()) {
            return str;
        } else if (len == 1) {
            int posn = vec[0].first;
            str.erase(str.begin() + posn);
            return str;
        } else {
            ostringstream oss;

            // part before first deletion char
            if (vec[0].first > 0) {
                oss << str.substr(0, vec[0].first);
            }

            // parts b/w intermediate deletion chars
            int i = 0;
            while (i < (len - 1)) {
                i = advanceTillNonConsec(vec, i);
                if (i < (len - 1)) {
                    int startInd = vec[i].first + 1;
                    int endInd = vec[i + 1].first - 1;

                    oss << str.substr(startInd, (endInd - startInd + 1));
                    i++;
                }
            }

            // part after the last deletion char
            if (vec[len - 1].first < len - 1) {
                int posn = vec[len - 1].first;
                oss << str.substr(posn + 1);
            }

            return oss.str();
        }
    }

   public:
    string minRemoveToMakeValid(string str) {
        if (str.empty()) {
            return str;
        }

        stack<pair<int, char> > stk = findRemoveIndices(str);
        if (stk.empty()) {
            return str;
        }

        vector<pair<int, char> > vec = convertToVec(stk);
        return eraseChars(str, vec);
    }

    friend class SolutionTest;
};

class SolutionTest {
   private:
    stack<pair<int, char> > getEmptyStack() {
        stack<pair<int, char> > stk;
        return stk;
    }

   public:
    void testFindRemoveIndices() {
        Solution soln = Solution();

        string str;
        stack<pair<int, char> > stkOutExpected;
        stack<pair<int, char> > stkOutComputed;

        stkOutExpected = getEmptyStack();
        str = "lee(t(c)o)de)";
        stkOutExpected.push({12, ')'});
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "a)b(c)d";
        stkOutExpected.push({1, ')'});
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "a)b(cd";
        stkOutExpected.push({1, ')'});
        stkOutExpected.push({3, '('});
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "a(b(c)d";
        stkOutExpected.push({1, '('});
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "a(b)c)d";
        stkOutExpected.push({5, ')'});
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "))((";
        stkOutExpected.push({0, ')'});
        stkOutExpected.push({1, ')'});
        stkOutExpected.push({2, '('});
        stkOutExpected.push({3, '('});
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "";
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "abcd";
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "(a)b()cd";
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);

        stkOutExpected = getEmptyStack();
        str = "()(())(()())";
        stkOutComputed = soln.findRemoveIndices(str);
        assert(stkOutExpected == stkOutComputed);
    }

    void testAdvanceTillNonConsec() {
        Solution soln = Solution();
        vector<pair<int, char> > vec;
        int iIn;
        int iOutExpected;
        int iOutComputed;

        vec = {};
        iIn = 0;
        iOutExpected = 0;
        iOutComputed = soln.advanceTillNonConsec(vec, iIn);
        assert(iOutExpected == iOutComputed);

        vec = {};
        iIn = 1;
        iOutExpected = 1;
        iOutComputed = soln.advanceTillNonConsec(vec, iIn);
        assert(iOutExpected == iOutComputed);

        vec = {{0, 'a'}};
        iIn = 0;
        iOutExpected = 0;
        iOutComputed = soln.advanceTillNonConsec(vec, iIn);
        assert(iOutExpected == iOutComputed);

        vec = {{0, 'a'}};
        iIn = 1;
        iOutExpected = 1;
        iOutComputed = soln.advanceTillNonConsec(vec, iIn);
        assert(iOutExpected == iOutComputed);

        vec = {{0, 'a'}, {1, 'b'}};
        iIn = 0;
        iOutExpected = 0;
        iOutComputed = soln.advanceTillNonConsec(vec, iIn);
        assert(iOutExpected == iOutComputed);

        vec = {{0, 'a'}, {1, 'b'}};
        iIn = 1;
        iOutExpected = 1;
        iOutComputed = soln.advanceTillNonConsec(vec, iIn);
        assert(iOutExpected == iOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testFindRemoveIndices();
    solnTest.testAdvanceTillNonConsec();

    return 0;
}
