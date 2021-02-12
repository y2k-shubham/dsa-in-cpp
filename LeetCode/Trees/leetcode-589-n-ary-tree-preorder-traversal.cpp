// LeetCode-429: https://leetcode.com/problems/n-ary-tree-level-order-traversal/

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
   public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
   public:
    void preOrderRec(Node* root, vector<int>& preOrder) {
        if (root != nullptr) {
            preOrder.push_back(root->val);

            vector<Node*> children = root->children;
            for (int i = 0; i < children.size(); i++) {
                preOrderRec(children[i], preOrder);
            }
        }
    }

    vector<int> preorder(Node* root) {
        vector<int> preOrder;
        preOrderRec(root, preOrder);

        return preOrder;
    }
};
