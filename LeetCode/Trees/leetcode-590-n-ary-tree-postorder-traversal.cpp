// LeetCode-590: https://leetcode.com/problems/n-ary-tree-postorder-traversal/
// implemented using stack (instead of recursion)

#include <stack>
#include <vector>
#include <utility>

using namespace std;

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
private:
    void pushNodeToStk(Node *node, stack<pair<Node *, int> > &stk) {
        if (node == nullptr) {
            return;
        }

        pushNodeToStk({node, 0}, stk);
    }

    void pushNodeToStk(
            pair<Node *, int> p,
            stack<pair<Node *, int> > &stk
    ) {
        if (p.first == nullptr) {
            return;
        }

        stk.push({p.first, p.second + 1});
    }

public:
    vector<int> postorder(Node *root) {
        vector<int> postOrderTrav;

        stack<pair<Node *, int> > stk;
        pushNodeToStk(root, stk);
        // printf("after pushing, stk is empty = %s\n", stk.empty() ? "true" : "false");

        while (!stk.empty()) {
            pair<Node *, int> p = stk.top();
            stk.pop();
            // printf("after popping %d (%d), stk is empty = %s\n", p.first->val, p.second, stk.empty() ? "true" : "false");

            if (p.second == 1) {
                pushNodeToStk(p, stk);

                int numChildren = p.first->children.size();
                // printf("numChildren = %d\n", numChildren);
                for (int i = numChildren - 1; i >= 0; i--) {
                    Node *childNode = p.first->children[i];
                    if (childNode != nullptr) {
                        pushNodeToStk(childNode, stk);
                    }
                }
            } else if (p.second == 2) {
                postOrderTrav.push_back(p.first->val);
            } else {
                // should never happen
            }
        }

        return postOrderTrav;
    }
};
