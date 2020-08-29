// LeetCode-321: https://leetcode.com/problems/create-maximum-number/
// Wrong soln (fails in one of the sample test-cases itself)

#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

void showVec(vector <int> vec, int minInd, int maxPermInd, string which);
void showIndMap(map<int, pair<set<int>, set<int> > >& indMap, string when);
map<int, pair<set<int>, set<int> > > buildIndMap(vector<int>& vec1, vector<int>& vec2);
list<int> findElesLessThan(set<int>& mSet, int ele);
void dropKeys(map<int, pair<set<int>, set<int> > >& indMap, list <int> keysToDrop);
void dropEles(set<int>& mSet, list<int> elesToDrop);
void dropIndsFirst(map<int, pair<set<int>, set<int> > >& indMap, int idx);
void dropIndsSecond(map<int, pair<set<int>, set<int> > >& indMap, int idx);
int getValidInd(set<int>& indSet, int idx);
int getValidIndFirst(map<int, pair<set<int>, set<int> > >& indMap, int ele, int idx);
int getValidIndSecond(map<int, pair<set<int>, set<int> > >& indMap, int ele, int idx);
void testMaxNumberDebug();
vector<int> maxNumberDebug(vector<int>& vec1, vector<int>& vec2, int k, bool debug);
vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k);

int main() {
    testMaxNumberDebug();

    return 0;
}

// show methods

void showVec(vector <int> vec, int minInd, int maxPermInd, string which) {
    printf("\n%s vec is:-\n", which.c_str());

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

    printf("\t");
    for (int i = 0; i <= maxPermInd; i++) {
        if (i == minInd) {
            printf("^min=%d\t", minInd);
        } else if (i == maxPermInd) {
            printf("^max=%d\t", maxPermInd);
        } else {
            printf("\t");
        }
    }
    cout << endl;
}

void showIndMap(map<int, pair<set<int>, set<int> > >& indMap, string when) {
    printf("\n%s, indMap is:-\n", when.c_str());

    printf("ele\tinds\n");
    for (map<int, pair<set<int>, set<int> > >::iterator i = indMap.begin(); i != indMap.end(); i++) {
        printf("%d\t", (*i).first);

        set<int> inds;

        printf("inds1 = {");
        inds = (*i).second.first;
        for (set<int>::iterator j = inds.begin(); j != inds.end(); j++) {
            printf("%d,", *j);
        }
        printf("}\t");

        printf("inds2 = {");
        inds = (*i).second.second;
        for (set<int>::iterator j = inds.begin(); j != inds.end(); j++) {
            printf("%d,", *j);
        }
        printf("}\t");

        cout << endl;
    }
}

// build index map (initialization)
map<int, pair<set<int>, set<int> > > buildIndMap(vector<int>& vec1, vector<int>& vec2) {
    map<int, pair<set<int>, set<int> > > indMap;

    for (int i = 0; i < vec1.size(); i++) {
        indMap[vec1[i]].first.insert(i);
    }

    for (int i = 0; i < vec2.size(); i++) {
        indMap[vec2[i]].second.insert(i);
    }

    return indMap;
}

// cleanup for optimization
list<int> findElesLessThan(set<int>& mSet, int ele) {
    list<int> elesLessThanList;
    for (set<int>::iterator j = mSet.begin(); j != mSet.end(); j++) {
        int ind = *j;

        if (ind < ele) {
            elesLessThanList.push_back(*j);
        } else {
            break;
        }
    }
    return elesLessThanList;
}

void dropKeys(map<int, pair<set<int>, set<int> > >& indMap, list <int> keysToDrop) {
    for (list <int>::iterator i = keysToDrop.begin(); i != keysToDrop.end(); i++) {
        indMap.erase(*i);
    }
}

void dropEles(set<int>& mSet, list<int> elesToDrop) {
    for (list<int>::iterator j = elesToDrop.begin(); j != elesToDrop.end(); j++) {
        mSet.erase(*j);
    }
}

void dropIndsFirst(map<int, pair<set<int>, set<int> > >& indMap, int idx) {
    // map<int, list<int> > dropInds;
    list <int> keysToDrop;

    for (map<int, pair<set<int>, set<int> > >::iterator i = indMap.begin(); i != indMap.end(); i++) {
        int ele = (*i).first;
        list<int> dropInds = findElesLessThan((*i).second.first, idx);
        dropEles((*i).second.first, dropInds);
        
        if (indMap[ele].first.empty() && indMap[ele].second.empty()) {
            keysToDrop.push_back(ele);
        }

        // for (list<int>::iterator j = dropInds.begin(); j != dropInds.end(); j++) {
        //     indMap[ele].first.erase(*j);
        // }
    }

    dropKeys(indMap, keysToDrop);

    // for (map<int, list<int> >::iterator i = dropInds.begin(); i != dropInds.end(); i++) {
    //     int ele = (*i).first;
    //     list<int> inds = (*i).second;
    //     for (list<int>::iterator j = inds.begin(); j != inds.end(); j++) {
    //         indMap[ele].first.erase(*j);
    //     }
    // }
}

