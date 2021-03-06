#include <stdio.h>
#include <stdlib.h>
#include "HanoiMsgQueue.h"

int *naA; //棒A
int *naB; //棒B
int *naC; //棒C
int nMoves = 0;  //総移動回数
int nDisks = 20; //円盤数

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

  //受け取りメッセージサイズを指定
  int nMesgLength = ...;

  //msgrcvでメッセージを受け取り、読み込みに成功したメッセージの長さを受け取る
  nMesgLength = ...;

  if (nMesgLength < 0) { 
    perror("ERR;msgrcv"); 
    return 0; 
  }

  //受信メッセージパケットの解釈

  //nDisksの中身を受け取ったら こちら側に塔情報を再現するためメモリ領域を確保する,
  //もしくはDisplay関数をMyMessagePacketを受け取って中身を出力するように書き換える



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

