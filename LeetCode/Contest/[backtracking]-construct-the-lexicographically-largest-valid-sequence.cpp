// https://leetcode.com/contest/biweekly-contest-43/problems/construct-the-lexicographically-largest-valid-sequence/
// medium; back-tracking / pure brute-force

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
   public:
    bool debug = false;

    void showSeq(vector<int>& seq, vector<bool>& filledPosns) {
        int seqLen = seq.size();

        printf("Ind:\t");
        for (int i = 0; i < seqLen; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < seqLen; i++) {
            if (filledPosns[i]) {
                printf("%d\t", seq[i]);
            } else {
                printf("\t");
            }
        }
        cout << endl;
    }

    bool buildSeq(vector<int>& seq, vector<bool>& filledPosns, set<int>& unfilledNums) {
        int seqLen = seq.size();

        if (unfilledNums.empty()) {
            return true;
        } else {
            int posnToFill;
            for (posnToFill = 0; (posnToFill < seqLen) && filledPosns[posnToFill]; posnToFill++)
                ;
            if (posnToFill >= seqLen) {
                return false;
            }

            if (!unfilledNums.empty()) {
                for (set<int>::reverse_iterator it = unfilledNums.rbegin(); it != unfilledNums.rend(); it++) {
                    int crrNum = *it;

                    if (debug) {
                        printf("\nat posnToFill=%d, trying to fill crrNum=%d\n", posnToFill, crrNum);
                    }

                    if (crrNum > 1) {
                        if (debug) {
                            printf("filledPosns[posnToFill=%d] = %s, filledPosns[posnToFill=%d + crrNum=%d = %d] = %s\n", posnToFill, (filledPosns[posnToFill] ? "true" : "false"), posnToFill, crrNum, (posnToFill + crrNum), (filledPosns[posnToFill + crrNum] ? "true" : "false"));
                        }

                        if (posnToFill + crrNum < seqLen && !filledPosns[posnToFill] && !filledPosns[posnToFill + crrNum]) {
                            seq[posnToFill] = crrNum;
                            seq[posnToFill + crrNum] = crrNum;

                            filledPosns[posnToFill] = true;
                            filledPosns[posnToFill + crrNum] = true;

                            set<int> unfilledNumsCopy = unfilledNums;
                            unfilledNumsCopy.erase(crrNum);

                            if (debug) {
                                printf("filled crrNum=%d, moving ahead\n\n", crrNum);
                                showSeq(seq, filledPosns);
                            }

                            if (buildSeq(seq, filledPosns, unfilledNumsCopy)) {
                                return true;
                            } else {
                                filledPosns[posnToFill] = false;
                                filledPosns[posnToFill + crrNum] = false;
                            }
                        }
                    } else {
                        if (debug) {
                            printf("filledPosns[posnToFill=%d] = %s\n", posnToFill, (filledPosns[posnToFill] ? "true" : "false"));
                        }

                        if (!filledPosns[posnToFill]) {
                            seq[posnToFill] = 1;
                            filledPosns[posnToFill] = true;

                            set<int> unfilledNumsCopy = unfilledNums;
                            unfilledNumsCopy.erase(1);

                            if (debug) {
                                printf("filled crrNum=%d, moving ahead\n\n", crrNum);
                                showSeq(seq, filledPosns);
                            }

                            if (buildSeq(seq, filledPosns, unfilledNumsCopy)) {
                                return true;
                            } else {
                                filledPosns[posnToFill] = false;
                            }
                        }
                    }
                }
            }

            return false;
        }
    }

    vector<int> constructDistancedSequence(int n) {
        int seqLen = (n - 1) * 2 + 1;
        vector<int> seq(seqLen);
        vector<bool> filledPosns(seqLen, false);

        set<int> unfilledNums;
        for (int i = 1; i <= n; i++) {
            unfilledNums.insert(i);
        }

        buildSeq(seq, filledPosns, unfilledNums);

        return seq;
    }
};