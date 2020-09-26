// LeetCode-72: https://leetcode.com/problems/edit-distance/
// TusharRoy: https://www.youtube.com/watch?v=We3YDTzNXEk
// InterviewBit requires space-optimized soln https://www.interviewbit.com/problems/edit-distance/
// https://www.geeksforgeeks.org/edit-distance-dp-5/

/**
 * @file leetcode-72-edit-distance.cpp
 * @author y2k-shubham (Shubham Gupta)
 * @brief classical dynamic programming problem of minimum edit distance b/w two strings (a particular
 *        simple case of class of algorithms in NLP called Levenshtein Distance)
 * @date 2020-09-26
 * @test-cases
 *  - horse ros 3
 *  - geek gesek 1
 *  - geeks gesek 2
 *  - sunday saturday
 */

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>  // for ostringstream
#include <stack>
#include <vector>

using namespace std;

int minDistance(string str1, string str2);
vector<vector<int> > createTable(string str1, string str2);
void fillTable(string str1, string str2, vector<vector<int> >& table);
void showTable(string str1, string str2, vector<vector<int> >& table);
void showStack(string str1, string str2, stack<string> edits);
void showResults(string str1, string str2, vector<vector<int> >& table, int r, int c, stack<string>& edits);

int main() {
    string str1, str2;

    cin >> str1 >> str2;
    minDistance(str1, str2);

    return 0;
}

int minDistanceSpaceOpt(string str1, string str2) {
    int len1 = str1.size();
    int len2 = str2.size();

    vector <int> prevVec(len2 + 1);
    for (int j = 0; j <= len2; j++) {
        prevVec[j] = j;
    }

    vector <int> crrVec(len2 + 1, INT_MAX);
    for (int i = 1; i <= len1; i++) {
        char ch1 = str1.at(i - 1);

        fill(crrVec.begin(), crrVec.end(), INT_MAX);
        crrVec[0] = i;

        for (int j = 1; j <= len2; j++) {
            char ch2 = str2.at(j - 1);

            if (ch1 == ch2) {
                crrVec[j] = prevVec[j - 1];
            } else {
                int minVal = min(prevVec[j - 1], min(prevVec[j], crrVec[j - 1]));
                crrVec[j] = minVal + 1;
            }
        }

        prevVec = crrVec;
    }

    return crrVec[len2];
}

int minDistance(string str1, string str2) {
    int len1 = str1.size();
    int len2 = str2.size();

    if (len1 == 0 || len2 == 0) {
        return max(len1, len2);
    }

    vector<vector<int> > table = createTable(str1, str2);
    fillTable(str1, str2, table);

    showTable(str1, str2, table);

    int minDistance = table[len1][len2];
    cout << endl
         << "Min edit distance is " << minDistance << endl;

    stack<string> edits;
    showResults(str1, str2, table, len1, len2, edits);

    return minDistance;
}

vector<vector<int> > createTable(string str1, string str2) {
    int len1 = str1.size();
    int len2 = str2.size();

    vector<vector<int> > table(len1 + 1);
    for (int i = 0; i <= len1; i++) {
        vector<int> row(len2 + 1, INT_MIN);
        if (i == 0) {
            for (int j = 0; j <= len2; j++) {
                row[j] = j;
            }
        }
        row[0] = i;
        table[i] = row;
    }

    return table;
}

void fillTable(string str1, string str2, vector<vector<int> >& table) {
    int len1 = str1.size();
    int len2 = str2.size();

    // showTable(str1, str2, table);
    for (int i = 1; i <= len1; i++) {
        char ch1 = str1.at(i - 1);
        for (int j = 1; j <= len2; j++) {
            if (ch1 == str2.at(j - 1)) {
                table[i][j] = table[i - 1][j - 1];
            } else {
                table[i][j] = min(min(table[i - 1][j], table[i][j - 1]), table[i - 1][j - 1]) + 1;
            }
        }
        // showTable(str1, str2, table);
    }
}

void showTable(string str1, string str2, vector<vector<int> >& table) {
    cout << endl;

    int len1 = str1.size();
    int len2 = str2.size();

    printf("\t\t");
    for (int j = 0; j <= len2; j++) {
        printf("[%d]\t", j);
    }
    cout << endl;

    printf("\t\t");
    for (int j = 0; j <= len2; j++) {
        if (j > 0) {
            printf("%c\t", str2.at(j - 1));
        } else {
            printf(".\t");
        }
    }
    cout << endl;

    for (int i = 0; i <= len1; i++) {
        if (i > 0) {
            printf("[%d]\t%c\t", i, str1.at(i - 1));
        } else {
            printf("[%d]\t.\t", i);
        }

        for (int j = 0; j <= len2; j++) {
            if (table[i][j] == INT_MIN) {
                printf("-\t");
            } else {
                printf("%d\t", table[i][j]);
            }
        }
        cout << endl;
    }
}

void showStack(string str1, string str2, stack<string> edits) {
    printf("\nA possible sequence of edits to make '%s' and '%s' equal are:-\n", str1.c_str(), str2.c_str());
    while (!edits.empty()) {
        cout << edits.top() << endl;
        edits.pop();
    }
}

void showResults(string str1, string str2, vector<vector<int> >& table, int r, int c, stack<string>& edits) {
    if (r == 0 || c == 0) {
        showStack(str1, str2, edits);
    } else {
        char c1 = str1.at(r - 1);
        char c2 = str2.at(c - 1);
        ostringstream out;

        if (c1 == c2) {
            showResults(str1, str2, table, r - 1, c - 1, edits);
        } else if (r == 1 && c != 1) {
            out.str("");
            out << "delete " << c2 << " from str2=" << str2;

            edits.push(out.str());
            showResults(str1, str2, table, r, c - 1, edits);

            edits.pop();
        } else if (r != 1 && c == 1) {
            out.str("");
            out << "delete " << c1 << " from str1=" << str1;

            edits.push(out.str());
            showResults(str1, str2, table, r - 1, c, edits);

            edits.pop();
        } else {
            int minVal = min(min(table[r - 1][c], table[r][c - 1]), table[r - 1][c - 1]);

            if (table[r - 1][c] == minVal) {
                // clearing stringstream https://stackoverflow.com/a/20792/3679900
                out.str("");
                out << "delete " << c1 << " from str1=" << str1;

                edits.push(out.str());
                showResults(str1, str2, table, r - 1, c, edits);

                edits.pop();
            }

            if (table[r][c - 1] == minVal) {
                out.str("");
                out << "delete " << c2 << " from str2=" << str2;

                edits.push(out.str());
                showResults(str1, str2, table, r, c - 1, edits);

                edits.pop();
            }

            if (table[r - 1][c - 1] == minVal) {
                out.str("");
                out << "change " << c1 << " in str1=" << str1 << " to " << c2 << " in str2=" << str2;

                edits.push(out.str());
                showResults(str1, str2, table, r - 1, c - 1, edits);

                edits.pop();
            }
        }
    }
}
