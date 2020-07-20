// LeetCode 6: https://leetcode.com/problems/zigzag-conversion/
// this is very tedious to implement (with plenty of edge cases)
// read about easier way to implement

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int calcColumns(string, int);
void testCalcColumns();
vector<vector<char> > createZigZagMatrix(string, int);
void testCreateZigZagMatrix();
void showMat(vector<vector<char> > mat);
vector<int> getWordEndIndexVec(vector<vector<char> > mat);
void testGetWordEndIndexVec();
void testConvertMatToString();
string convertMatToString(vector<vector<char> >);
string convert(string, int);
void testConvert();
void testConvertMatToStringFixed();
string convertMatToStringFixed(vector<vector<char> > mat);
string convertFixed(string, int);
void testConvertFixed();

int main() {
    testCalcColumns();
    testCreateZigZagMatrix();
    testGetWordEndIndexVec();
    testConvertMatToString();
    testConvert();

    testConvertMatToStringFixed();
    testConvertFixed();

    return 0;
}

void showMat(vector<vector<char> > mat) {
    printf("\t");
    for (int j = 0; j < mat[0].size(); j++) {
        printf("[%d]\t", j);
    }
    cout << endl;

    for (int i = 0; i < mat.size(); i++) {
        printf("[%d]\t", i);
        for (int j = 0; j < mat[0].size(); j++) {
            printf("%c\t", mat[i][j]);
        }
        cout << endl;
    }
}

void testCalcColumns() {
    assert(calcColumns("PAYPALISHIRING", 2) == 7);
    assert(calcColumns("PAYPALISHIRING", 3) == 7);
    assert(calcColumns("PAYPALISHIRING", 4) == 7);
    assert(calcColumns("PAYPALISHIRING", 5) == 6);
    assert(calcColumns("TOM", 3) == 1);
    assert(calcColumns("TOMMY", 4) == 2);
    assert(calcColumns("A", 5) == 1);
}

int calcColumns(string str, int rows) {
    int len = str.size();
    int colsFull = (len / (rows + rows - 2)) * (1 + rows - 2);
    int charsPart = len % (rows + rows - 2);
    int colsPart = (charsPart == 0) ? 0 : (((charsPart / rows) > 0) ? ((charsPart / rows) + (charsPart % rows)) : 1);
    // printf("charsPart = %d, colsFull = %d, colsPart = %d\n", charsPart, colsFull, colsPart);
    return (colsFull + colsPart);
}

void testCreateZigZagMatrix() {
    vector<vector<char> > matOutExpected;

    matOutExpected = {
        {'P', 'Y', 'A', 'I', 'H', 'R', 'N'},
        {'A', 'P', 'L', 'S', 'I', 'I', 'G'}};
    assert(createZigZagMatrix("PAYPALISHIRING", 2) == matOutExpected);

    matOutExpected = {
        {'P', ' ', 'A', ' ', 'H', ' ', 'N'},
        {'A', 'P', 'L', 'S', 'I', 'I', 'G'},
        {'Y', ' ', 'I', ' ', 'R', ' ', ' '}};
    assert(createZigZagMatrix("PAYPALISHIRING", 3) == matOutExpected);

    matOutExpected = {
        {'P', ' ', ' ', 'I', ' ', ' ', 'N'},
        {'A', ' ', 'L', 'S', ' ', 'I', 'G'},
        {'Y', 'A', ' ', 'H', 'R', ' ', ' '},
        {'P', ' ', ' ', 'I', ' ', ' ', ' '}};
    assert(createZigZagMatrix("PAYPALISHIRING", 4) == matOutExpected);

    matOutExpected = {
        {'P', ' ', ' ', ' ', 'H', ' '},
        {'A', ' ', ' ', 'S', 'I', ' '},
        {'Y', ' ', 'I', ' ', 'R', ' '},
        {'P', 'L', ' ', ' ', 'I', 'G'},
        {'A', ' ', ' ', ' ', 'N', ' '}};
    assert(createZigZagMatrix("PAYPALISHIRING", 5) == matOutExpected);
}

