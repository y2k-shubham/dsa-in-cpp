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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    /**
     * IMPORTANT: Since function is void, crrEleFreq has to be a reference
     * @param maxFreqEles {crrMaxFreq, {crr max freq values}}
     * @param root
     * @param crrEleFreq {crrEleFreq, crrEleVal}
     */
    void findModeRec1(pair<int, vector<int> >& maxFreqEles, TreeNode* root, pair<int, int>& crrEleFreq) {
        if (root == nullptr) {
            return;
        }

        // explore left subtree
        if (root->left != nullptr) {
            findModeRec1(maxFreqEles, root->left, crrEleFreq);
        }

        if (root->val == crrEleFreq.second) {
            // if root equals current element, increase the frequency of current element
            crrEleFreq.first++;
        } else {
            // else set root as current element
            crrEleFreq = {1, root->val};
        }

        if ((crrEleFreq.first == maxFreqEles.first) && (!maxFreqEles.second.empty() && (*maxFreqEles.second.rbegin() != root->val))) {
            // if current element's frequency has become equal to max frequency seen so far
            // then add current element into set of max frequency elements
            // (only if current element has not already been added in set -> although even without this condition
            // we get correct answer since this condition is implicitly satisfied for a BST)
            maxFreqEles.second.push_back(root->val);
        } else if (crrEleFreq.first > maxFreqEles.first) {
            // if current element's frequency has exceeded max frequency seen so far
            // then update the max frequency elements set
            maxFreqEles = {crrEleFreq.first, {root->val}};
        }

        // explore right subtree
        if (root->right != nullptr) {
            findModeRec1(maxFreqEles, root->right, crrEleFreq);
        }
    }

    /**
     * @param maxFreqEles {crrMaxFreq, {crr max freq values}}
     * @param root
     * @param crrEleFreq {crrEleFreq, crrEleVal}
     */
    pair<int, int> findModeRec2(pair<int, vector<int> >& maxFreqEles, TreeNode* root, pair<int, int> crrEleFreq) {
        if (root == nullptr) {
            return crrEleFreq;
        }

        // explore left subtree
        if (root->left != nullptr) {
            crrEleFreq = findModeRec2(maxFreqEles, root->left, crrEleFreq);
        }

        if (root->val == crrEleFreq.second) {
            // if root equals current element, increase the frequency of current element
            crrEleFreq.first++;
        } else {
            // else set root as current element
            crrEleFreq = {1, root->val};
        }

        if ((crrEleFreq.first == maxFreqEles.first) && (!maxFreqEles.second.empty() && (*maxFreqEles.second.rbegin() != root->val))) {
            // if current element's frequency has become equal to max frequency seen so far
            // then add current element into set of max frequency elements
            // (only if current element has not already been added in set -> although even without this condition
            // we get correct answer since this condition is implicitly satisfied for a BST)
            maxFreqEles.second.push_back(root->val);
        } else if (crrEleFreq.first > maxFreqEles.first) {
            // if current element's frequency has exceeded max frequency seen so far
            // then update the max frequency elements set
            maxFreqEles = {crrEleFreq.first, {root->val}};
        }

        // explore right subtree
        if (root->right != nullptr) {
            return findModeRec2(maxFreqEles, root->right, crrEleFreq);
        } else {
            return crrEleFreq;
        }
    }

public:
    vector<int> findMode(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        pair<int, int> crrEleFreq = {INT_MIN, INT_MAX};
        pair<int, vector<int> > maxFreqEles = {INT_MIN, {}};
//        findModeRec1(maxFreqEles, root, crrEleFreq);
        findModeRec2(maxFreqEles, root, crrEleFreq);

        return maxFreqEles.second;
    }
};
