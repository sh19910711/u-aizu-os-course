#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ChildProcess(char **argv, char **env, int *naPipeDesc);
void ParentProcess(char **argv, char **env, int *naPipeDesc);

int main(int argc, char *argv[], char *env[]){

  int nPid;
	
  // pipe�ؿ��ǥѥ��פΥե�����ǥ�������ץ������
  int naPipeDesc[2];
  pipe(naPipeDesc);

  nPid = fork();

  if (!nPid)         ChildProcess(argv, env, naPipeDesc);
  else if (nPid > 0) ParentProcess(argv, env, naPipeDesc);

  return 0;
}

void ChildProcess(char **argv, char **env, int *naPipeDesc) {

  //banner���ޥ�ɤΥѥ�����
  char *sBannerComm = "/Network/Servers/profsv0831/vol/vol1/home21/nisidate/bin/banner";

  //�ѥ��״�Ϣ�ν�����


  //banner�¹�
  //system�������ڤ��⤷��ޤ���
  //execve��Ȥ�������� :
  //banner���Ϥ����argv��0���ܤϼ¤ϲ��Ǥ��ɤ�(���ޥ��̾�Ǥ���"banner"��˾�ޤ���)
  //�פ����ɬ�ܤʤΤ�banner�ץ�������argv[1]��Aizu�ʤɤˤʤäƤ��뤳��


  //�ҥץ�����λ
  exit(0);

}

void ParentProcess(char **argv, char **env, int *naPipeDesc) {

  //sed���ޥ�ɤΥѥ�����
  char *sSedComm = "/usr/local/gnu/bin/sed";

  //�ѥ��״�Ϣ�ν�����


  //banner�η�̤������ä�sed�ʤΤ�, �ҥץ������¹Ԥ�������Τ��Ԥ�
  wait(0);
  

  //sed s/#/%c/g �¹� 


}
 
