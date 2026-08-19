// LeetCode-2476: https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/
// Incomplete

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>

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
    void serializeTree(TreeNode* root, vector <int>& vec) {
        if (root->left != nullptr) {
            serializeTree(root->left, vec);
        }

        vec.push_back(root->val);

        if (root->right != nullptr) {
            serializeTree(root->right, vec);
        }
    }

    vector <pair <int, int> > convertToQueryIdxVec(vector<int>& queries) {
        int len = queries.size();
        vector <pair <int, int> > queryIdxVec(len);

        for (int i = 0; i < len; i++) {
            queryIdxVec[i] = {queries[i], i};
        }

        // Sort by first element ascending (provided by Microsoft Copilot)
        sort(queryIdxVec.begin(), queryIdxVec.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.first < b.first;
        });

        return queryIdxVec;
    }

    vector <pair <pair <int, int>, int> > createClosestNodesForQueriesVec(
        vector <int>& bstVec,
        vector <pair <int, int> >& queryIdxVec) {
        int bstVecLen = bstVec.size();
        int queryVecLen = queryIdxVec.size();
        vector <pair <pair <int, int>, int> > closestNodesForQueriesVec(queryVecLen);

        for (int i = 0, j = 0; (i < bstVecLen) && (j < queryVecLen); ) {
            int bstVal = bstVec[i];
            int queryVal = queryIdxVec[j].first;

            if (bstVal < queryVal) {

            } else if (bstVal > queryVal) {

            } else {

            }
        }
    }

public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {

    }
};
