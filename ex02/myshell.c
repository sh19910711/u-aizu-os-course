/* ----------------------------------------------------------------- */
/* PROGRAM  shell.c                                                  */
/*    This program reads in an input line, parses the input line     */
/* into tokens, and use execvp() to execute the command.             */
/* ----------------------------------------------------------------- */

#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>
#include  <unistd.h>

/* extra headers */
#include <dirent.h>
#include <fcntl.h>
#include <sys/syscall.h>

struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

void  parse(char *line, char **argv)
{
  while (*line != '\0') {       /* if not the end of line ....... */ 
    while (*line == ' ' || *line == '\t' || *line == '\n')
      *line++ = '\0';     /* replace white spaces with 0    */
    *argv++ = line;          /* save the argument position     */
    while (*line != '\0' && *line != ' ' && 
        *line != '\t' && *line != '\n') 
      line++;             /* skip the argument until ...    */
  }
  *argv = NULL;                 /* mark the end of argument list  */
}

int count_args(char **argv) {
  int i = 0;
  while ( argv[i][0] != '\0' ) {
    i ++;
  }
  return i;
}

/* ls: list files and directories */
/* cat: show file */
int call_shell_function(char **argv) {
  int argc;
  int fd;
  char buf[1024];
  int num;
  int i;
  struct linux_dirent *dirent;

  argc = count_args(argv);

  /* (1) list the files in the current directory */
  if ( ! strcmp("ls", argv[0]) ) {
    /* Open directory */
    fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
    if ( fd == -1 ) {
      printf("*** error: file open\n");
      return 1;
    }

    for (;;) {
      num = syscall(SYS_getdents, fd, buf, sizeof(buf));
      if ( num == -1 ) {
        printf("*** error: read dir\n");
        return 1;
      }
      if ( num == 0 ) {
        break;
      }

      /* Output directory names */
      for ( i = 0; i < num; ) {
        dirent = (struct linux_dirent *)(buf + i);
        /* Ignore dot dirs */
        if ( strcmp(".", dirent->d_name) && strcmp("..", dirent->d_name) ) {
          printf("%s", dirent->d_name);
          if ( i + dirent->d_reclen < num ) {
            printf(" ");
          } else {
            printf("\n");
          }
        }
        i += dirent->d_reclen;
      }
    }

    return 0;
  }
  /* (3) show the contents of this file, as follows */
  else if ( ! strcmp("cat", argv[0]) ) {
    if ( argc != 2 ) {
      printf("usage: cat <filename>\n");
      return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if ( fd == -1 ) {
      printf("*** error: file open");
      return 1;
    }

    for (;;) {
      num = syscall(SYS_read, fd, buf, sizeof(buf));
      if ( num == -1 ) {
        printf("*** error: read file");
      }
      if ( num == 0 ) {
        break;
      }
      syscall(SYS_write, 1, buf, num);
    }

    return 0;
  }
  printf("*** ERROR: command not found\n");
  return 1;
}

int is_shell_function(char *cmd) {
  if ( ! strcmp("ls", cmd) ) return 1;
  if ( ! strcmp("cat", cmd) ) return 1;
  return 0;
}

/* ----------------------------------------------------------------- */
/* FUNCTION execute:                                                 */
/*    This function receives a commend line argument list with the   */
/* first one being a file name followed by its arguments.  Then,     */
/* this function forks a child process to execute the command using  */
/* system call execvp().                                             */
/* ----------------------------------------------------------------- */

void  execute(char **argv)
{
  pid_t  pid;
  int    status;
  char **p;

  if ((pid = fork()) < 0) {     /* fork a child process           */
    printf("*** ERROR: forking child process failed\n");
    exit(1);
  }
  else if (pid == 0) {          /* for the child process:         */
    /* add your code here, execute command using execvp function */
    if ( is_shell_function(argv[0]) ) {
      exit(call_shell_function(argv));
    } else {
      /* convert to NULL for execvp() */
      p = argv;
      while ( *p[0] != '\0' ) {
        p ++;
      }
      *p = NULL;

      /* call program */
      execvp(argv[0], argv);
      printf("*** ERROR: exec failed\n");
      exit(1);
    }
  } else {                                  /* for the parent:      */
    while (wait(&status) != pid)       /* wait for completion  */
      ;
  }
}

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */

int  main(void)
{
  char  line[1024];             /* the input line                 */
  char  *argv[64];              /* the command line argument      */

  while (1) {                   /* repeat until done ....         */
    printf("Shell -> ");     /*   display a prompt             */
    fgets(line,sizeof(line),stdin);              /*   read in the command line     */
    printf("\n");
    parse(line, argv);       /*   parse the line               */
    if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
      exit(0);            /*   exit if it is                */
    execute(argv);           /* otherwise, execute the command */
  }
}