vector<vector<char> > createZigZagMatrix(string str, int rows) {
    vector<vector<char> > mat(rows);
    int cols = calcColumns(str, rows);
    for (int i = 0; i < rows; i++) {
        vector<char> rowVec(cols, ' ');
        mat[i] = rowVec;
    }

    int i = 0;
    int j = 0;
    int c = 0;
    int crrSwitchTargetIndex = rows;
    bool verticalFlag = true;
    while (c < str.size()) {
        // printf("\n------\n");
        // printf("str[c=%d] = %c\n", c, str.at(c));
        // printf("filled mat[i=%d][j=%d] with %c\n", i, j, str.at(c));

        mat[i][j] = str.at(c);
        c++;

        // printf("\n");
        // showMat(mat);
        // printf("c incremented to %d\n", c);

        if (c == crrSwitchTargetIndex) {
            // printf("\n");
            //   printf("c equals crrSwitchTarget = %d\n", crrSwitchTargetIndex);
            crrSwitchTargetIndex += rows - 1;
            verticalFlag = !verticalFlag;
            // printf("crrSwitchTarget increased to %d\n", crrSwitchTargetIndex);
            // printf("verticalFlag = %s\n", (verticalFlag ? "true" : "false"));
        }
        // printf("\n");

        if (verticalFlag) {
            i++;
            // printf("i incremented to %d", i);

        } else {
            i--;
            j++;
            // printf("i decremeneted to %d, j incremented to %d\n", i, j);
        }
    }

    return mat;
}

void testGetWordEndIndexVec() {
    vector<int> outExpected;

    outExpected = {0, -1, -1, -1};
    assert(getWordEndIndexVec({{'A'}, {' '}, {' '}, {' '}}) == outExpected);

    outExpected = {6, 6};
    assert(getWordEndIndexVec({{'P', 'Y', 'A', 'I', 'H', 'R', 'N'},
                               {'A', 'P', 'L', 'S', 'I', 'I', 'G'}}) == outExpected);

    outExpected = {6, 6, 4};
    assert(getWordEndIndexVec({{'P', ' ', 'A', ' ', 'H', ' ', 'N'},
                               {'A', 'P', 'L', 'S', 'I', 'I', 'G'},
                               {'Y', ' ', 'I', ' ', 'R', ' ', ' '}}) == outExpected);

    outExpected = {6, 6, 4, 3};
    assert(getWordEndIndexVec({{'P', ' ', ' ', 'I', ' ', ' ', 'N'},
                               {'A', ' ', 'L', 'S', ' ', 'I', 'G'},
                               {'Y', 'A', ' ', 'H', 'R', ' ', ' '},
                               {'P', ' ', ' ', 'I', ' ', ' ', ' '}}) == outExpected);

    outExpected = {4, 4, 4, 5, 4};
    assert(getWordEndIndexVec({{'P', ' ', ' ', ' ', 'H', ' '},
                               {'A', ' ', ' ', 'S', 'I', ' '},
                               {'Y', ' ', 'I', ' ', 'R', ' '},
                               {'P', 'L', ' ', ' ', 'I', 'G'},
                               {'A', ' ', ' ', ' ', 'N', ' '}}) == outExpected);
}

vector<int> getWordEndIndexVec(vector<vector<char> > mat) {
    vector<int> indVec(mat.size(), -1);
    for (int i = 0; i < mat.size(); i++) {
        for (int j = ((int)mat[0].size() - 1); j >= 0; j--) {
            if (mat[i][j] != ' ') {
                indVec[i] = j;
                break;
            }
        }
    }
    return indVec;
}

void testConvertMatToString() {
    // printf("'%s'\n", convertMatToString({{'P', 'Y', 'A', 'I', 'H', 'R', 'N'},
    //                              {'A', 'P', 'L', 'S', 'I', 'I', 'G'}}).c_str());
    assert(convertMatToString({{'P', 'Y', 'A', 'I', 'H', 'R', 'N'},
                               {'A', 'P', 'L', 'S', 'I', 'I', 'G'}}) == "PYAIHRN\nAPLSIIG");
    assert(convertMatToString({{'P', ' ', 'A', ' ', 'H', ' ', 'N'},
                               {'A', 'P', 'L', 'S', 'I', 'I', 'G'},
                               {'Y', ' ', 'I', ' ', 'R', ' ', ' '}}) == "P A H N\nAPLSIIG\nY I R");
    assert(convertMatToString({{'P', ' ', ' ', 'I', ' ', ' ', 'N'},
                               {'A', ' ', 'L', 'S', ' ', 'I', 'G'},
                               {'Y', 'A', ' ', 'H', 'R', ' ', ' '},
                               {'P', ' ', ' ', 'I', ' ', ' ', ' '}}) == "P  I  N\nA LS IG\nYA HR\nP  I");
    assert(convertMatToString({{'P', ' ', ' ', ' ', 'H', ' '},
                               {'A', ' ', ' ', 'S', 'I', ' '},
                               {'Y', ' ', 'I', ' ', 'R', ' '},
                               {'P', 'L', ' ', ' ', 'I', 'G'},
                               {'A', ' ', ' ', ' ', 'N', ' '}}) == "P   H\nA  SI\nY I R\nPL  IG\nA   N");
}

