// Zomato Coding For Scale Hackathon (InterviewBit) 15th Dec 2018

/**
 * There are T test cases
 * There are N students numbered 1..N each with a happiness score Ai
 * There are Q queries in which groups to which two students belong are merged (if they belong to different groups)
 * 
 * After each query, output the following
 * 1. Max happiness score of students among those group which have max no of students
 * 2. No of groups having prime no of students
 * 3. Product of no of students in each group (modulo 10^7 + 1)
 * 
 * T = 10
 * 1 <= N <= 100,000
 * 1 <= Ai <= 1,000,000,000
 * dont remember Q but it was probably ~ 100
 */

/*
1
7 0
8 1 3 7 4 2 9

1
7 1
8 1 3 7 4 2 9
5 3

1
7 3
8 1 3 7 4 2 9
5 3
3 1
2 7
*/

#include <cstdio>
#include <iostream>
#include <set>
#include <map>
#include <cmath>

using namespace std;

// input and DS-creation methods
map <int, int> inputStudentValueMap(int);
map <int, int> createStudentRootMap(int);
map <int, set <int> > createRootStudentSetMap(int);
map <int, map <int, int> > createRootValueFreqMap(map <int, int>);
map <int, set <int> > createSizeRootSetMap(int);
// processing methods
void mergeStudentGroups(map <int, int>&, map <int, int>&, map <int, set <int> >&, map <int, map <int, int> >&, map <int, set <int> >&, int, int);
int findRoot(map <int, int>&, map <int, int>&, map <int, set <int> >&, map <int, map <int, int> >&, map <int, set <int> >&, int);
void moveAllStudents(map <int, int>&, map <int, int>&, map <int, set <int> >&, map <int, map <int, int> >&, map <int, set <int> >&, int, int);
void moveOneStudent(map <int, int>&, map <int, int>&, map <int, set <int> >&, map <int, map <int, int> >&, map <int, set <int> >&, int, int);
// output-debugging methods
void showDSs(map <int, int>, map <int, int>, map <int, set <int> >, map <int, map <int, int> >, map <int, set <int> >);
void showStepSeparator();
void showDSSeparator();
void showIntValueMap(map <int, int>, const char *);
void showSetValueMap(map <int, set <int> >, const char *);
void showMapValueMap(map <int, map <int, int> >, const char *);

int main() {
  int T;

  cin >> T;
  while (T-- > 0) {
    // input
    int N, Q;
    cin >> N >> Q;

    // input student happiness scores
    map <int, int> studentValueMap = inputStudentValueMap(N);

    // create DSs
    map <int, int> studentRootMap = createStudentRootMap(N);
    map <int, set <int> > rootStudentSetMap = createRootStudentSetMap(N);
    map <int, map <int, int> > rootValueFreqMap = createRootValueFreqMap(studentValueMap);
    map <int, set <int> > sizeRootSetMap = createSizeRootSetMap(N);

    showDSs(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap);
    while (Q-- > 0) {
      int student1, student2;
      cin >> student1 >> student2;

      cout << "Merge groups of students " << student1 << " and " << student2 << endl;
      mergeStudentGroups(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, student1, student2);
      showDSs(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap);
    }
  }

  return 0;
}

// input and ds-creation methods
map <int, int> inputStudentValueMap(int n) {
  int value;
  map <int, int> studentValueMap;

  for (int i = 1; i <= n; i++) {
    cin >> value;
    studentValueMap[i] = value;
  }

  return studentValueMap;
}

map <int, int> createStudentRootMap(int n) {
  map <int, int> studentRootMap;

  for (int i = 1; i <= n; i++) {
    studentRootMap[i] = i;
  }

  return studentRootMap;
}

map <int, set <int> > createRootStudentSetMap(int n) {
  map <int, set <int> > rootStudentSetMap;

  for (int i = 1; i <= n; i++) {
    set <int> studentSet;
    studentSet.insert(i);
    rootStudentSetMap[i] = studentSet;
  }

  return rootStudentSetMap;
}

map <int, map <int, int> > createRootValueFreqMap(map <int, int> studentValueMap) {
  map <int, map <int, int> > rootValueFreqMap;

  for (map <int, int>::iterator it = studentValueMap.begin(); it != studentValueMap.end(); it++) {
    map <int, int> valueFreqMap;
    valueFreqMap[(* it).second] = 1;
    rootValueFreqMap[(* it).first] = valueFreqMap;
  }

  return rootValueFreqMap;
}

map <int, set <int> > createSizeRootSetMap(int n) {
  map <int, set <int> > sizeRootSetMap;
  
  set <int> rootSet;
  for (int i = 1; i <= n; i++) {
    rootSet.insert(i);
  }
  sizeRootSetMap[1] = rootSet;

  return sizeRootSetMap;
}

// processing methods
void mergeStudentGroups(map <int, int>& studentValueMap, map <int, int>& studentRootMap, map <int, set <int> >& rootStudentSetMap, map <int, map <int, int> >& rootValueFreqMap, map <int, set <int> >& sizeRootSetMap, int student1, int student2) {
  int root1 = findRoot(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, student1);
  int root2 = findRoot(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, student2);

  if (root1 != root2) {
    int root1SetSize = rootStudentSetMap[root1].size();
    int root2SetSize = rootStudentSetMap[root2].size();

    if (root1SetSize > root2SetSize) {
      moveAllStudents(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, root2, root1);
    } else {
      moveAllStudents(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, root1, root2);
    }
  }
}

