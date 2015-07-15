#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void get_mode_str(int mode, char* s) {
  sprintf(s, "----------");
  if (mode & S_IFDIR) s[0] = 'd';
  if (mode & S_IRUSR) s[1] = 'r';
  if (mode & S_IWUSR) s[2] = 'w';
  if (mode & S_IXUSR) s[3] = 'x';
  if (mode & S_IRGRP) s[4] = 'r';
  if (mode & S_IWGRP) s[5] = 'w';
  if (mode & S_IXGRP) s[6] = 'x';
  if (mode & S_IROTH) s[7] = 'r';
  if (mode & S_IWOTH) s[8] = 'w';
  if (mode & S_IXOTH) s[9] = 'x';
}

void get_group_name(int id, char* s) {
  struct group* grp = getgrgid(id);
  sprintf(s, "%s", grp->gr_name);
}

void get_user_name(int id, char* s) {
  struct passwd* pwd = getpwuid(id);
  sprintf(s, "%s", pwd->pw_name);
}

void get_modified_time(time_t* t, char* s) {
  struct tm* info = localtime(t);
  strftime(s, 26, "%b %d %H:%M", info);
}

void print_info(char* filepath) {
  struct stat file_stat;
  int n_stat;

  n_stat = stat(filepath, &file_stat);

  if (n_stat != 0) {
    printf("stat failed");
    exit(1);
  }

  // exit if not a regular file
  if (!(file_stat.st_mode & S_IFREG)) {
    printf("%s is not a regular file");
    exit(1);
  }

  char mode_str[256];
  get_mode_str(file_stat.st_mode, mode_str);

  char group_name[256];
  get_group_name(file_stat.st_gid, group_name);

  char user_name[256];
  get_user_name(file_stat.st_uid, user_name);

  char modified_time[256];
  get_modified_time(&file_stat.st_mtime, modified_time);

  printf("%s %d %s %s %d %s %s\n",
      mode_str,
      file_stat.st_nlink,
      group_name,
      user_name,
      file_stat.st_size,
      modified_time,
      filepath);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: %s <filename>\n", argv[0]);
    return 0;
  }

  char* filepath = argv[1];
  print_info(filepath);

  return 0;
}
