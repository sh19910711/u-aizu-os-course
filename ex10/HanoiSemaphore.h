
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#ifndef SEM_R
#define SEM_R 000400
#endif

#ifndef SEM_A
#define SEM_A 000200
#endif

