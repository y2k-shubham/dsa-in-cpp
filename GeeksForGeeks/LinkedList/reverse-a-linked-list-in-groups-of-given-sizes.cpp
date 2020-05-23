// Method Completion problem
// Problem URL: http://www.practice.geeksforgeeks.org/probfunc-page.php?pid=700013
// Submission URL: http://www.practice.geeksforgeeks.org/viewSol.php?subId=129259
// Editorial URL: http://www.geeksforgeeks.org/reverse-a-list-in-groups-of-given-size/

#include <cstdio>
#include <iostream>
#include <cstdlib>

/*
  Reverse a linked list
  The input list will have at least one element
  Return the node which points to the head of the new LinkedList
  Node is defined as
  struct node
  {
     int data;
     struct Node *next;
  }
*/

struct node
  {
     int data;
     struct node *next;
  };

void swap(struct node * nod_1, struct node * nod_2) {
    int temp = nod_1 -> data;
    nod_1 -> data = nod_2 -> data;
    nod_2 -> data = temp;
}

struct node * revInGroup(struct node * head, struct node * curr, int i, int k) {
    if (i == k) {
        swap(head, curr);
        return head -> next;
    } else {
        struct node * nod = revInGroup(head, curr -> next, i + 1, k);

        if (i > (k >> 1)) {
            swap(nod, curr);
            return nod -> next;
        } else {
            return head;
        }
    }
}

struct node *reverse (struct node *head, int k)
{
  // Complete this method
  struct node * list;
  struct node * sublist;
  int ctr;

  for (list = head; list != NULL; ) {
      sublist = list;
      // advancing list by k positions
      for (ctr = 1; sublist != NULL && ctr <= k; ctr++) {
          sublist = sublist -> next;
      }

      // if list becomes prematurely NULL, then it means
      // that we are at last group of reversal, so make
      // k equal to the number of remaining nodes
      if (sublist == NULL) {
          k = ctr - 1;
      }

      // invoke the method for reversal of k-length block
      revInGroup(list, list, 1, k);

      // towards the end, advance list to sublist
      list = sublist;
  }

  return head;
}
