#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "HanoiMsgQueue.h"

void Initialize();
void Solve(int *,int *,int *,int);

void CreateMessageQueue();
void DiscardMessageQueue();

void SignalALRMHandler(int);
void SignalHandler(int);

void SendTowerState();

int *naA; //棒A
int *naB; //棒B
int *naC; //棒C
int nMoves = 0;  //総移動回数
int nDisks = 20; //円盤数

int nSignalALRMReceived = 0;
int nAlarmInterval = 5;

int main(int argc, char *argv[]) {

  int nPid;

  if (argc > 2) {
    fprintf(stderr,"Usage: %s [number_of_disks]\n", argv[0]);
    exit(1); 
  }
  if (argc == 2) nDisks = atoi(argv[1]);

  signal(SIGALRM, SignalALRMHandler);
  alarm(nAlarmInterval);

  signal(SIGINT , SignalHandler);
  signal(SIGQUIT, SignalHandler);
  signal(SIGTERM, SignalHandler);

  Initialize();

  CreateMessageQueue();

  Solve(naA, naB, naC, nDisks);

  DiscardMessageQueue();

  free(naA);
  free(naB);
  free(naC);

  return 0;
}

void Initialize() {
  int i;

  naA = (int*)malloc(sizeof(int)*nDisks);
  naB = (int*)malloc(sizeof(int)*nDisks);
  naC = (int*)malloc(sizeof(int)*nDisks);

  for (i=0; i<nDisks; ++i){
    naA[i] = nDisks - i;
    naB[i] = 0;
    naC[i] = 0;
  }

}

void Solve(int *_naA, int *_naB, int *_naC, int n) {

  if (n) {

    Solve(_naA+1, _naC, _naB, n-1);

    *_naB = *_naA;
    *_naA = 0;

    ++nMoves;

    if (nSignalALRMReceived == 1) { 
      SendTowerState(); 
      printf("Message sent\n");
      nSignalALRMReceived = 0; 
    } 

    sleep(1);

    Solve(_naC, _naB+1, _naA, n-1);

  }

}

void CreateMessageQueue() {

  nMesgQueueID = msgget(MY_MESG_KEY, MY_MESG_PERMISSION|IPC_CREAT);

  if (nMesgQueueID < 0) { 
    perror("ERR:msgget"); 
    exit(1); 
  }
}

void DiscardMessageQueue() {

  if (msgctl(nMesgQueueID, IPC_RMID, NULL) < 0) { 
    perror("Can't RMID queue?"); 
    exit(1); 
  }
}

void SendTowerState() {
  int i;

  int nMesgLength = 0;

  //送信メッセージパケットの作成
  MyMessagePacket mesgPacket;
  mesgPacket.nMessageType = 1;
  mesgPacket.nDisks = nDisks;
  mesgPacket.nMoves = nMoves;
  for (i = 0; i < nDisks; ++ i) {
    mesgPacket.naA[i] = naA[i];
    mesgPacket.naB[i] = naB[i];
    mesgPacket.naC[i] = naC[i];
  }

  //送信メッセージパケットのサイズも指定
  nMesgLength = sizeof(mesgPacket) - sizeof(mesgPacket.nMessageType);

  //メッセージパケットを送信する
  if (msgsnd(nMesgQueueID, (void*)(&mesgPacket), nMesgLength, IPC_NOWAIT) < 0) { 
    perror("ERR:msgsnd"); 
  }
}

void SignalALRMHandler(int code) {

  nSignalALRMReceived = 1;

  alarm(nAlarmInterval);

}

void SignalHandler(int h){
  DiscardMessageQueue();
}
