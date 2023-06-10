#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    pair<vector<int>, stack<TreeNode * > > traverseLevel(stack<TreeNode *> &stkCrrLvl, bool isEvenLevel) {
        stack<TreeNode *> stkNxtLvl;
        vector<int> vec;

        while (!stkCrrLvl.empty()) {
            TreeNode *node = stkCrrLvl.top();
            stkCrrLvl.pop();

            vec.push_back(node->val);

            if (isEvenLevel) {
                if (node->right != nullptr) {
                    stkNxtLvl.push(node->right);
                }
                if (node->left != nullptr) {
                    stkNxtLvl.push(node->left);
                }
            } else {
                if (node->left != nullptr) {
                    stkNxtLvl.push(node->left);
                }
                if (node->right != nullptr) {
                    stkNxtLvl.push(node->right);
                }
            }
        }

        return {vec, stkNxtLvl};
    }

public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        if (root == nullptr) {
            return {};
        }

        vector<vector<int> > zigzagLvlTrav;
        stack<TreeNode *> stk;

        stk.push(root);
        int lvl = 1;
        while (!stk.empty()) {
            bool isEvenLvl = (lvl % 2) == 0;

            pair<vector<int>, stack<TreeNode *> > lvlTravOut = traverseLevel(stk, isEvenLvl);
            if (lvlTravOut.first.empty()) {
                break;
            }

            zigzagLvlTrav.push_back(lvlTravOut.first);
            stk = lvlTravOut.second;

            lvl++;
        }

        return zigzagLvlTrav;
    }
};