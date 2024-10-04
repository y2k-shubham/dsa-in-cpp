// LeetCode-2491: https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int len = skill.size();
        if ((len == 0) || (len % 2 != 0)) {
            return -1;
        }

        sort(skill.begin(), skill.end());

        long long chemistrySum = 0;
        int expectedTeamSkill = skill[0] + skill[len - 1];

        for (int i = 0; i < (len / 2); i++) {
            int player1Skill = skill[i];
            int player2Skill = skill[len - 1 - i];

            int crrTeamSkill = player1Skill + player2Skill;
            if (crrTeamSkill != expectedTeamSkill) {
                return -1;
            }

            chemistrySum += (long long) (player1Skill * player2Skill);
        }

        return chemistrySum;
    }
};

class SolutionTest {
public:
    void testDividePlayers() {
        Solution soln = Solution();
        vector<int> skill;
        long long chemistrySumOutExpected;
        long long chemistrySumOutComputed;

        skill = {3, 2, 5, 1, 3, 4};
        chemistrySumOutExpected = 22;
        chemistrySumOutComputed = soln.dividePlayers(skill);
        assert(chemistrySumOutExpected == chemistrySumOutComputed);

        skill = {3, 4};
        chemistrySumOutExpected = 12;
        chemistrySumOutComputed = soln.dividePlayers(skill);
        assert(chemistrySumOutExpected == chemistrySumOutComputed);

        skill = {1, 1, 2, 3};
        chemistrySumOutExpected = -1;
        chemistrySumOutComputed = soln.dividePlayers(skill);
        assert(chemistrySumOutExpected == chemistrySumOutComputed);

        printf("[testDividePlayers] All test cases passed\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testDividePlayers();

    return 0;
}
