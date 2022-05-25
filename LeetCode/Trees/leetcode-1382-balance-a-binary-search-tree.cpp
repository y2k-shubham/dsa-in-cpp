// LeetCode-1382: https://leetcode.com/problems/balance-a-binary-search-tree/

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

    TreeNode* insertNode(TreeNode* root, TreeNode* newNode) {
        if (root == nullptr) {
            return newNode;
        }

        if (newNode->val < root->val) {
            root->left = insertNode(root->left, newNode);
        } else if (newNode->val > root->val) {
            root->right = insertNode(root->right, newNode);
        }

        return root;
    }

    void buildInOrderVec(TreeNode* root, vector<int>& inOrder) {
        if (root == nullptr) {
            return;
        }

        buildInOrderVec(root->left, inOrder);
        inOrder.push_back(root->val);
        buildInOrderVec(root->right, inOrder);
    }

    TreeNode* buildBalancedBSTRec(
            vector<int>& inOrder,
            int lo,
            int hi
    ) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return nullptr;
        }

        int mid = (lo + hi) / 2;

        TreeNode* root = createNode(inOrder[mid]);
        root->left = buildBalancedBSTRec(inOrder, lo, mid - 1);
        root->right = buildBalancedBSTRec(inOrder, mid + 1, hi);

        return root;
    }

public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> inOrder;
        buildInOrderVec(root, inOrder);

        int len = inOrder.size();
        return buildBalancedBSTRec(inOrder, 0, len - 1);
    }
};
