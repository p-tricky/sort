#include "dbEntries.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

long numFiles = 9;
dbEntries *files[9];
void *sort_files(void* file);

void* sort_files(void *file) {
  long myFile = (long) file; 
  printf("hello from thread %ld\n", myFile);
  char path[100];
  sprintf(path, "./A4_ParallelSort/data/%ld", myFile);
  FILE *data = fopen(path, "r");
  dbEntries *ents = dbEntries_init();
  read_file(data, ents);
  printf("hello again from thread %ld\n", myFile);
  fflush(stdout);
  sort_entries(ents);
  files[myFile] = ents;
  fclose(data);
  return NULL;
}

int merge_files(FILE *db) {
  unsigned int next = 1, max = 0; 
  dbEntry *next_entry;
  int i;
  for (i=0; i<numFiles; i++) {
    max += files[i]->numEntries;
  }
  while (next <= max) {
    for (i=0; i<numFiles; i++) {
      next_entry = files[i]->entries[files[i]->next];
      if (next_entry->index == next) {
        writeToFile(db, next_entry);
        if (files[i]->next < files[i]->numEntries-1) files[i]->next++;
      }
    }
    next++;
  }
  return 0;
}

int main() {
 long thread;
 pthread_t *thread_handles;
 thread_handles = malloc(numFiles*sizeof(pthread_t));
 for (thread=0; thread<numFiles; thread++)
   pthread_create(&thread_handles[thread], NULL, sort_files, (void*)thread);
 for (thread=0; thread<numFiles; thread++)
   pthread_join(thread_handles[thread], NULL);
 //write_entries_to_file(stdout, files[8]);
 FILE *db = fopen("database", "w");
 merge_files(db);
 fclose(db);
 exit(EXIT_SUCCESS);

 /*
    pthread_t threadA, threadB; // need to name the thread
    int rc;
    if ( (rc = pthread_create(&threadA , NULL, Thread, NULL)) )
    {fprintf(stdout,"ERROR; return pthread_create()" );
    exit(1); }
    if ( (rc = pthread_create(&threadB , NULL, Thread, NULL)) )
    {fprintf(stdout,"ERROR; return pthread_create()" );
    exit(1); }
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    exit(EXIT_SUCCESS);
    */
}

