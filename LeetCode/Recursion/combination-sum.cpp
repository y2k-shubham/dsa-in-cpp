// https://leetcode.com/problems/combination-sum/

#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

vector<vector<int>> combinationSum(vector<int>& candidates, int target);
void combSumRec(vector<int>& cand, set<map<int, int>>& combSums, int ind, map<int, int>& crrComb, int remSum, bool);
void showCombSums(set<map<int, int>> combSums);
void showMap(map<int, int> freqMap);
vector<vector<int>> convertCombSumsToVecVec(set<map<int, int>>& combSums);
vector<int> convertFreqMapToVec(map<int, int>& freqMap);
void showVecVec(vector<vector<int>> vecVec);
void showVec(vector<int> vec);

int main() {
    vector<int> candidates;

    // g++ -std=c++11 LeetCode/Recursion/combination-sum.cpp
    candidates = {8, 7, 4, 3};
    combinationSum(candidates, 11);

    // candidates = {2, 3, 6, 7};
    // combinationSum(candidates, 7);

    // candidates = {2, 3, 5};
    // combinationSum(candidates, 8);

    return 0;
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
    if (true) {
        showVecVec(vecVec);
    }
    return vecVec;
}

void combSumRec(vector<int>& cand, set<map<int, int>>& combSums, int ind, map<int, int>& crrComb, int remSum, bool debug) {
    if (debug) {
        cout << "\n---------\n";
        printf("at ind = %d ", ind);
        if (ind < cand.size()) {
            printf("cand[ind] = %d, ", cand[ind]);
        }
        printf("remSum = %d\n", remSum);
        showMap(crrComb);
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
        // try to take all possible quantities of crrCand element
        for (int i = 0; (i * crrCand) <= remSum; i++) {
            crrComb[crrCand] = i;
            combSumRec(cand, combSums, ind + 1, crrComb, remSum - (i * crrCand), debug);
        }
        // this is important: before returning, remove crrCand
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

void showCombSums(set<map<int, int>> combSums) {
    for (set<map<int, int>>::iterator i = combSums.begin(); i != combSums.end(); i++) {
        showMap(*i);
    }
}

void showMap(map<int, int> freqMap) {
    for (map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
        pair<int, int> freqPair = *i;
        if (freqPair.second != 0) {
            printf("[%d -> %d], ", freqPair.first, freqPair.second);
        }
    }
    cout << endl;
}

void showVecVec(vector<vector<int>> vecVec) {
    for (int i = 0; i < vecVec.size(); i++) {
        showVec(vecVec[i]);
    }
}

void showVec(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        printf("%d, ", vec[i]);
    }
    cout << endl;
}
