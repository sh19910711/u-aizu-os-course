#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> // for write() function
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "HanoiFileLock.h"

void Initialize();
void Solve(int *,int *,int *,int);
void SaveData(const char*);

int *naA; //棒A
int *naB; //棒B
int *naC; //棒C
unsigned int nMoves = 0;  //総移動回数
int nDisks = 20; //円盤数

int nAlarmSec = 10;
int nSaveRequested = 0;

void sig_handler(int sig) {
  if (sig == SIGALRM) {
    nSaveRequested = 1;
    alarm(nAlarmSec);
  }
}

int main(int argc,char *argv[]){
  if (argc < 2 || argc > 3) {
    printf("Usage: %s [disks] [sec]\n", argv[0]);
    exit(1);
  }

  if (argc >= 2) nDisks = atoi(argv[1]);

  // TODO: メモリ領域確保
  naA = (int*)malloc(sizeof(int) * nDisks);
  naB = (int*)malloc(sizeof(int) * nDisks);
  naC = (int*)malloc(sizeof(int) * nDisks);

  //塔の内容初期化
  Initialize();

  // TODO: アラーム間隔をコマンドラインから受け取り アラームシグナル間隔とハンドラ関数を設定
  if (SIG_ERR == signal(SIGALRM, sig_handler)) {
    printf("error: signal()");
    exit(1);
  }

  if (argc >= 3) nAlarmSec = atoi(argv[2]);
  alarm(nAlarmSec);

  //解く
  Solve(naA, naB, naC, nDisks);	

  SaveData(TMPFILE_NAME);

  //メモリ開放
  free(naA);
  free(naB);
  free(naC);

  return 0;
}

void Initialize() {
  int i;

  for(i=0; i<nDisks; ++i){
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

    if (nSaveRequested) {
      SaveData(TMPFILE_NAME);
      nSaveRequested = 0;
    }

    Solve(_naC, _naB+1, _naA, n-1);

  }

}

void SaveData(const char* sFileName) {

  //ファイルオープン
  int nFileDesc = open(sFileName, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

  // TODO: 塔データ書き込み(flockの効果を確認するときは, 途中にsleepやusleepを挟んでください)
  flock(nFileDesc, LOCK_EX);

  write(nFileDesc, &nDisks, sizeof(int));
  write(nFileDesc, &nMoves, sizeof(unsigned int));
  write(nFileDesc, naA, nDisks * sizeof(int));
  write(nFileDesc, naB, nDisks * sizeof(int));
  write(nFileDesc, naC, nDisks * sizeof(int));

  usleep(100000); // sleep 0.1[sec]

  flock(nFileDesc, LOCK_UN);
}

