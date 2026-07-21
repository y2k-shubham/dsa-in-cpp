// LeetCode-288: https://leetcode.com/problems/unique-word-abbreviation/
// Premium
// Companies: [Google]

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

class ValidWordAbbr {
private:
    unordered_map<string, unordered_set<string>> abbrvWords;

    string convertToAbbrv(string word) {
        int len = word.length();
        if (len <= 2) {
            return word; // nothing to abbreviate, avoids "i0t" for "it"
        }

        return string(1, word.front()) + to_string(len - 2) + string(1, word.back());
    }

    void initAbbrvFreqMap(vector<string>& words) {
        for (string word: words) {
            string abbrv = convertToAbbrv(word);
            abbrvWords[abbrv].insert(word);
        }
    }

public:
    ValidWordAbbr(vector<string>& dictionary) {
        initAbbrvFreqMap(dictionary);
    }

    bool isUnique(string word) {
        string abbrv = convertToAbbrv(word);

        if (abbrvWords.find(abbrv) == abbrvWords.end()) {
            return true;
        }

        unordered_set<string> wordsWithSameAbbrv = abbrvWords[abbrv];
        return (wordsWithSameAbbrv.size() == 1) && (*wordsWithSameAbbrv.begin() == word);
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
