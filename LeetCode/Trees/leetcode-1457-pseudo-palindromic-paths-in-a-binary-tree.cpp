// LeetCode-1457: https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/
// GFG: https://www.geeksforgeeks.org/print-palindromic-paths-of-binary-tree/
// CodeForces: https://codeforces.com/problemset/problem/914/E

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
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

void showSet(set<int> oddFreqEles, string msg) {
    printf("\n%s, oddFreqEles is:-\n", msg.c_str());
    for (set<int>::iterator i = oddFreqEles.begin(); i != oddFreqEles.end(); i++) {
        printf("%d\t", *i);
    }
    cout << endl;
}

int countPseudoPalinPaths(TreeNode* root, map<int, int>& freqMap, set<int>& oddFreqEles) {
    if (root == nullptr) {
        return 0;
    } else {
        int crrVal = root->val;

        // do note that freq increment has to be done for leaf nodes also (easy to overlook)
        freqMap[crrVal] = freqMap[crrVal] + 1;
        bool isOddFreq = (freqMap[crrVal] % 2) == 1;
        if (isOddFreq) {
            oddFreqEles.insert(crrVal);
        } else {
            // this else clause is important (and easy to miss)
            oddFreqEles.erase(crrVal);
        }

        int res = 0;
        if (root->left == nullptr && root->right == nullptr) {
            ostringstream oss;
            oss << "at leaf node " << root->val;
            // showFreqMap(freqMap, oss.str());
            // showSet(oddFreqEles, oss.str());

            if (oddFreqEles.size() <= 1) {
                // cout << "counting 1 psuedo palin" << endl;
                res = 1;
            } else {
                res = 0;
            }
        } else {
            int lRes = countPseudoPalinPaths(root->left, freqMap, oddFreqEles);
            int rRes = countPseudoPalinPaths(root->right, freqMap, oddFreqEles);
            res = lRes + rRes;
        }

        freqMap[crrVal]--;
        if (isOddFreq) {
            oddFreqEles.erase(crrVal);
        } else {
            // this else clause is important (and easy to miss)
            oddFreqEles.insert(crrVal);
        }

        return res;
    }
}

int pseudoPalindromicPaths(TreeNode* root) {
    map<int, int> freqMap;
    set<int> oddFreqEles;

    return countPseudoPalinPaths(root, freqMap, oddFreqEles);
}
