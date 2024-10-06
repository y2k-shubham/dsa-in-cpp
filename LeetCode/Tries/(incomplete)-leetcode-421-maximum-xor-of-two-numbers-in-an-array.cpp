// (incomplete)
// LeetCode-421: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
// Techdose: https://www.youtube.com/watch?v=jCuZCbXnpLo

// Certainly more difficult than average medium problem

#include <vector>
#include <cassert>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

class TrieNode {
private:
    pair<TrieNode*, TrieNode*> children;

    void set0Node(TrieNode* node) {
        children.first = node;
    }

    void set1Node(TrieNode* node) {
        children.second = node;
    }

public:
    TrieNode() {
        children.first = nullptr;
        children.second = nullptr;
    }

    TrieNode* get0Node() {
        return children.first;
    }

    TrieNode* get1Node() {
        return children.second;
    }

    bool has0Node() {
        return get0Node() != nullptr;
    }

    bool has1Node() {
        return get1Node() != nullptr;
    }

    TrieNode* create0Node() {
        TrieNode* node = new TrieNode();
        set0Node(node);
        return node;
    }

    TrieNode* create1Node() {
        TrieNode* node = new TrieNode();
        set1Node(node);
        return node;
    }
};

class Solution {
private:
    vector<int> vec;
    TrieNode* root;
    int maxSetBitPosn;
    int maxSetBitMask;

    void init() {
        root = new TrieNode();
        maxSetBitPosn = 0;
        maxSetBitMask = 0;
    }

    void init(vector <int>& vec) {
        init();
        this->vec = vec;
        constructStructures();
    }

    void constructStructures() {
        calculateMaxSetBitPosn(this->vec);
        calculateMaxSetBitMask();
        constructTrie(this->vec);
    }

    double log2(double x) {
        return log(x) / log(2);
    }

    void calculateMaxSetBitPosn(vector<int>& vec) {
        int maxValue = *max_element(vec.begin(), vec.end());
        maxSetBitPosn = log2(maxValue) + 1;
    }

    void calculateMaxSetBitMask() {
        for (int i = 1; i <= maxSetBitPosn; i++) {
            maxSetBitMask |= (1 << i);
        }
    }

    void insertTrieNode(TrieNode* root, int depth, int num) {
        for (int i = 1; i <= depth; i++) {
            bool isSet = (num & (1 << (depth - i))) > 0;
            root = isSet ? root->create1Node() : root->create0Node();
        }
    }

    void constructTrie(vector<int>& vec) {
        root = new TrieNode();
        for (int n: vec) {
            insertTrieNode(root, maxSetBitPosn, n);
        }
    }

    int findMaxXORPartnerForEle(int ele) {
        int maxPossibleXORPartner = maxSetBitMask ^ ele;

        TrieNode* node = root;
        int maxXORPartner = 0;
        for (int i = maxSetBitPosn; i >= 1; i--) {
            bool isSet = (maxPossibleXORPartner & (1 << (i - 1))) > 0;

            if (isSet) {
                if (node->has1Node()) {
                    maxXORPartner |= (1 << (i - 1));
                    node = node->get1Node();
                } else {
                    node = node->get0Node();
                }
            } else {
                if (node->has0Node()) {
                    node = node->get0Node();
                } else {
                    maxXORPartner |= (1 << (i - 1));
                    node = node->get1Node();
                }
            }
        }

        return maxXORPartner;
    }

public:
    friend class SolutionTest;

    int findMaximumXOR(vector<int>& nums) {
        init(vec);

        int maxXOR = 0;
        for (int i = 0; i < vec.size(); i++) {
            int ele = vec[i];
            int maxXORPartner = findMaxXORPartnerForEle(ele);

            maxXOR = max(maxXOR, ele ^ maxXORPartner);
        }

        return maxXOR;
    }
};

class SolutionTest {
public:
    void testFindMaxXORPartnerForEle() {
        Solution soln = Solution();
        vector<int> vec;
        int ele;
        int maxXORPartnerOutExpected, maxXORPartnerOutComputed;

        vec = {3, 5, 10, 25};
        soln.init(vec);

        ele = 3;
        maxXORPartnerOutExpected = 25;
        maxXORPartnerOutComputed = soln.findMaxXORPartnerForEle(ele);
        assert(maxXORPartnerOutExpected == maxXORPartnerOutComputed);

        ele = 5;
        maxXORPartnerOutExpected = 25;
        maxXORPartnerOutComputed = soln.findMaxXORPartnerForEle(ele);
        assert(maxXORPartnerOutExpected == maxXORPartnerOutComputed);

        ele = 10;
        maxXORPartnerOutExpected = 25;
        maxXORPartnerOutComputed = soln.findMaxXORPartnerForEle(ele);
        assert(maxXORPartnerOutExpected == maxXORPartnerOutComputed);

        printf("[testFindMaxXORPartnerForEle] All test cases passed!\n");
    }

    void testFindMaximumXOR() {
        Solution soln = Solution();
        vector<int> vec;
        int maxXOROutExpected, maxXOROutComputed;

        vec = {3, 10, 5, 25, 2, 8};
        maxXOROutExpected = 28;
        maxXOROutComputed = soln.findMaximumXOR(vec);
        assert(maxXOROutExpected == maxXOROutComputed);

        vec = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
        maxXOROutExpected = 127;
        maxXOROutComputed = soln.findMaximumXOR(vec);
        assert(maxXOROutExpected == maxXOROutComputed);

        printf("[testFindMaximumXOR] All test cases passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindMaxXORPartnerForEle();
    solnTest.testFindMaximumXOR();

    return 0;
}
