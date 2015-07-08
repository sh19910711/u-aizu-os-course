#include <stdio.h>
#include <stdlib.h>
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

  //円盤数を読み込む

  //メモリ領域確保

  //円盤数以外のデータも読む

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

