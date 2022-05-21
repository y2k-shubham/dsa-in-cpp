// LeetCode-1268: https://leetcode.com/problems/search-suggestions-system/

#include <vector>
#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

#define BEGIN_ALPHA 'a'
#define END_ALPHA 'z'
#define NUM_ALPHAS 26

class Trie {
private:
    bool debug;
    vector<Trie*> children;
    bool isEnd;

    Trie* insertWord(Trie* crrNode, string& str, int idx) {
        if (crrNode == nullptr) {
            Trie newNode = Trie();
            crrNode = &newNode;
        }

        int len = str.size();
        if (idx >= len) {
            crrNode->isEnd = true;
            if (debug) {
                printf("insert: marking end\n");
            }
            return crrNode;
        }

        char ch = str.at(idx);
//        if (debug) {
//            printf("insert: currently at %c, diff-idx=%d\n", ch, (ch - BEGIN_ALPHA));
//        }

//        Trie* childNode = crrNode->children[ch - BEGIN_ALPHA];
//        if (childNode == nullptr) {
//            Trie newNode = Trie();
//            //newNode.debug = this->debug;
//            childNode = &newNode;
//
//            if (debug) {
//                printf("insert: inserting new node at %c\n", ch);
//            }
//            crrNode->children[ch - BEGIN_ALPHA] = childNode;
//        } else {
//            if (debug) {
//                printf("insert: skipping inserting new node at %c\n", ch);
//            }
//        }

        crrNode->children[ch - BEGIN_ALPHA] = insertWord(crrNode->children[ch - BEGIN_ALPHA], str, idx + 1);
        return crrNode;
    }

    bool hasWord(Trie* crrNode, string& str, int idx) {
        if (crrNode == nullptr) {
            if (debug) {
                printf("has: returning as trie is empty\n");
            }
            return false;
        }

        int len = str.size();
        if (idx >= len) {
            if (debug) {
                printf("has: returning isEnd=%s as idx=%d >= len=%d\n", (crrNode->isEnd ? "true" : "false"), idx, len);
            }
            return crrNode->isEnd;
        }

        char ch = str.at(idx);

        Trie* childNode = crrNode->children[ch - BEGIN_ALPHA];
        if (childNode == nullptr) {
            if (debug) {
                printf("has: returning false as ch=%c is empty\n", ch);
            }
            return false;
        }

        if (debug) {
            printf("has: moving into ch=%c\n", ch);
        }
        return hasWord(childNode, str, idx + 1);
    }

    void showNonEmptyChildren(Trie* crrNode) {
        for (int i = 0; i < crrNode->children.size(); i++) {
            if (crrNode->children[i] != nullptr) {
                printf("%c, ", (BEGIN_ALPHA + i));
            }
        }
        cout << endl;
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class TrieTest;

    Trie() {
        vector<Trie*> children(END_ALPHA - BEGIN_ALPHA + 1, nullptr);
        this->children = children;

        this->isEnd = false;

        this->debug = false;
    }

    void insertWord(string& str) {
        insertWord(this, str, 0);
    }

    bool hasWord(string& str) {
        return hasWord(this, str, 0);
    }
};

class TrieTest {
public:
    void testInsertWord() {
        Trie trie = Trie();
        string word;
        bool hasWordOutExpected, hasWordOutComputed;

        word = "";
        hasWordOutExpected = false;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        word = "kip";
        hasWordOutExpected = false;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        trie.enableDebug();
        word = "kin";
        trie.insertWord(word);
        trie.disableDebug();

        trie.showNonEmptyChildren(&trie);
        trie.showNonEmptyChildren(trie.children['k' - BEGIN_ALPHA]);

//        trie.enableDebug();
//        word = "greyhound";
//        trie.insertWord(word);
//        trie.disableDebug();
//
//        trie.showNonEmptyChildren(&trie);
//        trie.showNonEmptyChildren(trie.children['g' - BEGIN_ALPHA]);

        trie.enableDebug();
        word = "kiger";
        trie.insertWord(word);
        trie.disableDebug();

        trie.enableDebug();
        word = "khyber";
        trie.insertWord(word);
        trie.disableDebug();

        trie.enableDebug();
        word = "kinshasa";
        trie.insertWord(word);
        trie.disableDebug();

        trie.enableDebug();
        word = "kins";
        trie.insertWord(word);
        trie.disableDebug();

        trie.enableDebug();
        word = "tycib";
        trie.insertWord(word);
        trie.disableDebug();

        trie.showNonEmptyChildren(&trie);
        trie.showNonEmptyChildren(trie.children['t' - BEGIN_ALPHA]);

        trie.enableDebug();
        word = "craft";
        trie.insertWord(word);
        trie.disableDebug();

        trie.showNonEmptyChildren(&trie);
        trie.showNonEmptyChildren(trie.children['c' - BEGIN_ALPHA]);

        trie.enableDebug();
        word = "anna";
        trie.insertWord(word);
        trie.disableDebug();

        trie.showNonEmptyChildren(&trie);
        trie.showNonEmptyChildren(trie.children['a' - BEGIN_ALPHA]);

        trie.enableDebug();
        word = "pinnacle";
        trie.insertWord(word);
        trie.disableDebug();

        trie.showNonEmptyChildren(&trie);
        trie.showNonEmptyChildren(trie.children['p' - BEGIN_ALPHA]);

        word = "k";
        hasWordOutExpected = false;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        word = "ki";
        hasWordOutExpected = false;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        trie.enableDebug();
        word = "kin";
        hasWordOutExpected = true;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);
        trie.disableDebug();

        word = "kins";
        hasWordOutExpected = false;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        word = "king";
        trie.insertWord(word);

        word = "king";
        hasWordOutExpected = true;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        word = "kins";
        trie.insertWord(word);

        word = "kins";
        hasWordOutExpected = true;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        word = "king";
        hasWordOutExpected = true;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);

        word = "kings";
        hasWordOutExpected = false;
        hasWordOutComputed = trie.hasWord(word);
        assert(hasWordOutExpected == hasWordOutComputed);
    }

    void testHasWord() {
        Trie trie = Trie();
        string str;

        Trie trie1 = Trie();
        trie.children['a' - BEGIN_ALPHA] = &trie1;
        trie1.isEnd = true;

        Trie trie2 = Trie();
        trie1.children['u' - BEGIN_ALPHA] = &trie2;

        Trie trie3 = Trie();
        trie2.children['n' - BEGIN_ALPHA] = &trie3;

        Trie trie4 = Trie();
        trie3.children['t' - BEGIN_ALPHA] = &trie4;
        trie4.isEnd = true;

        Trie trie5 = Trie();
        trie4.children['y' - BEGIN_ALPHA] = &trie5;
        trie5.isEnd = true;

        str = "a";
        assert(trie.hasWord(str) == true);

        str = "au";
        assert(trie.hasWord(str) == false);

        str = "aun";
        assert(trie.hasWord(str) == false);

        str = "aunt";
        assert(trie.hasWord(str) == true);

        str = "aunts";
        assert(trie.hasWord(str) == false);

        str = "aunty";
        assert(trie.hasWord(str) == true);

        str = "ank";
        assert(trie.hasWord(str) == false);
    }
};

class Solution {
private:

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {

    }
};

int main() {
    TrieTest trieTest = TrieTest();
    trieTest.testHasWord();
    trieTest.testInsertWord();

    return 0;
}
