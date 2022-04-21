// LeetCode-706: https://leetcode.com/problems/design-hashmap/
// pretty much the same (and dumb) as LeetCode-705: https://leetcode.com/problems/design-hashset/

#include <vector>

using namespace std;

#define MAX_KEY 1000001
#define NO_VALUE -1

class MyHashMap {
private:
    vector<int> vec;

public:
    MyHashMap() {
        vector<int> vec(MAX_KEY, NO_VALUE);
        this->vec = vec;
    }

    void put(int key, int value) {
        this->vec[key] = value;
    }

    int get(int key) {
        return this->vec[key];
    }

    void remove(int key) {
        this->vec[key] = NO_VALUE;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

