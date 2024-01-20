// LeetCode-380: https://leetcode.com/problems/insert-delete-getrandom-o1

#include <unordered_set>
#include <random>
#include <sstream>
#include <iterator>

using namespace std;

class RandomizedSet {
private:
    std::random_device dev;
    unordered_set<int> mSet;

    int getRandomInt(int max) {
        // random number generation: https://stackoverflow.com/a/13445752/3679900
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randomDist(0, max);
        return randomDist(rng);
    }

public:
    RandomizedSet() {
    }

    bool insert(int val) {
        if (mSet.find(val) == mSet.end()) {
            mSet.insert(val);
            return true;
        }

        return false;
    }

    bool remove(int val) {
        if (mSet.find(val) == mSet.end()) {
            return false;
        }

        mSet.erase(val);
        return true;
    }

    // barely accepted; runtime 801 ms, 5 %tile
    int getRandom() {
        int idx = getRandomInt(mSet.size() - 1);
        if (idx > 0) {
            // retrieve random / nth element from set https://stackoverflow.com/a/3052796/3679900
            auto it = std::begin(mSet);
            // 'advance' the iterator n times
            std::advance(it,idx);
            return *it;
        }

        return *mSet.begin();
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */