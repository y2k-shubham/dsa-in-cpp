// LeetCode-2096: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/
// incomplete

#include <list>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cassert>
#include <sstream>

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
    bool debug = false;

    bool findPath(TreeNode* root, int val, list<char>& path) {
        if (root == nullptr) {
            return false;
        }

        if (root->val == val) {
            return true;
        }

        path.push_back('L');
        if (findPath(root->left, val, path)) {
            return true;
        }
        path.pop_back();

        path.push_back('R');
        if (findPath(root->right, val, path)) {
            return true;
        }
        path.pop_back();

        return false;
    }

    void showPath(int val, list<char>& path) {
        printf("for node=%d, path is:-\n", val);
        for (auto& c: path) {
            cout << c << " ";
        }
        cout << endl;
    }

    int findCommonPathLen(list<char>& path1, list<char>& path2) {
        if (path1.empty() || path2.empty()) {
            return 0;
        }

        int len = 0;

        auto it1 = path1.begin();
        auto it2 = path2.begin();
        while (it1 != path1.end() && it2 != path2.end()) {
            if (*it1 == *it2) {
                len++;
                it1++;
                it2++;
            } else {
                break;
            }
        }

        return len;
    }

    void removeHeadNodes(list<char>& path, int n) {
        for (int i = 1; i <= n; i++) {
            path.pop_front();
        }
    }

    list<char> getPath(list<char>& path1, list<char>& path2) {
        if (path1.empty() && path2.empty()) {
            return {};
        }

        int commonPathLen = findCommonPathLen(path1, path2);

        if (commonPathLen >= 1) {
            removeHeadNodes(path1, commonPathLen);
            removeHeadNodes(path2, commonPathLen);
        }

        list<char> upPath('U', path1.size());
        list<char> downPath = path2;

        upPath.insert(upPath.end(), downPath.begin(), downPath.end());
        return upPath;
    }

public:
    friend class SolutionTest;

    string getDirections(TreeNode* root, int startValue, int destValue) {

    }
};

class SolutionTest {
public:
    void testFindCommonPathLen() {
        Solution soln = Solution();
        list<char> path1;
        list<char> path2;
        int outExpected, outComputed;

        path1 = {};
        path2 = {};
        outExpected = 0;
        outComputed = soln.findCommonPathLen(path1, path2);
        assert(outComputed == outExpected);

        path1 = {'L', 'R'};
        path2 = {'R'};
        outExpected = 0;
        outComputed = soln.findCommonPathLen(path1, path2);
        assert(outComputed == outExpected);

        path1 = {'L', 'R'};
        path2 = {'R', 'R'};
        outExpected = 0;
        outComputed = soln.findCommonPathLen(path1, path2);
        assert(outComputed == outExpected);

        path1 = {'L', 'R'};
        path2 = {'L', 'L'};
        outExpected = 1;
        outComputed = soln.findCommonPathLen(path1, path2);
        assert(outComputed == outExpected);

        path1 = {'L', 'R'};
        path2 = {'L', 'R'};
        outExpected = 2;
        outComputed = soln.findCommonPathLen(path1, path2);
        assert(outComputed == outExpected);
    }

    void testGetPath() {
        Solution soln = Solution();
        list<char> path1;
        list<char> path2;
        list<char> outExpected;
        list<char> outComputed;

        path1 = {};
        path2 = {};
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindCommonPathLen();
    solnTest.testGetPath();

    return 0;
}
