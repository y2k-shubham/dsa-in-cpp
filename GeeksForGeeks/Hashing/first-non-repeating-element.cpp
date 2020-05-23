// http://www.geeksforgeeks.org/find-first-non-repeating-character-stream-characters/
// geeksforgeeksandgeeksquizfor

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <set>

struct node {
  char c;
  struct node * prev;
  struct node * next;
};

using namespace std;

bool isRepeated(set <char>, char);
void addNewUniqueElement(set <char>&, pair <node *, node *>&, map <char, node *>&, char);
void removeRepeatedElement(pair <node *, node *>&, map <char, node *>&, char);
pair <node *, node *> insertNodeDLL(pair <node *, node *>, node *);
pair <node *, node *> deleteNodeDLL(pair <node *, node *>, node *);
void purgeNodeDLL(node *);
node * createNode(char);
void linkNodesDLL(node *, node *);
void outputFirstNotRepeatingChar(pair <node *, node *>);
void showDLL(pair <node *, node *>);
void showCharSet(set <char>);
void showCharNodeMap(map <char, node *>);
void showNodeDLL(node *);

int main() {
  set <char> charSet;
  pair <node *, node *> dllEnds;
  map <char, node *> charNodeMap;

  char c;
  cin >> c;
  while (c != '\n') {
    if (isRepeated(charSet, c)) {
      removeRepeatedElement(dllEnds, charNodeMap, c);
    } else {
      addNewUniqueElement(charSet, dllEnds, charNodeMap, c);
    }
    cout << "-------" << endl;
    showCharSet(charSet);
    showDLL(dllEnds);
    showCharNodeMap(charNodeMap);
    cout << "-------" << endl;
    outputFirstNotRepeatingChar(dllEnds);
    cout << "-------" << endl;
    cin >> c;
  }

  return 0;
}

bool isRepeated(set <char> charSet, char c) {
  if (charSet.find(c) == charSet.end()) {
    return false;
  } else {
    return true;
  }
}

void addNewUniqueElement(set <char>& charSet, pair <node *, node *>& dllEnds, map <char, node *>& charNodeMap, char c) {
  charSet.insert(c);
  node * newNode = createNode(c);
  dllEnds = insertNodeDLL(dllEnds, newNode);
  charNodeMap[c] = newNode;
}

void removeRepeatedElement(pair <node *, node *>& dllEnds, map <char, node *>& charNodeMap, char c) {
  if (charNodeMap.find(c) != charNodeMap.end()) {
    node * victimNode = charNodeMap[c];
    dllEnds = deleteNodeDLL(dllEnds, victimNode);
    charNodeMap.erase(c);
  }
}

pair <node *, node *> insertNodeDLL(pair <node *, node *> dllEnds, node * newNode) {
  node * head = dllEnds.first;
  node * tail = dllEnds.second;
  if (head == NULL) {
    dllEnds = make_pair(newNode, newNode);
  } else {
    linkNodesDLL(tail, newNode);
    dllEnds = make_pair(head, newNode);
  }
  return dllEnds;
}

pair <node *, node *> deleteNodeDLL(pair <node *, node *> dllEnds, node * victimNode) {
  node * head = dllEnds.first;
  node * tail = dllEnds.second;

  if (head == victimNode && tail == victimNode) {
    purgeNodeDLL(head);
    head = NULL;
    tail = NULL;
    return make_pair(head, tail);
  }

  if (head == victimNode) {
    head = head -> next;
  }

  if (tail == victimNode) {
    tail = tail -> prev;
  }

  purgeNodeDLL(victimNode);
  return make_pair(head, tail);
}

void purgeNodeDLL(node * myNode) {
  node * prevNode = myNode -> prev;
  node * nextNode = myNode -> next;
  if (prevNode != NULL) {
    prevNode -> next = nextNode;
  }
  if (nextNode != NULL) {
    nextNode -> prev = prevNode;
  }
  free(myNode);
}

node * createNode(char c) {
  node * newNode = new node;
  newNode -> prev = NULL;
  newNode -> next = NULL;
  newNode -> c = c;
  return newNode;
}

void linkNodesDLL(node * first, node * second) {
  first -> next = second;
  second -> prev = first;
}

void outputFirstNotRepeatingChar(pair <node *, node *> dllEnds) {
  node * head = dllEnds.first;
  if (head == NULL) {
    printf("No    non-repeating char at this point\n");
  } else {
    printf("First non-repeating char at this point is %c\n", head -> c);
  }
}

void showDLL(pair <node *, node *> dllEnds) {
  printf("DLL is:-\n");
  for (node * crrNode = dllEnds.first; crrNode != NULL; crrNode = crrNode -> next) {
    printf("%c -> ", crrNode -> c);
  }
  printf("NULL\n");
}

void showCharSet(set <char> charSet) {
  printf("charSet is:-\n");
  for (set <char>::iterator it = charSet.begin(); it != charSet.end(); it++) {
    printf("%c, ", * it);
  }
  cout << endl;
}

void showCharNodeMap(map <char, node *> charNodeMap) {
  printf("charNodeMap is:-\n");
  for (map <char, node *>::iterator it = charNodeMap.begin(); it != charNodeMap.end(); it++) {
    printf("%c -> ", (* it).first);
    showNodeDLL((* it).second);
    cout << endl;
  }
}

void showNodeDLL(node * myNode) {
  if (myNode == NULL) {
    printf("NULL");
  } else {
    if (myNode -> prev == NULL && myNode -> next == NULL) {
      printf("(NULL <- [%c] -> NULL)", myNode -> c);
    } else if (myNode -> prev == NULL && myNode -> next == NULL) {
      printf("(%c <- [%c] -> %c)", myNode -> prev -> c, myNode -> c, myNode -> next -> c);
    } else if (myNode -> prev != NULL) {
      printf("(%c <- [%c] -> NULL)", myNode -> prev -> c, myNode -> c);
    } else {
      printf("(NULL <- [%c] -> %c)", myNode -> c, myNode -> next -> c);
    }
  }
}