string convertMatToString(vector<vector<char> > mat) {
    vector<int> endIndexVec = getWordEndIndexVec(mat);
    string str;

    for (int i = 0; i < mat.size(); i++) {
        if (endIndexVec[i] == -1) {
            break;
        }

        for (int j = 0; j <= endIndexVec[i]; j++) {
            str = str + mat[i][j];
        }
        str = str + '\n';
    }

    if (str.at(str.size() - 1) == '\n') {
        str = str.substr(0, str.size() - 1);
    }

    return str;
}

void testConvert() {
    assert(convert("PAYPALISHIRING", 2) == "PYAIHRN\nAPLSIIG");
    assert(convert("PAYPALISHIRING", 3) == "P A H N\nAPLSIIG\nY I R");
    assert(convert("PAYPALISHIRING", 4) == "P  I  N\nA LS IG\nYA HR\nP  I");
    assert(convert("PAYPALISHIRING", 5) == "P   H\nA  SI\nY I R\nPL  IG\nA   N");
    assert(convert("TOM", 3) == "T\nO\nM");
    assert(convert("TOM", 2) == "TM\nO");
    assert(convert("TOMMY", 2) == "TMY\nOM");
    assert(convert("TOMMY", 3) == "T Y\nOM\nM");
    assert(convert("A", 5) == "A");
    // printf("'%s'\n", convert("ABCD", 5).c_str());
    assert(convert("ABCD", 5) == "A\nB\nC\nD");
}

string convert(string s, int numRows) {
    if (numRows == 1) {
        return s;
    } else {
        vector<vector<char> > mat = createZigZagMatrix(s, numRows);
        return convertMatToString(mat);
    }
}

void testConvertMatToStringFixed() {
    assert(convertMatToStringFixed({{'P', 'Y', 'A', 'I', 'H', 'R', 'N'},
                                    {'A', 'P', 'L', 'S', 'I', 'I', 'G'}}) == "PYAIHRNAPLSIIG");
    assert(convertMatToStringFixed({{'P', ' ', 'A', ' ', 'H', ' ', 'N'},
                                    {'A', 'P', 'L', 'S', 'I', 'I', 'G'},
                                    {'Y', ' ', 'I', ' ', 'R', ' ', ' '}}) == "PAHNAPLSIIGYIR");
    assert(convertMatToStringFixed({{'P', ' ', ' ', 'I', ' ', ' ', 'N'},
                                    {'A', ' ', 'L', 'S', ' ', 'I', 'G'},
                                    {'Y', 'A', ' ', 'H', 'R', ' ', ' '},
                                    {'P', ' ', ' ', 'I', ' ', ' ', ' '}}) == "PINALSIGYAHRPI");
    assert(convertMatToStringFixed({{'P', ' ', ' ', ' ', 'H', ' '},
                                    {'A', ' ', ' ', 'S', 'I', ' '},
                                    {'Y', ' ', 'I', ' ', 'R', ' '},
                                    {'P', 'L', ' ', ' ', 'I', 'G'},
                                    {'A', ' ', ' ', ' ', 'N', ' '}}) == "PHASIYIRPLIGAN");
}

string convertMatToStringFixed(vector<vector<char> > mat) {
    vector<int> endIndexVec = getWordEndIndexVec(mat);
    string str;

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j <= endIndexVec[i]; j++) {
            if (mat[i][j] != ' ') {
                str = str + mat[i][j];
            }
        }
    }

    if (str.at(str.size() - 1) == '\n') {
        str = str.substr(0, str.size() - 1);
    }

    return str;
}

void testConvertFixed() {
    assert(convertFixed("PAYPALISHIRING", 2) == "PYAIHRNAPLSIIG");
    assert(convertFixed("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    assert(convertFixed("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
    assert(convertFixed("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");
    assert(convertFixed("TOM", 3) == "TOM");
    assert(convertFixed("TOM", 2) == "TMO");
    assert(convertFixed("TOMMY", 2) == "TMYOM");
    assert(convertFixed("TOMMY", 3) == "TYOMM");
    assert(convertFixed("A", 5) == "A");
    assert(convertFixed("ABCD", 5) == "ABCD");
}

string convertFixed(string s, int numRows) {
    if (numRows == 1) {
        return s;
    } else {
        vector<vector<char> > mat = createZigZagMatrix(s, numRows);
        return convertMatToStringFixed(mat);
    }
}
