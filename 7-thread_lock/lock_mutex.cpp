/*
  Author: Mingzhe Wang
  Date: Jul 5, 2026
  Description:
    solution with `mutex` for `lock_issue.cpp`.

    this file shows how pthread works for the following senario:
            [global_count]
    |   |   |   ...  |  |  |
    t0  t1  t2  ... t8 t9 t10
    each thread +100000

    which reveals the issue of `thread racing`, i.e.
    ```c++
    count++
    ``` 
    --- compile --->
    ```assembly
    mov [count], eax
    inc eax
    mov eax, [count]
    ```
    expected case:
     thread 1                           thread 2
     --------------------------         --------------------------
    | mov [count], eax         |       |                          |
    | inc eax                  |       |                          |
    | mov eax, [count]         |       |                          |
    |                          |       | mov [count], eax         |
    |                          |       | inc eax                  |
    |                          |       | mov eax, [count]         |
     --------------------------         --------------------------

    unpected case:
     thread 1                           thread 2
     --------------------------         --------------------------
    | mov [count], eax         |       |                          |
    |                          |       | mov [count], eax         |
    |                          |       | inc eax                  |
    |                          |       | mov eax, [count]         |
    | inc eax                  |       |                          |
    | mov eax, [count]         |       |                          |
     --------------------------         --------------------------

           eax[thread 1]         count        eax[thread 2]
*/
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 10

pthread_mutex_t mutex;

void* thread_callback(void* arg) {
  int* pcount = (int *) arg;

  int i = 0;
  while (i++ < 100000) {
#if 0
    ++(*pcount);
#else
    pthread_mutex_lock(&mutex);
    ++(*pcount);
    pthread_mutex_unlock(&mutex);
#endif
    usleep(1);
  }
  
  return NULL;
}

int main() {
  int global_count = 0;

  pthread_mutex_init(&mutex, NULL);

  pthread_t thread_id[THREAD_COUNT] = {0}; // initialize all thread_id to 0
  int i;
  for (i = 0; i < THREAD_COUNT; ++i) {
    pthread_create(&thread_id[i], NULL, thread_callback, &global_count);
  }

  for (i = 0; i < 100; ++i) {
    printf("i: %d, thread_id: %lu, count : %d\n", i, (unsigned long) thread_id[i], global_count);
    sleep(1);
  }

  return 0;
}
