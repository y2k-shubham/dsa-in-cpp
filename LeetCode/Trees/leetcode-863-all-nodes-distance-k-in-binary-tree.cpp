// LeetCode-2385: https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected
// decent question
// basic approach is same as LeetCode-2385: https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected

#include <list>
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
    bool buildPathToTargetNode(TreeNode* root, TreeNode* target, list<char>& path) {
        if (root == nullptr) {
            return false;
        }

        if (root == target) {
            return true;
        }

        path.push_back('L');
        if (buildPathToTargetNode(root->left, target, path)) {
            return true;
        }
        path.pop_back();

        path.push_back('R');
        if (buildPathToTargetNode(root->right, target, path)) {
            return true;
        }
        path.pop_back();

        return false;
    }

    void showPath(TreeNode* root, list<char>& path) {
        if (path.empty()) {
            printf("[%d]\n", root->val);
            return;
        }

        TreeNode* node = root;
        for (auto& c: path) {
            printf("[%d]", node->val);

            if (c == 'L') {
                node = node->left;
            } else {
                node = node->right;
            }

            printf("--%c-->", c);
        }
        printf("[%d]\n", node->val);
    }

    // LC runtime: 0ms, 100%tile
    void findNodesAtKDistanceFromTarget(TreeNode* root, int k, list<char>& path, bool isInPath, int crrDist, vector <int>& nodesAtKDist) {
        if (root == nullptr) {
            return;
        }

        if (crrDist == k) {
            nodesAtKDist.push_back(root->val);
        }

        if (isInPath) {
            // so far we've been following and therefore 'consuming' path

            if (path.empty()) {
                // we are at the target node, crrDist must be zero
                findNodesAtKDistanceFromTarget(root->left, k, path, false, 1, nodesAtKDist);
                findNodesAtKDistanceFromTarget(root->right, k, path, false, 1, nodesAtKDist);
            } else if (path.front() == 'L') {
                // target node lies in left and we're going left: that is we're still 'consuming' path
                path.pop_front();
                findNodesAtKDistanceFromTarget(root->left, k, path, true, crrDist - 1, nodesAtKDist);
                path.push_front('L');

                // target node lies in left and we're going right: that is we're now treading away from path
                findNodesAtKDistanceFromTarget(root->right, k, path, false, crrDist + 1, nodesAtKDist);
            } else {
                // target node lies in right and we're going left: that is we're now treading away from path
                findNodesAtKDistanceFromTarget(root->left, k, path, false, crrDist + 1, nodesAtKDist);

                // target node lies in right and we're going right: that is we're still 'consuming' path
                path.pop_front();
                findNodesAtKDistanceFromTarget(root->right, k, path, true, crrDist - 1, nodesAtKDist);
                path.push_front('R');
            }
        } else {
            // we're already treading away from path
            findNodesAtKDistanceFromTarget(root->left, k, path, false, crrDist + 1, nodesAtKDist);
            findNodesAtKDistanceFromTarget(root->right, k, path, false, crrDist + 1, nodesAtKDist);
        }
    }

public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        list<char> path;
        buildPathToTargetNode(root, target, path);

        vector <int> nodesAtKDist;
        findNodesAtKDistanceFromTarget(root, k, path, true, path.size(), nodesAtKDist);

        return nodesAtKDist;
    }
};
