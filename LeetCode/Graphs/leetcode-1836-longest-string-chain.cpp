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

#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_set<string> prepareWordSet(vector<string>& wordVec) {
        unordered_set<string> wordSet(wordVec.begin(), wordVec.end());
        return wordSet;
    }

    unordered_map<string, unordered_set<string> > prepareAdjWordsGraph(vector<string>& wordVec) {
        unordered_set<string> wordSet = prepareWordSet(wordVec);
        unordered_map<string, unordered_set<string> > graph;

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

    int findLongestPathDfsRec(
        unordered_map<string, unordered_set<string> >& graph,
        unordered_map<string, int>& wordMaxDepthMap,
        string crrWord) {
        int maxChildDepth = 0;

        unordered_set<string> children = graph[crrWord];
        if (!children.empty()) {
            for (unordered_set<string>::iterator it = children.begin(); it != children.end(); it++) {
                maxChildDepth = max(maxChildDepth, findLongestPathDfsRec(graph, wordMaxDepthMap, *it));
            }
        }

        int crrWordDepth = maxChildDepth + 1;
        wordMaxDepthMap[crrWord] = crrWordDepth;

        return crrWordDepth;
    }

    unordered_map<string, int> findLongestPathDfs(
        vector<string>& wordVec,
        unordered_map<string, unordered_set<string> >& graph) {
        unordered_map<string, int> wordMaxDepthMap;
        for (int i = 0; i < wordVec.size(); i++) {
            wordMaxDepthMap[wordVec[i]] = 0;
        }

        for (unordered_map<string, unordered_set<string> >::iterator it = graph.begin(); it != graph.end(); it++) {
            string parentWord = it->first;
            if (wordMaxDepthMap[parentWord] == 0) {
                findLongestPathDfsRec(graph, wordMaxDepthMap, parentWord);
            }
        }

        return wordMaxDepthMap;
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

        unordered_map<string, unordered_set<string> > graph = prepareAdjWordsGraph(wordVec);
        if (graph.empty()) {
            return 1;
        }

        unordered_map<string, int> wordMaxDepthMap = findLongestPathDfs(wordVec, graph);
        return findLongestPath(wordMaxDepthMap);
    }
};
