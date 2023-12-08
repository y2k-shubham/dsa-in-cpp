// LeetCode-606: https://leetcode.com/problems/construct-string-from-binary-tree/
// LC submission - [speed] 11ms, 82 %centile, [memory] 23.49MB, 98 %centile

#include <string>
#include <sstream>

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
    inline bool isLeafNode(TreeNode* root) {
        return (root->left == nullptr) && (root->right == nullptr);
    }

    inline void tree2strRec(TreeNode* root, ostringstream& oss) {
        if (root == nullptr) {
            return;
        }

        oss << root->val;

        if (isLeafNode(root)) {
            return;
        }

        oss << "(";
        if (root->left != nullptr) {
            tree2strRec(root->left, oss);
        }
        oss << ")";

        if (root->right != nullptr) {
            oss << "(";
            tree2strRec(root->right, oss);
            oss << ")";
        }
    }

public:
    string tree2str(TreeNode* root) {
        ostringstream oss;
        tree2strRec(root, oss);
        return oss.str();
    }
};
