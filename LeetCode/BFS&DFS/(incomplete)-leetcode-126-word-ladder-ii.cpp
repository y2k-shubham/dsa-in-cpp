// LeetCode-126: https://leetcode.com/problems/word-ladder-ii/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/611/week-4-july-22nd-july-28th/3825/

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_set<string> convertToSet(vector<string>& wordVec) {
        unordered_set<string> wordSet(wordVec.begin(), wordVec.end());
        return wordSet;
    }

    vector<string> convertToVec(stack<string> wordStack) {
        int len = wordStack.size();

        vector<string> wordVec(len);
        for (int i = len - 1; i >= 0; i--) {
            wordVec[i] = wordStack.top();
            wordStack.pop();
        }

        return wordVec;
    }

    bool belongsToSet(unordered_set<string>& wordSet, string word) {
        return wordSet.find(word) != wordSet.end();
    }

    int findShortestDist(unordered_set<string>& allWordSet, string beginWord, string endWord) {
        int wordLen = beginWord.size();

        unordered_set<string> visitedWordSet;
        queue<string> que;

        visitedWordSet.insert(beginWord);
        que.push(beginWord);
        int lvlNo = 0;
        while (!que.empty()) {
            lvlNo++;

            int lvlSize = que.size();

            // printf("\n-----\nlvlNo = %d, lvlSize = %d\n-----\n", lvlNo, lvlSize);
            for (int i = 1; i <= lvlSize; i++) {
                string word = que.front();
                que.pop();
                string wordCopy = word;

                for (int j = 0; j < wordLen; j++) {
                    for (char c = 'a'; c <= 'z'; c++) {
                        // printf("updating word[%d] from %c to %c to get ", j, word.at(j), c);
                        word[j] = c;
                        // printf("%s\n", word.c_str());

                        if (word == endWord) {
                            // printf("endWord found\n");
                            return lvlNo;
                        }

                        if (belongsToSet(allWordSet, word) && !belongsToSet(visitedWordSet, word)) {
                            // printf("pushing word=%s in que\n", word.c_str());
                            que.push(word);
                            visitedWordSet.insert(word);
                        }
                    }

                    word = wordCopy;
                }
            }
        }

        return INT_MAX;
    }

    void dfs(
        unordered_set<string>& allWordSet,
        string targetWord,
        int targetLvl,
        vector<vector<string>>& ladders,
        unordered_set<string>& visitedWordSet,
        stack<string>& visitedWordStack,
        int crrLvl,
        string crrWord) {
        visitedWordStack.push(crrWord);
        visitedWordSet.insert(crrWord);

        if (crrLvl > targetLvl) {
            // nothing
        } else if (crrLvl == targetLvl) {
            if (crrWord == targetWord) {
                ladders.push_back(convertToVec(visitedWordStack));
            }
        } else {
            int wordLen = targetWord.size();

            string wordCopy = crrWord;
            for (int j = 0; j < wordLen; j++) {
                for (char c = 'a'; c <= 'z'; c++) {
                    crrWord[j] = c;

                    if (belongsToSet(allWordSet, crrWord) && !belongsToSet(visitedWordSet, crrWord)) {
                        dfs(
                            allWordSet,
                            targetWord,
                            targetLvl,
                            ladders,
                            visitedWordSet,
                            visitedWordStack,
                            crrLvl + 1,
                            crrWord);
                    }
                }

                crrWord = wordCopy;
            }
        }

        visitedWordStack.pop();
        visitedWordSet.erase(crrWord);
    }

   public:
    friend class SolutionTest;

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet = convertToSet(wordList);
        if (!belongsToSet(wordSet, endWord)) {
          return {};
        }

        int shortestDist = findShortestDist(wordSet, beginWord, endWord);
        cout << shortestDist << endl;

        if (shortestDist == INT_MAX) {
            return {};
        }

        vector<vector<string>> ladders;

        unordered_set<string> visitedWordSet;
        stack<string> visitedWordStack;

        dfs(
            wordSet,
            endWord,
            shortestDist,
            ladders,
            visitedWordSet,
            visitedWordStack,
            0,
            beginWord);

        return ladders;
    }
};

class SolutionTest {
   public:
    void testFindLadders() {
        Solution soln = Solution();
        vector<string> wordList;
        string beginWord;
        string endWord;
        vector<vector<string>> laddersOutExpected;
        vector<vector<string>> laddersOutComputed;

        beginWord = "hit";
        endWord = "cog";
        wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
        laddersOutExpected = {{"hit", "hot", "dot", "dog", "cog"}, {"hit", "hot", "lot", "log", "cog"}};
        laddersOutComputed = soln.findLadders(beginWord, endWord, wordList);
        assert(laddersOutExpected == laddersOutComputed);

        beginWord = "hit";
        endWord = "cog";
        wordList = {"hot", "dot", "dog", "lot", "log"};
        laddersOutExpected = {};
        laddersOutComputed = soln.findLadders(beginWord, endWord, wordList);
        assert(laddersOutExpected == laddersOutComputed);

        beginWord = "hot";
        endWord = "dog";
        wordList = {"hot", "dog"};
        laddersOutExpected = {};
        laddersOutComputed = soln.findLadders(beginWord, endWord, wordList);
        assert(laddersOutExpected == laddersOutComputed);

        beginWord = "hit";
        endWord = "dog";
        wordList = {"hot", "dog"};
        laddersOutExpected = {};
        laddersOutComputed = soln.findLadders(beginWord, endWord, wordList);
        assert(laddersOutExpected == laddersOutComputed);

        beginWord = "cet";
        endWord = "ism";
        wordList = {"kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob"};
        // laddersOutExpected = {};
        laddersOutComputed = soln.findLadders(beginWord, endWord, wordList);
        // assert(laddersOutExpected == laddersOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindLadders();

    return 0;
}
