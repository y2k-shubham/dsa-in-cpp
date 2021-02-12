// LeetCode-1640: https://leetcode.com/problems/check-array-formation-through-concatenation/

/**
 * @file leetcode-1640-check-array-formation-through-concatenation.cpp
 * @author y2k-shubham
 * @brief pretty tough normally; outright stupid when you read the constraints
 *         (a) 1 <= pieces.length <= arr.length <= 100
 *         (b) The integers in arr are distinct
 *         Most likely even hashing wont be needed, brute force should also work
 * @date 2021-02-12
 */

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    unordered_map<int, int> buildEleIndMap(vector<int>& vec) {
        unordered_map<int, int> eleIndMap;

        for (int i = 0; i < vec.size(); i++) {
            eleIndMap[vec[i]] = i;
        }

        return eleIndMap;
    }

    bool consumeEles(vector<int>& arr, vector<int>& piece, int startIdx, vector<bool>& arrConsumed) {
        int iArr = startIdx;
        int iPiece = 0;

        while (iPiece < piece.size()) {
            if ((arr[iArr] == piece[iPiece]) && (arrConsumed[iArr] == false)) {
                arrConsumed[iArr] = true;
            } else {
                return false;
            }

            iPiece++;
            iArr++;
        }

        return true;
    }

    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        int arrLen = arr.size();
        vector<bool> arrConsumed(arrLen, false);

        unordered_map<int, int> eleIndMap = buildEleIndMap(arr);

        for (int i = 0; i < pieces.size(); i++) {
            vector<int> piece = pieces[i];

            if (eleIndMap.find(piece[0]) == eleIndMap.end()) {
                return false;
            } else {
                if (!consumeEles(arr, piece, eleIndMap[piece[0]], arrConsumed)) {
                    return false;
                }
            }
        }

        return true;
    }
};
