#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ChildProcess(char **argv, char **env, int *naPipeDesc);
void ParentProcess(char **argv, char **env, int *naPipeDesc);

int main(int argc, char *argv[], char *env[]){

  int nPid;
	
  // pipe関数でパイプのファイルディスクリプタを取得
  int naPipeDesc[2];
  pipe(naPipeDesc);

  nPid = fork();

  if (!nPid)         ChildProcess(argv, env, naPipeDesc);
  else if (nPid > 0) ParentProcess(argv, env, naPipeDesc);

  return 0;
}

void ChildProcess(char **argv, char **env, int *naPipeDesc) {

  //bannerコマンドのパス指定
  char *sBannerComm = "/Network/Servers/profsv0831/vol/vol1/home21/nisidate/bin/banner";

  //パイプ関連の処理群


  //banner実行
  //systemの方が楽かもしれません
  //execveを使う場合の注意 :
  //bannerに渡されるargvの0番目は実は何でも良い(コマンド名である"banner"が望ましい)
  //要するに必須なのはbannerプログラム内のargv[1]がAizuなどになっていること


  //子プロセス終了
  exit(0);

}

void ParentProcess(char **argv, char **env, int *naPipeDesc) {

  //sedコマンドのパス指定
  char *sSedComm = "/usr/local/gnu/bin/sed";

  //パイプ関連の処理群


  //bannerの結果を受け取ってsedなので, 子プロセスが実行し終えるのを待つ
  wait(0);
  

  //sed s/#/%c/g 実行 


}
 
