#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

static pthread_t create_thread_1(void);
static pthread_t create_thread_2(void);
static void* thread1_callback(void*);
static void* thread2_callback(void*);

static char msg[100];

int main() {
  pthread_t p1 = create_thread_1();
  pthread_t p2 = create_thread_2();

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  return 0;
}

static pthread_t create_thread_1(void) {
  pthread_t pthread;
  int rc = pthread_create(&pthread, NULL, thread1_callback, (void*)msg);
  if (rc != 0) {
    printf("Failed to create thread - ERROR CODE %d\n", rc);
  }

  return pthread;
}

static pthread_t create_thread_2(void) {
  static char* msg = "This is from thread_2";
  pthread_t pthread;
  int rc = pthread_create(&pthread, NULL, thread2_callback, (void*)msg);
  if (rc != 0) {
    printf("Failed to create thread - ERROR CODE %d\n", rc);
  }

  return pthread;
}

static void* thread1_callback(void* arg) {
  for(size_t i = 0; i < 10; ++i) {
    snprintf(msg, 100, "thread_1 msg: %s\n", (char*)arg);
    write(STDOUT_FILENO, msg, strlen(msg));
  }
  sleep(1);

  return NULL;
}

static void* thread2_callback(void* arg) {
  for(size_t i = 0; i < 10; ++i) {
    snprintf(msg, 100, "thread_2 msg: %s\n", (char*)arg);
    write(STDOUT_FILENO, msg, strlen(msg));
  }
  sleep(1);

  return NULL;
}
