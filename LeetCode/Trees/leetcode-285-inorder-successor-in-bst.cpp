// LeetCode-285: https://leetcode.com/problems/inorder-successor-in-bst/
// Companies: [Google][Docusign][Meta][Microsoft][Amazon][Pocket Gems]

// certainly harder than medium

// optimizations (1 & 2) [search 'optimization' in comments] :
// just those 2nd expressions use BST sorted-order property and improves submission speed %-tile from 19% to 80%

#include <utility>
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
    // return {lastAccessedNode, inOrderSuccessor}
    // lastAccessedNode -> last node accessed as per in-order traversal
    // inOrderSuccessor -> the actual answer (if already found in this subtree)
    pair <TreeNode*, TreeNode*> inOrderSuccessorRec(TreeNode* targetNode, TreeNode* crrNode, TreeNode* prevNode) {
        if (crrNode == nullptr) {
            // printf("crrNode=null, reached dead end\n");
            // dead end
            return {nullptr, nullptr};
        }

        // in-order traversal: first go left if left-subtree is non-empty
        // optimization-1
        if ((crrNode->left != nullptr) && (targetNode->val <= crrNode->val)) {
            pair <TreeNode*, TreeNode*> lRes = inOrderSuccessorRec(targetNode, crrNode->left, prevNode);

            if (lRes.second != nullptr) {
                // result (actual in-order successor) already found in left subtree
                // printf("at crrNode=%d, got result=%d from left subtree\n", crrNode->val, lRes.second->val);
                return lRes;
            }

            if (lRes.first == targetNode) {
                // last accessed node from left subtree was targetNode, so the current node is the in-order successor
                // printf("at crrNode=%d, found last accessed node=%d=targetNode from left subtree, so crrNode is the inOrder successor\n", crrNode->val, lRes.first->val);
                return {crrNode, crrNode};
            }
        }

        // in-order traversal: then try current node
        if (prevNode == targetNode) {
            return {crrNode, crrNode};
        }

        // in-order traversal: finally go right if right-subtree is non-empty
        if ((crrNode->right != nullptr) && (targetNode->val >= crrNode->val)) {
            // printf("at crrNode=%d, returning result from right subtree\n", crrNode->val);
            return inOrderSuccessorRec(targetNode, crrNode->right, crrNode);
        }

        // but if right subtree was empty, then the returned result will be based on current node only
        return {crrNode, nullptr};
    }

public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if ((root == nullptr) || (p == nullptr)) {
            return nullptr;
        }

        pair <TreeNode*, TreeNode*> result = inOrderSuccessorRec(p, root, nullptr);
        return result.second;
    }
};
