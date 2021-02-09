// LeetCode-284: https://leetcode.com/problems/peeking-iterator/
// Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3633/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class Iterator {
   private:
    struct Data;
    Data* data;

   public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);

    // Returns the next element in the iteration.
    int next();

    // Returns true if the iteration has more elements.
    bool hasNext() const;
};

class PeekingIterator : public Iterator {
   private:
    int tmp;

   public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        this->tmp = INT_MIN;
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        int peekVal;

        if (this->tmp != INT_MIN) {
            peekVal = this->tmp;
        } else {
            this->tmp = Iterator::next();
            peekVal = this->tmp;
        }

        return peekVal;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        int nextVal;

        if (this->tmp != INT_MIN) {
            nextVal = this->tmp;
            this->tmp = INT_MIN;
        } else {
            nextVal = Iterator::next();
        }

        return nextVal;
    }

    bool hasNext() const {
        bool hasNextFlag;

        if (this->tmp != INT_MIN) {
            hasNextFlag = true;
        } else {
            hasNextFlag = Iterator::hasNext();
        }

        return hasNextFlag;
    }
};
