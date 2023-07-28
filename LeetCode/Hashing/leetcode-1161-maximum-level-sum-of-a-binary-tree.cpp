// LeetCode-1161: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

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
    void calcLevelSums(TreeNode *root, int level, vector<pair<int, int> > &levelSums) {
        if (root == nullptr) {
            return;
        }

        if (level > levelSums.size()) {
            levelSums.push_back({root->val, -level});
        } else {
            levelSums[level - 1].first += root->val;
        }

        calcLevelSums(root->left, level + 1, levelSums);
        calcLevelSums(root->right, level + 1, levelSums);
    }

    void showVec(vector<pair<int, int> > &levelSums, const char *when) {
        printf("%s levelSums vector is:-\n", when);

        printf("Ind:\t");
        for (int i = 0; i < levelSums.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Level:\t");
        for (int i = 0; i < levelSums.size(); i++) {
            printf("%d\t", -levelSums[i].second);
        }
        cout << endl;

        printf("Sum:\t");
        for (int i = 0; i < levelSums.size(); i++) {
            printf("%d\t", levelSums[i].first);
        }
        cout << endl;
    }

public:
    int maxLevelSum(TreeNode *root) {
        vector<pair<int, int> > levelSums;
        calcLevelSums(root, 1, levelSums);
        // showVec(levelSums, "before sorting");

        sort(levelSums.begin(), levelSums.end(), greater<>());
        // showVec(levelSums, "after sorting");

        return -levelSums[0].second;
    }
};
