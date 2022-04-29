// LeetCode-838: https://leetcode.com/problems/push-dominoes/
// incomplete (simulation problem)

#include <unordered_set>
#include <vector>
#include <iostream>
#include <utility>
#include <cassert>
#include <set>
#include <sstream>

using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, char>& v) const {
        return v.first * 31 + v.second;
    }
};

class Solution {
private:
    set<pair<int, char> > convertToOrderedSet(unordered_set<pair<int, char>, pair_hash>& unorderedSet) {
        set<pair<int, char> > orderedSet(unorderedSet.begin(), unorderedSet.end());
        return orderedSet;
    }

    string vecStringRepr(vector<char>& vec) {
        string str(vec.begin(), vec.end());
        return str;
    }

    string fallSetStringRepr(unordered_set<pair<int, char>, pair_hash>& fallSet, int len) {
        ostringstream oss;

        for (int i = 0; i < len; i++) {
            if (fallSet.find({i, 'L'}) != fallSet.end()) {
                oss << 'L';
            } else if (fallSet.find({i, 'R'}) != fallSet.end()) {
                oss << 'R';
            } else {
                oss << '.';
            }
        }

        return oss.str();
    }

    vector<char> convertToVec(string& str) {
        if (str.empty()) {
            return {};
        }

        vector<char> vec(str.begin(), str.end());
        return vec;
    }

    string convertToStr(vector<char>& vec) {
        if (vec.empty()) {
            return "";
        }

        string str(vec.begin(), vec.end());
        return str;
    }

    unordered_set<pair<int, char>, pair_hash> buildFallSet(vector<char>& vec) {
        if (vec.empty()) {
            return {};
        }

        unordered_set<pair<int, char>, pair_hash> fallSet;

        for (int i = 0; i < vec.size(); i++) {
            char ch = vec[i];
            if (ch != '.') {
                fallSet.insert({i, ch});
            }
        }

        return fallSet;
    }

    unordered_set<pair<int, char>, pair_hash> moveDominos(
            vector<char>& vec,
            unordered_set<pair<int, char>, pair_hash>& fallSet
    ) {
        if (vec.empty() || fallSet.empty()) {
            return {};
        }

        unordered_set<pair<int, char>, pair_hash> updatedFallSet;

        for (auto it = fallSet.begin(); it != fallSet.end(); it++) {
            pair<int, char> domino = *it;

            // update dominos state
            vec[domino.first] = domino.second;

            // determine position of next domino
            int nextDominoIdx = domino.first + ((domino.second == 'R') ? 1 : -1);
            // check if next domino exists and not already fallen
            bool nextDominoExists = (0 <= nextDominoIdx) && (nextDominoExists <= vec.size());
            bool nextDominoNotAlreadyFallen = nextDominoExists && (vec[nextDominoIdx] == '.');
            if (!nextDominoNotAlreadyFallen) {
                // if next domino already fallen, the domino-effect of current domino ends here
                continue;
            }

            // determine opposite fall direction of next domino
            char nextDominoOppFall = (domino.second == 'L') ? 'R' : 'L';
            if (updatedFallSet.find({nextDominoIdx, nextDominoOppFall}) != updatedFallSet.end()) {
                // if already added, (meaning that next domino
                // got fallen-upon from both sides) then remove it
                updatedFallSet.erase({nextDominoIdx, nextDominoOppFall});
            } else {
                // otherwise add next domino to updatedFallSet
                updatedFallSet.erase({nextDominoIdx, domino.second});
            }
        }

        return updatedFallSet;
    }

public:
    friend class SolutionTest;

    string pushDominoes(string dominoesStr) {
        vector<char> dominoesVec = convertToVec(dominoesStr);

        unordered_set<pair<int, char>, pair_hash> fallSet = buildFallSet(dominoesVec);
        while (!fallSet.empty()) {
            fallSet = moveDominos(dominoesVec, fallSet);
        }

        string finalDominoesStr = convertToStr(dominoesVec);
        return finalDominoesStr;
    }
};

class SolutionTest {
public:
    void testBuildFallSet() {
        Solution soln = Solution();
        string strIn;
        vector<char> vecInExpected;
        vector<char> vecInComputed;
        unordered_set<pair<int, char>, pair_hash> fallSetOutExpected;
        unordered_set<pair<int, char>, pair_hash> fallSetOutComputed;

        strIn = "";
        vecInExpected = {};
        vecInComputed = soln.convertToVec(strIn);
        assert(vecInExpected == vecInComputed);
        fallSetOutExpected = {};
        fallSetOutComputed = soln.buildFallSet(vecInExpected);
        assert(fallSetOutExpected == fallSetOutComputed);

        strIn = ".";
        vecInExpected = {'.'};
        vecInComputed = soln.convertToVec(strIn);
        assert(vecInExpected == vecInComputed);
        fallSetOutExpected = {};
        fallSetOutComputed = soln.buildFallSet(vecInExpected);
        assert(fallSetOutExpected == fallSetOutComputed);

        strIn = "L";
        vecInExpected = {'L'};
        vecInComputed = soln.convertToVec(strIn);
        assert(vecInExpected == vecInComputed);
        fallSetOutExpected = {{0, 'L'}};
        fallSetOutComputed = soln.buildFallSet(vecInExpected);
        assert(fallSetOutExpected == fallSetOutComputed);

        strIn = "L.R";
        vecInExpected = {'L', '.', 'R'};
        vecInComputed = soln.convertToVec(strIn);
        assert(vecInExpected == vecInComputed);
        fallSetOutExpected = {{0, 'L'},
                              {2, 'R'}};
        fallSetOutComputed = soln.buildFallSet(vecInExpected);
        assert(fallSetOutExpected == fallSetOutComputed);

        strIn = "L.RL.";
        vecInExpected = {'L', '.', 'R', 'L', '.'};
        vecInComputed = soln.convertToVec(strIn);
        assert(vecInExpected == vecInComputed);
        fallSetOutExpected = {{0, 'L'},
                              {2, 'R'},
                              {3, 'L'}};
        fallSetOutComputed = soln.buildFallSet(vecInExpected);
        assert(fallSetOutExpected == fallSetOutComputed);
    }

