// LeetCode-107: https://leetcode.com/problems/binary-tree-level-order-traversal-ii

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    vector <vector <int>> buildLvlOrderTraversal(TreeNode* root) {
        vector <vector <int>> lvlOrder;
        queue <TreeNode*> que;

        que.push(root);
        while (!que.empty()) {
            vector <int> crrLvl;
            int len = que.size();

            for (int i = 1; i <= len; i++) {
                TreeNode* crrNode = que.front();
                que.pop();

                crrLvl.push_back(crrNode->val);
                if (crrNode->left != nullptr) {
                    que.push(crrNode->left);
                }
                if (crrNode->right != nullptr) {
                    que.push(crrNode->right);
                }
            }

            lvlOrder.push_back(crrLvl);
        }

        return lvlOrder;
    }

public:
    vector <vector <int>> levelOrderBottom(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        vector <vector <int>> lvlOrder = buildLvlOrderTraversal(root);
        reverse(lvlOrder.begin(), lvlOrder.end());

        return lvlOrder;
    }
};