void dropIndsSecond(map<int, pair<set<int>, set<int> > >& indMap, int idx) {
    list <int> keysToDrop;

    for (map<int, pair<set<int>, set<int> > >::iterator i = indMap.begin(); i != indMap.end(); i++) {
        int ele = (*i).first;
        list<int> dropInds = findElesLessThan((*i).second.second, idx);
        dropEles((*i).second.second, dropInds);

        if (indMap[ele].first.empty() && indMap[ele].second.empty()) {
            keysToDrop.push_back(ele);
        }

        // for (list<int>::iterator j = dropInds.begin(); j != dropInds.end(); j++) {
        //     indMap[ele].first.erase(*j);
        // }
    }

    dropKeys(indMap, keysToDrop);

    // map<int, list<int> > dropInds;

    // for (map<int, pair<set<int>, set<int> > >::iterator i = indMap.begin(); i != indMap.end(); i++) {
    //     int ele = (*i).first;
    //     set<int> indSet = (*i).second.second;

    //     for (set<int>::iterator j = indSet.begin(); j != indSet.end(); j++) {
    //         int ind = *j;

    //         if (ind < idx) {
    //             dropInds[ele].push_back(*j);
    //         } else {
    //             break;
    //         }
    //     }
    // }

    // for (map<int, list<int> >::iterator i = dropInds.begin(); i != dropInds.end(); i++) {
    //     int ele = (*i).first;
    //     list<int> inds = (*i).second;
    //     for (list<int>::iterator j = inds.begin(); j != inds.end(); j++) {
    //         indMap[ele].second.erase(*j);
    //     }
    // }
}

// get valid index for picking a given element from a given vector
int getValidInd(set<int>& indSet, int idx) {
    if (indSet.empty() || (*indSet.rbegin() < idx)) {
        return -1;
    } else {
        // printf("reached else block\n");
        for (set<int>::iterator it = indSet.begin(); it != indSet.end(); it++) {
            if (*it >= idx) {
                return *it;
            }
        }
        return -1;
    }
}

int getValidIndFirst(map<int, pair<set<int>, set<int> > >& indMap, int ele, int idx) {
    return getValidInd(indMap[ele].first, idx);
    // set<int> indSet = indMap[ele].first;
    // if (indSet.empty()) {
    //     return -1;
    // } else {
    //     return getValidInd(indSet, idx);
    // }
}

int getValidIndSecond(map<int, pair<set<int>, set<int> > >& indMap, int ele, int idx) {
    return getValidInd(indMap[ele].second, idx);
    // set<int> indSet = indMap[ele].second;
    // if (indSet.empty()) {
    //     return -1;
    // } else {
    //     return getValidInd(indSet, idx);
    // }
}

// main / orchestrator / master method
void testMaxNumberDebug() {
    vector<int> vec1;
    vector<int> vec2;
    int k;
    vector<int> vecOutExpected;
    vector<int> vecOutComputed;

    vec1 = {3, 4, 6, 5};
    vec2 = {9, 1, 2, 5, 8, 3};
    k = 5;
    vecOutExpected = {9, 8, 6, 5, 3};
    vecOutComputed = maxNumberDebug(vec1, vec2, k, false);
    assert(vecOutExpected == vecOutComputed);

    // this case fails; exposes that the approach is incorrect
    vec1 = {6, 7};
    vec2 = {6, 0, 4};
    k = 5;
    vecOutExpected = {6, 7, 6, 0, 4};
    vecOutComputed = maxNumberDebug(vec1, vec2, k, true);
    assert(vecOutExpected == vecOutComputed);

    vec1 = {3, 9};
    vec2 = {8, 9};
    k = 3;
    vecOutExpected = {9, 8, 9};
    vecOutComputed = maxNumberDebug(vec1, vec2, k, false);
    assert(vecOutExpected == vecOutComputed);
}

