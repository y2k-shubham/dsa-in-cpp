// LeetCode-994: https://leetcode.com/problems/rotting-oranges/

#include <vector>
#include <queue>
#include <utility>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#define ROTTEN_ORANGE 2
#define FRESH_ORANGE 1
#define EMPTY_CELL 0

class Node {
public:
    pair<int, int> coord;
    int numAdjNodes;
    int enqueTime;
};

struct Comp {
    bool operator()(const Node& lhs, const Node& rhs) {
        if (lhs.numAdjNodes != rhs.numAdjNodes) {
            // we want node with higher no of adjacent nodes to get higher priority
            return lhs.numAdjNodes < rhs.numAdjNodes;
        }
        if (lhs.enqueTime != rhs.enqueTime) {
            // we want node with higher (later) enque time to get lower priority
            return lhs.enqueTime >= rhs.enqueTime;
        }
        // we want node with higher distance to get lower priority
        return (abs(lhs.coord.first) + abs(lhs.coord.second)) >= (abs(rhs.coord.first) + abs(rhs.coord.second));
    }
};

class Solution {
private:
    bool debug;
    // priority que of user-defined datatype: https://stackoverflow.com/a/19123561/3679900
//    priority_queue<Node, vector<Node>, Comp> pQue;
    queue<Node> pQue;
    vector<vector<int>> grid;
    vector<vector<bool>> queuedFlag;
    vector<vector<bool>> processedFlag;

