#include <cstdio>
#include <iostream>

using namespace std;

class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
   private:
    Node* findLeftMostChildNode(Node* node) {
        while ((node != nullptr) && (node->left == nullptr) && (node->right == nullptr)) {
            node = node->next;
        }

        if (node == nullptr) {
            return nullptr;
        }

        if (node->left != nullptr) {
            return node->left;
        } else if (node->right != nullptr) {
            return node->right;
        } else {
            return nullptr;
        }
    }

    // LC-submission: speed: 25 %tile
    void revPostOrderConnect(Node* root) {
        if (root == nullptr) {
            return;
        }
        if ((root->left == nullptr) && (root->right == nullptr)) {
            return;
        }

        // determine left most node in next level,
        // which is first non-null child of any node to right of root
        Node* leftMostChildNode = findLeftMostChildNode(root->next);

        // populate next ptr of root's right child (only child node, not entire subtree)
        if (root->right != nullptr) {
            root->right->next = leftMostChildNode;
        }

        // populate next ptr of root's left child (only child node, not entire subtree)
        if (root->left != nullptr) {
            root->left->next = (root->right != nullptr) ? root->right : leftMostChildNode;
        }

        // recurse for right subtree
        revPostOrderConnect(root->right);

        // recurse for left subtree
        revPostOrderConnect(root->left);
    }

   public:
    Node* connect(Node* root) {
        // map <int, Node*> lvlNodeMap;
        // inOrderConnect(root, lvlNodeMap, 0);

        revPostOrderConnect(root);

        return root;
    }
};
