#include <stdio.h>
#include <stdlib.h>

#define NDISKS 5

int naA[NDISKS]; //ËÀA
int naB[NDISKS]; //ËÀB
int naC[NDISKS]; //ËÀC
int nMoves = 0;  //Áí°ÜÆ°²ó¿ô
int nDisks = NDISKS; //±ßÈ×¿ô

void Initialize();
void Solve(int*, int*, int*, int);
void Display(int);

int main(int argc, char *argv[], char *envv[]) {

  Initialize();
  Display(getpid());

  Solve(naA, naB, naC, nDisks);
  Display(getpid());

}

void Initialize() {
  int i;

  for(i=0; i<nDisks; i++){
    naA[i] = nDisks-i;
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

    Solve(_naC, _naB+1, _naA, n-1);
  }

}

/* show the Tower of Hanoi */
void Display(int pid){
  int i;

  printf("%s","\033[H\033[2J\n\n");
  printf("Move: %d pid:%d\n", nMoves, pid);
  for(i=nDisks-1; i>=0; i--){
    printf("|%2d|   |%2d|   |%2d|\n", naA[i], naB[i], naC[i]);
  }
  printf("----   ----   ----\n");
  printf("  A      B      C\n");
  printf("Number of Moves: %d\n", nMoves);
  printf("Numer of Disks: %d\n", nDisks);
}

