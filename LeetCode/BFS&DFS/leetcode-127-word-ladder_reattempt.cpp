// LeetCode-127: https://leetcode.com/problems/word-ladder/
// LC Jan 2020 challenge: https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/580/week-2-january-8th-january-14th/3598/
// smart, simple soln: https://www.youtube.com/watch?v=O3hUyXyHeBw

// this simplified / basic soln is ~ 8x faster
// than the (arguably) more advanced soln submitted in previous attempt

#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool debug = false;

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (beginWord == endWord) {
            return 0;
        }

        // convert list of words into set to be able to quickly check
        // if a given word belongs to our corpus (list) of words
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // create a set to hold all words already seen (for BFS)
        unordered_set<string> visitedWords;
        visitedWords.insert(beginWord);
        // create a que for BFS
        queue<string> que;
        que.push(beginWord);

        int numSteps = 0;
        while (!que.empty()) {
            // this will be incremented in every 'cycle' of BFS
            // (when we exhaust all possibilities on a given level and move to next level)
            numSteps++;

            // this iteration will run until all items in current level
            // (which is numerically equal to que-length before the loop) are exhausted
            int numWordsCrrLvl = que.size();

            if (debug) {
                printf("\n============\n");
                printf("numSteps = %d, numWordsCrrLvl = %d\n", numSteps, numWordsCrrLvl);
            }
            for (int i = 1; i <= numWordsCrrLvl; i++) {
                // take an item from que
                string crrWord = que.front();
                que.pop();

                if (debug) {
                    printf("\n------------\n");
                    printf("crrWord = %s\n\n", crrWord.c_str());
                }

                for (int j = 0; j < crrWord.size(); j++) {
                    // take a char of word
                    char crrChar = crrWord.at(j);

                    for (char newChar = 'a'; newChar <= 'z'; newChar++) {
                        // try replacing it with every other possible char
                        if (crrChar != newChar) {
                            // changing single character of std string
                            // reference: https://stackoverflow.com/q/18305844/3679900
                            string newWord = crrWord;
                            newWord[j] = newChar;

                            if ((wordSet.find(newWord) != wordSet.end()) && (visitedWords.find(newWord) == visitedWords.end())) {
                                if (newWord == endWord) {
                                    if (debug) {
                                        printf("\nin crrWord = '%s', replacing crrWord[j=%d] = '%c' with '%c' to get newWord = '%s'\n", crrWord.c_str(), j, crrChar, newChar, newWord.c_str());
                                        printf("found answer!\n");
                                    }
                                    // if we reached the target word,
                                    // return no of steps (no of levels / depth of BFS)
                                    // {note that value is incremented by 1 on return because
                                    // we have to return no of words (nodes) rather than no of
                                    // transformations (edges)}
                                    return (numSteps + 1);
                                }

                                if (debug) {
                                    printf("\nin crrWord = '%s', replacing crrWord[j=%d] = '%c' with '%c' to get newWord = '%s'\n", crrWord.c_str(), j, crrChar, newChar, newWord.c_str());
                                    printf("pushing newWord = '%s' into que\n", newWord.c_str());
                                }
                                // otherwise if (1) newWord belongs to corpus & (2) it is still
                                // unvisited, then (a) push it to que and (b) mark it visited
                                que.push(newWord);
                                visitedWords.insert(newWord);
                            }
                        }
                    }
                }
            }
        }

        // BFS completed without reaching target word,
        // means no possible solution -> return 0
        return 0;
    }
};