// LeetCode-399: https://leetcode.com/problems/evaluate-division/
// NeetCode: https://www.youtube.com/watch?v=Uei1fwDoyKk

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cassert>

using namespace std;

// unused
class Fraction {
private:
    int numr;
    int denr;

    int gcd(int dividend, int divisor) {
        if ((divisor == dividend) || (divisor == 1)) {
            return divisor;
        }

        int remainder = dividend % divisor;
        if (remainder == 0) {
            return divisor;
        }

        return gcd(divisor, remainder);
    }

public:
    Fraction(int numr, int denr) {
        int gcdVal = gcd(numr, denr);

        numr /= gcdVal;
        denr /= gcdVal;

        this->numr = numr;
        this->denr = denr;
    }

    int getNumr() {
        return numr;
    }

    int getDenr() {
        return denr;
    }

    Fraction inverse() {
        return Fraction(denr, numr);
    }

    static Fraction multiply(Fraction first, Fraction second) {
        int numr = first.getNumr() * second.getNumr();
        int denr = first.getDenr() * second.getDenr();

        return Fraction(numr, denr);
    }
};

class Solution {
private:
    bool debug;
    unordered_map<string, unordered_map<string, double>> graph;
    unordered_map<string, bool> visited;

    void showGraph() {
        printf("\nadjList is:-\n");
        for (auto& node: graph) {
            cout << node.first << ": ";
            for (auto& adj: node.second) {
                cout << adj.first << "(" << adj.second << ") \t";
            }
            cout << endl;
        }
        cout << endl;
    }

    void buildGraph(vector<vector<string>>& equations, vector<double>& values) {
        this->graph = {};
        this->visited = {};

        for (int i = 0; i < equations.size(); i++) {
            string src = equations[i][0];
            string dest = equations[i][1];
            double val = values[i];

            if (graph.find(src) == graph.end()) {
                graph[src] = {};
            }
            if (graph.find(dest) == graph.end()) {
                graph[dest] = {};
            }

            graph[src][dest] = val;
            graph[dest][src] = 1 / val;

            visited[src] = false;
            visited[dest] = false;
        }
    }

    inline bool isKnown(string node) {
        return graph.find(node) != graph.end();
    }

    double dfs(string src, string dest, double val) {
        if (debug) {
            printf("in dfs(src=%s, dest=%s, val=%f)\n", src.c_str(), dest.c_str(), val);
        }

        if (src == dest) {
            if (debug) {
                printf("returning result (since src=dest) %f\n", val);
            }
            return val;
        }

        if (visited[src]) {
            return -1;
        }
        visited[src] = true;

        unordered_map<string, double>& adjList = graph[src];
        if (adjList.find(dest) != adjList.end()) {
            if (debug) {
                printf("returning result (since reached next to dest) %f\n", val * adjList[dest]);
            }
            return val * adjList[dest];
        }

        for (auto& adj: adjList) {
            if (!visited[adj.first]) {
                if (debug) {
                    printf("exploring edge %s\n", adj.first.c_str());
                }
                double result = dfs(adj.first, dest, val * adj.second);

                if (result > 0) {
                    return result;
                }
            }
        }

        if (debug) {
            printf("returning -1\n");
        }
        return -1;
    }

    vector<double> calcResults(vector<vector<string>>& queries) {
        vector<double> results;

        for (auto& query: queries) {
            this->visited = {};
            string src = query[0];
            string dest = query[1];

            if (!this->isKnown(src) || !this->isKnown(dest)) {
                if (debug) {
                    printf("for query %s/%s, result is unknown\n", src.c_str(), dest.c_str());
                }
                results.push_back(-1);
                continue;
            }

            if (src == dest) {
                if (debug) {
                    printf("for query %s/%s, result is 1\n", src.c_str(), dest.c_str());
                }
                results.push_back(1);
                continue;
            }

            if (debug) {
                printf("for query %s/%s, calculating result ", src.c_str(), dest.c_str());
            }
            double result = this->dfs(src, dest, 1);
            if (debug) {
                printf("for query %s/%s, result is %f\n", src.c_str(), dest.c_str(), result);
            }
            results.push_back(result);

            if (debug) {
                printf("\n-----------\n");
            }
        }

        return results;
    }

    // unused
    vector<double> convertToDoubles(vector<Fraction>& results) {
        vector<double> ret;

        for (auto& result: results) {
            ret.push_back(result.getNumr() / (double) result.getDenr());
        }

        return ret;
    }

public:
    friend class SolutionTest;

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        buildGraph(equations, values);
        if (debug) {
            showGraph();
        }

        return calcResults(queries);
    }
};

class SolutionTest {
public:
    void testCalcEquation() {
        Solution soln = Solution();
        vector<vector<string>> equations;
        vector<double> values;
        vector<vector<string>> queries;
        vector<double> outExpected, outComputed;

        equations = {{"a", "b"},
                     {"b", "c"}};
        values = {2.0, 3.0};
        queries = {{"a", "c"},
                   {"b", "a"},
                   {"a", "e"},
                   {"a", "a"},
                   {"x", "x"}};
        outExpected = {6.0, 0.5, -1.0, 1.0, -1.0};
        outComputed = soln.calcEquation(equations, values, queries);
        assert(outExpected == outComputed);

        equations = {{"a",  "b"},
                     {"b",  "c"},
                     {"bc", "cd"}};
        values = {1.5, 2.5, 5.0, 0.2};
        queries = {{"a",  "c"},
                   {"c",  "b"},
                   {"bc", "cd"},
                   {"cd", "bc"}};
        outExpected = {3.75, 0.40, 5.0, 0.2};
        outComputed = soln.calcEquation(equations, values, queries);
        assert(outExpected == outComputed);

//        soln.debug = true;
        equations = {{"a", "b"}};
        values = {0.5};
        queries = {{"a", "b"},
                   {"b", "a"},
                   {"a", "c"},
                   {"x", "y"}};
        outExpected = {0.5, 2, -1, -1};
        outComputed = soln.calcEquation(equations, values, queries);
        assert(outExpected == outComputed);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcEquation();

    return 0;
}
