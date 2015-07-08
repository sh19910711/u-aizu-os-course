#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for write() function
#include <fcntl.h>
#include <sys/file.h>
#include "HanoiFileLock.h"

void Display(void);
void ReadData(const char*);

int *naA; //棒A
int *naB; //棒B
int *naC; //棒C
unsigned int nMoves = 0;  //総移動回数
int nDisks = 0; //円盤数

int main(int argc,char *argv[]){

  ReadData(TMPFILE_NAME);

  Display();

  free(naA);
  free(naB);
  free(naC);

  return 0;
}  

void ReadData(const char* sFileName) {

  //ファイルオープン
  int nFileDesc = open(sFileName, O_RDONLY);

  // TODO: 円盤数を読み込む
  read(nFileDesc, &nDisks, sizeof(int));
  read(nFileDesc, &nMoves, sizeof(unsigned int));

  // TODO: メモリ領域確保
  naA = (int*)malloc(sizeof(int) * nDisks);
  naB = (int*)malloc(sizeof(int) * nDisks);
  naC = (int*)malloc(sizeof(int) * nDisks);

  // TODO: 円盤数以外のデータも読む
  read(nFileDesc, naA, nDisks * sizeof(int));
  read(nFileDesc, naB, nDisks * sizeof(int));
  read(nFileDesc, naC, nDisks * sizeof(int));
}

void Display(){	
  int i;

  printf("%s","\033[H\033[2J");	

  for (i=nDisks-1; i>=0; --i) {
    printf("|%2d|   |%2d|   |%2d|\n", naA[i], naB[i], naC[i]);
  }
  printf("----   ----   ----\n");
  printf("  1      2      3\n");
  printf("Number of Moves: %d\nNumber of Disks: %d\n\n", nMoves, nDisks);
  fflush(stdout);

}

