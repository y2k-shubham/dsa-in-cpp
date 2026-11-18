// LeetCode-950: https://leetcode.com/problems/reveal-cards-in-increasing-order/
// Companies: [Google][Amazon][Bloomberg][Microsoft]

// Not very easy;
// solved after reading editorial, though in more understandable (slightly less efficient) way

#include <queue>
#include <vector>

using namespace std;

class Solution {
private:
    queue <int> createIndicesQue(int len) {
        queue <int> indices;
        for (int i = 0; i < len; i++) {
            indices.push(i);
        }

        return indices;
    }

    vector <int> createIndicesRevealOrderVec(int len) {
        queue <int> indicesQue = createIndicesQue(len);
        vector <int> indicesRevealOrderVec(len);

        bool shouldReveal = true;
        int i = 0;
        while (!indicesQue.empty()) {
            int frontIndex = indicesQue.front();

            if (shouldReveal) {
                indicesRevealOrderVec[i++] = frontIndex;
            } else {
                indicesQue.push(frontIndex);
            }

            indicesQue.pop();
            shouldReveal = !shouldReveal;
        }

        return indicesRevealOrderVec;
    }

    vector <int> rearrangeSortedElesInOrderOfIndices(vector <int>& unOrderedEles, vector <int>& indicesOrder) {
        int len = unOrderedEles.size();

        vector <int> sortedOrderEles = unOrderedEles;
        sort(sortedOrderEles.begin(), sortedOrderEles.end());

        vector <int> indicesOrderedEles(len);

        for (int i = 0; i < len; i++) {
            indicesOrderedEles[indicesOrder[i]] = sortedOrderEles[i];
        }

        return indicesOrderedEles;
    }

public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int len = deck.size();
        if (len <= 1) {
            return deck;
        }

        vector <int> indicesRevealOrderVec = createIndicesRevealOrderVec(len);

        vector <int> rearragedSortedElesInOrderOfIndices = rearrangeSortedElesInOrderOfIndices(deck, indicesRevealOrderVec);
        return rearragedSortedElesInOrderOfIndices;
    }
};
