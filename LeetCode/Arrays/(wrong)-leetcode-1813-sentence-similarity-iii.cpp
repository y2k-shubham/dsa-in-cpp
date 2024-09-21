// LeetCode-1813: https://leetcode.com/problems/sentence-similarity-iii
// wrong: appear to have misunderstood the problem

/**
 * we have implemented the solution such that one sentence can be subsequence of other sentence
 * (that is any no of word insertions allowed at any position)
 */

#include <vector>
#include <string>
#include <cassert>
#include <sstream>

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

        int idx = 0;
        for (string word: sentenceVecShort) {
            idx = swallowTillWord(sentenceVecLong, word, idx);
            if (idx >= sentenceVecLong.size()) {
                return false;
            }
        }

        return true;
    }

private:
    int swallowTillWord(vector<string>& sentenceVec, string word, int startIdx) {
        int idx = startIdx;
        while (idx < sentenceVec.size() && sentenceVec[idx] != word) {
            idx++;
        }
        return idx;
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
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "of";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A lot";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "A of";
        sentence2 = "A lot of things";
        expected = true;
        actual = soln.areSentencesSimilar(sentence1, sentence2);
        assert(expected == actual);

        sentence1 = "lot of";
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

        printf("[testAreSentencesSimilar] All test cases passed\n");
    }

    void testSwallowTillWord() {
        Solution soln = Solution();
        vector<string> sentenceVec;
        string word;
        int startIdx, endIdx;

        sentenceVec = {"practice", "makes", "perfect", "coding", "makes"};

        word = "makes";

        startIdx = 0;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 1);

        startIdx = 1;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 1);

        startIdx = 2;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 4);

        word = "perfect";

        startIdx = 0;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 2);

        startIdx = 1;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 2);

        startIdx = 2;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 2);

        startIdx = 3;
        endIdx = soln.swallowTillWord(sentenceVec, word, startIdx);
        assert(endIdx == 5);

        printf("[testSwallowTillWord] All test cases passed\n");
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
    solnTest.testSwallowTillWord();
    solnTest.testTokenizeSentence();

    return 0;
}