int findRoot(map <int, int>& studentValueMap, map <int, int>& studentRootMap, map <int, set <int> >& rootStudentSetMap, map <int, map <int, int> >& rootValueFreqMap, map <int, set <int> >& sizeRootSetMap, int student) {
  if (studentRootMap[student] == student) {
    return student;
  } else {
    int crrRoot = studentRootMap[student];
    int mainRoot = findRoot(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, crrRoot);

    // move all students in crrRoot to mainRoot
    moveAllStudents(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, crrRoot, mainRoot);

    return mainRoot;
  }
}

void moveAllStudents(map <int, int>& studentValueMap, map <int, int>& studentRootMap, map <int, set <int> >& rootStudentSetMap, map <int, map <int, int> >& rootValueFreqMap, map <int, set <int> >& sizeRootSetMap, int srcRoot, int tgtRoot) {
  // move all students in srcRoot to tgtRoot
  set <int> studentsInSrcRootCopy = rootStudentSetMap[srcRoot];
  set <int> studentsInSrcRoot = studentsInSrcRootCopy;
  for (set <int>::iterator it = studentsInSrcRoot.begin(); it != studentsInSrcRoot.end(); it++) {
    moveOneStudent(studentValueMap, studentRootMap, rootStudentSetMap, rootValueFreqMap, sizeRootSetMap, (* it), tgtRoot);
  }
}

void moveOneStudent(map <int, int>& studentValueMap, map <int, int>& studentRootMap, map <int, set <int> >& rootStudentSetMap, map <int, map <int, int> >& rootValueFreqMap, map <int, set <int> >& sizeRootSetMap, int student, int newRoot) {
  int crrRoot = studentRootMap[student];
  int value = studentValueMap[student];

  // current root changes
  int crrRootSetSize = rootStudentSetMap[crrRoot].size();
  sizeRootSetMap[crrRootSetSize].erase(crrRoot);
  if (sizeRootSetMap[crrRootSetSize].empty()) {
    sizeRootSetMap.erase(crrRootSetSize);
  }
  if (crrRootSetSize > 1) {
    sizeRootSetMap[crrRootSetSize - 1].insert(crrRoot);
    rootStudentSetMap[crrRoot].erase(student);
    rootValueFreqMap[crrRoot][value]--;
  } else {
    rootStudentSetMap.erase(crrRoot);
    rootValueFreqMap.erase(crrRoot);
  }

  // new root changes
  int newRootSetSize = rootStudentSetMap[newRoot].size();
  sizeRootSetMap[newRootSetSize].erase(newRoot);
  if (sizeRootSetMap[newRootSetSize].empty()) {
    sizeRootSetMap.erase(newRootSetSize);
  }
  sizeRootSetMap[newRootSetSize + 1].insert(newRoot);
  rootStudentSetMap[newRoot].insert(student);
  rootValueFreqMap[newRoot][value]++;
  
  // student changes
  studentRootMap[student] = newRoot;
}

// output-debugging methods
void showDSs(map <int, int> studentValueMap, map <int, int> studentRootMap, map <int, set <int> > rootStudentSetMap, map <int, map <int, int> > rootValueFreqMap, map <int, set <int> > sizeRootSetMap) {
  showStepSeparator();
  showIntValueMap(studentValueMap, "studentValueMap");
  showDSSeparator();
  showIntValueMap(studentRootMap, "studentRootMap");
  showDSSeparator();
  showSetValueMap(rootStudentSetMap, "rootStudentSetMap");
  showDSSeparator();
  showMapValueMap(rootValueFreqMap, "rootValueFreqMap");
  showDSSeparator();
  showSetValueMap(sizeRootSetMap, "sizeRootSetMap");
  showStepSeparator();
}

void showStepSeparator() {
  cout << endl << "-------------------------" << endl;
}

void showDSSeparator() {
  cout << endl;
}

void showIntValueMap(map <int, int> intValueMap, const char * name) {
  printf("%s map is:-\n", name);
  for (map <int, int>::iterator it = intValueMap.begin(); it != intValueMap.end(); it++) {
    printf("[%d]\t->\t%d\n", (* it).first, (* it).second);
  }
}

void showSetValueMap(map <int, set <int> > setValueMap, const char * name) {
  printf("%s map is:-\n", name);
  for (map <int, set <int> >::iterator it = setValueMap.begin(); it != setValueMap.end(); it++) {
    printf("[%d]\t->\t{", (* it).first);
    set <int> setValue = (* it).second;
    for (set <int>::iterator jt = setValue.begin(); jt != setValue.end(); jt++) {
      printf("%d, ", (* jt));
    }
    printf("}\n");
  }
}

void showMapValueMap(map <int, map <int, int> > mapValueMap, const char * name) {
  printf("%s map is:-\n", name);
  for (map <int, map <int, int> >::iterator it = mapValueMap.begin(); it != mapValueMap.end(); it++) {
    printf("[%d]\t->\t{", (* it).first);
    map <int, int> mapValue = (* it).second;
    for (map <int, int>::iterator jt = mapValue.begin(); jt != mapValue.end(); jt++) {
      printf("(%d -> %d), ", (* jt).first, (* jt).second);
    }
    printf("}\n");
  }
}
