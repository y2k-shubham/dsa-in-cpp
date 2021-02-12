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
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) {
            return {};
        }

        queue<Node*> que;
        vector<vector<int>> lvlOrder;

        que.push(root);
        while (!que.empty()) {
            int len = que.size();

            vector<int> lvl;
            for (int i = 1; i <= len; i++) {
                Node* node = que.front();
                que.pop();

                lvl.push_back(node->val);

                vector<Node*> children = node->children;
                for (int i = 0; i < children.size(); i++) {
                    que.push(children[i]);
                }
            }

            lvlOrder.push_back(lvl);
        }

        return lvlOrder;
    }
};
