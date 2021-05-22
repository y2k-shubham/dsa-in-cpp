// incomplete: only partial test-cases passing

// LeetCode-1836: https://leetcode.com/problems/longest-string-chain/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3746/

/**
 * passing test-cases
 * ["a","b","ba","bca","bda","bdca"]
 * ["xbc","pcxbcf","xb","cxbc","pcxbc"]
 * ["mcq"]
 * ["mc", "m", "cm", "cmsju", "mcq", "cms", "cjm", "cmsj"]
 * ["abcd","dbqca"]
 * 
 * failing test-cases
 * ["cozddh","ferawpnpff","ivftewfdn","mq","zmq","nwzmbq","rcozyddh","rcozyddhm","czddh","hrcozyddhm","vftewfdn","vtefdn","rpeyrgwm","wcjaki","jiddfyh","nzmbq","xnvzrzc","zdh","utcc","peyrgwm","pergwm","vftefdn","rcozddh","h","zddh","tcc","nnwhszmbuq","utgcc","nnwszmbq","jiddfh","zmbq","ivtftewfdn","vefdn","ferawpnff","xnvzrc","nnwhszmbq","dh","nwszmbq"]
 * expected: 10
 * actual: 3
 */

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    unordered_set<string> prepareWordSet(vector<string>& wordVec) {
        unordered_set<string> wordSet(wordVec.begin(), wordVec.end());
        return wordSet;
    }

    unordered_map<string, unordered_set<string>> prepareAdjWordsGraph(vector<string>& wordVec) {
        unordered_set<string> wordSet = prepareWordSet(wordVec);
        unordered_map<string, unordered_set<string>> graph;

        for (int i = 0; i < wordVec.size(); i++) {
            string crrWord = wordVec[i];

            for (int j = 0; j < crrWord.size(); j++) {
                string newWord = crrWord;
                newWord.erase(j, 1);

                if (wordSet.find(newWord) != wordSet.end()) {
                    graph[crrWord].insert(newWord);
                }
            }
        }

        return graph;
    }

    void showWordMaxDepthMap(unordered_map<string, int>& wordMaxDepthMap) {
        printf("wordMaxDepthMap is:-\n");
        for (unordered_map<string, int>::iterator it = wordMaxDepthMap.begin(); it != wordMaxDepthMap.end(); it++) {
            printf("[%s] -> %d\n", it->first.c_str(), it->second);
        }
    }

    void showWordMaxDepthChildrenMap(unordered_map<string, unordered_set<string>>& wordMaxDepthChildrenMap) {
        printf("wordMaxDepthChildrenMap is:-\n");
        for (unordered_map<string, unordered_set<string>>::iterator it = wordMaxDepthChildrenMap.begin(); it != wordMaxDepthChildrenMap.end(); it++) {
            string parent = it->first;
            printf("[%s] -> ", parent.c_str());

            unordered_set<string> children = it->second;
            for (unordered_set<string>::iterator jt = children.begin(); jt != children.end(); jt++) {
                printf("%s, ", (*jt).c_str());
            }
            cout << endl;
        }
    }

    int findLongestPathDfsRec(
        unordered_map<string, unordered_set<string>>& graph,
        unordered_map<string, int>& wordMaxDepthMap,
        unordered_map<string, unordered_set<string>>& wordMaxDepthChildrenMap,
        string crrWord) {
        int maxChildDepth = 0;

        unordered_set<string> children = graph[crrWord];
        if (!children.empty()) {
            for (unordered_set<string>::iterator it = children.begin(); it != children.end(); it++) {
                string child = *it;
                int crrChildDepth = findLongestPathDfsRec(graph, wordMaxDepthMap, wordMaxDepthChildrenMap, child);
                if (crrChildDepth == maxChildDepth) {
                    wordMaxDepthChildrenMap[crrWord].insert(child);
                } else if (crrChildDepth > maxChildDepth) {
                    maxChildDepth = crrChildDepth;
                    wordMaxDepthChildrenMap[crrWord].clear();
                    wordMaxDepthChildrenMap[crrWord].insert(child);
                }
            }
        }

        int crrWordDepth = maxChildDepth + 1;
        wordMaxDepthMap[crrWord] = crrWordDepth;

        return crrWordDepth;
    }

    pair<unordered_map<string, int>, unordered_map<string, unordered_set<string>>> findLongestPathDfs(
        vector<string>& wordVec,
        unordered_map<string, unordered_set<string>>& graph) {
        unordered_map<string, int> wordMaxDepthMap;
        unordered_map<string, unordered_set<string>> wordMaxDepthChildrenMap;
        for (int i = 0; i < wordVec.size(); i++) {
            string crrWord = wordVec[i];
            wordMaxDepthMap[crrWord] = 0;
            wordMaxDepthChildrenMap[crrWord];  // create an entry in map -> helps debugging
        }

        for (unordered_map<string, unordered_set<string>>::iterator it = graph.begin(); it != graph.end(); it++) {
            string parentWord = it->first;
            if (wordMaxDepthMap[parentWord] == 0) {
                findLongestPathDfsRec(graph, wordMaxDepthMap, wordMaxDepthChildrenMap, parentWord);
            }
        }

        if (this->debug) {
            showWordMaxDepthMap(wordMaxDepthMap);
            showWordMaxDepthChildrenMap(wordMaxDepthChildrenMap);
        }

        return {wordMaxDepthMap, wordMaxDepthChildrenMap};
    }

    int findLongestPath(unordered_map<string, int>& wordMaxDepthMap) {
        int maxLen = 0;

        for (unordered_map<string, int>::iterator it = wordMaxDepthMap.begin(); it != wordMaxDepthMap.end(); it++) {
            maxLen = max(maxLen, it->second);
        }

        return maxLen;
    }

   public:
    int longestStrChain(vector<string>& wordVec) {
        int len = wordVec.size();
        if (len == 1) {
            return 1;
        }

        unordered_map<string, unordered_set<string>> graph = prepareAdjWordsGraph(wordVec);
        if (graph.empty()) {
            return 1;
        }

        pair<unordered_map<string, int>, unordered_map<string, unordered_set<string>>> result = findLongestPathDfs(wordVec, graph);
        unordered_map<string, int> wordMaxDepthMap = result.first;
        unordered_map<string, unordered_set<string>> wordMaxDepthChildrenMap = result.second;

        return findLongestPath(wordMaxDepthMap);
    }

    friend class SolutionTest;
};

