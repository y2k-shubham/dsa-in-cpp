// LeetCode-919: https://leetcode.com/problems/complete-binary-tree-inserter/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class CBTInserter {
   private:
    int crrPos;
    TreeNode* root;

    list<char> buildPath(int pos) {
        list<char> path;

        while (pos > 1) {
            if ((pos % 2) == 0) {
                path.push_front('L');
            } else {
                path.push_front('R');
            }

            pos /= 2;
        }

        return path;
    }

    TreeNode* createNode(int val) {
        TreeNode* node = new TreeNode;
        node->val = val;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    int findHeightCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + findHeightCompleteTree(root->left);
    }

    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + countNodes(root->left) + countNodes(root->right);
    }

   public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        this->crrPos = countNodes(root) + 1;
    }

    int insert(int val) {
        TreeNode* newNode = createNode(val);

        if (this->root == nullptr) {
            this->root = newNode;
            return -1;
        }

        list<char> path = buildPath(this->crrPos);
        TreeNode* node = this->root;

        for (list<char>::iterator it = path.begin(); next(it, 1) != path.end(); it++) {
            if (*it == 'L') {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        if ((this->crrPos % 2) == 0) {
            node->left = newNode;
        } else {
            node->right = newNode;
        }

        this->crrPos++;

        return node->val;
    }

    TreeNode* get_root() {
        return this->root;
    }
};

/**
Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
