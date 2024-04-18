// LeetCode-690: https://leetcode.com/problems/employee-importance/

#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

class Solution {
private:
    unordered_map<int, Employee*> employees;

    void buildMap(vector<Employee*> employees) {
        for (auto employee: employees) {
            this->employees[employee->id] = employee;
        }
    }

    int getImportanceRec(int id) {
        Employee* employee = employees[id];
        int importance = employee->importance;

        for (auto subId: employee->subordinates) {
            importance += getImportanceRec(subId);
        }

        return importance;
    }

public:
    friend class SolutionTest;

    int getImportance(vector<Employee*> employees, int id) {
        buildMap(employees);
        return getImportanceRec(id);
    }
};

class SolutionTest {
private:
    Employee* createEmployee(int id, int importance, vector<int> subordinates) {
        Employee* employee = new Employee();
        employee->id = id;
        employee->importance = importance;
        employee->subordinates = subordinates;

        return employee;
    }

public:
    void testGetImportance() {
        Solution soln = Solution();
        vector<Employee*> employees;
        int outExpected, outComputed;

        employees.push_back(createEmployee(1, 5, {2, 3}));
        employees.push_back(createEmployee(2, 3, {}));
        employees.push_back(createEmployee(3, 3, {}));

        outComputed = soln.getImportance(employees, 1);
        outExpected = 11;
        assert(outExpected == outComputed);

        outComputed = soln.getImportance(employees, 3);
        outExpected = 3;
        assert(outExpected == outComputed);

        outComputed = soln.getImportance(employees, 2);
        outExpected = 3;
        assert(outExpected == outComputed);

        employees.push_back(createEmployee(1, 2, {5}));
        employees.push_back(createEmployee(5, -3, {}));

        outComputed = soln.getImportance(employees, 5);
        outExpected = -3;
        assert(outExpected == outComputed);

        outComputed = soln.getImportance(employees, 1);
        outExpected = -1;
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testGetImportance();

    return 0;
}
