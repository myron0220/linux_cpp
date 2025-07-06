/*
  Author: Mingzhe Wang
  Date: Jul 5, 2026
  Description:
    solution with `atomic` for `lock_issue.cpp`.
    



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
pthread_spinlock_t spinlock; // ignore the syntax error here, this is because vscode is runing on MacOS

int inc(int* value, int add_on) {
  int old;

  // <--- only works on `x86` architecture
  // __asm__ volatile(
  //   "lock; xaddl %2, %1;"
  //   : "=a" (old)
  //   : "m" (*value), "a"(add_on)
  //   : "cc", "memory"
  // );

  // <--- only works on `aarch64` architecture
  // [TODO]

  return old;
}

void* thread_callback(void* arg) {
  int* pcount = (int *) arg;

  int i = 0;
  while (i++ < 100000) {
#if 0
    ++(*pcount);
#elif 0
    pthread_mutex_lock(&mutex);
    ++(*pcount);
    pthread_mutex_unlock(&mutex);
#elif 0
    pthread_spin_lock(&spinlock);
    ++(*pcount);
    pthread_spin_unlock(&spinlock);
#else
    inc(pcount, 1);
#endif
    usleep(1);
  }
  
  return NULL;
}

int main() {
  int global_count = 0;

  pthread_mutex_init(&mutex, NULL);
  pthread_spin_init(&spinlock, PTHREAD_PROCESS_SHARED);

  pthread_t thread_id[THREAD_COUNT] = {0}; // initialize all thread_id to 0
  int i;
  for (i = 0; i < THREAD_COUNT; ++i) {
    pthread_create(&thread_id[i], NULL, thread_callback, &global_count);
  }

  for (i = 0; i < 100; ++i) {
    printf("i: %d, thread_id: %lu, count : %d\n", i, (unsigned long) thread_id[i], global_count);
    sleep(1);
  }

  std::cout << "DONE." << '\n';
  return 0;
}
