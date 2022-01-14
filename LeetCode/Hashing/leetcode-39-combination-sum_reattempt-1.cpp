// LeetCode-39: https://leetcode.com/problems/combination-sum/

#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    void showMap(map<int, int> freqMap) {
        for (map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
            printf("[%d -> %d], ", (*i).first, (*i).second);
        }
        cout << endl;
    }

    void showCombSums(set<map<int, int>> combSums) {
        for (set<map<int, int>>::iterator i = combSums.begin(); i != combSums.end(); i++) {
            showMap(*i);
        }
    }

    void showVec(vector<int> vec) {
        for (int i = 0; i < vec.size(); i++) {
            printf("%d, ", vec[i]);
        }
        cout << endl;
    }

    void showVecVec(vector<vector<int>> vecVec) {
        for (int i = 0; i < vecVec.size(); i++) {
            showVec(vecVec[i]);
        }
    }

    void combSumRec(vector<int>& cand, set<map<int, int>>& combSums, int ind, map<int, int>& crrComb, int remSum, bool debug) {
        if (debug) {
            cout << "\n---------\n";
            printf("at ind = %d ", ind);
            if (ind < cand.size()) {
                printf("cand[ind] = %d, ", cand[ind]);
            }
            printf("remSum = %d\n", remSum);
        }

        if (remSum == 0) {
            map<int, int> crrCombCopy = crrComb;
            combSums.insert(crrCombCopy);
            if (debug) {
                printf("found new soln\n");
                showMap(crrCombCopy);
            }
        } else if (ind >= cand.size() || remSum < 0) {
            if (debug) {
                printf("returning on violation\n");
            }
            return;
        } else {
            int crrCand = cand[ind];
            for (int i = 0; (i * crrCand) <= remSum; i++) {
                crrComb[crrCand] = i;
                combSumRec(cand, combSums, ind + 1, crrComb, remSum - (i * crrCand), debug);
            }
            crrComb.erase(crrCand);
        }
    }

    vector<vector<int>> convertCombSumsToVecVec(set<map<int, int>>& combSums) {
        vector<vector<int>> vecVec;

        for (set<map<int, int>>::iterator i = combSums.begin(); i != combSums.end(); i++) {
            map<int, int> freqMap = *i;
            vecVec.push_back(convertFreqMapToVec(freqMap));
        }

        return vecVec;
    }

    vector<int> convertFreqMapToVec(map<int, int>& freqMap) {
        vector<int> vec;
        for (map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
            int crrNum = (*i).first;
            int freq = (*i).second;
            for (int j = 1; j <= freq; j++) {
                vec.push_back(crrNum);
            }
        }
        return vec;
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        bool debug = false;

        // map <int, set <map <int, int> > > sumFreqSumCombsMap;
        set<map<int, int>> combSums;
        map<int, int> freqMap;

        if (debug) {
            printf("combinationSum: calling combSumRec\n");
        }
        combSumRec(candidates, combSums, 0, freqMap, target, debug);
        if (debug) {
            printf("combinationSum: calling showCombSums\n");
        }
        if (debug) {
            showCombSums(combSums);
        }

        if (debug) {
            printf("combinationSum: returning\n");
        }

        vector<vector<int>> vecVec = convertCombSumsToVecVec(combSums);
        if (debug) {
            showVecVec(vecVec);
        }
        return vecVec;
    }
};