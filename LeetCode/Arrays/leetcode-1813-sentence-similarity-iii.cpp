// LeetCode-1813: https://leetcode.com/problems/sentence-similarity-iii
// not as easy as it appears to be

#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include <utility>

using namespace std;

class Solution {
public:
    friend class SolutionTest;

    bool areSentencesSimilar(string sentence1, string sentence2) {
        if (sentence1 == sentence2) {
            return true;
        }

        vector<string> sentenceVec1 = tokenizeSentence(sentence1);
        vector<string> sentenceVec2 = tokenizeSentence(sentence2);


        vector<string> sentenceVecLong = (sentenceVec1.size() >= sentenceVec2.size()) ? sentenceVec1 : sentenceVec2;
        vector<string> sentenceVecShort = (sentenceVec1.size() < sentenceVec2.size()) ? sentenceVec1 : sentenceVec2;

        int lenShort = sentenceVecShort.size();
        int lenLong = sentenceVecLong.size();

        int lIdx = swallowFromLeftTillMatching(sentenceVecShort, sentenceVecLong);
        if (lIdx == lenShort) {
            return true;
        }

        pair<int, int> rIdxes = swallowFromRightTillMatching(sentenceVecShort, sentenceVecLong);
        int rIdxShort = rIdxes.first;
        int rIdxLong = rIdxes.second;
        if (rIdxShort < lIdx) {
            return true;
        }

//        printf("lIdx=%d, rIdxes=(%d, %d)\n", lIdx, rIdxShort, rIdxLong);
        return (lIdx + (lenLong - rIdxLong - 1)) == lenShort;
    }

private:
    int swallowFromLeftTillMatching(vector<string>& vec1, vector<string>& vec2) {
        int len1 = vec1.size();
        int len2 = vec2.size();

        int i;
        for (i = 0; i < min(len1, len2); i++) {
            if (vec1[i] != vec2[i]) {
                return i;
            }
        }

        return i;
    }

    pair<int, int> swallowFromRightTillMatching(vector<string>& vec1, vector<string>& vec2) {
        int len1 = vec1.size();
        int len2 = vec2.size();

        int i1 = len1 - 1;
        int i2 = len2 - 1;

        for (; i1 >= 0 && i2 >= 0; i1--, i2--) {
            if (vec1[i1] != vec2[i2]) {
                return {i1, i2};
            }
        }

        return {i1, i2};
    }

    // function taken from GeeksForGeeks: https://www.geeksforgeeks.org/split-a-sentence-into-sentenceVec-in-cpp/
    vector<string> tokenizeSentence(string& sentenceStr) {
        // Create a stringstream object
        stringstream ss(sentenceStr);

        // Variable to hold each word
        string word;
        // Vector to store the sentenceVec
        vector<string> sentenceVec;

        // Extract sentenceVec from the sentence
        while (ss >> word) {
            // Add the word to the vector
            sentenceVec.push_back(word);
        }

        return sentenceVec;
    }
};

class SolutionTest {
public:
    void testAreSentencesSimilar() {
        Solution soln = Solution();
        string sentence1, sentence2;
        bool expected, actual;

        sentence1 = "My name is Haley";
        sentence2 = "My Haley";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "of";
        sentence2 = "A lot of words";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "of";
        sentence2 = "A lot of things";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A lot";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A of";
        sentence2 = "A lot of things";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "lot of";
        sentence2 = "A lot of things";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "lot of things";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "of things";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A lot of";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "of A";
        sentence2 = "A lot of things";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "Eating right now";
        sentence2 = "Eating";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "Eating right now";
        sentence2 = "Eating right";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "Eating right now";
        sentence2 = "Eating now";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "Eating right now";
        sentence2 = "right now";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "Eating right now";
        sentence2 = "now Eating";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "Luky";
        sentence2 = "Luky";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A a";
        sentence2 = "a";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A";
        sentence2 = "a";
        expected = false;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A";
        sentence2 = "A";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A B B";
        sentence2 = "A B C D B B";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        printf("[testAreSentencesSimilar] All test cases passed\n");
    }

    void testSwallowFromLeftTillMatching() {
        Solution soln = Solution();
        vector<string> sentenceVec1, sentenceVec2;
        int idx;

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A", "lot", "of", "words"};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 4);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A", "lot", "of", "things"};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 3);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A", "lot"};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 2);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A"};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 1);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"B"};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 0);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 0);

        sentenceVec1 = {"A"};
        sentenceVec2 = {"A"};
        idx = soln.swallowFromLeftTillMatching(sentenceVec1, sentenceVec2);
        assert(idx == 1);

        printf("[testSwallowFromLeftTillMatching] All test cases passed\n");
    }

    void testSwallowFromRightTillMatching() {
        Solution soln = Solution();
        vector<string> sentenceVec1, sentenceVec2;
        pair<int, int> idxPair;

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A", "lot", "of", "words"};
        idxPair = soln.swallowFromRightTillMatching(sentenceVec1, sentenceVec2);
        assert(idxPair.first == -1 && idxPair.second == -1);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A", "lot", "of", "things"};
        idxPair = soln.swallowFromRightTillMatching(sentenceVec1, sentenceVec2);
        assert(idxPair.first == 3 && idxPair.second == 3);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"A", "war", "of", "words"};
        idxPair = soln.swallowFromRightTillMatching(sentenceVec1, sentenceVec2);
        assert(idxPair.first == 1 && idxPair.second == 1);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {"of", "words"};
        idxPair = soln.swallowFromRightTillMatching(sentenceVec1, sentenceVec2);
        assert(idxPair.first == 1 && idxPair.second == -1);

        sentenceVec1 = {"A", "lot", "of", "words"};
        sentenceVec2 = {};
        idxPair = soln.swallowFromRightTillMatching(sentenceVec1, sentenceVec2);
        assert(idxPair.first == 3 && idxPair.second == -1);

        printf("[testSwallowFromRightTillMatching] All test cases passed\n");
    }

    void testTokenizeSentence() {
        Solution soln = Solution();
        string sentenceStrIn;
        vector<string> sentenceVecOutExpected, sentenceVecOutComputed;

        sentenceStrIn = "Geeks for Geeks";
        sentenceVecOutExpected = {"Geeks", "for", "Geeks"};
        sentenceVecOutComputed = soln.tokenizeSentence(sentenceStrIn);
        assert(sentenceVecOutComputed == sentenceVecOutExpected);

        sentenceStrIn = "practice makes perfect";
        sentenceVecOutExpected = {"practice", "makes", "perfect"};
        sentenceVecOutComputed = soln.tokenizeSentence(sentenceStrIn);
        assert(sentenceVecOutComputed == sentenceVecOutExpected);

        sentenceStrIn = "perseverance";
        sentenceVecOutExpected = {"perseverance"};
        sentenceVecOutComputed = soln.tokenizeSentence(sentenceStrIn);
        assert(sentenceVecOutComputed == sentenceVecOutExpected);

        printf("[testTokenizeSentence] All test cases passed\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testAreSentencesSimilar();
    solnTest.testSwallowFromLeftTillMatching();
    solnTest.testSwallowFromRightTillMatching();
    solnTest.testTokenizeSentence();

    return 0;
}
