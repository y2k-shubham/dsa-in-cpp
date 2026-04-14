// LeetCode-811: https://leetcode.com/problems/subdomain-visit-count/

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <utility>

#define PERIOD '.'

using namespace std;

class Solution {
private:
    // ----- step-1: build frequency map -----

    pair<string, int> splitCPDomain(string& cpdomain) {
        int spaceIdx = cpdomain.find(' ');
        int count = stoi(cpdomain.substr(0, spaceIdx));

        string name = cpdomain.substr(spaceIdx + 1);

        return {name, count};
    }

    list<string> splitDomain(string& cpdomain) {
        int len = cpdomain.size();

        list<string> subdomains;
        for (int i = len - 1; i >= 0; i--) {
            if (cpdomain.at(i) == PERIOD) {
                subdomains.push_back(cpdomain.substr(i + 1));
            }
        }

        subdomains.push_back(cpdomain);

        return subdomains;
    }

    void updateFreqs(unordered_map<string, int>& freqMap, list<string>& domains, int freq) {
        for (string domain : domains) {
            freqMap[domain] += freq;
        }
    }

    unordered_map<string, int> buildDomainFreqs(vector<string>& cpDomains) {
        unordered_map<string, int> freqMap;
        for (string cpDomain : cpDomains) {
            pair<string, int> domainAndFreq = splitCPDomain(cpDomain);

            list<string> subdomains = splitDomain(domainAndFreq.first);
            updateFreqs(freqMap, subdomains, domainAndFreq.second);
        }

        return freqMap;
    }

    // ----- step-2: generate output -----

    string createCPDomain(string domain, int freq) {
        return to_string(freq) + " " + domain;
    }

    vector<string> convertToCPDomains(unordered_map<string, int>& freqs) {
        vector<string> domains;
        domains.reserve(freqs.size());

        for (auto iter = freqs.begin(); iter != freqs.end(); iter++) {
            domains.push_back(createCPDomain(iter->first, iter->second));
        }

        return domains;
    }

public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> freqs = buildDomainFreqs(cpdomains);

        vector<string> domains = convertToCPDomains(freqs);
        return domains;
    }
};
