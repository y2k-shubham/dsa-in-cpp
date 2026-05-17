// LeetCode-2814: https://leetcode.com/problems/minimum-time-takes-to-reach-destination-without-drowning/
//
// Acknowledgements:
// - Amazon Q (CLion plugin): helped understand priority_queue comparator implementation,
//   fixing max-heap into min-heap ordering, and other C++ idioms.
// - Kiro CLI: debugged showLand alignment (Unicode width handling), identified correctness
//   bugs (flood propagation, reach time recording, infinite loop), fixed observability
//   outputs, added dedup optimization, and documented the code with callout labels.

#include <cassert>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <functional>
#include <cstdio>
#include <iostream>

using namespace std;

#define EMPTY_ "."
#define STONE_ "X"
#define FLOODED_ "*"
#define SRC_ "S"
#define DEST_ "D"

// ------- model classes and enums -------

enum CellType {
    WATER, GRASS, STONE
};

class Node {
public:
    CellType type;
    bool isSource;
    bool isDest;

    bool isStone() {
        return type == STONE;
    }

    bool isWater() {
        return type == WATER;
    }

    bool isGrass() {
        return type == GRASS;
    }

    bool isNotWaterAndCanGetFlooded() {
        return !isWater() && !isDest && !isStone() && isGrass();
    }

    bool isReachable() {
        bool isGrassOrDest = isGrass() || isDest;
        bool isStoneOrWater = isStone() || isWater();
        return isGrassOrDest && !isStoneOrWater;
    }

    static Node ofType(CellType type) {
        return Node{type, false, false};
    }

    static Node ofSource() {
        return Node{GRASS, true, false};
    }

    static Node ofDest() {
        return Node{GRASS, false, true};
    }

    static Node flooded(Node node) {
        node.type = CellType::WATER;
        return node;
    }
};

class Time {
public:
    int reach;
    int flood;

    bool isFlooded() {
        return flood != INT_MAX;
    }

    bool isReached() {
        return reach != INT_MAX;
    }

    bool isFeasible() const {
        return reach < flood;
    }

    // ------ static construction methods -------

    static Time forNone() {
        return Time{INT_MAX, INT_MAX};
    }

    static Time forReach(int reach) {
        return Time{reach, INT_MAX};
    }

    static Time forFlood(int flood) {
        return Time{INT_MAX, flood};
    }

    static Time forBoth(int reach, int flood) {
        return Time{reach, flood};
    }

    static Time flooded(Time time, int floodTime) {
        time.flood = floodTime;
        return time;
    }

    static Time reached(Time time, int reachTime) {
        time.reach = reachTime;
        return time;
    }
};

enum ActionType {
    REACH,
    FLOOD
};

class QueItem {
public:
    int time;
    ActionType actionType;
    pair <int, int> pos;

    bool isFlood() {
        return actionType == FLOOD;
    }

    bool isReach() {
        return actionType == REACH;
    }

    static QueItem of(int time, pair<int, int> pos, ActionType actionType) {
        return QueItem{time, actionType, pos};
    }

    static QueItem ofFlood(int time, pair <int, int> pos) {
        return QueItem::of(time, pos, ActionType::FLOOD);
    }

    static QueItem ofReach(int time, pair <int, int> pos) {
        return QueItem::of(time, pos, ActionType::REACH);
    }
};

struct CompareQueItems {
    bool isASmaller(const QueItem& a, const QueItem& b) const {
        if (a.time != b.time) {
            return a.time < b.time;
        }
        if (a.actionType != b.actionType) {
            return a.actionType == FLOOD;
        }
        if (a.pos.first != b.pos.first) {
            return a.pos.first < b.pos.first;
        }
        return a.pos.second < b.pos.second;
    }

    bool operator()(const QueItem& a, const QueItem& b) const {
        bool _isASmaller = isASmaller(a, b);
        return !(_isASmaller);
    }
};

enum FloodStatus {
    ALREADY_FLOODED,
    CANT_BE_FLOODED,
    FLOODED
};

enum ReachStatus {
    DROWNED,
    REACHED,
    REACHED_ALREADY,
    REACHED_DEST
};

class Solution {
private:
    // ------- debug helpers -------

    bool debug = false;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    static const int CELL_WIDTH = 10;

