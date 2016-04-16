#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFERSIZE 64
#define READSIZE 10

int main(){
  int fp = 0;
  if((fp = open("test.txt", O_RDWR)) == -1){
    printf("Can't open file test.txt: %s\n", strerror(errno));
    exit(1);
  }

  char buffer[BUFFERSIZE];
  read(fp, buffer, READSIZE);
  write(fp, "abcdefghij", READSIZE);

  close(fp);

  return 0;
}
