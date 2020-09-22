// LeetCode-501: https://leetcode.com/problems/find-mode-in-binary-search-tree/

#include <vector>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

void findMode(pair<int, vector<int> >& crrModes, TreeNode* root, pair<int, int>& crrEleFreq) {
    if (root != nullptr) {
        findMode(crrModes, root->left, crrEleFreq);

        if (root->val == crrEleFreq.second) {
            crrEleFreq.first++;
        } else {
            crrEleFreq.first = 1;
            crrEleFreq.second = root->val;
        }

        if (crrModes.first == crrEleFreq.first) {
            crrModes.second.push_back(crrEleFreq.second);
        } else if (crrEleFreq.first > crrModes.first) {
            crrModes.first = crrEleFreq.first;
            crrModes.second = {crrEleFreq.second};
        }

        findMode(crrModes, root->right, crrEleFreq);
    }
}

vector<int> findMode(TreeNode* root) {
    pair<int, vector<int> > crrModes = {0, {}};
    pair<int, int> crrEleFreq = {0, -1};

    findMode(crrModes, root, crrEleFreq);

    return crrModes.second;
}
