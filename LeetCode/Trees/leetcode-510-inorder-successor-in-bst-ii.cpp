// LeetCode-510: https://leetcode.com/problems/inorder-successor-in-bst-ii/
// Companies: [Meta][Arista][Google]

#include <vector>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};


class Solution {
private:
    Node* getInOrderSuccessorFromRightSubtree(Node* root) {
        Node* inOrderSuccessor = root->right;

        while (inOrderSuccessor->left != nullptr) {
            inOrderSuccessor = inOrderSuccessor->left;
        }

        return inOrderSuccessor;
    }

    Node* inorderSuccessor(Node* root, bool shouldExploreRightSubtree) {
        if (root == nullptr) {
            // extra safety
            return nullptr;
        }

        if (shouldExploreRightSubtree && (root->right != nullptr)) {
            // trivial case: in-order successor is the left-most node in right-subtree
            return getInOrderSuccessorFromRightSubtree(root);
        }

        if (root->parent == nullptr) {
            // there's no in-order successor since this is the last node in in-order traversal
            return nullptr;
        }

        if (root->val < root->parent->val) {
            // since root lies in the left subtree of it's parent,
            // parent itself will be the in-order successor
            return root->parent;
        } else if (root->val == root->parent->val) {
            // not possible in a BST
            throw invalid_argument("Invalid BST: found duplicates");
        } else {
            // root lies in right subtree of it's parent
            return inorderSuccessor(root->parent, false);
        }
    }

public:
    Node* inorderSuccessor(Node* node) {
        return inorderSuccessor(node, true);
    }
};
