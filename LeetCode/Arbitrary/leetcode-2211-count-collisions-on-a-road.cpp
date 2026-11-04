// LeetCode-2211: https://leetcode.com/problems/count-collisions-on-a-road/
// Companies: [Google][Amazon]

#include <vector>

using namespace std;

#define DIRECTION_LEFT 'L'
#define DIRECTION_RIGHT 'R'
#define DIRECTION_STATIONARY 'S'

class NextIdxNode {
private:
    int lMoveIdx;
    int rMoveIdx;
    int sIdx;

public:
    NextIdxNode() {

    }

    // ------- setters -------

    void setLMoveIdx(int lMoveIdx) {
        this->lMoveIdx = lMoveIdx;
    }

    void setRMoveIdx(int rMoveIdx) {
        this->rMoveIdx = rMoveIdx;
    }

    void setSIdx(int sIdx) {
        this->sIdx = sIdx;
    }

    // ------- getters -------

    int getLMoveIdx() {
        return lMoveIdx;
    }

    int getRMoveIdx() {
        return rMoveIdx;
    }

    int getSIdx() {
        return sIdx;
    }
};

enum Direction {
    LEFT,
    RIGHT,
    STATIONARY,
    UNKNOWN
};

class Solution {
private:
    vector <Direction> createDirectionVec(string& directionStr) {
        int len = directionStr.size();
        vector <Direction> directionVec(len);

        for (int i = 0; i < len; i++) {
            char directionCh = directionStr[i];

            Direction directionEnum;
            switch (directionCh) {
                case DIRECTION_LEFT:
                    directionEnum = Direction::LEFT;
                    break;

                case DIRECTION_RIGHT:
                    directionEnum = Direction::RIGHT;
                    break;

                case DIRECTION_STATIONARY:
                    directionEnum = Direction::STATIONARY;
                    break;

                default:
                    directionEnum = Direction::UNKNOWN;
                    break;
            }

            directionVec[i] = directionEnum;
        }

        return directionVec;
    }

    vector <NextIdxNode> createNextIdxNodeLVec(vector <Direction>& directionVec) {
        int len = directionVec.size();
        vector <NextIdxNode> nextIdxNodeLVec(len);

        int nextLMoveIdx = INT_MIN;
        int nextRMoveIdx = INT_MIN;
        int nextSIdx = INT_MIN;
        for (int i = 0; i < len; i++) {
            nextIdxNodeLVec[i].setLMoveIdx(nextLMoveIdx);
            nextIdxNodeLVec[i].setRMoveIdx(nextRMoveIdx);
            nextIdxNodeLVec[i].setSIdx(nextSIdx);

            switch (directionVec[i]) {
                case Direction::LEFT:
                    nextLMoveIdx = i;
                    break;

                case Direction::RIGHT:
                    nextRMoveIdx = i;
                    break;

                case Direction::STATIONARY:
                    nextSIdx = i;
                    break;

                default:
                    break;
            }
        }

        return nextIdxNodeLVec;
    }

    vector <NextIdxNode> createNextIdxNodeRVec(vector <Direction>& directionVec) {
        int len = directionVec.size();
        vector <NextIdxNode> nextIdxNodeRVec(len);

        int nextLMoveIdx = INT_MAX;
        int nextRMoveIdx = INT_MAX;
        int nextSIdx = INT_MAX;
        for (int i = len - 1; i >= 0; i--) {
            nextIdxNodeRVec[i].setLMoveIdx(nextLMoveIdx);
            nextIdxNodeRVec[i].setRMoveIdx(nextRMoveIdx);
            nextIdxNodeRVec[i].setSIdx(nextSIdx);

            switch (directionVec[i]) {
            case Direction::LEFT:
                nextLMoveIdx = i;
                break;

            case Direction::RIGHT:
                nextRMoveIdx = i;
                break;

            case Direction::STATIONARY:
                nextSIdx = i;
                break;

            default:
                break;
            }
        }

        return nextIdxNodeRVec;
    }

    int countCollisions(
        vector <Direction>& directionVec,
        vector <NextIdxNode>& nextIdxNodeLVec,
        vector <NextIdxNode>& nextIdxNodeRVec) {
        int len = directionVec.size();
        int numCollisions = 0;

        // left to right pass
        for (int i = 0; i < len; i++) {
            switch (directionVec[i]) {
                case Direction::STATIONARY:
                    // do nothing : collision will be counted elsewhere
                    break;

                case Direction::LEFT: {
                    int nextRMoveIdxLeft = nextIdxNodeLVec[i].getRMoveIdx();
                    int nextSIdxLeft = nextIdxNodeLVec[i].getSIdx();

                    if (max(nextRMoveIdxLeft, nextSIdxLeft) == INT_MIN) {
                        // no collision will happen
                        break;
                    } else {
                        // collision will happen
                        numCollisions++;
                    }
                    break;
                }

                case Direction::RIGHT: {
                    int nextLMoveIdxRight = nextIdxNodeRVec[i].getLMoveIdx();
                    int nextSIdxRight = nextIdxNodeRVec[i].getSIdx();

                    if (min(nextLMoveIdxRight, nextSIdxRight) == INT_MAX) {
                        // no collision will happen
                        break;
                    } else {
                        // collision will happen
                        numCollisions++;
                    }
                    break;
                }

                default:
                    // unreachable case
                    break;
            }
        }

        return numCollisions;
    }

public:
    int countCollisions(string directions) {
        int len = directions.size();
        if (len <= 1) {
            return 0;
        }

        vector <Direction> directionVec = createDirectionVec(directions);
        vector <NextIdxNode> nextIdxNodeLVec = createNextIdxNodeLVec(directionVec);
        vector <NextIdxNode> nextIdxNodeRVec = createNextIdxNodeRVec(directionVec);

        return countCollisions(directionVec, nextIdxNodeLVec, nextIdxNodeRVec);
    }
};
