#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "HanoiFileLock.h"

void Initialize();
void Solve(int *,int *,int *,int);
void SaveData(const char*);

int *naA; //��A
int *naB; //��B
int *naC; //��C
unsigned int nMoves = 0;  //���ư���
int nDisks = 20; //���׿�

int nAlarmSec = 10;
int nSaveRequested = 0;

int main(int argc,char *argv[]){

  if (argc > 3) {
    printf("Usage: %s [disks] [sec]\n", argv[0]);
    exit(1);
  }

  if (argc >= 2) nDisks = atoi(argv[1]);


  //�����ΰ����

  //������ƽ����
  Initialize();

  //���顼��ֳ֤򥳥ޥ�ɥ饤�󤫤������� ���顼�ॷ���ʥ�ֳ֤ȥϥ�ɥ�ؿ�������

  //��
  Solve(naA, naB, naC, nDisks);	

  SaveData(TMPFILE_NAME);

  //���곫��
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

  //�ե����륪���ץ�
  int nFileDesc = open(sFileName, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

  //��ǡ����񤭹���(flock�θ��̤��ǧ����Ȥ���, �����sleep��usleep�򶴤�Ǥ�������)

}