    // Returns display width accounting for wide Unicode chars (emoji=2, CJK=2)
    int displayWidth(const string& s) {
        int w = 0;
        for (size_t i = 0; i < s.size(); ) {
            unsigned char c = s[i];
            if (c < 0x80) { w += 1; i += 1; }
            else if ((c & 0xE0) == 0xC0) { w += 1; i += 2; }
            else if ((c & 0xF0) == 0xE0) { w += 2; i += 3; }
            else if ((c & 0xF8) == 0xF0) { w += 2; i += 4; }
            else { w += 1; i += 1; }
        }
        return w;
    }

    void printCell(const string& content) {
        int pad = CELL_WIDTH - displayWidth(content);
        cout << content << string(max(0, pad), ' ') << "| ";
    }

    void showLand(
        vector <vector<Node>>& nodeMat,
        vector<vector<Time>>& timeMat,
        int crrTime) {
        int nrRows = nodeMat.size();
        int nrCols = nodeMat[0].size();
        int sepWidth = (CELL_WIDTH + 2) * nrCols + 6;

        printf("======== t=%d ========\n", crrTime);
        printf("Land:-\n");

        // show indices caption row
        printf("Idx:  ");
        for (int i = 0; i < nrCols; i++) {
            string idx = "[" + to_string(i) + "]";
            int pad = CELL_WIDTH + 2 - idx.size();
            cout << idx << string(max(0, pad), ' ');
        }
        cout << endl;
        // show horizontal separator
        cout << string(sepWidth, '-') << endl;

        for (int i = 0; i < nrRows; i++) {
            // show src / dst
            printf("[%d]  | ", i);
            for (int j = 0; j < nrCols; j++) {
                Node crrCellNode = nodeMat[i][j];

                if (crrCellNode.isSource)       printCell("【S】");
                else if (crrCellNode.isDest)    printCell("【D】");
                else                            printCell("");
            }
            cout << endl;

            // show reach
            printf("[%d]  | ", i);
            for (int j = 0; j < nrCols; j++) {
                Node crrCellNode = nodeMat[i][j];
                Time crrCellTime = timeMat[i][j];
                string content;

                if (crrCellTime.isReached()) {
                    if (crrCellNode.isSource) content = "🦶";
                    else content = "👣 " + to_string(crrCellTime.reach);
                    if (crrCellTime.reach == crrTime) content += "*";
                } else {
                    content = "-";
                }

                printCell(content);
            }
            cout << endl;

            // show water, flooding, stone and grass
            printf("[%d]  | ", i);
            for (int j = 0; j < nrCols; j++) {
                Node crrCellNode = nodeMat[i][j];
                Time crrCellTime = timeMat[i][j];
                string content;

                if (crrCellTime.isFlooded()) {
                    if (crrCellNode.isWater()) content = "💧";
                    else content = "💦 " + to_string(crrCellTime.flood);
                } else if (crrCellNode.isStone()) {
                    content = "🪨";
                } else if (crrCellNode.isGrass()) {
                    content = "🌱";
                } else {
                    content = "❌";
                }
                if (crrCellTime.flood == crrTime) content += "*";

                printCell(content);
            }
            cout << endl;

            // show horizontal separator
            cout << string(sepWidth, '-') << endl;
        }
    }

    void showPQue(
        priority_queue<QueItem, vector<QueItem>, CompareQueItems> pQue,
        int crrTime) {
        printf("pQue:-\n");

        while (!pQue.empty()) {
            QueItem item = pQue.top();
            pQue.pop();

            printf("  (time=%d, type=%s, coord=[%d,%d])\n", item.time,
                (item.isFlood() ? "FLOOD" : "REACH"),
                item.pos.first, item.pos.second);
        }

        printf("\n====================\n");
    }

    // ------- initial data-structures creation -------

    pair <vector <vector<Node>>, list <pair <int, int> > > createNodeMatAndGetInitCoords(vector<vector<string>>& land) {
        int nrRows = land.size();
        int nrCols = land[0].size();

        vector <vector<Node>> nodeMat(nrRows, vector<Node>(nrCols));
        list <pair <int, int> > initCoords;

        for (int i = 0; i < nrRows; i++) {
            for (int j = 0; j < nrCols; j++) {
                string cellStr = land[i][j];
                if (cellStr == FLOODED_) {
                    nodeMat[i][j] = Node::ofType(WATER);
                    initCoords.push_back({i, j});
                } else if (cellStr == STONE_) {
                    nodeMat[i][j] = Node::ofType(STONE);
                } else if (cellStr == SRC_) {
                    nodeMat[i][j] = Node::ofSource();
                    initCoords.push_back({i, j});
                } else if (cellStr == DEST_) {
                    nodeMat[i][j] = Node::ofDest();
                } else if (cellStr == EMPTY_) {
                    nodeMat[i][j] = Node::ofType(GRASS);
                } else {
                    throw logic_error("unhandled cell type: " + cellStr);
                }
            }
        }

        return {nodeMat, initCoords};
    }

