// LeetCode-432: https://leetcode.com/problems/all-oone-data-structure/

/**
 * ["AllOne","inc","inc","getMaxKey","getMinKey","inc","getMaxKey","getMinKey"]
 * [[],["hello"],["hello"],[],[],["leet"],[],[]]
 *
 * ["AllOne","inc","inc","inc","inc","inc","dec","dec","getMaxKey","getMinKey"]
 * [[],["a"],["b"],["b"],["b"],["b"],["b"],["b"],[],[]]
 *
 * ["AllOne","inc","inc","inc","inc","inc","inc","dec", "dec","getMinKey","dec","getMaxKey","getMinKey"]
 * [[],["a"],["b"],["b"],["c"],["c"],["c"],["b"],["b"],[],["a"],[],[]]
 */

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * oddly enough, this supposedly optimized implementation of the DLL problem
 * performs ~ 75% poorer than the original version (LC runtime 139 ms, 45 %tile)
 * "Premature optimization is the root of all evil" - Donald Knuth
 */
class AllOne {
   private:
    unordered_map<string, int> keyCountMap;
    map<int, unordered_set<string> > countKeysMap;

    void showCountKeysMap() {
        printf("\ncountKeysMap is:-\n");
        for (map<int, unordered_set<string> >::iterator it1 = this->countKeysMap.begin(); it1 != this->countKeysMap.end(); it1++) {
            printf("[%d] : ", it1->first);
            for (unordered_set<string>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
                printf("%s ", (*it2).c_str());
            }
            cout << endl;
        }
    }

   public:
    friend class AllOneTest;

    AllOne() {
    }

    void inc(string key) {
        this->keyCountMap[key]++;

        int newCount = this->keyCountMap[key];
        if (newCount > 1) {
            this->countKeysMap[newCount - 1].erase(key);
            // important: dont miss this, or else it will all go for a toss
            if (this->countKeysMap[newCount - 1].empty()) {
                this->countKeysMap.erase(newCount - 1);
            }
        }

        this->countKeysMap[newCount].insert(key);
    }

    void dec(string key) {
        if (this->keyCountMap.find(key) == this->keyCountMap.end()) {
            return;
        }

        this->keyCountMap[key]--;

        int newCount = this->keyCountMap[key];
        if (newCount == 0) {
            this->keyCountMap.erase(key);
        } else {
            this->countKeysMap[newCount].insert(key);
        }

        this->countKeysMap[newCount + 1].erase(key);
        // important: dont miss this, or else it will all go for a toss
        if (this->countKeysMap[newCount + 1].empty()) {
            this->countKeysMap.erase(newCount + 1);
        }
    }

    string getMaxKey() {
        if (this->keyCountMap.empty()) {
            return "";
        } else {
            return *((this->countKeysMap.rbegin()->second).begin());
        }
    }

    string getMinKey() {
        if (this->keyCountMap.empty()) {
            return "";
        } else {
            return *((this->countKeysMap.begin()->second).begin());
        }
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

class AllOneTest {
   public:
    void testCase1() {
        AllOne allOne = AllOne();

        assert(allOne.getMaxKey() == "");
        assert(allOne.getMinKey() == "");

        allOne.inc("hello");
        assert(allOne.getMaxKey() == "hello");
        assert(allOne.getMinKey() == "hello");

        allOne.inc("hello");
        assert(allOne.getMaxKey() == "hello");
        // allOne.showCountKeysMap();
        assert(allOne.getMinKey() == "hello");

        allOne.inc("leet");
        assert(allOne.getMaxKey() == "hello");
        assert(allOne.getMinKey() == "leet");
    }

    void testCase2() {
        AllOne allOne = AllOne();

        assert(allOne.getMaxKey() == "");
        assert(allOne.getMinKey() == "");

        allOne.inc("a");
        assert(allOne.getMaxKey() == "a");
        assert(allOne.getMinKey() == "a");

        allOne.inc("b");
        assert((allOne.getMaxKey() == "a") || (allOne.getMaxKey() == "b"));
        assert((allOne.getMinKey() == "a") || (allOne.getMinKey() == "b"));

        allOne.inc("b");
        assert(allOne.getMaxKey() == "b");
        assert(allOne.getMinKey() == "a");

        allOne.inc("b");
        assert(allOne.getMaxKey() == "b");
        assert(allOne.getMinKey() == "a");

        allOne.inc("b");
        assert(allOne.getMaxKey() == "b");
        assert(allOne.getMinKey() == "a");

        allOne.dec("b");
        assert(allOne.getMaxKey() == "b");
        assert(allOne.getMinKey() == "a");

        allOne.dec("b");
        assert(allOne.getMaxKey() == "b");
        assert(allOne.getMinKey() == "a");
    }

    void testCase3() {
        AllOne allOne = AllOne();

        assert(allOne.getMaxKey() == "");
        assert(allOne.getMinKey() == "");

        allOne.inc("a");
        assert(allOne.getMaxKey() == "a");
        assert(allOne.getMinKey() == "a");

        allOne.inc("b");
        assert((allOne.getMaxKey() == "a") || (allOne.getMaxKey() == "b"));
        assert((allOne.getMinKey() == "a") || (allOne.getMinKey() == "b"));

        allOne.inc("b");
        assert(allOne.getMaxKey() == "b");
        assert(allOne.getMinKey() == "a");

        allOne.inc("c");
        assert(allOne.getMaxKey() == "b");
        assert((allOne.getMinKey() == "a") || (allOne.getMinKey() == "c"));

        allOne.inc("c");
        assert((allOne.getMaxKey() == "b") || (allOne.getMaxKey() == "c"));
        assert(allOne.getMinKey() == "a");

        allOne.inc("c");
        assert(allOne.getMaxKey() == "c");
        assert(allOne.getMinKey() == "a");

        allOne.dec("b");
        assert(allOne.getMaxKey() == "c");
        assert((allOne.getMinKey() == "a") || (allOne.getMinKey() == "b"));

        allOne.dec("b");
        assert(allOne.getMaxKey() == "c");
        assert(allOne.getMinKey() == "a");

        allOne.dec("a");
        assert(allOne.getMaxKey() == "c");
        assert(allOne.getMinKey() == "c");
    }
};

int main() {
    AllOneTest allOneTest = AllOneTest();

    allOneTest.testCase1();
    allOneTest.testCase2();
    allOneTest.testCase3();

    return 0;
}
