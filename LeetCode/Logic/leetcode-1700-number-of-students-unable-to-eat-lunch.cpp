// LeetCode-1700: https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/
// Companies: [Amazon][Bloomberg][Google][Meta][Microsoft]

// Optimal single-pass solution written after reading LeetCode editorial
// this is definitely not easy

#include <vector>

using namespace std;

#define CIRCULAR_SANDWICH 0
#define SQUARE_SANDWICH 1

class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int numStudentsTotal = students.size();
        int numStudentsWithPrefCircularSandwich = count(students.begin(), students.end(), CIRCULAR_SANDWICH);
        int numStudentsWithPrefSquareSandwich = numStudentsTotal - numStudentsWithPrefCircularSandwich;

        int remNumStudentsWithPrefCircularSandwich = numStudentsWithPrefCircularSandwich;
        int remNumStudentsWithPrefSquareSandwich = numStudentsWithPrefSquareSandwich;
        for (int i = 0; i < numStudentsTotal; i++) {
            if (sandwiches[i] == CIRCULAR_SANDWICH) {
                if (remNumStudentsWithPrefCircularSandwich == 0) {
                    return remNumStudentsWithPrefSquareSandwich;
                } else {
                    remNumStudentsWithPrefCircularSandwich--;
                    continue;
                }
            } else if (sandwiches[i] == SQUARE_SANDWICH) {
                if (remNumStudentsWithPrefSquareSandwich == 0) {
                    return remNumStudentsWithPrefCircularSandwich;
                } else {
                    remNumStudentsWithPrefSquareSandwich--;
                    continue;
                }
            }
        }

        return 0;
    }
};
