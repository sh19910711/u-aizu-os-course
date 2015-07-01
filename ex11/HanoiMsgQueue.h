#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MY_MESG_KEY 1234L 

#define MY_MESG_PERMISSION 0666

#define HANOI_MAX_NDISKS 64

typedef struct {
  long int nMessageType;
  int nDisks;
  int nMoves;
  int naA[HANOI_MAX_NDISKS];
  int naB[HANOI_MAX_NDISKS];
  int naC[HANOI_MAX_NDISKS];
} MyMessagePacket;

int nMesgQueueID;

