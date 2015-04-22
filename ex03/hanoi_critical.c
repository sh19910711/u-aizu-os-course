#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int *naA; //ËÀA
int *naB; //ËÀB
int *naC; //ËÀC
int nMoves = 0;  //Áí°ÜÆ°²ó¿ô
int nDisks; //±ßÈ×¿ô
int flag_display; // to avoid critical path?

void Initialize();
void Solve(int*, int*, int*, int);
void Display(int);
// added functions
int InputDisksFromCommandLine(int, char *[]);
void AllocateMemory(int);
void FreeMemory();
void SignalHandler(int);

int main(int argc, char *argv[], char *envv[]) {

  signal(SIGUSR1, SignalHandler);

  nDisks = InputDisksFromCommandLine(argc, argv);
  AllocateMemory(nDisks);

  Initialize();

  Solve(naA, naB, naC, nDisks);

  FreeMemory();
}

// Call Display()
void SignalHandler(int code) {
  // set flag
  flag_display = 1;
  // re-add this handler
  signal(SIGUSR1, SignalHandler);
}

void AllocateMemory(int num) {
  naA = malloc(num * sizeof(int));
  naB = malloc(num * sizeof(int));
  naC = malloc(num * sizeof(int));
}

void FreeMemory() {
  free(naA);
  free(naB);
  free(naC);
}

int InputDisksFromCommandLine(int argc, char *argv[]) {
  int disks;
  if ( argc != 2 ) {
    printf("error: invalid args");
    printf("usage: command {nDisks}");
    exit(1);
  }
  sscanf(argv[1], "%d", &disks);
  printf("nDisks = %d\n", disks);
  return disks;
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
    sleep(1); // delay
    *_naA = 0;

    ++nMoves;

    if ( flag_display ) {
      // reset flag
      flag_display = 0;
      // display
      Display(getpid());
    }

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

