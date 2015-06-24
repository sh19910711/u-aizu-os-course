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


  Display();


  return 0;
}

void AllocateShareMemory(int nShareMemID) {


}

void ReserveCriticalRegion(int nSemaphID) {

}

void ReleaseCriticalRegion(int nSemaphID) {

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

