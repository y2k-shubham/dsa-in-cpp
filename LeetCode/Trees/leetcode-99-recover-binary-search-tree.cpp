// LeetCode-99: https://leetcode.com/problems/recover-binary-search-tree/
// https://www.youtube.com/watch?v=LR3K5XAWV5k
//  - the folowing implemenation is O(n) space approach
//  - it can be minimized to O(logn) using pointers / references to keep track of last node seen in inOrder
//    traversal
//  - true constant space approach requires Morris InOrder traversal

#include <climits>
#include <cstdio>
#include <iostream>
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

void inOrderRec(TreeNode* root, vector<int>& vec);
vector<int> inOrder(TreeNode* root);
pair<int, int> findSwappedEles(vector<int> inOrderTravVec);
void recoverTreeRec1(TreeNode* root, pair<int, int> swappedEles);
void recoverTree1(TreeNode* root);
void recoverTree(TreeNode* root);

int main() {
    return 0;
}

void inOrderRec(TreeNode* root, vector<int>& vec) {
    if (root != nullptr) {
        inOrderRec(root->left, vec);
        vec.push_back(root->val);
        inOrderRec(root->right, vec);
    }
}

vector<int> inOrder(TreeNode* root) {
    vector<int> inOrderTravVec;
    inOrderRec(root, inOrderTravVec);
    return inOrderTravVec;
}

pair<int, int> findSwappedEles(vector<int> inOrderTravVec) {
    pair<int, int> swappedEles = {INT_MAX, INT_MIN};

    int len = inOrderTravVec.size();
    int numRevPairs = 0;

    for (int i = 1; i < len; i++) {
        if (inOrderTravVec[i - 1] > inOrderTravVec[i]) {
            numRevPairs++;
            if (numRevPairs == 1) {
                swappedEles.first = inOrderTravVec[i - 1];
            }
            swappedEles.second = inOrderTravVec[i];
        }
    }

    return swappedEles;
}

void recoverTreeRec1(TreeNode* root, pair<int, int> swappedEles) {
    if (root != nullptr) {
        recoverTreeRec1(root->left, swappedEles);

        if (root->val == swappedEles.first) {
            root->val = swappedEles.second;
        } else if (root->val == swappedEles.second) {
            root->val = swappedEles.first;
        }

        recoverTreeRec1(root->right, swappedEles);
    }
}

// LC submission: speed: 54 %centile, memory: 5 %centile
void recoverTree1(TreeNode* root) {
    if (root != nullptr) {
        vector<int> inOrderTravVec = inOrder(root);
        pair<int, int> swappedEles = findSwappedEles(inOrderTravVec);
        recoverTreeRec1(root, swappedEles);
    }
}

void recoverTree(TreeNode* root) {
    recoverTree1(root);
}
