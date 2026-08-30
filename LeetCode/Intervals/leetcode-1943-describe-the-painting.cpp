// LeetCode-1943: https://leetcode.com/problems/describe-the-painting/
// Almost identical to, though slightly simpler (does NOT require merging of segments), than LeetCode-2015: https://leetcode.com/problems/average-height-of-buildings-in-each-segment/

#include <vector>
#include <map>
#include <utility>

using namespace std;

class Solution {
private:
    map <int, pair <long, int> > createSegmentsMap(vector<vector<int>>& segments) {
        map <int, pair <long, int> > segmentsMap;

        for (vector<int>& segment : segments) {
            int start = segment[0];
            int end = segment[1];
            int color = segment[2];

            segmentsMap[start].first += color;
            segmentsMap[start].second++;

            segmentsMap[end].first -= color;
            segmentsMap[end].second--;
        }

        return segmentsMap;
    }

    vector<vector<long long>> createOverlappingSegmentsVec(map <int, pair <long, int> >& segmentsMap) {
        vector<vector<long long>> overlappingSegmentsVec;

        auto it = segmentsMap.begin();
        int prevMark = it->first;
        long long prevColor = it->second.first;
        for (it++; (it != segmentsMap.end()); it++) {
            int newMark = it->first;
            long long newColor = prevColor + it->second.first;

            if (prevColor > 0) {
                pair <int, int> spanMarks = {prevMark, newMark};
                vector <long long> overlappingSegmentVal = {spanMarks.first, spanMarks.second, prevColor};
                overlappingSegmentsVec.push_back(overlappingSegmentVal);
            }

            prevMark = newMark;
            prevColor = newColor;
        }

        return overlappingSegmentsVec;
    }

    int swallowItemsTillRangesCombine(vector<vector<long long>>& overlappingSegmentsVec, int i) {
        int len = overlappingSegmentsVec.size();
        long long color = overlappingSegmentsVec[i][2];

        long long prevEnd = overlappingSegmentsVec[i][1];
        int j = i + 1;
        while (
            (j < len)                                     // bounds not violated
            && (overlappingSegmentsVec[j][2] == color)    // color is same
            && (overlappingSegmentsVec[j][0] == prevEnd)  // range is contiguous
        ) {
            prevEnd = overlappingSegmentsVec[j][1];
            j++;
        }

        return j;
    }

    vector<vector<long long>> combineRanges(vector<vector<long long>>& overlappingSegmentsVec) {
        vector<vector<long long>> combinedSegmentsVec;

        for (int i = 0; i < overlappingSegmentsVec.size(); i++) {
            pair <int, int> iSpan = {overlappingSegmentsVec[i][0], overlappingSegmentsVec[i][1]};
            long long iColor = overlappingSegmentsVec[i][2];

            int j = swallowItemsTillRangesCombine(overlappingSegmentsVec, i);

            vector <long long> span;
            if (j > (i + 1)) {
                // found range [i .. j-1] to be combined
                pair <int, int> jMinus1Span = {overlappingSegmentsVec[j-1][0], overlappingSegmentsVec[j-1][1]};
                pair <int, int> spanMarks = {iSpan.first, jMinus1Span.second};
                span = {spanMarks.first, spanMarks.second, iColor};

                // jump i to skip all ranges of merged span
                i = j - 1;
            } else {
                span = {iSpan.first, iSpan.second, iColor};
            }

            combinedSegmentsVec.push_back(span);
        }

        return combinedSegmentsVec;
    }

    vector <long long> convertToLong(vector<int>& vecOfInts) {
        int len = vecOfInts.size();
        vector <long long> vecOfLongs(len);

        for (int i = 0; i < len; i++) {
            vecOfLongs[i] = vecOfInts[i];
        }

        return vecOfLongs;
    }

public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        int numSegments = segments.size();
        if (numSegments <= 1) {
            return {convertToLong(segments[0])};
        }

        map <int, pair <long, int> > segmentsMap = createSegmentsMap(segments);

        vector <vector <long long> > overlappingSegmentsVec = createOverlappingSegmentsVec(segmentsMap);
        return overlappingSegmentsVec;

        // vector<vector<long long>> combinedSegmentsVec = combineRanges(overlappingSegmentsVec);
        // return combinedSegmentsVec;
    }
};
