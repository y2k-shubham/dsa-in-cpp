// https://leetcode.com/problems/find-all-anagrams-in-a-string/
// https://www.geeksforgeeks.org/anagram-substring-search-search-permutations/
// https://practice.geeksforgeeks.org/problems/count-occurences-of-anagrams/0#_=_

/*
1
cbaebabacd abc

1
forxxorfxdofr for

2
forxxorfxdofr
for
aabaabaa
aaba

1
abacbabc abc

1
aaaaaaaaaa aaaaaaaaaaaaa
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<int> findAnagrams(string, string);
map<char, int> buildFreqMap(string, int, int);
void showMap(map<char, int>, const char *, char);
int countMatchingFreqs(map<char, int>, map<char, int>);
void outputLC(vector <int>);
void outputGFG(vector <int>);
void showStr(string, int, int);

int main() {
    int T;

    cin >> T;
    while (T-- > 0) {
        string s, p;
        cin >> s >> p;

        // map<char, int> freqMap = buildFreqMap(p, 0, ((int) p.size() - 1));
        // showMap(freqMap, "freqMap", '\n');

        vector <int> anagramIndices = findAnagrams(s, p);

        outputLC(anagramIndices);
        // outputGFG(anagramIndices);
    }

    return 0;
}

vector<int> findAnagrams(string str, string p) {
    vector<int> anagramIndices;
    int pSize = (int)p.size();

    if (str.empty() || (p.size() > str.size())) {
      return anagramIndices;
    }

    map<char, int> targetFreqMap = buildFreqMap(p, 0, pSize - 1);
    map<char, int> srcFreqMap = buildFreqMap(str, 0, pSize - 1);
    int numUniqueChars = (int) targetFreqMap.size();

    int matchCount = countMatchingFreqs(targetFreqMap, srcFreqMap);
    // showMap(targetFreqMap, "targetFreqMap", '\t');
    // printf("\nmatchCount = %d, numUniqueChars = %d\n", matchCount, numUniqueChars);
    if (matchCount == numUniqueChars) {
        // printf("found matching anagram at index 0\n");
        anagramIndices.push_back(0);
    }
    for (int i = pSize; i < str.size(); i++) {
        char outgoingChar = str.at(i - pSize);
        char incomingChar = str.at(i);

        if (outgoingChar != incomingChar) {
            srcFreqMap[outgoingChar]--;
            if (srcFreqMap.find(incomingChar) == srcFreqMap.end()) {
                srcFreqMap[incomingChar] = 1;
            } else {
                srcFreqMap[incomingChar]++;
            }

            // printf("\n-------------\n");
            // showMap(targetFreqMap, "targetFreqMap", '\t');
            /**
             * for some reason, following if expressions insert the
             * incomingChar & outgoingChar in targetFreqMap (with value 0)
             * if not already present
             */
            if (targetFreqMap[outgoingChar] != 0) {
                if (srcFreqMap[outgoingChar] == targetFreqMap[outgoingChar]) {
                  /**
                   * note that outgoing char can also create a match
                   * for instance str=abacb, & p=abc
                   *  - moving from i=1 to i=2 in str
                   *    - outgoing char = a
                   *    - previous freq of a in str [window] = 2
                   *    - new freq of a in str [window] = 1 (required)
                   */ 
                  matchCount++;
                } else if (srcFreqMap[outgoingChar] + 1 == targetFreqMap[outgoingChar]) {
                  /**
                   * - if previously outgoing character was matching and now removal of one occurence
                   *   broke it, then matchCount would go down
                   * - however matchCount wouldn't go down if outgoing character's freq
                   *   wasn't already matching
                   */
                  matchCount--;
                }
            }
            if (targetFreqMap[incomingChar] != 0) {
                if (srcFreqMap[incomingChar] == targetFreqMap[incomingChar]) {
                  matchCount++;
                } else if (srcFreqMap[incomingChar] == targetFreqMap[incomingChar] + 1) {
                  /**
                   * by same logic as above, incoming character can also create a mismatch
                   * but only when it was previously matching (and this extra incoming occurence broke it)
                   */ 
                  matchCount--;
                }
            }
        }

        // printf("\n-------------\n");
        // printf("at i=%d\n", i);
        // showStr(str, (i - pSize + 1), i);
        // printf("\noutgoingChar = str[%d] = '%c',\tsrcFreq = %d\ttargetFreq = %d\n", (i-pSize), outgoingChar, srcFreqMap[outgoingChar], targetFreqMap[outgoingChar]);
        // printf("incomingChar = str[%d] = '%c',\tsrcFreq = %d\ttargetFreq = %d\n", i, incomingChar, srcFreqMap[incomingChar], targetFreqMap[incomingChar]);
        // printf("\nmatchCount = %d\n", matchCount);

        // showMap(targetFreqMap, "targetFreqMap", '\t');
        // printf("\nmatchCount = %d, numUniqueChars = %d\n", matchCount, numUniqueChars);
        if (matchCount == numUniqueChars) {
          // printf("found matching anagram at index %d\n", (i - pSize + 1));
          anagramIndices.push_back(i - pSize + 1);
        }
    }
    
    return anagramIndices;
}

int countMatchingFreqs(map<char, int> freqMap1, map<char, int> freqMap2) {
    int count = 0;
    for (map<char, int>::iterator it = freqMap1.begin(); it != freqMap1.end(); it++) {
        char c = (*it).first;
        int freq1 = (*it).second;

        if (freqMap2.find(c) != freqMap2.end()) {
            int freq2 = freqMap2[c];
            if (freq1 == freq2) {
                count++;
            }
        }
    }
    return count;
}

void outputLC(vector <int> anagramIndices) {
  if (!anagramIndices.empty()) {
    printf("[");
    printf("%d", anagramIndices[0]);
    for (int i = 1; i < anagramIndices.size(); i++) {
      printf(", %d", anagramIndices[i]);
    }
    printf("]\n");
  }
}

void outputGFG(vector <int> anagramIndices) {
  printf("%d\n", ((int) anagramIndices.size()));
}

map<char, int> buildFreqMap(string str, int lo, int hi) {
    map<char, int> freqMap;
    for (int i = lo; i <= hi; i++) {
        char c = str.at(i);
        if (freqMap.find(c) == freqMap.end()) {
            freqMap[c] = 1;
        } else {
            freqMap[c]++;
        }
    }
    return freqMap;
}

void showMap(map<char, int> freqMap, const char *name, char separator) {
    printf("\n%s is:-\n", name);
    for (map<char, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
        printf("%c -> %d%c", (*it).first, (*it).second, separator);
    }
    cout << endl;
}

void showStr(string str, int lo, int hi) {
    printf("\nString is:-\n");

    printf("Ind:\t");
    for (int i = 0; i < str.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Char:\t");
    for (int i = 0; i < str.size(); i++) {
        printf("%c\t", str.at(i));
    }
    cout << endl;

    printf("\t");
    for (int i = 0; i < str.size(); i++) {
        if (i == lo || i == hi) {
          printf("^\t");
        } else {
          printf("\t");
        }
    }
    cout << endl;
}