    // debug output methods
    void showGrid() {
        printf("Grid is:-\n");

        printf("\t");
        for (int j = 0; j < grid[0].size(); j++) {
            printf("[%d]\t", j);
        }
        printf("\n");

        for (int i = 0; i < grid.size(); i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == ROTTEN_ORANGE) {
                    printf("X\t");
                } else if (grid[i][j] == FRESH_ORANGE) {
                    printf("0\t");
                } else {
                    printf(".\t");
                }
            }
            printf("\n");
        }

        printf("\n");
    }

    void showBoolMat(vector<vector<bool>>& boolMat, const char* name) {
        printf("%s is:-\n", name);

        printf("\t");
        for (int j = 0; j < boolMat[0].size(); j++) {
            printf("[%d]\t", j);
        }
        printf("\n");

        for (int i = 0; i < boolMat.size(); i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < boolMat[0].size(); j++) {
                if (boolMat[i][j]) {
                    printf("T\t");
                } else {
                    printf("F\t");
                }
            }
            printf("\n");
        }

        printf("\n");
    }

    void showQueuedAndProcessedFlags() {
        printf("Queued and processed flags are:-\n");

        printf("\t");
        for (int j = 0; j < grid[0].size(); j++) {
            printf("[%d]\t", j);
        }
        printf("\n");

        for (int i = 0; i < grid.size(); i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < grid[0].size(); j++) {
                if (processedFlag[i][j]) {
                    printf("P\t");
                } else if (queuedFlag[i][j]) {
                    printf("Q\t");
                } else {
                    printf(".\t");
                }
            }
            printf("\n");
        }

        printf("\n");
    }

    void showPQue() {
        printf("pQue is:-\n");

        printf("coord\t");
        printf("numAdjNodes\t");
        printf("enqueTime\n");

//        priority_queue<Node, vector<Node>, Comp> pQue = this->pQue;
        queue<Node> pQue = this->pQue;
        while (!pQue.empty()) {
//            Node node = pQue.top();
            Node node = pQue.front();
            pQue.pop();

            printf("(%d, %d)\t\t%d\t%d\n", node.coord.first, node.coord.second, node.numAdjNodes, node.enqueTime);
        }

        printf("\n");
    }

    void showAll(string when) {
        printf("--------%s-------\n", when.c_str());
        showGrid();
        showPQue();
        showQueuedAndProcessedFlags();
        printf("---------------\n");
    }

    // ------ initialization methods -------
    void reset() {
        while (!pQue.empty()) {
            pQue.pop();
        }

        this->queuedFlag = {};
        this->processedFlag = {};
    }

    bool init(vector<vector<int>>& grid) {
        reset();

        this->grid = grid;
        int numRows = grid.size();
        int numCols = grid[0].size();
        queuedFlag.resize(numRows, vector<bool>(numCols, false));
        processedFlag.resize(numRows, vector<bool>(numCols, false));

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (grid[i][j] == EMPTY_CELL) {
                    continue;
                }

                int numAdjacentFreshOranges = findNumAdjacentCellsOfType(i, j, FRESH_ORANGE);
                int numAdjacentRottenOranges = findNumAdjacentCellsOfType(i, j, ROTTEN_ORANGE);

                if (grid[i][j] == FRESH_ORANGE) {
                    if ((numAdjacentFreshOranges + numAdjacentRottenOranges) == 0) {
                        return true;
                    }
                }

                if (grid[i][j] == ROTTEN_ORANGE) {
                    if (numAdjacentFreshOranges == 0) {
                        if (debug) {
                            printf("found that (%d, %d) is rotten with numAdjNodes=0; marking as processed\n", i, j);
                        }
                        processedFlag[i][j] = true;
                        continue;
                    }

                    if (debug) {
                        printf("found that (%d, %d) is rotten with numAdjNodes=%d; en-queing\n", i, j, numAdjacentFreshOranges);
                    }
                    Node node = {
                            {i, j},
                            numAdjacentFreshOranges,
                            0
                    };
                    pQue.push(node);
                    queuedFlag[i][j] = true;
                }
            }
        }

        return false;
    }

    // ------ simulation methods -------
    int simulateRotting() {
        int numCycles = 0;
        if (pQue.empty()) {
            return 0;
        }

        while (!pQue.empty()) {
            bool moreNodesEnqued = simulateOneRottingCycle();
            if (moreNodesEnqued) {
                numCycles++;
            }

            if (debug) {
                string when = "after cycle ";
                when += to_string(numCycles);
                showAll(when);
            }
        }

        return numCycles;
    }

    inline bool simulateOneRottingCycle() {
        bool moreNodesEnqued = false;
        int numNewlyRottenFruits = pQue.size();

//        int newEnqueTime = pQue.top().enqueTime + 1;
        int newEnqueTime = pQue.front().enqueTime + 1;
        for (int i = 1; i <= numNewlyRottenFruits; i++) {
//            Node node = pQue.top();
            Node node = pQue.front();
            pQue.pop();

            int x = node.coord.first;
            int y = node.coord.second;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int absSum = abs(i) + abs(j);
                    if (absSum == 0 || absSum == 2) {
//                        if (debug) {
//                            printf("at (%d, %d), skipping (%d, %d) as it violates distance rule\n", x, y, i, j);
//                        }
                        continue;
                    }

                    int newX = x + i;
                    int newY = y + j;

                    if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
                        if (debug) {
                            printf("at (%d, %d), evaluating (%d, %d) for rotting\n", x, y, newX, newY);
                        }

                        if (grid[newX][newY] == FRESH_ORANGE) {
                            grid[newX][newY] = ROTTEN_ORANGE;
                            moreNodesEnqued = true;

                            int numAdjacentFreshOranges = findNumAdjacentFreshOrangesNotQued(newX, newY);
                            if (numAdjacentFreshOranges == 0) {
                                processedFlag[newX][newY] = true;
                                continue;
                            }

                            Node newNode = {
                                    {newX, newY},
                                    numAdjacentFreshOranges,
                                    newEnqueTime
                            };
                            pQue.push(newNode);
                            queuedFlag[newX][newY] = true;
                        }
                    }
                }
            }

            processedFlag[x][y] = true;
        }

        return moreNodesEnqued;
    }

    // ------ helper methods -------
    inline int findNumAdjacentCellsOfType(int x, int y, int type) {
        int numAdjNodes = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int absSum = abs(i) + abs(j);
                if (absSum == 0 || absSum == 2) {
                    continue;
                }

                int newX = x + i;
                int newY = y + j;
                if (!(newX >= 0 && newX < grid.size()) || !(newY >= 0 && newY < grid[0].size())) {
                    continue;
                }

                if (grid[newX][newY] == type) {
                    numAdjNodes++;
                }
            }
        }

        return numAdjNodes;
    }

    inline int findNumAdjacentFreshOrangesNotQued(int x, int y) {
        int numAdjNodes = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int absSum = abs(i) + abs(j);
                if (absSum == 0 || absSum == 2) {
                    continue;
                }

                int newX = x + i;
                int newY = y + j;
                if (!(newX >= 0 && newX < grid.size()) || !(newY >= 0 && newY < grid[0].size())) {
                    continue;
                }

                if (grid[newX][newY] == FRESH_ORANGE && !queuedFlag[newX][newY]) {
                    numAdjNodes++;
                }
            }
        }

        return numAdjNodes;
    }

    bool areAnyFreshOrangesLeft() {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == FRESH_ORANGE) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    friend class SolutionTest;

    int orangesRotting(vector<vector<int>>& grid) {
        bool hasUnreachableFreshOranges = init(grid);
        if (hasUnreachableFreshOranges) {
            return -1;
        }

        if (debug) {
            showAll("after init");
        }

        int numCycles = simulateRotting();
        if (debug) {
            printf("numCycles=%d\n", numCycles);
        }
        if (areAnyFreshOrangesLeft()) {
            return -1;
        } else {
            return numCycles;
        }
    }
};