vector<int> maxNumberDebug(vector<int>& vec1, vector<int>& vec2, int k, bool debug) {
    int len1 = vec1.size();
    int len2 = vec2.size();

    vector<int> vec(k);
    map<int, pair<set<int>, set<int> > > indMap = buildIndMap(vec1, vec2);

    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < k; i++) {
        int maxPermInd1 = len1 - ((k - i) - (len2 - i2));
        int maxPermInd2 = len2 - ((k - i) - (len1 - i1));

        if (debug) {
            printf("\n----------\n");
            printf("iter i=%d of k=%d\n", i, k);
            printf("maxPermInd1 = %d, maxPermInd2 = %d\n", maxPermInd1, maxPermInd2);

            showIndMap(indMap, "");
            showVec(vec1, i1, maxPermInd1, "vec1");
            showVec(vec2, i2, maxPermInd2, "vec2");
        }

        int pickEleVec = -1;
        int pickEleInd = -1;

        int ind1 = -1;
        int ind2 = -1;
        for (map<int, pair<set<int>, set<int> > >::reverse_iterator it = indMap.rbegin(); it != indMap.rend(); it++) {
            int ele = (*it).first;

            ind1 = getValidIndFirst(indMap, ele, i1);
            ind2 = getValidIndSecond(indMap, ele, i2);

            bool isValid1 = (ind1 >= 0) && (ind1 <= maxPermInd1);
            bool isValid2 = (ind2 >= 0) && (ind2 <= maxPermInd2);

            if (debug) {
                printf("\nevaluating picking of ele=%d\n", ele);
                printf("ind1 = %d, isValid1 = %s\n", ind1, (isValid1 ? "true" : "false"));
                printf("ind2 = %d, isValid2 = %s\n", ind2, (isValid2 ? "true" : "false"));
            }
            if (isValid1 && isValid2) {
                int postPickMargin1 = (len1 - ind1 - 1) + (len2 - i2);
                int postPickMargin2 = (len2 - ind2 - 1) + (len1 - i1);

                if (postPickMargin1 > postPickMargin2) {
                    pickEleVec = 1;
                    pickEleInd = ind1;
                } else {
                    pickEleVec = 2;
                    pickEleInd = ind2;
                }

                break;
            } else if (isValid1) {
                pickEleVec = 1;
                pickEleInd = ind1;
                break;
            } else if (isValid2) {
                pickEleVec = 2;
                pickEleInd = ind2;
                break;
            } else {
                continue;
            }
        }

        if (pickEleVec == -1 || pickEleInd == -1) {
            throw logic_error("unable to pick element we've reached inconsistent state");
        } else if (pickEleVec == 1) {
            // put element in max vec
            int ele = vec1[pickEleInd];
            vec[i] = ele;

            // remove element from map & increment i1
            // indMap[ele].first.erase(pickEleInd);
            i1 = pickEleInd + 1;
            dropIndsFirst(indMap, i1);

            if (debug) {
                printf("\npicked vec1[%d] = %d, incremented i1 to %d\n", pickEleInd, ele, i1);
            }
        } else {
            // put element in max vec
            int ele = vec2[pickEleInd];
            vec[i] = ele;

            // remove element from map & increment i2
            // indMap[ele].second.erase(pickEleInd);
            i2 = pickEleInd + 1;
            dropIndsSecond(indMap, i2);

            if (debug) {
                printf("\npicked vec2[%d] = %d, incremented i2 to %d\n", pickEleInd, ele, i2);
            }
        }

        if (debug) {
            showVec(vec, -1, -1, "after picking, vec");
        }
    }

    return vec;
}

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    return maxNumberDebug(nums1, nums2, k, false);
}

/*
priority_queue <pair <int, int> > buildPQue(vector <int> vec) {
  priority_queue <pair <int, int> > pQue;
  for (int i = 0; i < vec.size(); i++) {
    pQue.push(make_pair(vec[i], -i));
  }
}

void discardEles(priority_queue <pair <int, int> >& pQue, int ind) {
  while (!pQue.empty() && (-pQue.top().second) < ind) {
    pQue.pop();
  }
}

vector <int> buildMaxVec(vector <int> vec1, vector <int> vec2, int k) {
  vector <int> maxVec(k);

  priority_queue <pair <int, int> > pQue1 = buildPQue(vec1);
  priority_queue <pair <int, int> > pQue2 = buildPQue(vec2);
  int len1 = vec1.size();
  int len2 = vec2.size();

  int i = 0;
  int i1 = 0;
  int i2 = 0;
  while (!pQue1.empty() && !pQue2.empty() && i < k) {
    discardEles(pQue1, i1);
    discardEles(pQue2, i2);
    if (pQue1.empty() || pQue2.empty()) {
      break;
    }


  }
}
*/

/*
class CustomPQue {
   private:
    priority_queue<pair<int, int> > pQue;
    list<pair<int, int> > buffer;
    int maxInd;

    void flushBuffer() {
        while (!buffer.empty()) {
            pQue.push(buffer.front());
            buffer.pop_front();
        }
    }

    void throwBuffer() {
        buffer.clear();
    }

   public:
    bool empty() {
        return pQue.empty();
    }

    pair<int, int> top() {
        if (pQue.empty()) {
            throw out_of_range("pQue is empty");
        } else {
            return pQue.top();
        }
    }

    void pop() {
        if (pQue.empty()) {
            throw out_of_range("pQue is empty");
        } else {
            pQue.pop();
        }
    }

    void push(pair<int, int> mPair) {
        pQue.push(mPair);
    }

    pair<int, int> bufferTop(int maxInd) {
        // put back elements earlier moved from heap to buffer back into heap
        if (!buffer.empty()) {
            flushBuffer();
        }

        // persist maxIndValue
        this->maxInd = maxInd;

        if (empty()) {
            throw out_of_range("pQue is empty");
        } else {
            while (!pQue.empty() && pQue.top().second > maxInd) {
                buffer.push_back(pQue.top());
                pQue.pop();
            }

            pair<int, int> mRes;
            if (pQue.empty()) {
                // nothing available
                mRes = make_pair(-1, -1);
            } else {
                mRes = pQue.top();
                pQue.pop();
            }

            return mRes;
        }
    }

    void flush() {
      flushBuffer();
    }

    void commit() {
        throwBuffer();
    }
};
*/
