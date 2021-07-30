// LeetCode-677: https://leetcode.com/problems/map-sum-pairs/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/612/week-5-july-29th-july-31st/3832/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    char ch;
    int sum;
    int val;
    bool isLeaf;
    vector<TrieNode*> children;
};

// LC-submission speed: 100 %tile, memory 5 %tile (inputs are very small)
class MapSum {
   private:
    TrieNode* root;
    bool debug;

    TrieNode* createNode(char ch, int val, bool isLeaf) {
        TrieNode* node = new TrieNode;

        node->ch = ch;
        node->val = val;
        node->sum = val;
        node->isLeaf = isLeaf;

        vector<TrieNode*> children(26, nullptr);
        node->children = children;

        return node;
    }

    void showTrieNode(TrieNode* root) {
        printf("ch       : %c\n", root->ch);
        printf("isLeaf   : %s\n", (root->isLeaf ? "true" : "false"));
        printf("sum      : %d\n", root->sum);

        printf("children :-\n");
        for (char ch = 'a'; ch <= 'z'; ch++) {
            int idx = ch - 'a';
            if (root->children[idx] != nullptr) {
                printf("'%c' -> %d\n", ch, root->children[idx]->sum);
            }
        }

        cout << endl;
    }

    TrieNode* insertWord(TrieNode* root, string str, int newVal, int prevVal) {
        if (str.empty()) {
            return root;
        }

        char ch = str.at(0);
        if (root == nullptr) {
            if (str.size() == 1) {
                root = createNode(ch, newVal, false);
            } else {
                root = createNode(ch, 0, false);
                root->sum = newVal;
            }
        } else {
            root->sum -= prevVal;
            root->sum += newVal;
        }

        if (str.size() == 1) {
            root->val = newVal;
            root->isLeaf = true;
        } else {
            char nextChar = str.at(1);
            int idx = nextChar - 'a';
            root->children[idx] = insertWord(root->children[idx], str.substr(1), newVal, prevVal);
        }

        return root;
    }

    pair<int, int> findValAndSum(TrieNode* root, string prefix) {
        if (this->debug) {
            printf("------\n");
            printf("prefix: %s\n", prefix.c_str());
            showTrieNode(root);
            printf("------\n");
        }

        if (root == nullptr) {
            return {0, 0};
        }

        if (prefix.empty()) {
            return {root->val, root->sum};
        }

        char ch = prefix.at(0);
        int idx = ch - 'a';

        if (root->children[idx] == nullptr) {
            return {0, 0};
        }

        return findValAndSum(root->children[idx], prefix.substr(1));
    }

    bool keyExists(TrieNode* root, string key) {
        if (root == nullptr) {
            return false;
        }

        if (key.empty()) {
            return false;
        }

        char ch = key.at(0);
        int idx = ch - 'a';

        if (root->children[idx] == nullptr) {
            return false;
        }

        if (key.size() == 1) {
            return root->children[idx]->isLeaf;
        }

        return keyExists(root->children[idx], key.substr(1));
    }

   public:
    friend class MapSumTest;

    /** Initialize your data structure here. */
    MapSum() {
        this->root = createNode('\0', 0, false);
        this->debug = false;
    }

    void insert(string key, int val) {
        if (!key.empty()) {
            char ch = key.at(0);
            int idx = ch - 'a';

            int prevVal = 0;
            if (keyExists(key)) {
                prevVal = this->val(key);
            }

            this->root->children[idx] = insertWord(this->root->children[idx], key, val, prevVal);

            this->root->sum += val;
        }
    }

    int val(string key) {
        if (keyExists(root, key)) {
            return findValAndSum(this->root, key).first;
        }

        return 0;
    }

    int sum(string prefix) {
        return findValAndSum(this->root, prefix).second;
    }

    bool keyExists(string key) {
        return keyExists(this->root, key);
    }

    void clear() {
        this->root = createNode('\0', 0, false);
    }
};