    vector<vector<Time>> createTimeMat(vector <vector<Node>>& nodeMat) {
        int nrRows = nodeMat.size();
        int nrCols = nodeMat[0].size();

        vector <vector<Time>> timeMat(nrRows);
        for (int i = 0; i < nrRows; i++) {
            vector<Time> timeRow = vector<Time>(nrCols, Time::forNone());

            for (int j = 0; j < nrCols; j++) {
                if (nodeMat[i][j].isSource) {
                    timeRow[j] = Time::forReach(0);
                } else if (nodeMat[i][j].isWater()) {
                    timeRow[j] = Time::forFlood(0);
                }
            }

            timeMat[i] = timeRow;
        }

        return timeMat;
    }

    priority_queue<QueItem, vector<QueItem>, CompareQueItems> initPQue(
        vector <vector<Node>>& nodeMat,
        list <pair <int, int> >& initCoords) {
        priority_queue<QueItem, vector<QueItem>, CompareQueItems> pQue;

        for (pair <int, int> coord : initCoords) {
            if (nodeMat[coord.first][coord.second].isSource) {
                pQue.push(QueItem{0, REACH, coord});
            } else if (nodeMat[coord.first][coord.second].isWater()) {
                pQue.push(QueItem{0, FLOOD, coord});
            }
        }

        return pQue;
    }

    // ------- helpers -------

    pair <int, int> leftPos(pair <int, int> pos) {
        return {pos.first, pos.second - 1};
    }

    pair <int, int> rightPos(pair <int, int> pos) {
        return {pos.first, pos.second + 1};
    }

    pair <int, int> upPos(pair <int, int> pos) {
        return {pos.first - 1, pos.second};
    }

    pair <int, int> downPos(pair <int, int> pos) {
        return {pos.first + 1, pos.second};
    }

    // ------- actual simulation -------

    /**
     * [OPTIMIZATION] Encodes (row, col, actionType) into a unique integer for the dedup set.
     * Uses positional encoding: each (row, col) maps to a unique flat index,
     * then *2 + action distinguishes FLOOD(0) vs REACH(1) for the same cell.
     * Guarantees uniqueness as long as col < nrCols and action ∈ {0, 1}.
     */
    int encodeKey(int row, int col, int nrCols, ActionType action) {
        return (row * nrCols + col) * 2 + action;
    }