class SolutionTest {
public:
    void testOrangesRotting() {
        Solution soln = Solution();
        vector<vector<int>> grid;
        int outExpected, outComputed;

//        soln.debug = true;
        grid = {{ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE},
                {FRESH_ORANGE,  FRESH_ORANGE, EMPTY_CELL},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE}};
        outExpected = 4;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);
//        soln.debug = false;

        grid = {{ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE},
                {FRESH_ORANGE,  EMPTY_CELL,   FRESH_ORANGE}};
        outExpected = -1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

//        soln.debug = true;
        grid = {{EMPTY_CELL, ROTTEN_ORANGE}};
        outExpected = 0;
        outComputed = soln.orangesRotting(grid);
//        cout << outComputed << endl;
        assert(outExpected == outComputed);
//        soln.debug = false;

        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE, EMPTY_CELL},
                {FRESH_ORANGE,  FRESH_ORANGE, EMPTY_CELL,   EMPTY_CELL},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE}
        };
        outExpected = 5;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

//        soln.debug = true;
        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE, EMPTY_CELL},
                {FRESH_ORANGE,  FRESH_ORANGE, EMPTY_CELL,   FRESH_ORANGE},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE}
        };
        outExpected = 6;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);
//        soln.debug = false;

        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE, EMPTY_CELL},
                {FRESH_ORANGE,  FRESH_ORANGE, EMPTY_CELL,   FRESH_ORANGE},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE},
                {FRESH_ORANGE,  EMPTY_CELL,   EMPTY_CELL,   EMPTY_CELL}
        };
        outExpected = -1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE, EMPTY_CELL},
                {FRESH_ORANGE,  FRESH_ORANGE, EMPTY_CELL,   FRESH_ORANGE},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE},
                {FRESH_ORANGE,  EMPTY_CELL,   EMPTY_CELL,   EMPTY_CELL},
                {FRESH_ORANGE,  FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE}
        };
        outExpected = -1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE, EMPTY_CELL},
                {FRESH_ORANGE,  FRESH_ORANGE, EMPTY_CELL,   FRESH_ORANGE},
                {EMPTY_CELL,    FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE},
                {FRESH_ORANGE,  EMPTY_CELL,   EMPTY_CELL,   FRESH_ORANGE},
                {FRESH_ORANGE,  FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE}
        };
        outExpected = 11;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

//        soln.debug = true;
        grid = {
                {ROTTEN_ORANGE, ROTTEN_ORANGE},
                {FRESH_ORANGE,  FRESH_ORANGE},
                {EMPTY_CELL,    EMPTY_CELL},
                {ROTTEN_ORANGE,  EMPTY_CELL}
        };
        outExpected = 1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);
//        soln.debug = false;

        grid = {
                {ROTTEN_ORANGE}
        };
        outExpected = 0;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {FRESH_ORANGE}
        };
        outExpected = -1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {EMPTY_CELL}
        };
        outExpected = 0;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {EMPTY_CELL, FRESH_ORANGE}
        };
        outExpected = -1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {ROTTEN_ORANGE, EMPTY_CELL, FRESH_ORANGE}
        };
        outExpected = -1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, EMPTY_CELL}
        };
        outExpected = 1;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE}
        };
        outExpected = 2;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);

        soln.debug = true;
        grid = {
                {ROTTEN_ORANGE, FRESH_ORANGE, FRESH_ORANGE, ROTTEN_ORANGE},
                {FRESH_ORANGE, EMPTY_CELL, FRESH_ORANGE, ROTTEN_ORANGE},
                {EMPTY_CELL, FRESH_ORANGE, FRESH_ORANGE, FRESH_ORANGE}
        };
        outExpected = 2;
        outComputed = soln.orangesRotting(grid);
        assert(outExpected == outComputed);
        soln.debug = false;
    }
};

int main() {
    SolutionTest test = SolutionTest();
    test.testOrangesRotting();

    return 0;
}
