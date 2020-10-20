// LeetCode-652: https://leetcode.com/problems/find-duplicate-subtrees/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
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

string buildStrReprMap(TreeNode* root, map<string, vector<TreeNode*> >& strReprMap) {
    if (root == nullptr) {
        return "";
    } else {
        string repr = "(" + buildStrReprMap(root->left, strReprMap) + ")" + to_string(root->val) + buildStrReprMap(root->right, strReprMap) + ")";
        strReprMap[repr].push_back(root);
        return repr;
    }
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    map<string, vector<TreeNode*> > strReprMap;
    buildStrReprMap(root, strReprMap);

    vector<TreeNode*> duplicateSubtreeRoots;
    for (map<string, vector<TreeNode*> >::iterator i = strReprMap.begin(); i != strReprMap.end(); i++) {
        if ((*i).second.size() > 1) {
            duplicateSubtreeRoots.push_back((*i).second[0]);
        }
    }

    return duplicateSubtreeRoots;
}
