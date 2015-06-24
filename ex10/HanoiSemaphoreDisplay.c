#include <stdio.h>
#include <stdlib.h>
#include "HanoiShareMem.h"
#include "HanoiSemaphore.h"

void AllocateShareMemory(int nShareMemID);

void Display();

void ReserveCriticalRegion(int);
void ReleaseCriticalRegion(int);

int main(int argc, char *argv[]) {

  int nShareMemID;
  int nSemaphID;

  if (argc != 3) {
    printf("Usage: %s ShareMemoryID SemaphoreID\n", argv[0]);
    exit(1);
  }

  nShareMemID = atoi(argv[1]);
  nSemaphID = atoi(argv[2]);

  //共有メモリ確保と領域割り振り
  AllocateShareMemory(nShareMemID);

  ReserveCriticalRegion(nSemaphID);
  Display();
  ReleaseCriticalRegion(nSemaphID);


  return 0;
}

void ReserveCriticalRegion(int nSemaphID) {
  struct sembuf semBuf;
  semBuf.sem_num = 0;
  semBuf.sem_flg = 0;
  semBuf.sem_op = -1;

  if (semop(nSemaphID, &semBuf, 1) == -1) {
    perror("semop(reserve) failure");
    exit(-1);
  }
}

void ReleaseCriticalRegion(int nSemaphID) {
  struct sembuf semBuf;
  semBuf.sem_num = 0;
  semBuf.sem_flg = 0;
  semBuf.sem_op = 1;

  if (semop(nSemaphID, &semBuf, 1) == -1) {
    perror("semop(release) failure");
    exit(-1);
  }
}

void AllocateShareMemory(int nShareMemID) {
  // copied from ex07

  //メモリ領域割り振り
  nDisks = shmat(nShareMemID, 0, SHM_R | SHM_W);

  if (nDisks == (void*)-1) {
    printf("Share memory cannot be referred\n");
    exit(1);
  }

  //nMoves, naA, naB, naCにも割り振る
  nMoves = nDisks + 1;
  naA = nDisks + 2 + (*nDisks) * 0;
  naB = nDisks + 2 + (*nDisks) * 1;
  naC = nDisks + 2 + (*nDisks) * 2;
}

void Display(void){
  int i;

  printf("Move: %d\n\n", *nMoves);
  for(i=*nDisks-1; i>=0; --i){
    printf("|%2d|   |%2d|   |%2d|\n", naA[i], naB[i], naC[i]);
  }

  printf("----   ----   ----\n");
  printf("  A      B      C\n");
}

