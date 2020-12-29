// LeetCode-1457: https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/
// LeetCode Dec 2020 challenge: https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/573/week-5-december-29th-december-31st/3585/
// GFG: https://www.geeksforgeeks.org/print-palindromic-paths-of-binary-tree/
// CodeForces: https://codeforces.com/problemset/problem/914/E

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

void showFreqMap(map<int, int> freqMap, string msg) {
    printf("\n%s, freqMap is:-\n", msg.c_str());
    for (map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
        printf("[%d] -> %d\n", (*i).first, (*i).second);
    }
}

class Solution {
   public:
    int findNumPseudoPalinPaths(TreeNode* root, int numEles, unordered_map<int, int>& freqMap, int numOddFreqs, bool debug) {
        if (root == nullptr) {
            // this is controversial / not clear
            // - ideally a root with some non-null child in itself gives a palindromic path of length 1
            // - but one of the test cases break at that
            // this is that case: [8,8,null,7,7,null,null,2,4,null,8,null,7,null,1]
            return ((numEles >= 2) && (numOddFreqs <= 1)) ? 1 : 0;
        } else {
            int crrVal = root->val;

            freqMap[crrVal]++;
            if ((freqMap[crrVal] % 2) == 1) {
                // a new odd freq element was found
                numOddFreqs++;

                if (debug) {
                    cout << "\n-------\n";
                    printf("at node %d (onwards), freq[%d] incremented to %d and numOddFreqs incremented to %d\n", crrVal, crrVal, freqMap[crrVal], numOddFreqs);
                }
            } else if (freqMap[crrVal] >= 2) {
                // an element previously having odd freq, now has even freq
                numOddFreqs--;

                if (debug) {
                    cout << "\n-------\n";
                    printf("at node %d (onwards), freq[%d] incremented to %d and numOddFreqs decremented to %d\n", crrVal, crrVal, freqMap[crrVal], numOddFreqs);
                }
            }

            int lRes = findNumPseudoPalinPaths(root->left, numEles + 1, freqMap, numOddFreqs, debug);
            int rRes = findNumPseudoPalinPaths(root->right, numEles + 1, freqMap, numOddFreqs, debug);

            freqMap[crrVal]--;

            if (debug) {
                cout << "\n-------\n";
                printf("at node %d (return), freq[%d] decremented to %d\n", crrVal, crrVal, freqMap[crrVal]);
                printf("at node %d (return), lRes = %d and rRes = %d\n", crrVal, lRes, rRes);
            }

            if (root->left == nullptr && root->right == nullptr) {
                // if we dont do this, psuedo-palin paths ending in leaf nodes
                // will get counted twice
                if (debug) {
                    printf("leaf node, returning lRes = %d\n", lRes);
                }

                return lRes;
            } else {
                if (debug) {
                    printf("non leaf node, returning lRes=%d + rRes=%d = %d\n", lRes, rRes, (lRes + rRes));
                }

                return lRes + rRes;
            }
        }
    }

    int pseudoPalindromicPaths(TreeNode* root) {
        unordered_map<int, int> freqMap;
        return findNumPseudoPalinPaths(root, 0, freqMap, 0, false);
    }

    friend class TestSolution;
};
