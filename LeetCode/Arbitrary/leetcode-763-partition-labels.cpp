// LeetCode-763: https://leetcode.com/problems/partition-labels/
// Kevin Naughton Jr. https://www.youtube.com/watch?v=ED4ateJu86I

#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

map<char, pair<int, int> > buildFirstLastOccur(string str);
void showFirstLastOccur(map<char, pair<int, int> > firstLastOccur);
void testBuildFirstLastOccur();
map<int, set<char> > buildIndLastOccur(map<char, pair<int, int> > firstLastOccur);
list<pair<int, int> > findPartitionRanges(
    string str,
    map<char, pair<int, int> > firstLastOccur,
    map<int, set<char> > indLastOccur);
vector<int> convertRangesToSizes(list<pair<int, int> > ranges);
vector<int> partitionLabels(string S);

map<char, pair<int, int> > buildFirstLastOccur(string str) {
    map<char, pair<int, int> > firstLastOccur;
    for (int i = 0; i < str.size(); i++) {
        char c = str.at(i);

        if (firstLastOccur.find(c) == firstLastOccur.end()) {
            firstLastOccur[c] = make_pair(i, i);
        } else {
            firstLastOccur[c].second = i;
        }
    }

    return firstLastOccur;
}

void showFirstLastOccur(map<char, pair<int, int> > firstLastOccur) {
    printf("\nfirstLastOccur is:-\n");
    for (map<char, pair<int, int> >::iterator i = firstLastOccur.begin(); i != firstLastOccur.end(); i++) {
        printf("[%c] -> (%d, %d)\n", (*i).first, (*i).second.first, (*i).second.second);
    }
}

void testBuildFirstLastOccur() {
    string str;
    map<char, pair<int, int> > outExpected;
    map<char, pair<int, int> > outComputed;

    str = "";
    outExpected = {};
    outComputed = buildFirstLastOccur(str);
    assert(outExpected == outComputed);

    str = "aa";
    outExpected = {{'a', {0, 1}}};
    outComputed = buildFirstLastOccur(str);
    assert(outExpected == outComputed);

    str = "aba";
    outExpected = {{'a', {0, 2}}, {'b', {1, 1}}};
    outComputed = buildFirstLastOccur(str);
    assert(outExpected == outComputed);

    // pig=3
    // latin=5 8
    // paradigm = 8 16
    str = "piglatinparadigm";
    outExpected = {
        {'a', {4, 11}},
        {'d', {12, 12}},
        {'g', {2, 14}},
        {'i', {1, 13}},
        {'l', {3, 3}},
        {'m', {15, 15}},
        {'n', {7, 7}},
        {'p', {0, 8}},
        {'r', {10, 10}},
        {'t', {5, 5}}};
    outComputed = buildFirstLastOccur(str);
    // showFirstLastOccur(outComputed);
    assert(outExpected == outComputed);
}

map<int, set<char> > buildIndLastOccur(map<char, pair<int, int> > firstLastOccur) {
    map<int, set<char> > indLastOccur;

    for (map<char, pair<int, int> >::iterator i = firstLastOccur.begin(); i != firstLastOccur.end(); i++) {
        char c = (*i).first;
        int lastOccurInd = (*i).second.second;
        indLastOccur[lastOccurInd].insert(c);
    }

    return indLastOccur;
}

// LC-submission - speed 5 %tile, memory 7 %tile
list<pair<int, int> > findPartitionRanges(
    string str,
    map<char, pair<int, int> > firstLastOccur,
    map<int, set<char> > indLastOccur) {
    list<pair<int, int> > partitionRanges;

    int crrRangeStart = 0;
    int crrRangeMinEnd = 1;
    set <char> crrChars;
    int numCharsLeft = 0;

    for (int i = 0; i < str.size(); i++) {
        char c = str.at(i);
        if (crrChars.find(c) == crrChars.end()) {
          crrChars.insert(c);
          numCharsLeft++;
        }

        // printf("\n");
        // printf("at str[%d] = %c, numCharsLeft = %d\n", i, c, numCharsLeft);

        int cLastOccur = firstLastOccur[c].second;
        if (i == cLastOccur) {
            numCharsLeft--;
            crrChars.erase(c);

            // printf("this is last occurence of %c, decreased numCharsLeft = %d\n", c, numCharsLeft);
            if (numCharsLeft == 0) {
                // printf("since numCharsLeft = 0, pushing completed range (%d, %d) & setting newStart = %d\n", crrRangeStart, i, (i + 1));
                partitionRanges.push_back({crrRangeStart, i});
                crrRangeStart = i + 1;
            }
        }

        crrRangeMinEnd = max(crrRangeMinEnd, cLastOccur);
    }

    return partitionRanges;
}

vector<int> convertRangesToSizes(list<pair<int, int> > ranges) {
    vector<int> sizes;
    for (list<pair<int, int> >::iterator i = ranges.begin(); i != ranges.end(); i++) {
        sizes.push_back((*i).second - (*i).first + 1);
    }
    return sizes;
}

vector<int> partitionLabels(string S) {
    map<char, pair<int, int> > firstLastOccur = buildFirstLastOccur(S);
    map<int, set<char> > indLastOccur = buildIndLastOccur(firstLastOccur);

    list<pair<int, int> > partitionRanges = findPartitionRanges(S, firstLastOccur, indLastOccur);

    vector<int> sizes = convertRangesToSizes(partitionRanges);
    return sizes;
}

int main() {
    testBuildFirstLastOccur();
    partitionLabels("ababcbacadefegdehijhklij");

    return 0;
}
