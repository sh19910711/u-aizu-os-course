/* Scheduling Simulation*/

#include <stdio.h>
#include <stdlib.h>

/* Process Data Structure */
struct process {
  int pid;                /* Process ID */
  int burst;              /* CPU Burst Time, total CPU time required */
  int priority;           /* Priority */
  int working;            /* Working time, for round-robin scheduling */
  int waiting;            /* Waiting time, for round-robin scheduling */
  struct process *next;
};

/* Function Prototype Declarations */
struct process *init_process (int pid, int burst, int priority);
void fcfs (struct process *proc);
void listprocs (struct process *proc);
void rr (struct process *proc, int quantum);

/* Main Program Segment */
int main (void) {
  /* Initialize process list */
  struct process *plist, *ptmp;
  plist       = init_process(1, 10, 3);
  plist->next = init_process(2,  1, 1); ptmp = plist->next;
  ptmp->next  = init_process(3,  2, 3); ptmp = ptmp->next;
  ptmp->next  = init_process(4,  1, 4); ptmp = ptmp->next;
  ptmp->next  = init_process(5,  5, 2);

  /* Perform simulations */
  listprocs(plist);
  fcfs(plist);
  rr(plist, 1);

  /* Terminate cleanly */
  while (plist != NULL) {
    ptmp = plist;
    plist = plist->next;
    free(ptmp);
  };
  return(0);
};


/* Process list entry initialization routine */
struct process *init_process (int pid, int burst, int priority) {
  struct process *proc;
  proc = malloc(sizeof(struct process));
  if (proc == NULL) {
    printf("Fatal error: memory allocation failure.\nTerminating.\n");
    exit(1);
  };
  proc->pid = pid;
  proc->burst = burst;
  proc->priority = priority;
  proc->working = 0;
  proc->waiting = 0;
  proc->next = NULL;
  return(proc);
};


/* First-Come-First-Served scheduling simulation */
void fcfs (struct process *proc) {
  int time = 0, start, end;
  struct process *tmp = proc;

  printf("BEGIN:\tFirst-Come-First-Served scheduling simulation\n");

  while (tmp != NULL) {
    start = time;

    //add your code here





    end = time;
    printf("Process: %d\tEnd Time: %d\tWaiting: %d\tTurnaround: %d\n", tmp->pid, time, start, end);
    tmp = tmp->next;
  };

  printf("END:\tFirst-Come-First-served scheduling simulation\n\n");
};


/* Process listing */
void listprocs (struct process *proc) {
  struct process *tmp = proc;

  printf("BEGIN:\tProcess Listing\n");

  while (tmp != NULL) {
    printf("PID: %d\t\tPriority: %d\tBurst: %d\n", tmp->pid, tmp->priority, tmp->burst);
    tmp = tmp->next;
  };

  printf("END:\tProcess Listing\n\n");
};

/* Round-Robin scheduling simulation */
void rr (struct process *proc, int quantum) {

  struct process *current;

  printf("BEGIN:\tRound-Robin scheduling simulation (Quantum: %d)\n", quantum);

  int isAllFinished = 0;

  while ( !isAllFinished ) {

    isAllFinished = 1;

    current = proc;
    while ( current != NULL ) {

      if ( current->burst > current->working ) {

        //add working time to the current process






        //add waiting time to the other processes if not finished yet






        isAllFinished = 0;
      }

      current = current->next;
    }

  }

  /* Display statistics */
  current = proc;
  while (current != NULL) {
    printf("Process: %d\tWorking: %d\tWaiting: %d\tTurnaround: %d\n",
        current->pid, current->working, current->waiting, current->working + current->waiting);
    current = current->next;
  };

  printf("END:\tRR scheduling simulation\n\n");
};
