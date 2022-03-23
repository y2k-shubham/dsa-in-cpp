// LeetCode-449: https://leetcode.com/problems/serialize-and-deserialize-bst/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
   private:
    bool debug = false;

    void showVec(vector<int>& vec) {
        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    TreeNode* createNode(int val) {
        // this works fine on LeetCode, shows compilation error (red underline) on VS-Code
        TreeNode* newNode = new TreeNode(val);

        // newNode->val = val;
        // newNode->left = nullptr;
        // newNode->right = nullptr;

        return newNode;
    }

    vector<int> tokenizeStr(string& str) {
        if (str.empty()) {
            return {};
        }

        // tokenize std string based on delimiter: https://stackoverflow.com/a/14267455/3679900
        std::string delim = ",";
        vector<int> bstVec;

        auto start = 0U;
        auto end = str.find(delim);
        while (end != std::string::npos) {
            // parse std string to int: https://stackoverflow.com/a/7664227/3679900
            bstVec.push_back(stoi(str.substr(start, end - start)));
            start = end + delim.length();
            end = str.find(delim, start);
        }
        bstVec.push_back(stoi(str.substr(start, end)));

        return bstVec;
    }

    string stringifyVec(vector<int>& vec) {
        if (vec.empty()) {
            return "";
        }

        ostringstream oss;

        oss << vec[0];
        for (int i = 1; i < vec.size(); i++) {
            oss << "," << vec[i];
        }

        return oss.str();
    }

    void serialize(TreeNode* root, vector<int>& vec) {
        if (root != nullptr) {
            vec.push_back(root->val);
            serialize(root->left, vec);
            serialize(root->right, vec);
        }
    }

    TreeNode* deserialize(vector<int>& vec, int lo, int hi) {
        int len = hi - lo + 1;

        if (len <= 0) {
            return nullptr;
        } else if (len == 1) {
            return createNode(vec[lo]);
        } else {
            int rootVal = vec[lo];
            TreeNode* root = createNode(rootVal);

            // left subtree
            int ltLo = lo + 1;
            int ltHi = lo + 1;
            while ((ltHi <= hi) && (vec[ltHi] < rootVal)) {
                ltHi++;
            }
            ltHi--;
            root->left = deserialize(vec, ltLo, ltHi);

            // right subtree
            int rtLo = ltHi + 1;
            int rtHi = hi;
            root->right = deserialize(vec, rtLo, rtHi);

            return root;
        }
    }

   public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<int> serializedVec;
        serialize(root, serializedVec);

        string serializedStr = stringifyVec(serializedVec);

        if (debug) {
            printf("serialized vec\n");
            showVec(serializedVec);

            printf("serialized str\n");
            cout << serializedStr << endl;
        }

        return serializedStr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> vec = tokenizeStr(data);
        int len = vec.size();

        if (debug) {
            printf("stringified input\n");
            cout << data << endl;

            printf("tokenized str\n");
            showVec(vec);
        }

        return deserialize(vec, 0, len - 1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

int main() {
    return 0;
}
