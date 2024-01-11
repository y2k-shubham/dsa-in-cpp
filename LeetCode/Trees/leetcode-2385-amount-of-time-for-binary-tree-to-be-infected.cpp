// https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected
// decent question

#include <list>

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
    bool buildPathToTargetNode(TreeNode* root, int target, list<char>& path) {
        if (root == nullptr) {
            return false;
        }

        if (root->val == target) {
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

    // LC runtime 258ms, 86%tile
    int findMaxDistanceFromTarget(TreeNode* root, list<char>& path, bool isInPath, int crrDist) {
        if (root == nullptr) {
            return 0;
        }

        int lMaxDist;
        int rMaxDist;

        if (isInPath) {
            // so far we've been following and therefore 'consuming' path

            if (path.empty()) {
                // we are at the target node, crrDist must be zero
                lMaxDist = findMaxDistanceFromTarget(root->left, path, false, 1);
                rMaxDist = findMaxDistanceFromTarget(root->right, path, false, 1);
            } else if (path.front() == 'L') {
                // target node lies in left and we're going left: that is we're still 'consuming' path
                path.pop_front();
                lMaxDist = findMaxDistanceFromTarget(root->left, path, true, crrDist - 1);
                path.push_front('L');

                // target node lies in left and we're going right: that is we're now treading away from path
                rMaxDist = findMaxDistanceFromTarget(root->right, path, false, crrDist + 1);
            } else {
                // target node lies in right and we're going left: that is we're now treading away from path
                lMaxDist = findMaxDistanceFromTarget(root->left, path, false, crrDist + 1);

                // target node lies in right and we're going right: that is we're still 'consuming' path
                path.pop_front();
                rMaxDist = findMaxDistanceFromTarget(root->right, path, true, crrDist - 1);
                path.push_front('R');
            }
        } else {
            // we're already treading away from path
            lMaxDist = findMaxDistanceFromTarget(root->left, path, false, crrDist + 1);
            rMaxDist = findMaxDistanceFromTarget(root->right, path, false, crrDist + 1);
        }

        return max(crrDist, max(lMaxDist, rMaxDist));
    }

public:
    int amountOfTime(TreeNode* root, int start) {
        list<char> path;
        buildPathToTargetNode(root, start, path);
        //showPath(root, path);

        return findMaxDistanceFromTarget(root, path, true, path.size());
    }
};
