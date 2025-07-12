/*
  Author: Mingzhe Wang
  Date: Jul 6, 2026
  Description:
    Linked list for contacts.
                                              

    Service Layer                   service logic
    Interface Layer         add, delete, search, traverse | unpack, pack
    Infrastructure Layer           linked list with functions
*/
#include <iostream>

#define NAME_LENGTH 16
#define PHONE_LENGTH 32

// **Takeaway: Macros in C/C++ work by textual substitution.**
#define LIST_INSERT(node, list_head) do {

} while (0)

struct person {
  char name[NAME_LENGTH];
  char phone[PHONE_LENGTH];

  struct person* next;
  struct person* prev;
};

struct contacts {
  struct person* head;
  int count;
};

int main() {
  std::cout << "Hello World!" << '\n';

  return 0;
}
