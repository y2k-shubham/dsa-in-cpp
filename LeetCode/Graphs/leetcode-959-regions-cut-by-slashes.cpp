// https://leetcode.com/problems/regions-cut-by-slashes/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void showVec(vector<string> vec);
void showMat(vector<vector<char> > mat);
void testBuildGrid();
vector<vector<char> > buildGrid(vector<string>);

int main() {
    testBuildGrid();
    return 0;
}

void showVec(vector<string> vec) {
    int len = vec.size();

    printf("\nVec is:-\n");
    printf("Ind:\t");
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
        string str = vec[i];
        for (int j = 0; j < str.size(); j++) {
            printf("%c\t", str.at(j));
        }
        cout << endl;
    }
}

void showMat(vector<vector<char> > mat) {
    int len = mat.size();

    printf("\nMat is:-\n");
    printf("Ind:\t");
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
        for (int j = 0; j < len; j++) {
            printf("%c\t", mat[i][j]);
        }
        cout << endl;
    }
}

void testBuildGrid() {
    vector<string> in;
    vector<vector<char> > outExpected;
    vector<vector<char> > outComputed;

    in = {};
    outExpected = {};
    outComputed = buildGrid(in);
    assert(outExpected == outComputed);

    in = {""};
    outExpected = {};
    outComputed = buildGrid(in);
    assert(outExpected == outComputed);

    in = {" "};
    outExpected = {{' '}};
    outComputed = buildGrid(in);
    assert(outExpected == outComputed);

    in = {" \\", "//"};
    outExpected = {
        {' ', '\\'},
        {'/', '/'}};
    outComputed = buildGrid(in);
    assert(outExpected == outComputed);

    in = {" /\\ ", "/ / ", "\\/\\ ", " \\/ "};
    outExpected = {
        {' ', '/', '\\', ' '},
        {'/', ' ', '/', ' '},
        {'\\', '/', '\\', ' '},
        {' ', '\\', '/', ' '}};
    outComputed = buildGrid(in);
    // showMat(outExpected);
    // showMat(outComputed);
    // showVec(in);
    assert(outExpected == outComputed);
}

vector<vector<char> > buildGrid(vector<string> strGrid) {
    if (strGrid.empty() || strGrid[0].empty()) {
        return {};
    } else {
        int len = strGrid.size();
        vector<vector<char> > grid(len);

        for (int i = 0; i < len; i++) {
            vector<char> vec(len);

            string crrStr = strGrid[i];
            int k = 0;
            for (int j = 0; j < crrStr.size(); j++, k++) {
                char ch = crrStr.at(j);
                vec[k] = ch;
            }

            grid[i] = vec;
        }

        return grid;
    }
}

int regionsBySlashes(vector<string>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 1;
    } else {
    }
}
