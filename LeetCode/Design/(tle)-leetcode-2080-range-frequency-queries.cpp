// LeetCode-2080: https://leetcode.com/problems/range-frequency-queries/
// approach is correct & O(logn); yet caching of query results is required.
// even so, it is going TLE for some reason (LC submission said: 20 / 20 test cases passed, but took too long.)

#include <climits>
#include <cmath>
#include <cstdio>
#include <list>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

int findUpperBoundIdx(vector<int>& vec, int val, int lo, int hi) {
    int len = hi - lo + 1;
    if (len <= 0) {
        return INT_MAX;
    }

    int mid = (lo + hi) / 2;
    int midVal = vec[mid];

    if (midVal < val) {
        return findUpperBoundIdx(vec, val, mid + 1, hi);
    } else if (midVal == val) {
        return mid;
    } else {
        return min(findUpperBoundIdx(vec, val, lo, mid - 1), mid);
    }
}

int findLowerBoundIdx(vector<int>& vec, int val, int lo, int hi) {
    int len = hi - lo + 1;
    if (len <= 0) {
        return INT_MIN;
    }

    int mid = (lo + hi) / 2;
    int midVal = vec[mid];

    if (midVal < val) {
        return max(findLowerBoundIdx(vec, val, mid + 1, hi), mid);
    } else if (midVal == val) {
        return mid;
    } else {
        return findLowerBoundIdx(vec, val, lo, mid - 1);
    }
}

class RangeFreqQuery {
   private:
    vector<int> vec;
    unordered_map<int, list<int> > valIdxsListMap;
    unordered_map<int, vector<int> > valIdxsVecMap;
    unordered_map<string, int> queryCacheMap;

    void buildValIdxsListMap() {
        for (int i = 0; i < this->vec.size(); i++) {
            this->valIdxsListMap[this->vec[i]].push_back(i);
        }
    }

    void buildValIdxsVecMap() {
        for (
            unordered_map<int, list<int> >::iterator it = this->valIdxsListMap.begin();
            it != this->valIdxsListMap.end();
            it++) {
            int val = it->first;
            list<int> idxsList = it->second;

            vector<int> idxsVec(idxsList.begin(), idxsList.end());
            this->valIdxsVecMap[val] = idxsVec;
        }
    }

    string buildCacheKey(int left, int right, int value) {
        ostringstream oss;
        oss << left << "-" << right << "-" << value;
        return oss.str();
    }

   public:
    RangeFreqQuery(vector<int>& arr) {
        this->vec = arr;
        this->buildValIdxsListMap();
        this->buildValIdxsVecMap();
    }

    int query(int left, int right, int value) {
        string queryCacheKey = buildCacheKey(left, right, value);
        if (this->queryCacheMap.find(queryCacheKey) != this->queryCacheMap.end()) {
            return this->queryCacheMap[queryCacheKey];
        }

        if (this->valIdxsVecMap.find(value) == this->valIdxsVecMap.end()) {
            return 0;
        }

        vector<int> vec = this->valIdxsVecMap[value];
        int loIdx = findUpperBoundIdx(vec, left, 0, vec.size() - 1);
        if (loIdx == INT_MAX) {
            return 0;
        }

        int hiIdx = findLowerBoundIdx(vec, right, 0, vec.size() - 1);
        if (hiIdx == INT_MIN) {
            return 0;
        }

        int ans = hiIdx - loIdx + 1;
        this->queryCacheMap[queryCacheKey] = ans;

        return ans;
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