class SolutionTest {
   public:
    void testPrepareAdjWordsGraph() {
        Solution soln = Solution();
        vector<string> wordVec;
        unordered_map<string, unordered_set<string>> graphOutExpected;
        unordered_map<string, unordered_set<string>> graphOutComputed;

        wordVec = {};
        graphOutExpected = {};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"a"};
        graphOutExpected = {};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"a", "bb"};
        graphOutExpected = {};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"a", "bb", "ab"};
        graphOutExpected = {
            {"ab", {"a"}}};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"bba", "a", "bab", "bb", "ab", "abb", "ba"};
        graphOutExpected = {
            {"ab", {"a"}},
            {"ba", {"a"}},
            {"bba", {"bb", "ba"}},
            {"bab", {"bb", "ba", "ab"}},
            {"abb", {"bb", "ab"}}};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"a", "b", "ba", "bca", "bda", "bdca"};
        graphOutExpected = {
            {"ba", {"a", "b"}},
            {"bca", {"ba"}},
            {"bda", {"ba"}},
            {"bdca", {"bca", "bda"}}};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
        graphOutExpected = {
            {"xbc", {"xb"}},
            {"cxbc", {"xbc"}},
            {"pcxbc", {"cxbc"}},
            {"pcxbcf", {"pcxbc"}}};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"mcq"};
        graphOutExpected = {};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"mc", "m", "cm", "cmsju", "mcq", "cms", "cjm", "cmsj"};
        graphOutExpected = {
            {"mc", {"m"}},
            {"cm", {"m"}},
            {"mcq", {"mc"}},
            {"cms", {"cm"}},
            {"cjm", {"cm"}},
            {"cmsj", {"cms"}},
            {"cmsju", {"cmsj"}}};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);

        wordVec = {"abcd", "dbqca"};
        graphOutExpected = {};
        graphOutComputed = soln.prepareAdjWordsGraph(wordVec);
        assert(graphOutExpected == graphOutComputed);
    }

    void testFindLongestathDfs() {
        Solution soln = Solution();
        vector<string> wordVec;
        unordered_map<string, unordered_set<string>> graph;
        pair<unordered_map<string, int>, unordered_map<string, unordered_set<string>>> outExpected;
        unordered_map<string, int> wordMaxDepthMapExpected;
        unordered_map<string, unordered_set<string>> wordMaxDepthChildrenMapExpected;
        pair<unordered_map<string, int>, unordered_map<string, unordered_set<string>>> outComputed;
        unordered_map<string, int> wordMaxDepthMapComputed;
        unordered_map<string, unordered_set<string>> wordMaxDepthChildrenMapComputed;

        wordVec = {"a", "b", "ba", "bca", "bda", "bdca"};
        graph = soln.prepareAdjWordsGraph(wordVec);
        wordMaxDepthMapExpected = {
            {"a", 1},
            {"b", 1},
            {"ba", 2},
            {"bca", 3},
            {"bda", 3},
            {"bdca", 4}};
        wordMaxDepthChildrenMapExpected = {
            {"a", {}},
            {"b", {}},
            {"ba", {"a", "b"}},
            {"bca", {"ba"}},
            {"bda", {"ba"}},
            {"bdca", {"bca", "bda"}}};
        outComputed = soln.findLongestPathDfs(wordVec, graph);
        wordMaxDepthMapComputed = outComputed.first;
        wordMaxDepthChildrenMapComputed = outComputed.second;
        assert(wordMaxDepthMapExpected == wordMaxDepthMapComputed);
        assert(wordMaxDepthChildrenMapExpected == wordMaxDepthChildrenMapComputed);

        wordVec = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
        graph = soln.prepareAdjWordsGraph(wordVec);
        wordMaxDepthMapExpected = {
            {"xb", 1},
            {"xbc", 2},
            {"cxbc", 3},
            {"pcxbc", 4},
            {"pcxbcf", 5}};
        wordMaxDepthChildrenMapExpected = {
            {"xb", {}},
            {"xbc", {"xb"}},
            {"cxbc", {"xbc"}},
            {"pcxbc", {"cxbc"}},
            {"pcxbcf", {"pcxbc"}}};
        outComputed = soln.findLongestPathDfs(wordVec, graph);
        wordMaxDepthMapComputed = outComputed.first;
        wordMaxDepthChildrenMapComputed = outComputed.second;
        assert(wordMaxDepthMapExpected == wordMaxDepthMapComputed);
        assert(wordMaxDepthChildrenMapExpected == wordMaxDepthChildrenMapComputed);

        wordVec = {"mcq"};
        graph = soln.prepareAdjWordsGraph(wordVec);
        wordMaxDepthMapExpected = {
            {"mcq", 1}};
        wordMaxDepthChildrenMapExpected = {
            {"mcq", {}}};
        outComputed = soln.findLongestPathDfs(wordVec, graph);
        wordMaxDepthMapComputed = outComputed.first;
        wordMaxDepthChildrenMapComputed = outComputed.second;
        soln.showWordMaxDepthMap(wordMaxDepthMapExpected);
        soln.showWordMaxDepthMap(wordMaxDepthMapComputed);
        assert(wordMaxDepthMapExpected == wordMaxDepthMapComputed);
        assert(wordMaxDepthChildrenMapExpected == wordMaxDepthChildrenMapComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testPrepareAdjWordsGraph();
    solnTest.testFindLongestathDfs();

    return 0;
}
