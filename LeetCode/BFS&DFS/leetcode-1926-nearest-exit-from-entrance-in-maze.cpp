// LeetCode-1926: https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    inline bool isExit(vector <vector<char>> &maze, int x, int y) {
        if (maze.empty()) {
            return true;
        }

        int numRows = maze.size();
        int numCols = maze[0].size();
        if (x == 0 || x == numRows - 1 || y == 0 || y == numCols - 1) {
            return maze[x][y] == '.';
        }

        return false;
    }

    inline bool isEntrance(vector<int> &entrance, int x, int y) {
        return (entrance[0] == x) && (entrance[1] == y);
    }

    vector <vector<bool>> createBoolMat(int numRows, int numCols) {
        vector <vector<bool>> boolMat(numRows);
        for (int i = 0; i < numRows; i++) {
            vector<bool> row(numCols, false);
            boolMat[i] = row;
        }

        return boolMat;
    }

    void showMaze(vector <vector<char>> &maze) {
        int numRows = maze.size();
        int numCols = maze[0].size();

        printf("maze is:-\n");
        printf("\t");
        for (int j = 0; j < numCols; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (int i = 0; i < numRows; i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < numCols; j++) {
                printf("%c\t", maze[i][j]);
            }
            cout << endl;
        }
    }

    void showBoolMat(vector <vector<bool>> &boolMat, const char *name) {
        int numRows = boolMat.size();
        int numCols = boolMat[0].size();

        printf("%s mat is:-\n", name);
        printf("\t");
        for (int j = 0; j < numCols; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (int i = 0; i < numRows; i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < numCols; j++) {
                if (boolMat[i][j]) {
                    printf("T\t");
                } else {
                    printf("-\t");
                }
            }
            cout << endl;
        }
    }

    void showQue(queue <pair<int, int>> que) {
        printf("que is:-\n");
        while (!que.empty()) {
            pair<int, int> p = que.front();
            que.pop();
            printf("(%d, %d)\t", p.first, p.second);
        }
        cout << endl;
    }

    void showDebugOutputs(
            vector <vector<char>> &maze,
            vector <vector<bool>> &visitedMat,
            vector <vector<bool>> &enquedMat,
            queue <pair<int, int>> &que) {
        showMaze(maze);
        showBoolMat(visitedMat, "visitedMat");
        showBoolMat(enquedMat, "enquedMat");
        showQue(que);
        printf("\n----------\n");
    }

public:
    friend class SolutionTest;

    int nearestExit(vector <vector<char>> &maze, vector<int> &entrance) {
        int numRows = maze.size();
        int numCols = maze[0].size();

        queue <pair<int, int>> que;
        que.push({entrance[0], entrance[1]});

        vector <vector<bool>> visitedMat = createBoolMat(numRows, numCols);
        vector <vector<bool>> enquedMat = createBoolMat(numRows, numCols);
        enquedMat[entrance[0]][entrance[1]] = true;

        if (debug) {
            printf("\n----------\n");
            printf("before loop\n");
            showDebugOutputs(maze, visitedMat, enquedMat, que);
        }

        int steps = 0;
        while (!que.empty()) {
            int numNodes = que.size();
            for (int i = 1; i <= numNodes; i++) {
                pair<int, int> cell = que.front();
                que.pop();

                if (visitedMat[cell.first][cell.second]) {
                    continue;
                }

                visitedMat[cell.first][cell.second] = true;
                enquedMat[cell.first][cell.second] = true;

                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        // 2nd expression is important since we cant move diagonally
                        if ((i == 0 && j == 0) || (abs(i) == 1 && abs(j) == 1)) {
                            continue;
                        }

                        int x = cell.first + i;
                        int y = cell.second + j;
                        if (x < 0 || x >= numRows || y < 0 || y >= numCols) {
                            if (debug) printf("(%d, %d) returned from cond-1\n", x, y);
                            continue;
                        }

                        if (maze[x][y] == '+' || visitedMat[x][y] || enquedMat[x][y]) {
                            if (debug) printf("(%d, %d) returned from cond-2\n", x, y);
                            continue;
                        }

                        if (isExit(maze, x, y) && !isEntrance(entrance, x, y)) {
                            if (debug) printf("(%d, %d) found answer\n", x, y);
                            return steps + 1;
                        }

                        if (debug) {
                            printf("pushing (%d, %d) into queue", x, y);
                        }
                        que.push({x, y});
                    }
                }
            }

            if (debug) {
                printf("\n----------\n");
                printf("after step=%d\n", steps + 1);
                showDebugOutputs(maze, visitedMat, enquedMat, que);
            }

            steps++;
        }

        return -1;
    }
};

class SolutionTest {
public:
    void testIsExit() {
        Solution soln = Solution();
        vector <vector<char>> maze;
        int x, y;

        maze = {};
        x = 0;
        y = 0;
        assert(soln.isExit(maze, x, y) == true);

        maze = {{'+'}};
        x = 0;
        y = 0;
        assert(soln.isExit(maze, x, y) == false);

        maze = {{'.'}};
        x = 0;
        y = 0;
        assert(soln.isExit(maze, x, y) == true);

        maze = {{'+', '.'},
                {'+', '+'}};
        x = 0;
        y = 0;
        assert(soln.isExit(maze, x, y) == false);

        maze = {{'+', '.'},
                {'+', '+'}};
        x = 0;
        y = 1;
        assert(soln.isExit(maze, x, y) == true);
    }

    void testNearestExit() {
        Solution soln = Solution();
        vector <vector<char>> maze;
        vector<int> entrance;
        int ans;

        maze = {{'+', '+', '.', '+'},
                {'.', '.', '.', '+'},
                {'+', '+', '+', '.'}};
        entrance = {1, 2};
        ans = 1;
        assert(soln.nearestExit(maze, entrance) == ans);

        maze = {{'+', '+', '+'},
                {'.', '.', '.'},
                {'+', '+', '+'}};
        entrance = {1, 0};
        ans = 2;
        assert(soln.nearestExit(maze, entrance) == ans);

        maze = {{'.', '+'}};
        entrance = {0, 0};
        ans = -1;
        assert(soln.nearestExit(maze, entrance) == ans);

//        soln.debug = true;
        maze = {{{'+', '.', '+'}, {'.', '.', '.'}, {'+', '.', '+'}}};
        entrance = {1, 2};
        ans = 2;
        assert(soln.nearestExit(maze, entrance) == ans);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testIsExit();
    solnTest.testNearestExit();

    return 0;
}
