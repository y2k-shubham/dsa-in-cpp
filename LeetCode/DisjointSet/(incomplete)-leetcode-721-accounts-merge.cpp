// LeetCode-721: https://leetcode.com/problems/accounts-merge/
// incomplete; runtime errors

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    int findParent(vector<int>& parentsVec, int child) {
        if ((parentsVec.size() <= child) || (parentsVec[child] == child)) {
            return child;
        }

        int ultimateParent = findParent(parentsVec, parentsVec[child]);
        parentsVec[child] = ultimateParent;

        return ultimateParent;
    }

    vector<string> buildNamesVec(vector<vector<string>>& accounts) {
        int len = accounts.size();

        vector<string> names(len);
        for (int i = 0; i < len; i++) {
            names[i] = accounts[i][0];
        }

        return names;
    }

    // unused
    unordered_map<string, int> buildEmailParentMap(vector<vector<string>>& accounts) {
        int len = accounts.size();

        unordered_map<string, int> emailParentMap;
        for (int i = 0; i < len; i++) {
            emailParentMap[accounts[i][0]] = i;
        }

        return emailParentMap;
    }

    vector<int> buildParentsVec(vector<vector<string>>& accounts) {
        int len = accounts.size();

        vector<int> vec(len);
        for (int i = 0; i < len; i++) {
            vec[i] = i;
        }

        return vec;
    }

    unordered_map<string, int> mergeAccounts(
        vector<vector<string>>& accounts,
        vector<int>& parentsVec) {
        unordered_map<int, vector<string>> parentEmailsMap;
        unordered_map<string, int> emailParentMap;

        for (int i = 0; i < accounts.size(); i++) {
            for (int j = 1; j < accounts[i].size(); i++) {
                string email = accounts[i][j];

                if (emailParentMap.find(email) == emailParentMap.end()) {
                    emailParentMap[email] = findParent(parentsVec, i);
                    parentEmailsMap[i].push_back(email);
                } else {
                    // found common email across two persons
                    // merge parents of both emails
                    parentsVec[i] = findParent(parentsVec, emailParentMap[email]);
                }
            }
        }

        return emailParentMap;
    }

    unordered_map<int, vector<string>> buildMergedOutput1(
        vector<vector<string>>& accounts,
        vector<string>& namesVec,
        vector<int>& parentsVec,
        unordered_map<string, int>& emailParentMap) {
        unordered_map<int, vector<string>> output1;
        for (unordered_map<string, int>::iterator it = emailParentMap.begin(); it != emailParentMap.end(); it++) {
            int ultimateParent = findParent(parentsVec, it->second);
            output1[ultimateParent].push_back(it->first);
        }

        return output1;
    }

    vector<vector<string>> buildMergedOutput2(
        vector<string>& namesVec,
        unordered_map<int, vector<string>>& output1) {
        vector<vector<string>> output2;

        for (unordered_map<int, vector<string>>::iterator it = output1.begin(); it != output1.end(); it++) {
            string personName = namesVec[it->first];

            vector<string> emailsVec = it->second;
            sort(emailsVec.begin(), emailsVec.end());

            emailsVec.insert(emailsVec.begin(), personName);

            output2.push_back(emailsVec);
        }

        return output2;
    }

   public:
    friend class SolutionTest;

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        if (accounts.size() <= 1) {
            return accounts;
        }

        vector<string> namesVec = buildNamesVec(accounts);
        // unordered_map <string, int> emailParentMap = buildEmailParentMap(accounts);
        vector<int> parentsVec = buildParentsVec(accounts);

        unordered_map<string, int> emailParentMap = mergeAccounts(accounts, parentsVec);

        unordered_map<int, vector<string>> output1 = buildMergedOutput1(
            accounts,
            namesVec,
            parentsVec,
            emailParentMap);
        vector<vector<string>> output2 = buildMergedOutput2(namesVec, output1);

        return output2;
    }
};

class SolutionTest {
   public:
    void testFindParent() {
        Solution soln = Solution();
        vector<int> inParentsVec;
        int inChild;
        int outParentExpected, outParentComputed;

        inParentsVec = {};
        assert(soln.findParent(inParentsVec, 9) == 9);

        inParentsVec = {3, 2, 2, 2};
        assert(soln.findParent(inParentsVec, 0) == 2);
        assert(soln.findParent(inParentsVec, 1) == 2);
        assert(soln.findParent(inParentsVec, 2) == 2);
        assert(soln.findParent(inParentsVec, 3) == 2);

        inParentsVec = {3, 0, 2, 2};
        assert(soln.findParent(inParentsVec, 0) == 2);
        assert(soln.findParent(inParentsVec, 1) == 2);
        assert(soln.findParent(inParentsVec, 2) == 2);
        assert(soln.findParent(inParentsVec, 3) == 2);

        inParentsVec = {3, 0, 2, 3};
        assert(soln.findParent(inParentsVec, 0) == 3);
        assert(soln.findParent(inParentsVec, 1) == 3);
        assert(soln.findParent(inParentsVec, 2) == 2);
        assert(soln.findParent(inParentsVec, 3) == 3);

        inParentsVec = {3, 2, 2, 3};
        assert(soln.findParent(inParentsVec, 0) == 3);
        assert(soln.findParent(inParentsVec, 1) == 2);
        assert(soln.findParent(inParentsVec, 2) == 2);
        assert(soln.findParent(inParentsVec, 3) == 3);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindParent();

    return 0;
}