    /**
     * Floods the current cell and enqueues unflooded neighbors.
     *
     * [GOTCHA] Initial water cells (flood=0) are processed at time=0.
     * The guard `crrTime.flood < time` lets them through on first processing
     * but skips them if re-enqueued later. Using `<=` or checking isWater()
     * here would prevent flooding from ever spreading beyond initial cells.
     */
    FloodStatus floodAndFanout(
        vector <vector<Node>>& nodeMat,
        vector<vector<Time>>& timeMat,
        priority_queue<QueItem, vector<QueItem>, CompareQueItems>& pQue,
        unordered_set<int>& enqueued,
        QueItem crrItem) {
        int nrRows = nodeMat.size();
        int nrCols = nodeMat[0].size();

        int row = crrItem.pos.first;
        int col = crrItem.pos.second;
        int time = crrItem.time;

        Node crrNode = nodeMat[row][col];
        Time crrTime = timeMat[row][col];

        // [GOTCHA] strict `<` (not `<=`) — see docstring above
        if (crrTime.isFlooded() && (crrTime.flood < time)) {
            return FloodStatus::ALREADY_FLOODED;
        }
        if (crrNode.isDest) {
            return FloodStatus::CANT_BE_FLOODED;
        }

        // [REDUNDANT] min() is defensive — with dedup, each cell is flooded at most
        // once, so crrTime.flood should always be INT_MAX here. Kept for safety.
        Time crrFloodedTime = Time::flooded(crrTime, min(crrTime.flood, time));
        timeMat[row][col] = crrFloodedTime;

        // [OPTIMIZATION] Dedup via unordered_set before pushing to priority queue.
        // enqueued.insert(key).second is true only on first insertion,
        // preventing duplicate heap entries that waste CPU on insert (heap rebalance)
        // and later on dequeue (processed then discarded).
        if ((col > 0) && nodeMat[row][col - 1].isNotWaterAndCanGetFlooded()) {
            int key = encodeKey(row, col - 1, nrCols, FLOOD);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofFlood(time + 1, leftPos(crrItem.pos)));
            }
        }
        if ((col < nrCols - 1) && nodeMat[row][col + 1].isNotWaterAndCanGetFlooded()) {
            int key = encodeKey(row, col + 1, nrCols, FLOOD);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofFlood(time + 1, rightPos(crrItem.pos)));
            }
        }
        if ((row > 0) && nodeMat[row - 1][col].isNotWaterAndCanGetFlooded()) {
            int key = encodeKey(row - 1, col, nrCols, FLOOD);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofFlood(time + 1, upPos(crrItem.pos)));
            }
        }
        if ((row < nrRows - 1) && nodeMat[row + 1][col].isNotWaterAndCanGetFlooded()) {
            int key = encodeKey(row + 1, col, nrCols, FLOOD);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofFlood(time + 1, downPos(crrItem.pos)));
            }
        }

        return FloodStatus::FLOODED;
    }

    /**
     * Marks the current cell as reached and enqueues reachable neighbors.
     *
     * [GOTCHA] Uses min(crrTime.reach, time) to record the earliest reach time.
     * We originally had max() here, which meant an unvisited cell (reach=INT_MAX)
     * would compute max(INT_MAX, time) = INT_MAX — never recording the reach,
     * breaking both the debug display and the already-reached guard.
     */
    ReachStatus reachAndFanout(
        vector <vector<Node>>& nodeMat,
        vector<vector<Time>>& timeMat,
        priority_queue<QueItem, vector<QueItem>, CompareQueItems>& pQue,
        unordered_set<int>& enqueued,
        QueItem crrItem) {
        int nrRows = nodeMat.size();
        int nrCols = nodeMat[0].size();

        int row = crrItem.pos.first;
        int col = crrItem.pos.second;
        int time = crrItem.time;

        Node crrNode = nodeMat[row][col];
        Time crrTime = timeMat[row][col];

        // [CORRECTNESS] Cell was flooded before person arrived — drowned
        if (crrNode.isWater() || crrTime.isFlooded()) {
            return ReachStatus::DROWNED;
        }
        // [GOTCHA] Without this guard, the BFS loops forever bouncing between
        // adjacent cells in a dead end (e.g., two open cells surrounded by walls).
        if (crrTime.isReached() && (crrTime.reach < time)) {
            return ReachStatus::REACHED_ALREADY;
        }
        if (crrNode.isDest) {
            return ReachStatus::REACHED_DEST;
        }

        // [GOTCHA] Must use min(), not max(). An unvisited cell has reach=INT_MAX,
        // so max(INT_MAX, time) = INT_MAX — the reach would never be recorded,
        // causing showLand to display no movement and breaking the already-reached guard.
        Time crrReachedTime = Time::reached(crrTime, min(crrTime.reach, time));
        timeMat[row][col] = crrReachedTime;

        // [OPTIMIZATION] Dedup fan-out (same pattern as floodAndFanout)
        if ((col > 0) && nodeMat[row][col - 1].isReachable()) {
            int key = encodeKey(row, col - 1, nrCols, REACH);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofReach(time + 1, leftPos(crrItem.pos)));
            }
        }
        if ((col < nrCols - 1) && nodeMat[row][col + 1].isReachable()) {
            int key = encodeKey(row, col + 1, nrCols, REACH);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofReach(time + 1, rightPos(crrItem.pos)));
            }
        }
        if ((row > 0) && nodeMat[row - 1][col].isReachable()) {
            int key = encodeKey(row - 1, col, nrCols, REACH);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofReach(time + 1, upPos(crrItem.pos)));
            }
        }
        if ((row < nrRows - 1) && nodeMat[row + 1][col].isReachable()) {
            int key = encodeKey(row + 1, col, nrCols, REACH);
            if (enqueued.insert(key).second) {
                pQue.push(QueItem::ofReach(time + 1, downPos(crrItem.pos)));
            }
        }

        return ReachStatus::REACHED;
    }

    /**
     * Main BFS loop. Processes all items at each time step — floods first
     * (due to priority queue ordering), then reach moves. Checks after each
     * time step whether the person made any progress.
     */
    int performBFS(
        vector <vector<Node>>& nodeMat,
        list <pair <int, int> >& initCoords,
        vector<vector<Time>>& timeMat) {
        priority_queue<QueItem, vector<QueItem>, CompareQueItems> pQue = initPQue(nodeMat, initCoords);
        unordered_set<int> enqueued;

        for (int crrTime = 0; !pQue.empty(); crrTime++) {
            bool reachUpdated = false;

            while (!pQue.empty() && (pQue.top().time == crrTime)) {
                QueItem currItem = pQue.top();
                pQue.pop();

                if (currItem.isFlood()) {
                    FloodStatus floodStatus = floodAndFanout(nodeMat, timeMat, pQue, enqueued, currItem);
                } else if (currItem.isReach()) {
                    reachUpdated = true;

                    ReachStatus reachStatus = reachAndFanout(nodeMat, timeMat, pQue, enqueued, currItem);
                    if (reachStatus == REACHED_DEST) {
                        return currItem.time;
                    }
                }
            }

            if (debug) {
                showLand(nodeMat, timeMat, crrTime);
                showPQue(pQue, crrTime);
            }

            // [CORRECTNESS] Early termination: if no reach action succeeded this
            // time step, the person is either drowned or stuck with no reachable cells.
            if (!reachUpdated) {
                if (debug) {
                    printf("You got drowned 😔\n");
                }
                return -1;
            }
        }

        return -1;
    }

