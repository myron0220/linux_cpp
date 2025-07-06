#include <iostream>

#define NAME_LEN 32
#define PHONE_LEN 32

#define LIST_INSERT(item, list_head) do { \
  item->prev = NULL;                      \
  item->next = list_head;                 \
  list_head = item;                       \
} while(0)

#define LIST_REMOVE(item, list_head) do {                 \
  if (item->prev != NULL) item->prev->next = item->next;  \
  if (item->next != NULL) item->next->prev = item->prev;  \
  if (list_head == item) list = item->next;               \
  item->prev = item->next = NULL;                         \
} while(0)

struct person {
  char name[NAME_LEN];
  char phone[PHONE_LEN];

  struct person* prev;
  struct person* next;
};

struct contacts {
  struct person* head;
  int count;
};



int main() {
  std::cout << "Hello World!" << '\n';
  return 0;
}