// LeetCode-1315: https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
   private:
    void showQue(queue<TreeNode *> ancestors) {
        printf("Que is:-\n");
        while (!ancestors.empty()) {
            printf("%d ", ancestors.front()->val);
            ancestors.pop();
        }
        cout << endl;
    }

   public:
    int sumEvenGrandParent(TreeNode *root, queue<TreeNode *> ancestors, bool debug) {
        if (root == nullptr) {
            return 0;
        } else {
            if (debug) {
                printf("\nat node %d\n", root->val);
                showQue(ancestors);
            }

            int crrSum = 0;
            if ((ancestors.size() == 2)) {
                if ((ancestors.front()->val % 2 == 0)) {
                    crrSum = root->val;
                    if (debug) {
                        printf("crrSum = %d\n", crrSum);
                    }
                }
                ancestors.pop();
            }

            ancestors.push(root);

            return crrSum + sumEvenGrandParent(root->left, ancestors, debug) + sumEvenGrandParent(root->right, ancestors, debug);
        }
    }

    int sumEvenGrandparent(TreeNode *root) {
        queue<TreeNode *> ancestors;

        return sumEvenGrandParent(root, ancestors, false);
    }
};
