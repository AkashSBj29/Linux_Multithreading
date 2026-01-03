#include <stdio.h>
#include <pthread.h> /* POSIX threads */
#include <unistd.h> /* pause() and sleep() */

void create_thread(void);
static void* thread_fn_callback(void*);

int main(int argc, char** argv) {
  for(int i = 0; i < argc; ++i) {
    printf("Argument %d is %s\n", i, argv[i]);
  }
  printf("\n");

  create_thread();
  pause();

  return 0;
}

void create_thread(void) {
  static char* msg = "This is a thread";

  pthread_t pthread;
  /* Returns 0 on success */
  int rc = pthread_create(&pthread, NULL, thread_fn_callback, (void*)msg);
  if (rc != 0) {
    printf("Error creating thread - ERROR CODE %d\n", rc);
    return;
  }

}

static void* thread_fn_callback(void* arg) {
  char* data = (char*)arg;

  while(1) {
    printf("data: %s\n", data);
    sleep(2);
  }

  return NULL;
}
