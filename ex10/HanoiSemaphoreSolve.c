#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "HanoiShareMem.h"
#include "HanoiSemaphore.h"

void AllocateShareMemory(int);

void CreateSemaphore();
void DiscardSemaphore();

void ReserveCriticalRegion(int);
void ReleaseCriticalRegion(int);

void Initialize();
void Solve(int *,int *,int *,int);

void SignalHandler(int);

int nShareMemID;
int nSemaphID;

int main(int argc, char *argv[]) {

  int nRequestedNumDisks = 10;

  if (argc > 2) {
    printf("Usage: %s [ndisks]\n", argv[0]);
    exit(1);
  }
  if (argc == 2) nRequestedNumDisks = atoi(argv[1]);

  signal(SIGINT , SignalHandler);
  signal(SIGQUIT, SignalHandler);
  signal(SIGTERM, SignalHandler);

  CreateSemaphore();
  AllocateShareMemory(nRequestedNumDisks);

  *nMoves = 0;
  *nDisks = nRequestedNumDisks;
  Initialize();

  Solve(naA, naB, naC, *nDisks);

  printf("Number of Moves: %d\n", *nMoves);
  printf("Number of Disks: %d\n", *nDisks);

  shmctl(nShareMemID, IPC_RMID, 0);
  DiscardSemaphore();

  return 0;
}

void CreateSemaphore() {

  nSemaphID = semget(IPC_PRIVATE, 1, SEM_R|SEM_A|IPC_CREAT);

  if (nSemaphID == -1){
    perror("semget failure"); 
    exit(-1); 
  }

  //同時アクセス可能なプロセス数を1に設定したセマフォを作る
  union semun semctlArg;
  semctlArg.val = 1;
  if (semctl(nSemaphID, 0, SETVAL, semctlArg) == -1) {
    perror("semctl(SETVAL) failure"); 
    exit(-1); 
  }

  printf("Semaphore ID = %d\n", nSemaphID);

}

void DiscardSemaphore() {

  if (semctl(nSemaphID, 0, IPC_RMID, 0) == -1) {
    perror("semctl(del) failure"); 
    exit(-1); 
  }
}

void ReserveCriticalRegion(int nSemaphID) {

}

void ReleaseCriticalRegion(int nSemaphID) {

}

void AllocateShareMemory(int nRequestedNumDisks) {

}

void Initialize() {
  int i;

  for(i=0; i<*nDisks; ++i){
    naA[i] = *nDisks - i;
    naB[i] = 0;
    naC[i] = 0;
  }

}

void Solve(int *_naA, int *_naB, int *_naC, int n) {

  if (n) {

    Solve(_naA+1, _naC, _naB, n-1);

    
    *_naB = *_naA;
    //    usleep(100000);
    *_naA = 0;

    (*nMoves)++;


    Solve(_naC, _naB+1, _naA, n-1);

  }

}

void SignalHandler(int h){
  //後片付け
  shmctl(nShareMemID, IPC_RMID, 0);
  DiscardSemaphore();
  exit(1);
}
