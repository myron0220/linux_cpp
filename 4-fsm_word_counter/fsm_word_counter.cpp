/*
  Author: Mingzhe Wang
  Date: Jul 5, 2025
  Description: 
  ----------------------------------------------
    C++ word_counter using finite state machine
    usage: fsm_word_counter words.txt

    -----                                         -----
   | OUT | -- if not splitter: ++word_count -->  | IN  |
    -----                                         -----
  ----------------------------------------------
*/

#include <iostream>
#include <unordered_set>

#define OUT 0
#define IN 1
#define INIT OUT

bool is_splitter(char c) {
  std::unordered_set<char> splitter_set = {
    ' ', '\n', '\t'
  };

  if (splitter_set.count(c)) {
    return true;
  } else {
    return false;
  }
}

int count_word(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) return -1;

  std::cout << "filename: " << filename << '\n';

  int status = INIT;
  int word_count = 0;

  char c;
  int c_int;
  while ((c_int = fgetc(fp)) != EOF) {
    c = (char) c_int;

    if (is_splitter(c)) {
      status = OUT;
    } else if (status == OUT) {
      status = IN;
      ++word_count;
    }
  }

  return word_count;
}

int main(int argc, char *argv[]) {
  if (argc < 2) return -1;

  printf("words: %d\n", count_word(argv[1]));

  return 0;
}
