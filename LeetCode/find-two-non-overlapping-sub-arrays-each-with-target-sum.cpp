// https://leetcode.com/contest/biweekly-contest-28/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/

/*
 - could get all cases passed
 - started showing following error on 51st test case (last one here, output 16)
Line 1633: rapidjson::SizeType rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> >::Size() const [Encoding = rapidjson::UTF8<char>, Allocator = rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>]: Assertion `IsArray()' failed. (document.h)
*/

/*
Example 1:

Input: arr = [3,2,2,4,3], target = 3
Output: 2
Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
Example 2:

Input: arr = [7,3,4,7], target = 7
Output: 2
Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
Example 3:

Input: arr = [4,3,2,6,2,3,4], target = 6
Output: -1
Explanation: We have only one sub-array of sum = 6.
Example 4:

Input: arr = [5,5,4,4,5], target = 3
Output: -1
Explanation: We cannot find a sub-array of sum = 3.
Example 5:

Input: arr = [3,1,1,1,5,1,2,1], target = 3
Output: 3
Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.

Input: arr = [47,17,4,8,8,2,1,1,8,35,30,1,11,1,1,1,44,1,3,27,2,8], target = 88
Output: 16
*/

#include <climits>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int minSumOfLengths(vector<int> &arr, int target);
map<int, set<pair<int, int> > > buildSubarrMap(vector<int> arr, int target);
int findMinLenSum(map<int, set<pair<int, int> > > allRangesMap);
set<pair<int, int> > buildAllRangesSet(map<int, set<pair<int, int> > > allRangesMap);
void showSet(vector<int> &arr, set<pair<int, int> > &crrSet);
void showMap(vector<int> &arr, map<int, set<pair<int, int> > > &allRangesMap);
void showVec(vector<int>, const char *);

int main() {
    // g++ -std=c++11 find-all-anagrams-in-a-string.cpp
    std::vector<int> vec = {47, 17, 4, 8, 8, 2, 1, 1, 8, 35, 30, 1, 11, 1, 1, 1, 44, 1, 3, 27, 2, 8};
    int target = 88;

    // showVec(vec, "vec");
    cout << minSumOfLengths(vec, target) << endl;

    return 0;
}

int minSumOfLengths(vector<int> &arr, int target) {
    map<int, set<pair<int, int> > > allRangesMap = buildSubarrMap(arr, target);

    // printf("\n============\nallSets are:-\n");
    // showMap(arr, allRangesMap);

    return findMinLenSum(allRangesMap);
}

map<int, set<pair<int, int> > > buildSubarrMap(vector<int> arr, int target) {
    map<int, set<pair<int, int> > > allRangesMap;
    int i, j;
    int crrSum;

    int len = (int)arr.size();
    i = j = 0;
    crrSum = arr[0];
    while (i < len && j < len) {
        // printf("\n--------------\n");
        // showVec(arr, "arr");
        // showMap(arr, allRangesMap);
        // printf("arr[i=%d]=%d .. arr[j=%d]=%d\t(len=%d)\tcrrSum=%d\n", i, arr[i], j, arr[j], (j - i + 1), crrSum);

        if (crrSum < target) {
            j++;
            if (j < len) {
                crrSum += arr[j];
            }
            // printf("incremented j\n");
        } else if (crrSum == target) {
            int crrRangeLen = (j - i + 1);
            if (allRangesMap.find(crrRangeLen) == allRangesMap.end()) {
                set<pair<int, int> > newSet;
                newSet.insert(make_pair(i, j));
                allRangesMap[crrRangeLen] = newSet;
                // printf("found target subarray arr[i=%d]=%d .. arr[j=%d]=%d of new           length = %d\n", i, arr[i], j, arr[j], crrRangeLen);
            } else {
                allRangesMap[crrRangeLen].insert(make_pair(i, j));
                // printf("found target subarray arr[i=%d]=%d .. arr[j=%d]=%d of already known length = %d\n", i, arr[i], j, arr[j], crrRangeLen);
            }

            // increment i
            crrSum -= arr[i];
            i++;
        } else {
            crrSum -= arr[i];
            i++;
            // printf("incremented i\n");
        }
    }

    return allRangesMap;
}

int findMinLenSum(map<int, set<pair<int, int> > > allRangesMap) {
    set<pair<int, int> > allRangesSet = buildAllRangesSet(allRangesMap);

    for (set <pair <int, int> >::iterator i = allRangesSet.begin(); i != allRangesSet.end(); i++) {
      pair <int, int> crrFirstRange = *i;
      int crrFirstRangeSize = crrFirstRange.second - crrFirstRange.first + 1;

      map<int, set<pair<int, int> > > allRangesMapCopy = allRangesMap;
      allRangesMapCopy[crrFirstRangeSize].erase(crrFirstRange);
      if (allRangesMapCopy[crrFirstRangeSize].empty()) {
        allRangesMapCopy.erase(crrFirstRangeSize);
      }

      for (map<int, set<pair<int, int> > >::iterator i = allRangesMapCopy.begin(); i != allRangesMapCopy.end(); i++) {
        set<pair<int, int> > crrSet = (*i).second;
        for (set<pair<int, int> >::iterator j = crrSet.begin(); j != crrSet.end(); j++) {
            pair<int, int> crrSecondRange = *j;
            int crrSecondRangeSize = crrSecondRange.second - crrSecondRange.first + 1;

            if (crrFirstRange.second < crrSecondRange.first) {
              return (crrFirstRangeSize + crrSecondRangeSize);
            }
        }
      }
    }

    return -1;
}

set<pair<int, int> > buildAllRangesSet(map<int, set<pair<int, int> > > allRangesMap) {
    set<pair<int, int> > allRangesSet;
    for (map<int, set<pair<int, int> > >::iterator i = allRangesMap.begin(); i != allRangesMap.end(); i++) {
        int crrFirstRangeSize = (*i).first;
        set<pair<int, int> > crrSet = (*i).second;
        for (set<pair<int, int> >::iterator j = crrSet.begin(); j != crrSet.end(); j++) {
            pair<int, int> crrFirstRange = *j;
            allRangesSet.insert(crrFirstRange);
        }
    }
    return allRangesSet;
}

void showSet(vector<int> &arr, set<pair<int, int> > &crrSet) {
    // printf("crrSet is:-\n");
    for (set<pair<int, int> >::iterator j = crrSet.begin(); j != crrSet.end(); j++) {
        pair<int, int> crrEle = *j;
        int crrBegin = crrEle.first;
        int crrEnd = crrEle.second;
        printf("\tarr[i=%d]=%d .. arr[j=%d]=%d\n", crrBegin, arr[crrBegin], crrEnd, arr[crrEnd]);
    }
    cout << endl;
}

void showMap(vector<int> &arr, map<int, set<pair<int, int> > > &allRangesMap) {
    printf("allRangesMap are:-\n");
    for (map<int, set<pair<int, int> > >::iterator i = allRangesMap.begin(); i != allRangesMap.end(); i++) {
        printf("len=%d:\n", (*i).first);
        set<pair<int, int> > crrSet = (*i).second;
        showSet(arr, crrSet);
    }
    cout << endl;
    cout << endl;
}

void showVec(vector<int> vec, const char *name) {
    printf("\nVector %s is:-\n", name);

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
    cout << endl;
}
