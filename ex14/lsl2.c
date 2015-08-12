#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>

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

// Check either filepath points to file.
int is_file(char* filepath) {
  struct stat fstat;
  int n_stat;

  n_stat = stat(filepath, &fstat);

  if (n_stat != 0) {
    printf("stat failed\n");
    exit(1);
  }

  if (fstat.st_mode & S_IFREG) {
    return 1;
  } else {
    return 0;
  }
}

void print_entry_info(char* filepath) {
  struct stat file_stat;
  int n_stat;

  n_stat = stat(filepath, &file_stat);

  if (n_stat != 0) {
    printf("stat failed");
    exit(1);
  }

  // exit if not a regular file or directory
  if (!(file_stat.st_mode & S_IFREG) && !(file_stat.st_mode & S_IFDIR) ) {
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

  printf("%s %d %s %s %4d %s %s\n",
      mode_str,
      file_stat.st_nlink,
      group_name,
      user_name,
      file_stat.st_size,
      modified_time,
      filepath);
}

int is_dot(char* s) {
  return *s == '.';
}

// sort by alphabetically order
void sort_paths(int n, char p[1024][1024]) {
  char buf[1024];
  int i;
  int j;
  for (i=0;i<n;++i) {
    for (j=i;j<n;++j) {
      if (strcmp(p[i], p[j]) > 0) {
        strcpy(buf,  p[i]);
        strcpy(p[i], p[j]);
        strcpy(p[j], buf);
      }
    }
  }
}

void print_directory(char* dirpath) {
  struct dirent* entry;
  char dir_paths[1024][1024];
  int num_dir_paths;
  char file_paths[1024][1024];
  int num_file_paths;
  DIR* dir;
  int i;

  dir = opendir(dirpath);
  if (dir == NULL) {
    printf("failed to open directory\n");
    exit(1);
  }

  num_dir_paths = 0;
  num_file_paths = 0;

  entry = readdir(dir);
  while (entry != NULL) {
    // ignore entry starting with dot (.file)
    if (!is_dot(entry->d_name)) {
      if (is_file(entry->d_name)) {
        strcpy(file_paths[num_file_paths++], entry->d_name);
      } else {
        strcpy(dir_paths[num_dir_paths++], entry->d_name);
      }
    }
    entry = readdir(dir);
  }

  sort_paths(num_dir_paths, dir_paths);
  sort_paths(num_file_paths, file_paths);

  for (i=0;i<num_dir_paths;++i) {
    print_entry_info(dir_paths[i]);
  }
  for (i=0;i<num_file_paths;++i) {
    print_entry_info(file_paths[i]);
  }

  closedir(dir);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: %s <file or directory>\n", argv[0]);
    return 0;
  }

  char* file_or_dir_path = argv[1];

  if (is_file(file_or_dir_path)) {
    print_entry_info(file_or_dir_path);
  } else {
    print_directory(file_or_dir_path);
  }

  return 0;
}
