// main GeeksForGeeks article: https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree
// GeeksForGeeks judge: https://practice.geeksforgeeks.org/problems/inorder-successor-in-bst
// related GeeksForGeeks article: https://www.geeksforgeeks.org/inorder-succesor-node-binary-tree/
// identical to inorder-succesor-node-binary-tree with 2 minor modifications for optimization

#include <iostream>
#include <utility>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution{
private:
    inline bool hasLeftChild(Node* root) {
        return (root != nullptr) && (root->left != nullptr);
    }

    inline bool hasRightChild(Node* root) {
        return (root != nullptr) && (root->right != nullptr);
    }

    // return values {inOrderSuccessor, prevNode}
    pair <Node*, Node*> inOrderSuccessorRec(Node *root, Node *destNode, Node* prevNode) {
        if ((root == nullptr) || (destNode == nullptr)) {
            // reached dead end
            return {nullptr, prevNode};
        }

        // prevNode was the destination node, so current node would be inorder successor
        if ((prevNode == destNode) && !hasLeftChild(root)) {
            return {root, root};
        }

        if (hasLeftChild(root) && (destNode->data < root->data)) {
            pair <Node*, Node*> leftRes = inOrderSuccessorRec(root->left, destNode, prevNode);
            if (leftRes.first != nullptr) {
                // if result found in left subtree, return it
                return leftRes;
            }
            if (leftRes.second == destNode) {
                // if destination node was the last node of left subtree, then current node is the inorder successor
                return {root, root};
            }
        }

        if (hasRightChild(root) && (destNode->data >= root->data)) {
            // return result of right subtree
            return inOrderSuccessorRec(root->right, destNode, root);
        }

        // current subtree does NOT contain inorder successor
        return {nullptr, root};
    }

public:
    // returns the inorder successor of the Node x in BST (rooted at 'root')
    Node* inOrderSuccessor(Node *root, Node *x) {
        if ((root == nullptr) || (x == nullptr)) {
            return nullptr;
        }

        pair <Node*, Node*> res = inOrderSuccessorRec(root, x, nullptr);
        return res.first;
    }
};
