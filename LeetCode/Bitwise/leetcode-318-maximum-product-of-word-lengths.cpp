// LeetCode-318: https://leetcode.com/problems/maximum-product-of-word-lengths/
// other than converting strings into bitmasks for O(1) comparison, it is brute-force in nature

#include <vector>
#include <string>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'z'

class Solution {
private:
    int convertToBitMask(string str) {
        int bitMask = 0;
        for (auto it = str.begin(); it != str.end(); it++) {
            bitMask |= (1 << (*it - BEGIN_CHAR));
        }

        return bitMask;
    }

    vector<int> convertToBitMaskVec(vector<string>& strVec) {
        int len = strVec.size();

        vector<int> intVec(len);
        for (int i = 0; i < len; i++) {
            intVec[i] = convertToBitMask(strVec[i]);
        }

        return intVec;
    }

    vector<pair<string, int> > zipVecs(vector<string>& strVec, vector<int>& intVec) {
        int len = strVec.size();

        vector<pair<string, int> > zipVec(len);
        for (int i = 0; i < len; i++) {
            zipVec[i] = {strVec[i], intVec[i]};
        }

        return zipVec;
    }

    int findMaxUncommonCharProd(vector<pair<string, int> >& zipVec) {
        int len = zipVec.size();
        int maxLenProd = 0;

        for (int i = 0; i < len; i++) {
            int crrWordLen = zipVec[i].first.size();
            int crrWordBitMask = zipVec[i].second;

            for (int j = i + 1; j < len; j++) {
                if ((crrWordBitMask & zipVec[j].second) == 0) {
                    int crrLenProd = crrWordLen * zipVec[j].first.size();
                    maxLenProd = max(maxLenProd, crrLenProd);
                }
            }
        }

        return maxLenProd;
    }

public:
    int maxProduct(vector<string>& words) {
        vector<int> intVec = convertToBitMaskVec(words);
        vector<pair<string, int> > zipVec = zipVecs(words, intVec);

        return findMaxUncommonCharProd(zipVec);
    }
};
