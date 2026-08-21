// LeetCode-250: https://leetcode.com/problems/count-univalue-subtrees/
// Premium
// Companies: [Google][Amazon][6sense][Zeta Global]

#include <utility>

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
    pair <int, bool> countUnivalSubtreesRec(TreeNode* root) {
        if (root == nullptr) {
            return {0, true};
        }

        bool hasLChild = root->left != nullptr;
        bool hasRChild = root->right != nullptr;

        pair <int, bool> lResult = countUnivalSubtreesRec(root->left);
        pair <int, bool> rResult = countUnivalSubtreesRec(root->right);

        int numUnivalSubtreesRootedAtCrrNode = lResult.first + rResult.first;

        bool isUnivalWithLSubtree = !hasLChild || ((lResult.second == true) && (root->val == root->left->val));
        bool isUnivalWithRSubtree = !hasRChild || ((rResult.second == true) && (root->val == root->right->val));

        bool isSubtreeRootedAtCrrNodeAUnivalSubtree = isUnivalWithLSubtree && isUnivalWithRSubtree;
        if (isSubtreeRootedAtCrrNodeAUnivalSubtree) {
            numUnivalSubtreesRootedAtCrrNode++;
        }

        return {numUnivalSubtreesRootedAtCrrNode, isSubtreeRootedAtCrrNodeAUnivalSubtree};
    }

public:
    int countUnivalSubtrees(TreeNode* root) {
        pair <int, bool> result = countUnivalSubtreesRec(root);
        return result.first;
    }
};
