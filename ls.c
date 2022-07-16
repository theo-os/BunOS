#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  DIR *mydir;
  struct dirent *myfile;
  struct stat mystat;

  char buf[512];
  mydir = opendir(argv[1]);
  while ((myfile = readdir(mydir)) != NULL) {
    sprintf(buf, "%s/%s", argv[1], myfile->d_name);
    stat(buf, &mystat);
    printf("%zu", mystat.st_size);
    printf(" %s\n", myfile->d_name);
  }
  closedir(mydir);
}
