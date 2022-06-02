// LeetCode-981: https://leetcode.com/problems/time-based-key-value-store/

#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

class TimeMap {
private:
    unordered_map<string, map<int, string> > keyTsValueMap;

    void showMap() {
        for (auto it = keyTsValueMap.begin(); it != keyTsValueMap.end(); it++) {
            cout << "[" << it->first << "]\t";

            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                cout << it2->first << "\t";
            }
            cout << endl;

            cout << "\t";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                cout << it2->second << "\t";
            }
            cout << endl;
        }
    }

public:
    friend class TimeMapTest;

    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        keyTsValueMap[key][timestamp] = value;
    }

    string get(string key, int timestamp) {
        if (keyTsValueMap.find(key) == keyTsValueMap.end()) {
            return "";
        }

        // creating copy of map leads to TLE!
//        map<int, string> tsValueMap = keyTsValueMap[key];
        if (keyTsValueMap[key].find(timestamp) != keyTsValueMap[key].end()) {
            return keyTsValueMap[key][timestamp];
        }

        map<int, string>::iterator it = keyTsValueMap[key].lower_bound(timestamp);
        if (it == keyTsValueMap[key].begin()) {
            return "";
        }

        it--;
        return it->second;
    }
};

class TimeMapTest {
public:
    void testTimeMap() {
        TimeMap timeMap;

        timeMap.set("foo", "bar", 1);
//        timeMap.showMap();
//        cout << "----------" << endl;
        assert(timeMap.get("monchi", -1) == "");
//        printf("asserted1\n");
//        cout << timeMap.get("foo", 1) << endl;
        assert(timeMap.get("foo", 1) == "bar");
//        printf("asserted2\n");
        assert(timeMap.get("foo", 3) == "bar");
//        printf("asserted3\n");
        assert(timeMap.get("foo", 0) == "");
        assert(timeMap.get("foo", -1243) == "");
        assert(timeMap.get("foo", 3) == "bar");

        timeMap.set("foo", "bar2", 4);
//        timeMap.showMap();
//        cout << "----------" << endl;
        assert(timeMap.get("foo1", 4) == "");
        assert(timeMap.get("foo", 4) == "bar2");
        assert(timeMap.get("foo", 5) == "bar2");

        timeMap.set("foo1", "pika", 3);
//        timeMap.showMap();
//        cout << "----------" << endl;
        assert(timeMap.get("foo1", 4) == "pika");
        assert(timeMap.get("foo1", 2) == "");
        assert(timeMap.get("foo2", 5) == "");
    }
};

int main() {
    TimeMapTest timeMapTest;

    timeMapTest.testTimeMap();

    return 0;
}

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
