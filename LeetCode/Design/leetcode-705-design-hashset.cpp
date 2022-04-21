// LeetCode-705: https://leetcode.com/problems/design-hashset/
// space-unoptimized soln (this one) can be skipped (pretty dumb)
// something like a self-balanced BST soln would look charming

#include <vector>

using namespace std;

#define MAX_KEY 1000001

class MyHashSet {
private:
    vector<bool> presenceVec;

public:
    MyHashSet() {
        vector<bool> presenceVec(MAX_KEY, false);
        this->presenceVec = presenceVec;
    }

    void add(int key) {
        this->presenceVec[key] = true;
    }

    void remove(int key) {
        this->presenceVec[key] = false;
    }

    bool contains(int key) {
        return this->presenceVec[key];
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
