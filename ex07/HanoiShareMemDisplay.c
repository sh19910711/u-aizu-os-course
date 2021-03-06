#include <stdio.h>
#include <stdlib.h>
#include "HanoiShareMem.h"

void Display();
void AllocateShareMemory(int nShareMemID);

int main(int argc, char *argv[]) {

  int nShareMemID;

  if (argc != 2) {
    printf("Usage: %s ShareMemoryID\n", argv[0]);
    exit(1);
  }

  //引数で指定された円盤数にする
  nShareMemID = atoi(argv[1]);

  //共有メモリ確保と領域割り振り
  AllocateShareMemory(nShareMemID);

  //結果出力
  printf("Number of Moves: %d\n", *nMoves);
  printf("Number of Disks: %d\n", *nDisks);
  Display();

  return 0;
}

void AllocateShareMemory(int nShareMemID) {

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

