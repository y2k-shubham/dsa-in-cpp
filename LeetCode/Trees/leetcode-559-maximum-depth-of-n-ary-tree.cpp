// LeetCode-559: https://leetcode.com/problems/maximum-depth-of-n-ary-tree/

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
private:
    inline bool isNull(Node* root) {
        return root == nullptr;
    }

    inline bool isLeaf(Node* root) {
        return root->children.empty();
    }

public:
    int maxDepth(Node* root) {
        if (isNull(root)) {
            return 0;
        }
        if (isLeaf(root)) {
            return 1;
        }

        int maxChildrenDepth = 0;
        for (vector<Node*>::iterator it = root->children.begin(); it != root->children.end(); it++) {
            Node* child = *it;
            maxChildrenDepth = max(maxChildrenDepth, maxDepth(child));
        }

        return 1 + maxChildrenDepth;
    }
};

int main() {
    return 0;
}