    void testMoveDominos() {
        Solution soln = Solution();
        string strIn;
        vector<char> vecIn;
        vector<char> vecOutExpected;
        unordered_set<pair<int, char>, pair_hash> fallSetIn;
        unordered_set<pair<int, char>, pair_hash> fallSetOutExpected;
        unordered_set<pair<int, char>, pair_hash> fallSetOutComputed;
        string strOutExpected;
        string strOutComputed;

        strIn = "";
        strOutExpected = soln.convertToStr(vecIn);
        assert(strOutExpected == strOutComputed);
        vecIn = soln.convertToVec(strIn);
        vecOutExpected = soln.convertToVec(strOutExpected);
        assert(vecOutExpected == vecIn);
        fallSetIn = {{3, 'L'}};
        fallSetOutExpected = {};
        fallSetOutComputed = soln.moveDominos(vecIn, fallSetIn);
        assert(fallSetOutExpected == fallSetOutComputed);

        strIn = "LL.R";
        vecIn = soln.convertToVec(strIn);
        fallSetIn = {{0, 'L'},
                     {1, 'L'},
                     {3, 'R'}};
        fallSetOutExpected = {};
        fallSetOutComputed = soln.moveDominos(vecIn, fallSetIn);
        assert(fallSetOutExpected == fallSetOutComputed);
        vecOutExpected = {'L', 'L', '.', 'R'};
//        printf("outExpected=%s, outComputed=%s\n", soln.vecStringRepr(vecOutExpected).c_str(), soln.vecStringRepr(vecIn).c_str());
        assert(vecOutExpected == vecIn);
        strOutExpected = "LL.R";
        strOutComputed = soln.convertToStr(vecIn);
        assert(strOutExpected == strOutComputed);

        strIn = "RR.L";
        vecIn = soln.convertToVec(strIn);
        fallSetIn = {{0, 'R'},
                     {1, 'R'},
                     {3, 'L'}};
        fallSetOutExpected = {};
        fallSetOutComputed = soln.moveDominos(vecIn, fallSetIn);
        assert(fallSetOutExpected == fallSetOutComputed);
        vecOutExpected = {'R', 'R', '.', 'L'};
//        printf("outExpected=%s, outComputed=%s\n", soln.vecStringRepr(vecOutExpected).c_str(), soln.vecStringRepr(vecIn).c_str());
        assert(vecOutExpected == vecIn);
        strOutExpected = "RR.L";
        strOutComputed = soln.convertToStr(vecIn);
        assert(strOutExpected == strOutComputed);

        strIn = "RR.L..R..R..L.LRL";
        vecIn = soln.convertToVec(strIn);
        fallSetIn = {{0,  'R'},
                     {1,  'R'},
                     {3,  'L'},
                     {6,  'R'},
                     {9,  'R'},
                     {12, 'L'},
                     {14, 'L'},
                     {15, 'R'},
                     {16, 'L'}};
        fallSetOutExpected = {};
        fallSetOutComputed = soln.moveDominos(vecIn, fallSetIn);
        assert(fallSetOutExpected == fallSetOutComputed);
        vecOutExpected = {'R', 'R', '.', 'L', '.', '.', 'R', '.', '.', 'R', '.', '.', 'L', '.', 'L', 'R', 'L'};
//        printf("outExpected=%s, outComputed=%s\n", soln.vecStringRepr(vecOutExpected).c_str(), soln.vecStringRepr(vecIn).c_str());
        assert(vecOutExpected == vecIn);
        strOutExpected = "RR.L..R..R..L.LRL";
        strOutComputed = soln.convertToStr(vecIn);
        assert(strOutExpected == strOutComputed);

        strIn = "RR.L..R..R..L.LRL";
        vecIn = soln.convertToVec(strIn);
        fallSetIn = {{7,  'R'},
                     {10, 'R'},
                     {11, 'L'},
                     {13, 'L'}};
        fallSetOutExpected = {};
        fallSetOutComputed = soln.moveDominos(vecIn, fallSetIn);
        assert(fallSetOutExpected == fallSetOutComputed);
        vecOutExpected = {'R', 'R', '.', 'L', '.', '.', 'R', 'R', '.', 'R', 'R', 'L', 'L', 'L', 'L', 'R', 'L'};
//        printf("outExpected=%s, outComputed=%s\n", soln.vecStringRepr(vecOutExpected).c_str(), soln.vecStringRepr(vecIn).c_str());
        assert(vecOutExpected == vecIn);
        strOutExpected = "RR.L..RR.RRLLLLRL";
        strOutComputed = soln.convertToStr(vecIn);
        assert(strOutExpected == strOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildFallSet();
    solnTest.testMoveDominos();

    return 0;
}
