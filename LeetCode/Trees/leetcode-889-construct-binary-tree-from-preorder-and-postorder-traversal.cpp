// LeetCode-889: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/

#include <cstdio>
#include <iostream>
#include <unordered_set>
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

class Solution {
   private:
    TreeNode* createNode(int val) {
        TreeNode* newNode = new TreeNode;
        newNode->val = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // LC submission: speed 13 %tile, memory 5 %tile
    TreeNode* constructRec(
        vector<int>& pre,
        int preLo, int preHi,
        vector<int>& post,
        int postLo, int postHi) {
        int len = preHi - preLo + 1;
        // empty
        if (len <= 0) {
            return nullptr;
        }

        int rootVal = pre[preLo];
        TreeNode* root = createNode(rootVal);
        // just 1 node
        if (len == 1) {
            return root;
        }

        // find bounds of left / right subtree
        int preJ = preLo + 1;
        int postJ = postLo;
        unordered_set<int> preVals;
        unordered_set<int> postVals;
        unordered_set<int> mismatchVals;
        while (preVals.empty() || !mismatchVals.empty()) {
            int preVal = pre[preJ++];
            preVals.insert(preVal);

            int postVal = post[postJ++];
            postVals.insert(postVal);

            if (postVals.find(preVal) == postVals.end()) {
                mismatchVals.insert(preVal);
            } else {
                mismatchVals.erase(preVal);
            }

            if (preVals.find(postVal) == preVals.end()) {
                mismatchVals.insert(postVal);
            } else {
                mismatchVals.erase(postVal);
            }
        }

        // note that we aren't explicitly checking whether left or right subtrees are found to be empty
        // because that will be handled implicitly (when tree is empty, constructRec automatically returns nullptr)
        TreeNode* left = constructRec(
            pre,
            preLo + 1, preJ - 1,
            post,
            postLo, postJ - 1);
        TreeNode* right = constructRec(
            pre,
            preJ, preHi,
            post,
            postJ, postHi - 1);

        root->left = left;
        root->right = right;

        return root;
    }

   public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        return constructRec(
            pre,
            0, pre.size() - 1,
            post,
            0, post.size() - 1);
    }
};
