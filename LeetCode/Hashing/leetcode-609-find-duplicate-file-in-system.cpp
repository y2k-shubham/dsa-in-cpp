// incomplete; quite shitty problem

// LeetCode-609: https://leetcode.com/problems/find-duplicate-file-in-system/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3747/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    // ref: https://stackoverflow.com/a/5888676/3679900
    vector<string> split(const std::string& txt, char ch) {
        vector<string> tokens;

        size_t pos = txt.find(ch);
        size_t initialPos = 0;

        // Decompose statement
        while (pos != std::string::npos) {
            tokens.push_back(txt.substr(initialPos, pos - initialPos));
            initialPos = pos + 1;

            pos = txt.find(ch, initialPos);
        }

        // Add the last one
        tokens.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

        return tokens;
    }

    pair<string, string> splitFileNameContent(string item) {
        vector<string> tokens = split(item, '(');

        string filename = tokens[0];

        string content = tokens[1];
        content.pop_back();

        return {filename, content};
    }

    pair<string, unordered_map<string, string>> parsePath(string vecItem) {
        vector<string> tokens = split(vecItem, ' ');

        string path = tokens[0];

        unordered_map<string, string> fileNameContentMap;
        for (int i = 0; i < tokens.size(); i++) {
            string item = tokens[i];
            pair<string, string> fileNameContent = splitFileNameContent(item);

            fileNameContentMap[fileNameContent.first] = fileNameContentMap[fileNameContent.second];
        }

        return {path, fileNameContentMap};
    }

    unordered_map<string, string> buildFileNameContentMap(vector<string>& vec) {
        unordered_map<string, string> fileNameContentMap;

        for (int i = 0; i < vec.size(); i++) {
            string vecItem = vec[i];
            pair<string, unordered_map<string, string>> parsedOutput = parsePath(vecItem);

            string path = parsedOutput.first;
            unordered_map<string, string> localFileNameContentMap = parsedOutput.second;

            for (unordered_map<string, string>::iterator it = localFileNameContentMap.begin(); it != localFileNameContentMap.end(); it++) {
                fileNameContentMap[path + "/" + it->first] = it->second;
            }
        }

        return fileNameContentMap;
    }

    void addFilesToBuckets(
        unordered_map<string, vector<string>>& contentFileMap,
        unordered_map<string, string>& fileNameContentMap) {
        for (unordered_map<string, string>::iterator it = fileNameContentMap.begin(); it != fileNameContentMap.end(); it++) {
            contentFileMap[it->second].push_back(it->first);
        }
    }

    vector<vector<string>> buildOutputVec(unordered_map<string, vector<string>>& contentFileMap) {
        vector<vector<string>> outputVec;
        for (unordered_map<string, vector<string>>::iterator it = contentFileMap.begin(); it != contentFileMap.end(); it++) {
            outputVec.push_back(it->second);
        }

        return outputVec;
    }

   public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> contentFileMap;
        unordered_map<string, string> fileNameContentMap = buildFileNameContentMap(paths);

        addFilesToBuckets(contentFileMap, fileNameContentMap);

        return buildOutputVec(contentFileMap);
    }
};
