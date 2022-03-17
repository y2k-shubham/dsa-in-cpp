// LeetCode-1261: https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class FindElements {
   private:
    TreeNode* root;

    void recoverTree(TreeNode* root) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                root->left->val = (2 * root->val) + 1;
                recoverTree(root->left);
            }

            if (root->right != nullptr) {
                root->right->val = (2 * root->val) + 2;
                recoverTree(root->right);
            }
        }
    }

    bool isPresent(TreeNode* root, int target) {
        if (root == nullptr) {
            return false;
        } else if (target < root->val) {
            return false;
        } else if (root->val == target) {
            return true;
        } else {
            return isPresent(root->left, target) || isPresent(root->right, target);
        }
    }

   public:
    FindElements(TreeNode* root) {
        root->val = 0;
        recoverTree(root);

        this->root = root;
    }

    bool find(int target) {
        return isPresent(this->root, target);
    }
};

/**
Your FindElements object will be instantiated and called as such:
FindElements* obj = new FindElements(root);
bool param_1 = obj->find(target);
 */
