// LeetCode-1024: https://leetcode.com/problems/video-stitching

#include <map>
#include <vector>
#include <set>
#include <climits>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

/**
 * Sorts in ascending order of first value
 * If first values are same, sorts in descending order of second value
 */
inline bool sortComparator(const pair <int, int>& p1, const pair <int, int>& p2) {
    if (p1.first == p2.first) {
        return p1.second >= p2.second;
    }

    return p1.first < p2.first;
}

void showVec(vector <pair <int, int>>& vec) {
    printf("\n");
    for (auto& p : vec) {
        printf("[%d %d] ", p.first, p.second);
    }
    cout << endl;
}

class Solution {
private:
    bool debug;
    int totalEventDuration;
    int clipsHiIdx;
    vector <pair <int, int>> clips;
    int maxReachedEndTime;

    void enableDebug() {
        this->debug = true;
    }

    void disableDebug() {
        this->debug = false;
    }

    void init(vector <vector <int>>& clips, int time) {
        this->totalEventDuration = time;
        this->clips.clear();

        // convert clips into vector <pair <int, int> >
        for (auto& clip : clips) {
            this->clips.push_back({clip[0], clip[1]});
        }
        sort(this->clips.begin(), this->clips.end(), &sortComparator);

        this->clipsHiIdx = 0;
        this->maxReachedEndTime = 0;
    }

    int findMaxEndTime() {
        int maxEndTime = 0;
        for (auto& clip : clips) {
            maxEndTime = max(maxEndTime, clip.second);
        }

        return maxEndTime;
    }

    inline int consumeIntervalsHavingStartTimeTill(int tillStartTime) {
        int maxEndTime = 0;
        while ((clipsHiIdx < clips.size()) && (clips[clipsHiIdx].first <= tillStartTime)) {
            maxEndTime = max(maxEndTime, clips[clipsHiIdx].second);
            clipsHiIdx++;
        }

        return maxEndTime;
    }

public:
    friend class SolutionTest;

    int videoStitching(vector <vector <int>>& clips, int time) {
        init(clips, time);
        if (this->debug) {
            showVec(this->clips);
        }

        if (this->clips.empty()) {
            if (debug) {
                printf("returning here 1\n");
            }
            return -1;
        }
        if (this->clips[0].first > 0) {
            if (debug) {
                printf("returning here 2\n");
            }
            // we have no clip interval starting from 0
            return -1;
        }
        if (findMaxEndTime() < totalEventDuration) {
            if (debug) {
                printf("returning here 3\n");
            }
            // we can't cover entire event duration
            return -1;
        }
        if (debug) {
            printf("came here 1\n");
        }

        int numIntervals = 0;
        while ((this->clipsHiIdx < this->clips.size()) && (this->maxReachedEndTime < totalEventDuration)) {
            int crrReachedEndTime = consumeIntervalsHavingStartTimeTill(this->maxReachedEndTime);
            if (crrReachedEndTime <= this->maxReachedEndTime) {
                // can't reach any further
                return -1;
            }

            this->maxReachedEndTime = crrReachedEndTime;
            ++numIntervals;
        }

        if (this->maxReachedEndTime < totalEventDuration) {
            // can't cover entire event duration
            return -1;
        }

        return numIntervals;
    }
};

class SolutionTest {
public:
    void testVideoStitching() {
        Solution soln = Solution();
        vector <vector <int>> clipsIn;
        int timeIn;
        int numClipsOutExpected, numClipsOutComputed;

        clipsIn = {};
        timeIn = 10;
        numClipsOutExpected = -1;
        numClipsOutComputed = soln.videoStitching(clipsIn, timeIn);
        assert(numClipsOutExpected == numClipsOutComputed);

        clipsIn = {{2, 5}, {3, 7}};
        timeIn = 10;
        numClipsOutExpected = -1;
        numClipsOutComputed = soln.videoStitching(clipsIn, timeIn);
        assert(numClipsOutExpected == numClipsOutComputed);

        clipsIn = {{0, 1}, {1, 2}};
        timeIn = 5;
        numClipsOutExpected = -1;
        numClipsOutComputed = soln.videoStitching(clipsIn, timeIn);
        assert(numClipsOutExpected == numClipsOutComputed);

        // soln.enableDebug();
        clipsIn = {{0, 2}, {4, 6}, {8, 10}, {1, 9}, {1, 5}, {5, 9}};
        timeIn = 10;
        numClipsOutExpected = 3;
        numClipsOutComputed = soln.videoStitching(clipsIn, timeIn);
        assert(numClipsOutExpected == numClipsOutComputed);
        // soln.disableDebug();

        clipsIn = {
            {0, 1}, {6, 8}, {0, 2}, {5, 6}, {0, 4}, {0, 3}, {6, 7}, {1, 3}, {4, 7}, {1, 4}, {2, 5}, {2, 6}, {3, 4},
            {4, 5}, {5, 7}, {6, 9}
        };
        timeIn = 9;
        numClipsOutExpected = 3;
        numClipsOutComputed = soln.videoStitching(clipsIn, timeIn);
        assert(numClipsOutExpected == numClipsOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest test = SolutionTest();

    test.testVideoStitching();

    return 0;
}