public:
    friend class SolutionTest;

    int minimumSeconds(vector<vector<string>>& land) {
        // ------- initial data-structures creation -------

        pair <vector <vector<Node>>, list <pair <int, int> > > nodeMatAndInitCoords = createNodeMatAndGetInitCoords(land);
        vector <vector<Node>> nodeMat = nodeMatAndInitCoords.first;
        list <pair <int, int> > initCoords = nodeMatAndInitCoords.second;

        vector<vector<Time>> timeMat = createTimeMat(nodeMat);

        // ------- Priority Queue initialization -------

        priority_queue<QueItem, vector<QueItem>, CompareQueItems> pQue = initPQue(nodeMat, initCoords);

        // ------- actual simulation -------

        return performBFS(nodeMat, initCoords, timeMat);
    }
};

class SolutionTest {
public:
    void testMinumumSeconds() {
        Solution soln = Solution();
        vector<vector<string>> landIn;
        int minSecsOutExpected, minSecsOutComputed;

        // soln.enableDebug();
        landIn = {
            {DEST_, EMPTY_, FLOODED_},
            {EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, SRC_, EMPTY_}
        };
        minSecsOutExpected = 3;
        minSecsOutComputed = soln.minimumSeconds(landIn);
        assert(minSecsOutExpected == minSecsOutComputed);
        // soln.disableDebug();

        // soln.enableDebug();
        landIn = {
            {DEST_, STONE_, FLOODED_},
            {EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, SRC_}
        };
        minSecsOutExpected = -1;
        minSecsOutComputed = soln.minimumSeconds(landIn);
        assert(minSecsOutExpected == minSecsOutComputed);
        // soln.disableDebug();

        // soln.enableDebug();
        landIn = {
            {DEST_, EMPTY_, EMPTY_, EMPTY_, FLOODED_, EMPTY_},
            {EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, SRC_, EMPTY_}
        };
        minSecsOutExpected = 6;
        minSecsOutComputed = soln.minimumSeconds(landIn);
        assert(minSecsOutExpected == minSecsOutComputed);
        // soln.disableDebug();

        // soln.enableDebug();
        landIn = {
            {STONE_, STONE_, EMPTY_},
            {DEST_, STONE_, SRC_},
            {EMPTY_, EMPTY_, STONE_}
        };
        minSecsOutExpected = -1;
        minSecsOutComputed = soln.minimumSeconds(landIn);
        assert(minSecsOutExpected == minSecsOutComputed);
        // soln.disableDebug();

        // Large TLE test case (63x80 grid) - debug disabled
        landIn = {
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, SRC_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, FLOODED_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, FLOODED_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, FLOODED_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, DEST_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, FLOODED_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, STONE_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_},
            {EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_, EMPTY_}
        };
        minSecsOutComputed = soln.minimumSeconds(landIn);
        // printf("Large test case result: %d\n", minSecsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinumumSeconds();

    return 0;
}