class MapSumTest {
   public:
    void testCreateNode() {
        MapSum mapSum = MapSum();

        TrieNode* node = mapSum.createNode('f', -9, true);

        assert(node->ch == 'f');
        assert(node->sum == -9);
        assert(node->isLeaf == true);
        assert(node->children.size() == 26);
        for (vector<TrieNode*>::iterator i = node->children.begin(); i != node->children.end(); i++) {
            assert(*i == nullptr);
        }
    }

    void testVal() {
        MapSum mapSum = MapSum();

        mapSum.insert("monchi", 13);

        assert(mapSum.val("") == 0);
        assert(mapSum.val("a") == 0);
        assert(mapSum.val("m") == 0);
        assert(mapSum.val("mo") == 0);
        assert(mapSum.val("mon") == 0);
        assert(mapSum.val("monk") == 0);
        assert(mapSum.val("monki") == 0);
        assert(mapSum.val("monch") == 0);
        assert(mapSum.val("monchi") == 13);
        assert(mapSum.val("monchik") == 0);
    }

    void testInsertWord() {
        MapSum mapSum = MapSum();

        mapSum.insert("monchi", 13);
        // mapSum.showTrieNode(mapSum.root);
        // mapSum.showTrieNode(mapSum.root->children['m' - 'a']);

        assert(mapSum.sum("") == 13);
        assert(mapSum.sum("a") == 0);
        assert(mapSum.sum("m") == 13);
        assert(mapSum.sum("mo") == 13);
        assert(mapSum.sum("mon") == 13);
        assert(mapSum.sum("monk") == 0);
        assert(mapSum.sum("monki") == 0);
        assert(mapSum.sum("monch") == 13);
        assert(mapSum.sum("monchi") == 13);
        assert(mapSum.sum("monchik") == 0);

        mapSum.clear();

        mapSum.insert("apple", 3);
        assert(mapSum.sum("ap") == 3);
        mapSum.insert("app", 2);
        assert(mapSum.sum("ap") == 5);

        mapSum.clear();

        mapSum.insert("apple", 3);
        assert(mapSum.sum("ap") == 3);
        mapSum.insert("app", 2);
        // cout << (mapSum.keyExists("apple") ? "true" : "false") << endl;
        // cout << mapSum.sum("apple") << endl;
        mapSum.insert("apple", 2);
        // cout << mapSum.sum("apple") << endl;
        assert(mapSum.sum("apple") == 2);
        assert(mapSum.sum("app") == 4);
        assert(mapSum.sum("ap") == 4);

        mapSum.clear();

        mapSum.insert("appled", 2);
        assert(mapSum.sum("ap") == 2);
        mapSum.insert("apple", 3);
        assert(mapSum.sum("ap") == 5);
        assert(mapSum.sum("app") == 5);
        assert(mapSum.sum("appl") == 5);
        assert(mapSum.sum("apple") == 5);
        assert(mapSum.sum("appled") == 2);
        // cout << (mapSum.keyExists("apple") ? "true" : "false") << endl;
        // cout << mapSum.val("apple") << endl;
        // cout << mapSum.sum("apple") << endl;
        assert(mapSum.val("apple") == 3);
        mapSum.insert("apple", 2);
        // cout << mapSum.val("apple") << endl;
        // cout << mapSum.sum("apple") << endl;
        assert(mapSum.val("apple") == 2);
        // cout << mapSum.sum("apple") << endl;
        assert(mapSum.sum("apple") == 4);
        assert(mapSum.sum("app") == 4);
        assert(mapSum.sum("ap") == 4);
    }

    void testKeyExists() {
        MapSum mapSum = MapSum();

        mapSum.insert("monchi", 13);

        assert(mapSum.keyExists("") == false);
        assert(mapSum.keyExists("pika") == false);
        assert(mapSum.keyExists("m") == false);
        assert(mapSum.keyExists("mon") == false);
        assert(mapSum.keyExists("monch") == false);
        assert(mapSum.keyExists("monchi") == true);
        assert(mapSum.keyExists("monchipi") == false);
    }
};

int main() {
    MapSumTest mSumTest = MapSumTest();
    mSumTest.testCreateNode();
    mSumTest.testVal();
    mSumTest.testInsertWord();
    mSumTest.testKeyExists();

    return 0;
}

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
