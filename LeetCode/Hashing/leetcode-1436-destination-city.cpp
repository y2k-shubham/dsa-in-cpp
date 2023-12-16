// LeetCode-1436: https://leetcode.com/problems

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <unordered_set>

using namespace std;

class Solution {
private:
    // solution 1 based on in-degree and out-degree (complete, no heuristic shortcuts)
    // LC runtime 21ms, 7 %tile; memory 15.46MB, 5.39 %tile
    pair<unordered_map<string, int>, unordered_map<string, int>> buildInDegreeOutDegreeMaps(vector<vector<string>>& paths) {
        unordered_map<string, int> inDegreeMap;
        unordered_map<string, int> outDegreeMap;

        for (vector<string> path: paths) {
            inDegreeMap[path[1]]++;
            outDegreeMap[path[0]]++;
        }

        return make_pair(inDegreeMap, outDegreeMap);
    }

    string destCitySoln1(vector<vector<string>>& paths) {
        pair<unordered_map<string, int>, unordered_map<string, int>> inOutDegreeMaps = buildInDegreeOutDegreeMaps(paths);
        unordered_map<string, int> inDegreeMap = inOutDegreeMaps.first;
        unordered_map<string, int> outDegreeMap = inOutDegreeMaps.second;

        for (auto it = inDegreeMap.begin(); it != inDegreeMap.end(); it++) {
            string city = it->first;

            bool hasOneInDegree = (inDegreeMap[city] == 1);
            bool hasZeroOutDegree = (outDegreeMap.find(city) == outDegreeMap.end()) || (outDegreeMap[city] == 0);

            if (hasOneInDegree && hasZeroOutDegree) {
                return city;
            }
        }

        return "";
    }

    // solution 2 builds upon solution 1 with minor heuristics
    // LC runtime 14ms, 19.52 %tile; memory 11.82MB, 21.39 %tile
    string destCitySoln2(vector<vector<string>>& paths) {
        unordered_set<string> outDegreeCities;
        unordered_set<string> noOutDegreeCities;

        for (vector<string> path: paths) {
            string citySrc = path[0];
            string cityDest = path[1];

            noOutDegreeCities.erase(citySrc);
            outDegreeCities.insert(citySrc);

            if (outDegreeCities.find(cityDest) == outDegreeCities.end()) {
                noOutDegreeCities.insert(cityDest);
            }
        }

        if (noOutDegreeCities.size() == 1) {
            return *noOutDegreeCities.begin();
        } else {
            return "";
        }
    }

public:
    string destCity(vector<vector<string>>& paths) {
        return destCitySoln2(paths);
    }
};
