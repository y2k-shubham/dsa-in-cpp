// LeetCode-973: https://leetcode.com/problems/k-closest-points-to-origin/

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector <pair <int, int>> convertToPairVec(vector <vector <int>>& vecVec) {
        int len = vecVec.size();
        vector <pair <int, int>> pairVec(len);

        int i = 0;
        for (vector <int> pointVec : vecVec) {
            pairVec[i++] = {pointVec[0], pointVec[1]};
        }

        return pairVec;
    }

    vector <vector <int>> convertToVecVec(vector <pair <int, int>>& pairVec) {
        int len = pairVec.size();
        vector <vector <int>> vecVec(len);

        for (int i = 0; i < len; i++) {
            vecVec[i] = {pairVec[i].first, pairVec[i].second};
        }

        return vecVec;
    }

    vector <double> createDistanceVec(vector <pair <int, int>>& pointsPairs) {
        int len = pointsPairs.size();
        vector <double> distances(len);

        for (int i = 0; i < len; i++) {
            pair <int, int> point = pointsPairs[i];

            double distance = sqrt(pow(point.first, 2) + pow(point.second, 2));
            distances[i] = distance;
        }

        return distances;
    }

    vector <pair <double, pair <int, int>>> zipVecs(
        vector <pair <int, int>>& pointsPairs,
        vector <double>& distances) {
        int len = pointsPairs.size();
        vector <pair <double, pair <int, int>>> zippedVec(len);

        for (int i = 0; i < len; i++) {
            zippedVec[i] = {distances[i], pointsPairs[i]};
        }

        return zippedVec;
    }

    vector <pair <int, int>> getFirstKPoints(
        vector <pair <double, pair <int, int>>>& distanceCoordVec,
        int k) {
        vector <pair <int, int>> points(k);

        for (int i = 0; i < k; i++) {
            points[i] = distanceCoordVec[i].second;
        }

        return points;
    }

public:
    vector <vector <int>> kClosest(vector <vector <int>>& points, int k) {
        int len = points.size();
        if (k >= len) {
            return points;
        }

        vector <pair <int, int>> pointsPairs = convertToPairVec(points);
        vector <double> distances = createDistanceVec(pointsPairs);

        vector <pair <double, pair <int, int>>> distanceCoordVec = zipVecs(pointsPairs, distances);
        sort(distanceCoordVec.begin(), distanceCoordVec.end());

        vector <pair <int, int>> firstKPoints = getFirstKPoints(distanceCoordVec, k);
        return convertToVecVec(firstKPoints);
    }
};
