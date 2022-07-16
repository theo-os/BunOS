#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void mount_proc() {
  printf("Mounting /proc...");
  if (0 != mount("proc", "/proc", "proc", 0, "")) {
    printf("\nFailed to mount /proc!\n");
    exit(1);
  }
  printf("Done!\n");
}

void mount_sys() {
  printf("Mounting /sys...");
  if (0 != mount("sysfs", "/sys", "sysfs", 0, "")) {
    printf("\nFailed to mount /proc!\n");
    exit(1);
  }
  printf("Done!\n");
}

void mount_dev() {
  printf("Mounting /dev...");
  if (0 != mount("none", "/dev", "devtmpfs", 0, "")) {
    int errno2 = errno;
    // Error code 16 ("device or resource busy") is spurrious and doesn't really
    // matter. Ignore it.
    if (errno2 != 16) {
      printf("\nFailed to mount /dev! errno=%d strerror=%s\n", errno,
             strerror(errno));
      exit(1);
    }
  }
  printf("Done!\n");
}

int main(int argc, char *argv[]) {
  printf("Hello from the init system\n");

  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working dir: %s\n", cwd);
  } else {
    perror("getcwd() error");
    return 1;
  }

  // Bun requires these to be mounted beforehand
  // Otherwise, it causes a "module not found" error.
  mount_proc();
  mount_sys();
  mount_dev();

  /*return execlp("ls", "ls", "./src", NULL);*/
  return execl("/bin/bun", "/bin/bun", "./src/init.js", NULL);
}
