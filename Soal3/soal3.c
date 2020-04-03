#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    if(argc == 0) {
        printf("masukin argumen gini gan (-f, *, atau -d)");
        exit(EXIT_FAILURE);
    }
    if(strcmp(argv[1], "-f") == 0){
        printf("masuk ke -f gan\n");
    }
    else if(strcmp(argv[1], "-d") == 0){
        printf("masuk ke -d gan\n");
    }
    else if(strcmp(argv[1], "*") == 0){
        printf("masuk ke * gan\n");
        if(argc > 2) {
            printf("kalo *, ya itu aja gan jgn ditambah argumen lain\n");
            exit(EXIT_FAILURE);
        }
    }
    if(argc > 3) {
      printf("kelebihan gan\n");
      exit(EXIT_FAILURE);
    }

  return 0;
}
