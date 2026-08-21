// LeetCode-1469: https://leetcode.com/problems/find-all-the-lonely-nodes/
// Premium
// Companies: ?

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
    void getLonelyNodesRec(TreeNode* root, vector<int>& lonelyNodes) {
        if (root == nullptr) {
            return;
        }

        bool hasLChild = root->left != nullptr;
        bool hasRChild = root->right != nullptr;

        if (hasLChild && hasRChild) {
            getLonelyNodesRec(root->left, lonelyNodes);
            getLonelyNodesRec(root->right, lonelyNodes);
        } else if (hasLChild) {
            lonelyNodes.push_back(root->left->val);
            getLonelyNodesRec(root->left, lonelyNodes);
        } else if (hasRChild) {
            lonelyNodes.push_back(root->right->val);
            getLonelyNodesRec(root->right, lonelyNodes);
        } else {
            // do nothing
        }
    }

public:
    vector<int> getLonelyNodes(TreeNode* root) {
        vector <int> lonelyNodes;
        getLonelyNodesRec(root, lonelyNodes);
        return lonelyNodes;
    }
};
