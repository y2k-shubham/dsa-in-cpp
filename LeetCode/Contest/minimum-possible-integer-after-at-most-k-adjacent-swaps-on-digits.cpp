// https://leetcode.com/contest/weekly-contest-196/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/

// solution incorrect as per given sample test cases
// but unable to understand the test case itself (i feel the last test case is wrong)

/*
In: 4321 4
Out: 1234

In: 1234 4
Out: 1234

In: 100 1
Out: 010

In: 36789 1000
Out: 36789

In: 22 22
Out: 22


// this one
In: 9438957234785635408 23
Out: 0345989723478563548
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <list>

using namespace std;

vector<int> convertToVec(string);
void showVec(vector<int>, string);
pair <set<pair<int, int> >, set<pair<int, int> > > buildInitialSets(vector<int>, int);
void showSet(set<pair<int, int> >, string);
vector<int> rearrangeDigs(vector<int>, int);
void removeDig(vector<int>, int, set<pair<int, int> >&, set<pair<int, int> >&);
void addDig(vector<int>, int, set<pair<int, int> >&, set<pair<int, int> >&);
void swapVals(vector<int>&, int, int);
string convertToString(vector<int>);
void showNumStr(vector <int> digVec, string msg);
void removeElesBeyondInd(vector<int> digVec, int startInd, set<pair<int, int> >& digIndSet, set<pair<int, int> >& indDigSet);

int main() {
    string numStrIn;
    cin >> numStrIn;

    vector<int> digVecIn = convertToVec(numStrIn);
    showVec(digVecIn, "digVec");

    int k;
    cin >> k;

    vector<int> digVecOut = rearrangeDigs(digVecIn, k);
    string numStrOut = convertToString(digVecOut);

    cout << numStrOut << endl;

    return 0;
}

vector<int> convertToVec(string numStr) {
    vector<int> digVec(numStr.size());

    for (int i = 0; i < numStr.size(); i++) {
        char c = numStr.at(i);
        int digit = c - '0';
        digVec[i] = digit;
    }

    return digVec;
}

void showVec(vector<int> vec, string name) {
    printf("\nVector %s is:-\n", name.c_str());

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
}

pair <set<pair<int, int> >, set<pair<int, int> > > buildInitialSets(vector<int> digVec, int k) {
    set<pair<int, int> > digIndSet;
    set<pair<int, int> > indDigSet;

    for (int i = 1; i < digVec.size() && i < k; i++) {
        digIndSet.insert(make_pair(digVec[i], i));
        indDigSet.insert(make_pair(i, digVec[i]));
    }

    return make_pair(digIndSet, indDigSet);
}

void showSet(set<pair<int, int> > mySet, string name) {
    printf("\n%s set is:-\n", name.c_str());

    for (set<pair<int, int> >::iterator it = mySet.begin(); it != mySet.end(); it++) {
        printf("%d -> %d\n", (*it).first, (*it).second);
    }
}

vector<int> rearrangeDigs(vector<int> digVecIn, int k) {
    ostringstream printMsg;

    pair <set<pair<int, int> >, set<pair<int, int> > > initialSets = buildInitialSets(digVecIn, k);
    set<pair<int, int> > digIndSet = initialSets.first;
    set<pair<int, int> > indDigSet = initialSets.second;
    // https://stackoverflow.com/a/4983095/3679900
    printMsg << "before loop, digIndSet";
    showSet(digIndSet, printMsg.str());
    printMsg.str("");
    printMsg << "before loop, indDigSet";
    showSet(indDigSet, printMsg.str());
    printMsg.str("");

    // output vector
    vector<int> digVecOut = digVecIn;

    int i = 0;
    while (i < digVecOut.size() - 1 && k > 0) {
        printf("\n--------------\n");
        printMsg << "before i = " << i << ", vec[" << i << "] = " << digVecOut[i] << ", k = " << k;
        showNumStr(digVecOut, printMsg.str());

        int crrDig = digVecOut[i];
        // remove current digit (candidate for replacement) from set
        removeDig(digVecOut, i, digIndSet, indDigSet);
        if (i + k < digVecOut.size()) {
            // include digit k places ahead of current digit in set
            addDig(digVecOut, i + k, digIndSet, indDigSet);
        }

        showSet(digIndSet, printMsg.str());
        showSet(indDigSet, printMsg.str());
        printMsg.str("");

        // find smallest digit from set
        pair<int, int> smallestDigIndSet = *(digIndSet.begin());
        int smallestDig = smallestDigIndSet.first;
        int smallestDigInd = smallestDigIndSet.second;

        // if replacement is expected to decrease value of number
        if (smallestDig < crrDig) {
            printf("\nswapping crrDig vec[%d] = %d with smallest dig in set vec[%d] = %d\n", i, crrDig, smallestDigInd, smallestDig);

            // remove smallest digit from set (from position pre-swapping)
            removeDig(digVecOut, smallestDigInd, digIndSet, indDigSet);

            // swap current digit with smallest digit
            swapVals(digVecOut, i, smallestDigInd);

            int jumps = smallestDigInd - i;

            // decrease k to account for k swaps
            k  = k - jumps;

            // add current digit to set (from position post-swapping)
            addDig(digVecOut, smallestDigInd, digIndSet, indDigSet);

            // remove elements beyond adjusted 'k'
            removeElesBeyondInd(digVecOut, i + k + 1, digIndSet, indDigSet);            
        }

        printMsg << "after i = " << i << ", vec[" << i << "] = " << digVecOut[i] << ", k = " << k;
        showSet(digIndSet, printMsg.str());
        showSet(indDigSet, printMsg.str());
        printMsg.str("");

        // increase index of current digit taken into consideration
        i++;
    }

    return digVecOut;
}

void removeDig(vector<int> digVec, int ind, set<pair<int, int> >& digIndSet, set<pair<int, int> >& indDigSet) {
    int dig = digVec[ind];
    pair <int, int> pairToRemove = make_pair(dig, ind);
    // this check isn't really required https://stackoverflow.com/q/4525795/3679900
    if (digIndSet.find(pairToRemove) != digIndSet.end()) {
      digIndSet.erase(pairToRemove);
      indDigSet.erase(make_pair(ind, dig));
    }
}

void addDig(vector<int> digVec, int ind, set<pair<int, int> >& digIndSet, set<pair<int, int> >& indDigSet) {
    int dig = digVec[ind];
    digIndSet.insert(make_pair(dig, ind));
    indDigSet.insert(make_pair(ind, dig));
}

void swapVals(vector<int>& vec, int ind1, int ind2) {
    int temp = vec[ind1];
    vec[ind1] = vec[ind2];
    vec[ind2] = temp;
}

string convertToString(vector<int> digVec) {
    // https://stackoverflow.com/a/1430774/3679900
    stringstream sStreamOut;
    for (int i = 0; i < digVec.size(); i++) {
        sStreamOut << digVec[i];
    }
    return sStreamOut.str();
}

void showNumStr(vector <int> digVec, string msg) {
    string numStr = convertToString(digVec);
    printf("\n%s, numStr = %s\n", msg.c_str(), numStr.c_str());
}

void removeElesBeyondInd(vector<int> digVec, int startInd, set<pair<int, int> >& digIndSet, set<pair<int, int> >& indDigSet) {
    list <pair <int, int> > indDigsToRemove;
    for (set <pair <int, int> >::iterator it = indDigSet.find(make_pair(startInd, digVec[startInd])); it != indDigSet.end(); it++) {
        indDigsToRemove.push_back(*it);
    }

    for (list <pair <int, int> >::iterator it = indDigsToRemove.begin(); it != indDigsToRemove.end(); it++) {
        pair <int, int> indDigToRemove = *it;
        digIndSet.erase(make_pair(indDigToRemove.second, indDigToRemove.first));
        indDigSet.erase(indDigToRemove);
    }
}
