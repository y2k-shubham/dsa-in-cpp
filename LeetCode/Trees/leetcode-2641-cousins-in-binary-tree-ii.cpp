// LeetCode-2641: https://leetcode.com/problems/cousins-in-binary-tree-ii/

#include <iostream>
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
    void calcLevelSums(TreeNode* root, int level, vector<int>& levelSums) {
        if (root == nullptr) {
            return;
        }

        if (level >= levelSums.size()) {
            levelSums.push_back(root->val);
        } else {
            levelSums[level] += root->val;
        }

        calcLevelSums(root->left, level + 1, levelSums);
        calcLevelSums(root->right, level + 1, levelSums);
    }

    void printLevelSums(vector<int>& levelSums) {
        cout << "ind:\t";
        for (int i = 0; i < levelSums.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("val:\t");
        for (int i = 0; i < levelSums.size(); i++) {
            cout << levelSums[i] << "\t";
        }
        cout << endl;
    }

    void replaceVals(TreeNode* root, int level, vector<int>& levelSums) {
        if (root == nullptr) {
            return;
        }

        replaceVals(root->left, level + 1, levelSums);
        replaceVals(root->right, level + 1, levelSums);

        bool hasLeftChild = root->left != nullptr;
        int leftChildVal = hasLeftChild ? root->left->val : 0;

        bool hasRightChild = root->right != nullptr;
        int rightChildVal = hasRightChild ? root->right->val : 0;

        int childrenSum = leftChildVal + rightChildVal;

        if (hasLeftChild) {
            root->left->val = levelSums[level + 1] - childrenSum;
        }
        if (hasRightChild) {
            root->right->val = levelSums[level + 1] - childrenSum;
        }
    }

public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        vector<int> levelSums;
        calcLevelSums(root, 0, levelSums);
//        printLevelSums(levelSums);

        replaceVals(root, 0, levelSums);
        root->val = 0;

        return root;
    }
};
