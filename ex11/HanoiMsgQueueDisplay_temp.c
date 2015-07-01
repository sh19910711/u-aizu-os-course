#include <stdio.h>
#include <stdlib.h>
#include "HanoiMsgQueue.h"

int *naA; //��A
int *naB; //��B
int *naC; //��C
int nMoves = 0;  //���ư���
int nDisks = 20; //���׿�

int ReceiveTowerState();
void Display();

int main(int argc, char *argv[]) {

  nMesgQueueID = msgget(MY_MESG_KEY, 0);
  if (nMesgQueueID < 0) { 
    perror("ERR:msgget"); 
    exit(1); 
  }

  while (ReceiveTowerState() == 0) {

    nMesgQueueID = msgget(MY_MESG_KEY, 0);

    if (nMesgQueueID < 0) exit(1);

  }

  Display();

  free(naA);
  free(naB);
  free(naC);

  return 0;
}

int ReceiveTowerState() {
  int i;

  MyMessagePacket mesgPacket;

  //��������å����������������
  int nMesgLength = ...;

  //msgrcv�ǥ�å������������ꡢ�ɤ߹��ߤ�����������å�������Ĺ����������
  nMesgLength = ...;

  if (nMesgLength < 0) { 
    perror("ERR;msgrcv"); 
    return 0; 
  }

  //������å������ѥ��åȤβ��

  //nDisks����Ȥ������ä��� ������¦��������Ƹ����뤿������ΰ����ݤ���,
  //�⤷����Display�ؿ���MyMessagePacket�������ä���Ȥ���Ϥ���褦�˽񤭴�����



  return nMesgLength;
}

void Display(){

  int i;
  printf("Printing by process %d\n", getpid());

  for(i=nDisks-1; i>=0; i--){
    printf("|%2d|   |%2d|   |%2d|\n", naA[i], naB[i], naC[i]);
  }
  printf("----   ----   ----\n");
  printf("  A      B      C\n");

  printf("Number of Moves: %d\n", nMoves);
  printf("Number of Disks: %d\n", nDisks);

}

