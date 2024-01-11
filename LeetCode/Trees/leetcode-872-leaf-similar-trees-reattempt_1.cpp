// LeetCode-872: https://leetcode.com/problems/leaf-similar-trees

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

class Solution {
private:
    // LC runtime: 3 ms / 4 ms (fluctuating)
    inline void getLeaves(TreeNode* root, list<int>& leaves) {
        if (root == nullptr) {
            return;
        }

        if (root->left == nullptr && root->right == nullptr) {
            leaves.push_back(root->val);
            return;
        }

        getLeaves(root->left, leaves);
        getLeaves(root->right, leaves);
    }

public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        list<int> leaves1;
        getLeaves(root1, leaves1);

        list<int> leaves2;
        getLeaves(root2, leaves2);

        return leaves1 == leaves2;
    }
};
