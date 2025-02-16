// LeetCode-2096: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/

#include <list>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>

using namespace std;

#define LEFT 'L'
#define RIGHT 'R'
#define UP 'U'
#define NULL_CHAR '\0'

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
    void showPath(list <char>& path, string name) {
        cout << name << ": ";
        for (char ch : path) {
            cout << ch << " ";
        }
        cout << endl;
    }

    bool buildPathRec(TreeNode* root, int target, list <char>& path) {
        if (root == nullptr) {
            return false;
        }
        if (root->val == target) {
            return true;
        }

        if (root->left != nullptr) {
            path.push_back(LEFT);
            if (buildPathRec(root->left, target, path)) {
                return true;
            }
            path.pop_back();
        }

        if (root->right != nullptr) {
            path.push_back(RIGHT);
            if (buildPathRec(root->right, target, path)) {
                return true;
            }
            path.pop_back();
        }

        return false;
    }

    list <char> buildPath(TreeNode* root, int target) {
        list <char> path;
        if (buildPathRec(root, target, path)) {
            return path;
        }

        return {NULL_CHAR};
    }

    void swallowCommonPathPrefix(list <char>& path1, list <char>& path2) {
        while (!path1.empty() && !path2.empty()) {
            if (path1.front() == path2.front()) {
                path1.pop_front();
                path2.pop_front();
            } else {
                break;
            }
        }
    }

    string serializePath(list <char>& path) {
        ostringstream oss;
        for (char ch : path) {
            oss << ch;
        }

        return oss.str();
    }

public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        list <char> pathToStart = buildPath(root, startValue);
        // showPath(pathToStart, "pathToStart (before swallow)");

        list <char> pathToDest = buildPath(root, destValue);
        // showPath(pathToDest, "pathToDest (before swallow)");

        swallowCommonPathPrefix(pathToStart, pathToDest);
        // showPath(pathToStart, "pathToStart (after swallow)");
        // showPath(pathToDest, "pathToDest (after swallow)");

        list <char> pathFromStartToLca = {};
        if (!pathToStart.empty()) {
            list <char> upPath(pathToStart.size(), UP);
            pathFromStartToLca = upPath;
        }

        list <char> pathFromLcaToDest = pathToDest;

        list <char> pathFromStartToDest = pathFromStartToLca;
        // showPath(pathFromStartToDest, "pathFromStartToDest (before insert)");
        pathFromStartToDest.insert(pathFromStartToDest.end(), pathFromLcaToDest.begin(), pathFromLcaToDest.end());
        // showPath(pathFromStartToDest, "pathFromStartToDest (after insert)");

        return serializePath(pathFromStartToDest);
    }
};
