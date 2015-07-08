#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/file.h>
#include "HanoiFileLock.h"

void Display(void);
void ReadData(const char*);

int *naA; //��A
int *naB; //��B
int *naC; //��C
unsigned int nMoves = 0;  //���ư���
int nDisks = 0; //���׿�

int main(int argc,char *argv[]){

  ReadData(TMPFILE_NAME);

  Display();

  free(naA);
  free(naB);
  free(naC);

  return 0;
}  

void ReadData(const char* sFileName) {

  //�ե����륪���ץ�
  int nFileDesc = open(sFileName, O_RDONLY);

  //���׿����ɤ߹���

  //�����ΰ����

  //���׿��ʳ��Υǡ������ɤ�

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

